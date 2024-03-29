/*
 *  wslua_field.c
 *
 * Wireshark's interface to the Lua Programming Language
 *
 * (c) 2006, Luis E. Garcia Ontanon <luis@ontanon.org>
 *
 * $Id: wslua_field.c 53225 2013-11-10 14:00:29Z darkjames $
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

#include <epan/emem.h>
#include <epan/ftypes/ftypes-int.h>

/* WSLUA_MODULE Field Obtaining dissection data */

#include "wslua.h"

WSLUA_CLASS_DEFINE(FieldInfo,NOP,NOP);
/*
   An extracted Field
   */

WSLUA_METAMETHOD FieldInfo__len(lua_State* L) {
    /*
       Obtain the Length of the field
       */
    FieldInfo fi = checkFieldInfo(L,1);
    lua_pushnumber(L,fi->length);
    return 1;
}

WSLUA_METAMETHOD FieldInfo__unm(lua_State* L) {
    /*
       Obtain the Offset of the field
       */
    FieldInfo fi = checkFieldInfo(L,1);
    lua_pushnumber(L,fi->start);
    return 1;
}

WSLUA_METAMETHOD FieldInfo__call(lua_State* L) {
    /*
       Obtain the Value of the field
       */
    FieldInfo fi = checkFieldInfo(L,1);

    switch(fi->hfinfo->type) {
        case FT_BOOLEAN:
                lua_pushboolean(L,(int)fvalue_get_uinteger(&(fi->value)));
                return 1;
        case FT_UINT8:
        case FT_UINT16:
        case FT_UINT24:
        case FT_UINT32:
        case FT_FRAMENUM:
                lua_pushnumber(L,(lua_Number)fvalue_get_uinteger(&(fi->value)));
                return 1;
        case FT_INT8:
        case FT_INT16:
        case FT_INT24:
        case FT_INT32:
                lua_pushnumber(L,(lua_Number)fvalue_get_sinteger(&(fi->value)));
                return 1;
        case FT_FLOAT:
        case FT_DOUBLE:
                lua_pushnumber(L,(lua_Number)fvalue_get_floating(&(fi->value)));
                return 1;
        case FT_INT64: {
                Int64 num = (Int64)g_malloc(sizeof(gint64));
                *num = fvalue_get_integer64(&(fi->value));
                pushInt64(L,num);
                return 1;
            }
        case FT_UINT64: {
                UInt64 num = (UInt64)g_malloc(sizeof(guint64));
                *num = fvalue_get_integer64(&(fi->value));
                pushUInt64(L,num);
                return 1;
            }
        case FT_ETHER: {
                Address eth = (Address)g_malloc(sizeof(address));
                eth->type = AT_ETHER;
                eth->len = fi->length;
                eth->data = tvb_memdup(NULL,fi->ds_tvb,fi->start,fi->length);
                pushAddress(L,eth);
                return 1;
            }
        case FT_IPv4:{
                Address ipv4 = (Address)g_malloc(sizeof(address));
                ipv4->type = AT_IPv4;
                ipv4->len = fi->length;
                ipv4->data = tvb_memdup(NULL,fi->ds_tvb,fi->start,fi->length);
                pushAddress(L,ipv4);
                return 1;
            }
        case FT_IPv6: {
                Address ipv6 = (Address)g_malloc(sizeof(address));
                ipv6->type = AT_IPv6;
                ipv6->len = fi->length;
                ipv6->data = tvb_memdup(NULL,fi->ds_tvb,fi->start,fi->length);
                pushAddress(L,ipv6);
                return 1;
            }
        case FT_IPXNET:{
                Address ipx = (Address)g_malloc(sizeof(address));
                ipx->type = AT_IPX;
                ipx->len = fi->length;
                ipx->data = tvb_memdup(NULL,fi->ds_tvb,fi->start,fi->length);
                pushAddress(L,ipx);
                return 1;
            }
        case FT_ABSOLUTE_TIME:
        case FT_RELATIVE_TIME: {
                NSTime nstime = (NSTime)g_malloc(sizeof(nstime_t));
                *nstime = *(NSTime)fvalue_get(&(fi->value));
                pushNSTime(L,nstime);
                return 1;
            }
        case FT_STRING:
        case FT_STRINGZ: {
                gchar* repr = fvalue_to_string_repr(&fi->value,FTREPR_DISPLAY,NULL);
                if (repr)
                    lua_pushstring(L,repr);
                else
                    luaL_error(L,"field cannot be represented as string because it may contain invalid characters");

                return 1;
            }
        case FT_NONE:
                if (fi->length == 0) {
                        lua_pushnil(L);
                        return 1;
                }
                /* FALLTHROUGH */
        case FT_BYTES:
        case FT_UINT_BYTES:
        case FT_GUID:
        case FT_PROTOCOL:
        case FT_REL_OID:
        case FT_OID: {
                ByteArray ba = g_byte_array_new();
                g_byte_array_append(ba, (const guint8 *)tvb_memdup(wmem_packet_scope(),fi->ds_tvb,fi->start,fi->length),fi->length);
                pushByteArray(L,ba);
                return 1;
            }
        default:
                luaL_error(L,"FT_ not yet supported");
                return 1;
    }
}

WSLUA_METAMETHOD FieldInfo__tostring(lua_State* L) {
    /* The string representation of the field */
    FieldInfo fi = checkFieldInfo(L,1);

    if (!fi) {
        return luaL_error(L,"Missing FieldInfo object");
    }

    if (fi->value.ftype->val_to_string_repr) {
        gchar* repr = fvalue_to_string_repr(&fi->value,FTREPR_DISPLAY,NULL);
        if (repr) {
            lua_pushstring(L,repr);
        }
        else {
            lua_pushstring(L,"(unknown)");
        }
    }
    else if (fi->hfinfo->type == FT_NONE) {
        lua_pushstring(L, "(none)");
    }
    else {
        lua_pushstring(L,"(n/a)");
    }

    return 1;
}

static int FieldInfo_display(lua_State* L) {
    /* The display string of this field as seen in GUI */
    FieldInfo fi = checkFieldInfo(L,1);
    gchar         label_str[ITEM_LABEL_LENGTH+1];
    gchar        *label_ptr;
    gchar        *value_ptr;

    if (!fi) return 0;

    if (!fi->rep) {
        label_ptr = label_str;
        proto_item_fill_label(fi, label_str);
    } else 
        label_ptr = fi->rep->representation;

    if (!label_ptr) return 0;

    value_ptr = strstr(label_ptr, ": ");
    if (!value_ptr) {
        /* just use whatever's there */
        lua_pushstring(L, label_ptr);
    } else {
        value_ptr += 2;  /* get past the ': ' */
        lua_pushstring(L, value_ptr);
    }

    return 1;
}

static int FieldInfo_get_range(lua_State* L) {
    /* The TvbRange covering this field */
    FieldInfo fi = checkFieldInfo(L,1);
    TvbRange r = ep_new(struct _wslua_tvbrange);
    r->tvb = ep_new(struct _wslua_tvb);

    r->tvb->ws_tvb = fi->ds_tvb;
    r->tvb->expired = FALSE;
    r->tvb->need_free = FALSE;
    r->offset = fi->start;
    r->len = fi->length;

    pushTvbRange(L,r);
    return 1;
}

static int FieldInfo_get_generated(lua_State* L) {
    /* Whether this field was marked as generated. */
    FieldInfo fi = checkFieldInfo(L,1);
    lua_pushboolean(L,FI_GET_FLAG(fi, FI_GENERATED));
    return 1;
}

static int FieldInfo_get_name(lua_State* L) {
    /* The filter name of this field. */
    FieldInfo fi = checkFieldInfo(L,1);
    lua_pushstring(L,fi->hfinfo->abbrev);
    return 1;
}

static const luaL_Reg FieldInfo_get[] = {
    /*    {"data_source", FieldInfo_get_data_source }, */
    {"range", FieldInfo_get_range},
    /*    {"hidden", FieldInfo_get_hidden}, */
    {"generated", FieldInfo_get_generated},

    /* WSLUA_ATTRIBUTE FieldInfo_name RO The name of this field */
    {"name", FieldInfo_get_name},
    /* WSLUA_ATTRIBUTE FieldInfo_label RO The string representing this field */
    {"label", FieldInfo__tostring},
    /* WSLUA_ATTRIBUTE FieldInfo_value RO The value of this field */
    {"value", FieldInfo__call},
    /* WSLUA_ATTRIBUTE FieldInfo_tvb RO A tvbrange covering this field */
    {"tvb", FieldInfo_get_range},
    /* WSLUA_ATTRIBUTE FieldInfo_len RO The length of this field */
    {"len", FieldInfo__len},
    /* WSLUA_ATTRIBUTE FieldInfo_offset RO The offset of this field */
    {"offset", FieldInfo__unm},
    /* WSLUA_ATTRIBUTE FieldInfo_display RO The string display of this field as seen in GUI */
    {"display", FieldInfo_display},
    { NULL, NULL }
};

static int FieldInfo__index(lua_State* L) {
    /*
       Other attributes:
       */
    const gchar* idx = luaL_checkstring(L,2);
    const luaL_Reg* r;

    checkFieldInfo(L,1);

    for (r = FieldInfo_get; r->name; r++) {
        if (g_str_equal(r->name, idx)) {
            return r->func(L);
        }
    }

    return 0;
}

WSLUA_METAMETHOD FieldInfo__eq(lua_State* L) {
    /* Checks whether lhs is within rhs */
    FieldInfo l = checkFieldInfo(L,1);
    FieldInfo r = checkFieldInfo(L,2);

    if (l->ds_tvb != r->ds_tvb)
        WSLUA_ERROR(FieldInfo__eq,"Data source must be the same for both fields");

    if (l->start <= r->start && r->start + r->length <= l->start + r->length) {
        lua_pushboolean(L,1);
        return 1;
    } else {
        return 0;
    }
}

WSLUA_METAMETHOD FieldInfo__le(lua_State* L) {
    /* Checks whether the end byte of lhs is before the end of rhs */
    FieldInfo l = checkFieldInfo(L,1);
    FieldInfo r = checkFieldInfo(L,2);

    if (l->ds_tvb != r->ds_tvb)
        WSLUA_ERROR(FieldInfo__le,"Data source must be the same for both fields");

    if (r->start + r->length <= l->start + r->length) {
        lua_pushboolean(L,1);
        return 1;
    } else {
        return 0;
    }
}

WSLUA_METAMETHOD FieldInfo__lt(lua_State* L) {
    /* Checks whether the end byte of rhs is before the beginning of rhs */
    FieldInfo l = checkFieldInfo(L,1);
    FieldInfo r = checkFieldInfo(L,2);

    if (l->ds_tvb != r->ds_tvb)
        WSLUA_ERROR(FieldInfo__lt,"Data source must be the same for both fields");

    if ( r->start + r->length < l->start ) {
        lua_pushboolean(L,1);
        return 1;
    } else {
        return 0;
    }
}

static int FieldInfo__gc(lua_State* L _U_) {
    /* do NOT free FieldInfo */
    return 0;
}

static const luaL_Reg FieldInfo_meta[] = {
    {"__tostring", FieldInfo__tostring},
    {"__call", FieldInfo__call},
    {"__index", FieldInfo__index},
    {"__len", FieldInfo__len},
    {"__unm", FieldInfo__unm},
    {"__eq", FieldInfo__eq},
    {"__le", FieldInfo__le},
    {"__lt", FieldInfo__lt},
    { NULL, NULL }
};

int FieldInfo_register(lua_State* L) {
    WSLUA_REGISTER_META(FieldInfo);
    return 1;
}


WSLUA_FUNCTION wslua_all_field_infos(lua_State* L) {
    /*
    Obtain all fields from the current tree.  Note this only gets whatever fields the underlying
    dissectors have filled in for this packet at this time - there may be fields applicable to
    the packet that simply aren't being filled in because at this time they're not needed for anything.
    This function only gets what the C-side code has currently populated, not the full list.
    */
    GPtrArray* found;
    int items_found = 0;
    guint i;

    if (! lua_tree || ! lua_tree->tree ) {
        WSLUA_ERROR(wslua_all_field_infos,"Cannot be called outside a listener or dissector");
    }

    found = proto_all_finfos(lua_tree->tree);

    if (found) {
        for (i=0; i<found->len; i++) {
            pushFieldInfo(L,(FieldInfo)g_ptr_array_index(found,i));
            items_found++;
        }

        g_ptr_array_free(found,TRUE);
    }

    return items_found;
}

WSLUA_CLASS_DEFINE(Field,NOP,NOP);
/*
   A Field extractor to to obtain field values.
 */

static GPtrArray* wanted_fields = NULL;
static dfilter_t* wslua_dfilter = NULL;

/* We use a fake dfilter for Lua field extractors, so that 
 * epan_dissect_run() will populate the fields.  This won't happen
 * if the passed-in edt->tree is NULL, which it will be if the 
 * proto_tree isn't created by epan_dissect_init().  But that's by
 * design - if shark doesn't pass in a proto_tree, it's probably for
 * a good reason and we shouldn't override that. (right?)
 */
void wslua_prime_dfilter(epan_dissect_t *edt) {
    if (wslua_dfilter && edt && edt->tree) {
        dfilter_prime_proto_tree(wslua_dfilter, edt->tree);
    }
}

/*
 * field extractor registartion is tricky, In order to allow
 * the user to define them in the body of the script we will
 * populate the Field value with a pointer of the abbrev of it
 * to later replace it with the hfi.
 *
 * This will be added to the wanted_fields array that will
 * exists only while they can be defined, and be cleared right
 * after the fields are primed.
 */

void lua_prime_all_fields(proto_tree* tree _U_) {
    GString* fake_tap_filter = g_string_new("frame");
    guint i;
    static gboolean fake_tap = FALSE;

    for(i=0; i < wanted_fields->len; i++) {
        Field f = (Field)g_ptr_array_index(wanted_fields,i);
        gchar* name = *((gchar**)f);

        *f = proto_registrar_get_byname(name);

        if (!*f) {
            report_failure("Could not find field `%s'",name);
            *f = NULL;
            g_free(name);
            continue;
        }

        g_free(name);

        g_string_append_printf(fake_tap_filter," || %s",(*f)->abbrev);
        fake_tap = TRUE;
    }

    g_ptr_array_free(wanted_fields,TRUE);
    wanted_fields = NULL;

    if (fake_tap) {
        /* a boring tap :-) */
        GString* error = register_tap_listener("frame",
                &fake_tap,
                fake_tap_filter->str,
                0, /* XXX - do we need the protocol tree or columns? */
                NULL, NULL, NULL);

        if (error) {
            report_failure("while registering lua_fake_tap:\n%s",error->str);
            g_string_free(error,TRUE);
        }
        else if (!dfilter_compile(fake_tap_filter->str, &wslua_dfilter)) {
            report_failure("while compiling dfilter for wslua: '%s'", fake_tap_filter->str);
        }
    }

}

WSLUA_CONSTRUCTOR Field_new(lua_State *L) {
    /*
       Create a Field extractor
       */
#define WSLUA_ARG_Field_new_FIELDNAME 1 /* The filter name of the field (e.g. ip.addr) */
    const gchar* name = luaL_checkstring(L,WSLUA_ARG_Field_new_FIELDNAME);
    Field f;

    if (!name) return 0;

    if (!proto_registrar_get_byname(name) && !wslua_is_field_available(L, name))
        WSLUA_ARG_ERROR(Field_new,FIELDNAME,"a field with this name must exist");

    if (!wanted_fields)
        WSLUA_ERROR(Field_new,"A Field extractor must be defined before Taps or Dissectors get called");

    f = (Field)g_malloc(sizeof(void*));
    *f = (header_field_info*)g_strdup(name); /* cheating */

    g_ptr_array_add(wanted_fields,f);

    pushField(L,f);
    WSLUA_RETURN(1); /* The field extractor */
}

WSLUA_METAMETHOD Field__call (lua_State* L) {
    /* Obtain all values (see FieldInfo) for this field. */
    Field f = checkField(L,1);
    header_field_info* in = *f;
    int items_found = 0;

    if (! in) {
        luaL_error(L,"invalid field");
        return 0;
    }

    if (! lua_pinfo ) {
        WSLUA_ERROR(Field__call,"Fields cannot be used outside dissectors or taps");
    }

    while (in) {
        GPtrArray* found = proto_get_finfo_ptr_array(lua_tree->tree, in->id);
        guint i;
        if (found) {
            for (i=0; i<found->len; i++) {
                pushFieldInfo(L,(FieldInfo)g_ptr_array_index(found,i));
                items_found++;
            }
        }
	in = (in->same_name_prev_id != -1) ? proto_registrar_get_nth(in->same_name_prev_id) : NULL;
    }

    WSLUA_RETURN(items_found); /* All the values of this field */
}

WSLUA_METAMETHOD Field__tostring(lua_State* L) {
	/* Obtain a string with the field name */
    Field f = checkField(L,1);

    if ( !(f && *f) ) {
        luaL_error(L,"invalid Field");
        return 0;
    }

    if (wanted_fields) {
        lua_pushstring(L,*((gchar**)f));
    } else {
        lua_pushstring(L,(*f)->abbrev);
    }

    return 1;
}

static int Field__gc(lua_State* L _U_) {
    /* do NOT free Field */
    return 0;
}

static const luaL_Reg Field_methods[] = {
    {"new", Field_new},
    { NULL, NULL }
};

static const luaL_Reg Field_meta[] = {
    {"__tostring", Field__tostring},
    {"__call", Field__call},
    { NULL, NULL }
};

int Field_register(lua_State* L) {

    wanted_fields = g_ptr_array_new();

    WSLUA_REGISTER_CLASS(Field);

    return 1;
}

/*
 * Editor modelines  -  http://www.wireshark.org/tools/modelines.html
 *
 * Local variables:
 * c-basic-offset: 4
 * tab-width: 8
 * indent-tabs-mode: nil
 * End:
 *
 * vi: set shiftwidth=4 tabstop=8 expandtab:
 * :indentSize=4:tabSize=8:noTabs=true:
 */
