/* plugins_dlg.c
 * Dialog boxes for plugins
 *
 * $Id: plugins_dlg.c 53389 2013-11-17 14:03:45Z alagoutte $
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

#include "config.h"

#include <gtk/gtk.h>

#include "epan/plugins.h"

#include "ui/gtk/dlg_utils.h"
#include "ui/gtk/gui_utils.h"
#include "ui/gtk/plugins_dlg.h"

#include "webbrowser.h"

#if defined(HAVE_PLUGINS) || defined(HAVE_LUA)

static gboolean
about_plugins_callback(GtkWidget *widget, GdkEventButton *event, gint id _U_)
{
  GtkTreeSelection *tree_selection;
  GtkTreeModel *model;
  GtkTreeIter  iter;
  gchar        *type;
  gchar        *file;

  tree_selection = gtk_tree_view_get_selection (GTK_TREE_VIEW(widget));

  if (gtk_tree_selection_count_selected_rows (tree_selection) == 0)
    return FALSE;

  if (event->type != GDK_2BUTTON_PRESS)
    /* not a double click */
    return FALSE;

  if (gtk_tree_selection_get_selected (tree_selection, &model, &iter)) {
     gtk_tree_model_get (model, &iter, 2, &type, -1);
     if (strcmp (type, "lua script") == 0) {
        gtk_tree_model_get (model, &iter, 3, &file, -1);
        browser_open_data_file (file);
        g_free (file);
     }
     g_free (type);
  }

  return TRUE;
}

/*
 * Fill the list widget with a list of the plugin modules.
 * XXX - We might want to combine this with plugins_dump_all().
 */
static void
plugins_scan(GtkWidget *list)
{
#ifdef HAVE_PLUGINS
    plugin     *pt_plug;
    const char *sep;
#endif
#ifdef HAVE_LUA
    wslua_plugin  *lua_plug;
#endif
    GString    *type;

#ifdef HAVE_PLUGINS
    for (pt_plug = plugin_list; pt_plug != NULL; pt_plug = pt_plug->next)
    {
        type = g_string_new("");
        sep = "";
        if (pt_plug->register_protoinfo)
        {
            type = g_string_append(type, "dissector");
            sep = ", ";
        }
        if (pt_plug->register_tap_listener)
        {
            type = g_string_append(type, sep);
            type = g_string_append(type, "tap");
            sep = ", ";
        }
        if (pt_plug->register_wtap_module)
        {
            type = g_string_append(type, sep);
            type = g_string_append(type, "file format");
            sep = ", ";
        }
        if (pt_plug->register_codec_module)
        {
            type = g_string_append(type, sep);
            type = g_string_append(type, "codec");
        }
        simple_list_append(list, 0, pt_plug->name, 1, pt_plug->version,
                           2, type->str, 3, g_module_name(pt_plug->handle), -1);
        g_string_free(type, TRUE);
    }
#endif

#ifdef HAVE_LUA
    for (lua_plug = wslua_plugin_list; lua_plug != NULL; lua_plug = lua_plug->next)
    {
        type = g_string_new("");
        type = g_string_append(type, "lua script");

        simple_list_append(list, 0, lua_plug->name, 1, lua_plug->version, 2, type->str, 3, lua_plug->filename, -1);
        g_string_free(type, TRUE);
    }
#endif
}


GtkWidget *
about_plugins_page_new(void)
{
    GtkWidget *scrolledwindow;
    GtkWidget *plugins_list;
    static const gchar *titles[] = {"Name", "Version", "Type", "Path"};


    scrolledwindow = scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(scrolledwindow),
                                   GTK_SHADOW_IN);

    plugins_list = simple_list_new(4, titles);
    plugins_scan(plugins_list);

    /* connect a callback so we can spot a double-click */
    g_signal_connect(plugins_list, "button_press_event",
                     G_CALLBACK(about_plugins_callback), NULL);

    gtk_container_add(GTK_CONTAINER(scrolledwindow), plugins_list);

    return scrolledwindow;
}

#endif /* HAVE_PLUGINS || HAVE_LUA */

/*
 * Editor modelines
 *
 * Local Variables:
 * c-basic-offset: 4
 * tab-width: 8
 * indent-tabs-mode: nil
 * End:
 *
 * ex: set shiftwidth=4 tabstop=8 expandtab:
 * :indentSize=4:tabSize=8:noTabs=true:
 */
