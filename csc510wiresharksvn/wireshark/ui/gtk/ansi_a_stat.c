/* ansi_a_stat.c
 *
 * Copyright 2003, Michael Lum <mlum [AT] telostech.com>
 * In association with Telos Technology Inc.
 *
 * MUCH code modified from service_response_time_table.c.
 *
 * $Id: ansi_a_stat.c 53230 2013-11-10 15:59:37Z darkjames $
 *
 * Wireshark - Network traffic analyzer
 * By Gerald Combs <gerald@wireshark.org>
 * Copyright 1998 Gerald Combs
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

/*
 * This TAP provides statistics for the ANSI A-Interface:
 */

#include "config.h"

#include <gtk/gtk.h>

#include <stdlib.h>
#include <string.h>

#include "epan/packet_info.h"
#include "epan/epan.h"
#include "epan/value_string.h"
#include <epan/stat_cmd_args.h>
#include <epan/tap.h>
#include <epan/dissectors/packet-bssap.h>
#include <epan/dissectors/packet-ansi_a.h>

#include "../stat_menu.h"

#include "ui/simple_dialog.h"

#include "ui/gtk/gui_stat_menu.h"
#include "ui/gtk/dlg_utils.h"
#include "ui/gtk/filter_dlg.h"
#include "ui/gtk/gui_utils.h"

#include "ui/gtk/old-gtk-compat.h"

enum
{
   IEI_COLUMN,
   MSG_NAME_COLUMN,
   COUNT_COLUMN,
   N_COLUMN /* The number of columns */
};

typedef struct _ansi_a_stat_dlg_t {
    GtkWidget           *win;
    GtkWidget           *scrolled_win;
    GtkWidget           *table;
} ansi_a_stat_dlg_t;

typedef struct _ansi_a_stat_t {
    int                 bsmap_message_type[0xff];
    int                 dtap_message_type[0xff];
} ansi_a_stat_t;


static ansi_a_stat_dlg_t        dlg_bsmap;
static ansi_a_stat_dlg_t        dlg_dtap;
static ansi_a_stat_t            ansi_a_stat;


static void
ansi_a_stat_reset(
    void                *tapdata)
{
    ansi_a_stat_t       *stat_p = (ansi_a_stat_t *)tapdata;

    memset(stat_p, 0, sizeof(ansi_a_stat_t));
}


static gboolean
ansi_a_stat_packet(
    void                *tapdata,
    packet_info         *pinfo _U_,
    epan_dissect_t      *edt _U_,
    const void          *data)
{
    ansi_a_stat_t       *stat_p = (ansi_a_stat_t *)tapdata;
    const ansi_a_tap_rec_t      *data_p = (ansi_a_tap_rec_t *)data;

    switch (data_p->pdu_type)
    {
    case BSSAP_PDU_TYPE_BSMAP:
        stat_p->bsmap_message_type[data_p->message_type]++;
        break;

    case BSSAP_PDU_TYPE_DTAP:
        stat_p->dtap_message_type[data_p->message_type]++;
        break;

    default:
        /*
         * unknown PDU type !!!
         */
        return(FALSE);
    }

    return(TRUE);
}


static void
ansi_a_stat_draw(
    void           *tapdata)
{
    ansi_a_stat_t  *stat_p = (ansi_a_stat_t *)tapdata;
    int             i;
    GtkListStore   *list_store;
    GtkTreeIter     iter;

    if (dlg_bsmap.win && tapdata)
    {
        list_store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW (dlg_bsmap.table))); /* Get store */

        i = 0;
        while (ansi_a_bsmap_strings[i].strptr){
            /* Creates a new row at position. iter will be changed to point to this new row.
             * If position is larger than the number of rows on the list, then the new row will be appended to the list.
             * The row will be filled with the values given to this function.
             * :
             * should generally be preferred when inserting rows in a sorted list store.
             */
            gtk_list_store_insert_with_values( list_store , &iter, G_MAXINT,
                                 IEI_COLUMN, ansi_a_bsmap_strings[i].value,
                                 MSG_NAME_COLUMN, (char *)ansi_a_bsmap_strings[i].strptr,
                                 COUNT_COLUMN, stat_p->bsmap_message_type[ansi_a_bsmap_strings[i].value],
                                 -1);
            i++;
        }
    }

    if (dlg_dtap.win && tapdata){
        i = 0;
        list_store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW (dlg_dtap.table))); /* Get store */


        while (ansi_a_dtap_strings[i].strptr){
            /* Creates a new row at position. iter will be changed to point to this new row.
             * If position is larger than the number of rows on the list, then the new row will be appended to the list.
             * The row will be filled with the values given to this function.
             * :
             * should generally be preferred when inserting rows in a sorted list store.
             */
            gtk_list_store_insert_with_values( list_store , &iter, G_MAXINT,
                                 IEI_COLUMN, ansi_a_dtap_strings[i].value,
                                 MSG_NAME_COLUMN, (char *)ansi_a_dtap_strings[i].strptr,
                                 COUNT_COLUMN, stat_p->dtap_message_type[ansi_a_dtap_strings[i].value],
                                 -1);

            i++;
        }
    }
}

static void
ansi_a_stat_gtk_win_destroy_cb(
    GtkWindow   *win _U_,
    gpointer     user_data )
{
    memset((void *) user_data, 0, sizeof(ansi_a_stat_dlg_t));
}


/* Create list */
static
GtkWidget* create_list(void)
{

    GtkListStore *list_store;
    GtkWidget *list;
    GtkTreeViewColumn *column;
    GtkCellRenderer *renderer;
    GtkTreeSortable *sortable;
    GtkTreeView     *list_view;
    GtkTreeSelection  *selection;

    /* Create the store */
    list_store = gtk_list_store_new(N_COLUMN,           /* Total number of columns XXX  */
                                    G_TYPE_UINT,        /* IEI                          */
                                    G_TYPE_STRING,      /* Message Name                 */
                                    G_TYPE_UINT);       /* Count                        */

    /* Create a view */
    list = gtk_tree_view_new_with_model (GTK_TREE_MODEL (list_store));

    list_view = GTK_TREE_VIEW(list);
    sortable = GTK_TREE_SORTABLE(list_store);

    /* Speed up the list display */
    gtk_tree_view_set_fixed_height_mode(list_view, TRUE);

    /* Setup the sortable columns */
    gtk_tree_sortable_set_sort_column_id(sortable, IEI_COLUMN, GTK_SORT_ASCENDING);
    gtk_tree_view_set_headers_clickable(list_view, FALSE);

    /* The view now holds a reference.  We can get rid of our own reference */
    g_object_unref (G_OBJECT (list_store));

    /*
     * Create the first column packet, associating the "text" attribute of the
     * cell_renderer to the first column of the model
     */
    renderer = gtk_cell_renderer_text_new ();
    column = gtk_tree_view_column_new_with_attributes ("IEI",  renderer,
                                                       "text", IEI_COLUMN,
                                                       NULL);

    gtk_tree_view_column_set_cell_data_func(column, renderer, present_as_hex_func,
                                            GINT_TO_POINTER(IEI_COLUMN), NULL);

    gtk_tree_view_column_set_sort_column_id(column, IEI_COLUMN);
    gtk_tree_view_column_set_resizable(column, TRUE);
    gtk_tree_view_column_set_sizing(column, GTK_TREE_VIEW_COLUMN_FIXED);
    gtk_tree_view_column_set_min_width(column, 50);

    /* Add the column to the view. */
    gtk_tree_view_append_column (list_view, column);

    /* Second column.. Message Name. */
    renderer = gtk_cell_renderer_text_new ();
    column = gtk_tree_view_column_new_with_attributes ("Message Name", renderer,
                                                       "text", MSG_NAME_COLUMN,
                                                       NULL);
    gtk_tree_view_column_set_sort_column_id(column, MSG_NAME_COLUMN);
    gtk_tree_view_column_set_resizable(column, TRUE);
    gtk_tree_view_column_set_sizing(column, GTK_TREE_VIEW_COLUMN_FIXED);
    gtk_tree_view_column_set_min_width(column, 280);
    gtk_tree_view_append_column (list_view, column);

    /* Third column.. Count. */
    renderer = gtk_cell_renderer_text_new ();
    column = gtk_tree_view_column_new_with_attributes ("Count", renderer,
                                                       "text", COUNT_COLUMN,
                                                       NULL);


    gtk_tree_view_column_set_sort_column_id(column, COUNT_COLUMN);
    gtk_tree_view_column_set_resizable(column, TRUE);
    gtk_tree_view_column_set_sizing(column, GTK_TREE_VIEW_COLUMN_FIXED);
    gtk_tree_view_column_set_min_width(column, 50);
    gtk_tree_view_append_column (list_view, column);

    /* Now enable the sorting of each column */
    gtk_tree_view_set_rules_hint(GTK_TREE_VIEW(list_view), TRUE);
    gtk_tree_view_set_headers_clickable(GTK_TREE_VIEW(list_view), TRUE);

    /* Setup the selection handler */
    selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(list));
    gtk_tree_selection_set_mode(selection, GTK_SELECTION_SINGLE);

    return list;

}
static void
ansi_a_stat_gtk_win_create(
    ansi_a_stat_dlg_t   *dlg_p,
    const char          *title)
{
    GtkWidget           *vbox;
    GtkWidget           *bt_close;
    GtkWidget           *bbox;


    dlg_p->win= dlg_window_new(title);  /* transient_for top_level */
    gtk_window_set_destroy_with_parent (GTK_WINDOW(dlg_p->win), TRUE);

    gtk_window_set_default_size(GTK_WINDOW(dlg_p->win), 480, 450);

    vbox=ws_gtk_box_new(GTK_ORIENTATION_VERTICAL, 3, FALSE);
    gtk_container_add(GTK_CONTAINER(dlg_p->win), vbox);
    gtk_container_set_border_width(GTK_CONTAINER(vbox), 12);

    dlg_p->scrolled_win = scrolled_window_new(NULL, NULL);
    gtk_box_pack_start(GTK_BOX(vbox), dlg_p->scrolled_win, TRUE, TRUE, 0);

    dlg_p->table = create_list();
    gtk_widget_show(dlg_p->table);


    gtk_container_add(GTK_CONTAINER(dlg_p->scrolled_win), dlg_p->table);

    /* Button row. */
    bbox = dlg_button_row_new(GTK_STOCK_CLOSE, NULL);
    gtk_box_pack_start(GTK_BOX(vbox), bbox, FALSE, FALSE, 0);

    bt_close = (GtkWidget *)g_object_get_data(G_OBJECT(bbox), GTK_STOCK_CLOSE);
    window_set_cancel_button(dlg_p->win, bt_close, window_cancel_button_cb);

    g_signal_connect(dlg_p->win, "delete_event", G_CALLBACK(window_delete_event_cb), NULL);
    g_signal_connect(dlg_p->win, "destroy", G_CALLBACK(ansi_a_stat_gtk_win_destroy_cb), dlg_p);

    gtk_widget_show_all(dlg_p->win);
    window_present(dlg_p->win);
}

void
ansi_a_stat_gtk_bsmap_cb(GtkAction *action _U_, gpointer user_data _U_)
{
    /*
     * if the window is already open, bring it to front
     */
    if (dlg_bsmap.win)
    {
        gdk_window_raise(gtk_widget_get_window(dlg_bsmap.win));
        return;
    }

    ansi_a_stat_gtk_win_create(&dlg_bsmap, "ANSI A-I/F BSMAP Statistics");
    ansi_a_stat_draw(&ansi_a_stat);
}

void
ansi_a_stat_gtk_dtap_cb(GtkAction *action _U_, gpointer user_data _U_)
{

    /*
     * if the window is already open, bring it to front
     */
    if (dlg_dtap.win)
    {
        gdk_window_raise(gtk_widget_get_window(dlg_dtap.win));
        return;
    }

    ansi_a_stat_gtk_win_create(&dlg_dtap, "ANSI A-I/F DTAP Statistics");
    ansi_a_stat_draw(&ansi_a_stat);
}

void
register_tap_listener_gtkansi_a_stat(void)
{
    GString         *err_p;


    memset((void *) &ansi_a_stat, 0, sizeof(ansi_a_stat_t));

    err_p =
        register_tap_listener("ansi_a", &ansi_a_stat, NULL, 0,
                              ansi_a_stat_reset,
                              ansi_a_stat_packet,
                              ansi_a_stat_draw);

    if (err_p != NULL)
    {
        simple_dialog(ESD_TYPE_ERROR, ESD_BTN_OK, "%s", err_p->str);
        g_string_free(err_p, TRUE);

        exit(1);
    }
}

