/* expert.h
 * Collecting of Expert information.
 *
 * For further info, see: http://wiki.wireshark.org/Development/ExpertInfo
 *
 * $Id: expert.h 52341 2013-10-03 01:54:02Z mmann $
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

#ifndef __EXPERT_H__
#define __EXPERT_H__

#include <epan/packet_info.h>
#include <epan/proto.h>
#include "value_string.h"
#include "ws_symbol_export.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** only for internal and display use. */
typedef struct expert_info_s {
	guint32 packet_num;
	int group;
	int severity;
	const gchar *protocol;
	gchar *summary;
	proto_item *pitem;
} expert_info_t;

/* Expert Info and Display hf data */
typedef struct expert_field
{
	int ei;
	int hf;
} expert_field;

#define EI_INIT {-1, -1}

typedef struct expert_field_info {
	/* ---------- set by dissector --------- */
	const char *name;
	int group;
	int severity;
	const gchar *summary;

	/* ------- set by register routines (prefilled by EXPFILL macro, see below) ------ */
	int id;
	const gchar *protocol;
	hf_register_info hf_info;

} expert_field_info;

#define EXPFILL 0, NULL, \
        {0, {"Expert Info", NULL, FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL}}

typedef struct ei_register_info {
	expert_field      *ids;         /**< written to by register() function */
	expert_field_info eiinfo;      /**< the field info to be registered */
} ei_register_info;

typedef struct expert_module expert_module_t;

static const value_string expert_group_vals[] = {
        { PI_CHECKSUM,          "Checksum" },
        { PI_SEQUENCE,          "Sequence" },
        { PI_RESPONSE_CODE,     "Response" },
        { PI_REQUEST_CODE,      "Request" },
        { PI_UNDECODED,         "Undecoded" },
        { PI_REASSEMBLE,        "Reassemble" },
        { PI_MALFORMED,         "Malformed" },
        { PI_DEBUG,             "Debug" },
        { PI_PROTOCOL,          "Protocol" },
        { PI_SECURITY,          "Security" },
        { PI_COMMENTS_GROUP,    "Comment" },
        { 0, NULL }
};

static const value_string expert_severity_vals[] = {
        { PI_ERROR,             "Error" },
        { PI_WARN,              "Warn" },
        { PI_NOTE,              "Note" },
        { PI_CHAT,              "Chat" },
        { PI_COMMENT,           "Comment" },
        { 0,                    "Ok" },
        { 0, NULL }
};

#define PRE_ALLOC_EXPERT_FIELDS_MEM 5000

/* "proto_expert" is exported from libwireshark.dll.
 * Thus we need a special declaration.
 */
WS_DLL_PUBLIC int proto_expert;

extern void
expert_init(void);

extern void
expert_packet_init(void);

extern void
expert_cleanup(void);

extern void
expert_packet_cleanup(void);

WS_DLL_PUBLIC int
expert_get_highest_severity(void);

WS_DLL_PUBLIC void
expert_update_comment_count(guint64 count);

/** Add an expert info.
 Add an expert info tree to a protocol item using registered expert info item
 @param pinfo Packet info of the currently processed packet. May be NULL if
        pi is supplied
 @param pi Current protocol item (or NULL)
 @param eiindex The registered expert info item
 */
WS_DLL_PUBLIC void
expert_add_info(packet_info *pinfo, proto_item *pi, expert_field* eiindex);

/** Add an expert info. FOR INTERNAL (NON-DISSECTOR) USE ONLY!!!
 Add an expert info tree to a protocol item, with classification and message.
 @param pinfo Packet info of the currently processed packet. May be NULL if
        pi is supplied
 @param pi Current protocol item (or NULL)
 @param group The expert group (like PI_CHECKSUM - see: proto.h)
 @param severity The expert severity (like PI_WARN - see: proto.h)
 @param format Printf-style format string for additional arguments
 */
WS_DLL_PUBLIC void
expert_add_info_format_internal(packet_info *pinfo, proto_item *pi, int group,
	int severity, const char *format, ...)
	G_GNUC_PRINTF(5, 6);

/** Add an expert info.
 Add an expert info tree to a protocol item, using registered expert info item,
 but with a formatted message.
 @param pinfo Packet info of the currently processed packet. May be NULL if
        pi is supplied
 @param pi Current protocol item (or NULL)
 @param eiindex The registered expert info item
 @param format Printf-style format string for additional arguments
 */
WS_DLL_PUBLIC void
expert_add_info_format(packet_info *pinfo, proto_item *pi, expert_field *eiindex,
	const char *format, ...) G_GNUC_PRINTF(4, 5);

/** Add an expert info associated with some byte data
 Add an expert info tree to a protocol item using registered expert info item.
 This function is intended to replace places where 
 proto_tree_add_text or proto_tree_add_none_format + expert_add_info
 would be used.
 @param tree Current protocol item (or NULL)
 @param pinfo Packet info of the currently processed packet. May be NULL if
        pi is supplied
 @param eiindex The registered expert info item
 @param tvb the tv buffer of the current data
 @param start start of data in tvb
 @param length length of data in tvb
 @return the newly created item above expert info tree
 */
WS_DLL_PUBLIC proto_item *
proto_tree_add_expert(proto_tree *tree, packet_info *pinfo, expert_field* eiindex,
        tvbuff_t *tvb, gint start, gint length);

/** Add an expert info associated with some byte data
 Add an expert info tree to a protocol item, using registered expert info item,
 but with a formatted message.
 This function is intended to replace places where 
 proto_tree_add_text or proto_tree_add_none_format + expert_add_info_format
 would be used.
 @param tree Current protocol item (or NULL)
 @param pinfo Packet info of the currently processed packet. May be NULL if tree is supplied
 @param eiindex The registered expert info item
 @param tvb the tv buffer of the current data
 @param start start of data in tvb
 @param length length of data in tvb
 @return the newly created item above expert info tree
 */
WS_DLL_PUBLIC proto_item *
proto_tree_add_expert_format(proto_tree *tree, packet_info *pinfo, expert_field* eiindex,
        tvbuff_t *tvb, gint start, gint length, const char *format, ...) G_GNUC_PRINTF(7, 8);

/*
 * Register that a protocol has expert info.
 */
WS_DLL_PUBLIC expert_module_t *expert_register_protocol(int id);

/** Register a expert field array.
 @param module the protocol handle from expert_register_protocol()
 @param ei the ei_register_info array
 @param num_records the number of records in exp */
WS_DLL_PUBLIC void
expert_register_field_array(expert_module_t* module, ei_register_info *ei, const int num_records);

#define EXPERT_CHECKSUM_DISABLED    -2
#define EXPERT_CHECKSUM_UNKNOWN     -1
#define EXPERT_CHECKSUM_GOOD        0
#define EXPERT_CHECKSUM_BAD         1

WS_DLL_PUBLIC const value_string expert_checksum_vals[];

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __EXPERT_H__ */
