/* iface_lists.c
 * Code to manage the global list of interfaces and to update widgets/windows
 * displaying items from those lists
 *
 * $Id: iface_lists.c 52756 2013-10-22 10:36:12Z ruengeler $
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

#ifdef HAVE_LIBPCAP

#include <string.h>

#include <glib.h>

#include <epan/prefs.h>
#include <epan/to_str.h>

#include "../capture_ui_utils.h"

#include "ui/capture_globals.h"
#include "ui/iface_lists.h"
#include "../log.h"

/*
 * Used when sorting an interface list into alphabetical order by
 * their friendly names.
 */
gint
if_list_comparator_alph(const void *first_arg, const void *second_arg)
{
    const if_info_t *first = (const if_info_t *)first_arg, *second = (const if_info_t *)second_arg;

    if (first != NULL && first->friendly_name != NULL &&
        second != NULL && second->friendly_name != NULL) {
        return g_ascii_strcasecmp(first->friendly_name, second->friendly_name);
    } else {
        return 0;
    }
}

/*
 * Fetch the list of local interfaces with capture_interface_list()
 * and set the list of "all interfaces" in *capture_opts to include
 * those interfaces.
 */
void
scan_local_interfaces(void (*update_cb)(void))
{
    GList             *if_entry, *lt_entry, *if_list;
    if_info_t         *if_info, *temp;
    char              *if_string;
    gchar             *descr;
    if_capabilities_t *caps=NULL;
    gint              linktype_count;
    gboolean          monitor_mode;
    GSList            *curr_addr;
    int               ips = 0, i, err;
    guint             count = 0, j;
    if_addr_t         *addr, *temp_addr;
    link_row          *link = NULL;
    data_link_info_t  *data_link_info;
    interface_t       device;
    GString           *ip_str;
    interface_options interface_opts;
    gboolean          found = FALSE;


    if (global_capture_opts.all_ifaces->len > 0) {
        for (i = (int)global_capture_opts.all_ifaces->len-1; i >= 0; i--) {
            device = g_array_index(global_capture_opts.all_ifaces, interface_t, i);
            if (device.local && device.type != IF_PIPE && device.type != IF_STDIN) {
                global_capture_opts.all_ifaces = g_array_remove_index(global_capture_opts.all_ifaces, i);
            }
        }
    }

    /* Scan through the list and build a list of strings to display. */
    if_list = capture_interface_list(&err, NULL, update_cb);
    count = 0;
    for (if_entry = if_list; if_entry != NULL; if_entry = g_list_next(if_entry)) {
        if_info = (if_info_t *)if_entry->data;
        ip_str = g_string_new("");
        ips = 0;
        if (strstr(if_info->name, "rpcap:")) {
            continue;
        }
        device.name = g_strdup(if_info->name);
        if (if_info->friendly_name != NULL) {
            device.friendly_name = g_strdup(if_info->friendly_name);
        } else {
            device.friendly_name = NULL;
        }
        device.hidden = FALSE;
        device.locked = FALSE;
        temp = (if_info_t *)g_malloc0(sizeof(if_info_t));
        temp->name = g_strdup(if_info->name);
        temp->friendly_name = g_strdup(if_info->friendly_name);
        temp->vendor_description = g_strdup(if_info->vendor_description);
        temp->loopback = if_info->loopback;
        /* Is this interface hidden and, if so, should we include it anyway? */

        /* Do we have a user-supplied description? */
        descr = capture_dev_user_descr_find(if_info->name);
        if (descr != NULL) {
            /* Yes, we have a user-supplied description; use it. */
            if_string = g_strdup_printf("%s: %s", descr, if_info->name);
            g_free(descr);
        } else {
            /* No, we don't have a user-supplied description; did we get
            one from the OS or libpcap? */
            if (if_info->friendly_name != NULL) {
                /* We have a friendly name from the OS, use it */
#ifdef _WIN32
                /*
                 * On Windows, if we have a friendly name, just show it,
                 * don't show the name, as that's a string made out of
                 * the device GUID, and not at all friendly.
                 */
                if_string = g_strdup_printf("%s", if_info->friendly_name);
#else
		/*
		 * On UN*X, if we have a friendly name, show it along
		 * with the interface name; the interface name is short
		 * and somewhat friendly, and many UN*X users are used
		 * to interface names, so we should show it.
		 */
                if_string = g_strdup_printf("%s: %s", if_info->friendly_name, if_info->name);
#endif
            } else if (if_info->vendor_description != NULL) {
                /* We have a device description from libpcap - use it. */
                if_string = g_strdup_printf("%s: %s", if_info->vendor_description, if_info->name);
            } else {
                /* No. */
                if_string = g_strdup(if_info->name);
            }
        }
        device.display_name = if_string;
        device.selected = FALSE;
        if (prefs_is_capture_device_hidden(if_info->name)) {
            device.hidden = TRUE;
        }
        device.type = if_info->type;
        monitor_mode = prefs_capture_device_monitor_mode(if_info->name);
        caps = capture_get_if_capabilities(if_info->name, monitor_mode, NULL, update_cb);
        for (; (curr_addr = g_slist_nth(if_info->addrs, ips)) != NULL; ips++) {
            temp_addr = (if_addr_t *)g_malloc0(sizeof(if_addr_t));
            if (ips != 0) {
                g_string_append(ip_str, "\n");
            }
            addr = (if_addr_t *)curr_addr->data;
            if (addr) {
                temp_addr->ifat_type = addr->ifat_type;
                switch (addr->ifat_type) {
                    case IF_AT_IPv4:
                        temp_addr->addr.ip4_addr = addr->addr.ip4_addr;
                        g_string_append(ip_str, ip_to_str((guint8 *)&addr->addr.ip4_addr));
                        break;
                    case IF_AT_IPv6:
                        memcpy(temp_addr->addr.ip6_addr, addr->addr.ip6_addr, sizeof(addr->addr));
                        g_string_append(ip_str,  ip6_to_str((struct e_in6_addr *)&addr->addr.ip6_addr));
                        break;
                    default:
                        /* In case we add non-IP addresses */
                        break;
                }
            } else {
                g_free(temp_addr);
                temp_addr = NULL;
            }
            if (temp_addr) {
                temp->addrs = g_slist_append(temp->addrs, temp_addr);
            }
        }
#ifdef HAVE_PCAP_REMOTE
        device.local = TRUE;
        device.remote_opts.src_type = CAPTURE_IFLOCAL;
        device.remote_opts.remote_host_opts.remote_host = g_strdup(global_capture_opts.default_options.remote_host);
        device.remote_opts.remote_host_opts.remote_port = g_strdup(global_capture_opts.default_options.remote_port);
        device.remote_opts.remote_host_opts.auth_type = global_capture_opts.default_options.auth_type;
        device.remote_opts.remote_host_opts.auth_username = g_strdup(global_capture_opts.default_options.auth_username);
        device.remote_opts.remote_host_opts.auth_password = g_strdup(global_capture_opts.default_options.auth_password);
        device.remote_opts.remote_host_opts.datatx_udp = global_capture_opts.default_options.datatx_udp;
        device.remote_opts.remote_host_opts.nocap_rpcap = global_capture_opts.default_options.nocap_rpcap;
        device.remote_opts.remote_host_opts.nocap_local = global_capture_opts.default_options.nocap_local;
#endif
#ifdef HAVE_PCAP_SETSAMPLING
        device.remote_opts.sampling_method = global_capture_opts.default_options.sampling_method;
        device.remote_opts.sampling_param  = global_capture_opts.default_options.sampling_param;
#endif
        linktype_count = 0;
        device.links = NULL;
        if (caps != NULL) {
#if defined(HAVE_PCAP_CREATE)
            device.monitor_mode_enabled = monitor_mode;
            device.monitor_mode_supported = caps->can_set_rfmon;
#endif
            for (lt_entry = caps->data_link_types; lt_entry != NULL; lt_entry = g_list_next(lt_entry)) {
                data_link_info = (data_link_info_t *)lt_entry->data;
                if (linktype_count == 0) {
                    device.active_dlt = data_link_info->dlt;
                }
                link = (link_row *)g_malloc(sizeof(link_row));
                if (data_link_info->description != NULL) {
                    link->dlt = data_link_info->dlt;
                    link->name = g_strdup_printf("%s", data_link_info->description);
                } else {
                    link->dlt = -1;
                    link->name = g_strdup_printf("%s (not supported)", data_link_info->name);
                }
                device.links = g_list_append(device.links, link);
                linktype_count++;
            }
            if (linktype_count > 0) {
                if ((device.active_dlt = capture_dev_user_linktype_find(if_info->name)) == -1) {
                    device.active_dlt = global_capture_opts.default_options.linktype;
                }
            }
        } else {
#if defined(HAVE_PCAP_CREATE)
            device.monitor_mode_enabled = FALSE;
            device.monitor_mode_supported = FALSE;
#endif
            device.active_dlt = -1;
        }
        device.addresses = g_strdup(ip_str->str);
        device.no_addresses = ips;
        device.local = TRUE;
        device.if_info = *temp;
        device.last_packets = 0;
        if ((device.pmode = capture_dev_user_pmode_find(if_info->name)) == -1) {
            device.pmode = global_capture_opts.default_options.promisc_mode;
        }
        if ((device.has_snaplen = capture_dev_user_hassnap_find(if_info->name)) == -1) {
            device.has_snaplen = global_capture_opts.default_options.has_snaplen;
        }
        if (capture_dev_user_snaplen_find(if_info->name) == -1) {
            device.snaplen = global_capture_opts.default_options.snaplen;
        } else {
            device.snaplen = (guint)capture_dev_user_snaplen_find(if_info->name);
        }
        device.cfilter      = g_strdup(global_capture_opts.default_options.cfilter);
#if defined(_WIN32) || defined(HAVE_PCAP_CREATE)
        if ((device.buffer = capture_dev_user_buffersize_find(if_info->name)) == -1) {
            device.buffer = global_capture_opts.default_options.buffer_size;
        }
#endif

        if (global_capture_opts.ifaces->len > 0) {
            for (j = 0; j < global_capture_opts.ifaces->len; j++) {
                interface_opts = g_array_index(global_capture_opts.ifaces, interface_options, j);
                if (strcmp(interface_opts.name, device.name) == 0) {
#if defined(HAVE_PCAP_CREATE)
                    device.buffer = interface_opts.buffer_size;
                    device.monitor_mode_enabled = interface_opts.monitor_mode;
#endif
                    device.pmode = interface_opts.promisc_mode;
                    device.has_snaplen = interface_opts.has_snaplen;
                    device.snaplen = interface_opts.snaplen;
                    device.cfilter = g_strdup(interface_opts.cfilter);
                    if (interface_opts.linktype != -1) {
                        device.active_dlt = interface_opts.linktype;
                    }
                    device.selected = TRUE;
                    global_capture_opts.num_selected++;
                    break;
                }
            }
        }
        if (global_capture_opts.all_ifaces->len <= count) {
            g_array_append_val(global_capture_opts.all_ifaces, device);
            count = global_capture_opts.all_ifaces->len;
        } else {
            g_array_insert_val(global_capture_opts.all_ifaces, count, device);
        }
        if (caps != NULL) {
            free_if_capabilities(caps);
        }

        g_string_free(ip_str, TRUE);
        count++;
    }
    free_interface_list(if_list);
    /* see whether there are additional interfaces in ifaces */
    for (j = 0; j < global_capture_opts.ifaces->len; j++) {
        interface_opts = g_array_index(global_capture_opts.ifaces, interface_options, j);
        found = FALSE;
        for (i = 0; i < (int)global_capture_opts.all_ifaces->len; i++) {
            device = g_array_index(global_capture_opts.all_ifaces, interface_t, i);
            if (strcmp(device.name, interface_opts.name) == 0) {
                found = TRUE;
                break;
            }
        }
        if (!found) {  /* new interface, maybe a pipe */
            device.name         = g_strdup(interface_opts.name);
            device.display_name = g_strdup_printf("%s: %s", device.name, interface_opts.descr);
            device.hidden       = FALSE;
            device.selected     = TRUE;
            device.type         = IF_PIPE;
#if defined(_WIN32) || defined(HAVE_PCAP_CREATE)
            device.buffer = interface_opts.buffer_size;
#endif
#if defined(HAVE_PCAP_CREATE)
            device.monitor_mode_enabled = interface_opts.monitor_mode;
            device.monitor_mode_supported = FALSE;
#endif
            device.pmode = interface_opts.promisc_mode;
            device.has_snaplen = interface_opts.has_snaplen;
            device.snaplen = interface_opts.snaplen;
            device.cfilter = g_strdup(interface_opts.cfilter);
            device.active_dlt = interface_opts.linktype;
            device.addresses    = NULL;
            device.no_addresses = 0;
            device.last_packets = 0;
            device.links        = NULL;
            device.local        = TRUE;
            device.locked       = FALSE;
            device.if_info.name = g_strdup(interface_opts.name);
            device.if_info.friendly_name = NULL;
            device.if_info.vendor_description = g_strdup(interface_opts.descr);
            device.if_info.addrs = NULL;
            device.if_info.loopback = FALSE;

            g_array_append_val(global_capture_opts.all_ifaces, device);
            global_capture_opts.num_selected++;
        }
    }
}

/*
 * Get the global interface list.  Generate it if we haven't done so 
 * already.  This can be quite time consuming the first time, so 
 * record how long it takes in the info log.
 */
void
fill_in_local_interfaces(void(*update_cb)(void))
{
	GTimeVal start_time;
	GTimeVal end_time;
	float elapsed;
	static gboolean initialized = FALSE;

	/* record the time we started, so we can log total time later */
	g_get_current_time(&start_time);
	g_log(LOG_DOMAIN_MAIN, G_LOG_LEVEL_INFO, "fill_in_local_interfaces() starts");
	
    if (!initialized) {
		/* do the actual work */
        scan_local_interfaces(update_cb);
        initialized = TRUE;
    }
	/* log how long it took */
    g_get_current_time(&end_time);
    elapsed = (float) ((end_time.tv_sec - start_time.tv_sec) +
                        ((end_time.tv_usec - start_time.tv_usec) / 1e6));

    g_log(LOG_DOMAIN_MAIN, G_LOG_LEVEL_INFO, "fill_in_local_interfaces() ends, taking %.3fs", elapsed);
}

void
hide_interface(gchar* new_hide)
{
    gchar       *tok;
    guint       i;
    interface_t device;
    gboolean    found = FALSE;
    GList       *hidden_devices = NULL, *entry;
    if (new_hide != NULL) {
        for (tok = strtok (new_hide, ","); tok; tok = strtok(NULL, ",")) {
            hidden_devices = g_list_append(hidden_devices, tok);
        }
    }
    for (i = 0; i < global_capture_opts.all_ifaces->len; i++) {
        device = g_array_index(global_capture_opts.all_ifaces, interface_t, i);
        found = FALSE;
        for (entry = hidden_devices; entry != NULL; entry = g_list_next(entry)) {
            if (strcmp((char *)entry->data, device.name)==0) {
                device.hidden = TRUE;
                if (device.selected) {
                    device.selected = FALSE;
                    global_capture_opts.num_selected--;
                }
                found = TRUE;
                break;
            }
        }
        if (!found) {
            device.hidden = FALSE;
        }
        global_capture_opts.all_ifaces = g_array_remove_index(global_capture_opts.all_ifaces, i);
        g_array_insert_val(global_capture_opts.all_ifaces, i, device);
    }
}
#endif /* HAVE_LIBPCAP */

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
