/* packet-zbee-zcl-meas-sensing.c
 * Dissector routines for the ZigBee ZCL Measurement & Sensing clusters like
 * Illuminance Measurement, Temperature Measurement ...
 * By Fabio Tarabelloni <fabio.tarabelloni@reloc.it>
 * Copyright 2013 RELOC s.r.l.
 *
 * $Id: packet-zbee-zcl-meas-sensing.c 52591 2013-10-13 19:56:52Z wmeier $
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

/*  Include Files */
#include "config.h"

#include <string.h>
#include <glib.h>
#include <epan/packet.h>

#include "packet-zbee.h"
#include "packet-zbee-aps.h"
#include "packet-zbee-zcl.h"


/* ########################################################################## */
/* #### (0x0400) ILLUMINANCE MEASUREMENT CLUSTER ############################ */
/* ########################################################################## */

/*************************/
/* Defines               */
/*************************/

#define ZBEE_ZCL_ILLUM_MEAS_NUM_GENERIC_ETT                     1
#define ZBEE_ZCL_ILLUM_MEAS_NUM_ETT                             ZBEE_ZCL_ILLUM_MEAS_NUM_GENERIC_ETT

/* Attributes */
#define ZBEE_ZCL_ATTR_ID_ILLUM_MEAS_MEASURED_VALUE              0x0000  /* Measured Value */
#define ZBEE_ZCL_ATTR_ID_ILLUM_MEAS_MIN_MEASURED_VALUE          0x0001  /* Min Measured Value */
#define ZBEE_ZCL_ATTR_ID_ILLUM_MEAS_MAX_MEASURED_VALUE          0x0002  /* Max Measured Value */
#define ZBEE_ZCL_ATTR_ID_ILLUM_MEAS_TOLERANCE                   0x0003  /* Tolerance */
#define ZBEE_ZCL_ATTR_ID_ILLUM_MEAS_LIGHT_SENSOR_TYPE           0x0004  /* Light Sensor Type */

/* Server Commands Received - None */

/* Server Commands Generated - None */

#define ZBEE_ZCL_ATTR_ID_ILLUM_MEAS_TOO_LOW_VALUE        0x0000  /* Too Low Value */
#define ZBEE_ZCL_ATTR_ID_ILLUM_MEAS_INVALID_VALUE        0x8000  /* Invalid Value */

#define ZBEE_ZCL_ATTR_ID_ILLUM_MEAS_MIN_LO_VALUE         0x0002  /* Minimum Value (Low Bound) */
#define ZBEE_ZCL_ATTR_ID_ILLUM_MEAS_MIN_HI_VALUE         0xfffd  /* Minimum Value (High Bound) */

#define ZBEE_ZCL_ATTR_ID_ILLUM_MEAS_MAX_LO_VALUE         0x0001  /* Maximum Value (Low Bound) */
#define ZBEE_ZCL_ATTR_ID_ILLUM_MEAS_MAX_HI_VALUE         0xfffe  /* Maximum Value (High Bound) */

#define ZBEE_ZCL_ATTR_ID_ILLUM_MEAS_TOL_LO_VALUE         0x0000  /* Tolerance (Low Bound) */
#define ZBEE_ZCL_ATTR_ID_ILLUM_MEAS_TOL_HI_VALUE         0x0800  /* Tolerance (Low Bound) */

#define ZBEE_ZCL_ILLUM_MEAS_SENSOR_TYPE_PHOTODIODE       0x00  /* Photodiode */
#define ZBEE_ZCL_ILLUM_MEAS_SENSOR_TYPE_CMOS             0x01  /* CMOS */

/*************************/
/* Function Declarations */
/*************************/

/* Command Dissector Helpers */

/* Private functions prototype */
static void dissect_zcl_illum_meas_attr_id       (proto_tree *tree, tvbuff_t *tvb, guint *offset, guint16 attr_id);
static void dissect_zcl_illum_meas_attr_data     (proto_tree *tree, tvbuff_t *tvb, guint *offset, guint16 attr_id, guint data_type);

static void decode_illum_meas_value              (gchar *s, guint16 value);
static void decode_illum_meas_min_value          (gchar *s, guint16 value);
static void decode_illum_meas_max_value          (gchar *s, guint16 value);
static void decode_illum_meas_tolerance          (gchar *s, guint16 value);

/*************************/
/* Global Variables      */
/*************************/

/* Initialize the protocol and registered fields */
static int proto_zbee_zcl_illum_meas = -1;

static int hf_zbee_zcl_illum_meas_attr_id = -1;
static int hf_zbee_zcl_illum_meas_measured_value = -1;
static int hf_zbee_zcl_illum_meas_min_measured_value = -1;
static int hf_zbee_zcl_illum_meas_max_measured_value = -1;
static int hf_zbee_zcl_illum_meas_tolerance = -1;
static int hf_zbee_zcl_illum_meas_sensor_type = -1;

/* Initialize the subtree pointers */
static gint ett_zbee_zcl_illum_meas = -1;

/* Attributes */
static const value_string zbee_zcl_illum_meas_attr_names[] = {
    { ZBEE_ZCL_ATTR_ID_ILLUM_MEAS_MEASURED_VALUE,       "Measured Value" },
    { ZBEE_ZCL_ATTR_ID_ILLUM_MEAS_MIN_MEASURED_VALUE,   "Min Measured Value" },
    { ZBEE_ZCL_ATTR_ID_ILLUM_MEAS_MAX_MEASURED_VALUE,   "Max Measured Value" },
    { ZBEE_ZCL_ATTR_ID_ILLUM_MEAS_TOLERANCE,            "Tolerance" },
    { ZBEE_ZCL_ATTR_ID_ILLUM_MEAS_LIGHT_SENSOR_TYPE,    "Light Sensor Type" },
    { 0, NULL }
};

static const value_string zbee_zcl_illum_meas_sensor_type_names[] = {
    { ZBEE_ZCL_ILLUM_MEAS_SENSOR_TYPE_PHOTODIODE,       "Photodiode" },
    { ZBEE_ZCL_ILLUM_MEAS_SENSOR_TYPE_CMOS,             "CMOS" },
    { 0, NULL }
};

/*************************/
/* Function Bodies       */
/*************************/

/*FUNCTION:------------------------------------------------------
 *  NAME
 *      dissect_zbee_zcl_illum_meas
 *  DESCRIPTION
 *      ZigBee ZCL Illuminance Measurement cluster dissector for wireshark.
 *  PARAMETERS
 *      tvbuff_t *tvb       - pointer to buffer containing raw packet.
 *      packet_info *pinfo  - pointer to packet information fields
 *      proto_tree *tree    - pointer to data tree Wireshark uses to display packet.
 *  RETURNS
 *      none
 *---------------------------------------------------------------
 */
static void
dissect_zbee_zcl_illum_meas(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_)
{
    return;
} /*dissect_zbee_zcl_illum_meas*/

/*FUNCTION:------------------------------------------------------
 *  NAME
 *      dissect_zcl_illum_meas_attr_id
 *  DESCRIPTION
 *      this function is called by ZCL foundation dissector in order to decode
 *      specific cluster attributes identifier.
 *  PARAMETERS
 *      proto_tree *tree    - pointer to data tree Wireshark uses to display packet.
 *      tvbuff_t *tvb       - pointer to buffer containing raw packet.
 *      guint *offset       - pointer to buffer offset
 *      guint16 attr_id     - attribute identifier
 *
 *  RETURNS
 *      none
 *---------------------------------------------------------------
 */
static void
dissect_zcl_illum_meas_attr_id(proto_tree *tree, tvbuff_t *tvb, guint *offset, guint16 attr_id)
{
    proto_tree_add_item(tree, hf_zbee_zcl_illum_meas_attr_id, tvb, *offset, 2, attr_id);
} /*dissect_zcl_illum_meas_attr_id*/

/*FUNCTION:------------------------------------------------------
 *  NAME
 *      dissect_zcl_illum_meas_attr_data
 *  DESCRIPTION
 *      this function is called by ZCL foundation dissector in order to decode
 *      specific cluster attributes data.
 *  PARAMETERS
 *      proto_tree *tree    - pointer to data tree Wireshark uses to display packet.
 *      tvbuff_t *tvb       - pointer to buffer containing raw packet.
 *      guint *offset       - pointer to buffer offset
 *      guint16 attr_id     - attribute identifier
 *      guint data_type     - attribute data type
 *  RETURNS
 *      none
 *---------------------------------------------------------------
 */
static void
dissect_zcl_illum_meas_attr_data(proto_tree *tree, tvbuff_t *tvb, guint *offset, guint16 attr_id, guint data_type)
{
    /* Dissect attribute data type and data */
    switch ( attr_id ) {

        case ZBEE_ZCL_ATTR_ID_ILLUM_MEAS_MEASURED_VALUE:
            proto_tree_add_item(tree, hf_zbee_zcl_illum_meas_measured_value, tvb, *offset, 2, ENC_LITTLE_ENDIAN);
            *offset += 2;
            break;

            case ZBEE_ZCL_ATTR_ID_ILLUM_MEAS_MIN_MEASURED_VALUE:
            proto_tree_add_item(tree, hf_zbee_zcl_illum_meas_min_measured_value, tvb, *offset, 2, ENC_LITTLE_ENDIAN);
            *offset += 2;
            break;

        case ZBEE_ZCL_ATTR_ID_ILLUM_MEAS_MAX_MEASURED_VALUE:
            proto_tree_add_item(tree, hf_zbee_zcl_illum_meas_max_measured_value, tvb, *offset, 2, ENC_LITTLE_ENDIAN);
            *offset += 2;
            break;

        case ZBEE_ZCL_ATTR_ID_ILLUM_MEAS_TOLERANCE:
            proto_tree_add_item(tree, hf_zbee_zcl_illum_meas_tolerance, tvb, *offset, 2, ENC_LITTLE_ENDIAN);
            *offset += 2;
            break;

        case ZBEE_ZCL_ATTR_ID_ILLUM_MEAS_LIGHT_SENSOR_TYPE:
            proto_tree_add_item(tree, hf_zbee_zcl_illum_meas_sensor_type, tvb, *offset, 1, ENC_NA);
            *offset += 1;
            break;

        default:
            dissect_zcl_attr_data(tvb, tree, offset, data_type);
            break;
    }

} /*dissect_zcl_illum_meas_attr_data*/

/*FUNCTION:------------------------------------------------------
 *  NAME
 *    decode_illum_meas_value
 *  DESCRIPTION
 *    this function decodes illuminance value
 *  PARAMETERS
 *      guint *s        - string to display
 *      guint16 value   - value to decode
 *  RETURNS
 *    none
 *---------------------------------------------------------------
 */
static void
decode_illum_meas_value(gchar *s, guint16 value)
{
    if (value == ZBEE_ZCL_ATTR_ID_ILLUM_MEAS_TOO_LOW_VALUE)
        g_snprintf(s, ITEM_LABEL_LENGTH, "Value too low to be measured");
    else if (value == ZBEE_ZCL_ATTR_ID_ILLUM_MEAS_INVALID_VALUE)
        g_snprintf(s, ITEM_LABEL_LENGTH, "Invalid value");
    else
        g_snprintf(s, ITEM_LABEL_LENGTH, "%d [lx]", value);

    return;
} /*decode_illum_meas_value*/

/*FUNCTION:------------------------------------------------------
 *  NAME
 *    decode_illum_meas_min_value
 *  DESCRIPTION
 *    this function decodes minimum illuminance value
 *  PARAMETERS
 *      guint *s        - string to display
 *      guint16 value   - value to decode
 *  RETURNS
 *    none
 *---------------------------------------------------------------
 */
static void
decode_illum_meas_min_value(gchar *s, guint16 value)
{
    if ( (value < ZBEE_ZCL_ATTR_ID_ILLUM_MEAS_MIN_LO_VALUE) ||
         (value > ZBEE_ZCL_ATTR_ID_ILLUM_MEAS_MIN_HI_VALUE) )
        g_snprintf(s, ITEM_LABEL_LENGTH, "Out of range");
    else
        g_snprintf(s, ITEM_LABEL_LENGTH, "%d [lx]", value);

    return;
} /*decode_illum_meas_min_value*/

/*FUNCTION:------------------------------------------------------
 *  NAME
 *    decode_illum_meas_max_value
 *  DESCRIPTION
 *    this function decodes maximum illuminance value
 *  PARAMETERS
 *      guint *s        - string to display
 *      guint16 value   - value to decode
 *  RETURNS
 *    none
 *---------------------------------------------------------------
 */
static void
decode_illum_meas_max_value(gchar *s, guint16 value)
{
    if ( (value < ZBEE_ZCL_ATTR_ID_ILLUM_MEAS_MAX_LO_VALUE) ||
         (value > ZBEE_ZCL_ATTR_ID_ILLUM_MEAS_MAX_HI_VALUE) )
        g_snprintf(s, ITEM_LABEL_LENGTH, "Out of range");
    else
        g_snprintf(s, ITEM_LABEL_LENGTH, "%d [lx]", value);

    return;
} /*decode_illum_meas_max_value*/

/*FUNCTION:------------------------------------------------------
 *  NAME
 *    decode_illum_meas_tolerance
 *  DESCRIPTION
 *    this function decodes tolerance value
 *  PARAMETERS
 *      guint *s        - string to display
 *      guint16 value   - value to decode
 *  RETURNS
 *    none
 *---------------------------------------------------------------
 */
static void
decode_illum_meas_tolerance(gchar *s, guint16 value)
{
    if (value > ZBEE_ZCL_ATTR_ID_ILLUM_MEAS_TOL_HI_VALUE)
        g_snprintf(s, ITEM_LABEL_LENGTH, "Out of range");
    else
        g_snprintf(s, ITEM_LABEL_LENGTH, "%d [lx]", value);

    return;
} /*decode_illum_meas_tolerance*/

/*FUNCTION:------------------------------------------------------
 *  NAME
 *      proto_register_zbee_zcl_illum_meas
 *  DESCRIPTION
 *      this function registers the ZCL Illuminance Measurement dissector
 *      and all its information.
 *  PARAMETERS
 *      none
 *  RETURNS
 *      none
 *---------------------------------------------------------------
 */
void
proto_register_zbee_zcl_illum_meas(void)
{
    static hf_register_info hf[] = {

        { &hf_zbee_zcl_illum_meas_attr_id,
            { "Attribute", "zbee_zcl_meas_sensing.illummeas.attr_id", FT_UINT16, BASE_HEX, VALS(zbee_zcl_illum_meas_attr_names),
            0x00, NULL, HFILL } },

        { &hf_zbee_zcl_illum_meas_measured_value,
            { "Measured Value", "zbee_zcl_meas_sensing.illummeas.attr.value", FT_UINT16, BASE_CUSTOM, decode_illum_meas_value,
            0x00, NULL, HFILL } },

        { &hf_zbee_zcl_illum_meas_min_measured_value,
            { "Min Measured Value", "zbee_zcl_meas_sensing.illummeas.attr.value.min", FT_UINT16, BASE_CUSTOM, decode_illum_meas_min_value,
            0x00, NULL, HFILL } },

        { &hf_zbee_zcl_illum_meas_max_measured_value,
            { "Max Measured Value", "zbee_zcl_meas_sensing.illummeas.attr.value.max", FT_UINT16, BASE_CUSTOM, decode_illum_meas_max_value,
            0x00, NULL, HFILL } },

        { &hf_zbee_zcl_illum_meas_tolerance,
            { "Tolerance", "zbee_zcl_meas_sensing.illummeas.attr.tolerance", FT_UINT16, BASE_CUSTOM, decode_illum_meas_tolerance,
            0x00, NULL, HFILL } },

        { &hf_zbee_zcl_illum_meas_sensor_type,
            { "Sensor Type", "zbee_zcl_meas_sensing.illummeas.attr.sensor_type", FT_UINT8, BASE_HEX, VALS(zbee_zcl_illum_meas_sensor_type_names),
            0x00, NULL, HFILL } }

    };

    /* Register the ZigBee ZCL Illuminance Measurement cluster protocol name and description */
    proto_zbee_zcl_illum_meas = proto_register_protocol("ZigBee ZCL Illuminance Meas.", "ZCL Illuminance Meas.", ZBEE_PROTOABBREV_ZCL_ILLUMMEAS);
    proto_register_field_array(proto_zbee_zcl_illum_meas, hf, array_length(hf));

    /* Register the ZigBee ZCL Illuminance Measurement dissector. */
    register_dissector(ZBEE_PROTOABBREV_ZCL_ILLUMMEAS, dissect_zbee_zcl_illum_meas, proto_zbee_zcl_illum_meas);

} /*proto_register_zbee_zcl_illum_meas*/


/*FUNCTION:------------------------------------------------------
 *  NAME
 *      proto_reg_handoff_zbee_zcl_illum_meas
 *  DESCRIPTION
 *      Hands off the ZCL Illuminance Measurement dissector.
 *  PARAMETERS
 *      none
 *  RETURNS
 *      none
 *---------------------------------------------------------------
 */
void
proto_reg_handoff_zbee_zcl_illum_meas(void)
{
    zbee_zcl_init_cluster(  proto_zbee_zcl_illum_meas,
                            ett_zbee_zcl_illum_meas,
                            ZBEE_ZCL_CID_ILLUMINANCE_MEASUREMENT,
                            (zbee_zcl_fn_attr_id)dissect_zcl_illum_meas_attr_id,
                            (zbee_zcl_fn_attr_data)dissect_zcl_illum_meas_attr_data
                         );
} /*proto_reg_handoff_zbee_zcl_illum_meas*/


/* ########################################################################## */
/* #### (0x0402) TEMPERATURE MEASUREMENT CLUSTER ############################ */
/* ########################################################################## */

/*************************/
/* Defines               */
/*************************/

#define ZBEE_ZCL_TEMP_MEAS_NUM_GENERIC_ETT              1
#define ZBEE_ZCL_TEMP_MEAS_NUM_ETT                      ZBEE_ZCL_TEMP_MEAS_NUM_GENERIC_ETT

/* Attributes */
#define ZBEE_ZCL_ATTR_ID_TEMP_MEAS_MEASURED_VALUE       0x0000  /* Measured Value */
#define ZBEE_ZCL_ATTR_ID_TEMP_MEAS_MIN_MEASURED_VALUE   0x0001  /* Min Measured Value */
#define ZBEE_ZCL_ATTR_ID_TEMP_MEAS_MAX_MEASURED_VALUE   0x0002  /* Max Measured Value */
#define ZBEE_ZCL_ATTR_ID_TEMP_MEAS_TOLERANCE            0x0003  /* Tolerance */

/* Server Commands Received - None */

/* Server Commands Generated - None */

#define ZBEE_ZCL_ATTR_ID_TEMP_MEAS_INVALID_VALUE        0x8000  /* Invalid Value */

#define ZBEE_ZCL_ATTR_ID_TEMP_MEAS_MIN_LO_VALUE         0x954d  /* Minimum Value (Low Bound) */
#define ZBEE_ZCL_ATTR_ID_TEMP_MEAS_MIN_HI_VALUE         0x7ffe  /* Minimum Value (High Bound) */

#define ZBEE_ZCL_ATTR_ID_TEMP_MEAS_MAX_LO_VALUE         0x954e  /* Maximum Value (Low Bound) */
#define ZBEE_ZCL_ATTR_ID_TEMP_MEAS_MAX_HI_VALUE         0x7fff  /* Maximum Value (High Bound) */

#define ZBEE_ZCL_ATTR_ID_TEMP_MEAS_TOL_LO_VALUE         0x0000  /* Tolerance (Low Bound) */
#define ZBEE_ZCL_ATTR_ID_TEMP_MEAS_TOL_HI_VALUE         0x0800  /* Tolerance (Low Bound) */


/*************************/
/* Function Declarations */
/*************************/

/* Command Dissector Helpers */

/* Private functions prototype */
static void dissect_zcl_temp_meas_attr_id       (proto_tree *tree, tvbuff_t *tvb, guint *offset, guint16 attr_id);
static void dissect_zcl_temp_meas_attr_data     (proto_tree *tree, tvbuff_t *tvb, guint *offset, guint16 attr_id, guint data_type);

static void decode_temp_meas_value              (gchar *s, gint16 value);
static void decode_temp_meas_min_value          (gchar *s, gint16 value);
static void decode_temp_meas_max_value          (gchar *s, gint16 value);
static void decode_temp_meas_tolerance          (gchar *s, guint16 value);

/*************************/
/* Global Variables      */
/*************************/

/* Initialize the protocol and registered fields */
static int proto_zbee_zcl_temp_meas = -1;

static int hf_zbee_zcl_temp_meas_attr_id = -1;
static int hf_zbee_zcl_temp_meas_measured_value = -1;
static int hf_zbee_zcl_temp_meas_min_measured_value = -1;
static int hf_zbee_zcl_temp_meas_max_measured_value = -1;
static int hf_zbee_zcl_temp_meas_tolerance = -1;

/* Initialize the subtree pointers */
static gint ett_zbee_zcl_temp_meas = -1;

/* Attributes */
static const value_string zbee_zcl_temp_meas_attr_names[] = {
    { ZBEE_ZCL_ATTR_ID_TEMP_MEAS_MEASURED_VALUE,        "Measured Value" },
    { ZBEE_ZCL_ATTR_ID_TEMP_MEAS_MIN_MEASURED_VALUE,    "Min Measured Value" },
    { ZBEE_ZCL_ATTR_ID_TEMP_MEAS_MAX_MEASURED_VALUE,    "Max Measured Value" },
    { ZBEE_ZCL_ATTR_ID_TEMP_MEAS_TOLERANCE,             "Tolerance" },
    { 0, NULL }
};

/*************************/
/* Function Bodies       */
/*************************/

/*FUNCTION:------------------------------------------------------
 *  NAME
 *      dissect_zbee_zcl_temp_meas
 *  DESCRIPTION
 *      ZigBee ZCL Temperature Measurement cluster dissector for wireshark.
 *  PARAMETERS
 *      tvbuff_t *tvb       - pointer to buffer containing raw packet.
 *      packet_info *pinfo  - pointer to packet information fields
 *      proto_tree *tree    - pointer to data tree Wireshark uses to display packet.
 *  RETURNS
 *      none
 *---------------------------------------------------------------
 */
static void
dissect_zbee_zcl_temp_meas(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_)
{
    return;
} /*dissect_zbee_zcl_temp_meas*/

/*FUNCTION:------------------------------------------------------
 *  NAME
 *      dissect_zcl_temp_meas_attr_id
 *  DESCRIPTION
 *      this function is called by ZCL foundation dissector in order to decode
 *      specific cluster attributes identifier.
 *  PARAMETERS
 *      proto_tree *tree    - pointer to data tree Wireshark uses to display packet.
 *      tvbuff_t *tvb       - pointer to buffer containing raw packet.
 *      guint *offset       - pointer to buffer offset
 *      guint16 attr_id     - attribute identifier
 *
 *  RETURNS
 *      none
 *---------------------------------------------------------------
 */
static void
dissect_zcl_temp_meas_attr_id(proto_tree *tree, tvbuff_t *tvb, guint *offset, guint16 attr_id)
{
    proto_tree_add_item(tree, hf_zbee_zcl_temp_meas_attr_id, tvb, *offset, 2, attr_id);
} /*dissect_zcl_temp_meas_attr_id*/

/*FUNCTION:------------------------------------------------------
 *  NAME
 *      dissect_zcl_temp_meas_attr_data
 *  DESCRIPTION
 *      this function is called by ZCL foundation dissector in order to decode
 *      specific cluster attributes data.
 *  PARAMETERS
 *      proto_tree *tree    - pointer to data tree Wireshark uses to display packet.
 *      tvbuff_t *tvb       - pointer to buffer containing raw packet.
 *      guint *offset       - pointer to buffer offset
 *      guint16 attr_id     - attribute identifier
 *      guint data_type     - attribute data type
 *  RETURNS
 *      none
 *---------------------------------------------------------------
 */
static void
dissect_zcl_temp_meas_attr_data(proto_tree *tree, tvbuff_t *tvb, guint *offset, guint16 attr_id, guint data_type)
{
    /* Dissect attribute data type and data */
    switch ( attr_id ) {

        case ZBEE_ZCL_ATTR_ID_TEMP_MEAS_MEASURED_VALUE:
            proto_tree_add_item(tree, hf_zbee_zcl_temp_meas_measured_value, tvb, *offset, 2, ENC_LITTLE_ENDIAN);
            *offset += 2;
            break;

            case ZBEE_ZCL_ATTR_ID_TEMP_MEAS_MIN_MEASURED_VALUE:
            proto_tree_add_item(tree, hf_zbee_zcl_temp_meas_min_measured_value, tvb, *offset, 2, ENC_LITTLE_ENDIAN);
            *offset += 2;
            break;

        case ZBEE_ZCL_ATTR_ID_TEMP_MEAS_MAX_MEASURED_VALUE:
            proto_tree_add_item(tree, hf_zbee_zcl_temp_meas_max_measured_value, tvb, *offset, 2, ENC_LITTLE_ENDIAN);
            *offset += 2;
            break;

        case ZBEE_ZCL_ATTR_ID_TEMP_MEAS_TOLERANCE:
            proto_tree_add_item(tree, hf_zbee_zcl_temp_meas_tolerance, tvb, *offset, 2, ENC_LITTLE_ENDIAN);
            *offset += 2;
            break;

        default:
            dissect_zcl_attr_data(tvb, tree, offset, data_type);
            break;
    }

} /*dissect_zcl_temp_meas_attr_data*/

/*FUNCTION:------------------------------------------------------
 *  NAME
 *    decode_temp_meas_value
 *  DESCRIPTION
 *    this function decodes temperature value
 *  PARAMETERS
 *      guint *s        - string to display
 *      guint16 value   - value to decode
 *  RETURNS
 *    none
 *---------------------------------------------------------------
 */
static void
decode_temp_meas_value(gchar *s, gint16 value)
{
    if (value == (gint16)ZBEE_ZCL_ATTR_ID_TEMP_MEAS_INVALID_VALUE)
        g_snprintf(s, ITEM_LABEL_LENGTH, "Invalid value");
    else
        g_snprintf(s, ITEM_LABEL_LENGTH, "%d.%d [\302\260C]", value/100, value%100);

    return;
} /*decode_temp_meas_value*/

/*FUNCTION:------------------------------------------------------
 *  NAME
 *    decode_temp_meas_min_value
 *  DESCRIPTION
 *    this function decodes minimum temperature value
 *  PARAMETERS
 *      guint *s        - string to display
 *      guint16 value   - value to decode
 *  RETURNS
 *    none
 *---------------------------------------------------------------
 */
static void
decode_temp_meas_min_value(gchar *s, gint16 value)
{
    if ( (value < (gint16)ZBEE_ZCL_ATTR_ID_TEMP_MEAS_MIN_LO_VALUE) ||
         (value > (gint16)ZBEE_ZCL_ATTR_ID_TEMP_MEAS_MIN_HI_VALUE) )
        g_snprintf(s, ITEM_LABEL_LENGTH, "Out of range");
    else
        g_snprintf(s, ITEM_LABEL_LENGTH, "%d.%d [\302\260C]", value/100, value%100);

    return;
} /*decode_temp_meas_min_value*/

/*FUNCTION:------------------------------------------------------
 *  NAME
 *    decode_temp_meas_max_value
 *  DESCRIPTION
 *    this function decodes maximum temperature value
 *  PARAMETERS
 *      guint *s        - string to display
 *      guint16 value   - value to decode
 *  RETURNS
 *    none
 *---------------------------------------------------------------
 */
static void
decode_temp_meas_max_value(gchar *s, gint16 value)
{
    if (value < (gint16)ZBEE_ZCL_ATTR_ID_TEMP_MEAS_MAX_LO_VALUE)
        g_snprintf(s, ITEM_LABEL_LENGTH, "Out of range");
    else
        g_snprintf(s, ITEM_LABEL_LENGTH, "%d.%d [\302\260C]", value/100, value%100);

    return;
} /*decode_temp_meas_max_value*/

/*FUNCTION:------------------------------------------------------
 *  NAME
 *    decode_temp_meas_tolerance
 *  DESCRIPTION
 *    this function decodes tolerance value
 *  PARAMETERS
 *      guint *s        - string to display
 *      guint16 value   - value to decode
 *  RETURNS
 *    none
 *---------------------------------------------------------------
 */
static void
decode_temp_meas_tolerance(gchar *s, guint16 value)
{
    if (value > ZBEE_ZCL_ATTR_ID_TEMP_MEAS_TOL_HI_VALUE)
        g_snprintf(s, ITEM_LABEL_LENGTH, "Out of range");
    else
        g_snprintf(s, ITEM_LABEL_LENGTH, "%d.%d [\302\260C]", value/100, value%100);

    return;
} /*decode_temp_meas_tolerance*/

/*FUNCTION:------------------------------------------------------
 *  NAME
 *      proto_register_zbee_zcl_temp_meas
 *  DESCRIPTION
 *      this function registers the ZCL Temperature Measurement dissector
 *      and all its information.
 *  PARAMETERS
 *      none
 *  RETURNS
 *      none
 *---------------------------------------------------------------
 */
void
proto_register_zbee_zcl_temp_meas(void)
{
    static hf_register_info hf[] = {

        { &hf_zbee_zcl_temp_meas_attr_id,
            { "Attribute", "zbee_zcl_meas_sensing.tempmeas.attr_idd", FT_UINT16, BASE_HEX, VALS(zbee_zcl_temp_meas_attr_names),
            0x00, NULL, HFILL } },

        { &hf_zbee_zcl_temp_meas_measured_value,
            { "Measured Value", "zbee_zcl_meas_sensing.tempmeas.attr.value", FT_INT16, BASE_CUSTOM, decode_temp_meas_value,
            0x00, NULL, HFILL } },

        { &hf_zbee_zcl_temp_meas_min_measured_value,
            { "Min Measured Value", "zbee_zcl_meas_sensing.tempmeas.attr.value.min", FT_INT16, BASE_CUSTOM, decode_temp_meas_min_value,
            0x00, NULL, HFILL } },

        { &hf_zbee_zcl_temp_meas_max_measured_value,
            { "Max Measured Value", "zbee_zcl_meas_sensing.tempmeas.attr.value.max", FT_INT16, BASE_CUSTOM, decode_temp_meas_max_value,
            0x00, NULL, HFILL } },

        { &hf_zbee_zcl_temp_meas_tolerance,
            { "Tolerance", "zbee_zcl_meas_sensing.tempmeas.attr.tolerance", FT_UINT16, BASE_CUSTOM, decode_temp_meas_tolerance,
            0x00, NULL, HFILL } }

    };

    /* Register the ZigBee ZCL Temperature Measurement cluster protocol name and description */
    proto_zbee_zcl_temp_meas = proto_register_protocol("ZigBee ZCL Temperature Meas.", "ZCL Temperature Meas.", ZBEE_PROTOABBREV_ZCL_TEMPMEAS);
    proto_register_field_array(proto_zbee_zcl_temp_meas, hf, array_length(hf));

    /* Register the ZigBee ZCL Temperature Measurement dissector. */
    register_dissector(ZBEE_PROTOABBREV_ZCL_TEMPMEAS, dissect_zbee_zcl_temp_meas, proto_zbee_zcl_temp_meas);

} /*proto_register_zbee_zcl_temp_meas*/


/*FUNCTION:------------------------------------------------------
 *  NAME
 *      proto_reg_handoff_zbee_zcl_temp_meas
 *  DESCRIPTION
 *      Hands off the ZCL Temperature Measurement dissector.
 *  PARAMETERS
 *      none
 *  RETURNS
 *      none
 *---------------------------------------------------------------
 */
void
proto_reg_handoff_zbee_zcl_temp_meas(void)
{
    zbee_zcl_init_cluster(  proto_zbee_zcl_temp_meas,
                            ett_zbee_zcl_temp_meas,
                            ZBEE_ZCL_CID_TEMPERATURE_MEASUREMENT,
                            (zbee_zcl_fn_attr_id)dissect_zcl_temp_meas_attr_id,
                            (zbee_zcl_fn_attr_data)dissect_zcl_temp_meas_attr_data
                         );
} /*proto_reg_handoff_zbee_zcl_temp_meas*/


/* ########################################################################## */
/* #### (0x0403) PRESSURE MEASUREMENT CLUSTER ############################### */
/* ########################################################################## */

/*************************/
/* Defines               */
/*************************/

#define ZBEE_ZCL_PRESS_MEAS_NUM_GENERIC_ETT              1
#define ZBEE_ZCL_PRESS_MEAS_NUM_ETT                      ZBEE_ZCL_PRESS_MEAS_NUM_GENERIC_ETT

/* Attributes */
#define ZBEE_ZCL_ATTR_ID_PRESS_MEAS_MEASURED_VALUE       0x0000  /* Measured Value */
#define ZBEE_ZCL_ATTR_ID_PRESS_MEAS_MIN_MEASURED_VALUE   0x0001  /* Min Measured Value */
#define ZBEE_ZCL_ATTR_ID_PRESS_MEAS_MAX_MEASURED_VALUE   0x0002  /* Max Measured Value */
#define ZBEE_ZCL_ATTR_ID_PRESS_MEAS_TOLERANCE            0x0003  /* Tolerance */
#define ZBEE_ZCL_ATTR_ID_PRESS_MEAS_SCALED_VALUE         0x0010  /* Scaled Value */
#define ZBEE_ZCL_ATTR_ID_PRESS_MEAS_MIN_SCALED_VALUE     0x0011  /* Min Scaled Value */
#define ZBEE_ZCL_ATTR_ID_PRESS_MEAS_MAX_SCALED_VALUE     0x0012  /* Max Scaled Value */
#define ZBEE_ZCL_ATTR_ID_PRESS_MEAS_SCALED_TOLERANCE     0x0013  /* Scaled Tolerance */
#define ZBEE_ZCL_ATTR_ID_PRESS_MEAS_SCALE                0x0014  /* Scale */

/* Server Commands Received - None */

/* Server Commands Generated - None */

#define ZBEE_ZCL_ATTR_ID_PRESS_MEAS_INVALID_VALUE        0x8000  /* Invalid Value */

#define ZBEE_ZCL_ATTR_ID_PRESS_MEAS_MIN_LO_VALUE         0x8001  /* Minimum Value (Low Bound) */
#define ZBEE_ZCL_ATTR_ID_PRESS_MEAS_MIN_HI_VALUE         0x7ffe  /* Minimum Value (High Bound) */

#define ZBEE_ZCL_ATTR_ID_PRESS_MEAS_MAX_LO_VALUE         0x8002  /* Maximum Value (Low Bound) */
#define ZBEE_ZCL_ATTR_ID_PRESS_MEAS_MAX_HI_VALUE         0x7fff  /* Maximum Value (High Bound) */

#define ZBEE_ZCL_ATTR_ID_PRESS_MEAS_TOL_LO_VALUE         0x0000  /* Tolerance (Low Bound) */
#define ZBEE_ZCL_ATTR_ID_PRESS_MEAS_TOL_HI_VALUE         0x0800  /* Tolerance (Low Bound) */

#define ZBEE_ZCL_ATTR_ID_PRESS_MEAS_SCALE_LO_VALUE       0x81  /* Scale (Low Bound) */
#define ZBEE_ZCL_ATTR_ID_PRESS_MEAS_SCALE_HI_VALUE       0x7f  /* Scale (Low Bound) */

/*************************/
/* Function Declarations */
/*************************/

/* Command Dissector Helpers */

/* Private functions prototype */
static void dissect_zcl_press_meas_attr_id       (proto_tree *tree, tvbuff_t *tvb, guint *offset, guint16 attr_id);
static void dissect_zcl_press_meas_attr_data     (proto_tree *tree, tvbuff_t *tvb, guint *offset, guint16 attr_id, guint data_type);

static void decode_press_meas_value              (gchar *s, gint16 value);
static void decode_press_meas_min_value          (gchar *s, gint16 value);
static void decode_press_meas_max_value          (gchar *s, gint16 value);
static void decode_press_meas_tolerance          (gchar *s, guint16 value);

/*************************/
/* Global Variables      */
/*************************/

/* Initialize the protocol and registered fields */
static int proto_zbee_zcl_press_meas = -1;

static int hf_zbee_zcl_press_meas_attr_id = -1;
static int hf_zbee_zcl_press_meas_measured_value = -1;
static int hf_zbee_zcl_press_meas_min_measured_value = -1;
static int hf_zbee_zcl_press_meas_max_measured_value = -1;
static int hf_zbee_zcl_press_meas_tolerance = -1;
static int hf_zbee_zcl_press_meas_scaled_value = -1;
static int hf_zbee_zcl_press_meas_min_scaled_value = -1;
static int hf_zbee_zcl_press_meas_max_scaled_value = -1;
static int hf_zbee_zcl_press_meas_scaled_tolerance = -1;
static int hf_zbee_zcl_press_meas_scale = -1;

/* Initialize the subtree pointers */
static gint ett_zbee_zcl_press_meas = -1;

/* Attributes */
static const value_string zbee_zcl_press_meas_attr_names[] = {
    { ZBEE_ZCL_ATTR_ID_PRESS_MEAS_MEASURED_VALUE,       "Measured Value" },
    { ZBEE_ZCL_ATTR_ID_PRESS_MEAS_MIN_MEASURED_VALUE,   "Min Measured Value" },
    { ZBEE_ZCL_ATTR_ID_PRESS_MEAS_MAX_MEASURED_VALUE,   "Max Measured Value" },
    { ZBEE_ZCL_ATTR_ID_PRESS_MEAS_TOLERANCE,            "Tolerance" },
    { ZBEE_ZCL_ATTR_ID_PRESS_MEAS_SCALED_VALUE,         "Scaled Value" },
    { ZBEE_ZCL_ATTR_ID_PRESS_MEAS_MIN_SCALED_VALUE,     "Min Scaled Value" },
    { ZBEE_ZCL_ATTR_ID_PRESS_MEAS_MAX_SCALED_VALUE,     "Max Scaled Value" },
    { ZBEE_ZCL_ATTR_ID_PRESS_MEAS_SCALED_TOLERANCE,     "Scaled Tolerance" },
    { ZBEE_ZCL_ATTR_ID_PRESS_MEAS_SCALE,                "Scale" },
    { 0, NULL }
};

/*************************/
/* Function Bodies       */
/*************************/

/*FUNCTION:------------------------------------------------------
 *  NAME
 *      dissect_zbee_zcl_press_meas
 *  DESCRIPTION
 *      ZigBee ZCL Pressure Measurement cluster dissector for wireshark.
 *  PARAMETERS
 *      tvbuff_t *tvb       - pointer to buffer containing raw packet.
 *      packet_info *pinfo  - pointer to packet information fields
 *      proto_tree *tree    - pointer to data tree Wireshark uses to display packet.
 *  RETURNS
 *      none
 *---------------------------------------------------------------
 */
static void
dissect_zbee_zcl_press_meas(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_)
{
    return;
} /*dissect_zbee_zcl_press_meas*/

/*FUNCTION:------------------------------------------------------
 *  NAME
 *      dissect_zcl_press_meas_attr_id
 *  DESCRIPTION
 *      this function is called by ZCL foundation dissector in order to decode
 *      specific cluster attributes identifier.
 *  PARAMETERS
 *      proto_tree *tree    - pointer to data tree Wireshark uses to display packet.
 *      tvbuff_t *tvb       - pointer to buffer containing raw packet.
 *      guint *offset       - pointer to buffer offset
 *      guint16 attr_id     - attribute identifier
 *
 *  RETURNS
 *      none
 *---------------------------------------------------------------
 */
static void
dissect_zcl_press_meas_attr_id(proto_tree *tree, tvbuff_t *tvb, guint *offset, guint16 attr_id)
{
    proto_tree_add_item(tree, hf_zbee_zcl_press_meas_attr_id, tvb, *offset, 2, attr_id);
} /*dissect_zcl_press_meas_attr_id*/

/*FUNCTION:------------------------------------------------------
 *  NAME
 *      dissect_zcl_press_meas_attr_data
 *  DESCRIPTION
 *      this function is called by ZCL foundation dissector in order to decode
 *      specific cluster attributes data.
 *  PARAMETERS
 *      proto_tree *tree    - pointer to data tree Wireshark uses to display packet.
 *      tvbuff_t *tvb       - pointer to buffer containing raw packet.
 *      guint *offset       - pointer to buffer offset
 *      guint16 attr_id     - attribute identifier
 *      guint data_type     - attribute data type
 *  RETURNS
 *      none
 *---------------------------------------------------------------
 */
static void
dissect_zcl_press_meas_attr_data(proto_tree *tree, tvbuff_t *tvb, guint *offset, guint16 attr_id, guint data_type)
{
    /* Dissect attribute data type and data */
    switch ( attr_id ) {

        case ZBEE_ZCL_ATTR_ID_PRESS_MEAS_MEASURED_VALUE:
            proto_tree_add_item(tree, hf_zbee_zcl_press_meas_measured_value, tvb, *offset, 2, ENC_LITTLE_ENDIAN);
            *offset += 2;
            break;

        case ZBEE_ZCL_ATTR_ID_PRESS_MEAS_MIN_MEASURED_VALUE:
            proto_tree_add_item(tree, hf_zbee_zcl_press_meas_min_measured_value, tvb, *offset, 2, ENC_LITTLE_ENDIAN);
            *offset += 2;
            break;

        case ZBEE_ZCL_ATTR_ID_PRESS_MEAS_MAX_MEASURED_VALUE:
            proto_tree_add_item(tree, hf_zbee_zcl_press_meas_max_measured_value, tvb, *offset, 2, ENC_LITTLE_ENDIAN);
            *offset += 2;
            break;

        case ZBEE_ZCL_ATTR_ID_PRESS_MEAS_TOLERANCE:
            proto_tree_add_item(tree, hf_zbee_zcl_press_meas_tolerance, tvb, *offset, 2, ENC_LITTLE_ENDIAN);
            *offset += 2;
            break;

        case ZBEE_ZCL_ATTR_ID_PRESS_MEAS_SCALED_VALUE:
            proto_tree_add_item(tree, hf_zbee_zcl_press_meas_scaled_value, tvb, *offset, 2, ENC_LITTLE_ENDIAN);
            *offset += 2;
            break;

        case ZBEE_ZCL_ATTR_ID_PRESS_MEAS_MIN_SCALED_VALUE:
            proto_tree_add_item(tree, hf_zbee_zcl_press_meas_min_scaled_value, tvb, *offset, 2, ENC_LITTLE_ENDIAN);
            *offset += 2;
            break;

        case ZBEE_ZCL_ATTR_ID_PRESS_MEAS_MAX_SCALED_VALUE:
            proto_tree_add_item(tree, hf_zbee_zcl_press_meas_max_scaled_value, tvb, *offset, 2, ENC_LITTLE_ENDIAN);
            *offset += 2;
            break;

        case ZBEE_ZCL_ATTR_ID_PRESS_MEAS_SCALED_TOLERANCE:
            proto_tree_add_item(tree, hf_zbee_zcl_press_meas_scaled_tolerance, tvb, *offset, 2, ENC_LITTLE_ENDIAN);
            *offset += 2;
            break;

        case ZBEE_ZCL_ATTR_ID_PRESS_MEAS_SCALE:
            proto_tree_add_item(tree, hf_zbee_zcl_press_meas_scale, tvb, *offset, 1, ENC_NA);
            *offset += 1;
            break;

        default:
            dissect_zcl_attr_data(tvb, tree, offset, data_type);
            break;
    }

} /*dissect_zcl_press_meas_attr_data*/


/*FUNCTION:------------------------------------------------------
 *  NAME
 *    decode_press_meas_value
 *  DESCRIPTION
 *    this function decodes pressure value
 *  PARAMETERS
 *      guint *s        - string to display
 *      guint16 value   - value to decode
 *  RETURNS
 *    none
 *---------------------------------------------------------------
 */
static void
decode_press_meas_value(gchar *s, gint16 value)
{
    if (value == (gint16)ZBEE_ZCL_ATTR_ID_PRESS_MEAS_INVALID_VALUE)
        g_snprintf(s, ITEM_LABEL_LENGTH, "Invalid value");
    if (value < (gint16)ZBEE_ZCL_ATTR_ID_PRESS_MEAS_MIN_LO_VALUE)
        g_snprintf(s, ITEM_LABEL_LENGTH, "Out of range");
    else
        g_snprintf(s, ITEM_LABEL_LENGTH, "%d.%d [kPa]", value/10, value%10);

    return;
} /*decode_press_meas_value*/

/*FUNCTION:------------------------------------------------------
 *  NAME
 *    decode_press_meas_min_value
 *  DESCRIPTION
 *    this function decodes minimum pressure value
 *  PARAMETERS
 *      guint *s        - string to display
 *      guint16 value   - value to decode
 *  RETURNS
 *    none
 *---------------------------------------------------------------
 */
static void
decode_press_meas_min_value(gchar *s, gint16 value)
{
    if (value > (gint16)ZBEE_ZCL_ATTR_ID_PRESS_MEAS_MIN_HI_VALUE)
        g_snprintf(s, ITEM_LABEL_LENGTH, "Out of range");
    else
        g_snprintf(s, ITEM_LABEL_LENGTH, "%d.%d [kPa]", value/10, value%10);

    return;
} /*decode_press_meas_min_value*/

/*FUNCTION:------------------------------------------------------
 *  NAME
 *    decode_press_meas_max_value
 *  DESCRIPTION
 *    this function decodes maximum pressure value
 *  PARAMETERS
 *      guint *s        - string to display
 *      guint16 value   - value to decode
 *  RETURNS
 *    none
 *---------------------------------------------------------------
 */
static void
decode_press_meas_max_value(gchar *s, gint16 value)
{
    if (value < (gint16)ZBEE_ZCL_ATTR_ID_PRESS_MEAS_MAX_LO_VALUE)
        g_snprintf(s, ITEM_LABEL_LENGTH, "Out of range");
    else
        g_snprintf(s, ITEM_LABEL_LENGTH, "%d.%d [kPa]", value/10, value%10);

    return;
} /*decode_press_meas_max_value*/

/*FUNCTION:------------------------------------------------------
 *  NAME
 *    decode_press_meas_tolerance
 *  DESCRIPTION
 *    this function decodes tolerance value
 *  PARAMETERS
 *      guint *s        - string to display
 *      guint16 value   - value to decode
 *  RETURNS
 *    none
 *---------------------------------------------------------------
 */
static void
decode_press_meas_tolerance(gchar *s, guint16 value)
{
    if (value > (guint16)ZBEE_ZCL_ATTR_ID_PRESS_MEAS_TOL_HI_VALUE)
        g_snprintf(s, ITEM_LABEL_LENGTH, "Out of range");
    else
         g_snprintf(s, ITEM_LABEL_LENGTH, "%d.%d [kPa]", value/10, value%10);

    return;
} /*decode_press_meas_tolerance*/

/*FUNCTION:------------------------------------------------------
 *  NAME
 *      proto_register_zbee_zcl_press_meas
 *  DESCRIPTION
 *      this function registers the ZCL Pressure Measurement dissector
 *      and all its information.
 *  PARAMETERS
 *      none
 *  RETURNS
 *      none
 *---------------------------------------------------------------
 */
void
proto_register_zbee_zcl_press_meas(void)
{
    static hf_register_info hf[] = {

        { &hf_zbee_zcl_press_meas_attr_id,
            { "Attribute", "zbee_zcl_meas_sensing.pressmeas.attr_id", FT_UINT16, BASE_HEX, VALS(zbee_zcl_press_meas_attr_names),
            0x00, NULL, HFILL } },

        { &hf_zbee_zcl_press_meas_measured_value,
            { "Measured Value", "zbee_zcl_meas_sensing.pressmeas.attr.value", FT_INT16, BASE_CUSTOM, decode_press_meas_value,
            0x00, NULL, HFILL } },

        { &hf_zbee_zcl_press_meas_min_measured_value,
            { "Min Measured Value", "zbee_zcl_meas_sensing.pressmeas.attr.value.min", FT_INT16, BASE_CUSTOM, decode_press_meas_min_value,
            0x00, NULL, HFILL } },

        { &hf_zbee_zcl_press_meas_max_measured_value,
            { "Max Measured Value", "zbee_zcl_meas_sensing.pressmeas.attr.value.max", FT_INT16, BASE_CUSTOM, decode_press_meas_max_value,
            0x00, NULL, HFILL } },

        { &hf_zbee_zcl_press_meas_tolerance,
            { "Tolerance", "zbee_zcl_meas_sensing.pressmeas.attr.tolerance", FT_UINT16, BASE_CUSTOM, decode_press_meas_tolerance,
            0x00, NULL, HFILL } },

        { &hf_zbee_zcl_press_meas_scaled_value,
            { "Scaled Value", "zbee_zcl_meas_sensing.pressmeas.attr.scaled_value", FT_INT16, BASE_DEC, NULL,
            0x00, NULL, HFILL } },

        { &hf_zbee_zcl_press_meas_min_scaled_value,
            { "Min Scaled Value", "zbee_zcl_meas_sensing.pressmeas.attr.scaled_value.min", FT_INT16, BASE_DEC, NULL,
            0x00, NULL, HFILL } },

        { &hf_zbee_zcl_press_meas_max_scaled_value,
            { "Max Scaled Value", "zbee_zcl_meas_sensing.pressmeas.attr.scaled_value.max", FT_INT16, BASE_DEC, NULL,
            0x00, NULL, HFILL } },

        { &hf_zbee_zcl_press_meas_scaled_tolerance,
            { "Scaled Tolerance", "zbee_zcl_meas_sensing.pressmeas.attr.scaled_tolerance", FT_UINT16, BASE_DEC, NULL,
            0x00, NULL, HFILL } },

        { &hf_zbee_zcl_press_meas_scale,
            { "Scale", "zbee_zcl_meas_sensing.pressmeas.attr.scale", FT_UINT8, BASE_DEC, NULL,
            0x00, NULL, HFILL } }

    };

    /* Register the ZigBee ZCL Pressure Measurement cluster protocol name and description */
    proto_zbee_zcl_press_meas = proto_register_protocol("ZigBee ZCL Pressure Meas.", "ZCL Pressure Meas.", ZBEE_PROTOABBREV_ZCL_PRESSMEAS);
    proto_register_field_array(proto_zbee_zcl_press_meas, hf, array_length(hf));

    /* Register the ZigBee ZCL Pressure Measurement dissector. */
    register_dissector(ZBEE_PROTOABBREV_ZCL_PRESSMEAS, dissect_zbee_zcl_press_meas, proto_zbee_zcl_press_meas);

} /*proto_register_zbee_zcl_press_meas*/


/*FUNCTION:------------------------------------------------------
 *  NAME
 *      proto_reg_handoff_zbee_zcl_press_meas
 *  DESCRIPTION
 *      Hands off the ZCL Pressure Measurement dissector.
 *  PARAMETERS
 *      none
 *  RETURNS
 *      none
 *---------------------------------------------------------------
 */
void
proto_reg_handoff_zbee_zcl_press_meas(void)
{
    zbee_zcl_init_cluster(  proto_zbee_zcl_press_meas,
                            ett_zbee_zcl_press_meas,
                            ZBEE_ZCL_CID_PRESSURE_MEASUREMENT,
                            (zbee_zcl_fn_attr_id)dissect_zcl_press_meas_attr_id,
                            (zbee_zcl_fn_attr_data)dissect_zcl_press_meas_attr_data
                         );
} /*proto_reg_handoff_zbee_zcl_press_meas*/


/* ########################################################################## */
/* #### (0x0405) RELATIVE HUMIDITY MEASUREMENT CLUSTER ###################### */
/* ########################################################################## */


/*************************/
/* Defines               */
/*************************/

#define ZBEE_ZCL_RELHUM_MEAS_NUM_GENERIC_ETT              1
#define ZBEE_ZCL_RELHUM_MEAS_NUM_ETT                      ZBEE_ZCL_RELHUM_MEAS_NUM_GENERIC_ETT

/* Attributes */
#define ZBEE_ZCL_ATTR_ID_RELHUM_MEAS_MEASURED_VALUE       0x0000  /* Measured Value */
#define ZBEE_ZCL_ATTR_ID_RELHUM_MEAS_MIN_MEASURED_VALUE   0x0001  /* Min Measured Value */
#define ZBEE_ZCL_ATTR_ID_RELHUM_MEAS_MAX_MEASURED_VALUE   0x0002  /* Max Measured Value */
#define ZBEE_ZCL_ATTR_ID_RELHUM_MEAS_TOLERANCE            0x0003  /* Tolerance */

/* Server Commands Received - None */

/* Server Commands Generated - None */

#define ZBEE_ZCL_ATTR_ID_RELHUM_MEAS_INVALID_VALUE        0xffff  /* Invalid Value */

#define ZBEE_ZCL_ATTR_ID_RELHUM_MEAS_MIN_LO_VALUE         0x0000  /* Minimum Value (Low Bound) */
#define ZBEE_ZCL_ATTR_ID_RELHUM_MEAS_MIN_HI_VALUE         0x270f  /* Minimum Value (High Bound) */

#define ZBEE_ZCL_ATTR_ID_RELHUM_MEAS_MAX_LO_VALUE         0x0000  /* Maximum Value (Low Bound) */
#define ZBEE_ZCL_ATTR_ID_RELHUM_MEAS_MAX_HI_VALUE         0x2710  /* Maximum Value (High Bound) */

#define ZBEE_ZCL_ATTR_ID_RELHUM_MEAS_TOL_LO_VALUE         0x0000  /* Tolerance (Low Bound) */
#define ZBEE_ZCL_ATTR_ID_RELHUM_MEAS_TOL_HI_VALUE         0x0800  /* Tolerance (Low Bound) */


/*************************/
/* Function Declarations */
/*************************/

/* Command Dissector Helpers */

/* Private functions prototype */
static void dissect_zcl_relhum_meas_attr_id       (proto_tree *tree, tvbuff_t *tvb, guint *offset, guint16 attr_id);
static void dissect_zcl_relhum_meas_attr_data     (proto_tree *tree, tvbuff_t *tvb, guint *offset, guint16 attr_id, guint data_type);

static void decode_relhum_meas_value              (gchar *s, guint16 value);
static void decode_relhum_meas_min_value          (gchar *s, guint16 value);
static void decode_relhum_meas_max_value          (gchar *s, guint16 value);
static void decode_relhum_meas_tolerance          (gchar *s, guint16 value);

/*************************/
/* Global Variables      */
/*************************/

/* Initialize the protocol and registered fields */
static int proto_zbee_zcl_relhum_meas = -1;

static int hf_zbee_zcl_relhum_meas_attr_id = -1;
static int hf_zbee_zcl_relhum_meas_measured_value = -1;
static int hf_zbee_zcl_relhum_meas_min_measured_value = -1;
static int hf_zbee_zcl_relhum_meas_max_measured_value = -1;
static int hf_zbee_zcl_relhum_meas_tolerance = -1;

/* Initialize the subtree pointers */
static gint ett_zbee_zcl_relhum_meas = -1;

/* Attributes */
static const value_string zbee_zcl_relhum_meas_attr_names[] = {
    { ZBEE_ZCL_ATTR_ID_RELHUM_MEAS_MEASURED_VALUE,        "Measured Value" },
    { ZBEE_ZCL_ATTR_ID_RELHUM_MEAS_MIN_MEASURED_VALUE,    "Min Measured Value" },
    { ZBEE_ZCL_ATTR_ID_RELHUM_MEAS_MAX_MEASURED_VALUE,    "Max Measured Value" },
    { ZBEE_ZCL_ATTR_ID_RELHUM_MEAS_TOLERANCE,             "Tolerance" },
    { 0, NULL }
};

/*************************/
/* Function Bodies       */
/*************************/

/*FUNCTION:------------------------------------------------------
 *  NAME
 *      dissect_zbee_zcl_relhum_meas
 *  DESCRIPTION
 *      ZigBee ZCL Relative Humidity Measurement cluster dissector for wireshark.
 *  PARAMETERS
 *      tvbuff_t *tvb       - pointer to buffer containing raw packet.
 *      packet_info *pinfo  - pointer to packet information fields
 *      proto_tree *tree    - pointer to data tree Wireshark uses to display packet.
 *  RETURNS
 *      none
 *---------------------------------------------------------------
 */
static void
dissect_zbee_zcl_relhum_meas(tvbuff_t *tvb _U_, packet_info *pinfo _U_, proto_tree *tree _U_)
{
    return;
} /*dissect_zbee_zcl_relhum_meas*/

/*FUNCTION:------------------------------------------------------
 *  NAME
 *      dissect_zcl_relhum_meas_attr_id
 *  DESCRIPTION
 *      this function is called by ZCL foundation dissector in order to decode
 *      specific cluster attributes identifier.
 *  PARAMETERS
 *      proto_tree *tree    - pointer to data tree Wireshark uses to display packet.
 *      tvbuff_t *tvb       - pointer to buffer containing raw packet.
 *      guint *offset       - pointer to buffer offset
 *      guint16 attr_id     - attribute identifier
 *
 *  RETURNS
 *      none
 *---------------------------------------------------------------
 */
static void
dissect_zcl_relhum_meas_attr_id(proto_tree *tree, tvbuff_t *tvb, guint *offset, guint16 attr_id)
{
    proto_tree_add_item(tree, hf_zbee_zcl_relhum_meas_attr_id, tvb, *offset, 2, attr_id);
} /*dissect_zcl_relhum_meas_attr_id*/

/*FUNCTION:------------------------------------------------------
 *  NAME
 *      dissect_zcl_relhum_meas_attr_data
 *  DESCRIPTION
 *      this function is called by ZCL foundation dissector in order to decode
 *      specific cluster attributes data.
 *  PARAMETERS
 *      proto_tree *tree    - pointer to data tree Wireshark uses to display packet.
 *      tvbuff_t *tvb       - pointer to buffer containing raw packet.
 *      guint *offset       - pointer to buffer offset
 *      guint16 attr_id     - attribute identifier
 *      guint data_type     - attribute data type
 *  RETURNS
 *      none
 *---------------------------------------------------------------
 */
static void
dissect_zcl_relhum_meas_attr_data(proto_tree *tree, tvbuff_t *tvb, guint *offset, guint16 attr_id, guint data_type)
{
    /* Dissect attribute data type and data */
    switch ( attr_id ) {

        case ZBEE_ZCL_ATTR_ID_RELHUM_MEAS_MEASURED_VALUE:
            proto_tree_add_item(tree, hf_zbee_zcl_relhum_meas_measured_value, tvb, *offset, 2, ENC_LITTLE_ENDIAN);
            *offset += 2;
            break;

            case ZBEE_ZCL_ATTR_ID_RELHUM_MEAS_MIN_MEASURED_VALUE:
            proto_tree_add_item(tree, hf_zbee_zcl_relhum_meas_min_measured_value, tvb, *offset, 2, ENC_LITTLE_ENDIAN);
            *offset += 2;
            break;

        case ZBEE_ZCL_ATTR_ID_RELHUM_MEAS_MAX_MEASURED_VALUE:
            proto_tree_add_item(tree, hf_zbee_zcl_relhum_meas_max_measured_value, tvb, *offset, 2, ENC_LITTLE_ENDIAN);
            *offset += 2;
            break;

        case ZBEE_ZCL_ATTR_ID_RELHUM_MEAS_TOLERANCE:
            proto_tree_add_item(tree, hf_zbee_zcl_relhum_meas_tolerance, tvb, *offset, 2, ENC_LITTLE_ENDIAN);
            *offset += 2;
            break;

        default:
            dissect_zcl_attr_data(tvb, tree, offset, data_type);
            break;
    }

} /*dissect_zcl_relhum_meas_attr_data*/


/*FUNCTION:------------------------------------------------------
 *  NAME
 *    decode_relhum_meas_value
 *  DESCRIPTION
 *    this function decodes relative humidity value
 *  PARAMETERS
 *      guint *s        - string to display
 *      guint16 value   - value to decode
 *  RETURNS
 *    none
 *---------------------------------------------------------------
 */
static void
decode_relhum_meas_value(gchar *s, guint16 value)
{
    if (value == ZBEE_ZCL_ATTR_ID_RELHUM_MEAS_INVALID_VALUE)
        g_snprintf(s, ITEM_LABEL_LENGTH, "Invalid value");
    else
        g_snprintf(s, ITEM_LABEL_LENGTH, "%d.%d [%c]", value/100, value%100, '%');

    return;
} /*decode_relhum_meas_value*/

/*FUNCTION:------------------------------------------------------
 *  NAME
 *    decode_relhum_meas_min_value
 *  DESCRIPTION
 *    this function decodes minimum relative humidity value
 *  PARAMETERS
 *      guint *s        - string to display
 *      guint16 value   - value to decode
 *  RETURNS
 *    none
 *---------------------------------------------------------------
 */
static void
decode_relhum_meas_min_value(gchar *s, guint16 value)
{
    if (value > ZBEE_ZCL_ATTR_ID_RELHUM_MEAS_MIN_HI_VALUE)
        g_snprintf(s, ITEM_LABEL_LENGTH, "Out of range");
    else
        g_snprintf(s, ITEM_LABEL_LENGTH, "%d.%d [%c]", value/100, value%100, '%');

    return;
} /*decode_relhum_meas_min_value*/

/*FUNCTION:------------------------------------------------------
 *  NAME
 *    decode_relhum_meas_max_value
 *  DESCRIPTION
 *    this function decodes maximum relative humidity value
 *  PARAMETERS
 *      guint *s        - string to display
 *      guint16 value   - value to decode
 *  RETURNS
 *    none
 *---------------------------------------------------------------
 */
static void
decode_relhum_meas_max_value(gchar *s, guint16 value)
{
    if (value > ZBEE_ZCL_ATTR_ID_RELHUM_MEAS_MAX_HI_VALUE)
        g_snprintf(s, ITEM_LABEL_LENGTH, "Out of range");
    else
        g_snprintf(s, ITEM_LABEL_LENGTH, "%d.%d [%c]", value/100, value%100, '%');

    return;
} /*decode_relhum_meas_max_value*/

/*FUNCTION:------------------------------------------------------
 *  NAME
 *    decode_relhum_meas_tolerance
 *  DESCRIPTION
 *    this function decodes tolerance value
 *  PARAMETERS
 *      guint *s        - string to display
 *      guint16 value   - value to decode
 *  RETURNS
 *    none
 *---------------------------------------------------------------
 */
static void
decode_relhum_meas_tolerance(gchar *s, guint16 value)
{
    if (value > ZBEE_ZCL_ATTR_ID_RELHUM_MEAS_TOL_HI_VALUE)
        g_snprintf(s, ITEM_LABEL_LENGTH, "Out of range");
    else
        g_snprintf(s, ITEM_LABEL_LENGTH, "%d.%d [%c]", value/100, value%100, '%');

    return;
} /*decode_relhum_meas_tolerance*/

/*FUNCTION:------------------------------------------------------
 *  NAME
 *      proto_register_zbee_zcl_relhum_meas
 *  DESCRIPTION
 *      this function registers the ZCL Relative Humidity Measurement dissector
 *      and all its information.
 *  PARAMETERS
 *      none
 *  RETURNS
 *      none
 *---------------------------------------------------------------
 */
void
proto_register_zbee_zcl_relhum_meas(void)
{
    static hf_register_info hf[] = {

        { &hf_zbee_zcl_relhum_meas_attr_id,
            { "Attribute", "zbee_zcl_meas_sensing.relhummeas.attr_id", FT_UINT16, BASE_HEX, VALS(zbee_zcl_relhum_meas_attr_names),
            0x00, NULL, HFILL } },

        { &hf_zbee_zcl_relhum_meas_measured_value,
            { "Measured Value", "zbee_zcl_meas_sensing.relhummeas.attr.value", FT_UINT16, BASE_CUSTOM, decode_relhum_meas_value,
            0x00, NULL, HFILL } },

        { &hf_zbee_zcl_relhum_meas_min_measured_value,
            { "Min Measured Value", "zbee_zcl_meas_sensing.relhummeas.attr.value.min", FT_UINT16, BASE_CUSTOM, decode_relhum_meas_min_value,
            0x00, NULL, HFILL } },

        { &hf_zbee_zcl_relhum_meas_max_measured_value,
            { "Max Measured Value", "zbee_zcl_meas_sensing.relhummeas.attr.value.max", FT_UINT16, BASE_CUSTOM, decode_relhum_meas_max_value,
            0x00, NULL, HFILL } },

        { &hf_zbee_zcl_relhum_meas_tolerance,
            { "Tolerance", "zbee_zcl_meas_sensing.relhummeas.attr.tolerance", FT_UINT16, BASE_CUSTOM, decode_relhum_meas_tolerance,
            0x00, NULL, HFILL } }

    };

    /* Register the ZigBee ZCL Relative Humidity Measurement cluster protocol name and description */
    proto_zbee_zcl_relhum_meas = proto_register_protocol("ZigBee ZCL Rel. Humidity Meas.", "ZCL Relative Humidity Meas.", ZBEE_PROTOABBREV_ZCL_RELHUMMEAS);
    proto_register_field_array(proto_zbee_zcl_relhum_meas, hf, array_length(hf));

    /* Register the ZigBee ZCL Relative Humidity Measurement dissector. */
    register_dissector(ZBEE_PROTOABBREV_ZCL_RELHUMMEAS, dissect_zbee_zcl_relhum_meas, proto_zbee_zcl_relhum_meas);

} /*proto_register_zbee_zcl_relhum_meas*/


/*FUNCTION:------------------------------------------------------
 *  NAME
 *      proto_reg_handoff_zbee_zcl_relhum_meas
 *  DESCRIPTION
 *      Hands off the ZCL Relative Humidity Measurement dissector.
 *  PARAMETERS
 *      none
 *  RETURNS
 *      none
 *---------------------------------------------------------------
 */
void
proto_reg_handoff_zbee_zcl_relhum_meas(void)
{
    zbee_zcl_init_cluster(  proto_zbee_zcl_relhum_meas,
                            ett_zbee_zcl_relhum_meas,
                            ZBEE_ZCL_CID_REL_HUMIDITY_MEASUREMENT,
                            (zbee_zcl_fn_attr_id)dissect_zcl_relhum_meas_attr_id,
                            (zbee_zcl_fn_attr_data)dissect_zcl_relhum_meas_attr_data
                         );
} /*proto_reg_handoff_zbee_zcl_relhum_meas*/
