/* packet-wccp.c
 * Routines for Web Cache Communication Protocol dissection
 * Jerry Talkington <jtalkington@users.sourceforge.net>
 *
 * $Id: packet-wccp.c 53194 2013-11-09 14:58:28Z darkjames $
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

#include <glib.h>
#include <epan/packet.h>
#include <epan/to_str.h>
#include <epan/wmem/wmem.h>
#include <epan/ipproto.h>
#include <epan/expert.h>
#include <epan/ipv6-utils.h>
#include <epan/ipv4.h>
#include "packet-wccp.h"

static int proto_wccp = -1;
static int hf_wccp_message_type = -1;   /* the message type */
static int hf_wccp_version = -1;        /* protocol version */
static int hf_message_header_version = -1;
static int hf_hash_revision = -1;       /* the version of the hash */
static int hf_change_num = -1;          /* change number */
static int hf_hash_flag = -1;
static int hf_hash_flag_u = -1;
static int hf_recvd_id = -1;
static int hf_wc_num = -1;
static int hf_wc_view_wc_num = -1;
static int hf_cache_ip = -1;
static int hf_message_header_length = -1;
static int hf_item_type = -1;
static int hf_item_length = -1;
static int hf_item_data = -1;
static int hf_security_info_option = -1;
static int hf_security_info_md5_checksum = -1;
static int hf_command_element_type = -1;
static int hf_command_element_length = -1;
static int hf_command_element_shutdown_ip = -1;
static int hf_service_info_type = -1;
static int hf_service_info_id_standard = -1;
static int hf_service_info_id_dynamic = -1;
static int hf_service_info_priority = -1;
static int hf_service_info_protocol = -1;
static int hf_service_info_flags = -1;
static int hf_service_info_flags_src_ip_hash = -1;
static int hf_service_info_flags_dest_ip_hash = -1;
static int hf_service_info_flags_src_port_hash = -1;
static int hf_service_info_flags_dest_port_hash = -1;
static int hf_service_info_flags_ports_defined = -1;
static int hf_service_info_flags_ports_source = -1;
static int hf_service_info_flags_redirect_only_protocol_0 = -1;
static int hf_service_info_flags_src_ip_alt_hash = -1;
static int hf_service_info_flags_dest_ip_alt_hash = -1;
static int hf_service_info_flags_src_port_alt_hash = -1;
static int hf_service_info_flags_dest_port_alt_hash = -1;
static int hf_service_info_source_port = -1;
static int hf_service_info_destination_port = -1;
static int hf_router_identity_ip = -1;
static int hf_router_identity_receive_id = -1;
static int hf_router_identity_send_to_ip = -1;
static int hf_router_identity_received_from_num = -1;
static int hf_web_cache_identity_ip = -1;
static int hf_web_cache_identity_hash_rev = -1;
static int hf_web_cache_identity_flags = -1;
static int hf_web_cache_identity_flag_hash_info = -1;
static int hf_web_cache_identity_flag_assign_type = -1;
static int hf_web_cache_identity_flag_version_request = -1;
static int hf_mask_value_set_element_value_element_num = -1;
static int hf_assignment_weight = -1;
static int hf_assignment_status = -1;
static int hf_assignment_key_ip = -1;
static int hf_assignment_key_change_num = -1;
static int hf_router_view_member_change_num = -1;
static int hf_router_router_num = -1;
static int hf_router_identity_router_ip = -1;
static int hf_wc_view_info_change_num = -1;
static int hf_wc_view_info_router_ip = -1;
static int hf_wc_view_info_wc_ip = -1;
static int hf_wc_view_router_num = -1;
static int hf_wc_identity_ip_address = -1;
static int hf_router_identity_received_from_ip = -1;
static int hf_router_assignment_element_change_num = -1;
static int hf_assignment_info_router_num = -1;
static int hf_hash_buckets_assignment_wc_num = -1;
static int hf_hash_buckets_assignment_wc_ip = -1;
static int hf_assignment_info_router_ip = -1;
static int hf_router_view_ip = -1;
static int hf_router_query_info_ip = -1;
static int hf_router_query_info_send_to_ip = -1;
static int hf_router_query_info_target_ip = -1;
static int hf_capability_element_type = -1;
static int hf_capability_element_length = -1;
static int hf_capability_info_value = -1;
static int hf_capability_forwarding_method_flag_gre = -1;
static int hf_capability_forwarding_method_flag_l2 = -1;
static int hf_capability_assignment_method_flag_hash = -1;
static int hf_capability_assignment_method_flag_mask = -1;
static int hf_capability_return_method_flag_gre = -1;
static int hf_capability_return_method_flag_l2 = -1;
static int hf_capability_transmit_t = -1;
static int hf_capability_transmit_t_upper_limit = -1;
static int hf_capability_transmit_t_lower_limit = -1;
static int hf_capability_timer_scale_timeout_scale = -1;
static int hf_capability_timer_scale_ra_timer_scale = -1;
static int hf_capability_timer_scale_timeout_scale_upper_limit = -1;
static int hf_capability_timer_scale_timeout_scale_lower_limit = -1;
static int hf_capability_timer_scale_ra_scale_upper_limit = -1;
static int hf_capability_timer_scale_ra_scale_lower_limit = -1;
static int hf_value_element_src_ip = -1;
static int hf_value_element_dest_ip = -1;
static int hf_value_element_src_port = -1;
static int hf_value_element_dest_port = -1;
static int hf_value_element_web_cache_ip = -1;
static int hf_mask_value_set_list_num_elements = -1;
static int hf_mask_element_src_ip = -1;
static int hf_mask_element_dest_ip = -1;
static int hf_mask_element_src_port = -1;
static int hf_mask_element_dest_port = -1;
static int hf_alt_assignment_info_assignment_type = -1;
static int hf_extended_assignment_data_type = -1;
static int hf_alt_assignment_info_assignment_length = -1;
static int hf_alt_assignment_map_assignment_type = -1;
static int hf_alt_assignment_map_assignment_length = -1;
static int hf_extended_assignment_data_length = -1;
static int hf_alt_assignment_info_num_routers = -1;
static int hf_alt_assignment_mask_value_set_element_num_wc_value_elements = -1;
static int hf_web_cache_value_element_wc_address = -1;
static int hf_web_cache_value_element_num_values = -1;
static int hf_alt_assignment_mask_value_set_list_num_elements = -1;
static int hf_address_table_family = -1;
static int hf_address_table_address_length = -1;
static int hf_address_table_length = -1;
static int hf_address_table_element = -1;

static gint ett_wccp = -1;
static gint ett_buckets = -1;
static gint ett_hash_assignment_buckets = -1;
static gint ett_mask_assignment_data_element = -1;
static gint ett_alternate_mask_assignment_data_element = -1;
static gint ett_extended_assigment_data_element = -1;
static gint ett_table_element = -1;
static gint ett_hash_flags = -1;
static gint ett_wc_identity_flags = -1;
static gint ett_cache_info = -1;
static gint ett_security_info = -1;
static gint ett_service_info = -1;
static gint ett_service_flags = -1;
static gint ett_service_info_ports = -1;
static gint ett_wc_view_info_router_element = -1;
static gint ett_router_identity_info = -1;
static gint ett_wc_identity_element = -1;
static gint ett_wc_identity_info = -1;
static gint ett_router_view_info = -1;
static gint ett_wc_view_info = -1;
static gint ett_router_assignment_element = -1;
static gint ett_hash_buckets_assignment_wc_element=-1;
static gint ett_hash_buckets_assignment_buckets=-1;
static gint ett_router_alt_assignment_element = -1;
static gint ett_router_assignment_info = -1;
static gint ett_query_info = -1;
static gint ett_capabilities_info = -1;
static gint ett_capability_element = -1;
static gint ett_capability_forwarding_method = -1;
static gint ett_capability_assignment_method = -1;
static gint ett_capability_return_method = -1;
static gint ett_capability_transmit_t = -1;
static gint ett_capability_timer_scale = -1;
static gint ett_alt_assignment_info = -1;
static gint ett_alt_assignment_map = -1;
static gint ett_address_table = -1;
static gint ett_assignment_map = -1;
static gint ett_command_extension = -1;
static gint ett_alternate_mask_value_set=-1;
static gint ett_alternate_mask_value_set_element=-1;
static gint ett_mv_set_list = -1;
static gint ett_mv_set_element = -1;
static gint ett_mv_set_value_list = -1;
static gint ett_alternate_mv_set_element_list = -1;
static gint ett_web_cache_value_element_list = -1;
static gint ett_alternate_mv_set_element = -1;
static gint ett_value_element = -1;
static gint ett_unknown_info = -1;

static expert_field ei_wccp_missing_security_info = EI_INIT;
static expert_field ei_wccp_missing_service_info = EI_INIT;
static expert_field ei_wccp_missing_wc_id_info = EI_INIT;
static expert_field ei_wccp_missing_router_id_info = EI_INIT;
static expert_field ei_wccp_missing_query_info = EI_INIT;
static expert_field ei_wccp_missing_wc_view_info = EI_INIT;
static expert_field ei_wccp_missing_rtr_view_info = EI_INIT;
static expert_field ei_wccp_contains_redirect_assignment = EI_INIT;
static expert_field ei_wccp_contains_router_id_info = EI_INIT;
static expert_field ei_wccp_contains_rtr_view_info = EI_INIT;
static expert_field ei_wccp_contains_query_info = EI_INIT;
static expert_field ei_wccp_contains_alt_assignment = EI_INIT;
static expert_field ei_wccp_contains_assign_map = EI_INIT;
static expert_field ei_wccp_contains_alt_assignment_map = EI_INIT;
static expert_field ei_wccp_contains_wc_id_info = EI_INIT;
static expert_field ei_wccp_contains_wc_view_info = EI_INIT;
static expert_field ei_wccp_contains_capabilities_info = EI_INIT;
static expert_field ei_wccp_contains_command_extension = EI_INIT;
static expert_field ei_wccp_missing_assignment = EI_INIT;
static expert_field ei_wccp_assignment_length_bad = EI_INIT;
static expert_field ei_wccp_length_bad = EI_INIT;
static expert_field ei_wccp_service_info_priority_nonzero = EI_INIT;
static expert_field ei_wccp_service_info_protocol_nonzero = EI_INIT;
static expert_field ei_wccp_router_identity_receive_id_zero = EI_INIT;
static expert_field ei_wccp_web_cache_identity_hash_rev_zero = EI_INIT;
static expert_field ei_wccp_address_table_family_unknown = EI_INIT;
static expert_field ei_wccp_capability_element_length = EI_INIT;

/*
 * At
 *
 *      http://tools.ietf.org/html/draft-forster-wrec-wccp-v1-00
 *
 * is a copy of the now-expired Internet-Draft for WCCP 1.0.
 *
 * At
 *
 *      http://tools.ietf.org/id/draft-wilson-wrec-wccp-v2-01.txt
 *
 * is an Internet-Draft for WCCP 2.0.
 *
 * http://tools.ietf.org/html/draft-mclaggan-wccp-v2rev1
 *
 * is the current draft for WCCP 2.01
 *
 */

/* This is NOT IANA assigned */
#define UDP_PORT_WCCP           2048

#define WCCPv1                  4
#define WCCPv2                  0x0200
#define WCCPv2r1                0x0201
#define WCCP_HERE_I_AM          7
#define WCCP_I_SEE_YOU          8
#define WCCP_ASSIGN_BUCKET      9
#define WCCP2_HERE_I_AM         10
#define WCCP2_I_SEE_YOU         11
#define WCCP2_REDIRECT_ASSIGN   12
#define WCCP2_REMOVAL_QUERY     13

static const value_string wccp_type_vals[] = {
  { WCCP_HERE_I_AM,        "1.0 Here I am" },
  { WCCP_I_SEE_YOU,        "1.0 I see you" },
  { WCCP_ASSIGN_BUCKET,    "1.0 Assign bucket" },
  { WCCP2_HERE_I_AM,       "2.0 Here I am" },
  { WCCP2_I_SEE_YOU,       "2.0 I see you" },
  { WCCP2_REDIRECT_ASSIGN, "2.0 Redirect assign" },
  { WCCP2_REMOVAL_QUERY,   "2.0 Removal query" },
  { 0,                     NULL }
};

static const value_string wccp_version_val[] = {
  { WCCPv1, "1"},
  { WCCPv2, "2"},
  { WCCPv2r1, "2.01"},
  { 0, NULL}
};

const true_false_string tfs_defined_not_defined = { "Defined", "Not defined" };
const true_false_string tfs_src_dest_port = { "Source port", "Destination port" };
const true_false_string tfs_redirect_protocol0 = { "Redirect only protocol 0 (IP)", "Redirect all traffic" };
const true_false_string tfs_historical_current = { "Historical", "Current" };
const true_false_string tfs_version_min_max = {"WCCP version set is maximum supported by CE", "WCCP version set is minimum supported by CE"};

static const value_string wccp_address_family_val[] = {
  { 0, "Reserved" },
  { 1, "IPv4" },
  { 2, "IPv6" },
  { 0, NULL }
};


#define WCCP2_HASH_ASSIGNMENT_TYPE         0
#define WCCP2_MASK_ASSIGNMENT_TYPE         1
#define WCCP2r1_ALT_MASK_ASSIGNMENT_TYPE   2
#define WCCP2r1_ASSIGNMENT_WEIGHT_STATUS   3

static const value_string assignment_type_vals[] = {
  { WCCP2_HASH_ASSIGNMENT_TYPE, "Hash" },
  { WCCP2_MASK_ASSIGNMENT_TYPE, "Mask" },
  { WCCP2r1_ALT_MASK_ASSIGNMENT_TYPE, "WCCP2r1 Alternate Mask"},
  { WCCP2r1_ASSIGNMENT_WEIGHT_STATUS, "WCCP2r1 Assignment Weight Status"},
  { 0,                          NULL }
};

#define HASH_INFO_SIZE          (4*(1+8+1))

#define WCCP2_SECURITY_INFO             0
#define WCCP2_SERVICE_INFO              1
#define WCCP2_ROUTER_ID_INFO            2
#define WCCP2_WC_ID_INFO                3
#define WCCP2_RTR_VIEW_INFO             4
#define WCCP2_WC_VIEW_INFO              5
#define WCCP2_REDIRECT_ASSIGNMENT       6
#define WCCP2_QUERY_INFO                7
#define WCCP2_CAPABILITIES_INFO         8
#define WCCP2_ALT_ASSIGNMENT            13
#define WCCP2_ASSIGN_MAP                14
#define WCCP2_COMMAND_EXTENSION         15
/* WCCP 2 r1 additions: */
#define WCCP2r1_ALT_ASSIGNMENT_MAP      16
#define WCCP2r1_ADDRESS_TABLE           17

  static const value_string info_type_vals[] = {
    { WCCP2_SECURITY_INFO,       "Security Info" },
    { WCCP2_SERVICE_INFO,        "Service Info" },
    { WCCP2_ROUTER_ID_INFO,      "Router Identity Info" },
    { WCCP2_WC_ID_INFO,          "Web-Cache Identity Info" },
    { WCCP2_RTR_VIEW_INFO,       "Router View Info" },
    { WCCP2_WC_VIEW_INFO,        "Web-Cache View Info" },
    { WCCP2_REDIRECT_ASSIGNMENT, "Assignment Info" },
    { WCCP2_QUERY_INFO,          "Router Query Info" },
    { WCCP2_CAPABILITIES_INFO,   "Capabilities Info" },
    { WCCP2_ALT_ASSIGNMENT,      "Alternate Assignment" },
    { WCCP2_ASSIGN_MAP,          "Assignment Map" },
    { WCCP2_COMMAND_EXTENSION,   "Command Extension" },
    { WCCP2r1_ALT_ASSIGNMENT_MAP, "Alternative Assignment Map" },
    { WCCP2r1_ADDRESS_TABLE,      "Address Table" },
    { 0,                         NULL }
  };

const value_string service_id_vals[] = {
  { 0x00, "HTTP" },
  { 0,    NULL }
};

typedef struct capability_flag {
  guint32 value;
  const char *short_name;
  int* phf;
} capability_flag;




#define WCCP2_WEB_CACHE_ASSIGNMENT_DATA_TYPE_HASH        0
#define WCCP2_WEB_CACHE_ASSIGNMENT_DATA_TYPE_MASK        1
#define WCCP2_WEB_CACHE_ASSIGNMENT_DATA_TYPE_NOT_PRESENT 2
#define WCCP2_WEB_CACHE_ASSIGNMENT_DATA_TYPE_EXTENDED    3

static const value_string wccp_web_cache_assignment_data_type_val[] = {
  { WCCP2_WEB_CACHE_ASSIGNMENT_DATA_TYPE_HASH        , "Hash Assignment Data Element"},
  { WCCP2_WEB_CACHE_ASSIGNMENT_DATA_TYPE_MASK        , "Mask Assignment Data Element"},
  { WCCP2_WEB_CACHE_ASSIGNMENT_DATA_TYPE_NOT_PRESENT , "Assignment Data Element Not Present"},
  { WCCP2_WEB_CACHE_ASSIGNMENT_DATA_TYPE_EXTENDED    , "Extended Assignment Data Element"},
  { 0,                          NULL }
};

#define WCCP2_FORWARDING_METHOD         0x01
#define WCCP2_ASSIGNMENT_METHOD         0x02
#define WCCP2_PACKET_RETURN_METHOD      0x03
#define WCCP2_TRANSMIT_T                0x04
#define WCCP2_TIMER_SCALE               0x05

static const value_string capability_type_vals[] = {
  { WCCP2_FORWARDING_METHOD,    "Forwarding Method" },
  { WCCP2_ASSIGNMENT_METHOD,    "Assignment Method" },
  { WCCP2_PACKET_RETURN_METHOD, "Packet Return Method" },
  { WCCP2_TRANSMIT_T,           "Transmit_t Message interval values"},
  { WCCP2_TIMER_SCALE,          "Timer_scale Timeout scale values"},
  { 0, NULL }
};


/* with version 2.01 we now have a address table which is possibly present */

typedef struct wccp_address_table {
  gboolean in_use;
  gint16 family;
  gint16 version;
  guint16 table_length;
  guint32 *table_ipv4;
  struct e_in6_addr *table_ipv6;
} wccp_address_table;


wccp_address_table wccp_wccp_address_table;

static guint dissect_hash_data(tvbuff_t *tvb, int offset,
                               proto_tree *wccp_tree);
static guint dissect_web_cache_list_entry(tvbuff_t *tvb, int offset,
                                          int idx, proto_tree *wccp_tree);
static int wccp_bucket_info(guint8 bucket_info, proto_tree *bucket_tree,
                            guint32 start, tvbuff_t *tvb, int offset);
static gchar *bucket_name(guint8 bucket);
static guint16 dissect_wccp2_header(tvbuff_t *tvb, int offset,
                                    proto_tree *wccp_tree);
static void dissect_wccp2_info(tvbuff_t *tvb, int offset, guint16 length,
                               packet_info *pinfo, proto_tree *wccp_tree, guint32 wccp_message_type);

/* WCCP 2r1 IPv6 utlility functions */
static void find_wccp_address_table(tvbuff_t *tvb, int offset, guint16 length,
                                    packet_info *pinfo _U_, proto_tree *wccp_tree _U_);
/* The V2 dissectors will return the remaining length of the packet
   and a negative number if there are missing bytes to finish the
   dissection */
static gint dissect_wccp2_security_info(tvbuff_t *tvb, int offset, gint lengreth,
                                        packet_info *pinfo _U_, proto_tree *info_tree);
static gint dissect_wccp2_service_info(tvbuff_t *tvb, int offset, gint length,
                                       packet_info *pinfo, proto_tree *info_tree);
static gint  dissect_wccp2r1_address_table_info(tvbuff_t *tvb, int offset,
                                                int length, packet_info *pinfo, proto_tree *info_tree);
static gint dissect_wccp2_router_identity_info(tvbuff_t *tvb, int offset, gint length,
                                               packet_info *pinfo _U_, proto_tree *info_tree);
static gint dissect_wccp2_wc_identity_info(tvbuff_t *tvb, int offset, gint length,
                                           packet_info *pinfo _U_, proto_tree *info_tree);
static gint dissect_wccp2_router_view_info(tvbuff_t *tvb, int offset, gint length,
                                           packet_info *pinfo _U_, proto_tree *info_tree);
static gint dissect_wccp2_web_cache_view_info(tvbuff_t *tvb, int offset, gint length,
                                              packet_info *pinfo _U_, proto_tree *info_tree);
static gint dissect_wccp2_assignment_info(tvbuff_t *tvb, int offset, gint length,
                                          packet_info *pinfo _U_, proto_tree *info_tree);
static gint dissect_wccp2_hash_buckets_assignment_element(tvbuff_t *tvb, int offset, gint length,
                                                          packet_info *pinfo, proto_tree *info_tree);
static gboolean dissect_wccp2_router_query_info(tvbuff_t *tvb, int offset, gint length,
                                                packet_info *pinfo _U_, proto_tree *info_tree);
static gint dissect_wccp2_capability_info(tvbuff_t *tvb, int offset, gint length,
                                          packet_info *pinfo _U_, proto_tree *info_tree);
static gint dissect_wccp2_alternate_assignment_info(tvbuff_t *tvb, int offset, gint length,
                                                    packet_info *pinfo, proto_tree *info_tree);
static gint dissect_wccp2_hash_assignment_info(tvbuff_t *tvb, int offset, gint length,
                                               packet_info *pinfo _U_, proto_tree *info_tree);
static gint dissect_wccp2_assignment_map(tvbuff_t *tvb, int offset,
                                         int length, packet_info *pinfo _U_, proto_tree *info_tree);
static gint  dissect_wccp2r1_alt_assignment_map_info(tvbuff_t *tvb, int offset,
                                                     int length, packet_info *pinfo, proto_tree *info_tree);
static gint  dissect_wccp2_command_extension(tvbuff_t *tvb, int offset,
                                             int length, packet_info *pinfo _U_, proto_tree *info_tree);
static void dissect_wccp2_router_identity_element(tvbuff_t *tvb, int offset, packet_info *pinfo,
                                                  proto_tree *tree);
static gint dissect_wccp2_web_cache_identity_element(tvbuff_t *tvb, int offset, gint length, packet_info *pinfo,
                                                     proto_tree *info_tree);
static gint dissect_wccp2_hash_assignment_data_element(tvbuff_t *tvb, int offset, gint length, packet_info *pinfo,
                                                       proto_tree *info_tree);
static gint dissect_wccp2_mask_assignment_data_element(tvbuff_t *tvb, int offset, gint length, packet_info *pinfo,
                                                       proto_tree *info_tree) ;
static gint dissect_wccp2_alternate_mask_assignment_data_element(tvbuff_t *tvb, int offset, gint length, packet_info *pinfo,
                                                                 proto_tree *info_tree);
static gint dissect_wccp2_assignment_weight_and_status_element(tvbuff_t *tvb, int offset, gint length, packet_info *pinfo,
                                                               proto_tree *info_tree);
static gint dissect_wccp2_extended_assignment_data_element(tvbuff_t *tvb, int offset, gint length, packet_info *pinfo,
                                                           proto_tree *info_tree);
static gint dissect_wccp2_assignment_key_element(tvbuff_t *tvb, int offset, gint length, packet_info *pinfo,
                                                 proto_tree *info_tree);
static void dissect_wccp2_router_assignment_element(tvbuff_t *tvb, int offset, gint length,
                                                    packet_info *pinfo, proto_tree *info_tree) ;
static gint dissect_wccp2_capability_element(tvbuff_t *tvb, int offset, gint length,
                                             packet_info *pinfo _U_, proto_tree *info_tree);
static gint  dissect_wccp2_mask_value_set_list(tvbuff_t *tvb, int offset,
                                               int length, packet_info *pinfo, proto_tree *info_tree);

/* Utility functions */
static gint dissect_wccp2_mask_value_set_element(tvbuff_t *tvb, int offset,
                                                 gint length, int idx, packet_info *pinfo, proto_tree *info_tree);
static gint dissect_wccp2_mask_element(tvbuff_t *tvb, int offset,
                                       gint length, packet_info *pinfo, proto_tree *info_tree);
static gint dissect_wccp2_value_element(tvbuff_t *tvb, int offset,
                                        gint length, int idx, packet_info *pinfo, proto_tree *info_tree);
static gint dissect_wccp2_alternate_mask_value_set_list(tvbuff_t *tvb, int offset,
                                                        gint length, packet_info *pinfo _U_, proto_tree *info_tree);
static gint dissect_wccp2_alternate_mask_value_set_element(tvbuff_t *tvb, int offset, gint length, guint el_index, packet_info *pinfo, proto_tree *info_tree);
static gint dissect_wccp2_web_cache_value_element(tvbuff_t *tvb, int offset,
                                                  gint length,  packet_info *pinfo, proto_tree *info_tree);
static gchar *assignment_bucket_name(guint8 bucket);
static void dissect_32_bit_capability_flags(tvbuff_t *tvb, int curr_offset,
                                            guint16 capability_val_len, gint ett, const capability_flag *flags,
                                            proto_tree *element_tree, proto_item *header);
static void dissect_transmit_t_capability(tvbuff_t *tvb, proto_item *te, int curr_offset,
                                          guint16 capability_val_len, gint ett, proto_tree *element_tree);
static void dissect_timer_scale_capability(tvbuff_t *tvb, int curr_offset,
                                           guint16 capability_val_len, gint ett, proto_tree *element_tree);




/*
 * In WCCP 2.01 addresses are encoded to support IPv6 with 32 bit fields
 *
 * handle the decoding
 */

static void
find_wccp_address_table(tvbuff_t *tvb, int offset, guint16 length,
                        packet_info *pinfo _U_, proto_tree *wccp_tree _U_)
{
  guint16 type;
  guint16 item_length;

  /* first clean up: */
  wccp_wccp_address_table.in_use = FALSE;
  wccp_wccp_address_table.family = -1;
  wccp_wccp_address_table.version = -1;
  wccp_wccp_address_table.table_length = 0;
  wccp_wccp_address_table.table_ipv4 = (guint32 *) NULL;
  wccp_wccp_address_table.table_ipv6 = (struct e_in6_addr *)NULL;

  while (length >= 4) {
    type = tvb_get_ntohs(tvb, offset);
    item_length = tvb_get_ntohs(tvb, offset+2);

    if (item_length > tvb_length_remaining(tvb, offset))
      return;

    if (type == WCCP2r1_ADDRESS_TABLE)
      {
        dissect_wccp2r1_address_table_info(tvb, offset+4, item_length, NULL, NULL);
        /* no need to decode the rest */
        return;
      }

    /* check if we _can_ advance */
    if (length < (item_length+4))
      return;

    offset = offset + item_length + 4;
    length = length - item_length - 4;
  }
}


/* This function prints the IP or the encoded IP if the table exists */

/* at most an IPv6 IP: see
   http://stackoverflow.com/questions/166132/maximum-length-of-the-textual-representation-of-an-ipv6-address

   39 = 8 groups of 4 digits with 7 : characters

   or

   45 = IPv4 tunnel features: 0000:0000:0000:0000:0000:0000:192.168.0.1
*/

/* problem here is that the IP is in network byte order for IPv4
   we need to fix that
*/

static void wccp_fmt_ipadddress(gchar *buffer, guint32 host_addr)
{
  /* are we using an address table? */
  if (! wccp_wccp_address_table.in_use)
    {
      /* no return the IPv4 IP */
      /* first fix the byte order */
      guint addr= GUINT32_SWAP_LE_BE(host_addr);

      ip_to_str_buf( (guint8 *) &addr, buffer, ITEM_LABEL_LENGTH);
      return;
    }
  else
    {
      /* we need to decode the encoded address: */
      guint16 reserv = (host_addr & 0xFF00) >> 16;
      guint16 addr_index  = (host_addr & 0x00FF);

      if (reserv != 0) {
        g_snprintf(buffer, ITEM_LABEL_LENGTH, "INVALID: reserved part non zero");
        return;
      }

      /* now check if it's IPv4 or IPv6 we need to print */
      switch (wccp_wccp_address_table.family) {
      case 1:
        /* IPv4 */

        /* special case: index 0 -> undefined IP */
        if (addr_index == 0) {
          g_snprintf(buffer, ITEM_LABEL_LENGTH, "0.0.0.0");
          return;
        }
        /* are we be beyond the end of the table? */
        if (addr_index > wccp_wccp_address_table.table_length) {
          g_snprintf(buffer, ITEM_LABEL_LENGTH, "INVALID IPv4 index: %d > %d",
                     addr_index, wccp_wccp_address_table.table_length);
          return;
        }

        /* ok get the IP */
        if (wccp_wccp_address_table.table_ipv4 != NULL) {
          ip_to_str_buf( (guint8 *) &(wccp_wccp_address_table.table_ipv4[addr_index-1]), buffer, ITEM_LABEL_LENGTH);
          return;
        }
        else {
          g_snprintf(buffer, ITEM_LABEL_LENGTH, "INVALID IPv4 table empty!");
          return;
        }
        break;
      case 2:
        /* IPv6 */
        /* special case: index 0 -> undefined IP */
        if (addr_index == 0) {
          g_snprintf(buffer, ITEM_LABEL_LENGTH, "::");
          return;
        }

        /* are we be beyond the end of the table? */
        if (addr_index > wccp_wccp_address_table.table_length) {
          g_snprintf(buffer, ITEM_LABEL_LENGTH, "INVALID IPv6 index: %d > %d",
                     addr_index, wccp_wccp_address_table.table_length);
          return;
        }

        /* ok get the IP */
        if (wccp_wccp_address_table.table_ipv6 != NULL) {
          ip6_to_str_buf(&(wccp_wccp_address_table.table_ipv6[addr_index-1]), buffer);
          return;
        }
        else {
          g_snprintf(buffer, ITEM_LABEL_LENGTH, "INVALID IPv6 table empty!");
          return;
        }
        break;
      default:
        g_snprintf(buffer, ITEM_LABEL_LENGTH, "INVALID IP family");
        return;
      }
    }
}


#define WCCP_IP_MAX_LENGTH (MAX_IP_STR_LEN > 46 ? MAX_IP_STR_LEN : 46)


static const gchar * decode_wccp_encoded_address(tvbuff_t *tvb, int offset, packet_info *pinfo _U_, proto_tree *info_tree _U_)
{
  gchar *buffer;
  guint32 host_addr;

  buffer= (char *) wmem_alloc(wmem_packet_scope(), WCCP_IP_MAX_LENGTH+1);
  host_addr = tvb_get_ntohl(tvb,offset);

  wccp_fmt_ipadddress(buffer, host_addr);
  return buffer;
}

static int
dissect_wccp(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, void *data _U_)
{
  int offset = 0;
  proto_tree *wccp_tree = NULL;
  proto_item *wccp_tree_item;
  guint32 wccp_message_type;
  guint16 length;
  guint32 cache_count;
  guint32 ipaddr;
  guint i;

  wccp_message_type = tvb_get_ntohl(tvb, offset);

  /* Check if this is really a WCCP message */
  if (try_val_to_str(wccp_message_type, wccp_type_vals) == NULL)
    return 0;

  col_set_str(pinfo->cinfo, COL_PROTOCOL, "WCCP");

  col_add_str(pinfo->cinfo, COL_INFO, val_to_str(wccp_message_type,
                                                   wccp_type_vals, "Unknown WCCP message (%u)"));

  wccp_tree_item = proto_tree_add_item(tree, proto_wccp, tvb, offset, -1, ENC_NA);
  wccp_tree = proto_item_add_subtree(wccp_tree_item, ett_wccp);

  proto_tree_add_uint(wccp_tree, hf_wccp_message_type, tvb, offset, 4, wccp_message_type);
  offset += 4;

  switch (wccp_message_type) {

    case WCCP_HERE_I_AM:
      proto_tree_add_item(wccp_tree, hf_wccp_version, tvb,
                          offset, 4, ENC_BIG_ENDIAN);
      offset += 4;
      offset = dissect_hash_data(tvb, offset, wccp_tree);
      proto_tree_add_item(wccp_tree, hf_recvd_id, tvb, offset,
                          4, ENC_BIG_ENDIAN);
      /*offset += 4;*/
      break;

    case WCCP_I_SEE_YOU:
      proto_tree_add_item(wccp_tree, hf_wccp_version, tvb,
                          offset, 4, ENC_BIG_ENDIAN);
      offset += 4;
      proto_tree_add_item(wccp_tree, hf_change_num, tvb, offset,
                          4, ENC_BIG_ENDIAN);
      offset += 4;
      proto_tree_add_item(wccp_tree, hf_recvd_id, tvb, offset,
                          4, ENC_BIG_ENDIAN);
      offset += 4;
      cache_count = tvb_get_ntohl(tvb, offset);
      proto_tree_add_uint(wccp_tree, hf_wc_num, tvb, offset, 4, cache_count);
      offset += 4;
      for (i = 0; i < cache_count; i++) {
        offset = dissect_web_cache_list_entry(tvb, offset, i,
                                              wccp_tree);
      }
      break;

    case WCCP_ASSIGN_BUCKET:
      /*
       * This hasn't been tested, since I don't have any
       * traces with this in it.
       *
       * The V1 spec claims that this does, indeed,
       * have a Received ID field after the type,
       * rather than a Version field.
       */
      proto_tree_add_item(wccp_tree, hf_recvd_id, tvb, offset,
                          4, ENC_BIG_ENDIAN);
      offset += 4;
      cache_count = tvb_get_ntohl(tvb, offset);
      proto_tree_add_uint(wccp_tree, hf_wc_num, tvb, offset, 4, cache_count);
      offset += 4;
      for (i = 0; i < cache_count; i++) {
        ipaddr = tvb_get_ipv4(tvb, offset);
        proto_tree_add_ipv4_format(wccp_tree,
                                   hf_cache_ip, tvb, offset, 4,
                                   ipaddr,
                                   "Web Cache %d IP Address: %s", i,
                                   ip_to_str((guint8 *)&ipaddr));
        offset += 4;
      }
      for (i = 0; i < 256; i += 4) {
        proto_tree_add_text(wccp_tree, tvb, offset, 4,
                            "Buckets %d - %d: %10s %10s %10s %10s",
                            i, i + 3,
                            bucket_name(tvb_get_guint8(tvb, offset)),
                            bucket_name(tvb_get_guint8(tvb, offset+1)),
                            bucket_name(tvb_get_guint8(tvb, offset+2)),
                            bucket_name(tvb_get_guint8(tvb, offset+3)));
        offset += 4;
      }
      break;

    case WCCP2_HERE_I_AM:
    case WCCP2_I_SEE_YOU:
    case WCCP2_REMOVAL_QUERY:
    case WCCP2_REDIRECT_ASSIGN:
    default:    /* assume unknown packets are v2 */
      length = dissect_wccp2_header(tvb, offset, wccp_tree);
      offset += 4;
      dissect_wccp2_info(tvb, offset, length, pinfo, wccp_tree, wccp_message_type);
      break;
  }

  return tvb_length(tvb);
}

static guint
dissect_hash_data(tvbuff_t *tvb, int offset, proto_tree *wccp_tree)
{
  proto_item *bucket_item;
  proto_tree *bucket_tree;
  proto_item *tf;
  proto_tree *field_tree;
  int i;
  guint8 bucket_info;
  int n;

  proto_tree_add_item(wccp_tree, hf_hash_revision, tvb, offset, 4,
                      ENC_BIG_ENDIAN);
  offset += 4;

  bucket_item = proto_tree_add_text(wccp_tree, tvb, offset, 32,
                                    "Hash information");
  bucket_tree = proto_item_add_subtree(bucket_item, ett_buckets);

  for (i = 0, n = 0; i < 32; i++) {
    bucket_info = tvb_get_guint8(tvb, offset);
    n = wccp_bucket_info(bucket_info, bucket_tree, n, tvb, offset);
    offset += 1;
  }
  tf = proto_tree_add_item(wccp_tree, hf_hash_flag, tvb, offset, 4, ENC_BIG_ENDIAN);
  field_tree = proto_item_add_subtree(tf, ett_hash_flags);
  proto_tree_add_item(field_tree, hf_hash_flag_u, tvb, offset, 4, ENC_BIG_ENDIAN);
  offset += 4;
  return offset;
}

static guint
dissect_web_cache_list_entry(tvbuff_t *tvb, int offset, int idx,
                             proto_tree *wccp_tree)
{
  proto_item *tl;
  proto_tree *list_entry_tree;

  tl = proto_tree_add_text(wccp_tree, tvb, offset, 4 + HASH_INFO_SIZE,
                           "Web-Cache List Entry(%d)", idx);
  list_entry_tree = proto_item_add_subtree(tl, ett_cache_info);
  proto_tree_add_item(list_entry_tree, hf_cache_ip, tvb, offset, 4,
                      ENC_BIG_ENDIAN);
  offset += 4;
  offset = dissect_hash_data(tvb, offset, list_entry_tree);
  return offset;
}

/*
 * wccp_bucket_info()
 * takes an integer representing a "Hash Information" bitmap, and spits out
 * the corresponding proto_tree entries, returning the next bucket number.
 */
static int
wccp_bucket_info(guint8 bucket_info, proto_tree *bucket_tree, guint32 start,
                 tvbuff_t *tvb, int offset)
{
  guint32 i;

  for(i = 0; i < 8; i++) {
    proto_tree_add_text(bucket_tree, tvb, offset, sizeof(bucket_info), "Bucket %3d: %s", start, (bucket_info & 1<<i ? "Assigned" : "Not Assigned") );
    start++;
  }
  return(start);
}

static gchar *
bucket_name(guint8 bucket)
{
  if (bucket == 0xff) {
    return (gchar *) "Unassigned";
  } else {
    return wmem_strdup_printf(wmem_packet_scope(), "%u", bucket);
  }
}


/* 5.5 WCCP Message Header */
static guint16
dissect_wccp2_header(tvbuff_t *tvb, int offset, proto_tree *wccp_tree)
{
  guint16 length;

  proto_tree_add_item(wccp_tree, hf_message_header_version, tvb, offset, 2,
                      ENC_BIG_ENDIAN);
  offset += 2;
  length = tvb_get_ntohs(tvb, offset);
  proto_tree_add_uint(wccp_tree, hf_message_header_length, tvb, offset, 2, length);
  return length;
}


static void
dissect_wccp2_info(tvbuff_t *tvb, int offset, guint16 length,
                   packet_info *pinfo, proto_tree *wccp_tree,
                   guint32 message_type)
{
  guint16 type;
  guint16 item_length;
  proto_item *tf;
  proto_tree *info_tree;
  gint ett;
  gint (*dissector)(tvbuff_t *, int, int, packet_info *, proto_tree *);

  /* check if all required fields are there */
  gboolean wccp2_security_info;
  gboolean wccp2_service_info;
  gboolean wccp2_router_id_info;
  gboolean wccp2_wc_id_info;
  gboolean wccp2_rtr_view_info;
  gboolean wccp2_wc_view_info;
  gboolean wccp2_redirect_assignment;
  gboolean wccp2_query_info;
  gboolean wccp2_capabilities_info;
  gboolean wccp2_alt_assignment;
  gboolean wccp2_assign_map;
  gboolean wccp2_command_extension;
  gboolean wccp2r1_alt_assignment_map;

  wccp2_security_info=FALSE;
  wccp2_service_info=FALSE;
  wccp2_router_id_info=FALSE;
  wccp2_wc_id_info=FALSE;
  wccp2_rtr_view_info=FALSE;
  wccp2_wc_view_info=FALSE;
  wccp2_redirect_assignment=FALSE;
  wccp2_query_info=FALSE;
  wccp2_capabilities_info=FALSE;
  wccp2_alt_assignment=FALSE;
  wccp2_assign_map=FALSE;
  wccp2_command_extension=FALSE;
  wccp2r1_alt_assignment_map=FALSE;

  /* ugly hack: we first need to check for the address table
     compnent, otherwise we cannot print the IP's.
  */
  find_wccp_address_table(tvb,offset,length,pinfo,wccp_tree);

  while (length != 0) {

    if (length < 4) {
      tf = proto_tree_add_text(wccp_tree, tvb, offset, length,
                               "Invalid WCCP Type/Length values");

      expert_add_info_format(pinfo, tf, &ei_wccp_length_bad,
                             "The packet only has %d bytes left. That is not enough for a WCCP item type and length.",
                             length);
      break;
    }

    type = tvb_get_ntohs(tvb, offset);
    item_length = tvb_get_ntohs(tvb, offset+2);


    if (item_length > tvb_length_remaining(tvb, offset)) {
      tf = proto_tree_add_text(wccp_tree, tvb, offset, length,
                               "Excessive WCCP Length values");
      expert_add_info_format(pinfo, tf, &ei_wccp_length_bad,
                             "The length of the item is %d but there are only %d bytes remaining in the packet, I counted %d remaining",
                             item_length, tvb_length_remaining(tvb, offset), length);
      break;
    }
    switch (type) {

    case WCCP2_SECURITY_INFO:
      wccp2_security_info=TRUE;
      ett = ett_security_info;
      dissector = dissect_wccp2_security_info;
      break;

    case WCCP2_SERVICE_INFO:
      wccp2_service_info=TRUE;
      ett = ett_service_info;
      dissector = dissect_wccp2_service_info;
      break;

    case WCCP2_ROUTER_ID_INFO:
      wccp2_router_id_info=TRUE;
      ett = ett_router_identity_info;
      dissector = dissect_wccp2_router_identity_info;
      break;

    case WCCP2_WC_ID_INFO:
      wccp2_wc_id_info=TRUE;
      ett = ett_wc_identity_info;
      dissector = dissect_wccp2_wc_identity_info;
      break;

    case WCCP2_RTR_VIEW_INFO:
      wccp2_rtr_view_info=TRUE;
      ett = ett_router_view_info;
      dissector = dissect_wccp2_router_view_info;
      break;

    case WCCP2_WC_VIEW_INFO:
      wccp2_wc_view_info=TRUE;
      ett = ett_wc_view_info;
      dissector = dissect_wccp2_web_cache_view_info;
      break;

    case WCCP2_REDIRECT_ASSIGNMENT:
      wccp2_redirect_assignment=TRUE;
      ett = ett_router_assignment_info;
      dissector = dissect_wccp2_assignment_info;
      break;

    case WCCP2_QUERY_INFO:
      wccp2_query_info=TRUE;
      ett = ett_query_info;
      dissector = dissect_wccp2_router_query_info;
      break;

    case WCCP2_CAPABILITIES_INFO:
      wccp2_capabilities_info=TRUE;
      ett = ett_capabilities_info;
      dissector = dissect_wccp2_capability_info;
      break;

    case WCCP2_ALT_ASSIGNMENT:
      wccp2_alt_assignment=TRUE;
      ett = ett_alt_assignment_info;
      dissector = dissect_wccp2_alternate_assignment_info;
      break;

    case WCCP2r1_ALT_ASSIGNMENT_MAP:
      wccp2r1_alt_assignment_map=TRUE;
      ett = ett_alt_assignment_map;
      dissector = dissect_wccp2r1_alt_assignment_map_info;
      break;

    case WCCP2r1_ADDRESS_TABLE:
      ett = ett_address_table;
      dissector = dissect_wccp2r1_address_table_info;
      break;

    case WCCP2_ASSIGN_MAP:
      wccp2_assign_map=TRUE;
      ett = ett_assignment_map;
      dissector = dissect_wccp2_assignment_map;
      break;
    case WCCP2_COMMAND_EXTENSION:
      wccp2_command_extension=TRUE;
      ett = ett_command_extension;
      dissector = dissect_wccp2_command_extension;
      break;

    default:
      ett = ett_unknown_info;
      dissector = NULL;
      break;
    }

    tf = proto_tree_add_text(wccp_tree, tvb, offset, item_length + 4, "%s",
                             val_to_str(type, info_type_vals, "Unknown info type (%u)"));
    info_tree = proto_item_add_subtree(tf, ett);
    proto_tree_add_item(info_tree, hf_item_type, tvb, offset, 2, ENC_BIG_ENDIAN);
    proto_tree_add_item(info_tree, hf_item_length, tvb, offset+2, 2, ENC_BIG_ENDIAN);

    offset += 4;
    length -= 4;

    if (length < item_length) {
      expert_add_info_format(pinfo, tf, &ei_wccp_length_bad,
                             "The item has length %d but the remaining WCCP data is only %d long",
                             item_length,
                             length);
    }

    if (dissector != NULL) {
      gint remaining_item_length = (*dissector)(tvb, offset, item_length, pinfo, info_tree);

      /* warn if we left bytes */
      if (remaining_item_length > 0)
        expert_add_info_format(pinfo, tf, &ei_wccp_length_bad,
                               "The dissector left %d bytes undecoded",
                               remaining_item_length);

      /* error if we needed more bytes */
      if (remaining_item_length < 0)
        expert_add_info_format(pinfo, tf, &ei_wccp_length_bad,
                               "The dissector needed %d more bytes to decode the packet, but the item is not that long",
                               remaining_item_length);

      /* we assume that the item length is correct and jump forward */
    } else {
      proto_tree_add_item(info_tree, hf_item_data, tvb, offset, item_length, ENC_NA);
    }
    /* avoid looping forever */
    if (length < item_length)
      return;

    offset += item_length;

    /* should no happen....*/
    DISSECTOR_ASSERT( ( (signed int) length - item_length) >= 0);
    length -= item_length;
  }


  /* we're done. Check if we got all the required components */

  switch (message_type) {
  case WCCP2_HERE_I_AM:
    if (!wccp2_security_info)
      expert_add_info(pinfo, wccp_tree, &ei_wccp_missing_security_info);
    if (!wccp2_service_info)
      expert_add_info(pinfo, wccp_tree, &ei_wccp_missing_service_info);
    if (wccp2_router_id_info)
      expert_add_info(pinfo, wccp_tree, &ei_wccp_contains_router_id_info);
    if (!wccp2_wc_id_info)
      expert_add_info(pinfo, wccp_tree, &ei_wccp_missing_wc_id_info);
    if (wccp2_rtr_view_info)
      expert_add_info(pinfo, wccp_tree, &ei_wccp_contains_rtr_view_info);
    if (!wccp2_wc_view_info)
      expert_add_info(pinfo, wccp_tree, &ei_wccp_missing_wc_view_info);
    if (wccp2_redirect_assignment)
      expert_add_info(pinfo, wccp_tree, &ei_wccp_contains_redirect_assignment);
    if (wccp2_query_info)
      expert_add_info(pinfo, wccp_tree, &ei_wccp_contains_query_info);
    if (wccp2_alt_assignment)
      expert_add_info(pinfo, wccp_tree, &ei_wccp_contains_alt_assignment);
    if (wccp2_assign_map)
      expert_add_info(pinfo, wccp_tree, &ei_wccp_contains_assign_map);
    if (wccp2r1_alt_assignment_map)
      expert_add_info(pinfo, wccp_tree, &ei_wccp_contains_alt_assignment_map);
    break;
  case WCCP2_I_SEE_YOU:
    if (!wccp2_security_info)
      expert_add_info(pinfo, wccp_tree, &ei_wccp_missing_security_info);
    if (!wccp2_service_info)
      expert_add_info(pinfo, wccp_tree, &ei_wccp_missing_service_info);
    if (!wccp2_router_id_info)
      expert_add_info(pinfo, wccp_tree, &ei_wccp_missing_router_id_info);
    if (wccp2_wc_id_info)
      expert_add_info(pinfo, wccp_tree, &ei_wccp_contains_wc_id_info);
    if (!wccp2_rtr_view_info)
      expert_add_info(pinfo, wccp_tree, &ei_wccp_missing_rtr_view_info);
    if (wccp2_wc_view_info)
      expert_add_info(pinfo, wccp_tree, &ei_wccp_contains_wc_view_info);
    if (wccp2_redirect_assignment)
      expert_add_info(pinfo, wccp_tree, &ei_wccp_contains_redirect_assignment);
    if (wccp2_query_info)
      expert_add_info(pinfo, wccp_tree, &ei_wccp_contains_query_info);
    if (wccp2r1_alt_assignment_map)
      expert_add_info(pinfo, wccp_tree, &ei_wccp_contains_alt_assignment_map);
    break;

  case WCCP2_REMOVAL_QUERY:
    if (!wccp2_security_info)
      expert_add_info(pinfo, wccp_tree, &ei_wccp_missing_security_info);
    if (!wccp2_service_info)
      expert_add_info(pinfo, wccp_tree, &ei_wccp_missing_service_info);
    if (wccp2_router_id_info)
      expert_add_info(pinfo, wccp_tree, &ei_wccp_contains_router_id_info);
    if (wccp2_wc_id_info)
      expert_add_info(pinfo, wccp_tree, &ei_wccp_contains_wc_id_info);
    if (wccp2_rtr_view_info)
      expert_add_info(pinfo, wccp_tree, &ei_wccp_contains_rtr_view_info);
    if (wccp2_wc_view_info)
      expert_add_info(pinfo, wccp_tree, &ei_wccp_contains_wc_view_info);
    if (wccp2_redirect_assignment)
      expert_add_info(pinfo, wccp_tree, &ei_wccp_contains_redirect_assignment);
    if (!wccp2_query_info)
      expert_add_info(pinfo, wccp_tree, &ei_wccp_missing_query_info);
    if (wccp2_capabilities_info)
      expert_add_info(pinfo, wccp_tree, &ei_wccp_contains_capabilities_info);
    if (wccp2_alt_assignment)
      expert_add_info(pinfo, wccp_tree, &ei_wccp_contains_alt_assignment);
    if (wccp2_assign_map)
      expert_add_info(pinfo, wccp_tree, &ei_wccp_contains_assign_map);
    if (wccp2_command_extension)
      expert_add_info(pinfo, wccp_tree, &ei_wccp_contains_command_extension);
    if (wccp2r1_alt_assignment_map)
      expert_add_info(pinfo, wccp_tree, &ei_wccp_contains_alt_assignment_map);
    break;

  case WCCP2_REDIRECT_ASSIGN:
    if (!wccp2_security_info)
      expert_add_info(pinfo, wccp_tree, &ei_wccp_missing_security_info);
    if (!wccp2_service_info)
      expert_add_info(pinfo, wccp_tree, &ei_wccp_missing_service_info);
    if (wccp2_router_id_info)
      expert_add_info(pinfo, wccp_tree, &ei_wccp_contains_router_id_info);
    if (wccp2_wc_id_info)
      expert_add_info(pinfo, wccp_tree, &ei_wccp_contains_wc_id_info);
    if (wccp2_rtr_view_info)
      expert_add_info(pinfo, wccp_tree, &ei_wccp_contains_rtr_view_info);
    if (wccp2_wc_view_info)
      expert_add_info(pinfo, wccp_tree, &ei_wccp_contains_wc_view_info);
    if (wccp2_query_info)
      expert_add_info(pinfo, wccp_tree, &ei_wccp_contains_query_info);
    if (wccp2_capabilities_info)
      expert_add_info(pinfo, wccp_tree, &ei_wccp_contains_capabilities_info);
    if (! (wccp2_assign_map || wccp2r1_alt_assignment_map || wccp2_alt_assignment || wccp2_redirect_assignment))
      expert_add_info(pinfo, wccp_tree, &ei_wccp_missing_assignment);
    if (wccp2_command_extension)
      expert_add_info(pinfo, wccp_tree, &ei_wccp_contains_command_extension);
    break;
  }
}

/* the following functions all need to check the length and the offset
   so we have a few macros to use
*/

#define EAT(x) {length -= x; offset += x;}

#define EAT_AND_CHECK(x,next) {length -= x; offset += x; if (length < next) return length - next;}

#define NOTE_EATEN_LENGTH(new_length) {if (new_length<0) return new_length;  offset += length-new_length; length = new_length; }


/* 5.1.1 Security Info Component */

/* Security options */

#define WCCP2_NO_SECURITY               0
#define WCCP2_MD5_SECURITY              1

#define SECURITY_INFO_LEN               4

const value_string security_option_vals[] = {
  { WCCP2_NO_SECURITY, "None" },
  { WCCP2_MD5_SECURITY, "MD5" },
  { 0,    NULL }
};


static gint
dissect_wccp2_security_info(tvbuff_t *tvb, int offset, gint length,
                            packet_info *pinfo _U_, proto_tree *info_tree)
{
  guint32 security_option;

  if (length < SECURITY_INFO_LEN)
    return (length-SECURITY_INFO_LEN);

  security_option = tvb_get_ntohl(tvb, offset);
  proto_tree_add_item(info_tree, hf_security_info_option, tvb, offset, 4, ENC_BIG_ENDIAN);

  if (security_option == WCCP2_MD5_SECURITY) {
    offset += 4;

    proto_tree_add_item(info_tree, hf_security_info_md5_checksum, tvb, offset, length-4, ENC_NA);

    return length-4-16;
  }
  return length-4;
}


/* 5.1.2 Service Info Component */

#define SERVICE_INFO_LEN                (4+4+8*2)

#define WCCP2_SERVICE_STANDARD          0
#define WCCP2_SERVICE_DYNAMIC           1

const value_string service_type_vals[] = {
  { WCCP2_SERVICE_STANDARD, "Standard predefined service"},
  { WCCP2_SERVICE_DYNAMIC, "Dynamic CE defined service" },
  { 0,    NULL }
};

/*
 * Service flags.
 */
#define WCCP2_SI_SRC_IP_HASH                    0x0001
#define WCCP2_SI_DST_IP_HASH                    0x0002
#define WCCP2_SI_SRC_PORT_HASH                  0x0004
#define WCCP2_SI_DST_PORT_HASH                  0x0008
#define WCCP2_SI_PORTS_DEFINED                  0x0010
#define WCCP2_SI_PORTS_SOURCE                   0x0020
#define WCCP2r1_SI_REDIRECT_ONLY_PROTOCOL_0     0x0040
#define WCCP2_SI_SRC_IP_ALT_HASH                0x0100
#define WCCP2_SI_DST_IP_ALT_HASH                0x0200
#define WCCP2_SI_SRC_PORT_ALT_HASH              0x0400
#define WCCP2_SI_DST_PORT_ALT_HASH              0x0800


static gint
dissect_wccp2_service_info(tvbuff_t *tvb, int offset, gint length,
                           packet_info *pinfo, proto_tree *info_tree)
{
  guint8 service_type;
  guint32 flags;
  proto_item *tf;
  proto_tree *field_tree, *ports_tree;
  int i;
  gchar *buf;
  int max_offset = offset+length;

  if (length != SERVICE_INFO_LEN)
    return length - SERVICE_INFO_LEN;

  service_type = tvb_get_guint8(tvb, offset);
  proto_tree_add_item(info_tree, hf_service_info_type, tvb,
                      offset, 1, ENC_BIG_ENDIAN);

  switch (service_type) {

  case WCCP2_SERVICE_STANDARD:
    proto_tree_add_item(info_tree, hf_service_info_id_standard, tvb,
                        offset +1 , 1, ENC_BIG_ENDIAN);

    tf = proto_tree_add_item(info_tree, hf_service_info_priority, tvb, offset+2, 1, ENC_BIG_ENDIAN);
    if (tvb_get_guint8(tvb, offset+2) != 0)
      expert_add_info(pinfo, tf, &ei_wccp_service_info_priority_nonzero);

    tf = proto_tree_add_item(info_tree, hf_service_info_protocol, tvb,
                        offset+3, 1, ENC_BIG_ENDIAN);

    if (tvb_get_guint8(tvb, offset+3) != 0)
      expert_add_info(pinfo, tf, &ei_wccp_service_info_protocol_nonzero);
    break;

  case WCCP2_SERVICE_DYNAMIC:
    proto_tree_add_item(info_tree, hf_service_info_id_dynamic, tvb,
                        offset +1 , 1, ENC_BIG_ENDIAN);
    proto_tree_add_item(info_tree, hf_service_info_priority, tvb,
                        offset+2, 1, ENC_BIG_ENDIAN);
    proto_tree_add_item(info_tree, hf_service_info_protocol, tvb,
                        offset+3, 1, ENC_BIG_ENDIAN);
    break;
  }
  offset += 4;

  flags = tvb_get_ntohl(tvb, offset);
  tf = proto_tree_add_item(info_tree, hf_service_info_flags, tvb, offset, 4, ENC_BIG_ENDIAN);

  field_tree = proto_item_add_subtree(tf, ett_service_flags);
  proto_tree_add_item(field_tree, hf_service_info_flags_src_ip_hash, tvb, offset, 4, ENC_BIG_ENDIAN);
  proto_tree_add_item(field_tree, hf_service_info_flags_dest_ip_hash, tvb, offset, 4, ENC_BIG_ENDIAN);
  proto_tree_add_item(field_tree, hf_service_info_flags_src_port_hash, tvb, offset, 4, ENC_BIG_ENDIAN);
  proto_tree_add_item(field_tree, hf_service_info_flags_dest_port_hash, tvb, offset, 4, ENC_BIG_ENDIAN);
  proto_tree_add_item(field_tree, hf_service_info_flags_ports_defined, tvb, offset, 4, ENC_BIG_ENDIAN);
  /* if they are defined which ? */
  if (flags & WCCP2_SI_PORTS_DEFINED)
    proto_tree_add_item(field_tree, hf_service_info_flags_ports_source, tvb, offset, 4, ENC_BIG_ENDIAN);

  proto_tree_add_item(field_tree, hf_service_info_flags_redirect_only_protocol_0, tvb, offset, 4, ENC_BIG_ENDIAN);
  proto_tree_add_item(field_tree, hf_service_info_flags_src_ip_alt_hash, tvb, offset, 4, ENC_BIG_ENDIAN);
  proto_tree_add_item(field_tree, hf_service_info_flags_dest_ip_alt_hash, tvb, offset, 4, ENC_BIG_ENDIAN);
  proto_tree_add_item(field_tree, hf_service_info_flags_src_port_alt_hash, tvb, offset, 4, ENC_BIG_ENDIAN);
  proto_tree_add_item(field_tree, hf_service_info_flags_dest_port_alt_hash, tvb, offset, 4, ENC_BIG_ENDIAN);

  buf= (char *) wmem_alloc(wmem_packet_scope(), 128);
  decode_bitfield_value(buf, flags,
                        0xFFFFFFFF ^ (WCCP2_SI_SRC_IP_HASH
                                      | WCCP2_SI_DST_IP_HASH
                                      | WCCP2_SI_SRC_PORT_HASH
                                      | WCCP2_SI_DST_PORT_HASH
                                      | WCCP2_SI_PORTS_DEFINED
                                      | WCCP2_SI_PORTS_SOURCE
                                      | WCCP2r1_SI_REDIRECT_ONLY_PROTOCOL_0
                                      | WCCP2_SI_SRC_IP_ALT_HASH
                                      | WCCP2_SI_DST_IP_ALT_HASH
                                      | WCCP2_SI_SRC_PORT_ALT_HASH
                                      | WCCP2_SI_DST_PORT_ALT_HASH),
                        32);
  proto_tree_add_text(field_tree, tvb, offset, 2,
                      "%s : %s",
                      buf, "reserved, should be 0");

  offset += 4;

  if (flags & WCCP2_SI_PORTS_DEFINED) {
    tf = proto_tree_add_text(info_tree, tvb, offset, 2*8,
                             "Ports list: ");
    ports_tree = proto_item_add_subtree(tf, ett_service_info_ports);

    for (i = 0; i < 8; i++) {
      guint16 port = tvb_get_ntohs(tvb, offset);

      if (port) {
        if (flags & WCCP2_SI_SRC_PORT_HASH)
          proto_tree_add_item(ports_tree, hf_service_info_source_port, tvb, offset, 2, ENC_BIG_ENDIAN);
        else
          proto_tree_add_item(ports_tree, hf_service_info_destination_port, tvb, offset, 2, ENC_BIG_ENDIAN);
        proto_item_append_text(tf, " %d", port);
      }
      offset += 2;
      DISSECTOR_ASSERT(offset <= max_offset);
    }
  }
  else {
    /* just use up the space if there is */
    if (offset + 8 * 2 <= max_offset)  {
      proto_tree_add_text(info_tree, tvb, offset, 8*2,
                          "Ports fields not used");
      /*offset += 8*2;*/
    }
  }

  return length - SERVICE_INFO_LEN;
}

/* 6.1 Router Identity Element */
static void
dissect_wccp2_router_identity_element(tvbuff_t *tvb, int offset, packet_info *pinfo,
                                      proto_tree *tree)
{
  proto_item *tf;


  proto_tree_add_item(tree, hf_router_identity_ip, tvb, offset, 4, ENC_BIG_ENDIAN);
  tf = proto_tree_add_item(tree, hf_router_identity_receive_id, tvb, offset+4, 4, ENC_BIG_ENDIAN);

  if (tvb_get_ntohl(tvb, offset + 4) == 0)
    expert_add_info(pinfo, tf, &ei_wccp_router_identity_receive_id_zero);
}

#define ROUTER_ID_INFO_MIN_LEN          (8+4+4)

/* 5.3.1 Router Identity Info Component */
static gint
dissect_wccp2_router_identity_info(tvbuff_t *tvb, int offset, gint length,
                                   packet_info *pinfo, proto_tree *info_tree)
{
  guint32 n_received_from;
  guint i;
  proto_item *te;
  proto_tree *element_tree;

  if (length < 8)
    return length -  ROUTER_ID_INFO_MIN_LEN;


  te = proto_tree_add_item(info_tree, hf_router_identity_router_ip, tvb, offset, 4, ENC_BIG_ENDIAN);

  element_tree = proto_item_add_subtree(te,ett_wc_view_info_router_element);

  dissect_wccp2_router_identity_element(tvb,offset,pinfo,element_tree);
  EAT_AND_CHECK(8,4);


  proto_tree_add_item(info_tree, hf_router_identity_send_to_ip, tvb, offset, 4, ENC_BIG_ENDIAN);
  EAT_AND_CHECK(4,4);

  n_received_from = tvb_get_ntohl(tvb, offset);
  proto_tree_add_item(info_tree, hf_router_identity_received_from_num, tvb, offset, 4, ENC_BIG_ENDIAN);
  EAT(4);

  for (i = 0; i < n_received_from; i++) {
    if (length < 4)
      return length-4*(i-n_received_from);


    proto_tree_add_item(info_tree, hf_router_identity_received_from_ip, tvb, offset, 4, ENC_BIG_ENDIAN);
    EAT(4);
  }

  return length;
}

#define ROUTER_WC_ID_ELEMENT_MIN_LEN (4+2+2)

/* 6.4 Web-Cache Identity Element */
static gint
dissect_wccp2_web_cache_identity_element(tvbuff_t *tvb, int offset, gint length, packet_info *pinfo,
                                         proto_tree *info_tree)
{
  proto_item *tf;
  proto_tree *field_tree;
  guint16 flags;
  guint data_element_type;
  char *buf;

  if (length < ROUTER_WC_ID_ELEMENT_MIN_LEN)
    return length - ROUTER_WC_ID_ELEMENT_MIN_LEN;

  proto_tree_add_item(info_tree, hf_web_cache_identity_ip, tvb, offset, 4, ENC_BIG_ENDIAN);
  EAT_AND_CHECK(4,2);

  tf = proto_tree_add_item(info_tree, hf_web_cache_identity_hash_rev, tvb, offset, 2, ENC_BIG_ENDIAN);
  if (tvb_get_ntohs(tvb, offset) != 0)
    expert_add_info(pinfo, tf, &ei_wccp_web_cache_identity_hash_rev_zero);

  EAT_AND_CHECK(2,2);

  flags = tvb_get_ntohs(tvb, offset);
  tf = proto_tree_add_uint(info_tree, hf_web_cache_identity_flags, tvb, offset, 2, flags);
  data_element_type = (flags & 0x6) >> 1;

  field_tree = proto_item_add_subtree(tf, ett_wc_identity_flags);
  proto_tree_add_item(field_tree, hf_web_cache_identity_flag_hash_info, tvb, offset, 2, ENC_BIG_ENDIAN);
  proto_tree_add_item(field_tree, hf_web_cache_identity_flag_assign_type, tvb, offset, 2, ENC_BIG_ENDIAN);
  proto_tree_add_item(field_tree, hf_web_cache_identity_flag_version_request, tvb, offset, 2, ENC_BIG_ENDIAN);
  buf=(char *) wmem_alloc(wmem_packet_scope(), 128);
  decode_bitfield_value(buf, flags, 0xFFF0, 16);
  proto_tree_add_text(field_tree, tvb, offset, 2,
                      "%s : %s",
                      buf, "reserved, should be 0");
  EAT(2);

  switch (data_element_type) {
  case WCCP2_WEB_CACHE_ASSIGNMENT_DATA_TYPE_HASH:
    return dissect_wccp2_hash_assignment_data_element(tvb,offset,length,pinfo,info_tree);
  case WCCP2_WEB_CACHE_ASSIGNMENT_DATA_TYPE_MASK:
    return dissect_wccp2_mask_assignment_data_element(tvb,offset,length,pinfo,info_tree);

  case WCCP2_WEB_CACHE_ASSIGNMENT_DATA_TYPE_NOT_PRESENT:
    proto_tree_add_text(info_tree, tvb, offset, 2,
                        "No Assignment Data Present");
    return length;
    break;
  case WCCP2_WEB_CACHE_ASSIGNMENT_DATA_TYPE_EXTENDED:
    return dissect_wccp2_extended_assignment_data_element(tvb,offset,length,pinfo,info_tree);
  }
  return length;
}

/* 5.2.1  Web-Cache Identity Info Component */
static gint
dissect_wccp2_wc_identity_info(tvbuff_t *tvb, int offset, gint length,
                               packet_info *pinfo _U_, proto_tree *info_tree)
{
  proto_item *te;
  proto_tree *element_tree;


  te = proto_tree_add_item(info_tree, hf_wc_identity_ip_address, tvb, offset, 4, ENC_BIG_ENDIAN);

  element_tree = proto_item_add_subtree(te, ett_wc_identity_element);
  return dissect_wccp2_web_cache_identity_element(tvb, offset,length, pinfo,
                                                  element_tree);
}

/* 6.3 Assignment Key Element */
static gint
dissect_wccp2_assignment_key_element(tvbuff_t *tvb, int offset, gint length, packet_info *pinfo _U_,
                                     proto_tree *info_tree)
{
  if (length < 8)
    return length -8;


  proto_tree_add_item(info_tree, hf_assignment_key_ip, tvb, offset, 4, ENC_BIG_ENDIAN);

  EAT_AND_CHECK(4,4);
  proto_tree_add_item(info_tree, hf_assignment_key_change_num, tvb, offset, 4, ENC_BIG_ENDIAN);
  EAT(4);

  return length;
}


#define ROUTER_VIEW_INFO_MIN_LEN        (4+8+4+4)

/* 5.3.2 Router View Info Component */
static gint
dissect_wccp2_router_view_info(tvbuff_t *tvb, int offset, gint length,
                               packet_info *pinfo, proto_tree *info_tree)
{
  guint32 n_routers;
  guint32 n_web_caches;
  guint i;
  proto_item *te;
  proto_tree *element_tree;
  gint new_length;

  if (length < ROUTER_VIEW_INFO_MIN_LEN)
    return length - ROUTER_VIEW_INFO_MIN_LEN;

  proto_tree_add_item(info_tree, hf_router_view_member_change_num, tvb, offset, 4, ENC_BIG_ENDIAN);
  EAT(4);

  new_length=dissect_wccp2_assignment_key_element(tvb, offset, length, pinfo, info_tree);
  NOTE_EATEN_LENGTH(new_length);

  n_routers = tvb_get_ntohl(tvb, offset);
  proto_tree_add_uint(info_tree, hf_router_router_num, tvb, offset, 4, n_routers);
  EAT(4);

  for (i = 0; i < n_routers; i++) {
    if (length < 4)
      return length - (n_routers-i)*4 - 4;

    proto_tree_add_item(info_tree, hf_router_view_ip, tvb, offset, 4, ENC_BIG_ENDIAN);
    EAT(4);
  }

  if (length < 4)
    return length - 4;

  n_web_caches = tvb_get_ntohl(tvb, offset);
  proto_tree_add_uint(info_tree, hf_wc_view_wc_num, tvb, offset, 4, n_web_caches);
  EAT(4);

  for (i = 0; i < n_web_caches; i++) {
    gint old_length;
    old_length = length;

    if (length < 4)
      return length - 4*(n_web_caches-i);

    te = proto_tree_add_item(info_tree, hf_router_query_info_ip, tvb, offset, 4, ENC_BIG_ENDIAN);

    element_tree = proto_item_add_subtree(te, ett_wc_identity_element);
    length = dissect_wccp2_web_cache_identity_element(tvb,
                                                      offset, length, pinfo,
                                                      element_tree);
    if (length < 0)
      return length;

    offset += old_length - length;
  }
  return length;
}

#define WC_VIEW_INFO_MIN_LEN            (4+4+4)

/* 5.2.2 Web Cache View Info Component */

static gint
dissect_wccp2_web_cache_view_info(tvbuff_t *tvb, int offset, gint length,
                                  packet_info *pinfo, proto_tree *info_tree)
{
  guint32 n_routers;
  guint32 n_web_caches;
  guint i;
  proto_item *te;
  proto_tree *element_tree;


  if (length < WC_VIEW_INFO_MIN_LEN)
    return length - WC_VIEW_INFO_MIN_LEN;


  proto_tree_add_item(info_tree, hf_wc_view_info_change_num, tvb, offset, 4, ENC_BIG_ENDIAN);
  EAT_AND_CHECK(4,4);

  n_routers = tvb_get_ntohl(tvb, offset);
  proto_tree_add_uint(info_tree, hf_wc_view_router_num, tvb, offset, 4, n_routers);
  EAT(4);

  for (i = 0; i < n_routers; i++) {
    if (length < 8)
      return length -8 * (n_routers-i) - 4;

    te = proto_tree_add_item(info_tree, hf_wc_view_info_router_ip, tvb, offset, 4, ENC_BIG_ENDIAN);
    /* also include the receive id in the object */
    proto_item_set_len(te, 8);

    element_tree = proto_item_add_subtree(te,ett_wc_view_info_router_element);
    dissect_wccp2_router_identity_element(tvb, offset, pinfo, element_tree);
    EAT(8);
  }

  if (length < 4)
    return length - 4;

  n_web_caches = tvb_get_ntohl(tvb, offset);
  proto_tree_add_uint(info_tree, hf_wc_view_wc_num, tvb, offset, 4, n_web_caches);
  EAT(4);

  for (i = 0; i < n_web_caches; i++) {
    if (length < 4)
      return length - 4*(n_web_caches-i);

    proto_tree_add_item(info_tree, hf_wc_view_info_wc_ip, tvb, offset, 4, ENC_BIG_ENDIAN);
    EAT(4);
  }
  return length;
}

/* 6.2 Router Assignment Element */
static void
dissect_wccp2_router_assignment_element(tvbuff_t *tvb, int offset,
                                        gint length, packet_info *pinfo, proto_tree *info_tree)
{
  dissect_wccp2_router_identity_element(tvb,offset,pinfo,info_tree);
  EAT(8);
  proto_tree_add_item(info_tree, hf_router_assignment_element_change_num, tvb, offset, 4, ENC_BIG_ENDIAN);
  EAT(4);
}

static gchar *
assignment_bucket_name(guint8 bucket)
{
  gchar *cur;

  if (bucket == 0xff) {
    cur= (gchar *) "Unassigned";
  } else {
    cur=wmem_strdup_printf(wmem_packet_scope(), "%u%s", bucket & 0x7F,
                         (bucket & 0x80) ? " (Alt)" : "");
  }
  return cur;
}

#define ASSIGNMENT_INFO_MIN_LEN         (8+4+4)

/* 5.4.1 Assignment Info Component  */
static gint
dissect_wccp2_assignment_info(tvbuff_t *tvb, int offset, gint length,
                              packet_info *pinfo, proto_tree *info_tree)
{
  guint32 n_routers;
  guint i;
  proto_item *te;
  proto_tree *element_tree;
  gint new_length;

  if (length < ASSIGNMENT_INFO_MIN_LEN)
    return length - ASSIGNMENT_INFO_MIN_LEN;


  new_length=dissect_wccp2_assignment_key_element(tvb, offset, length, pinfo,  info_tree);
  NOTE_EATEN_LENGTH(new_length);

  n_routers = tvb_get_ntohl(tvb, offset);
  proto_tree_add_uint(info_tree, hf_assignment_info_router_num, tvb, offset, 4, n_routers);
  EAT(4);

  for (i = 0; i < n_routers; i++) {
    if (length < 12)
      return length - 12*(n_routers-i)-4-256;

    te = proto_tree_add_item(info_tree, hf_assignment_info_router_ip, tvb, offset, 4, ENC_BIG_ENDIAN);

    element_tree = proto_item_add_subtree(te, ett_router_assignment_element);
    dissect_wccp2_router_assignment_element(tvb, offset, length , pinfo,
                                            element_tree);
    EAT(12);
  }

  new_length = dissect_wccp2_hash_buckets_assignment_element(tvb, offset, length, pinfo, info_tree);
  NOTE_EATEN_LENGTH(new_length);
  return length;
}


#define QUERY_INFO_LEN                  (4+4+4+4)

/* 5.5.1 Router Query Info Component */
static gboolean
dissect_wccp2_router_query_info(tvbuff_t *tvb, int offset, gint length,
                                packet_info *pinfo, proto_tree *info_tree)
{
  if (length < QUERY_INFO_LEN)
    return length - QUERY_INFO_LEN;

  dissect_wccp2_router_identity_element(tvb,offset,pinfo,info_tree);
  EAT_AND_CHECK(8,4);

  proto_tree_add_item(info_tree, hf_router_query_info_send_to_ip, tvb, offset, 4, ENC_BIG_ENDIAN);
  EAT_AND_CHECK(4,4);
  proto_tree_add_item(info_tree, hf_router_query_info_target_ip, tvb, offset, 4, ENC_BIG_ENDIAN);
  EAT(4);

  return length;
}

/* 6.5 Hash Buckets Assignment Element */
static gint dissect_wccp2_hash_buckets_assignment_element(tvbuff_t *tvb, int offset, gint length,
                                                          packet_info *pinfo _U_, proto_tree *info_tree)
{
  guint32 i,n_web_caches;
  proto_item *te;
  proto_tree *element_tree;

  if (length < 4)
    return length - 4;

  n_web_caches = tvb_get_ntohl(tvb, offset);
  te = proto_tree_add_uint(info_tree, hf_hash_buckets_assignment_wc_num, tvb, offset, 4, n_web_caches);
  EAT(4);

  element_tree = proto_item_add_subtree(te,ett_hash_buckets_assignment_wc_element);
  for (i = 0; i < n_web_caches; i++) {
    proto_item *l_te;

    if (length < 4)
      return length - 4*(n_web_caches-i)-256;

    l_te = proto_tree_add_item(element_tree, hf_hash_buckets_assignment_wc_ip, tvb, offset, 4, ENC_BIG_ENDIAN);

    proto_item_append_text(l_te, " id: %d", i);
    EAT(4);
  }

  te = proto_tree_add_text(info_tree,tvb, offset,256, "Buckets");
  element_tree = proto_item_add_subtree(te,ett_hash_buckets_assignment_buckets);

  for (i = 0; i < 256; i += 4) {
    if (length < 4)
      return length - (256-i);

    proto_tree_add_text(element_tree, tvb, offset, 4,
                        "Buckets %3d - %3d: %10s %10s %10s %10s",
                        i, i + 3,
                        assignment_bucket_name(tvb_get_guint8(tvb, offset)),
                        assignment_bucket_name(tvb_get_guint8(tvb, offset+1)),
                        assignment_bucket_name(tvb_get_guint8(tvb, offset+2)),
                        assignment_bucket_name(tvb_get_guint8(tvb, offset+3)));
    EAT(4);
  }
  return length;
}

#define WCCP2_FORWARDING_METHOD_GRE     0x00000001
#define WCCP2_FORWARDING_METHOD_L2      0x00000002

static const capability_flag forwarding_method_flags[] = {
  { WCCP2_FORWARDING_METHOD_GRE, "IP-GRE", &hf_capability_forwarding_method_flag_gre },
  { WCCP2_FORWARDING_METHOD_L2, "L2", &hf_capability_forwarding_method_flag_l2 },
  { 0, NULL, NULL }
};

#define WCCP2_ASSIGNMENT_METHOD_HASH    0x00000001
#define WCCP2_ASSIGNMENT_METHOD_MASK    0x00000002

static const capability_flag assignment_method_flags[] = {
  { WCCP2_ASSIGNMENT_METHOD_HASH, "Hash", &hf_capability_assignment_method_flag_hash },
  { WCCP2_ASSIGNMENT_METHOD_MASK, "Mask", &hf_capability_assignment_method_flag_mask },
  { 0,                            NULL,   NULL }
};


#define WCCP2_PACKET_RETURN_METHOD_GRE  0x00000001
#define WCCP2_PACKET_RETURN_METHOD_L2   0x00000002

static const capability_flag packet_return_method_flags[] = {
  { WCCP2_PACKET_RETURN_METHOD_GRE, "IP-GRE", &hf_capability_return_method_flag_gre },
  { WCCP2_PACKET_RETURN_METHOD_L2, "L2", &hf_capability_return_method_flag_l2 },
  { 0, NULL, NULL }
};

#define WCCP2_COMMAND_TYPE_SHUTDOWN           1
#define WCCP2_COMMAND_TYPE_SHUTDOWN_RESPONSE  2

static const value_string wccp_command_type_vals[] = {
  { WCCP2_COMMAND_TYPE_SHUTDOWN,          "CE shutting down" },
  { WCCP2_COMMAND_TYPE_SHUTDOWN_RESPONSE, "Router Acknowledge CE shutdown"},
  { 0, NULL }
};



/* 5.1.3 Capabilities Info Component */

static gint
dissect_wccp2_capability_info(tvbuff_t *tvb, int offset, gint length,
                              packet_info *pinfo, proto_tree *info_tree)
{
  gint capability_length;

  while (length >= 8) {
    capability_length = dissect_wccp2_capability_element(tvb,offset,length,pinfo,info_tree);

    NOTE_EATEN_LENGTH(capability_length);
  }
  return length;
}


#define ALT_COMMAND_EXTENSION_MIN_LEN  (4)

/* 5.1.4 && 6.12 Command Extension Component */

static gint
dissect_wccp2_command_extension(tvbuff_t *tvb, int offset,
                                int length, packet_info *pinfo _U_, proto_tree *info_tree)
{
  guint16 command_type;
  guint16 command_length;

  for (;;) {
    if (length == 0)
      return length;

    if (length < ALT_COMMAND_EXTENSION_MIN_LEN )
      return length - ALT_COMMAND_EXTENSION_MIN_LEN ;

    command_type = tvb_get_ntohs(tvb, offset);
    proto_tree_add_item(info_tree, hf_command_element_type, tvb, offset, 2, ENC_BIG_ENDIAN);
    EAT_AND_CHECK(2,2);


    command_length = tvb_get_ntohs(tvb, offset);
    proto_tree_add_item(info_tree, hf_command_element_length, tvb, offset, 2, ENC_BIG_ENDIAN);
    proto_tree_add_text(info_tree, tvb, offset, 2,
                        "Command length: %u", command_length);
    EAT(2);

    if (((command_type == WCCP2_COMMAND_TYPE_SHUTDOWN) ||
         (command_type == WCCP2_COMMAND_TYPE_SHUTDOWN_RESPONSE)) &&
        (command_length == 4)) {
      if (length < 4)
        return length - 4;
      proto_tree_add_item(info_tree, hf_command_element_shutdown_ip, tvb, offset, 4, ENC_BIG_ENDIAN);
    } else {
      if (length < command_length)
        return length - command_length;

      proto_tree_add_text(info_tree, tvb, offset, command_length,
                          "Unknown command");
    }
    EAT(command_length);
  }
}


/* 5.1.5 Address Table Component */
/* this function is special as it can be invoked twice during a packet decode:
   once to get the tables, once to display them
*/
static gint
dissect_wccp2r1_address_table_info(tvbuff_t *tvb, int offset,
                                   int length, packet_info *pinfo, proto_tree *info_tree)
{
  guint16 address_length;
  guint32 i;
  proto_tree *element_tree=NULL;
  proto_item *tf=NULL;

  wccp_wccp_address_table.in_use = TRUE;

  if (info_tree)
    tf = proto_tree_get_parent(info_tree);

  if (length < 2*4)
    return length - 2*4;


  wccp_wccp_address_table.family = tvb_get_ntohs(tvb,offset);
  if (pinfo && info_tree)
    proto_tree_add_item(info_tree, hf_address_table_family, tvb,
                        offset, 2, ENC_BIG_ENDIAN);
  EAT_AND_CHECK(2,2);

  address_length = tvb_get_ntohs(tvb,offset);
  if (info_tree)
    proto_tree_add_item(info_tree, hf_address_table_address_length, tvb, offset, 2, ENC_BIG_ENDIAN);
  EAT_AND_CHECK(2,2);

  wccp_wccp_address_table.table_length =  tvb_get_ntohl(tvb,offset);
  if (pinfo && info_tree) {
    tf = proto_tree_add_item(info_tree, hf_address_table_length, tvb, offset, 4, ENC_BIG_ENDIAN);
    element_tree = proto_item_add_subtree(tf, ett_table_element);
  }
  EAT(4);

  /* check if the length is valid and allocate the tables if needed*/
  switch (wccp_wccp_address_table.family) {
  case 1:
    if (wccp_wccp_address_table.table_ipv4 == NULL)
      wccp_wccp_address_table.table_ipv4 = (guint32 *)
        wmem_alloc(wmem_packet_scope(), wccp_wccp_address_table.table_length * 4);
    if ((address_length != 4) && (pinfo && info_tree)) {
      expert_add_info_format(pinfo, tf, &ei_wccp_length_bad,
                             "The Address length must be 4, but I found  %d for IPv4 addresses. Correcting this.",
                             address_length);
      address_length = 4;
    }
    break;
  case 2:
    if (wccp_wccp_address_table.table_ipv6 == NULL)
      wccp_wccp_address_table.table_ipv6 = (struct e_in6_addr *)
        wmem_alloc(wmem_packet_scope(), wccp_wccp_address_table.table_length * sizeof(struct e_in6_addr));
    if ((address_length != 16) && (pinfo && info_tree)) {
      expert_add_info_format(pinfo, tf, &ei_wccp_length_bad,
                             "The Address length must be 16, but I found %d for IPv6 addresses.  Correcting this",
                             address_length);
      address_length=16;
    }
    break;
  default:
    if (pinfo && info_tree) {
      expert_add_info_format(pinfo, tf, &ei_wccp_address_table_family_unknown,
                    "Unknown address family: %d", wccp_wccp_address_table.family);
    }
  };

  /* now read the addresses and print/store them */

  for(i=0; i<wccp_wccp_address_table.table_length; i++) {
    const gchar* addr;

    /* do we have space? */
    if (length < address_length) {
      if (pinfo && tf)
        expert_add_info_format(pinfo, tf, &ei_wccp_length_bad, "Ran out of space to decode");

      /* first clean up: */
      wccp_wccp_address_table.in_use = FALSE;
      wccp_wccp_address_table.family = -1;
      wccp_wccp_address_table.version = -1;
      wccp_wccp_address_table.table_length = 0;
      wccp_wccp_address_table.table_ipv4 = (guint32 *) NULL;
      wccp_wccp_address_table.table_ipv6 = (struct e_in6_addr *)NULL;

      /* ABORT The decode */
      return length - address_length;
    }

    switch (wccp_wccp_address_table.family) {
    case 1:
      /* IPv4 */
      addr  =  tvb_ip_to_str(tvb, offset);
      if (wccp_wccp_address_table.table_ipv4 != NULL)
        wccp_wccp_address_table.table_ipv4[i] = tvb_get_ntohl(tvb,offset);
      break;
    case 2:
      /* IPv6 */
      addr = tvb_ip6_to_str(tvb,offset);
      if (wccp_wccp_address_table.table_ipv6 != NULL)
        tvb_get_ipv6(tvb, offset, &(wccp_wccp_address_table.table_ipv6[i]));
      break;
    default:
      addr = wmem_strdup_printf(wmem_packet_scope(), "unknown family");
    };

    if (element_tree) {
      proto_tree_add_string_format_value(element_tree, hf_address_table_element, tvb,
                                         offset, address_length, addr,
                                         "%d: %s", i+1, addr);
    }
    EAT(address_length);
  }
  return length;
}





#define HASH_ASSIGNMENT_INFO_MIN_LEN (4+256)

/* part of 5.6.11 Alternate Assignment Component */
static gint
dissect_wccp2_hash_assignment_info(tvbuff_t *tvb, int offset, gint length,
                                   packet_info *pinfo, proto_tree *info_tree)
{
  guint32 n_web_caches;
  guint i;

  if (length < HASH_ASSIGNMENT_INFO_MIN_LEN)
    return length - ASSIGNMENT_INFO_MIN_LEN;

  n_web_caches = tvb_get_ntohl(tvb, offset);
  proto_tree_add_uint(info_tree, hf_wc_view_wc_num, tvb, offset, 4, n_web_caches);
  EAT(4);

  for (i = 0; i < n_web_caches; i++) {
    if (length < 4)
      return length - 4*(n_web_caches-i)-256;

    proto_tree_add_text(info_tree, tvb, offset, 4,
                        "Web-Cache %d: IP address %s", i,
                        decode_wccp_encoded_address(tvb, offset, pinfo, info_tree));
    EAT(4);
  }

  for (i = 0; i < 256; i += 4) {
    if (length < 4)
      return length - (256-i);

    proto_tree_add_text(info_tree, tvb, offset, 4,
                        "Buckets %d - %d: %10s %10s %10s %10s",
                        i, i + 3,
                        assignment_bucket_name(tvb_get_guint8(tvb, offset)),
                        assignment_bucket_name(tvb_get_guint8(tvb, offset+1)),
                        assignment_bucket_name(tvb_get_guint8(tvb, offset+2)),
                        assignment_bucket_name(tvb_get_guint8(tvb, offset+3)));
    EAT(4);
  }
  return length;
}

/* 5.3.3 Assignment Map Component */
static gint dissect_wccp2_assignment_map(tvbuff_t *tvb, int offset,
                                         int length, packet_info *pinfo, proto_tree *info_tree)
{
  gint new_length;

  new_length=dissect_wccp2_mask_value_set_list(tvb, offset, length, pinfo, info_tree);

  NOTE_EATEN_LENGTH(new_length);

  return length;
}



#define ALT_ASSIGNMENT_MAP_MIN_LEN  (4)

/* 5.3.4 Alternate Assignment Map Component */
static gint
dissect_wccp2r1_alt_assignment_map_info(tvbuff_t *tvb, int offset,
                                        int length, packet_info *pinfo, proto_tree *info_tree)
{
  guint16 assignment_type;
  guint16 assignment_length;
  proto_item *tf=NULL;

  if (length < ALT_ASSIGNMENT_MAP_MIN_LEN )
    return length - ALT_ASSIGNMENT_MAP_MIN_LEN ;


  assignment_type = tvb_get_ntohs(tvb, offset);
  proto_tree_add_item(info_tree, hf_alt_assignment_map_assignment_type, tvb, offset, 2, ENC_BIG_ENDIAN);
  EAT_AND_CHECK(2,2);

  assignment_length = tvb_get_ntohs(tvb, offset);
  tf=proto_tree_add_item(info_tree, hf_alt_assignment_map_assignment_length, tvb, offset, 2, ENC_BIG_ENDIAN);
  EAT(2);

  if (length < assignment_length)
    expert_add_info_format(pinfo, tf, &ei_wccp_assignment_length_bad,
                           "Assignment length is %d but only %d remain in the packet. Ignoring this for now",
                           assignment_length, length);

  if (length > assignment_length)  {
    expert_add_info_format(pinfo, tf, &ei_wccp_assignment_length_bad,
                           "Assignment length is %d but %d remain in the packet. Assuming that the assignment length is wrong and setting it to %d.",
                           assignment_length, length, length);
    assignment_length = length;
  }

  switch (assignment_type) {
  case WCCP2_HASH_ASSIGNMENT_TYPE:
    return dissect_wccp2_assignment_info(tvb, offset, assignment_length,
                                         pinfo, info_tree);
  case WCCP2_MASK_ASSIGNMENT_TYPE:
    return dissect_wccp2_mask_value_set_list(tvb, offset, assignment_length,
                                             pinfo, info_tree);
  case WCCP2r1_ALT_MASK_ASSIGNMENT_TYPE:
    return dissect_wccp2_alternate_mask_value_set_list(tvb, offset, assignment_length,
                                                       pinfo, info_tree);
  default:
    return length;
  }
}





/* 6.6 Hash Assignment Data Element */
static gint
dissect_wccp2_hash_assignment_data_element(tvbuff_t *tvb, int offset, gint length,
                                           packet_info *pinfo _U_,
                                           proto_tree *info_tree)

{
  proto_item *bucket_item;
  proto_tree *bucket_tree;
  int i;
  guint8 bucket_info;
  int n;


  bucket_item = proto_tree_add_text(info_tree, tvb, offset, 8*4,
                                    "Hash Assignment Data");
  bucket_tree = proto_item_add_subtree(bucket_item, ett_hash_assignment_buckets);

  for (i = 0, n = 0; i < 32; i++) {
    if (length == 0) {
      return -i-2-2;
    }

    bucket_info = tvb_get_guint8(tvb, offset);
    n = wccp_bucket_info(bucket_info, bucket_tree, n, tvb, offset);
    EAT(1);
  }

  if (length < 2){
    return -2-2;
  }

  return dissect_wccp2_assignment_weight_and_status_element(tvb, offset, length, pinfo, info_tree);
}

/* 6.7 Mask Assignment Data Element */
static gint
dissect_wccp2_mask_assignment_data_element(tvbuff_t *tvb, int offset, gint length, packet_info *pinfo,
                                           proto_tree *info_tree)

{
  proto_item *mask_item;
  proto_tree *mask_tree;
  gint new_length,start;


  mask_item = proto_tree_add_text(info_tree, tvb, offset, 4,
                                  "Mask Assignment Data");
  mask_tree = proto_item_add_subtree(mask_item, ett_mask_assignment_data_element);
  start = offset;

  new_length=dissect_wccp2_mask_value_set_list(tvb, offset, length, pinfo, mask_tree);

  NOTE_EATEN_LENGTH(new_length);

  if (length < 2)
    return length-4;

  new_length =  dissect_wccp2_assignment_weight_and_status_element(tvb, offset, length, pinfo, info_tree);
  NOTE_EATEN_LENGTH(new_length);

  proto_item_set_len(mask_item, offset-start);
  return length;
}


/* 5.7.5 Alternate Mask Assignment Data Element */
static gint
dissect_wccp2_alternate_mask_assignment_data_element(tvbuff_t *tvb, int offset, gint length, packet_info *pinfo,
                                                     proto_tree *info_tree)
{
  proto_item *mask_item;
  proto_tree *mask_tree;

  mask_item = proto_tree_add_text(info_tree, tvb, offset, length,
                                  "Alternate Mask Assignment Data");
  mask_tree = proto_item_add_subtree(mask_item, ett_alternate_mask_assignment_data_element);

  if (length < 4)
    return length-4;

  if (length > 4)
    for (;length >4;)
      {
        gint new_length;

        new_length=dissect_wccp2_alternate_mask_value_set_list(tvb, offset, length, pinfo, mask_tree);

        NOTE_EATEN_LENGTH(new_length);
      }

  if (length < 2)
    return -2;

  return  dissect_wccp2_assignment_weight_and_status_element(tvb, offset, length, pinfo, info_tree);
}


/* 6.9 Assignment Weight and Status Data Element */
static gint
dissect_wccp2_assignment_weight_and_status_element(tvbuff_t *tvb, int offset, gint length,
                                                   packet_info *pinfo _U_,
                                                   proto_tree *info_tree)

{
  if (length < 4)
    return length - 4;


  proto_tree_add_item(info_tree, hf_assignment_weight, tvb, offset, 2, ENC_BIG_ENDIAN);
  EAT_AND_CHECK(2,2);
  proto_tree_add_item(info_tree, hf_assignment_status, tvb, offset, 2, ENC_BIG_ENDIAN);
  EAT(2);
  return length;
}


/* 6.10 Extended Assignment Data Element */
static gint
dissect_wccp2_extended_assignment_data_element(tvbuff_t *tvb, int offset, gint length, packet_info *pinfo,
                                               proto_tree *info_tree)
{
  proto_item *element_item, *header;
  proto_tree *item_tree;

  guint type_of_assignment;

  gint assignment_length;

  if (length < 4)
    return length-4;


  header = proto_tree_add_text(info_tree, tvb, offset, length,
                               "Extended Assignment Data Element");

  item_tree = proto_item_add_subtree(header, ett_extended_assigment_data_element);

  type_of_assignment = tvb_get_ntohs(tvb, offset);
  proto_tree_add_item(item_tree, hf_extended_assignment_data_type, tvb, offset, 2, ENC_BIG_ENDIAN);
  EAT_AND_CHECK(2,2);

  assignment_length = tvb_get_ntohs(tvb,offset);
  element_item = proto_tree_add_item(item_tree, hf_extended_assignment_data_length, tvb, offset, 2, ENC_BIG_ENDIAN);
  EAT(2);

  if (length < assignment_length)
    expert_add_info_format(pinfo, element_item, &ei_wccp_assignment_length_bad,
                           "Assignment length is %d but only %d remain in the packet. Ignoring this for now",
                           assignment_length, length);

  /* Now a common bug seems to be to set the assignment_length to the length -4
     check for this */
  if ((length > assignment_length) &&
      (length == (assignment_length + 4)))
    {
      expert_add_info_format(pinfo, element_item, &ei_wccp_assignment_length_bad,
                             "Assignment length is %d but %d remain in the packet. Assuming that this is wrong as this is only 4 bytes to small, proceding with the assumption it is %d",
                             assignment_length, length, length);
      assignment_length = length;
    }


  proto_item_set_len(header, assignment_length+4);

  switch (type_of_assignment)
    {
    case WCCP2_HASH_ASSIGNMENT_TYPE:
      return dissect_wccp2_hash_assignment_data_element(tvb, offset, assignment_length,
                                                        pinfo, item_tree);
    case WCCP2_MASK_ASSIGNMENT_TYPE:
      return dissect_wccp2_mask_assignment_data_element(tvb, offset, assignment_length,
                                                        pinfo, item_tree);
    case WCCP2r1_ALT_MASK_ASSIGNMENT_TYPE:
      return dissect_wccp2_alternate_mask_assignment_data_element(tvb, offset, assignment_length,
                                                                  pinfo, item_tree);
    case WCCP2r1_ASSIGNMENT_WEIGHT_STATUS:
      return dissect_wccp2_assignment_weight_and_status_element(tvb, offset, assignment_length,
                                                                pinfo, item_tree);
    }
  return length;
}






/* 6.11 Capability Element */
static gint
dissect_wccp2_capability_element(tvbuff_t *tvb, int offset, gint length,
                                 packet_info *pinfo, proto_tree *info_tree)
{
  guint16 capability_type;
  guint16 capability_val_len;
  proto_item *te, *header, *tf;
  proto_tree *element_tree;

  if (length < 4)
    return length - 4;


  capability_type = tvb_get_ntohs(tvb, offset);
  capability_val_len = tvb_get_ntohs(tvb, offset + 2);
  header = te = proto_tree_add_item(info_tree, hf_capability_element_type, tvb, offset, 2, ENC_BIG_ENDIAN);

  proto_item_set_len(te, capability_val_len + 4);
  element_tree = proto_item_add_subtree(te, ett_capability_element);

  tf = proto_tree_add_uint(element_tree, hf_capability_element_length, tvb, offset+2, 2, capability_val_len);

  proto_tree_add_text(element_tree, tvb, offset, 2,
                      "Type: %s",
                      val_to_str(capability_type,
                                 capability_type_vals, "Unknown (0x%08X)"));
  if (capability_val_len < 4) {
    expert_add_info_format(pinfo, tf, &ei_wccp_capability_element_length,
                "Value Length: %u (illegal, must be >= 4)", capability_val_len);
    return -length;
  }

  if (length < (4+capability_val_len))
    return length - 4 - capability_val_len;

  switch (capability_type) {
  case WCCP2_FORWARDING_METHOD:
    dissect_32_bit_capability_flags(tvb, offset,
                                    capability_val_len,
                                    ett_capability_forwarding_method,
                                    forwarding_method_flags, element_tree, header);
    break;

  case WCCP2_ASSIGNMENT_METHOD:
    dissect_32_bit_capability_flags(tvb, offset,
                                    capability_val_len,
                                    ett_capability_assignment_method,
                                    assignment_method_flags, element_tree, header);
    break;

  case WCCP2_PACKET_RETURN_METHOD:
    dissect_32_bit_capability_flags(tvb, offset,
                                    capability_val_len,
                                    ett_capability_return_method,
                                    packet_return_method_flags, element_tree, header);
    break;

  case WCCP2_TRANSMIT_T:
    dissect_transmit_t_capability(tvb, te, offset,
                                  capability_val_len,
                                  ett_capability_transmit_t,element_tree);
    break;

  case WCCP2_TIMER_SCALE:
    dissect_timer_scale_capability(tvb, offset,
                                   capability_val_len,
                                   ett_capability_timer_scale, element_tree);
    break;
  default:
    proto_tree_add_text(element_tree, tvb,
                        offset, capability_val_len,
                        "Value: %s",
                        tvb_bytes_to_str(tvb, offset,
                                         capability_val_len));
    break;
  }
  return length - 4 - capability_val_len;
}


/* 6.13 Mask/Value Set List */
static gint
dissect_wccp2_mask_value_set_list(tvbuff_t *tvb, int offset,
                                  int length, packet_info *pinfo, proto_tree *info_tree)
{
  guint num_of_elem;
  guint i;
  proto_item *te;
  proto_tree *element_tree;
  guint start;


  if (length < 4)
    return length - 4;

  te = proto_tree_add_text(info_tree, tvb, offset, 4, "Mask/Value Set List");
  element_tree = proto_item_add_subtree(te, ett_mv_set_list);
  start = offset;


  num_of_elem = tvb_get_ntohl(tvb, offset);
  proto_tree_add_item(element_tree, hf_mask_value_set_list_num_elements,
                      tvb, offset, 4, ENC_BIG_ENDIAN);
  /*  proto_tree_add_uint(element_tree, , tvb, offset, 4, num_of_elem); */
  EAT(4);

  for (i = 0; i < num_of_elem; i++)
    {
      gint new_length;

      new_length=dissect_wccp2_mask_value_set_element(tvb, offset, length, i, pinfo, element_tree);

      NOTE_EATEN_LENGTH(new_length);
    }

  proto_item_set_len(te, offset-start);
  return length;
}





/* 6.15 Mask Element */
static gint
dissect_wccp2_mask_element(tvbuff_t *tvb, int offset, gint length, packet_info *pinfo _U_, proto_tree *info_tree)
{
  if (length < 2)
    return length-12;

  proto_tree_add_item(info_tree, hf_mask_element_src_ip, tvb, offset, 4, ENC_BIG_ENDIAN);
  EAT_AND_CHECK(4,4);
  proto_tree_add_item(info_tree, hf_mask_element_dest_ip, tvb, offset, 4, ENC_BIG_ENDIAN);

  EAT_AND_CHECK(4,2);
  proto_tree_add_item(info_tree, hf_mask_element_src_port, tvb, offset, 2, ENC_BIG_ENDIAN);
  EAT_AND_CHECK(2,2);
  proto_tree_add_item(info_tree, hf_mask_element_dest_port, tvb, offset, 2, ENC_BIG_ENDIAN);
  EAT(2);

  return length;
}






/* 6.17 Alternate Mask/Value Set List */
static gint dissect_wccp2_alternate_mask_value_set_list(tvbuff_t *tvb, int offset,
                                                        int length, packet_info *pinfo, proto_tree *info_tree)
{
  proto_item *header;
  proto_tree *list_tree;
  guint num_of_val_elements;
  guint i;

  if (length < 4)
    return length - 4;

  header = proto_tree_add_text(info_tree, tvb, offset, length,
                               "Alternate Mask/Value Set List");
  list_tree = proto_item_add_subtree(header, ett_alternate_mask_value_set);

  num_of_val_elements = tvb_get_ntohl(tvb, offset);
  proto_tree_add_uint(list_tree, hf_alt_assignment_mask_value_set_list_num_elements, tvb, offset, 4, num_of_val_elements);
  EAT(4);

  for(i=0;i<num_of_val_elements;i++) {
    gint new_length;

    new_length=dissect_wccp2_alternate_mask_value_set_element(tvb, offset, length, i, pinfo, list_tree);

    NOTE_EATEN_LENGTH(new_length);
  }
  return length;
}


/* 6.18 Alternate Mask/Value Set Element */
static gint
dissect_wccp2_alternate_mask_value_set_element(tvbuff_t *tvb, int offset, gint length, guint el_index, packet_info *pinfo, proto_tree *info_tree)
{
  proto_item *tl, *header;
  proto_tree *element_tree, *value_tree;
  guint number_of_elements;
  gint new_length, total_length;
  guint i;

  header = proto_tree_add_text(info_tree, tvb, offset, 0,
                               "Alternate Mask/Value Set Element(%d)", el_index);
  element_tree = proto_item_add_subtree(header, ett_alternate_mask_value_set_element);

  total_length = 0;

  new_length=dissect_wccp2_mask_element(tvb,offset,length,pinfo,element_tree);
  total_length += length - new_length;
  NOTE_EATEN_LENGTH(new_length);

  if (length < 4)
    return length - 4;

  number_of_elements  = tvb_get_ntohl(tvb, offset);
  tl = proto_tree_add_uint(element_tree, hf_alt_assignment_mask_value_set_element_num_wc_value_elements, tvb, offset, 4, number_of_elements);
  value_tree = proto_item_add_subtree(tl, ett_alternate_mv_set_element_list);
  total_length += 4;
  EAT(4);

  for (i=0; i < number_of_elements; i++) {
    new_length=dissect_wccp2_web_cache_value_element(tvb, offset, length, pinfo,  value_tree);
    total_length += length - new_length;
    NOTE_EATEN_LENGTH(new_length);
  }
  proto_item_set_len(header, total_length);

  return length;
}

/* 6.19 Web-Cache Value Element */
static gint
dissect_wccp2_web_cache_value_element(tvbuff_t *tvb, int offset, gint length,  packet_info *pinfo _U_, proto_tree *info_tree)
{
  guint number_of_elements;
  proto_item *tl;
  proto_tree *element_tree;
  guint i;

  if (length < 4)
    return length - 8;

  tl = proto_tree_add_item(info_tree, hf_web_cache_value_element_wc_address, tvb, offset, 4, ENC_BIG_ENDIAN);

  element_tree = proto_item_add_subtree(tl, ett_web_cache_value_element_list);
  EAT_AND_CHECK(4,4);

  number_of_elements  = tvb_get_ntohl(tvb, offset);
  proto_tree_add_uint(element_tree, hf_web_cache_value_element_num_values, tvb, offset, 4, number_of_elements);
  EAT(4);

  for (i=0; i < number_of_elements; i++) {
    if (length < 4)
      return length - 4*(number_of_elements-i);

    proto_tree_add_text(element_tree, tvb, offset, 4,
                        "Value Sequence Number %d: %x",
                        i+1,
                        tvb_get_ntohl(tvb, offset));
    EAT(4);
  }

  return length;
}


/* End of standard functions */


static void
dissect_32_bit_capability_flags(tvbuff_t *tvb, int curr_offset,
                                guint16 capability_val_len, gint ett, const capability_flag *flags,
                                proto_tree *element_tree, proto_item *header)
{
  guint32 capability_val;
  proto_item *tm;
  proto_tree *method_tree;
  int i;
  gboolean first = TRUE;

  capability_val = tvb_get_ntohl(tvb, curr_offset + 4);
  tm = proto_tree_add_uint(element_tree, hf_capability_info_value, tvb, curr_offset + 4, 4, capability_val);

  DISSECTOR_ASSERT(capability_val_len == 4);

  for (i = 0; flags[i].short_name != NULL; i++) {
    if (capability_val & flags[i].value) {
      if (first) {
        proto_item_append_text( tm, " (%s", flags[i].short_name);
        proto_item_append_text( header, " (%s", flags[i].short_name);
        first = FALSE;
      } else {
        proto_item_append_text( tm, ", %s", flags[i].short_name);
        proto_item_append_text( header, " (%s", flags[i].short_name);
      }
    }
  }

  if (first == FALSE) {
    proto_item_append_text( tm, ")");
    proto_item_append_text( header, ")");
  }

  method_tree = proto_item_add_subtree(tm, ett);
  for (i = 0; flags[i].phf != NULL; i++)
    proto_tree_add_item(method_tree, *(flags[i].phf), tvb, curr_offset+4, 4, ENC_BIG_ENDIAN);
}



/* 6.11.4 Capability Type WCCP2_TRANSMIT_T */
static void
dissect_transmit_t_capability(tvbuff_t *tvb, proto_item *te, int curr_offset,
                              guint16 capability_val_len, gint ett, proto_tree *element_tree)
{
  guint16 upper_limit, lower_limit;
  proto_item *tm;
  proto_tree *method_tree;

  DISSECTOR_ASSERT(capability_val_len == 4);

  upper_limit = tvb_get_ntohs(tvb, curr_offset);
  lower_limit = tvb_get_ntohs(tvb, curr_offset + 2);

  if ( upper_limit == 0) {
    tm = proto_tree_add_text(element_tree, tvb, curr_offset, 2,
                             "Only accepting one value");
    method_tree = proto_item_add_subtree(tm, ett);
    proto_tree_add_text(method_tree, tvb, curr_offset, 2,
                        "Reserved, must be 0: %d", upper_limit);

    proto_tree_add_item(method_tree, hf_capability_transmit_t , tvb, curr_offset+2, 2, ENC_BIG_ENDIAN);
    proto_item_append_text(te, " %d ms", lower_limit);
  } else {
    tm = proto_tree_add_text(element_tree, tvb, curr_offset, 2,
                             "Accepting a range");
    method_tree = proto_item_add_subtree(tm, ett);
    proto_tree_add_item(method_tree, hf_capability_transmit_t_upper_limit,
                        tvb, curr_offset, 2, ENC_BIG_ENDIAN);

    proto_tree_add_item(method_tree, hf_capability_transmit_t_lower_limit,
                        tvb, curr_offset+2, 2, ENC_BIG_ENDIAN);
    proto_item_append_text(te, " < %d ms > %d ms", lower_limit, upper_limit);
  }
}


static void
dissect_timer_scale_capability(tvbuff_t *tvb, int curr_offset,
                               guint16 capability_val_len, gint ett, proto_tree *element_tree)
{
  guint8 a,c;
  proto_item *tm;
  proto_tree *method_tree;

  DISSECTOR_ASSERT(capability_val_len == 4);

  a = tvb_get_guint8(tvb, curr_offset);
  c = tvb_get_guint8(tvb, curr_offset+2);

  if ( a == 0) {
    if ( c == 0) {
      tm = proto_tree_add_text(element_tree, tvb, curr_offset, 2,
                               "Only accepting one value");

      method_tree = proto_item_add_subtree(tm, ett);
      proto_tree_add_text(method_tree, tvb, curr_offset, 1,
                          "Reserved, must be 0: %d", a);

      proto_tree_add_item(method_tree, hf_capability_timer_scale_timeout_scale,
                          tvb, curr_offset+1, 1, ENC_BIG_ENDIAN);
      proto_tree_add_text(method_tree, tvb, curr_offset+2, 1,
                          "Reserved, must be 0: %d", c);
      proto_tree_add_item(method_tree, hf_capability_timer_scale_ra_timer_scale,
                          tvb, curr_offset+3, 1, ENC_BIG_ENDIAN);
    } else {
      proto_tree_add_text(element_tree, tvb, curr_offset, 1,
                               "Error A is 0, but C is not");
    }
  } else {
    if ( c == 0) {
      proto_tree_add_text(element_tree, tvb, curr_offset, 1,
                               "Error C is 0, but A is not");
    } else {
      tm = proto_tree_add_text(element_tree, tvb, curr_offset, 2,
                               "Accepting a range");
      method_tree = proto_item_add_subtree(tm, ett);
      proto_tree_add_item(method_tree, hf_capability_timer_scale_timeout_scale_upper_limit,
                          tvb, curr_offset, 1, ENC_BIG_ENDIAN);

      proto_tree_add_item(method_tree, hf_capability_timer_scale_timeout_scale_lower_limit,
                          tvb, curr_offset+1, 1, ENC_BIG_ENDIAN);
      proto_tree_add_item(method_tree, hf_capability_timer_scale_ra_scale_upper_limit,
                          tvb, curr_offset+2, 1, ENC_BIG_ENDIAN);
      proto_tree_add_item(method_tree, hf_capability_timer_scale_ra_scale_lower_limit,
                          tvb, curr_offset+3, 1, ENC_BIG_ENDIAN);
    }
  }
}


/* 6.16 Value Element */
static gint
dissect_wccp2_value_element(tvbuff_t *tvb, int offset, gint length, int idx, packet_info *pinfo, proto_tree *info_tree)
{
  proto_item *tl;
  proto_tree *element_tree;

  if (length < 4)
    return length - 16;

  tl = proto_tree_add_text(info_tree, tvb, offset, 16, "Value Element(%u) %s",
                           idx,decode_wccp_encoded_address(tvb, offset+4+4+2+2, pinfo, info_tree));
  element_tree = proto_item_add_subtree(tl, ett_value_element);

  proto_tree_add_item(element_tree, hf_value_element_src_ip, tvb, offset, 4, ENC_BIG_ENDIAN);
  EAT_AND_CHECK(4,4);
  proto_tree_add_item(element_tree, hf_value_element_dest_ip, tvb, offset, 4, ENC_BIG_ENDIAN);

  EAT_AND_CHECK(4,2);
  proto_tree_add_item(element_tree, hf_value_element_src_port, tvb, offset, 2, ENC_BIG_ENDIAN);
  EAT_AND_CHECK(2,2);
  proto_tree_add_item(element_tree, hf_value_element_dest_port, tvb, offset, 2, ENC_BIG_ENDIAN);
  EAT_AND_CHECK(2,4);

  proto_tree_add_item(element_tree, hf_value_element_web_cache_ip, tvb, offset, 4, ENC_BIG_ENDIAN);
  EAT(4);

  return length;
}


/* 6.14 Mask/Value Set Element */
static gint
dissect_wccp2_mask_value_set_element(tvbuff_t *tvb, int offset, gint length, int idx, packet_info *pinfo, proto_tree *info_tree)
{
  proto_item *tl, *te;
  proto_tree *element_tree, *value_tree;
  guint num_of_val_elements;
  guint i;
  gint new_length;

  tl = proto_tree_add_text(info_tree, tvb, offset, 0,
                           "Mask/Value Set Element(%d)", idx);
  element_tree = proto_item_add_subtree(tl, ett_mv_set_element);

  new_length = dissect_wccp2_mask_element(tvb,offset,length,pinfo,element_tree);
  NOTE_EATEN_LENGTH(new_length);

  if (length < 4)
    return length-4;

  num_of_val_elements = tvb_get_ntohl(tvb, offset);
  te = proto_tree_add_uint(element_tree, hf_mask_value_set_element_value_element_num, tvb, offset, 4, num_of_val_elements);

  value_tree = proto_item_add_subtree(te, ett_mv_set_value_list);
  EAT(4);

  for (i = 0; i < num_of_val_elements; i++)
    {
      new_length=dissect_wccp2_value_element(tvb, offset, length, i, pinfo,  value_tree);

      NOTE_EATEN_LENGTH(new_length);
    }

  proto_item_set_len(tl, 16+num_of_val_elements*16);

  return length;
}

#define ALT_ASSIGNMENT_INFO_MIN_LEN    (4+4)

/* 5.4.2 Alternate Assignment Component */
static gint
dissect_wccp2_alternate_assignment_info(tvbuff_t *tvb, int offset, gint length,
                                        packet_info *pinfo, proto_tree *info_tree)
{
  guint16 assignment_type;
  guint16 assignment_length;
  proto_item *tf=NULL;

  guint32 n_routers;
  guint i;
  proto_item *te;
  proto_tree *element_tree;
  gint new_length;


  if (length < ALT_ASSIGNMENT_INFO_MIN_LEN)
    return length - ALT_ASSIGNMENT_INFO_MIN_LEN;


  assignment_type = tvb_get_ntohs(tvb, offset);
  proto_tree_add_item(info_tree, hf_alt_assignment_info_assignment_type, tvb, offset, 2, ENC_BIG_ENDIAN);
  EAT_AND_CHECK(2,2);

  assignment_length = tvb_get_ntohs(tvb, offset);
  tf=proto_tree_add_item(info_tree, hf_alt_assignment_info_assignment_length, tvb, offset, 2, ENC_BIG_ENDIAN);
  EAT(2);

  if (length < assignment_length)
    expert_add_info_format(pinfo, tf, &ei_wccp_assignment_length_bad,
                           "Assignment length is %d but only %d remain in the packet. Ignoring this for now",
                           assignment_length, length);

  if (length > assignment_length)  {
    expert_add_info_format(pinfo, tf, &ei_wccp_assignment_length_bad,
                           "Assignment length is %d but %d remain in the packet. Assuming that the assignment length is wrong and setting it to %d.",
                           assignment_length, length, length);
  }

  new_length=dissect_wccp2_assignment_key_element(tvb, offset, length, pinfo,  info_tree);
  NOTE_EATEN_LENGTH(new_length);

  n_routers = tvb_get_ntohl(tvb, offset);
  proto_tree_add_uint(info_tree, hf_alt_assignment_info_num_routers, tvb, offset, 4, n_routers);
  EAT(4);

  for (i = 0; i < n_routers; i++) {
    if (length < 12)
      return length - 12*(n_routers-i);

    te = proto_tree_add_text(info_tree, tvb, offset, 12,
                             "Router %d Assignment Element: IP address %s", i,
                             decode_wccp_encoded_address(tvb, offset, pinfo, info_tree));

    element_tree = proto_item_add_subtree(te, ett_router_alt_assignment_element);
    dissect_wccp2_router_assignment_element(tvb, offset, length , pinfo, element_tree);
    EAT(12);
  }

  switch (assignment_type) {
  case WCCP2_HASH_ASSIGNMENT_TYPE:
    return dissect_wccp2_hash_assignment_info(tvb, offset, length,
                                              pinfo, info_tree);
  case WCCP2_MASK_ASSIGNMENT_TYPE:
    return dissect_wccp2_mask_value_set_list(tvb, offset, length,
                                             pinfo, info_tree);
  case WCCP2r1_ALT_MASK_ASSIGNMENT_TYPE:
    return dissect_wccp2_alternate_mask_value_set_list(tvb, offset, length,
                                                       pinfo, info_tree);
  default:
    return length;
  }
}




/* End of utility functions */

void
proto_register_wccp(void)
{
  static hf_register_info hf[] = {
    { &hf_wccp_message_type,
      { "WCCP Message Type", "wccp.message", FT_UINT32, BASE_DEC, VALS(wccp_type_vals), 0x0,
        "The WCCP message that was sent", HFILL }
    },
    { &hf_wccp_version,
      { "WCCP Version", "wccp.version", FT_UINT32, BASE_HEX, VALS(wccp_version_val), 0x0,
        "The WCCP version", HFILL }
    },
    { &hf_message_header_version,
      { "WCCP Version (>=2)", "wccp.message_header_version", FT_UINT16, BASE_HEX, NULL, 0x0,
        "The WCCP version for version 2 and above", HFILL }
    },
    { &hf_hash_revision,
      { "Hash Revision", "wccp.hash_revision", FT_UINT32, BASE_DEC, 0x0, 0x0,
        "The cache hash revision", HFILL }
    },
    { &hf_change_num,
      { "Change Number", "wccp.change_num", FT_UINT32, BASE_DEC, 0x0, 0x0,
        "The Web-Cache list entry change number", HFILL }
    },
    { &hf_hash_flag,
      { "Flags", "wccp.hash_flag", FT_UINT32, BASE_HEX, 0x0, 0x0,
        NULL, HFILL }
    },
    { &hf_hash_flag_u,
      { "Hash information", "wccp.hash_flag.u", FT_BOOLEAN, 32, TFS(&tfs_historical_current), 0x10000,
        NULL, HFILL }
    },
    { &hf_recvd_id,
      { "Received ID", "wccp.recvd_id", FT_UINT32, BASE_DEC, 0x0, 0x0,
        "The number of I_SEE_YOU's that have been sent", HFILL }
    },
    { &hf_cache_ip,
      { "Web Cache IP address", "wccp.cache_ip", FT_IPv4, BASE_NONE, NULL, 0x0,
        "The IP address of a Web cache", HFILL }
    },
    { &hf_wc_num,
      { "Number of Web Caches", "wccp.wc_num", FT_UINT32, BASE_DEC, 0x0, 0x0,
        NULL, HFILL }
    },
    { &hf_message_header_length,
      { "Length", "wccp.message_header_length", FT_UINT16, BASE_DEC, 0x0, 0x0,
        NULL, HFILL }
    },
    { &hf_item_length,
      { "Length", "wccp.item_length", FT_UINT16, BASE_DEC, 0x0, 0x0,
        "The Length ofthe WCCPv2 item", HFILL }
    },
    { &hf_item_type,
      { "Type", "wccp.item_type", FT_UINT16, BASE_DEC, VALS(info_type_vals), 0x0,
        "The type of the WCCPv2 item", HFILL }
    },
    { &hf_item_data,
      { "Data", "wccp.item_data", FT_BYTES, BASE_NONE, 0x0, 0x0,
        "The data for an unknown item type", HFILL }
    },
    { &hf_security_info_option,
      { "Security Option", "wccp.security_info_option", FT_UINT16, BASE_DEC, VALS(security_option_vals), 0x0,
        NULL, HFILL }
    },
    { &hf_security_info_md5_checksum,
      { "MD5 checksum (not checked)", "wccp.security_md5_checksum", FT_BYTES, BASE_NONE, 0x0, 0x0,
        NULL, HFILL }
    },
    { &hf_command_element_type,
      {"Command Extension Type", "wccp.command_element_type", FT_UINT16, BASE_DEC, VALS(wccp_command_type_vals), 0x0,
       NULL, HFILL }
    },
    { &hf_command_element_length,
      {"Command Extension Length", "wccp.command_element_length", FT_UINT16, BASE_DEC, NULL, 0x0,
       NULL, HFILL }
    },
    { &hf_command_element_shutdown_ip,
      {"Command Extension Length", "wccp.command_element_shudown_ip", FT_UINT32, BASE_CUSTOM, wccp_fmt_ipadddress, 0x0,
       NULL, HFILL }
    },
    { &hf_service_info_type,
      { "Service Type", "wccp.service_info_type", FT_UINT8, BASE_DEC, VALS(service_type_vals), 0x0,
        NULL, HFILL }
    },
    { &hf_service_info_id_standard,
      { "WCCP Service ID (Standard)", "wccp.service_info_std_id", FT_UINT8, BASE_DEC, VALS(service_id_vals) , 0x0,
        "The WCCP Service id (Standard)", HFILL }
    },
    { &hf_service_info_id_dynamic,
      { "WCCP Service ID ( Dynamic)", "wccp.service_info_dyn_id", FT_UINT8, BASE_DEC, NULL , 0x0,
        "The WCCP Service id (Dynamic)", HFILL }
    },
    { &hf_service_info_priority,
      { "Priority (highest is 255)", "wccp.service_info_priority", FT_UINT8, BASE_DEC, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_service_info_protocol,
      { "Protocol", "wccp.service_info_protocol", FT_UINT8, BASE_DEC | BASE_EXT_STRING, &ipproto_val_ext, 0x0,
        NULL, HFILL }
    },
    { &hf_service_info_flags,
      { "Flags", "wccp.service_info_flags", FT_UINT32, BASE_HEX, 0x0, 0x0,
        NULL, HFILL }
    },
    { &hf_service_info_flags_src_ip_hash,
      { "Source IP address in primary hash", "wccp.service_info_flag.src_ip_hash", FT_BOOLEAN, 32, TFS(&tfs_used_notused), WCCP2_SI_SRC_IP_HASH,
        NULL, HFILL }
    },
    { &hf_service_info_flags_dest_ip_hash,
      { "Destination IP address in primary hash", "wccp.service_info_flag.dest_ip_hash", FT_BOOLEAN, 32, TFS(&tfs_used_notused), WCCP2_SI_DST_IP_HASH,
        NULL, HFILL }
    },
    { &hf_service_info_flags_src_port_hash,
      { "Source port in primary hash", "wccp.service_info_flag.src_port_hash", FT_BOOLEAN, 32, TFS(&tfs_used_notused), WCCP2_SI_SRC_PORT_HASH,
        NULL, HFILL }
    },
    { &hf_service_info_flags_dest_port_hash,
      { "Destination port in primary hash", "wccp.service_info_flag.dest_port_hash", FT_BOOLEAN, 32, TFS(&tfs_used_notused), WCCP2_SI_DST_PORT_HASH,
        NULL, HFILL }
    },
    { &hf_service_info_flags_ports_defined,
      { "Ports", "wccp.service_info_flag.ports_defined", FT_BOOLEAN, 32, TFS(&tfs_defined_not_defined), WCCP2_SI_PORTS_DEFINED,
        NULL, HFILL }
    },
    { &hf_service_info_flags_ports_source,
      { "Ports refer to", "wccp.service_info_flag.ports_source", FT_BOOLEAN, 32, TFS(&tfs_src_dest_port), WCCP2_SI_PORTS_SOURCE,
        NULL, HFILL }
    },
    { &hf_service_info_flags_redirect_only_protocol_0,
      { "Redirect only protocol 0", "wccp.service_info_flag.redirect_only_protocol_0", FT_BOOLEAN, 32, TFS(&tfs_redirect_protocol0), WCCP2r1_SI_REDIRECT_ONLY_PROTOCOL_0,
        NULL, HFILL }
    },
    { &hf_service_info_flags_src_ip_alt_hash,
      { "Source IP address in secondary hash", "wccp.service_info_flag.src_ip_alt_hash", FT_BOOLEAN, 32, TFS(&tfs_used_notused), WCCP2_SI_SRC_IP_ALT_HASH,
        NULL, HFILL }
    },
    { &hf_service_info_flags_dest_ip_alt_hash,
      { "Destination IP address in secondary hash", "wccp.service_info_flag.dest_ip_alt_hash", FT_BOOLEAN, 32, TFS(&tfs_used_notused), WCCP2_SI_DST_IP_ALT_HASH,
        NULL, HFILL }
    },
    { &hf_service_info_flags_src_port_alt_hash,
      { "Source port in secondary hash", "wccp.service_info_flag.src_port_alt_hash", FT_BOOLEAN, 32, TFS(&tfs_used_notused), WCCP2_SI_SRC_PORT_ALT_HASH,
        NULL, HFILL }
    },
    { &hf_service_info_flags_dest_port_alt_hash,
      { "Destination port in secondary hash", "wccp.service_info_flag.dest_port_alt_hash", FT_BOOLEAN, 32, TFS(&tfs_used_notused), WCCP2_SI_DST_PORT_ALT_HASH,
        NULL, HFILL }
    },
    { &hf_service_info_source_port,
      { "Source Port", "wccp.service_info_source_port", FT_UINT16, BASE_DEC, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_service_info_destination_port,
      { "Destination Port", "wccp.service_info_destination_port", FT_UINT16, BASE_DEC, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_router_identity_ip,
      { "IP Address", "wccp.router_identity.ip", FT_UINT32, BASE_CUSTOM, wccp_fmt_ipadddress, 0x0,
        NULL, HFILL }
    },
    { &hf_router_identity_receive_id,
      { "Received ID", "wccp.router_identity.receive_id", FT_UINT32, BASE_DEC, 0x0, 0x0,
        NULL, HFILL }
    },
    { &hf_router_identity_send_to_ip,
      { "Sent To IP Address", "wccp.router_identity.send_to_ip", FT_UINT32, BASE_CUSTOM, wccp_fmt_ipadddress, 0x0,
        NULL, HFILL }
    },
    { &hf_router_identity_received_from_num,
      { "Number of Received From IP addresses (Webcache to which the message is directed)", "wccp.router.num_recv_ip", FT_UINT32, BASE_DEC, 0x0, 0x0,
        NULL, HFILL }
    },
    { &hf_web_cache_identity_ip,
      { "Web-Cache IP Address", "wccp.web_cache_identity.ip", FT_UINT32, BASE_CUSTOM, wccp_fmt_ipadddress, 0x0,
        NULL, HFILL }
    },
    { &hf_web_cache_identity_hash_rev,
      { "Hash Revision", "wccp.web_cache_identity.hash_rev", FT_UINT16, BASE_DEC, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_web_cache_identity_flags,
      { "Flags", "wccp.web_cache_identity.flags", FT_UINT16, BASE_HEX, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_web_cache_identity_flag_hash_info,
      { "Hash information", "wccp.web_cache_identity.flags.hash_info", FT_BOOLEAN, 16,
        TFS(&tfs_historical_current), 0x1,
        NULL, HFILL }
    },
    { &hf_web_cache_identity_flag_assign_type,
      { "Assignment Type", "wccp.web_cache_identity.flags.assign_type", FT_UINT16, BASE_HEX,
        VALS(&wccp_web_cache_assignment_data_type_val), 0x6,
        NULL, HFILL }
    },
    { &hf_web_cache_identity_flag_version_request,
      { "Version Request", "wccp.web_cache_identity.flags.version_request", FT_BOOLEAN, 16,
        TFS(&tfs_version_min_max), 0x8,
        NULL, HFILL }
    },
    { &hf_mask_value_set_element_value_element_num,
      { "Number of Value Elements", "wccp.mask_value_set_selement.value_element_num", FT_UINT32, BASE_DEC, 0x0, 0x0,
        NULL, HFILL }
    },
    { &hf_assignment_weight,
      { "Assignment Weight", "wccp.assignment_weight", FT_UINT16, BASE_DEC, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_assignment_status,
      { "Status", "wccp.assignment_status", FT_UINT16, BASE_HEX, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_assignment_key_ip,
      { "Assignment Key IP Address", "wccp.assignment_key.ip", FT_UINT32, BASE_CUSTOM, wccp_fmt_ipadddress, 0x0,
        NULL, HFILL }
    },
    { &hf_assignment_key_change_num,
      { "Assignment Key Change Number", "wccp.assignment_key.change_num", FT_UINT32, BASE_DEC, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_router_view_member_change_num,
      { "Member Change Number", "wccp.router_view.member_change_num", FT_UINT32, BASE_DEC, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_router_router_num,
      { "Number of Routers", "wccp.router_view.router_num", FT_UINT32, BASE_DEC, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_router_identity_router_ip,
      { "Router IP Address", "wccp.router_identity.router_ip", FT_UINT32, BASE_CUSTOM, wccp_fmt_ipadddress, 0x0,
        NULL, HFILL }
    },
    { &hf_router_identity_received_from_ip,
      { "Received From IP Address/Target Web Cache IP", "wccp.router_identity.received_from_ip", FT_UINT32, BASE_CUSTOM, wccp_fmt_ipadddress, 0x0,
        NULL, HFILL }
    },
    { &hf_wc_view_info_change_num,
      { "Change Number", "wccp.wc_view_info.change_num", FT_UINT32, BASE_DEC, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_wc_view_info_router_ip,
      { "Router IP", "wccp.wc_view_info.router_ip", FT_UINT32, BASE_CUSTOM, wccp_fmt_ipadddress, 0x0,
        NULL, HFILL }
    },
    { &hf_wc_view_info_wc_ip,
      { "Web Cache IP", "wccp.wc_view_info.wc_ip", FT_UINT32, BASE_CUSTOM, wccp_fmt_ipadddress, 0x0,
        NULL, HFILL }
    },
    { &hf_wc_view_router_num,
      { "Number of Routers", "wccp.wc_view_info.router_num", FT_UINT32, BASE_DEC, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_wc_view_wc_num,
      { "Number of Web Caches", "wccp.wc_view_info.wc_num", FT_UINT32, BASE_DEC, 0x0, 0x0,
        NULL, HFILL }
    },
    { &hf_wc_identity_ip_address,
      { "Web Cache Identity", "wccp.hf_wc_identity_ip_address", FT_UINT32, BASE_CUSTOM, wccp_fmt_ipadddress, 0x0,
        "The IP identifying the Web Cache", HFILL }
    },
    { &hf_router_assignment_element_change_num,
      { "Change Number", "wccp.router_assignment_element.change_num", FT_UINT32, BASE_DEC, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_assignment_info_router_num,
      { "Number of Routers", "wccp.assignment_info.router_num", FT_UINT32, BASE_DEC, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_assignment_info_router_ip,
      { "Router IP", "wccp.assignment_info.router_ip", FT_UINT32, BASE_CUSTOM, wccp_fmt_ipadddress, 0x0,
        NULL, HFILL }
    },
    { &hf_hash_buckets_assignment_wc_num,
      { "Number of WC", "wccp.hash_buckets_assignment.wc_num", FT_UINT32, BASE_DEC, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_hash_buckets_assignment_wc_ip,
      { "WC IP", "wccp.hash_buckets_assignment.wc_ip", FT_UINT32, BASE_CUSTOM, wccp_fmt_ipadddress, 0x0,
        NULL, HFILL }
    },
    { &hf_router_view_ip,
      { "Router IP Address", "wccp.router_view.ip", FT_UINT32, BASE_CUSTOM, wccp_fmt_ipadddress, 0x0,
        NULL, HFILL }
    },
    { &hf_router_query_info_ip,
      { "Web-Cache Identity Element IP address", "wccp.router_query_info.ip", FT_UINT32, BASE_CUSTOM, wccp_fmt_ipadddress, 0x0,
        NULL, HFILL }
    },
    { &hf_router_query_info_send_to_ip,
      { "Sent To IP Address", "wccp.router_query_info.send_to_ip", FT_UINT32, BASE_CUSTOM, wccp_fmt_ipadddress, 0x0,
        NULL, HFILL }
    },
    { &hf_router_query_info_target_ip,
      { "Target IP Address", "wccp.router_query_info.target_ip", FT_UINT32, BASE_CUSTOM, wccp_fmt_ipadddress, 0x0,
        NULL, HFILL }
    },
    { &hf_capability_element_type,
      { "Type", "wccp.capability_element.type", FT_UINT16, BASE_DEC, VALS(capability_type_vals), 0x0,
        NULL, HFILL }
    },
    { &hf_capability_element_length,
      { "Value Length", "wccp.capability_element.length", FT_UINT16, BASE_DEC, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_capability_info_value,
      { "Value", "wccp.capability_info.value", FT_UINT32, BASE_HEX, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_capability_forwarding_method_flag_gre,
      { "GRE-encapsulated", "wccp.capability_info.forwarding_method_flag.gre", FT_BOOLEAN, 32, TFS(&tfs_supported_not_supported), WCCP2_FORWARDING_METHOD_GRE,
        NULL, HFILL }
    },
    { &hf_capability_forwarding_method_flag_l2,
      { "L2 rewrite", "wccp.capability_info.forwarding_method_flag.l2", FT_BOOLEAN, 32, TFS(&tfs_supported_not_supported), WCCP2_FORWARDING_METHOD_L2,
        NULL, HFILL }
    },
    { &hf_capability_assignment_method_flag_hash,
      { "Hash", "wccp.capability_info.assignment_method_flag.hash", FT_BOOLEAN, 32, TFS(&tfs_supported_not_supported), WCCP2_ASSIGNMENT_METHOD_HASH,
        NULL, HFILL }
    },
    { &hf_capability_assignment_method_flag_mask,
      { "Mask", "wccp.capability_info.assignment_method_flag.mask", FT_BOOLEAN, 32, TFS(&tfs_supported_not_supported), WCCP2_ASSIGNMENT_METHOD_MASK,
        NULL, HFILL }
    },
    { &hf_capability_return_method_flag_gre,
      { "GRE-encapsulated", "wccp.capability_info.return_method_flag.gre", FT_BOOLEAN, 32, TFS(&tfs_supported_not_supported), WCCP2_PACKET_RETURN_METHOD_GRE,
        NULL, HFILL }
    },
    { &hf_capability_return_method_flag_l2,
      { "L2 rewrite", "wccp.capability_info.return_method_flag.l2", FT_BOOLEAN, 32, TFS(&tfs_supported_not_supported), WCCP2_PACKET_RETURN_METHOD_L2,
        NULL, HFILL }
    },
    { &hf_capability_transmit_t,
      { "Message interval in milliseconds", "wccp.capability.transmit_t", FT_UINT16, BASE_DEC, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_capability_transmit_t_upper_limit,
      { "Message interval upper limit in milliseconds", "wccp.capability.transmit_t.upper_limit", FT_UINT16, BASE_DEC, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_capability_transmit_t_lower_limit,
      { "Message interval lower limit in milliseconds", "wccp.capability.transmit_t.upper_limit", FT_UINT16, BASE_DEC, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_capability_timer_scale_timeout_scale,
      { "Timer scale", "wccp.capability.timer_scale.timeout_scale", FT_UINT8, BASE_DEC, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_capability_timer_scale_timeout_scale_upper_limit,
      { "Timer scale upper limit", "wccp.capability.timer_scale.timeout_scale.upper_limit", FT_UINT8, BASE_DEC, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_capability_timer_scale_timeout_scale_lower_limit,
      { "Timer scale lower limit", "wccp.capability.timer_scale.timeout_scale.lower_limit", FT_UINT8, BASE_DEC, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_capability_timer_scale_ra_timer_scale,
      { "RA Timer scale", "wccp.capability.timer_scale.ra_timer_scale", FT_UINT8, BASE_DEC, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_capability_timer_scale_ra_scale_upper_limit,
      { "RA Timer scale upper limit", "wccp.capability.timer_scale.ra_timer_scale.upper_limit", FT_UINT8, BASE_DEC, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_capability_timer_scale_ra_scale_lower_limit,
      { "RA Timer scale lower limit", "wccp.capability.timer_scale.ra_timer_scale.lower_limit", FT_UINT8, BASE_DEC, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_value_element_src_ip,
      { "Source Address", "wccp.value_element.src_ip", FT_UINT32, BASE_CUSTOM, wccp_fmt_ipadddress, 0x0,
        NULL, HFILL }
    },
    { &hf_value_element_dest_ip,
      { "Destination Address", "wccp.value_element.dest_ip", FT_UINT32, BASE_CUSTOM, wccp_fmt_ipadddress, 0x0,
        NULL, HFILL }
    },
    { &hf_value_element_src_port,
      { "Source Port", "wccp.value_element.src_port", FT_UINT16, BASE_DEC, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_value_element_dest_port,
      { "Destination Port", "wccp.value_element.dest_port", FT_UINT16, BASE_DEC, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_value_element_web_cache_ip,
      { "Web Cache Address", "wccp.value_element.web_cache_ip", FT_UINT32, BASE_CUSTOM, wccp_fmt_ipadddress, 0x0,
        NULL, HFILL }
    },
    { &hf_mask_value_set_list_num_elements,
      { "Number of elements", "wccp.mask_value_set_list.num_elements", FT_UINT32, BASE_DEC, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_mask_element_src_ip,
      { "Source Address Mask", "wccp.mask_element.src_ip", FT_UINT32, BASE_HEX, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_mask_element_dest_ip,
      { "Destination Address Mask", "wccp.mask_element.dest_ip", FT_UINT32, BASE_HEX, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_mask_element_src_port,
      { "Source Port Mask", "wccp.mask_element.src_port", FT_UINT16, BASE_HEX, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_mask_element_dest_port,
      { "Destination Port Mask", "wccp.mask_element.dest_port", FT_UINT16, BASE_HEX, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_alt_assignment_info_assignment_type,
      { "Assignment type", "wccp.alt_assignment_info.assignment_type", FT_UINT16, BASE_DEC, VALS(assignment_type_vals), 0x0,
        NULL, HFILL }
    },
    { &hf_extended_assignment_data_type,
      { "Assignment type", "wccp.extended_assignment_data.type", FT_UINT16, BASE_DEC, VALS(assignment_type_vals), 0x0,
        NULL, HFILL }
    },
    { &hf_alt_assignment_map_assignment_type,
      { "Assignment type", "wccp.alt_assignment_map.assignment_type", FT_UINT16, BASE_DEC, VALS(assignment_type_vals), 0x0,
        NULL, HFILL }
    },
    { &hf_alt_assignment_map_assignment_length,
      { "Assignment length", "wccp.alt_assignment_map.assignment_length", FT_UINT16, BASE_DEC, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_alt_assignment_info_assignment_length,
      { "Assignment length", "wccp.alt_assignment_info.assignment_length", FT_UINT16, BASE_DEC, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_extended_assignment_data_length,
      { "Assignment length", "wccp.extended_assignment_data.length", FT_UINT16, BASE_DEC, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_alt_assignment_info_num_routers,
      { "Number of routers", "wccp.alt_assignment_info.num_routers", FT_UINT32, BASE_DEC, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_alt_assignment_mask_value_set_element_num_wc_value_elements,
      { "Number of Web-Cache Value Elements", "wccp.alt_assignment_mask_value_set_element.num_wc_value_elements", FT_UINT32, BASE_DEC, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_web_cache_value_element_wc_address,
      { "Web-Cache Address", "wccp.web_cache_value_element.wc_address", FT_UINT32, BASE_CUSTOM, wccp_fmt_ipadddress, 0x0,
        NULL, HFILL }
    },
    { &hf_web_cache_value_element_num_values,
      { "Number of Valye Sequence Numbers", "wccp.web_cache_value_element.num_values", FT_UINT32, BASE_DEC, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_alt_assignment_mask_value_set_list_num_elements,
      { "Number of Alternate Mask/Value Set Elements", "wccp.alt_assignment_mask_value_list.num_elements", FT_UINT32, BASE_DEC, NULL, 0x0,
        NULL, HFILL }
    },
    { &hf_address_table_family,
      { "Family Type", "wccp.address_table.family_type", FT_UINT16, BASE_DEC, VALS(wccp_address_family_val), 0x0,
        "The WCCP Address Table Family type", HFILL }
    },
    { &hf_address_table_address_length,
      { "Address Length", "wccp.address_table.address_length", FT_UINT16, BASE_DEC, NULL, 0x0,
        "The WCCP Address Table Address Length", HFILL }
    },
    { &hf_address_table_length,
      { "Length", "wccp.address_table.length", FT_UINT16, BASE_DEC, NULL, 0x0,
        "The WCCP Address Table Length", HFILL }
    },
    { &hf_address_table_element,
      { "Address", "wccp.address_table.element", FT_STRING, BASE_NONE, NULL, 0x0,
        NULL, HFILL }
    },

  };
  static gint *ett[] = {
    &ett_wccp,
    &ett_buckets,
    &ett_hash_assignment_buckets,
    &ett_mask_assignment_data_element,
    &ett_alternate_mask_assignment_data_element,
    &ett_extended_assigment_data_element,
    &ett_table_element,
    &ett_hash_flags,
    &ett_wc_identity_flags,
    &ett_cache_info,
    &ett_security_info,
    &ett_service_info,
    &ett_service_flags,
    &ett_service_info_ports,
    &ett_wc_view_info_router_element,
    &ett_router_identity_info,
    &ett_wc_identity_element,
    &ett_wc_identity_info,
    &ett_router_view_info,
    &ett_wc_view_info,
    &ett_query_info,
    &ett_router_assignment_element,
    &ett_hash_buckets_assignment_wc_element,
    &ett_hash_buckets_assignment_buckets,
    &ett_router_alt_assignment_element,
    &ett_router_assignment_info,
    &ett_capabilities_info,
    &ett_capability_element,
    &ett_capability_forwarding_method,
    &ett_capability_assignment_method,
    &ett_capability_return_method,
    &ett_capability_transmit_t,
    &ett_capability_timer_scale,
    &ett_mv_set_list,
    &ett_mv_set_element,
    &ett_mv_set_value_list,
    &ett_alternate_mv_set_element_list,
    &ett_web_cache_value_element_list,
    &ett_alternate_mv_set_element,
    &ett_value_element,
    &ett_alt_assignment_info,
    &ett_alt_assignment_map,
    &ett_assignment_map,
    &ett_address_table,
    &ett_unknown_info,
    &ett_alternate_mask_value_set,
    &ett_alternate_mask_value_set_element,
    &ett_command_extension,
  };

  static ei_register_info ei[] = {
     { &ei_wccp_missing_security_info, { "wccp.missing.security_info", PI_PROTOCOL, PI_ERROR, "This message should contain a Security Info component, but it is missing", EXPFILL }},
     { &ei_wccp_missing_service_info, { "wccp.missing.service_info", PI_PROTOCOL, PI_ERROR, "This message should contain a Service Info component, but it is missing", EXPFILL }},
     { &ei_wccp_missing_wc_id_info, { "wccp.missing.wc_id_info", PI_PROTOCOL, PI_ERROR, "This message should contain a Web-Cache Identity Info component, but it is missing", EXPFILL }},
     { &ei_wccp_missing_router_id_info, { "wccp.missing.router_id_info", PI_PROTOCOL, PI_ERROR, "This message should contain a Router Identity Info component, but it is missing", EXPFILL }},
     { &ei_wccp_missing_query_info, { "wccp.missing.query_info", PI_PROTOCOL, PI_ERROR, "This message should contain a Query Info component, but it is missing", EXPFILL }},
     { &ei_wccp_missing_wc_view_info, { "wccp.missing.wc_view_info", PI_PROTOCOL, PI_ERROR, "This message should contain a Web-Cache View Info component, but it is missing", EXPFILL }},
     { &ei_wccp_missing_rtr_view_info, { "wccp.missing.rtr_view_info", PI_PROTOCOL, PI_ERROR, "This message should contain a Router View Info component, but it is missing", EXPFILL }},
     { &ei_wccp_missing_assignment, { "wccp.missing.assignment", PI_PROTOCOL, PI_ERROR, "This message should contain a Alternate Assignment, Assignment Map, Assignment Info or "
                                      "Alternative Assignment Map component, but it is missing", EXPFILL }},
     { &ei_wccp_contains_redirect_assignment, { "wccp.contains.redirect_assignment", PI_PROTOCOL, PI_ERROR, "This message contains a Assignment Info component, but it should not", EXPFILL }},
     { &ei_wccp_contains_router_id_info, { "wccp.contains.router_id_info", PI_PROTOCOL, PI_ERROR, "This message contains a Router Identity Info component, but it should not", EXPFILL }},
     { &ei_wccp_contains_rtr_view_info, { "wccp.contains.rtr_view_info", PI_PROTOCOL, PI_ERROR, "This message contains a Router View Info component, but it should not", EXPFILL }},
     { &ei_wccp_contains_query_info, { "wccp.contains.query_info", PI_PROTOCOL, PI_ERROR, "This message contains a Query Info component, but it should not", EXPFILL }},
     { &ei_wccp_contains_alt_assignment, { "wccp.contains.alt_assignment", PI_PROTOCOL, PI_ERROR, "This message contains a Alternate Assignment component, but it should not", EXPFILL }},
     { &ei_wccp_contains_assign_map, { "wccp.contains.assign_map", PI_PROTOCOL, PI_ERROR, "This message contains a Assignment Map component, but it should not", EXPFILL }},
     { &ei_wccp_contains_alt_assignment_map, { "wccp.contains.alt_assignment_map", PI_PROTOCOL, PI_ERROR, "This message contains a Alternative Assignment Map component, but it should not", EXPFILL }},
     { &ei_wccp_contains_wc_id_info, { "wccp.contains.wc_id_info", PI_PROTOCOL, PI_ERROR, "This message contains a Web-Cache Identity Info component, but it should not", EXPFILL }},
     { &ei_wccp_contains_wc_view_info, { "wccp.contains.wc_view_info", PI_PROTOCOL, PI_ERROR, "This message contains a Web-Cache View Info component, but it should not", EXPFILL }},
     { &ei_wccp_contains_capabilities_info, { "wccp.contains.capabilities_info", PI_PROTOCOL, PI_ERROR, "This message contains a Capabilities Info component, but it should not", EXPFILL }},
     { &ei_wccp_contains_command_extension, { "wccp.contains.command_extension", PI_PROTOCOL, PI_ERROR, "This message contains a Command Extension component, but it should not", EXPFILL }},
     { &ei_wccp_assignment_length_bad, { "wccp.assignment_length_bad", PI_PROTOCOL, PI_ERROR, "Assignment length bad", EXPFILL }},
     { &ei_wccp_length_bad, { "wccp.length_bad", PI_PROTOCOL, PI_ERROR, "Length bad", EXPFILL }},
     { &ei_wccp_service_info_priority_nonzero, { "wccp.service_info_priority.nonzero", PI_PROTOCOL, PI_WARN, "The priority must be zero for well-known services.", EXPFILL }},
     { &ei_wccp_service_info_protocol_nonzero, { "wccp.service_info_protocol.nonzero", PI_PROTOCOL, PI_WARN, "The protocol must be zero for well-known services.", EXPFILL }},
     { &ei_wccp_router_identity_receive_id_zero, { "wccp.router_identity.receive_id.zero", PI_PROTOCOL, PI_WARN, "Receive ID shouldn't be 0", EXPFILL }},
     { &ei_wccp_web_cache_identity_hash_rev_zero, { "wccp.web_cache_identity.hash_rev.zero", PI_PROTOCOL, PI_WARN, "Should be 0 (6.4)", EXPFILL }},
     { &ei_wccp_address_table_family_unknown, { "wccp.address_table.family_type.unknown", PI_PROTOCOL, PI_ERROR, "Unknown address family", EXPFILL }},
     { &ei_wccp_capability_element_length, { "wccp.capability_element.length.invalid", PI_PROTOCOL, PI_WARN, "Value Length invalid", EXPFILL }},
  };

  expert_module_t* expert_wccp;

  proto_wccp = proto_register_protocol("Web Cache Communication Protocol",
                                       "WCCP", "wccp");
  proto_register_field_array(proto_wccp, hf, array_length(hf));
  proto_register_subtree_array(ett, array_length(ett));
  expert_wccp = expert_register_protocol(proto_wccp);
  expert_register_field_array(expert_wccp, ei, array_length(ei));
}

void
proto_reg_handoff_wccp(void)
{
  dissector_handle_t wccp_handle;

  wccp_handle = new_create_dissector_handle(dissect_wccp, proto_wccp);
  dissector_add_uint("udp.port", UDP_PORT_WCCP, wccp_handle);
}

/*
 * Editor modelines  -  http://www.wireshark.org/tools/modelines.html
 *
 * Local variables:
 * c-basic-offset: 2
 * tab-width: 8
 * indent-tabs-mode: nil
 * End:
 *
 * vi: set shiftwidth=2 tabstop=8 expandtab:
 * :indentSize=2:tabSize=8:noTabs=true:
 */

