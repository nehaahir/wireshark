/* packet-bthci-cmd.c
 * Routines for the Bluetooth HCI Command dissection
 * Copyright 2002, Christoph Scholz <scholz@cs.uni-bonn.de>
 *  From: http://affix.sourceforge.net/archive/ethereal_affix-3.patch
 *
 * Refactored for wireshark checkin
 *   Ronnie Sahlberg 2006
 *
 * Updated to HCI specification 2.1 + EDR
 *   Allan M. Madsen 2007
 * Updated to HCI specification 3.0+HS & 4.0
 *   Allan M. Madsen 2012
 *
 * $Id: packet-bthci_cmd.c 53051 2013-11-02 19:20:04Z mmann $
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

#include <epan/packet.h>
#include <epan/addr_resolv.h>
#include <epan/expert.h>
#include <epan/prefs.h>

#include "packet-bluetooth-hci.h"

/* Initialize the protocol and registered fields */
static int proto_bthci_cmd = -1;
static int hf_bthci_cmd_opcode = -1;
static int hf_bthci_cmd_ogf = -1;
static int hf_bthci_cmd_ocf = -1;
static int hf_bthci_cmd_ocf_link_control = -1;
static int hf_bthci_cmd_ocf_link_policy = -1;
static int hf_bthci_cmd_ocf_host_controller_and_baseband = -1;
static int hf_bthci_cmd_ocf_informational = -1;
static int hf_bthci_cmd_ocf_status = -1;
static int hf_bthci_cmd_ocf_testing = -1;
static int hf_bthci_cmd_ocf_logo_testing = -1;
static int hf_bthci_cmd_ocf_low_energy = -1;
static int hf_bthci_cmd_param_length = -1;
static int hf_bthci_cmd_lap = -1;
static int hf_bthci_cmd_inq_length = -1;
static int hf_bthci_cmd_num_responses = -1;
static int hf_bthci_cmd_encrypt_mode = -1;
static int hf_bthci_cmd_bd_addr = -1;
static int hf_bthci_cmd_packet_type_dm1 = -1;
static int hf_bthci_cmd_packet_type_dm3 = -1;
static int hf_bthci_cmd_packet_type_dm5 = -1;
static int hf_bthci_cmd_packet_type_dh1 = -1;
static int hf_bthci_cmd_packet_type_dh3 = -1;
static int hf_bthci_cmd_packet_type_dh5 = -1;
static int hf_bthci_cmd_packet_type_2dh1 = -1;
static int hf_bthci_cmd_packet_type_3dh1 = -1;
static int hf_bthci_cmd_packet_type_2dh3 = -1;
static int hf_bthci_cmd_packet_type_3dh3 = -1;
static int hf_bthci_cmd_packet_type_2dh5 = -1;
static int hf_bthci_cmd_packet_type_3dh5 = -1;
static int hf_bthci_cmd_clock_offset = -1;
static int hf_bthci_cmd_clock_offset_valid = -1;
static int hf_bthci_cmd_allow_role_switch = -1;
static int hf_bthci_cmd_page_scan_mode = -1;
static int hf_bthci_cmd_page_scan_repetition_mode = -1;
static int hf_bthci_cmd_page_scan_period_mode = -1;
static int hf_bthci_cmd_max_period_length = -1;
static int hf_bthci_cmd_min_period_length = -1;
static int hf_bthci_cmd_connection_handle = -1;
static int hf_bthci_cmd_reason = -1;
static int hf_bthci_cmd_num_link_keys = -1;
static int hf_bthci_cmd_link_key = -1;
static int hf_bthci_cmd_packet_type_hv1 = -1;
static int hf_bthci_cmd_packet_type_hv2 = -1;
static int hf_bthci_cmd_packet_type_hv3 = -1;
static int hf_bthci_cmd_role = -1;
static int hf_bthci_cmd_pin_code_length = -1;
static int hf_bthci_cmd_pin_code = -1;
static int hf_bthci_cmd_pin_type = -1;
static int hf_bthci_cmd_encryption_enable = -1;
static int hf_bthci_cmd_key_flag = -1;
static int hf_bthci_cmd_max_interval_hold = -1;
static int hf_bthci_cmd_min_interval_hold = -1;
static int hf_bthci_cmd_max_interval_sniff = -1;
static int hf_bthci_cmd_min_interval_sniff = -1;
static int hf_bthci_cmd_sniff_attempt = -1;
static int hf_bthci_cmd_timeout = -1;
static int hf_bthci_cmd_max_interval_beacon = -1;
static int hf_bthci_cmd_min_interval_beacon = -1;
static int hf_bthci_cmd_flags = -1;
static int hf_bthci_cmd_service_type = -1;
static int hf_bthci_cmd_token_rate = -1;
static int hf_bthci_cmd_token_bucket_size = -1;
static int hf_bthci_cmd_peak_bandwidth = -1;
static int hf_bthci_cmd_latency = -1;
static int hf_bthci_cmd_delay_variation = -1;
static int hf_bthci_cmd_link_policy_setting_switch = -1;
static int hf_bthci_cmd_link_policy_setting_hold = -1;
static int hf_bthci_cmd_link_policy_setting_sniff = -1;
static int hf_bthci_cmd_link_policy_setting_park = -1;
static int hf_bthci_cmd_filter_type = -1;
static int hf_bthci_cmd_inquiry_result_filter_condition_type = -1;
static int hf_bthci_cmd_connection_setup_filter_condition_type = -1;
static int hf_bthci_cmd_class_of_device = -1;
static int hf_bthci_cmd_cod_format_type = -1;
static int hf_bthci_cmd_cod_major_service_class_information = -1;
static int hf_bthci_cmd_cod_major_service_class_telephony = -1;
static int hf_bthci_cmd_cod_major_service_class_audio = -1;
static int hf_bthci_cmd_cod_major_service_class_object_transfer = -1;
static int hf_bthci_cmd_cod_major_service_class_capturing = -1;
static int hf_bthci_cmd_cod_major_service_class_rendering = -1;
static int hf_bthci_cmd_cod_major_service_class_networking = -1;
static int hf_bthci_cmd_cod_major_service_class_positioning = -1;
static int hf_bthci_cmd_cod_major_service_class_reserved = -1;
static int hf_bthci_cmd_cod_major_service_class_limited_discoverable_mode = -1;
static int hf_bthci_cmd_cod_major_device_class = -1;
static int hf_bthci_cmd_cod_minor_device_class_computer = -1;
static int hf_bthci_cmd_cod_minor_device_class_phone = -1;
static int hf_bthci_cmd_cod_minor_device_class_lan_net_load_factor = -1;
static int hf_bthci_cmd_cod_minor_device_class_lan_net_type = -1;
static int hf_bthci_cmd_cod_minor_device_class_audio_video = -1;
static int hf_bthci_cmd_cod_minor_device_class_peripheral_class = -1;
static int hf_bthci_cmd_cod_minor_device_class_peripheral_type = -1;
static int hf_bthci_cmd_cod_minor_device_class_imaging_class_printer = -1;
static int hf_bthci_cmd_cod_minor_device_class_imaging_class_scanner = -1;
static int hf_bthci_cmd_cod_minor_device_class_imaging_class_camera = -1;
static int hf_bthci_cmd_cod_minor_device_class_imaging_class_display = -1;
static int hf_bthci_cmd_cod_minor_device_class_imaging_type = -1;
static int hf_bthci_cmd_cod_minor_device_class_wearable = -1;
static int hf_bthci_cmd_cod_minor_device_class_toy = -1;
static int hf_bthci_cmd_cod_minor_device_class_health = -1;
static int hf_bthci_cmd_cod_minor_device_class_unknown = -1;
static int hf_bthci_cmd_class_of_device_mask = -1;
static int hf_bthci_cmd_cod_minor_device_class_mask= -1;
static int hf_bthci_cmd_cod_format_type_mask = -1;
static int hf_bthci_cmd_cod_major_service_class_information_mask = -1;
static int hf_bthci_cmd_cod_major_service_class_telephony_mask = -1;
static int hf_bthci_cmd_cod_major_service_class_audio_mask = -1;
static int hf_bthci_cmd_cod_major_service_class_object_transfer_mask = -1;
static int hf_bthci_cmd_cod_major_service_class_capturing_mask = -1;
static int hf_bthci_cmd_cod_major_service_class_rendering_mask = -1;
static int hf_bthci_cmd_cod_major_service_class_networking_mask = -1;
static int hf_bthci_cmd_cod_major_service_class_positioning_mask = -1;
static int hf_bthci_cmd_cod_major_service_class_reserved_mask = -1;
static int hf_bthci_cmd_cod_major_service_class_limited_discoverable_mode_mask = -1;
static int hf_bthci_cmd_cod_major_device_class_mask = -1;
static int hf_bthci_cmd_auto_acc_flag = -1;
static int hf_bthci_cmd_read_all_flag = -1;
static int hf_bthci_cmd_delete_all_flag = -1;
static int hf_bthci_cmd_authentication_enable = -1;
static int hf_bthci_cmd_input_unused = -1;
static int hf_bthci_cmd_input_coding = -1;
static int hf_bthci_cmd_input_data_format = -1;
static int hf_bthci_cmd_input_sample_size = -1;
static int hf_bthci_cmd_linear_pcm_bit_pos = -1;
static int hf_bthci_cmd_air_coding_format = -1;
static int hf_bthci_cmd_num_broadcast_retransmissions = -1;
static int hf_bthci_cmd_hold_mode_act_page = -1;
static int hf_bthci_cmd_hold_mode_act_inquiry = -1;
static int hf_bthci_cmd_hold_mode_act_periodic = -1;
static int hf_bthci_cmd_scan_enable = -1;
static int hf_bthci_cmd_interval = -1;
static int hf_bthci_cmd_window = -1;
static int hf_bthci_cmd_device_name = -1;
static int hf_bthci_cmd_num_curr_iac = -1;
static int hf_bthci_cmd_iac_lap = -1;
static int hf_bthci_cmd_evt_mask_00 = -1;
static int hf_bthci_cmd_evt_mask_01 = -1;
static int hf_bthci_cmd_evt_mask_02 = -1;
static int hf_bthci_cmd_evt_mask_03 = -1;
static int hf_bthci_cmd_evt_mask_04 = -1;
static int hf_bthci_cmd_evt_mask_05 = -1;
static int hf_bthci_cmd_evt_mask_06 = -1;
static int hf_bthci_cmd_evt_mask_07 = -1;
static int hf_bthci_cmd_evt_mask_10 = -1;
static int hf_bthci_cmd_evt_mask_11 = -1;
static int hf_bthci_cmd_evt_mask_12 = -1;
static int hf_bthci_cmd_evt_mask_13 = -1;
static int hf_bthci_cmd_evt_mask_14 = -1;
static int hf_bthci_cmd_evt_mask_17 = -1;
static int hf_bthci_cmd_evt_mask_20 = -1;
static int hf_bthci_cmd_evt_mask_21 = -1;
static int hf_bthci_cmd_evt_mask_23 = -1;
static int hf_bthci_cmd_evt_mask_24 = -1;
static int hf_bthci_cmd_evt_mask_25 = -1;
static int hf_bthci_cmd_evt_mask_26 = -1;
static int hf_bthci_cmd_evt_mask_27 = -1;
static int hf_bthci_cmd_evt_mask_30 = -1;
static int hf_bthci_cmd_evt_mask_31 = -1;
static int hf_bthci_cmd_evt_mask_32 = -1;
static int hf_bthci_cmd_evt_mask_33 = -1;
static int hf_bthci_cmd_evt_mask_34 = -1;
static int hf_bthci_cmd_evt_mask_35 = -1;
static int hf_bthci_cmd_evt_mask_36 = -1;
static int hf_bthci_cmd_evt_mask_37 = -1;
static int hf_bthci_cmd_evt_mask_40 = -1;
static int hf_bthci_cmd_evt_mask_41 = -1;
static int hf_bthci_cmd_evt_mask_42 = -1;
static int hf_bthci_cmd_evt_mask_53 = -1;
static int hf_bthci_cmd_evt_mask_54 = -1;
static int hf_bthci_cmd_evt_mask_55 = -1;
static int hf_bthci_cmd_evt_mask_56 = -1;
static int hf_bthci_cmd_evt_mask_57 = -1;
static int hf_bthci_cmd_evt_mask_60 = -1;
static int hf_bthci_cmd_evt_mask_61 = -1;
static int hf_bthci_cmd_evt_mask_62 = -1;
static int hf_bthci_cmd_evt_mask_63 = -1;
static int hf_bthci_cmd_evt_mask_64 = -1;
static int hf_bthci_cmd_evt_mask_65 = -1;
static int hf_bthci_cmd_evt_mask_67 = -1;
static int hf_bthci_cmd_evt_mask_70 = -1;
static int hf_bthci_cmd_evt_mask_72 = -1;
static int hf_bthci_cmd_evt_mask_73 = -1;
static int hf_bthci_cmd_sco_flow_control = -1;
static int hf_bthci_cmd_num_handles = -1;
static int hf_bthci_cmd_num_compl_packets = -1;
static int hf_bthci_cmd_flow_contr_enable = -1;
static int hf_bthci_cmd_host_data_packet_length_acl = -1;
static int hf_bthci_cmd_host_data_packet_length_sco = -1;
static int hf_bthci_cmd_host_total_num_acl_data_packets = -1;
static int hf_bthci_cmd_host_total_num_sco_data_packets = -1;
static int hf_bthci_cmd_loopback_mode = -1;
static int hf_bthci_cmd_page_number = -1;
static int hf_bthci_cmd_transmit_bandwidth = -1;
static int hf_bthci_cmd_receive_bandwidth = -1;
static int hf_bthci_cmd_max_latency_ms = -1;
static int hf_bthci_cmd_max_latency = -1;
static int hf_bthci_cmd_retransmission_effort = -1;
static int hf_bthci_cmd_scan_type = -1;
static int hf_bthci_cmd_inq_mode = -1;
static int hf_bthci_cmd_fec_required = -1;
static int hf_bthci_cmd_err_data_reporting = -1;
static int hf_bthci_cmd_tx_power = -1;
static int hf_bthci_cmd_sco_packet_type_hv1 = -1;
static int hf_bthci_cmd_sco_packet_type_hv2 = -1;
static int hf_bthci_cmd_sco_packet_type_hv3 = -1;
static int hf_bthci_cmd_sco_packet_type_ev3 = -1;
static int hf_bthci_cmd_sco_packet_type_ev4 = -1;
static int hf_bthci_cmd_sco_packet_type_ev5 = -1;
static int hf_bthci_cmd_sco_packet_type_2ev3 = -1;
static int hf_bthci_cmd_sco_packet_type_3ev3 = -1;
static int hf_bthci_cmd_sco_packet_type_2ev5 = -1;
static int hf_bthci_cmd_sco_packet_type_3ev5 = -1;
static int hf_bthci_cmd_min_remote_timeout = -1;
static int hf_bthci_cmd_min_local_timeout = -1;
static int hf_bthci_cmd_flush_packet_type = -1;
static int hf_bthci_cmd_afh_ch_assessment_mode = -1;
static int hf_bthci_cmd_afh_ch_classification = -1;
static int hf_bthci_cmd_which_clock = -1;
static int hf_bthci_cmd_io_capability = -1;
static int hf_bthci_cmd_oob_data_present = -1;
static int hf_bthci_cmd_auth_requirements = -1;
static int hf_bthci_cmd_passkey = -1;
static int hf_bthci_cmd_randomizer_r = -1;
static int hf_bthci_cmd_hash_c = -1;
static int hf_bthci_cmd_simple_pairing_mode = -1;
static int hf_bthci_cmd_simple_pairing_debug_mode = -1;
static int hf_bthci_cmd_notification_type = -1;
static int hf_bthci_cmd_eir_data = -1;
static int hf_bthci_cmd_eir_struct_length = -1;
static int hf_bthci_cmd_eir_struct_type = -1;
static int hf_bthci_cmd_sc_uuid16 = -1;
static int hf_bthci_cmd_sc_uuid32 = -1;
static int hf_bthci_cmd_sc_uuid128 = -1;
static int hf_bthci_cmd_physical_link_handle = -1;
static int hf_bthci_cmd_dedicated_amp_key_length = -1;
static int hf_bthci_cmd_dedicated_amp_key_type = -1;
static int hf_bthci_cmd_dedicated_amp_key = -1;
static int hf_bthci_cmd_flow_spec = -1;
static int hf_bthci_cmd_flow_spec_identifier = -1;
static int hf_bthci_cmd_flow_spec_service_type = -1;
static int hf_bthci_cmd_flow_spec_sdu_size = -1;
static int hf_bthci_cmd_flow_spec_sdu_arrival_time = -1;
static int hf_bthci_cmd_flow_spec_access_latency = -1;
static int hf_bthci_cmd_flush_to_us = -1;
static int hf_bthci_cmd_logical_link_handle = -1;
static int hf_bthci_cmd_evt_mask2_00 = -1;
static int hf_bthci_cmd_evt_mask2_01 = -1;
static int hf_bthci_cmd_evt_mask2_02 = -1;
static int hf_bthci_cmd_evt_mask2_03 = -1;
static int hf_bthci_cmd_evt_mask2_04 = -1;
static int hf_bthci_cmd_evt_mask2_05 = -1;
static int hf_bthci_cmd_evt_mask2_06 = -1;
static int hf_bthci_cmd_evt_mask2_07 = -1;
static int hf_bthci_cmd_evt_mask2_10 = -1;
static int hf_bthci_cmd_evt_mask2_11 = -1;
static int hf_bthci_cmd_evt_mask2_12 = -1;
static int hf_bthci_cmd_evt_mask2_13 = -1;
static int hf_bthci_cmd_evt_mask2_14 = -1;
static int hf_bthci_cmd_evt_mask2_15 = -1;
static int hf_bthci_cmd_location_domain_aware = -1;
static int hf_bthci_cmd_location_domain = -1;
static int hf_bthci_cmd_location_domain_options = -1;
static int hf_bthci_cmd_location_options = -1;
static int hf_bthci_cmd_flow_control_mode = -1;
static int hf_bthci_cmd_tx_power_level_type = -1;
static int hf_bthci_cmd_short_range_mode = -1;
static int hf_bthci_cmd_le_supported_host = -1;
static int hf_bthci_cmd_le_simultaneous_host = -1;
static int hf_bthci_cmd_enable_amp_recv_reports = -1;
static int hf_bthci_cmd_amp_recv_report_interval = -1;
static int hf_bthci_cmd_length_so_far = -1;
static int hf_bthci_cmd_amp_assoc_length = -1;
static int hf_bthci_cmd_amp_remaining_assoc_length = -1;
static int hf_bthci_cmd_amp_assoc_fragment = -1;
static int hf_bthci_cmd_le_evt_mask_00 = -1;
static int hf_bthci_cmd_le_evt_mask_01 = -1;
static int hf_bthci_cmd_le_evt_mask_02 = -1;
static int hf_bthci_cmd_le_evt_mask_03 = -1;
static int hf_bthci_cmd_le_evt_mask_04 = -1;
static int hf_bthci_cmd_le_advts_interval_min = -1;
static int hf_bthci_cmd_le_advts_interval_max = -1;
static int hf_bthci_cmd_le_advts_type = -1;
static int hf_bthci_cmd_le_own_address_type = -1;
static int hf_bthci_cmd_le_direct_address_type = -1;
static int hf_bthci_cmd_le_advts_channel_map_1 = -1;
static int hf_bthci_cmd_le_advts_channel_map_2 = -1;
static int hf_bthci_cmd_le_advts_channel_map_3 = -1;
static int hf_bthci_cmd_le_advts_filter_policy = -1;
static int hf_bthci_cmd_le_data_length = -1;
static int hf_bthci_cmd_le_advts_enable = -1;
static int hf_bthci_cmd_le_scan_enable = -1;
static int hf_bthci_cmd_le_filter_dublicates = -1;
static int hf_bthci_cmd_le_scan_type = -1;
static int hf_bthci_cmd_le_scan_interval = -1;
static int hf_bthci_cmd_le_scan_window = -1;
static int hf_bthci_cmd_le_scan_filter_policy = -1;
static int hf_bthci_cmd_le_initiator_filter_policy = -1;
static int hf_bthci_cmd_le_peer_address_type = -1;
static int hf_bthci_cmd_le_con_interval_min = -1;
static int hf_bthci_cmd_le_con_interval_max = -1;
static int hf_bthci_cmd_le_con_latency = -1;
static int hf_bthci_cmd_le_supervision_timeout = -1;
static int hf_bthci_cmd_le_min_ce_length = -1;
static int hf_bthci_cmd_le_max_ce_length = -1;
static int hf_bthci_cmd_le_address_type = -1;
static int hf_bthci_cmd_le_channel_map = -1;
static int hf_bthci_cmd_key = -1;
static int hf_bthci_cmd_plaintext_data = -1;
static int hf_bthci_cmd_random_number = -1;
static int hf_bthci_cmd_encrypted_diversifier = -1;
static int hf_bthci_cmd_le_long_term_key = -1;
static int hf_bthci_cmd_rx_freqency = -1;
static int hf_bthci_cmd_tx_freqency = -1;
static int hf_bthci_cmd_test_data_length = -1;
static int hf_bthci_cmd_test_packet_payload = -1;
static int hf_bthci_cmd_appearance = -1;
static int hf_bthci_cmd_flags_limited_disc_mode = -1;
static int hf_bthci_cmd_flags_general_disc_mode = -1;
static int hf_bthci_cmd_flags_bredr_not_support = -1;
static int hf_bthci_cmd_flags_le_bredr_support_ctrl = -1;
static int hf_bthci_cmd_flags_le_bredr_support_host = -1;
static int hf_bthci_cmd_flags_le_oob_data_present = -1;
static int hf_bthci_cmd_flags_le_oob_le_supported_host = -1;
static int hf_bthci_cmd_flags_le_oob_le_bredr_support = -1;
static int hf_bthci_cmd_flags_le_oob_address_type = -1;
static int hf_bthci_cmd_eir_ad_advertising_interval = -1;
static int hf_bthci_cmd_eir_ad_ssp_oob_length = -1;
static int hf_bthci_cmd_eir_ad_company_id = -1;
static int hf_eir_ad_item = -1;
static int hf_extended_inquiry_response_data = -1;
static int hf_advertising_data = -1;
static int hf_3ds_association_notification = -1;
static int hf_3ds_battery_level_reporting = -1;
static int hf_3ds_send_battery_level_report_on_startup = -1;
static int hf_3ds_reserved = -1;
static int hf_3ds_factory_test_mode = -1;
static int hf_3ds_path_loss_threshold = -1;
static int hf_3ds_legacy_fixed = -1;
static int hf_3ds_legacy_3d_capable_tv = -1;
static int hf_3ds_legacy_ignored_1_3 = -1;
static int hf_3ds_legacy_fixed_4 = -1;
static int hf_3ds_legacy_ignored_5 = -1;
static int hf_3ds_legacy_fixed_6 = -1;
static int hf_3ds_legacy_test_mode = -1;
static int hf_3ds_legacy_path_loss_threshold = -1;
static int hf_did_vendor_id = -1;
static int hf_did_vendor_id_bluetooth_sig = -1;
static int hf_did_vendor_id_usb_forum = -1;
static int hf_did_product_id = -1;
static int hf_did_version = -1;
static int hf_did_vendor_id_source = -1;

static expert_field ei_eir_undecoded                                  = EI_INIT;
static expert_field ei_eir_unknown                                    = EI_INIT;
static expert_field ei_command_undecoded                              = EI_INIT;
static expert_field ei_command_unknown                                = EI_INIT;
static expert_field ei_command_parameter_unexpected                   = EI_INIT;

/* Initialize the subtree pointers */
static gint ett_bthci_cmd = -1;
static gint ett_opcode = -1;
static gint ett_cod = -1;
static gint ett_cod_mask = -1;
static gint ett_eir_subtree = -1;
static gint ett_eir_struct_subtree = -1;
static gint ett_flow_spec_subtree = -1;

extern value_string_ext ext_usb_vendors_vals;
extern value_string_ext ext_usb_products_vals;
extern value_string_ext did_vendor_id_source_vals_ext;

static const value_string bthci_ogf_vals[] = {
    { 0x01,  "Link Control Commands" },
    { 0x02,  "Link Policy Commands" },
    { 0x03,  "Host Controller & Baseband Commands" },
    { 0x04,  "Informational Parameters" },
    { 0x05,  "Status Parameters" },
    { 0x06,  "Testing Commands" },
    { 0x08,  "LE Controller Commands" },
    { 0x3E,  "Bluetooth Logo Testing Commands" },
    { 0x3F,  "Vendor-Specific Commands" },
    { 0, NULL }
};
value_string_ext bthci_ogf_vals_ext = VALUE_STRING_EXT_INIT(bthci_ogf_vals);

static const value_string bthci_cmd_ocf_link_control_vals[] = {
/* Bluetooth Core 4.0 */
    { 0x001,  "Inquiry" },
    { 0x002,  "Inquiry Cancel" },
    { 0x003,  "Periodic Inquiry Mode" },
    { 0x004,  "Exit Periodic Inquiry Mode" },
    { 0x005,  "Create Connection" },
    { 0x006,  "Disconnect" },
    { 0x007,  "Add SCO Connection" },
    { 0x008,  "Create Connection Cancel" },
    { 0x009,  "Accept Connection Request" },
    { 0x00A,  "Reject Connection Request" },
    { 0x00B,  "Link Key Request Reply" },
    { 0x00C,  "Link Key Request Negative Reply" },
    { 0x00D,  "PIN Code Request Reply" },
    { 0x00E,  "PIN Code Request Negative Reply" },
    { 0x00F,  "Change Connection Packet Type" },
    { 0x011,  "Authentication Requested" },
    { 0x013,  "Set Connection Encryption" },
    { 0x015,  "Change Connection Link Key" },
    { 0x017,  "Master Link Key" },
    { 0x019,  "Remote Name Request" },
    { 0x01A,  "Remote Name Request Cancel" },
    { 0x01B,  "Read Remote Supported Features" },
    { 0x01C,  "Read Remote Extended Features" },
    { 0x01D,  "Read Remote Version Information" },
    { 0x01F,  "Read Clock offset" },
    { 0x020,  "Read LMP Handle" },
    { 0x028,  "Setup Synchronous Connection" },
    { 0x029,  "Accept Synchronous Connection Request" },
    { 0x02A,  "Reject Synchronous Connection Request" },
    { 0x02B,  "IO Capability Request Reply" },
    { 0x02C,  "User Confirmation Request Reply" },
    { 0x02D,  "User Confirmation Request Negative Reply" },
    { 0x02E,  "User Passkey Request Reply" },
    { 0x02F,  "User Passkey Request Negative Reply" },
    { 0x030,  "Remote OOB Data Request Reply" },
    { 0x033,  "Remote OOB Data Request Negative Reply" },
    { 0x034,  "IO Capability Request Negative Reply" },
    { 0x035,  "Create Physical Link" },
    { 0x036,  "Accept Physical Link" },
    { 0x037,  "Disconnect Physical Link" },
    { 0x038,  "Create Logical Link" },
    { 0x039,  "Accept Logical Link" },
    { 0x03A,  "Disconnect Logical Link" },
    { 0x03B,  "Logical Link Cancel" },
    { 0x03C,  "Flow Spec Modify" },
/* Bluetooth Core Specification Addendum 2 */
    { 0x03D,  "Enhanced Setup Synchronous Connection" },
    { 0x03E,  "Enhanced Accept Synchronous Connection Request" },
/* Bluetooth Core Specification Addendum 4 */
    { 0x03F,  "Truncated Page" },
    { 0x040,  "Truncated Page Cancel" },
    { 0x041,  "Set Connectionless Slave Broadcast" },
    { 0x042,  "Set Connectionless Slave Broadcast Receive" },
    { 0x043,  "Start Synchronization Train" },
    { 0x044,  "Receive Synchronization Train" },
    { 0, NULL }
};
value_string_ext bthci_cmd_ocf_link_control_vals_ext = VALUE_STRING_EXT_INIT(bthci_cmd_ocf_link_control_vals);

static const value_string bthci_cmd_ocf_link_policy_vals[] = {
/* Bluetooth Core 4.0 */
    { 0x001,  "Hold Mode" },
    { 0x003,  "Sniff Mode" },
    { 0x004,  "Exit Sniff Mode" },
    { 0x005,  "Park Mode" },
    { 0x006,  "Exit Park Mode" },
    { 0x007,  "QoS Setup" },
    { 0x009,  "Role Discovery" },
    { 0x00b,  "Switch Role" },
    { 0x00c,  "Read Link Policy Settings" },
    { 0x00d,  "Write Link Policy Settings" },
    { 0x00e,  "Read Default Link Policy Settings" },
    { 0x00f,  "Write Default Link Policy Settings" },
    { 0x010,  "Flow Specification" },
    { 0x011,  "Sniff Subrating" },
    { 0, NULL }
};
value_string_ext bthci_cmd_ocf_link_policy_vals_ext = VALUE_STRING_EXT_INIT(bthci_cmd_ocf_link_policy_vals);

static const value_string bthci_cmd_ocf_host_controller_and_baseband_vals[] = {
/* Bluetooth Core 4.0 */
    { 0x001,  "Set Event Mask" },
    { 0x003,  "Reset" },
    { 0x005,  "Set Event Filter" },
    { 0x008,  "Flush" },
    { 0x009,  "Read PIN Type" },
    { 0x00A,  "Write PIN Type" },
    { 0x00B,  "Create New Unit Key" },
    { 0x00D,  "Read Stored Link Key" },
    { 0x011,  "Write Stored Link Key" },
    { 0x012,  "Delete Stored Link Key" },
    { 0x013,  "Change Local Name" },
    { 0x014,  "Read Local Name" },
    { 0x015,  "Read Connection Accept Timeout" },
    { 0x016,  "Write Connection Accept Timeout" },
    { 0x017,  "Read Page Timeout" },
    { 0x018,  "Write Page Timeout" },
    { 0x019,  "Read Scan Enable" },
    { 0x01A,  "Write Scan Enable" },
    { 0x01B,  "Read Page Scan Activity" },
    { 0x01C,  "Write Page Scan Activity" },
    { 0x01D,  "Read Inquiry Scan Activity" },
    { 0x01E,  "Write Inquiry Scan Activity" },
    { 0x01F,  "Read Authentication Enable" },
    { 0x020,  "Write Authentication Enable" },
    { 0x021,  "Read Encryption Mode" },
    { 0x022,  "Write Encryption Mode" },
    { 0x023,  "Read Class of Device" },
    { 0x024,  "Write Class of Device" },
    { 0x025,  "Read Voice Setting" },
    { 0x026,  "Write Voice Setting" },
    { 0x027,  "Read Automatic Flush Timeout" },
    { 0x028,  "Write Automatic Flush Timeout" },
    { 0x029,  "Read Num Broadcast Retransmissions" },
    { 0x02A,  "Write Num Broadcast Retransmissions" },
    { 0x02B,  "Read Hold Mode Activity" },
    { 0x02C,  "Write Hold Mode Activity" },
    { 0x02D,  "Read Tx Power Level" },
    { 0x02E,  "Read SCO Flow Control Enable" },
    { 0x02F,  "Write SCO Flow Control Enable" },
    { 0x031,  "Set Host Controller To Host Flow Control" },
    { 0x033,  "Host Buffer Size" },
    { 0x035,  "Host Number of Completed Packets" },
    { 0x036,  "Read Link Supervision Timeout" },
    { 0x037,  "Write Link Supervision Timeout" },
    { 0x038,  "Read Number of Supported IAC" },
    { 0x039,  "Read Current IAC LAP" },
    { 0x03A,  "Write Current IAC LAP" },
    { 0x03B,  "Read Page Scan Period Mode" },
    { 0x03C,  "Write Page Scan Period Mode" },
    { 0x03D,  "Read Page Scan Mode" },
    { 0x03E,  "Write Page Scan Mode" },
    { 0x03F,  "Set AFH Host Channel Classification" },
    { 0x042,  "Read Inquiry Scan Type" },
    { 0x043,  "Write Inquiry Scan Type" },
    { 0x044,  "Read Inquiry Mode" },
    { 0x045,  "Write Inquiry Mode" },
    { 0x046,  "Read Page Scan Type" },
    { 0x047,  "Write Page Scan Type" },
    { 0x048,  "Read AFH Channel Assessment Mode" },
    { 0x049,  "Write AFH Channel Assessment Mode" },
    { 0x051,  "Read Extended Inquiry Response" },
    { 0x052,  "Write Extended Inquiry Response" },
    { 0x053,  "Refresh Encryption Key" },
    { 0x055,  "Read Simple Pairing Mode" },
    { 0x056,  "Write Simple Pairing Mode" },
    { 0x057,  "Read Local OOB Data" },
    { 0x058,  "Read Inquiry Response Tx Power Level" },
    { 0x059,  "Write Inquiry Tx Power Level" },
    { 0x05A,  "Read Default Erroneous Data Reporting" },
    { 0x05B,  "Write Default Erroneous Data Reporting" },
    { 0x05F,  "Enhanced Flush" },
    { 0x060,  "Send Keypress Notification" },
    { 0x061,  "Read Logical Link Accept Timeout" },
    { 0x062,  "Write Logical Link Accept Timeout" },
    { 0x063,  "Set Event Mask Page 2" },
    { 0x064,  "Read Location Data" },
    { 0x065,  "Write Location Data" },
    { 0x066,  "Read Flow Control Mode" },
    { 0x067,  "Write Flow Control Mode" },
    { 0x068,  "Read Enhanced Transmit Power Level" },
    { 0x069,  "Read Best Effort Flush Timeout" },
    { 0x06A,  "Write Best Effort Flush Timeout" },
    { 0x06B,  "Short Range Mode" },
    { 0x06C,  "Read LE Host Supported" },
    { 0x06D,  "Write LE Host Supported" },
/* Bluetooth Core Specification Addendum 3 */
    { 0x06E,  "Set MWS Channel Parameters"},
    { 0x06F,  "Set External Frame Configuration"},
    { 0x070,  "Set MWS Signaling"},
    { 0x071,  "Set MWS Transport Layer"},
    { 0x072,  "Set MWS Scan Frequency Table"},
    { 0x073,  "Set MWS Pattern Configuration"},
/* Bluetooth Core Specification Addendum 4 */
    { 0x074,  "Set Reserved LT_ADDR" },
    { 0x075,  "Delete Reserved LT_ADDR" },
    { 0x076,  "Set Connectionless Slave Broadcast Data" },
    { 0x077,  "Read Synchronization Train Parameters" },
    { 0x078,  "Write Synchronization Train Parameters" },
    { 0, NULL }
};
value_string_ext bthci_cmd_ocf_host_controller_and_baseband_vals_ext = VALUE_STRING_EXT_INIT(bthci_cmd_ocf_host_controller_and_baseband_vals);

static const value_string bthci_cmd_ocf_informational_vals[] = {
/* Bluetooth Core 4.0 */
    { 0x001,  "Read Local Version Information" },
    { 0x002,  "Read Local Supported Commands" },
    { 0x003,  "Read Local Supported Features" },
    { 0x004,  "Read Local Extended Features" },
    { 0x005,  "Read Buffer Size" },
    { 0x007,  "Read Country Code" },
    { 0x009,  "Read BD ADDR" },
    { 0x00A,  "Read Data Block Size" },
/* Bluetooth Core Specification Addendum 2 */
    { 0x00B,  "Read Local Supported Codecs" },
    { 0, NULL }
};
value_string_ext bthci_cmd_ocf_informational_vals_ext = VALUE_STRING_EXT_INIT(bthci_cmd_ocf_informational_vals);


static const value_string bthci_cmd_ocf_status_vals[] = {
/* Bluetooth Core 4.0 */
    { 0x001, "Read Failed Contact Counter" },
    { 0x002, "Reset Failed Contact Counter" },
    { 0x003, "Read Link Quality" },
    { 0x005, "Read RSSI" },
    { 0x006, "Read AFH Channel Map" },
    { 0x007, "Read Clock" },
    { 0x008, "Read Encryption Key Size" },
    { 0x009, "Read Local AMP Info" },
    { 0x00A, "Read Local AMP Assoc" },
    { 0x00B, "Write Remote AMP Assoc" },
/* Bluetooth Core Specification Addendum 3 */
    { 0x00C,  "Get MWS Transport Layer Configuration" },
/* Bluetooth Core Specification Addendum 4 */
    { 0x00D,  "Set Triggered Clock Capture" },
    { 0, NULL }
};
value_string_ext bthci_cmd_ocf_status_vals_ext = VALUE_STRING_EXT_INIT(bthci_cmd_ocf_status_vals);

static const value_string bthci_cmd_ocf_testing_vals[] = {
/* Bluetooth Core 4.0 */
    { 0x001,  "Read Loopback Mode" },
    { 0x002,  "Write Loopback Mode" },
    { 0x003,  "Enable Device Under Test Mode" },
    { 0x004,  "Write Simple Pairing Debug Mode" },
    { 0x007,  "Enable AMP Receiver Reports" },
    { 0x008,  "AMP Test End" },
    { 0x009,  "AMP Test" },
    { 0, NULL }
};
value_string_ext bthci_cmd_ocf_testing_vals_ext = VALUE_STRING_EXT_INIT(bthci_cmd_ocf_testing_vals);

static const value_string bthci_cmd_ocf_low_energy_vals[] = {
/* Bluetooth Core 4.0 */
    { 0x001,  "LE Set Event Mask" },
    { 0x002,  "LE Read Buffer Size" },
    { 0x003,  "LE Read Local Supported Features" },
    { 0x005,  "LE Set Random Address" },
    { 0x006,  "LE Set Advertising Parameters" },
    { 0x007,  "LE Read Advertising Channel Tx Power" },
    { 0x008,  "LE Set Advertising Data" },
    { 0x009,  "LE Set Scan Response Data" },
    { 0x00A,  "LE Set Advertise Enable" },
    { 0x00B,  "LE Set Scan Parameters" },
    { 0x00C,  "LE Set Scan Enable" },
    { 0x00D,  "LE Create Connection" },
    { 0x00E,  "LE Create Connection Cancel" },
    { 0x00F,  "LE Read White List Size" },
    { 0x010,  "LE Clear White List" },
    { 0x011,  "LE Add Device To White List" },
    { 0x012,  "LE Remove Device From White List" },
    { 0x013,  "LE Connection Update" },
    { 0x014,  "LE Set Host Channel Classification" },
    { 0x015,  "LE Read Channel Map" },
    { 0x016,  "LE Read Remote Used Features" },
    { 0x017,  "LE Encrypt" },
    { 0x018,  "LE Rand" },
    { 0x019,  "LE Start Encryption" },
    { 0x01A,  "LE Long Term Key Request Reply" },
    { 0x01B,  "LE Long Term Key Request Negative Reply" },
    { 0x01C,  "LE Read Supported States" },
    { 0x01D,  "LE Receiver Test" },
    { 0x01E,  "LE Transmitter Test" },
    { 0x01F,  "LE Test End" },
    { 0, NULL }
};
value_string_ext bthci_cmd_ocf_low_energy_vals_ext = VALUE_STRING_EXT_INIT(bthci_cmd_ocf_low_energy_vals);


static value_string bthci_cmd_opcode_vals[array_length(bthci_cmd_ocf_link_control_vals) - 1 +
        array_length(bthci_cmd_ocf_link_policy_vals) - 1 +
        array_length(bthci_cmd_ocf_host_controller_and_baseband_vals) - 1 +
        array_length(bthci_cmd_ocf_informational_vals) - 1 +
        array_length(bthci_cmd_ocf_status_vals) - 1 +
        array_length(bthci_cmd_ocf_testing_vals) - 1 +
        array_length(bthci_cmd_ocf_low_energy_vals) - 1 + 2];
value_string_ext bthci_cmd_opcode_vals_ext = VALUE_STRING_EXT_INIT(bthci_cmd_opcode_vals);

static const value_string bthci_cmd_status_vals[] = {
    {0x00, "Success"},
    {0x01, "Unknown HCI Command"},
    {0x02, "No Connection"},
    {0x03, "Hardware Failure"},
    {0x04, "Page Timeout"},
    {0x05, "Authentication Failure"},
    {0x06, "Key Missing"},
    {0x07, "Memory Full"},
    {0x08, "Connection Timeout"},
    {0x09, "Max Number Of Connections"},
    {0x0A, "Max Number Of SCO Connections To A Device"},
    {0x0B, "ACL connection already exists"},
    {0x0C, "Command Disallowed"},
    {0x0D, "Host Rejected due to limited resources"},
    {0x0E, "Host Rejected due to security reasons"},
    {0x0F, "Host Rejected due to remote device is only a personal device"},
    {0x10, "Host Timeout"},
    {0x11, "Unsupported Feature or Parameter Value"},
    {0x12, "Invalid HCI Command Parameters"},
    {0x13, "Other End Terminated Connection: User Ended Connection"},
    {0x14, "Other End Terminated Connection: Low Resources"},
    {0x15, "Other End Terminated Connection: About to Power Off"},
    {0x16, "Connection Terminated by Local Host"},
    {0x17, "Repeated Attempts"},
    {0x18, "Pairing Not Allowed"},
    {0x19, "Unknown LMP PDU"},
    {0x1A, "Unsupported Remote Feature"},
    {0x1B, "SCO Offset Rejected"},
    {0x1C, "SCO Interval Rejected"},
    {0x1D, "SCO Air Mode Rejected"},
    {0x1E, "Invalid LMP Parameters"},
    {0x1F, "Unspecified Error"},
    {0x20, "Unsupported LMP Parameter Value"},
    {0x21, "Role Change Not Allowed"},
    {0x22, "LMP Response Timeout"},
    {0x23, "LMP Error Transaction Collision"},
    {0x24, "LMP PDU Not Allowed"},
    {0x25, "Encryption Mode Not Acceptable"},
    {0x26, "Unit Key Used"},
    {0x27, "QoS is Not Supported"},
    {0x28, "Instant Passed"},
    {0x29, "Pairing with Unit Key Not Supported"},
    {0x2A, "Different Transaction Collision"},
    {0x2C, "QoS Unacceptable Parameter"},
    {0x2D, "QoS Rejected"},
    {0x2E, "Channel Classification Not Supported"},
    {0x2F, "Insufficient Security"},
    {0x30, "Parameter Out Of Mandatory Range"},
    {0x31, "Unknown"},
    {0x32, "Role Switch Pending"},
    {0x33, "Unknown"},
    {0x34, "Reserved Slot Violation"},
    {0x35, "Role Switch Failed"},
    {0x36, "Extended Inquiry Response Too Large"},
    {0x37, "Secure Simple Pairing Not Supported By Host"},
    {0x38, "Host Busy - Pairing"},
    {0x39, "Connection Rejected - No Suitable Channel Found"},
    {0x3a, "Controller Busy"},
    {0x3b, "Unacceptable Connection Interval"},
    {0x3c, "Directed Advertising Timeout"},
    {0x3d, "Connection Terminated - MIC Failure"},
    {0x3e, "Connection Failed To Be Established"},
    {0x3f, "MAC Connection Failed"},
    {0, NULL }
};
value_string_ext bthci_cmd_status_vals_ext = VALUE_STRING_EXT_INIT(bthci_cmd_status_vals);

static const value_string bthci_cmd_cod_major_device_class_vals[] = {
    {0x00, "Miscellaneous"},
    {0x01, "Computer"},
    {0x02, "Phone"},
    {0x03, "LAN/Network Access Point"},
    {0x04, "Audio/Video"},
    {0x05, "Peripheral (HID)"},
    {0x06, "Imaging"},
    {0x07, "Wearable"},
    {0x08, "Toy"},
    {0x09, "Health"},
    {0x1F, "Uncategorized: device code not specified"},
    {0, NULL }
};
value_string_ext bthci_cmd_cod_major_device_class_vals_ext = VALUE_STRING_EXT_INIT(bthci_cmd_cod_major_device_class_vals);

static const value_string bthci_cmd_cod_minor_device_class_computer_vals[] = {
    { 0x00,  "Uncategorized, code for device not assigned" },
    { 0x01,  "Desktop workstation" },
    { 0x02,  "Server-class computer" },
    { 0x03,  "Laptop" },
    { 0x04,  "Handheld PC/PDA (clamshell)" },
    { 0x05,  "Palm-size PC/PDA" },
    { 0x06,  "Wearable computer (watch size)" },
    { 0x07,  "Tablet" },
    { 0, NULL }
};
value_string_ext bthci_cmd_cod_minor_device_class_computer_vals_ext = VALUE_STRING_EXT_INIT(bthci_cmd_cod_minor_device_class_computer_vals);

static const value_string bthci_cmd_cod_minor_device_class_phone_vals[] = {
    { 0x00,  "Uncategorized, code for device not assigned" },
    { 0x01,  "Cellular" },
    { 0x02,  "Cordless" },
    { 0x03,  "Smartphone" },
    { 0x04,  "Wired modem or voice gateway" },
    { 0x05,  "Common ISDN access" },
    { 0, NULL }
};
value_string_ext bthci_cmd_cod_minor_device_class_phone_vals_ext = VALUE_STRING_EXT_INIT(bthci_cmd_cod_minor_device_class_phone_vals);

static const value_string bthci_cmd_cod_minor_device_class_lan_net_load_factor_vals[] = {
    { 0x00,  "Fully available" },
    { 0x01,  "1% to 17% utilized" },
    { 0x02,  "17% to 33% utilized" },
    { 0x03,  "33% to 50% utilized" },
    { 0x04,  "50% to 67% utilized" },
    { 0x05,  "67% to 83% utilized" },
    { 0x06,  "83% to 99% utilized" },
    { 0x07,  "No service available" },
    { 0, NULL }
};
value_string_ext bthci_cmd_cod_minor_device_class_lan_net_load_factor_vals_ext = VALUE_STRING_EXT_INIT(bthci_cmd_cod_minor_device_class_lan_net_load_factor_vals);

static const value_string bthci_cmd_cod_minor_device_class_lan_net_type_vals[] = {
    { 0x00,  "Uncategorized (used if no others apply)" },
    { 0, NULL }
};
value_string_ext bthci_cmd_cod_minor_device_class_lan_net_type_vals_ext = VALUE_STRING_EXT_INIT(bthci_cmd_cod_minor_device_class_lan_net_type_vals);

static const value_string bthci_cmd_cod_minor_device_class_audio_video_vals[] = {
    { 0x00,  "Uncategorized, code not assigned" },
    { 0x01,  "Wearable Headset Device" },
    { 0x02,  "Hands-free Device" },
    { 0x04,  "Microphone" },
    { 0x05,  "Loudspeaker" },
    { 0x06,  "Headphones" },
    { 0x07,  "Portable Audio" },
    { 0x08,  "Car audio" },
    { 0x09,  "Set-top box" },
    { 0x0A,  "HiFi Audio Device" },
    { 0x0B,  "VCR" },
    { 0x0C,  "Video Camera" },
    { 0x0D,  "Camcorder" },
    { 0x0E,  "Video Monitor" },
    { 0x0F,  "Video Display and Loudspeaker" },
    { 0x10,  "Video Conferencing" },
    { 0x12,  "Gaming/Toy" },
    { 0, NULL }
};
value_string_ext bthci_cmd_cod_minor_device_class_audio_video_vals_ext = VALUE_STRING_EXT_INIT(bthci_cmd_cod_minor_device_class_audio_video_vals);

static const value_string bthci_cmd_cod_minor_device_class_peripheral_class_vals[] = {
    { 0x00,  "Not Keyboard / Not Pointing Device" },
    { 0x01,  "Keyboard" },
    { 0x02,  "Pointing device" },
    { 0x03,  "Combo keyboard/pointing device" },
    { 0, NULL }
};
value_string_ext bthci_cmd_cod_minor_device_class_peripheral_class_vals_ext = VALUE_STRING_EXT_INIT(bthci_cmd_cod_minor_device_class_peripheral_class_vals);

static const value_string bthci_cmd_cod_minor_device_class_peripheral_type_vals[] = {
    { 0x00,  "Uncategorized device" },
    { 0x01,  "Joystick" },
    { 0x02,  "Gamepad" },
    { 0x03,  "Remote control" },
    { 0x04,  "Sensing device" },
    { 0x05,  "Digitizer tablet" },
    { 0x06,  "Card Reader" },
    { 0x07,  "Digital Pen" },
    { 0x08,  "Handheld scanner for bar-codes" },
    { 0x09,  "Handheld gestural input device" },
    { 0, NULL }
};
value_string_ext bthci_cmd_cod_minor_device_class_peripheral_type_vals_ext = VALUE_STRING_EXT_INIT(bthci_cmd_cod_minor_device_class_peripheral_type_vals);


static const value_string bthci_cmd_cod_minor_device_class_imaging_type_vals[] = {
    { 0x00,  "Uncategorized, default" },
    { 0, NULL }
};
value_string_ext bthci_cmd_cod_minor_device_class_imaging_type_vals_ext = VALUE_STRING_EXT_INIT(bthci_cmd_cod_minor_device_class_imaging_type_vals);

static const value_string bthci_cmd_cod_minor_device_class_wearable_vals[] = {
    { 0x01,  "Wristwatch" },
    { 0x02,  "Pager" },
    { 0x03,  "Jacket" },
    { 0x04,  "Helmet" },
    { 0x05,  "Glasses" },
    { 0, NULL }
};
value_string_ext bthci_cmd_cod_minor_device_class_wearable_vals_ext = VALUE_STRING_EXT_INIT(bthci_cmd_cod_minor_device_class_wearable_vals);

static const value_string bthci_cmd_cod_minor_device_class_toy_vals[] = {
    { 0x01,  "Robot" },
    { 0x02,  "Vehicle" },
    { 0x03,  "Doll / Action figure" },
    { 0x04,  "Controller" },
    { 0x05,  "Game" },
    { 0, NULL }
};
value_string_ext bthci_cmd_cod_minor_device_class_toy_vals_ext = VALUE_STRING_EXT_INIT(bthci_cmd_cod_minor_device_class_toy_vals);

static const value_string bthci_cmd_cod_minor_device_class_health_vals[] = {
    { 0x00,  "Undefined" },
    { 0x01,  "Blood Pressure Monitor" },
    { 0x02,  "Thermometer" },
    { 0x03,  "Weighing Scale" },
    { 0x04,  "Glucose Meter" },
    { 0x05,  "Pulse Oximeter" },
    { 0x06,  "Heart/Pulse Rate Monitor" },
    { 0x07,  "Health Data Display" },
    { 0x08,  "Step Counter" },
    { 0x09,  "Body Composition Analyzer" },
    { 0x0A,  "Peak Flow Monitor" },
    { 0x0B,  "Medication Monitor" },
    { 0x0C,  "Knee Prosthesis" },
    { 0x0D,  "Ankle Prosthesis" },
    { 0x0E,  "Generic Health Manager" },
    { 0x0F,  "Personal Mobility Device" },
    { 0, NULL }
};
value_string_ext bthci_cmd_cod_minor_device_class_health_vals_ext = VALUE_STRING_EXT_INIT(bthci_cmd_cod_minor_device_class_health_vals);

static const value_string bthci_cmd_service_class_type_vals[] = {
    {0x1000, "Service Discovery Server Service"},
    {0x1001, "Browse Group Descriptor Service"},
    {0x1002, "Public Browse Group"},
    {0x1101, "Serial Port"},
    {0x1102, "LAN Access Using PPP"},
    {0x1103, "Dialup Networking"},
    {0x1104, "IrMC Sync"},
    {0x1105, "OBEX Object Push"},
    {0x1106, "OBEX File Transfer"},
    {0x1107, "IrMC Sync Command"},
    {0x1108, "Headset"},
    {0x1109, "Cordless Telephony"},
    {0x110A, "Audio Source"},
    {0x110B, "Audio Sink"},
    {0x110C, "A/V Remote Control Target"},
    {0x110D, "Advanced Audio Distribution"},
    {0x110E, "A/V Remote Control"},
    {0x110F, "Video Conferencing"},
    {0x1110, "Intercom"},
    {0x1111, "Fax"},
    {0x1112, "Headset Audio Gateway"},
    {0x1113, "WAP"},
    {0x1114, "WAP Client"},
    {0x1115, "PANU"},
    {0x1116, "NAP"},
    {0x1117, "GN"},
    {0x1118, "Direct Printing"},
    {0x1119, "Reference Printing"},
    {0x111A, "Imaging"},
    {0x111B, "Imaging Responder"},
    {0x111C, "Imaging Automatic Archive"},
    {0x111D, "Imaging Referenced Objects"},
    {0x111E, "Handsfree"},
    {0x111F, "Handsfree Audio Gateway"},
    {0x1120, "Direct Printing Reference Objects Service"},
    {0x1121, "Reflected UI"},
    {0x1122, "Basic Printing"},
    {0x1123, "Printing Status"},
    {0x1124, "Human Interface Device Service"},
    {0x1125, "Hardcopy Cable Replacement"},
    {0x1126, "HCR Print"},
    {0x1127, "HCR Scan"},
    {0x1128, "Common ISDN Access"},
    {0x1129, "Video Conferencing GW"},
    {0x112A, "UDI_MT"},
    {0x112B, "UDI_TA"},
    {0x112C, "Audio/Video"},
    {0x112D, "SIM Access"},
    {0x112E, "Phonebook Access - PCE"},
    {0x112F, "Phonebook Access - PSE"},
    {0x1130, "Phonebook Access"},
    {0x1200, "PnP Information"},
    {0x1201, "Generic Networking"},
    {0x1202, "Generic File Transfer"},
    {0x1203, "Generic Audio"},
    {0x1204, "Generic Telephony"},
    {0x1205, "UPNP Service"},
    {0x1206, "UPNP IP Service"},
    {0x1300, "ESDP_UPNP_IP_PAN"},
    {0x1301, "ESDP_UPNP_IP_LAP"},
    {0x1302, "ESDP_UPNP_L2CAP"},
    {0x1303, "Video Source"},
    {0x1304, "Video Sink"},
    {0x1305, "Video Distribution"},
    /* LE services */
    {0x1800, "Generic Access"},
    {0x1801, "Generic Attribute"},
    {0x1802, "Immediate Alert"},
    {0x1803, "Link Loss"},
    {0x1804, "Tx Power"},
    {0x1805, "Current Time"},
    {0x1806, "Reference Time Update"},
    {0x1807, "Next DST Change"},
    {0x1808, "Glucose"},
    {0x1809, "Health Thermometer"},
    {0x180a, "Device Information"},
    {0x180b, ""},
    {0x180c, ""},
    {0x180d, "Heart Rate"},
    {0x180e, "Phone Alert Status"},
    {0x180f, "Battery"},
    {0x1810, "Blood Pressure"},
    {0x1811, "Alert Notification"},
    {0x1812, "Human Interface Device"},
    {0x1813, "Scan Parameters"},
    {0x1814, "Running Speed and Cadence"},
    {0x1816, "Cycling Speed and Cadence"},
    {0, NULL}
};
value_string_ext bthci_cmd_service_class_type_vals_ext = VALUE_STRING_EXT_INIT(bthci_cmd_service_class_type_vals);

static const value_string bthci_cmd_eir_data_type_vals[] = {
    {0x01, "Flags" },
    {0x02, "16-bit Service Class UUIDs (incomplete)" },
    {0x03, "16-bit Service Class UUIDs" },
    {0x04, "32-bit Service Class UUIDs (incomplete)" },
    {0x05, "32-bit Service Class UUIDs" },
    {0x06, "128-bit Service Class UUIDs (incomplete)" },
    {0x07, "128-bit Service Class UUIDs" },
    {0x08, "Device Name (shortened)" },
    {0x09, "Device Name" },
    {0x0A, "Tx Power Level" },
    {0x0B, "OOB Optional Data Length" },
    {0x0C, "BD_ADDR" },
    {0x0D, "Class Of Device" },
    {0x0E, "Simple Pairing Hash C" },
    {0x0F, "Simple Pairing Randomizer R" },
    {0x10, "Device ID / Security Manager TK Value" },
    {0x11, "Security Manager Out of Band Flags" },
    {0x12, "Slave Connection Interval Range" },
    {0x14, "List of 16-bit Service Solicitation UUIDs" },
    {0x15, "List of 128-bit Service Solicitation UUIDs" },
    {0x16, "Service Data" },
    {0x17, "Public Target Address" },
    {0x18, "Random Target Address" },
    {0x19, "Appearance" },
    {0x1A, "Advertising Interval" },
    {0x3D, "3D Information Data" },
    {0xFF, "Manufacturer Specific" },
    {   0, NULL }
};
value_string_ext bthci_cmd_eir_data_type_vals_ext = VALUE_STRING_EXT_INIT(bthci_cmd_eir_data_type_vals);

static const value_string bthci_cmd_appearance_vals[] = {
    { 0x0000, "Unknown" },
    { 0x0040, "Generic Phone" },
    { 0x0080, "Generic Computer" },
    { 0x00C0, "Generic Watch" },
    { 0x00C1, "Sports Watch" },
    { 0x0100, "Generic Clock" },
    { 0x0140, "Generic Display" },
    { 0x0180, "Generic Remote Control" },
    { 0x01C0, "Generic Eye-glasses" },
    { 0x0200, "Generic Tag" },
    { 0x0240, "Generic Keyring" },
    { 0x0280, "Generic Media Player" },
    { 0x02C0, "Generic Barcode Scanner" },
    { 0x0300, "Generic Thermometer" },
    { 0x0301, "Ear Thermometer" },
    { 0x0340, "Generic Heart Rate Sensor" },
    { 0x0341, "Heart Rate Belt Sensor" },
    { 0x0380, "Generic Blood Pressure" },
    { 0x0381, "Arm Blood Pressure" },
    { 0x0382, "Wrist Blood Pressure" },
    { 0x03C0, "Human Interface Device (HID)" },
    { 0x03C1, "Keyboard" },
    { 0x03C2, "Mouse" },
    { 0x03C3, "Joystick" },
    { 0x03C4, "Gamepad" },
    { 0x03C5, "Digitizer Tablet" },
    { 0x03C6, "Card Reader" },
    { 0x03C7, "Digital Pen" },
    { 0x03C8, "Barcode Scanner" },
    { 0x0400, "Generic Glucose Meter" },
    { 0x0440, "Generic Running/Walking Sensor" },
    { 0x0441, "In-shoe Running/Walking Sensor" },
    { 0x0442, "On-shoe Running/Walking Sensor" },
    { 0x0443, "On-hip Running/Walking Sensor" },
    { 0x0480, "Generic Cycling Sensor" },
    { 0x0481, "Cycling Computer" },
    { 0x0482, "Cycling Speed Sensor" },
    { 0x0483, "Cycling Cadence Sensor" },
    { 0x0484, "Cycling Power Sensor" },
    { 0x0485, "Cycling Speed and Cadence Sensor" },
    { 0, NULL }
};
value_string_ext bthci_cmd_appearance_vals_ext = VALUE_STRING_EXT_INIT(bthci_cmd_appearance_vals);

const value_string bthci_cmd_io_capability_vals[] = {
    {0x00, "Display Only" },
    {0x01, "Display Yes/No" },
    {0x02, "Keyboard Only" },
    {0x03, "No Input, No Output" },
    {   0, NULL }
};

const value_string bthci_cmd_oob_data_present_vals[] = {
    {0x00, "OOB Authentication Data Not Present" },
    {0x01, "OOB Authentication Data From Remote Device Present" },
    {   0, NULL }
};

static const value_string bthci_cmd_auth_req_vals[] = {
    {0x00, "MITM Protection Not Required - No Bonding. Numeric Comparison, Automatic Accept Allowed" },
    {0x01, "MITM Protection Required - No Bonding. Use IO Capabilty To Determine Procedure" },
    {0x02, "MITM Protection Not Required - Dedicated Bonding. Numeric Comparison, Automatic Accept Allowed" },
    {0x03, "MITM Protection Required - Dedicated Bonding. Use IO Capabilty To Determine Procedure" },
    {0x04, "MITM Protection Not Required - General Bonding. Numeric Comparison, Automatic Accept Allowed" },
    {0x05, "MITM Protection Required - General Bonding. Use IO Capabilty To Determine Procedure" },
    {   0, NULL }
};
value_string_ext bthci_cmd_auth_req_vals_ext = VALUE_STRING_EXT_INIT(bthci_cmd_auth_req_vals);

const value_string bthci_cmd_address_types_vals[] = {
    { 0x00, "Public Device Address" },
    { 0x01, "Random Device Address" },
    { 0, NULL }
};

static const value_string cmd_role_vals[] = {
    {0x00, "Become Master"},
    {0x01, "Remain Slave"},
    {0, NULL }
};

static const value_string cmd_pin_types[] = {
    {0x00, "Variable PIN" },
    {0x01, "Fixed PIN" },
    {0, NULL }
};

static const value_string cmd_encryption_enable[] = {
    {0x00, "Link Level Encryption is OFF"},
    {0x01, "Link Level Encryption is ON"},
    {0, NULL }
};

static const value_string cmd_key_flag[] = {
    {0x00, "Using Semi-permanent Link Key"},
    {0x01, "Using Temporary Link Key"},
    {0, NULL }
};

static const value_string cmd_filter_types[] = {
    {0x00, "Clear all Filters" },
    {0x01, "Inquiry Result" },
    {0x02, "Connection Setup" },
    {0, NULL }
};

static const value_string cmd_inquiry_result_filter_condition_types[] = {
    {0x00, "A new device responded" },
    {0x01, "A device with the specified Class of Device responded" },
    {0x02, "A device with the specified BD_ADDR responded" },
    {0, NULL }
};

static const value_string cmd_service_types[] = {
    {0x00, "No Traffic"},
    {0x01, "Best Effort"},
    {0x02, "Guaranteed"},
    {0, NULL }
};

static const value_string cmd_connection_setup_filter_condition_types[] = {
    {0x00, "Allow Connections from all devices" },
    {0x01, "Allow Connections from a device with a specific Class of Device" },
    {0x02, "Allow Connections from a device with a specific BD_ADDR" },
    {0, NULL }
};

static const value_string cmd_auto_acc_flag_values[] = {
    {0x01, "Do NOT Auto accept" },
    {0x02, "Do Auto accept, role switch disabled" },
    {0x03, "Do Auto accept, role switch enabled" },
    {0, NULL }
};

static const value_string cmd_read_all_flag_values[] = {
    {0x00, "Return Link Key for specified BD_ADDR" },
    {0x01, "Return all stored Link Keys" },
    {0, NULL }
};

static const value_string cmd_delete_all_flag_values[] = {
    {0x00, "Delete only Link Key for specified BD_ADDR" },
    {0x01, "Delete all stored Link Keys" },
    {0, NULL }
};

const value_string bthci_cmd_scan_enable_values[] = {
    {0x00, "No Scans enabled" },
    {0x01, "Inquiry Scan enabled/Page Scan disable" },
    {0x02, "Inquiry Scan disabled/Page Scan enabled" },
    {0x03, "Inquiry Scan enabled/Page Scan enabled" },
    {0, NULL }
};

static const value_string cmd_authentication_enable_values[] = {
    {0x00, "Authentication disabled" },
    {0x01, "Authentication enabled for all connection" },
    {0, NULL }
};

static const value_string cmd_input_coding_values[] = {
    {0x0, "Linear" },
    {0x1, "\xb5-law" },
    {0x2, "A-law" },
    {0, NULL }
};
value_string_ext bthci_cmd_input_coding_vals_ext = VALUE_STRING_EXT_INIT(cmd_input_coding_values);

static const value_string cmd_input_data_format_values[] = {
    {0x0, "1's complement" },
    {0x1, "2's complement" },
    {0x2, "Sign-Magnitude" },
    {0x3, "Unsigned" },
    {0, NULL }
};
value_string_ext bthci_cmd_input_data_format_vals_ext = VALUE_STRING_EXT_INIT(cmd_input_data_format_values);

static const value_string cmd_input_sample_size_values[] = {
    {0x0, "8 bit (only for Linear PCM)" },
    {0x1, "16 bit (only for Linear PCM)" },
    {0, NULL }
};
value_string_ext bthci_cmd_input_sample_size_vals_ext = VALUE_STRING_EXT_INIT(cmd_input_sample_size_values);

static const value_string cmd_air_coding_format_values[] = {
    {0x0, "CVSD" },
    {0x1, "\xb5-law" },
    {0x2, "A-law" },
    {0x3, "Transparent" },
    {0, NULL }
};
value_string_ext bthci_cmd_air_coding_format_vals_ext = VALUE_STRING_EXT_INIT(cmd_air_coding_format_values);

static const value_string cmd_en_disabled[] = {
    {0x00, "disabled" },
    {0x01, "enabled" },
    {0, NULL }
};

static const value_string cmd_flow_contr_enable[] = {
    {0x00, "Flow control off in direction from Host Controller to Host." },
    {0x01, "ON - HCI ACL Data Packets / OFF - HCI SCO Data Packets" },
    {0x02, "OFF - HCI ACL Data Packets / ON - HCI SCO Data Packets" },
    {0x03, "ON - HCI ACL Data Packets / ON - HCI SCO Data Packets" },
    {0, NULL }
};

static const value_string cmd_power_level_types[] = {
    {0x00, "Current Tx Power Level" },
    {0x01, "Maximum Tx Power Level" },
    {0, NULL }
};

static const value_string cmd_loopback_modes[] = {
    {0x00, "No Loopback mode enabled" },
    {0x01, "Enable Local Loopback" },
    {0x02, "Enable Remote Loopback" },
    {0, NULL }
};

static const value_string cmd_encrypt_mode_vals[] = {
    { 0x00, "Encryption Disabled" },
    { 0x01, "Encryption only for Point-To-Point Packets" },
    { 0x02, "Encryption for Point-To-Point and Broadcast Packets" },
    { 0, NULL }
};

static const value_string cmd_boolean[] = {
    {0, "false" },
    {1, "true" },
    {0, NULL }
};

const value_string bthci_cmd_page_scan_modes[] = {
    {0, "Mandatory Page Scan Mode"},
    {1, "Optional Page Scan Mode I"},
    {2, "Optional Page Scan Mode II"},
    {3, "Optional Page Scan Mode III"},
    {0, NULL }
};

const value_string bthci_cmd_page_scan_repetition_modes[] = {
    {0, "R0"},
    {1, "R1"},
    {2, "R2"},
    {0, NULL }
};

const value_string bthci_cmd_page_scan_period_modes[] = {
    {0, "P0"},
    {1, "P1"},
    {2, "P2"},
    {0, NULL }
};

static const value_string cmd_role_switch_modes[] = {
    {0, "Local device will be master, and will not accept a master-slave switch request." },
    {1, "Local device may be master, or may become slave after accepting a master slave switch." },
    {0, NULL }
};

static const value_string cmd_rtx_effort[] = {
    {0x00, "No Retransmission" },
    {0x01, "At least 1 retransmission, optimize for power consumption" },
    {0x02, "At least 1 retransmission, optimize for link quality" },
    {0xFF, "Don't Care" },
    {   0, NULL }
};

static const value_string cmd_scan_types[] = {
    {0x00, "Standard Scan" },
    {0x01, "Interlaced Scan" },
    {   0, NULL }
};

static const value_string cmd_inq_modes[] = {
    {0x00, "Standard Results" },
    {0x01, "Results With RSSI" },
    {0x02, "Results With RSSI or Extended Results" },
    {   0, NULL }
};

static const value_string cmd_flush_pkt_type[] = {
    {0x00, "Automatically Flushable Only" },
    {   0, NULL }
};

static const value_string cmd_which_clock[] = {
    {0x00, "Local" },
    {0x01, "Piconet" },
    {   0, NULL }
};

const value_string bthci_cmd_notification_types[] = {
    {0x00, "Passkey Entry Started" },
    {0x01, "Passkey Digit Entered" },
    {0x02, "Passkey Digit Erased" },
    {0x03, "Passkey Cleared" },
    {0x04, "Passkey Entry Completed" },
    {   0, NULL }
};

static const value_string bthci_cmd_amp_key_type[] = {
  {0x03, "Debug Combination Key" },
  {0x04, "Authenticated Combination Key" },
  {0x05, "Unauthenticated Combination Key" },
  {   0, NULL }
};

static const value_string cmd_flow_spec_servicetype[] = {
    { 0x00, "No traffic" },
    { 0x01, "Best effort (Default)" },
    { 0x02, "Guaranteed" },
    { 0, NULL }
};

static const value_string  cmd_flow_ctrl_mode[] = {
    { 0x00, "Packet based" },
    { 0x01, "Data Block based" },
    { 0, NULL }
};

static const value_string cmd_le_advertising_types[] = {
    { 0x00, "Connectable Unidirected Advertising" },
    { 0x01, "Connectable Directed Advertising" },
    { 0x02, "Scannable Unidirected Advertising" },
    { 0x03, "Non-Connectable Unidirected Advertising" },
    { 0, NULL }
};

static const value_string cmd_le_advertising_filter_policy[] = {
    { 0x00, "Allow Scan Req from Any, Allow Connect Req from Any" },
    { 0x01, "Allow Scan Req from White List Only, Allow Connect Req from Any" },
    { 0x02, "Allow Scan Req from Any, Allow Connect Req from White List Only" },
    { 0x03, "Allow Scan Req from White List Only, Allow Connect Req from White List Only." },
    { 0, NULL }
};

static const value_string cmd_le_scan_types[] = {
    { 0x00, "Passive" },
    { 0x01, "Active" },
    { 0, NULL }
};

static const value_string cmd_le_scan_filter_policy[] = {
    { 0x00, "Accept all advertisments. Ignore directed advertisements not addresed to this device" },
    { 0x01, "Ignore advertisments from devices not in the white list only. Ignore directed advertisements not addresed to this device" },
    { 0, NULL }
};

static const value_string cmd_init_filter_policy[] = {
    { 0x00, "Use Peer Address" },
    { 0x01, "Use White List. Ignore Peer Address" },
    { 0, NULL }
};

static const value_string cmd_le_test_pkt_payload[] = {
    { 0x00, "Pseudo-Random Sequence 9" },
    { 0x01, "Pattern Of Alternating Bits '11110000'" },
    { 0x02, "Pattern Of Alternating Bits '10101010'" },
    { 0x03, "Pseudo-Random Sequence 15" },
    { 0x04, "Pattern Of All '1' bits" },
    { 0x05, "Pattern Of All '0' bits" },
    { 0x06, "Pattern Of Alternating Bits '00001111'" },
    { 0x07, "Pattern Of Alternating Bits '0101'" },
    { 0, NULL }
};

void proto_register_bthci_cmd(void);
void proto_reg_handoff_bthci_cmd(void);

static int
dissect_bthci_cmd_bd_addr(tvbuff_t *tvb, int offset, packet_info *pinfo _U_, proto_tree *tree)
{
    guint8 bd_addr[6];

    bd_addr[5] = tvb_get_guint8(tvb, offset);
    bd_addr[4] = tvb_get_guint8(tvb, offset + 1);
    bd_addr[3] = tvb_get_guint8(tvb, offset + 2);
    bd_addr[2] = tvb_get_guint8(tvb, offset + 3);
    bd_addr[1] = tvb_get_guint8(tvb, offset + 4);
    bd_addr[0] = tvb_get_guint8(tvb, offset + 5);

    proto_tree_add_ether(tree, hf_bthci_cmd_bd_addr, tvb, offset, 6, bd_addr);
    offset += 6;

    return offset;
}

static int
dissect_bthci_cmd_cod(tvbuff_t *tvb, int offset, packet_info *pinfo _U_, proto_tree *tree)
{
    guint16      major_service_classes;
    guint8       major_device_class;
    guint8       minor_device_class;
    const gchar *minor_device_class_name;
    proto_item  *cod_item;
    proto_item  *cod_tree;

    cod_item = proto_tree_add_item(tree, hf_bthci_cmd_class_of_device, tvb, offset, 3, ENC_LITTLE_ENDIAN);
    cod_tree = proto_item_add_subtree(cod_item, ett_cod);

    major_device_class = tvb_get_guint8(tvb, offset + 1) & 0x1F;
    minor_device_class = tvb_get_guint8(tvb, offset) >> 2;

    switch(major_device_class) {
    case 0x01: /* Computer */
        proto_tree_add_item(cod_tree, hf_bthci_cmd_cod_minor_device_class_computer, tvb, offset, 1, ENC_LITTLE_ENDIAN);
        minor_device_class_name = val_to_str_ext_const(minor_device_class, &bthci_cmd_cod_minor_device_class_computer_vals_ext, "Unknown");
        break;
    case 0x02: /* Phone */
        proto_tree_add_item(cod_tree, hf_bthci_cmd_cod_minor_device_class_phone, tvb, offset, 1, ENC_LITTLE_ENDIAN);
        minor_device_class_name = val_to_str_ext_const(minor_device_class, &bthci_cmd_cod_minor_device_class_phone_vals_ext, "Unknown");
        break;
    case 0x03: /* LAN/Network Access Point */
        proto_tree_add_item(cod_tree, hf_bthci_cmd_cod_minor_device_class_lan_net_load_factor, tvb, offset, 1, ENC_LITTLE_ENDIAN);
        proto_tree_add_item(cod_tree, hf_bthci_cmd_cod_minor_device_class_lan_net_type, tvb, offset, 1, ENC_LITTLE_ENDIAN);
        minor_device_class_name = val_to_str_ext_const(minor_device_class, &bthci_cmd_cod_minor_device_class_lan_net_load_factor_vals_ext, "Unknown");
        break;
    case 0x04: /* Audio/Video */
        proto_tree_add_item(cod_tree, hf_bthci_cmd_cod_minor_device_class_audio_video, tvb, offset, 1, ENC_LITTLE_ENDIAN);
        minor_device_class_name = val_to_str_ext_const(minor_device_class, &bthci_cmd_cod_minor_device_class_audio_video_vals_ext, "Unknown");
        break;
    case 0x05: /* Peripheral */
        proto_tree_add_item(cod_tree, hf_bthci_cmd_cod_minor_device_class_peripheral_class, tvb, offset, 1, ENC_LITTLE_ENDIAN);
        proto_tree_add_item(cod_tree, hf_bthci_cmd_cod_minor_device_class_peripheral_type, tvb, offset, 1, ENC_LITTLE_ENDIAN);
        minor_device_class_name = val_to_str_ext_const(minor_device_class, &bthci_cmd_cod_minor_device_class_peripheral_class_vals_ext, "Unknown");
        break;
    case 0x06: /* Imaging */
        proto_tree_add_item(cod_tree, hf_bthci_cmd_cod_minor_device_class_imaging_class_printer, tvb, offset, 1, ENC_LITTLE_ENDIAN);
        proto_tree_add_item(cod_tree, hf_bthci_cmd_cod_minor_device_class_imaging_class_scanner, tvb, offset, 1, ENC_LITTLE_ENDIAN);
        proto_tree_add_item(cod_tree, hf_bthci_cmd_cod_minor_device_class_imaging_class_camera, tvb, offset, 1, ENC_LITTLE_ENDIAN);
        proto_tree_add_item(cod_tree, hf_bthci_cmd_cod_minor_device_class_imaging_class_display, tvb, offset, 1, ENC_LITTLE_ENDIAN);

        proto_tree_add_item(cod_tree, hf_bthci_cmd_cod_minor_device_class_imaging_type, tvb, offset, 1, ENC_LITTLE_ENDIAN);
        minor_device_class_name = val_to_str_ext_const(minor_device_class, &bthci_cmd_cod_minor_device_class_imaging_type_vals_ext, "Unknown");
        break;
    case 0x07: /* Wearable */
        proto_tree_add_item(cod_tree, hf_bthci_cmd_cod_minor_device_class_wearable, tvb, offset, 1, ENC_LITTLE_ENDIAN);
        minor_device_class_name = val_to_str_ext_const(minor_device_class, &bthci_cmd_cod_minor_device_class_wearable_vals_ext, "Unknown");
        break;
    case 0x08: /* Toy */
        proto_tree_add_item(cod_tree, hf_bthci_cmd_cod_minor_device_class_toy, tvb, offset, 1, ENC_LITTLE_ENDIAN);
        minor_device_class_name = val_to_str_ext_const(minor_device_class, &bthci_cmd_cod_minor_device_class_toy_vals_ext, "Unknown");
        break;
    case 0x09: /* Health */
        proto_tree_add_item(cod_tree, hf_bthci_cmd_cod_minor_device_class_health, tvb, offset, 1, ENC_LITTLE_ENDIAN);
        minor_device_class_name = val_to_str_ext_const(minor_device_class, &bthci_cmd_cod_minor_device_class_health_vals_ext, "Unknown");
        break;
    default:
        minor_device_class_name = "Unknown";
        proto_tree_add_item(cod_tree, hf_bthci_cmd_cod_minor_device_class_unknown, tvb, offset, 1, ENC_LITTLE_ENDIAN);
    }

    proto_tree_add_item(cod_tree, hf_bthci_cmd_cod_format_type, tvb, offset, 1, ENC_LITTLE_ENDIAN);
    offset += 1;

    proto_tree_add_item(cod_tree, hf_bthci_cmd_cod_major_service_class_information, tvb, offset, 2, ENC_LITTLE_ENDIAN);
    proto_tree_add_item(cod_tree, hf_bthci_cmd_cod_major_service_class_telephony, tvb, offset, 2, ENC_LITTLE_ENDIAN);
    proto_tree_add_item(cod_tree, hf_bthci_cmd_cod_major_service_class_audio, tvb, offset, 2, ENC_LITTLE_ENDIAN);
    proto_tree_add_item(cod_tree, hf_bthci_cmd_cod_major_service_class_object_transfer, tvb, offset, 2, ENC_LITTLE_ENDIAN);
    proto_tree_add_item(cod_tree, hf_bthci_cmd_cod_major_service_class_capturing, tvb, offset, 2, ENC_LITTLE_ENDIAN);
    proto_tree_add_item(cod_tree, hf_bthci_cmd_cod_major_service_class_rendering, tvb, offset, 2, ENC_LITTLE_ENDIAN);
    proto_tree_add_item(cod_tree, hf_bthci_cmd_cod_major_service_class_networking, tvb, offset, 2, ENC_LITTLE_ENDIAN);
    proto_tree_add_item(cod_tree, hf_bthci_cmd_cod_major_service_class_positioning, tvb, offset, 2, ENC_LITTLE_ENDIAN);
    proto_tree_add_item(cod_tree, hf_bthci_cmd_cod_major_service_class_reserved, tvb, offset, 2, ENC_LITTLE_ENDIAN);
    proto_tree_add_item(cod_tree, hf_bthci_cmd_cod_major_service_class_limited_discoverable_mode, tvb, offset, 2, ENC_LITTLE_ENDIAN);
    major_service_classes = tvb_get_letohs(tvb, offset) >> 5;

    proto_tree_add_item(cod_tree, hf_bthci_cmd_cod_major_device_class, tvb, offset, 2, ENC_LITTLE_ENDIAN);
    offset += 2;

    proto_item_append_text(cod_item, " (%s:%s - services:",
            val_to_str_ext_const(major_device_class, &bthci_cmd_cod_major_device_class_vals_ext, "Unknown"),
            minor_device_class_name);

    if (major_service_classes & 0x001) proto_item_append_text(cod_item, " LimitedDiscoverableMode");
    if (major_service_classes & 0x008) proto_item_append_text(cod_item, " Positioning");
    if (major_service_classes & 0x010) proto_item_append_text(cod_item, " Networking");

    if (major_service_classes & 0x020) proto_item_append_text(cod_item, " Rendering");
    if (major_service_classes & 0x040) proto_item_append_text(cod_item, " Capturing");
    if (major_service_classes & 0x080) proto_item_append_text(cod_item, " ObjectTransfer");
    if (major_service_classes & 0x100) proto_item_append_text(cod_item, " Audio");
    if (major_service_classes & 0x200) proto_item_append_text(cod_item, " Telephony");
    if (major_service_classes & 0x400) proto_item_append_text(cod_item, " Information");

    proto_item_append_text(cod_item, ")");

    return offset;
}

static int
dissect_bthci_cmd_cod_mask(tvbuff_t *tvb, int offset, packet_info *pinfo _U_, proto_tree *tree)
{
    proto_item  *cod_mask_item;
    proto_item  *cod_mask_tree;

    cod_mask_item = proto_tree_add_item(tree, hf_bthci_cmd_class_of_device_mask, tvb, offset, 3, ENC_LITTLE_ENDIAN);
    cod_mask_tree = proto_item_add_subtree(cod_mask_item, ett_cod_mask);

    proto_tree_add_item(cod_mask_tree, hf_bthci_cmd_cod_minor_device_class_mask, tvb, offset, 1, ENC_LITTLE_ENDIAN);
    proto_tree_add_item(cod_mask_tree, hf_bthci_cmd_cod_format_type_mask, tvb, offset, 1, ENC_LITTLE_ENDIAN);
    offset += 1;

    proto_tree_add_item(cod_mask_tree, hf_bthci_cmd_cod_major_service_class_information_mask, tvb, offset, 2, ENC_LITTLE_ENDIAN);
    proto_tree_add_item(cod_mask_tree, hf_bthci_cmd_cod_major_service_class_telephony_mask, tvb, offset, 2, ENC_LITTLE_ENDIAN);
    proto_tree_add_item(cod_mask_tree, hf_bthci_cmd_cod_major_service_class_audio_mask, tvb, offset, 2, ENC_LITTLE_ENDIAN);
    proto_tree_add_item(cod_mask_tree, hf_bthci_cmd_cod_major_service_class_object_transfer_mask, tvb, offset, 2, ENC_LITTLE_ENDIAN);
    proto_tree_add_item(cod_mask_tree, hf_bthci_cmd_cod_major_service_class_capturing_mask, tvb, offset, 2, ENC_LITTLE_ENDIAN);
    proto_tree_add_item(cod_mask_tree, hf_bthci_cmd_cod_major_service_class_rendering_mask, tvb, offset, 2, ENC_LITTLE_ENDIAN);
    proto_tree_add_item(cod_mask_tree, hf_bthci_cmd_cod_major_service_class_networking_mask, tvb, offset, 2, ENC_LITTLE_ENDIAN);
    proto_tree_add_item(cod_mask_tree, hf_bthci_cmd_cod_major_service_class_positioning_mask, tvb, offset, 2, ENC_LITTLE_ENDIAN);
    proto_tree_add_item(cod_mask_tree, hf_bthci_cmd_cod_major_service_class_reserved_mask, tvb, offset, 2, ENC_LITTLE_ENDIAN);
    proto_tree_add_item(cod_mask_tree, hf_bthci_cmd_cod_major_service_class_limited_discoverable_mode_mask, tvb, offset, 2, ENC_LITTLE_ENDIAN);

    proto_tree_add_item(cod_mask_tree, hf_bthci_cmd_cod_major_device_class_mask, tvb, offset, 2, ENC_LITTLE_ENDIAN);
    offset += 2;

    return offset;
}

static int
dissect_bthci_eir_ad_data(tvbuff_t *tvb, int offset, packet_info *pinfo, proto_tree *tree, guint8 size)
{
    guint8 length, type, data_size = size;
    guint16 i, j;
    proto_item *item, *ti_data = NULL;
    proto_tree *ti_data_subtree = NULL;
    proto_item  *sub_item;

    if (tree) {
        ti_data = proto_tree_add_item(tree, (size == 240) ? hf_extended_inquiry_response_data : hf_advertising_data,
                tvb, offset, data_size, ENC_NA);
        ti_data_subtree = proto_item_add_subtree(ti_data, ett_eir_subtree);
    }

    i=0;
    while (i < data_size) {
        length = tvb_get_guint8(tvb, offset + i);
        if (length != 0) {

            proto_item *ti_data_struct;
            proto_tree *ti_data_struct_subtree;

            type = tvb_get_guint8(tvb, offset + i + 1);

            ti_data_struct = proto_tree_add_none_format(ti_data_subtree, hf_eir_ad_item, tvb, offset + i, length + 1, "%s",
                    val_to_str_const(type, bthci_cmd_eir_data_type_vals, "Unknown"));
            ti_data_struct_subtree = proto_item_add_subtree(ti_data_struct, ett_eir_struct_subtree);

            proto_tree_add_item(ti_data_struct_subtree, hf_bthci_cmd_eir_struct_length, tvb, offset + i, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(ti_data_struct_subtree, hf_bthci_cmd_eir_struct_type, tvb, offset + i + 1, 1, ENC_LITTLE_ENDIAN);

            switch (type) {
                case 0x01: /* flags */
                    if (length > 1)
                    {
                        proto_tree_add_item(ti_data_struct_subtree, hf_bthci_cmd_flags_limited_disc_mode, tvb, offset+i+2, 1, ENC_LITTLE_ENDIAN);
                        proto_tree_add_item(ti_data_struct_subtree, hf_bthci_cmd_flags_general_disc_mode, tvb, offset+i+2, 1, ENC_LITTLE_ENDIAN);
                        proto_tree_add_item(ti_data_struct_subtree, hf_bthci_cmd_flags_bredr_not_support, tvb, offset+i+2, 1, ENC_LITTLE_ENDIAN);
                        proto_tree_add_item(ti_data_struct_subtree, hf_bthci_cmd_flags_le_bredr_support_ctrl, tvb, offset+i+2, 1, ENC_LITTLE_ENDIAN);
                        proto_tree_add_item(ti_data_struct_subtree, hf_bthci_cmd_flags_le_bredr_support_host, tvb, offset+i+2, 1, ENC_LITTLE_ENDIAN);
                    }
                    break;
                case 0x02: /* 16-bit Service Class UUIDs, incomplete list */
                case 0x03: /* 16-bit Service Class UUIDs, complete list */
                case 0x14: /* 16-bit Service Solicitation UUIDs */
                    j=0;
                    while(j<(length-1))
                    {
                        proto_tree_add_item(ti_data_struct_subtree, hf_bthci_cmd_sc_uuid16, tvb, offset+i+j+2, 2, ENC_LITTLE_ENDIAN);
                        j+=2;
                    }
                    break;
                case 0x04: /* 32-bit Service Class UUIDs, incomplete list */
                case 0x05: /* 32-bit Service Class UUIDs, complete list */
                    j=0;
                    while(j<(length-1))
                    {
                        proto_tree_add_item(ti_data_struct_subtree, hf_bthci_cmd_sc_uuid32, tvb, offset+i+j+2, 4, ENC_LITTLE_ENDIAN);
                        j+=4;
                    }
                    break;
                case 0x06: /* 128-bit Service Class UUIDs, incomplete list */
                case 0x07: /* 128-bit Service Class UUIDs, complete list */
                case 0x15: /* 128-bit Service Solicitation UUIDs */
                    j=0;
                    while(j<(length-1))
                    {
                        proto_tree_add_item(ti_data_struct_subtree, hf_bthci_cmd_sc_uuid128, tvb, offset+i+j+2, 16, ENC_NA);
                        j+=16;
                    }
                    break;
                case 0x08: /* Device Name, shortened */
                case 0x09: /* Device Name, full */
                    proto_tree_add_item(ti_data_struct_subtree, hf_bthci_cmd_device_name, tvb, offset+i+2, length-1, ENC_ASCII|ENC_NA);
                    proto_item_append_text(ti_data_struct,": %s", tvb_format_text(tvb,offset+i+2,length-1));
                    break;
                case 0x0A: /* Tx Power Level */
                    proto_tree_add_item(ti_data_struct_subtree, hf_bthci_cmd_tx_power, tvb, offset+i+2, 1, ENC_LITTLE_ENDIAN);
                    break;
                case 0x0B: /* OOB Optional Data Length */
                    /* From CSS v3.pdf */
                    proto_tree_add_item(ti_data_struct_subtree, hf_bthci_cmd_eir_ad_ssp_oob_length, tvb, offset + i + 2, 2, ENC_LITTLE_ENDIAN);
                    break;
                case 0x0C: /* BD_ADDR */
                    /* From CSS v3.pdf */
                    dissect_bthci_cmd_bd_addr(tvb, offset + i + 2, pinfo, tree);
                    break;
                case 0x0D: /* Class of Device */
                    dissect_bthci_cmd_cod(tvb, offset+i+2, pinfo, ti_data_struct_subtree);
                    break;
                case 0x0E: /* Simple Pairing Hash C */
                    proto_tree_add_item(ti_data_struct_subtree, hf_bthci_cmd_hash_c, tvb, offset+i+2, 16, ENC_NA);
                    break;
                case 0x0F: /* Simple Pairing Randomizer R */
                    proto_tree_add_item(ti_data_struct_subtree, hf_bthci_cmd_randomizer_r, tvb, offset + i + 2, 16, ENC_NA);
                    break;
                case 0x10: /* Device ID / Security Manager TK Value */
#if 0
/* XXX: Need to know how to check (or is it possible) that is le_physical_channel or not */
                    if (le_physical_channel) { /* Security Manager TK Value - Value as used in pairing over LE Physical channel. */
                        sub_item = proto_tree_add_item(ti_data_struct_subtree, hf_bthci_cmd_eir_data, tvb, offset + i + 2, 16, ENC_NA);
                        expert_add_info(pinfo, sub_item, &ei_eir_undecoded);
                    }
                    break;
#endif
                    {
                    /* DID */
                    guint16       vendor_id_source;
                    guint16       vendor_id;
                    guint16       product_id;
                    const gchar  *str_val;

                    proto_tree_add_item(ti_data_struct_subtree, hf_did_vendor_id_source, tvb, offset + i + 2, 2, ENC_LITTLE_ENDIAN);
                    vendor_id_source = tvb_get_letohs(tvb, offset + i + 2);

                    if (vendor_id_source == DID_VENDOR_ID_SOURCE_BLUETOOTH_SIG) {
                        proto_tree_add_item(ti_data_struct_subtree, hf_did_vendor_id_bluetooth_sig, tvb, offset + i + 2 + 2, 2, ENC_LITTLE_ENDIAN);
                    } else if (vendor_id_source == DID_VENDOR_ID_SOURCE_USB_FORUM) {
                        proto_tree_add_item(ti_data_struct_subtree, hf_did_vendor_id_usb_forum, tvb, offset + i + 2 + 2, 2, ENC_LITTLE_ENDIAN);
                    } else {
                        proto_tree_add_item(ti_data_struct_subtree, hf_did_vendor_id, tvb, offset + i + 2 + 2, 2, ENC_LITTLE_ENDIAN);
                    }
                    vendor_id = tvb_get_letohs(tvb, offset + i + 2 + 2);

                    sub_item = proto_tree_add_item(ti_data_struct_subtree, hf_did_product_id, tvb, offset + i + 2 + 4, 2, ENC_LITTLE_ENDIAN);
                    product_id = tvb_get_letohs(tvb, offset + i + 2 + 4);

                    if (vendor_id_source == DID_VENDOR_ID_SOURCE_USB_FORUM) {
                        str_val = val_to_str_ext_const(vendor_id << 16 | product_id, &ext_usb_products_vals, "Unknown");
                        proto_item_append_text(sub_item, " (%s)", str_val);
                    }

                    proto_tree_add_item(ti_data_struct_subtree, hf_did_version, tvb, offset + i + 2 + 6, 2, ENC_LITTLE_ENDIAN);
                    }
                    break;
                case 0x11: /* Security Manager OOB Flags */
                    proto_tree_add_item(ti_data_struct_subtree, hf_bthci_cmd_flags_le_oob_data_present, tvb, offset+i+2, 1, ENC_LITTLE_ENDIAN);
                    proto_tree_add_item(ti_data_struct_subtree, hf_bthci_cmd_flags_le_oob_le_supported_host, tvb, offset+i+2, 1, ENC_LITTLE_ENDIAN);
                    proto_tree_add_item(ti_data_struct_subtree, hf_bthci_cmd_flags_le_oob_le_bredr_support, tvb, offset+i+2, 1, ENC_LITTLE_ENDIAN);
                    proto_tree_add_item(ti_data_struct_subtree, hf_bthci_cmd_flags_le_oob_address_type, tvb, offset+i+2, 1, ENC_LITTLE_ENDIAN);
                    break;
                case 0x12: /* Slave Connection Interval Range */
                    item = proto_tree_add_item(tree, hf_bthci_cmd_le_con_interval_min, tvb, offset+i+2, 2, ENC_LITTLE_ENDIAN);
                    proto_item_append_text(item, " (%g msec)",  tvb_get_letohs(tvb, offset+i+2)*1.25);
                    item = proto_tree_add_item(tree, hf_bthci_cmd_le_con_interval_max, tvb, offset+i+4, 2, ENC_LITTLE_ENDIAN);
                    proto_item_append_text(item, " (%g msec)",  tvb_get_letohs(tvb, offset+i+4)*1.25);
                    proto_item_append_text(ti_data_struct,": %g - %g msec", tvb_get_letohs(tvb, offset+i+2)*1.25, tvb_get_letohs(tvb, offset+i+4)*1.25);
                    break;
                case 0x16: /* Service Data */
                    proto_tree_add_item(ti_data_struct_subtree, hf_bthci_cmd_sc_uuid16, tvb, offset+i+2, 2, ENC_LITTLE_ENDIAN);
                    break;
                case 0x17: /* Public Target Address */
                case 0x18: /* Random Target Address */
                {
                    j=0;
                    while(j<(length-1))
                    {
                        dissect_bthci_cmd_bd_addr(tvb, offset+i+j+2, pinfo, ti_data_struct_subtree);
                        j+=6;
                    }
                    break;
                }
                case 0x19: /* Appearance */
                {
                    guint16 appearance = tvb_get_letohs(tvb, offset+i+2);
                    proto_tree_add_item(ti_data_struct_subtree, hf_bthci_cmd_appearance, tvb, offset+i+2, 2, ENC_LITTLE_ENDIAN);
                    proto_item_append_text(ti_data_struct,": %s", val_to_str(appearance, bthci_cmd_appearance_vals, "Unknown"));
                    break;
                }
                case 0x1A: /* Advertising Interval */
                    /* From CSS v3.pdf */
                    sub_item = proto_tree_add_item(ti_data_struct_subtree, hf_bthci_cmd_eir_ad_advertising_interval, tvb, offset + i + 2, 2, ENC_LITTLE_ENDIAN);
                    proto_item_append_text(sub_item, " (%g msec)", tvb_get_letohs(tvb, offset + i + 2) * 0.625);
                    break;
                case 0x3D: /* 3D Information Data */
                    proto_tree_add_item(ti_data_struct_subtree, hf_3ds_factory_test_mode, tvb, offset + i + 2, 1, ENC_LITTLE_ENDIAN);
                    proto_tree_add_item(ti_data_struct_subtree, hf_3ds_reserved, tvb, offset + i + 2, 1, ENC_LITTLE_ENDIAN);
                    proto_tree_add_item(ti_data_struct_subtree, hf_3ds_send_battery_level_report_on_startup, tvb, offset + i + 2, 1, ENC_LITTLE_ENDIAN);
                    proto_tree_add_item(ti_data_struct_subtree, hf_3ds_battery_level_reporting, tvb, offset + i + 2, 1, ENC_LITTLE_ENDIAN);
                    proto_tree_add_item(ti_data_struct_subtree, hf_3ds_association_notification, tvb, offset + i + 2, 1, ENC_LITTLE_ENDIAN);

                    proto_tree_add_item(ti_data_struct_subtree, hf_3ds_path_loss_threshold, tvb, offset + i + 2 + 1, 1, ENC_LITTLE_ENDIAN);

                    break;
                case 0xFF: /* Manufacturer Specific */ {
                    guint16  company_id;

                    proto_tree_add_item(ti_data_struct_subtree, hf_bthci_cmd_eir_ad_company_id, tvb, offset + i + 2, 2, ENC_LITTLE_ENDIAN);
                    company_id = tvb_get_letohs(tvb, offset + i + 2);
                    if (company_id == 0x000F && tvb_get_guint8(tvb, offset + i + 2 + 2) == 0) { /* 3DS profile Legacy Devices */
                        proto_tree_add_item(ti_data_struct_subtree, hf_3ds_legacy_fixed, tvb, offset + i + 2 + 2, 1, ENC_LITTLE_ENDIAN);

                        proto_tree_add_item(ti_data_struct_subtree, hf_3ds_legacy_3d_capable_tv, tvb, offset + i + 2 + 3, 1, ENC_LITTLE_ENDIAN);
                        proto_tree_add_item(ti_data_struct_subtree, hf_3ds_legacy_ignored_1_3, tvb, offset + i + 2 + 3, 1, ENC_LITTLE_ENDIAN);
                        proto_tree_add_item(ti_data_struct_subtree, hf_3ds_legacy_fixed_4, tvb, offset + i + 2 + 3, 1, ENC_LITTLE_ENDIAN);
                        proto_tree_add_item(ti_data_struct_subtree, hf_3ds_legacy_ignored_5, tvb, offset + i + 2 + 3, 1, ENC_LITTLE_ENDIAN);
                        proto_tree_add_item(ti_data_struct_subtree, hf_3ds_legacy_fixed_6, tvb, offset + i + 2 + 3, 1, ENC_LITTLE_ENDIAN);
                        proto_tree_add_item(ti_data_struct_subtree, hf_3ds_legacy_test_mode, tvb, offset + i + 2 + 3, 1, ENC_LITTLE_ENDIAN);

                        proto_tree_add_item(ti_data_struct_subtree, hf_3ds_legacy_path_loss_threshold, tvb, offset + i + 2 + 4, 1, ENC_LITTLE_ENDIAN);
                    } else {
                        sub_item = proto_tree_add_item(ti_data_struct_subtree, hf_bthci_cmd_eir_data, tvb, offset + i + 2, length - 1, ENC_NA);
                        expert_add_info(pinfo, sub_item, &ei_eir_undecoded);
                    }
                    }
                    break;
                default:
                    sub_item = proto_tree_add_item(ti_data_struct_subtree, hf_bthci_cmd_eir_data, tvb, offset + i + 2, length - 1, ENC_NA);
                    expert_add_info(pinfo, sub_item, &ei_eir_unknown);
                    break;
            }
            i += length+1;
        }
        else {
            break;
        }
    }

    return offset+data_size;
}

static int
dissect_bthci_cmd_flow_spec(tvbuff_t *tvb, int offset, packet_info *pinfo _U_, proto_tree *tree, gboolean tx)
{
    proto_item *ti_flow_spec;
    proto_tree *ti_flow_spec_subtree;

    ti_flow_spec = proto_tree_add_none_format(tree, hf_bthci_cmd_flow_spec, tvb, offset, 16, tx?"Tx Flow Spec ":"Rx Flow Spec");
    ti_flow_spec_subtree = proto_item_add_subtree(ti_flow_spec, ett_flow_spec_subtree);

    proto_tree_add_item(ti_flow_spec_subtree, hf_bthci_cmd_flow_spec_identifier, tvb, offset, 1, ENC_LITTLE_ENDIAN);
    offset++;
    proto_tree_add_item(ti_flow_spec_subtree, hf_bthci_cmd_flow_spec_service_type, tvb, offset, 1, ENC_LITTLE_ENDIAN);
    offset++;
    proto_tree_add_item(ti_flow_spec_subtree, hf_bthci_cmd_flow_spec_sdu_size, tvb, offset, 2, ENC_LITTLE_ENDIAN);
    offset+=2;
    proto_tree_add_item(ti_flow_spec_subtree, hf_bthci_cmd_flow_spec_sdu_arrival_time, tvb, offset, 4, ENC_LITTLE_ENDIAN);
    offset+=4;
    proto_tree_add_item(ti_flow_spec_subtree, hf_bthci_cmd_flow_spec_access_latency, tvb, offset, 4, ENC_LITTLE_ENDIAN);
    offset+=4;
    proto_tree_add_item(ti_flow_spec_subtree, hf_bthci_cmd_flush_to_us, tvb, offset, 4, ENC_LITTLE_ENDIAN);
    offset+=4;

    return offset;
}

static int
dissect_link_control_cmd(tvbuff_t *tvb, int offset, packet_info *pinfo, proto_tree *tree, guint16 cmd_ocf)
{
    proto_item *item;
    guint32     clock_value;

    switch (cmd_ocf) {
        case 0x0001: /* Inquiry */
            proto_tree_add_item(tree, hf_bthci_cmd_lap, tvb, offset, 3, ENC_LITTLE_ENDIAN);
            offset+=3;
            item = proto_tree_add_item(tree, hf_bthci_cmd_inq_length, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            proto_item_append_text(item, " (%g sec)", 1.28*tvb_get_guint8(tvb, offset));
            offset++;
            proto_tree_add_item(tree, hf_bthci_cmd_num_responses, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            break;

        case 0x0003: /* Periodic Inquiry Mode */
            item = proto_tree_add_item(tree, hf_bthci_cmd_max_period_length, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_item_append_text(item, " (%g sec)", 1.28*tvb_get_letohs(tvb, offset));
            offset+=2;
            item = proto_tree_add_item(tree, hf_bthci_cmd_min_period_length, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_item_append_text(item, " (%g sec)", 1.28*tvb_get_letohs(tvb, offset));
            offset+=2;
            proto_tree_add_item(tree, hf_bthci_cmd_lap, tvb, offset, 3, ENC_LITTLE_ENDIAN);
            offset+=3;
            item = proto_tree_add_item(tree, hf_bthci_cmd_inq_length, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            proto_item_append_text(item, " (%g sec)", 1.28*tvb_get_guint8(tvb, offset));
            offset++;
            proto_tree_add_item(tree, hf_bthci_cmd_num_responses, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            break;

        case 0x0005: /* Create Connection */
            offset = dissect_bthci_cmd_bd_addr(tvb, offset, pinfo, tree);

            proto_tree_add_item(tree, hf_bthci_cmd_packet_type_2dh1, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_packet_type_3dh1, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_packet_type_dm1, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_packet_type_dh1, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_packet_type_2dh3, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_packet_type_3dh3, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_packet_type_dm3, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_packet_type_dh3, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_packet_type_2dh5, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_packet_type_3dh5, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_packet_type_dm5, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_packet_type_dh5, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            offset+=2;

            proto_tree_add_item(tree, hf_bthci_cmd_page_scan_repetition_mode, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;

            proto_tree_add_item(tree, hf_bthci_cmd_page_scan_mode, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;

            item = proto_tree_add_item(tree, hf_bthci_cmd_clock_offset, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            clock_value = tvb_get_letohs(tvb, 13) & 32767; /* only bit0-14 are valid  */
            proto_item_append_text(item, " (%g msec)", 1.25*clock_value);
            proto_tree_add_item(tree, hf_bthci_cmd_clock_offset_valid , tvb, offset, 2, ENC_LITTLE_ENDIAN);
            offset+=2;

            proto_tree_add_item(tree, hf_bthci_cmd_allow_role_switch, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            break;

        case 0x0006: /* Disconnect */
            proto_tree_add_item(tree, hf_bthci_cmd_connection_handle, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            offset+=2;
            proto_tree_add_item(tree, hf_bthci_cmd_reason, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            break;

        case 0x0007: /* Add SCO Connection */
            proto_tree_add_item(tree, hf_bthci_cmd_connection_handle, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            offset+=2;
            proto_tree_add_item(tree, hf_bthci_cmd_packet_type_hv1, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_packet_type_hv2, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_packet_type_hv3, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            offset+=2;
            break;

        case 0x0008: /* Create Connection Cancel Request */
            offset = dissect_bthci_cmd_bd_addr(tvb, offset, pinfo, tree);
            break;

        case 0x0009: /* Accept Connection Request */
            offset = dissect_bthci_cmd_bd_addr(tvb, offset, pinfo, tree);

            proto_tree_add_item(tree, hf_bthci_cmd_role, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            break;

        case 0x000a: /* Reject Connection Request */
            offset = dissect_bthci_cmd_bd_addr(tvb, offset, pinfo, tree);

            proto_tree_add_item(tree, hf_bthci_cmd_reason, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            break;

        case 0x000b: /* Link Key Request Reply */
            offset = dissect_bthci_cmd_bd_addr(tvb, offset, pinfo, tree);

            proto_tree_add_item(tree, hf_bthci_cmd_link_key, tvb, offset, 16, ENC_NA);
            offset+=16;
            break;

        case 0x000c: /* Link Key Request Negative Reply */
            offset = dissect_bthci_cmd_bd_addr(tvb, offset, pinfo, tree);
            break;

        case 0x000d: /* PIN Code Request Reply */
            offset = dissect_bthci_cmd_bd_addr(tvb, offset, pinfo, tree);

            proto_tree_add_item(tree, hf_bthci_cmd_pin_code_length ,tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            proto_tree_add_item(tree, hf_bthci_cmd_pin_code ,tvb, offset, 16, ENC_ASCII|ENC_NA);
            offset+=16;
            break;

        case 0x000e: /* PIN Code Request Negative Reply */
            offset = dissect_bthci_cmd_bd_addr(tvb, offset, pinfo, tree);
            break;

        case 0x000f: /* Change Connection Packet Type */
            proto_tree_add_item(tree, hf_bthci_cmd_connection_handle, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            offset+=2;
            proto_tree_add_item(tree, hf_bthci_cmd_packet_type_2dh1, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_packet_type_3dh1, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_packet_type_dm1, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_packet_type_dh1, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_packet_type_2dh3, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_packet_type_3dh3, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_packet_type_dm3, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_packet_type_dh3, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_packet_type_2dh5, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_packet_type_3dh5, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_packet_type_dm5, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_packet_type_dh5, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            offset+=2;
            break;

        case 0x0011: /* Authentication Request */
            proto_tree_add_item(tree, hf_bthci_cmd_connection_handle, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            offset+=2;
            break;

        case 0x0013: /* Set Connection Encryption */
            proto_tree_add_item(tree, hf_bthci_cmd_connection_handle, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            offset+=2;
            proto_tree_add_item(tree, hf_bthci_cmd_encryption_enable, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            break;

        case 0x0017: /* Master Link Key */
            proto_tree_add_item(tree, hf_bthci_cmd_key_flag, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            break;

        case 0x0019: /* Remote Name Request */
            offset = dissect_bthci_cmd_bd_addr(tvb, offset, pinfo, tree);

            proto_tree_add_item(tree, hf_bthci_cmd_page_scan_repetition_mode, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;

            proto_tree_add_item(tree, hf_bthci_cmd_page_scan_mode, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;

            item = proto_tree_add_item(tree, hf_bthci_cmd_clock_offset, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            clock_value = tvb_get_letohs(tvb, offset) & 32767; /* only bit0-14 are valid  */
            proto_item_append_text(item, " (%g msec)", 1.25*clock_value);
            proto_tree_add_item(tree, hf_bthci_cmd_clock_offset_valid , tvb, offset, 2, ENC_LITTLE_ENDIAN);
            offset+=2;
            break;

        case 0x001a: /* Remote Name Request Cancel */
            offset = dissect_bthci_cmd_bd_addr(tvb, offset, pinfo, tree);
            break;

        case 0x001c: /* Read Remote Extended Features */
            proto_tree_add_item(tree, hf_bthci_cmd_connection_handle, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            offset+=2;
            proto_tree_add_item(tree, hf_bthci_cmd_page_number, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            break;

        case 0x0028: /* Setup Synchronous Connection */
        case 0x0029: /* Accept Synchronous Connection Request */
            proto_tree_add_item(tree, hf_bthci_cmd_connection_handle, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            offset+=2;
            proto_tree_add_item(tree, hf_bthci_cmd_transmit_bandwidth, tvb, offset, 4, ENC_LITTLE_ENDIAN);
            offset+=4;
            proto_tree_add_item(tree, hf_bthci_cmd_receive_bandwidth, tvb, offset, 4, ENC_LITTLE_ENDIAN);
            offset+=4;
            proto_tree_add_item(tree, hf_bthci_cmd_max_latency_ms, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            offset+=2;

            proto_tree_add_item(tree, hf_bthci_cmd_input_unused, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_input_coding, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_input_data_format, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_input_sample_size, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_linear_pcm_bit_pos, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_air_coding_format, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            offset+=2;

            proto_tree_add_item(tree, hf_bthci_cmd_retransmission_effort, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;

            proto_tree_add_item(tree, hf_bthci_cmd_sco_packet_type_hv1, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_sco_packet_type_hv2, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_sco_packet_type_hv3, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_sco_packet_type_ev3, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_sco_packet_type_ev4, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_sco_packet_type_ev5, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_sco_packet_type_2ev3, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_sco_packet_type_3ev3, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_sco_packet_type_2ev5, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_sco_packet_type_3ev5, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            offset+=2;
            break;

        case 0x002a: /* Reject Synchronous Connection Request */
            offset = dissect_bthci_cmd_bd_addr(tvb, offset, pinfo, tree);

            proto_tree_add_item(tree, hf_bthci_cmd_reason, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            break;

        case 0x0015: /* Change Connection Link Key */
        case 0x001b: /* Read Remote Supported Features */
        case 0x001d: /* Read Remote Version Information */
        case 0x001f: /* Read Clock Offset*/
        case 0x0020: /* Read LMP Handle */
            proto_tree_add_item(tree, hf_bthci_cmd_connection_handle, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            offset+=2;
            break;

        case 0x002b: /* IO Capability Response */
            offset = dissect_bthci_cmd_bd_addr(tvb, offset, pinfo, tree);

            proto_tree_add_item(tree, hf_bthci_cmd_io_capability, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            proto_tree_add_item(tree, hf_bthci_cmd_oob_data_present, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            proto_tree_add_item(tree, hf_bthci_cmd_auth_requirements, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            break;

        case 0x0034: /* IO Capability Request Negative Reply */
            offset = dissect_bthci_cmd_bd_addr(tvb, offset, pinfo, tree);
            proto_tree_add_item(tree, hf_bthci_cmd_reason, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            break;

        case 0x002c: /* User Confirmation Request Reply */
        case 0x002d: /* User Confirmation Request Negative Reply */
        case 0x002f: /* User Passkey Request Negative Reply */
        case 0x0033: /* Remote OOB Data Request Negative Reply */
            offset = dissect_bthci_cmd_bd_addr(tvb, offset, pinfo, tree);
            break;

        case 0x002e: /* User Passkey Request Reply */
            offset = dissect_bthci_cmd_bd_addr(tvb, offset, pinfo, tree);

            proto_tree_add_item(tree, hf_bthci_cmd_passkey, tvb, offset, 4, ENC_LITTLE_ENDIAN);
            offset+=4;
            break;

        case 0x0030: /* Remote OOB Data Request Reply */
            offset = dissect_bthci_cmd_bd_addr(tvb, offset, pinfo, tree);

            proto_tree_add_item(tree, hf_bthci_cmd_hash_c, tvb, offset, 16, ENC_NA);
            offset+=16;
            proto_tree_add_item(tree, hf_bthci_cmd_randomizer_r, tvb, offset, 16, ENC_NA);
            offset+=16;
            break;

        case 0x0035: /* Create Physical Link */
        case 0x0036: /* Accept Physical Link */
            proto_tree_add_item(tree, hf_bthci_cmd_physical_link_handle, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            proto_tree_add_item(tree, hf_bthci_cmd_dedicated_amp_key_length, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            proto_tree_add_item(tree, hf_bthci_cmd_dedicated_amp_key_type, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            proto_tree_add_item(tree, hf_bthci_cmd_dedicated_amp_key, tvb, offset, -1, ENC_NA);
            offset+=tvb_length_remaining(tvb, offset);
            break;

        case 0x0037: /* Disconnect Physical Link */
            proto_tree_add_item(tree, hf_bthci_cmd_physical_link_handle, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            proto_tree_add_item(tree, hf_bthci_cmd_reason, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            break;

        case 0x0038: /* Create Logical Link */
        case 0x0039: /* Accept Logical Link */
            proto_tree_add_item(tree, hf_bthci_cmd_physical_link_handle, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            offset = dissect_bthci_cmd_flow_spec(tvb, offset, pinfo, tree, TRUE);
            offset = dissect_bthci_cmd_flow_spec(tvb, offset, pinfo, tree, FALSE);
            break;

        case 0x003a: /* Disconnect Logical Link */
            proto_tree_add_item(tree, hf_bthci_cmd_logical_link_handle, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            offset+=2;
            break;

        case 0x003b: /* Logical Link Cancel */
            proto_tree_add_item(tree, hf_bthci_cmd_physical_link_handle, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            proto_tree_add_item(tree, hf_bthci_cmd_flow_spec_identifier, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            break;

        case 0x003c: /* Flow Spec Modify */
            proto_tree_add_item(tree, hf_bthci_cmd_logical_link_handle, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            offset = dissect_bthci_cmd_flow_spec(tvb, offset, pinfo, tree, TRUE);
            offset = dissect_bthci_cmd_flow_spec(tvb, offset, pinfo, tree, FALSE);
            break;

        case 0x0002: /* Inquiry Cancel */
        case 0x0004: /* Exit Periodic Inquiry Mode */
            /* NOTE: No parameters */
            break;

        case 0x003D: /* Enhanced Setup Synchronous Connection */
        case 0x003E: /* Enhanced Accept Synchronous Connection Request */
        case 0x003F: /* Truncated Page */
        case 0x0040: /* Truncated Page Cancel */
        case 0x0041: /* Set Connectionless Slave Broadcast */
        case 0x0042: /* Set Connectionless Slave Broadcast Receive */
        case 0x0043: /* Start Synchronization Train */
        case 0x0044: /* Receive Synchronization Train */
/* TODO: Implement above cases */
            proto_tree_add_expert(tree, pinfo, &ei_command_undecoded, tvb, offset, -1);
            offset += tvb_length_remaining(tvb, offset);
            break;
    }

    return offset;
}

static int
dissect_link_policy_cmd(tvbuff_t *tvb, int offset, packet_info *pinfo, proto_tree *tree, guint16 cmd_ocf)
{
    proto_item *item;
    guint16     timeout;

    switch (cmd_ocf) {
        case 0x0001: /* Hold Mode */
            proto_tree_add_item(tree, hf_bthci_cmd_connection_handle, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            offset+=2;
            item = proto_tree_add_item(tree, hf_bthci_cmd_max_interval_hold, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            timeout = tvb_get_letohs(tvb, offset);
            proto_item_append_text(item, " slots (%g msec)", timeout*0.625);
            offset+=2;
            item = proto_tree_add_item(tree, hf_bthci_cmd_min_interval_hold, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            timeout = tvb_get_letohs(tvb, offset);
            proto_item_append_text(item, " slots (%g msec)", timeout*0.625);
            offset+=2;
            break;

        case 0x0003: /* sniff mode */
            proto_tree_add_item(tree, hf_bthci_cmd_connection_handle, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            offset+=2;
            item = proto_tree_add_item(tree, hf_bthci_cmd_max_interval_sniff, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_item_append_text(item, " slots (%g msec)",  tvb_get_letohs(tvb, offset)*0.625);
            offset+=2;
            item = proto_tree_add_item(tree, hf_bthci_cmd_min_interval_sniff, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_item_append_text(item, " slots (%g msec)",  tvb_get_letohs(tvb, offset)*0.625);
            offset+=2;
            item = proto_tree_add_item(tree, hf_bthci_cmd_sniff_attempt, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            timeout = tvb_get_letohs(tvb, offset);
            if (timeout>0) {
                proto_item_append_text(item, " (%g msec)", (2*timeout-1)*0.625);
            } else {
                proto_item_append_text(item, " (0 msec)");
            }
            offset+=2;
            item = proto_tree_add_item(tree, hf_bthci_cmd_timeout, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_item_append_text(item, " slots (%g msec)",  tvb_get_letohs(tvb, offset)*1.25);
            offset+=2;
            break;

        case 0x0005: /* Park Mode */
            proto_tree_add_item(tree, hf_bthci_cmd_connection_handle, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            offset+=2;
            item = proto_tree_add_item(tree, hf_bthci_cmd_max_interval_beacon, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            timeout = tvb_get_letohs(tvb, offset);
            proto_item_append_text(item, " slots (%g msec)", timeout*0.625);
            offset+=2;
            item = proto_tree_add_item(tree, hf_bthci_cmd_min_interval_beacon, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            timeout = tvb_get_letohs(tvb, offset);
            proto_item_append_text(item, " slots (%g msec)", timeout*0.625);
            offset+=2;
            break;

        case 0x0007: /* QoS Setup */
            proto_tree_add_item(tree, hf_bthci_cmd_connection_handle, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            offset+=2;
            proto_tree_add_item(tree, hf_bthci_cmd_flags, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            proto_tree_add_item(tree, hf_bthci_cmd_service_type, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            proto_tree_add_item(tree, hf_bthci_cmd_token_rate, tvb, offset, 4, ENC_LITTLE_ENDIAN);
            offset+=4;
            proto_tree_add_item(tree, hf_bthci_cmd_peak_bandwidth, tvb, offset, 4, ENC_LITTLE_ENDIAN);
            offset+=4;
            proto_tree_add_item(tree, hf_bthci_cmd_latency, tvb, offset, 4, ENC_LITTLE_ENDIAN);
            offset+=4;
            proto_tree_add_item(tree, hf_bthci_cmd_delay_variation, tvb, offset, 4, ENC_LITTLE_ENDIAN);
            offset+=4;
            break;

        case 0x000b: /* Switch Role */
            offset = dissect_bthci_cmd_bd_addr(tvb, offset, pinfo, tree);

            proto_tree_add_item(tree, hf_bthci_cmd_role, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            break;

        case 0x0004: /* Exit Sniff Mode */
        case 0x0006: /* Exit Park Mode */
        case 0x0009: /* Role Discovery */
        case 0x000c: /* Read Link Policy Settings */
            proto_tree_add_item(tree, hf_bthci_cmd_connection_handle, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            offset+=2;
            break;

        case 0x000d: /* Write Link Policy Settings */
            proto_tree_add_item(tree, hf_bthci_cmd_connection_handle, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            offset+=2;
            /* deliberately fall through */
        case 0x000f: /* Write Default Link Policy Settings */
            proto_tree_add_item(tree, hf_bthci_cmd_link_policy_setting_switch, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_link_policy_setting_hold  , tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_link_policy_setting_sniff , tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_link_policy_setting_park  , tvb, offset, 2, ENC_LITTLE_ENDIAN);
            offset+=2;
            break;

        case 0x0010: /* Flow Specification */
            proto_tree_add_item(tree, hf_bthci_cmd_connection_handle, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            offset+=2;
            proto_tree_add_item(tree, hf_bthci_cmd_flags, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            proto_tree_add_item(tree, hf_bthci_cmd_service_type, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            proto_tree_add_item(tree, hf_bthci_cmd_token_rate, tvb, offset, 4, ENC_LITTLE_ENDIAN);
            offset+=4;
            proto_tree_add_item(tree, hf_bthci_cmd_token_bucket_size, tvb, offset, 4, ENC_LITTLE_ENDIAN);
            offset+=4;
            proto_tree_add_item(tree, hf_bthci_cmd_peak_bandwidth, tvb, offset, 4, ENC_LITTLE_ENDIAN);
            offset+=4;
            proto_tree_add_item(tree, hf_bthci_cmd_latency, tvb, offset, 4, ENC_LITTLE_ENDIAN);
            offset+=4;
            break;

        case 0x0011: /* Sniff Subrating */
            proto_tree_add_item(tree, hf_bthci_cmd_connection_handle, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            offset+=2;

            item = proto_tree_add_item(tree, hf_bthci_cmd_max_latency, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_item_append_text(item, " slots (%g msec)",  tvb_get_letohs(tvb, offset)*0.625);
            offset+=2;

            item = proto_tree_add_item(tree, hf_bthci_cmd_min_remote_timeout, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_item_append_text(item, " slots (%g msec)",  tvb_get_letohs(tvb, offset)*0.625);
            offset+=2;

            item = proto_tree_add_item(tree, hf_bthci_cmd_min_local_timeout, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_item_append_text(item, " slots (%g msec)",  tvb_get_letohs(tvb, offset)*0.625);
            offset+=2;
            break;

        case 0x00e: /* Read Default Link Policy Setting */
            /* NOTE: No parameters */
            break;
    }

    return offset;
}

static int
dissect_host_controller_baseband_cmd(tvbuff_t *tvb, int offset, packet_info *pinfo,
        proto_tree *tree, guint16 cmd_ocf)
{
    proto_item *item;
    guint16     timeout;
    guint8      filter_type, filter_condition_type, num8;
    int         i;

    switch (cmd_ocf) {
        case 0x0001: /* Set Event Mask */
            proto_tree_add_item(tree, hf_bthci_cmd_evt_mask_00, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_evt_mask_01, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_evt_mask_02, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_evt_mask_03, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_evt_mask_04, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_evt_mask_05, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_evt_mask_06, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_evt_mask_07, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;

            proto_tree_add_item(tree, hf_bthci_cmd_evt_mask_10, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_evt_mask_11, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_evt_mask_12, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_evt_mask_13, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_evt_mask_14, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_evt_mask_17, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;

            proto_tree_add_item(tree, hf_bthci_cmd_evt_mask_20, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_evt_mask_21, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_evt_mask_23, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_evt_mask_24, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_evt_mask_25, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_evt_mask_26, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_evt_mask_27, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;

            proto_tree_add_item(tree, hf_bthci_cmd_evt_mask_30, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_evt_mask_31, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_evt_mask_32, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_evt_mask_33, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_evt_mask_34, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_evt_mask_35, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_evt_mask_36, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_evt_mask_37, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;

            proto_tree_add_item(tree, hf_bthci_cmd_evt_mask_40, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_evt_mask_41, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_evt_mask_42, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;

            proto_tree_add_item(tree, hf_bthci_cmd_evt_mask_53, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_evt_mask_54, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_evt_mask_55, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_evt_mask_56, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_evt_mask_57, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;

            proto_tree_add_item(tree, hf_bthci_cmd_evt_mask_60, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_evt_mask_61, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_evt_mask_62, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_evt_mask_63, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_evt_mask_64, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_evt_mask_65, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_evt_mask_67, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;

            proto_tree_add_item(tree, hf_bthci_cmd_evt_mask_70, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_evt_mask_72, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_evt_mask_73, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            break;

        case 0x0005: /* Set Event Filter */
            proto_tree_add_item(tree, hf_bthci_cmd_filter_type, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            filter_type = tvb_get_guint8(tvb, 3);
            offset++;
            switch (filter_type) {

                case 0x01: /* Inquiry Result Filter */
                    proto_tree_add_item(tree, hf_bthci_cmd_inquiry_result_filter_condition_type,
                            tvb, offset, 1, ENC_LITTLE_ENDIAN);
                    filter_condition_type = tvb_get_guint8(tvb, offset);
                    offset++;
                    switch (filter_condition_type) {
                        case 0x01:
                            offset=dissect_bthci_cmd_cod(tvb, offset, pinfo, tree);
                            offset=dissect_bthci_cmd_cod_mask(tvb, offset, pinfo, tree);
                            break;

                        case 0x02:
                            offset = dissect_bthci_cmd_bd_addr(tvb, offset, pinfo, tree);
                            break;

                        default:
                            break;

                    }
                    break;

                case 0x02: /* Connection Setup Filter */
                    proto_tree_add_item(tree, hf_bthci_cmd_connection_setup_filter_condition_type,
                            tvb, offset, 1, ENC_LITTLE_ENDIAN);
                    filter_condition_type = tvb_get_guint8(tvb, offset);
                    offset++;
                    switch (filter_condition_type) {
                        case 0x00:
                            proto_tree_add_item(tree, hf_bthci_cmd_auto_acc_flag, tvb, offset, 1, ENC_LITTLE_ENDIAN);
                            offset++;
                            break;

                        case 0x01:
                            offset=dissect_bthci_cmd_cod(tvb, offset, pinfo, tree);
                            offset=dissect_bthci_cmd_cod_mask(tvb, offset, pinfo, tree);

                            proto_tree_add_item(tree, hf_bthci_cmd_auto_acc_flag, tvb, offset, 1, ENC_LITTLE_ENDIAN);
                            offset++;
                            break;

                        case 0x02:
                            offset = dissect_bthci_cmd_bd_addr(tvb, offset, pinfo, tree);

                            proto_tree_add_item(tree, hf_bthci_cmd_auto_acc_flag, tvb, offset, 1, ENC_LITTLE_ENDIAN);
                            offset++;
                            break;

                        default:
                            break;

                    }
                    break;

                default:
                    break;

            }

            break;
        case 0x000a: /* Write PIN Type */
            proto_tree_add_item(tree, hf_bthci_cmd_pin_type, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            break;

        case 0x000d: /* Read Stored Link Key */
            offset = dissect_bthci_cmd_bd_addr(tvb, offset, pinfo, tree);

            proto_tree_add_item(tree, hf_bthci_cmd_read_all_flag, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            break;

        case 0x0011: /* Write Stored Link Key */
            proto_tree_add_item(tree, hf_bthci_cmd_num_link_keys, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            num8 = tvb_get_guint8(tvb, offset);
            offset++;
            for (i=0; i<num8; i++) {
                dissect_bthci_cmd_bd_addr(tvb, offset+(i*22), pinfo, tree);
                proto_tree_add_item(tree, hf_bthci_cmd_link_key, tvb, offset+6+(i*22), 16, ENC_NA);
            }
            break;

        case 0x0012: /* Delete Stored Link Key */
            offset = dissect_bthci_cmd_bd_addr(tvb, offset, pinfo, tree);

            proto_tree_add_item(tree, hf_bthci_cmd_delete_all_flag, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            break;

        case 0x0013: /* Change Local Name */
            proto_tree_add_item(tree, hf_bthci_cmd_device_name,
                    tvb, offset, 248, ENC_ASCII|ENC_NA);
            offset+=248;
            break;

        case 0x0016: /* Write Connection Accept Timeout */
            item = proto_tree_add_item(tree, hf_bthci_cmd_timeout, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            timeout = tvb_get_letohs(tvb, offset);
            proto_item_append_text(item, " slots (%g msec)", timeout*0.625);
            offset+=2;
            break;

        case 0x0018: /* Write Page Timeout */
            item = proto_tree_add_item(tree, hf_bthci_cmd_timeout, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            timeout = tvb_get_letohs(tvb, offset);
            if (timeout > 0) {
                proto_item_append_text(item, " slots (%g msec)", timeout*0.625);
            } else {
                proto_item_append_text(item, " Illegal Page Timeout");
            }
            offset+=2;
            break;

        case 0x001a: /* Write Scan Enable */
            proto_tree_add_item(tree, hf_bthci_cmd_scan_enable,
                    tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            break;

        case 0x0020: /* Write Authentication Enable */
            proto_tree_add_item(tree, hf_bthci_cmd_authentication_enable,
                    tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            break;

        case 0x0022: /* Write Encryption Mode */
            proto_tree_add_item(tree, hf_bthci_cmd_encrypt_mode, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            break;

        case 0x0024: /* Write Class of Device */
            offset=dissect_bthci_cmd_cod(tvb, offset, pinfo, tree);
            break;

        case 0x0026: /* Write Voice Setting */
            proto_tree_add_item(tree, hf_bthci_cmd_input_unused,
                    tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_input_coding,
                    tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_input_data_format,
                    tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_input_sample_size,
                    tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_linear_pcm_bit_pos,
                    tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_air_coding_format,
                    tvb, offset, 2, ENC_LITTLE_ENDIAN);
            offset+=2;
            break;

        case 0x0028: /* Write Automatic Flush Timeout */
            proto_tree_add_item(tree, hf_bthci_cmd_connection_handle, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            offset+=2;
            item = proto_tree_add_item(tree, hf_bthci_cmd_timeout, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            timeout = tvb_get_letohs(tvb, offset);
            if (timeout>0) {
                proto_item_append_text(item, " slots (%g msec)", timeout*0.625);
            } else {
                proto_item_append_text(item, " (= No Automatic Flush )");
            }
            offset+=2;
            break;

        case 0x002a: /* Write Num of Broadcast Retransmissions */
            proto_tree_add_item(tree, hf_bthci_cmd_num_broadcast_retransmissions,
                    tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            break;

        case 0x002c: /* Write Hold Mode Activity */
            proto_tree_add_item(tree, hf_bthci_cmd_hold_mode_act_page,
                    tvb, offset, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_hold_mode_act_inquiry,
                    tvb, offset, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_hold_mode_act_periodic,
                    tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            break;

        case 0x002d: /* Read Transmit Power Level */
            proto_tree_add_item(tree, hf_bthci_cmd_connection_handle,
                    tvb, offset, 2, ENC_LITTLE_ENDIAN);
            offset+=2;
            proto_tree_add_item(tree, hf_bthci_cmd_tx_power_level_type,
                    tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            break;

        case 0x002f: /* Write SCO Flow Control Enable */
            proto_tree_add_item(tree, hf_bthci_cmd_sco_flow_control,
                    tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            break;

        case 0x0031: /* Set Host Controller To Host Flow Control */
            proto_tree_add_item(tree, hf_bthci_cmd_flow_contr_enable,
                    tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            break;

        case 0x0033: /* Host Buffer Size */
            proto_tree_add_item(tree, hf_bthci_cmd_host_data_packet_length_acl,
                    tvb, offset, 2, ENC_LITTLE_ENDIAN);
            offset+=2;
            proto_tree_add_item(tree, hf_bthci_cmd_host_data_packet_length_sco,
                    tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            proto_tree_add_item(tree, hf_bthci_cmd_host_total_num_acl_data_packets,
                    tvb, offset, 2, ENC_LITTLE_ENDIAN);
            offset+=2;
            proto_tree_add_item(tree, hf_bthci_cmd_host_total_num_sco_data_packets,
                    tvb, offset, 2, ENC_LITTLE_ENDIAN);
            offset+=2;
            break;

        case 0x0035: /* Host Number Of Completed Packets */
            proto_tree_add_item(tree, hf_bthci_cmd_num_handles,
                    tvb, offset, 1, ENC_LITTLE_ENDIAN);
            num8 = tvb_get_guint8(tvb, offset);
            offset++;
            for (i=0; i<num8; i++) {
                proto_tree_add_item(tree, hf_bthci_cmd_connection_handle,
                        tvb, offset+(i*4), 2, ENC_LITTLE_ENDIAN);
                proto_tree_add_item(tree, hf_bthci_cmd_num_compl_packets,
                        tvb, offset+2+(i*4), 2, ENC_LITTLE_ENDIAN);
            }
            break;

        case 0x0037: /* Write Link Supervision Timeout */
            proto_tree_add_item(tree, hf_bthci_cmd_connection_handle,
                    tvb, offset, 2, ENC_LITTLE_ENDIAN);
            offset+=2;
            item = proto_tree_add_item(tree, hf_bthci_cmd_timeout,
                    tvb, offset, 2, ENC_LITTLE_ENDIAN);
            timeout = tvb_get_letohs(tvb, offset);
            if (timeout>0) {
                proto_item_append_text(item, " slots (%g msec)", timeout*0.625);
            } else {
                proto_item_append_text(item, " (= No Link Supervision Timeout)");
            }
            offset+=2;
            break;

        case 0x003a: /* Write Current IAC LAP */
            proto_tree_add_item(tree, hf_bthci_cmd_num_curr_iac, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            num8 = tvb_get_guint8(tvb, offset);
            offset++;
            for (i=0; i<num8; i++) {
                proto_tree_add_item(tree, hf_bthci_cmd_iac_lap, tvb, offset+(i*3), 3, ENC_LITTLE_ENDIAN);
            }
            offset += num8 * 3;
            break;

        case 0x003c: /* Write Page Scan Period Mode */
            proto_tree_add_item(tree, hf_bthci_cmd_page_scan_period_mode,
                    tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            break;

        case 0x003e: /* Write Page Scan Mode */
            proto_tree_add_item(tree, hf_bthci_cmd_page_scan_mode,
                    tvb, 3, 1, ENC_LITTLE_ENDIAN);
            break;

        case 0x003f: /* Set AFH Host Channel Classification */
            proto_tree_add_item(tree, hf_bthci_cmd_afh_ch_classification, tvb, offset, 10, ENC_NA);
            offset+=10;
            break;

        case 0x0008: /* Flush */
        case 0x0027: /* Read Automatic Flush Timeout */
        case 0x0036: /* Read Link Supervision Timeout */
            proto_tree_add_item(tree, hf_bthci_cmd_connection_handle, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            offset+=2;
            break;

        case 0x001c: /* Write Page Scan Activity */
        case 0x001e: /* Write Inquiry Scan Activity */
            item = proto_tree_add_item(tree, hf_bthci_cmd_interval, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_item_append_text(item, " slots (%g msec)",  tvb_get_letohs(tvb, offset)*0.625);
            offset+=2;
            item = proto_tree_add_item(tree, hf_bthci_cmd_window, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_item_append_text(item, " slots (%g msec)",  tvb_get_letohs(tvb, offset)*0.625);
            offset+=2;
            break;


        case 0x0043: /* Write Inquiry Scan Type */
            proto_tree_add_item(tree, hf_bthci_cmd_scan_type, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            break;

        case 0x0045: /* Write Inquiry Mode */
            proto_tree_add_item(tree, hf_bthci_cmd_inq_mode, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            break;

        case 0x0047: /* Write Page Scan Type */
            proto_tree_add_item(tree, hf_bthci_cmd_scan_type, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            break;

        case 0x0049: /* Write AFH Channel Assessment Mode */
            proto_tree_add_item(tree, hf_bthci_cmd_afh_ch_assessment_mode, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            break;

        case 0x0052: /* Write Extended Inquiry Response */
            proto_tree_add_item(tree, hf_bthci_cmd_fec_required, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            offset=dissect_bthci_eir_ad_data(tvb, offset, pinfo, tree, 240);
            break;

        case 0x0053: /* Refresh Encryption Key */
            proto_tree_add_item(tree, hf_bthci_cmd_connection_handle, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            offset+=2;
            break;

        case 0x0056: /* Write Simple Pairing Mode */
            proto_tree_add_item(tree, hf_bthci_cmd_simple_pairing_mode, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            break;

        case 0x0059: /* Write Inquiry Tx Response Power Level */
            proto_tree_add_item(tree, hf_bthci_cmd_tx_power, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            break;

        case 0x005b: /* Write Default Erroneous Data Reporting */
            proto_tree_add_item(tree, hf_bthci_cmd_err_data_reporting, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            break;

        case 0x005f: /* Enhanced Flush */
            proto_tree_add_item(tree, hf_bthci_cmd_connection_handle, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            offset+=2;
            proto_tree_add_item(tree, hf_bthci_cmd_flush_packet_type, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            break;

        case 0x0060: /* Send Keypress Notification */
            offset = dissect_bthci_cmd_bd_addr(tvb, offset, pinfo, tree);

            proto_tree_add_item(tree, hf_bthci_cmd_notification_type, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            break;

        case 0x0062: /* Write Logical Link Accept Timeout */
            item =  proto_tree_add_item(tree, hf_bthci_cmd_timeout, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_item_append_text(item, " slots (%g msec)",  tvb_get_letohs(tvb, offset)*0.625);
            offset+=2;
            break;

        case 0x0063: /* Set Event Mask Page 2 */
            proto_tree_add_item(tree, hf_bthci_cmd_evt_mask2_00, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_evt_mask2_01, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_evt_mask2_02, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_evt_mask2_03, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_evt_mask2_04, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_evt_mask2_05, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_evt_mask2_06, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_evt_mask2_07, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;

            proto_tree_add_item(tree, hf_bthci_cmd_evt_mask2_10, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_evt_mask2_11, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_evt_mask2_12, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_evt_mask2_13, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_evt_mask2_14, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_evt_mask2_15, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset+=7;
            break;

        case 0x0065: /* Write Location Data */
            proto_tree_add_item(tree, hf_bthci_cmd_location_domain_aware, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            proto_tree_add_item(tree, hf_bthci_cmd_location_domain, tvb, offset, 2, ENC_ASCII | ENC_NA);
            offset+=2;
            proto_tree_add_item(tree, hf_bthci_cmd_location_domain_options, tvb, offset, 1, ENC_ASCII | ENC_NA);
            offset++;
            proto_tree_add_item(tree, hf_bthci_cmd_location_options, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            break;

        case 0x0067: /* Write Flow Control Mode */
            proto_tree_add_item(tree, hf_bthci_cmd_flow_control_mode, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            break;

        case 0x0068: /* Read Enhanced Tx Power Level */
            proto_tree_add_item(tree, hf_bthci_cmd_connection_handle, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            offset+=2;
            proto_tree_add_item(tree, hf_bthci_cmd_tx_power_level_type, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            break;

        case 0x0069: /* Read Best Effort Flush Timeout */
            proto_tree_add_item(tree, hf_bthci_cmd_logical_link_handle, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            offset+=2;
            break;

        case 0x006a: /* Write Best Effort Flush Timeout */
            proto_tree_add_item(tree, hf_bthci_cmd_logical_link_handle, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            offset+=2;
            proto_tree_add_item(tree, hf_bthci_cmd_flush_to_us, tvb, offset, 4, ENC_LITTLE_ENDIAN);
            offset+=4;
            break;

        case 0x006b: /* Short Range Mode */
            proto_tree_add_item(tree, hf_bthci_cmd_physical_link_handle, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            proto_tree_add_item(tree, hf_bthci_cmd_short_range_mode, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            break;

        case 0x006d: /* Write LE Host Supported */
            proto_tree_add_item(tree, hf_bthci_cmd_le_supported_host, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            proto_tree_add_item(tree, hf_bthci_cmd_le_simultaneous_host, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            break;

        case 0x003: /* Reset */
        case 0x009: /* Read PIN Type */
        case 0x00B: /* Create New Unit Key */
        case 0x014: /* Read Local Name */
        case 0x015: /* Read Connection Accept Timeout */
        case 0x017: /* Read Page Timeout */
        case 0x019: /* Read Scan Enable */
        case 0x01B: /* Read Page Scan Activity */
        case 0x01D: /* Read Inquiry Scan Activity */
        case 0x01F: /* Read Authentication Enable */
        case 0x021: /* Read Encryption Mode */
        case 0x023: /* Read Class of Device */
        case 0x025: /* Read Voice Setting */
        case 0x029: /* Read Num Broadcast Retransmissions */
        case 0x02B: /* Read Hold Mode Activity */
        case 0x02E: /* Read SCO Flow Control Enable */
        case 0x038: /* Read Number of Supported IAC */
        case 0x039: /* Read Current IAC LAP */
        case 0x03B: /* Read Page Scan Period Mode */
        case 0x03D: /* Read Page Scan Mode */
        case 0x042: /* Read Inquiry Scan Type */
        case 0x044: /* Read Inquiry Mode */
        case 0x046: /* Read Page Scan Type */
        case 0x048: /* Read AFH Channel Assessment Mode */
        case 0x051: /* Read Extended Inquiry Response */
        case 0x055: /* Read Simple Pairing Mode */
        case 0x057: /* Read Local OOB Data */
        case 0x058: /* Read Inquiry Response Tx Power Level */
        case 0x05A: /* Read Default Erroneous Data Reporting */
        case 0x061: /* Read Logical Link Accept Timeout */
        case 0x064: /* Read Location Data */
        case 0x066: /* Read Flow Control Mode */
        case 0x06C: /* Read LE Host Supported */
            /* NOTE: No parameters */
            break;

        case 0x06E: /* Set MWS Channel Parameters */
        case 0x06F: /* Set External Frame Configuration */
        case 0x070: /* Set MWS Signaling */
        case 0x071: /* Set MWS Transport Layer */
        case 0x072: /* Set MWS Scan Frequency Table */
        case 0x073: /* Set MWS Pattern Configuration */
        case 0x074: /* Set Reserved LT_ADDR */
        case 0x075: /* Delete Reserved LT_ADDR */
        case 0x076: /* Set Connectionless Slave Broadcast Data */
        case 0x077: /* Read Synchronization Train Parameters */
        case 0x078: /* Write Synchronization Train Parameters */
/* TODO: Implement above cases */
            proto_tree_add_expert(tree, pinfo, &ei_command_undecoded, tvb, offset, -1);
            offset += tvb_length_remaining(tvb, offset);
            break;
    }

    return offset;
}

static int
dissect_informational_parameters_cmd(tvbuff_t *tvb, int offset, packet_info *pinfo _U_,
        proto_tree *tree, guint16 cmd_ocf)
{
    switch (cmd_ocf) {

        case 0x0004: /* Read Local Extended Features */
            proto_tree_add_item(tree, hf_bthci_cmd_page_number, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            break;

        case 0x001: /* Read Local Version Information */
        case 0x002: /* Read Local Supported Commands */
        case 0x003: /* Read Local Supported Features */
        case 0x005: /* Read Buffer Size */
        case 0x007: /* Read Country Code */
        case 0x009: /* Read BD ADDR */
        case 0x00A: /* Read Data Block Size */
        case 0x00B: /* Read Local Supported Codecs */
            /* NOTE: No parameters */
            break;
    }

    return offset;
}

static int
dissect_status_parameters_cmd(tvbuff_t *tvb, int offset, packet_info *pinfo _U_,
        proto_tree *tree, guint16 cmd_ocf)
{
    switch (cmd_ocf) {

        case 0x0001: /* Read Failed Contact Counter */
        case 0x0002: /* Reset Failed Contact Counter */
        case 0x0003: /* Get Link Quality */
        case 0x0005: /* Read RSSI */
        case 0x0006: /* Read AFH Channel Map */
        case 0x0008: /* Read Encryption Key Size */
            proto_tree_add_item(tree, hf_bthci_cmd_connection_handle, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            offset+=2;
            break;

        case 0x0007: /* Read Clock */
            proto_tree_add_item(tree, hf_bthci_cmd_connection_handle, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            offset+=2;
            proto_tree_add_item(tree, hf_bthci_cmd_which_clock, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            break;

        case 0x0009: /* Read Local AMP Info */
            break;

        case 0x000a: /* Read Local AMP Assoc */
            proto_tree_add_item(tree, hf_bthci_cmd_physical_link_handle, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            proto_tree_add_item(tree, hf_bthci_cmd_length_so_far, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            offset+=2;
            proto_tree_add_item(tree, hf_bthci_cmd_amp_assoc_length, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            offset+=2;
            break;

        case 0x000b: /* Write Remote AMP Assoc */
            proto_tree_add_item(tree, hf_bthci_cmd_physical_link_handle, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            proto_tree_add_item(tree, hf_bthci_cmd_length_so_far, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            offset+=2;
            proto_tree_add_item(tree, hf_bthci_cmd_amp_remaining_assoc_length, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            offset+=2;
            proto_tree_add_item(tree, hf_bthci_cmd_amp_assoc_fragment, tvb, offset, -1, ENC_NA);
            offset+=tvb_length_remaining(tvb, offset);
            break;

        case 0x00D: /* Set Triggered Clock Capture */
            /* NOTE: No parameters */
            break;

        case 0x00C: /* Get MWS Transport Layer Configuration */
/* TODO: Implement above cases */
            proto_tree_add_expert(tree, pinfo, &ei_command_undecoded, tvb, offset, -1);
            offset += tvb_length_remaining(tvb, offset);
            break;
    }

    return offset;
}

static int
dissect_testing_cmd(tvbuff_t *tvb, int offset, packet_info *pinfo _U_, proto_tree *tree, guint16 cmd_ocf)
{
    switch (cmd_ocf) {

        case 0x0002: /* Write Loopback Mode */
            proto_tree_add_item(tree, hf_bthci_cmd_loopback_mode, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            break;

        case 0x0004: /* Write Simple Pairing Debug Mode */
            proto_tree_add_item(tree, hf_bthci_cmd_simple_pairing_debug_mode, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            break;

        case 0x0007: /* Enable AMP Receiver Reports */
            proto_tree_add_item(tree, hf_bthci_cmd_enable_amp_recv_reports, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            proto_tree_add_item(tree, hf_bthci_cmd_amp_recv_report_interval, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            break;

        case 0x001: /* Read Loopback Mode */
        case 0x003: /* Enable Device Under Test Mode */
        case 0x008: /* AMP Test End */
            /* NOTE: No parameters */
            break;

        case 0x009: /* AMP Test */
/* TODO: Implement above case */
            proto_tree_add_expert(tree, pinfo, &ei_command_undecoded, tvb, offset, -1);
            offset += tvb_length_remaining(tvb, offset);
            break;
    }

    return offset;
}

static gint
dissect_le_cmd(tvbuff_t *tvb, int offset, packet_info *pinfo, proto_tree *tree, guint16 cmd_ocf)
{
    proto_item *item;

    switch(cmd_ocf) {

        case 0x0001: /* LE Set Event Mask */
            proto_tree_add_item(tree, hf_bthci_cmd_le_evt_mask_00, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_le_evt_mask_01, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_le_evt_mask_02, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_le_evt_mask_03, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_le_evt_mask_04, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset+=8;
            break;

        case 0x0005: /* LE Set Random Address */
            offset = dissect_bthci_cmd_bd_addr(tvb, offset, pinfo, tree);
            break;

        case 0x0006: /* LE Set Advertising Parameters */
            item = proto_tree_add_item(tree, hf_bthci_cmd_le_advts_interval_min, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_item_append_text(item, " (%g msec)",  tvb_get_letohs(tvb, offset)*0.625);
            offset+=2;
            item = proto_tree_add_item(tree, hf_bthci_cmd_le_advts_interval_max, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_item_append_text(item, " (%g msec)",  tvb_get_letohs(tvb, offset)*0.625);
            offset+=2;
            proto_tree_add_item(tree, hf_bthci_cmd_le_advts_type, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            proto_tree_add_item(tree, hf_bthci_cmd_le_own_address_type, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            proto_tree_add_item(tree, hf_bthci_cmd_le_direct_address_type, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            offset = dissect_bthci_cmd_bd_addr(tvb, offset, pinfo, tree);
            proto_tree_add_item(tree, hf_bthci_cmd_le_advts_channel_map_1, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_le_advts_channel_map_2, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            proto_tree_add_item(tree, hf_bthci_cmd_le_advts_channel_map_3, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            proto_tree_add_item(tree, hf_bthci_cmd_le_advts_filter_policy, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            break;

        case 0x0008: /* LE Set Advertising Data */
        case 0x0009: /* LE Set Scan Response Data */
            proto_tree_add_item(tree, hf_bthci_cmd_le_data_length, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            offset = dissect_bthci_eir_ad_data(tvb, offset, pinfo, tree, 31);
            break;

        case 0x000a: /* LE Set Advertise Enable */
            proto_tree_add_item(tree, hf_bthci_cmd_le_advts_enable, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            break;

        case 0x000b: /* LE Set Scan Parameters */
            proto_tree_add_item(tree, hf_bthci_cmd_le_scan_type, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            item = proto_tree_add_item(tree, hf_bthci_cmd_le_scan_interval, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_item_append_text(item, " (%g msec)",  tvb_get_letohs(tvb, offset)*0.625);
            offset+=2;
            item = proto_tree_add_item(tree, hf_bthci_cmd_le_scan_window, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_item_append_text(item, " (%g msec)",  tvb_get_letohs(tvb, offset)*0.625);
            offset+=2;
            proto_tree_add_item(tree, hf_bthci_cmd_le_own_address_type, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            proto_tree_add_item(tree, hf_bthci_cmd_le_scan_filter_policy, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            break;

        case 0x000c: /* LE Set Scan Enable */
            proto_tree_add_item(tree, hf_bthci_cmd_le_scan_enable, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            proto_tree_add_item(tree, hf_bthci_cmd_le_filter_dublicates, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            break;

        case 0x000d: /* LE Create Connection */
            item = proto_tree_add_item(tree, hf_bthci_cmd_le_scan_interval, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_item_append_text(item, " (%g msec)",  tvb_get_letohs(tvb, offset)*0.625);
            offset+=2;
            item = proto_tree_add_item(tree, hf_bthci_cmd_le_scan_window, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_item_append_text(item, " (%g msec)",  tvb_get_letohs(tvb, offset)*0.625);
            offset+=2;
            proto_tree_add_item(tree, hf_bthci_cmd_le_initiator_filter_policy, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            proto_tree_add_item(tree, hf_bthci_cmd_le_peer_address_type, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            offset = dissect_bthci_cmd_bd_addr(tvb, offset, pinfo, tree);
            proto_tree_add_item(tree, hf_bthci_cmd_le_own_address_type, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            item = proto_tree_add_item(tree, hf_bthci_cmd_le_con_interval_min, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_item_append_text(item, " (%g msec)",  tvb_get_letohs(tvb, offset)*1.25);
            offset+=2;
            item = proto_tree_add_item(tree, hf_bthci_cmd_le_con_interval_max, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_item_append_text(item, " (%g msec)",  tvb_get_letohs(tvb, offset)*1.25);
            offset+=2;
            item = proto_tree_add_item(tree, hf_bthci_cmd_le_con_latency, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_item_append_text(item, " (number events)");
            offset+=2;
            item = proto_tree_add_item(tree, hf_bthci_cmd_le_supervision_timeout, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_item_append_text(item, " (%g sec)",  tvb_get_letohs(tvb, offset)*0.01);
            offset+=2;
            item = proto_tree_add_item(tree, hf_bthci_cmd_le_min_ce_length, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_item_append_text(item, " (%g msec)",  tvb_get_letohs(tvb, offset)*0.625);
            offset+=2;
            item = proto_tree_add_item(tree, hf_bthci_cmd_le_max_ce_length, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_item_append_text(item, " (%g msec)",  tvb_get_letohs(tvb, offset)*0.625);
            offset+=2;
            break;

        case 0x0011: /* LE Add Device To White List */
        case 0x0012: /* LE Remove Device From White List */
            proto_tree_add_item(tree, hf_bthci_cmd_le_address_type, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            offset = dissect_bthci_cmd_bd_addr(tvb, offset, pinfo, tree);
            break;

        case 0x0013: /* LE Connection Update */
            proto_tree_add_item(tree, hf_bthci_cmd_connection_handle, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            offset+=2;
            item = proto_tree_add_item(tree, hf_bthci_cmd_le_con_interval_min, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_item_append_text(item, " (%g msec)",  tvb_get_letohs(tvb, offset)*1.25);
            offset+=2;
            item = proto_tree_add_item(tree, hf_bthci_cmd_le_con_interval_max, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_item_append_text(item, " (%g msec)",  tvb_get_letohs(tvb, offset)*1.25);
            offset+=2;
            item = proto_tree_add_item(tree, hf_bthci_cmd_le_con_latency, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_item_append_text(item, " (number events)");
            offset+=2;
            item = proto_tree_add_item(tree, hf_bthci_cmd_le_supervision_timeout, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_item_append_text(item, " (%g sec)",  tvb_get_letohs(tvb, offset)*0.01);
            offset+=2;
            item = proto_tree_add_item(tree, hf_bthci_cmd_le_min_ce_length, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_item_append_text(item, " (%g msec)",  tvb_get_letohs(tvb, offset)*0.625);
            offset+=2;
            item = proto_tree_add_item(tree, hf_bthci_cmd_le_max_ce_length, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            proto_item_append_text(item, " (%g msec)",  tvb_get_letohs(tvb, offset)*0.625);
            offset+=2;
            break;

        case 0x0014: /* LE Set Host Channel Classification */
            proto_tree_add_item(tree, hf_bthci_cmd_le_channel_map, tvb, offset, 2, ENC_NA);
            offset+=5;
            break;

        case 0x0015: /* LE Read Channel Map */
        case 0x0016: /* LE Read Remote Used Features */
        case 0x001b: /* LE Long Term Key Request Negative Reply */
            proto_tree_add_item(tree, hf_bthci_cmd_connection_handle, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            offset+=2;
            break;

        case 0x0017: /* LE Encrypt */
            proto_tree_add_item(tree, hf_bthci_cmd_key, tvb, offset, 16, ENC_NA);
            offset+=16;
            proto_tree_add_item(tree, hf_bthci_cmd_plaintext_data, tvb, offset, 16, ENC_NA);
            offset+=16;
            break;

        case 0x0019: /* LE Start Encryption */
            proto_tree_add_item(tree, hf_bthci_cmd_connection_handle, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            offset+=2;
            proto_tree_add_item(tree, hf_bthci_cmd_random_number, tvb, offset, 8, ENC_NA);
            offset+=8;
            proto_tree_add_item(tree, hf_bthci_cmd_encrypted_diversifier, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            offset+=2;
            proto_tree_add_item(tree, hf_bthci_cmd_le_long_term_key, tvb, offset, 16, ENC_NA);
            offset+=16;
            break;

        case 0x001a: /* LE Long Term Key Request Reply */
            proto_tree_add_item(tree, hf_bthci_cmd_connection_handle, tvb, offset, 2, ENC_LITTLE_ENDIAN);
            offset+=2;
            proto_tree_add_item(tree, hf_bthci_cmd_le_long_term_key, tvb, offset, 16, ENC_NA);
            offset+=16;
            break;

        case 0x001d: /* LE Receiver Test */
            item = proto_tree_add_item(tree, hf_bthci_cmd_rx_freqency, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            proto_item_append_text(item, " (%d MHz)",  2402 + 2*tvb_get_guint8(tvb, offset));
            offset++;
            break;

        case 0x001e: /* LE Transmitter Test */
            item = proto_tree_add_item(tree, hf_bthci_cmd_tx_freqency, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            proto_item_append_text(item, " (%d MHz)",  2402 + 2*tvb_get_guint8(tvb, offset));
            offset++;
            proto_tree_add_item(tree, hf_bthci_cmd_test_data_length, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            proto_tree_add_item(tree, hf_bthci_cmd_test_packet_payload, tvb, offset, 1, ENC_LITTLE_ENDIAN);
            offset++;
            break;
        case 0x002: /* LE Read Buffer Size */
        case 0x003: /* LE Read Local Supported Features */
        case 0x007: /* LE Read Advertising Channel Tx Power */
        case 0x00E: /* LE Create Connection Cancel */
        case 0x00F: /* LE Read White List Size */
        case 0x010: /* LE Clear White List */
        case 0x018: /* LE Rand */
        case 0x01C: /* LE Read Supported States */
        case 0x01F: /* LE Test End */
            /* NOTE: No parameters */
            break;
    }

    return offset;
}

/* Code to actually dissect the packets */
static gint
dissect_bthci_cmd(tvbuff_t *tvb, packet_info *pinfo, proto_tree *tree, void *data _U_)
{
    proto_item  *ti_cmd;
    proto_tree  *bthci_cmd_tree;
    guint16      opcode;
    guint16      ocf;
    guint8       param_length;
    guint8       ogf;
    gint         offset = 0;
    proto_item  *ti_opcode;
    proto_tree  *opcode_tree;
    gint         hfx;

    ti_cmd = proto_tree_add_item(tree, proto_bthci_cmd, tvb, offset, -1, ENC_NA);
    bthci_cmd_tree = proto_item_add_subtree(ti_cmd, ett_bthci_cmd);

    switch (pinfo->p2p_dir) {
        case P2P_DIR_SENT:
            col_set_str(pinfo->cinfo, COL_INFO, "Sent ");
            break;
        case P2P_DIR_RECV:
            col_set_str(pinfo->cinfo, COL_INFO, "Rcvd ");
            break;
        default:
            col_add_fstr(pinfo->cinfo, COL_INFO, "Unknown direction %d ",
                pinfo->p2p_dir);
            break;
    }

    opcode = tvb_get_letohs(tvb, offset);
    ocf = opcode & 0x03ff;
    ogf = (guint8) (opcode >> 10);

    proto_item_append_text(ti_cmd," - %s", val_to_str_ext(opcode, &bthci_cmd_opcode_vals_ext, "Unknown 0x%04x"));

    col_set_str(pinfo->cinfo, COL_PROTOCOL, "HCI_CMD");

    col_append_fstr(pinfo->cinfo, COL_INFO, "%s", val_to_str_ext(opcode, &bthci_cmd_opcode_vals_ext, "Unknown 0x%04x"));

    ti_opcode = proto_tree_add_item(bthci_cmd_tree, hf_bthci_cmd_opcode, tvb, offset, 2, ENC_LITTLE_ENDIAN);
    opcode_tree = proto_item_add_subtree(ti_opcode, ett_opcode);
    proto_tree_add_item(opcode_tree, hf_bthci_cmd_ogf, tvb, offset, 2, ENC_LITTLE_ENDIAN);

    if (ogf == HCI_OGF_LINK_CONTROL)
        hfx = hf_bthci_cmd_ocf_link_control;
    else if (ogf == HCI_OGF_LINK_POLICY)
        hfx = hf_bthci_cmd_ocf_link_policy;
    else if (ogf == HCI_OGF_HOST_CONTROLLER)
        hfx = hf_bthci_cmd_ocf_host_controller_and_baseband;
    else if (ogf == HCI_OGF_INFORMATIONAL)
        hfx = hf_bthci_cmd_ocf_informational;
    else if (ogf == HCI_OGF_STATUS)
        hfx = hf_bthci_cmd_ocf_status;
    else if (ogf == HCI_OGF_TESTING)
        hfx = hf_bthci_cmd_ocf_testing;
    else if (ogf == HCI_OGF_LOW_ENERGY)
        hfx = hf_bthci_cmd_ocf_low_energy;
    else if (ogf == HCI_OGF_LOGO_TESTING)
        hfx = hf_bthci_cmd_ocf_logo_testing;
    else
        hfx = hf_bthci_cmd_ocf;
    proto_tree_add_item(opcode_tree, hfx, tvb, offset, 2, ENC_LITTLE_ENDIAN);
    offset+=2;


    proto_tree_add_item(bthci_cmd_tree, hf_bthci_cmd_param_length, tvb, offset, 1, ENC_LITTLE_ENDIAN);
    param_length = tvb_get_guint8(tvb, offset);
    offset++;

    if (param_length > 0) {
        switch (ogf) {
            case HCI_OGF_LINK_CONTROL:
                offset = dissect_link_control_cmd(tvb, offset, pinfo, bthci_cmd_tree, ocf);
                break;

            case HCI_OGF_LINK_POLICY:
                offset = dissect_link_policy_cmd(tvb, offset, pinfo, bthci_cmd_tree, ocf);
                break;

            case HCI_OGF_HOST_CONTROLLER:
                offset = dissect_host_controller_baseband_cmd(tvb, offset, pinfo, bthci_cmd_tree, ocf);
                break;

            case HCI_OGF_INFORMATIONAL:
                offset = dissect_informational_parameters_cmd(tvb, offset, pinfo, bthci_cmd_tree, ocf);
                break;

            case HCI_OGF_STATUS:
                offset = dissect_status_parameters_cmd(tvb, offset, pinfo, bthci_cmd_tree, ocf);
                break;

            case HCI_OGF_TESTING:
                offset = dissect_testing_cmd(tvb, offset, pinfo, bthci_cmd_tree, ocf);
                break;

            case HCI_OGF_LOW_ENERGY:
                offset = dissect_le_cmd(tvb, offset, pinfo, bthci_cmd_tree, ocf);
                break;

            default:
                proto_tree_add_expert(bthci_cmd_tree, pinfo, &ei_command_unknown, tvb, 3, -1);
                offset += tvb_length_remaining(tvb, offset);
                break;
        }
    }

    if (tvb_length_remaining(tvb, offset) > 0) {
        proto_tree_add_expert(bthci_cmd_tree, pinfo, &ei_command_parameter_unexpected, tvb, offset, -1);
        /*offset += tvb_length_remaining(tvb, offset);*/
    }

    return offset;
}


/* Register the protocol with Wireshark */

/* this format is require because a script is used to build the C function
   that calls all the protocol registration.
   */
void
proto_register_bthci_cmd(void)
{
    module_t         *module;
    expert_module_t  *expert_bthci_cmd;
    guint             i_opcode = 0;
    guint             i_array;
    guint             i_string_array;

    /* Setup list of header fields  See Section 1.6.1 for details*/
    static hf_register_info hf[] = {
        { &hf_bthci_cmd_opcode,
          { "Command Opcode",               "bthci_cmd.opcode",
            FT_UINT16, BASE_HEX|BASE_EXT_STRING, &bthci_cmd_opcode_vals_ext, 0x0,
            "HCI Command Opcode", HFILL }
        },
        { &hf_bthci_cmd_ogf,
          { "Opcode Group Field",           "bthci_cmd.opcode.ogf",
            FT_UINT16, BASE_HEX|BASE_EXT_STRING, &bthci_ogf_vals_ext, 0xfc00,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_ocf_link_control,
          { "Opcode Command Field",           "bthci_cmd.opcode.ocf",
            FT_UINT16, BASE_HEX | BASE_EXT_STRING, &bthci_cmd_ocf_link_control_vals_ext, 0x03ff,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_ocf_link_policy,
          { "Opcode Command Field",           "bthci_cmd.opcode.ocf",
            FT_UINT16, BASE_HEX | BASE_EXT_STRING, &bthci_cmd_ocf_link_policy_vals_ext, 0x03ff,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_ocf_host_controller_and_baseband,
          { "Opcode Command Field",           "bthci_cmd.opcode.ocf",
            FT_UINT16, BASE_HEX | BASE_EXT_STRING, &bthci_cmd_ocf_host_controller_and_baseband_vals_ext, 0x03ff,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_ocf_informational,
          { "Opcode Command Field",           "bthci_cmd.opcode.ocf",
            FT_UINT16, BASE_HEX | BASE_EXT_STRING, &bthci_cmd_ocf_informational_vals_ext, 0x03ff,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_ocf_status,
          { "Opcode Command Field",           "bthci_cmd.opcode.ocf",
            FT_UINT16, BASE_HEX | BASE_EXT_STRING, &bthci_cmd_ocf_status_vals_ext, 0x03ff,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_ocf_testing,
          { "Opcode Command Field",           "bthci_cmd.opcode.ocf",
            FT_UINT16, BASE_HEX | BASE_EXT_STRING, &bthci_cmd_ocf_testing_vals_ext, 0x03ff,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_ocf_low_energy,
          { "Opcode Command Field",           "bthci_cmd.opcode.ocf",
            FT_UINT16, BASE_HEX | BASE_EXT_STRING, &bthci_cmd_ocf_low_energy_vals_ext, 0x03ff,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_ocf_logo_testing,
          { "Opcode Command Field",           "bthci_cmd.opcode.ocf",
            FT_UINT16, BASE_HEX, NULL, 0x03ff,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_ocf,
          { "Opcode Command Field",           "bthci_cmd.opcode.ocf",
            FT_UINT16, BASE_HEX, NULL, 0x03ff,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_param_length,
          { "Parameter Total Length",           "bthci_cmd.param_length",
            FT_UINT8, BASE_DEC, NULL, 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_lap,
          { "LAP",           "bthci_cmd.lap",
            FT_UINT24, BASE_HEX, NULL, 0x0,
            "LAP for the inquiry access code", HFILL }
        },
        { &hf_bthci_cmd_inq_length,
          { "Inquiry Length",           "bthci_cmd.inq_length",
            FT_UINT8, BASE_DEC, NULL, 0x0,
            "Inquiry Length (*1.28s)", HFILL }
        },
        { &hf_bthci_cmd_num_responses,
          { "Num Responses",           "bthci_cmd.num_responses",
            FT_UINT8, BASE_DEC, NULL, 0x0,
            "Number of Responses", HFILL }
        },
        { &hf_bthci_cmd_encrypt_mode,
          { "Encryption Mode",           "bthci_cmd.encrypt_mode",
            FT_UINT8, BASE_HEX, VALS(cmd_encrypt_mode_vals), 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_bd_addr,
          { "BD_ADDR",          "bthci_cmd.bd_addr",
            FT_ETHER, BASE_NONE, NULL, 0x0,
            "Bluetooth Device Address", HFILL}
        },
        { &hf_bthci_cmd_packet_type_2dh1,
          { "Packet Type 2-DH1",        "bthci_cmd.packet_type_2dh1",
            FT_UINT16, BASE_DEC, VALS(cmd_boolean), 0x0002,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_packet_type_3dh1,
          { "Packet Type 3-DH1",        "bthci_cmd.packet_type_3dh1",
            FT_UINT16, BASE_DEC, VALS(cmd_boolean), 0x0004,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_packet_type_dm1,
          { "Packet Type DM1",        "bthci_cmd.packet_type_dm1",
            FT_UINT16, BASE_DEC, VALS(cmd_boolean), 0x0008,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_packet_type_dh1,
          { "Packet Type DH1",        "bthci_cmd.packet_type_dh1",
            FT_UINT16, BASE_DEC, VALS(cmd_boolean), 0x0010,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_packet_type_2dh3,
          { "Packet Type 2-DH3",        "bthci_cmd.packet_type_2dh3",
            FT_UINT16, BASE_DEC, VALS(cmd_boolean), 0x0100,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_packet_type_3dh3,
          { "Packet Type 3-DH3",        "bthci_cmd.packet_type_3dh3",
            FT_UINT16, BASE_DEC, VALS(cmd_boolean), 0x0200,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_packet_type_dm3,
          { "Packet Type DM3",        "bthci_cmd.packet_type_dm3",
            FT_UINT16, BASE_DEC, VALS(cmd_boolean), 0x0400,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_packet_type_dh3,
          { "Packet Type DH3",        "bthci_cmd.packet_type_dh3",
            FT_UINT16, BASE_DEC, VALS(cmd_boolean), 0x0800,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_packet_type_2dh5,
          { "Packet Type 2-DH5",        "bthci_cmd.packet_type_2dh5",
            FT_UINT16, BASE_DEC, VALS(cmd_boolean), 0x1000,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_packet_type_3dh5,
          { "Packet Type 3-DH5",        "bthci_cmd.packet_type_3dh5",
            FT_UINT16, BASE_DEC, VALS(cmd_boolean), 0x2000,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_packet_type_dm5,
          { "Packet Type DM5",        "bthci_cmd.packet_type_dm5",
            FT_UINT16, BASE_DEC, VALS(cmd_boolean), 0x4000,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_packet_type_dh5,
          { "Packet Type DH5",        "bthci_cmd.packet_type_dh5",
            FT_UINT16, BASE_DEC, VALS(cmd_boolean), 0x8000,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_page_scan_mode,
          { "Page Scan Mode",        "bthci_cmd.page_scan_mode",
            FT_UINT8, BASE_HEX, VALS(bthci_cmd_page_scan_modes), 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_page_scan_repetition_mode,
          { "Page Scan Repetition Mode",        "bthci_cmd.page_scan_repetition_mode",
            FT_UINT8, BASE_HEX, VALS(bthci_cmd_page_scan_repetition_modes), 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_page_scan_period_mode,
          { "Page Scan Period Mode",        "bthci_cmd.page_scan_period_mode",
            FT_UINT8, BASE_HEX, VALS(bthci_cmd_page_scan_period_modes), 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_clock_offset,
          { "Clock Offset",        "bthci_cmd.clock_offset",
            FT_UINT16, BASE_HEX, NULL, 0x7FFF,
            "Bit 2-16 of the Clock Offset between CLKmaster-CLKslave", HFILL }
        },
        { &hf_bthci_cmd_clock_offset_valid,
          { "Clock_Offset_Valid_Flag",     "bthci_cmd.clock_offset_valid",
            FT_UINT16, BASE_DEC, VALS(cmd_boolean), 0x8000,
            "Indicates if clock offset is valid", HFILL }
        },
        { &hf_bthci_cmd_allow_role_switch,
          { "Allow Role Switch",         "bthci_cmd.allow_role_switch",
            FT_UINT8, BASE_HEX, VALS(cmd_role_switch_modes), 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_max_period_length,
          { "Max Period Length",           "bthci_cmd.max_period_length",
            FT_UINT16, BASE_DEC, NULL, 0x0,
            "Maximum amount of time specified between consecutive inquiries.", HFILL }
        },
        { &hf_bthci_cmd_min_period_length,
          { "Min Period Length",           "bthci_cmd.min_period_length",
            FT_UINT16, BASE_DEC, NULL, 0x0,
            "Minimum amount of time specified between consecutive inquiries.", HFILL }
        },
        { &hf_bthci_cmd_connection_handle,
          { "Connection Handle",             "bthci_cmd.connection_handle",
            FT_UINT16, BASE_HEX, NULL, 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_reason,
          { "Reason",           "bthci_cmd.reason",
            FT_UINT8, BASE_HEX|BASE_EXT_STRING, &bthci_cmd_status_vals_ext, 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_num_link_keys,
          { "Number of Link Keys", "bthci_cmd.num_link_keys",
            FT_UINT8, BASE_DEC, NULL, 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_link_key,
          { "Link Key",        "bthci_cmd.link_key",
            FT_BYTES, BASE_NONE, NULL, 0x0,
            "Link Key for the associated BD_ADDR", HFILL }
        },
        { &hf_bthci_cmd_packet_type_hv1,
          { "Packet Type HV1",        "bthci_cmd.packet_type_hv1",
            FT_UINT16, BASE_DEC, VALS(cmd_boolean), 0x0020,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_packet_type_hv2,
          { "Packet Type HV2",        "bthci_cmd.packet_type_hv2",
            FT_UINT16, BASE_DEC, VALS(cmd_boolean), 0x0040,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_packet_type_hv3,
          { "Packet Type HV3",        "bthci_cmd.packet_type_hv3",
            FT_UINT16, BASE_DEC, VALS(cmd_boolean), 0x0080,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_role,
          { "Role",        "bthci_cmd.role",
            FT_UINT8, BASE_HEX, VALS(cmd_role_vals), 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_pin_code_length,
          { "PIN Code Length",        "bthci_cmd.pin_code_length",
            FT_UINT8, BASE_DEC, NULL, 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_pin_code,
          { "PIN Code",        "bthci_cmd.pin_code",
            FT_STRING, BASE_NONE, NULL, 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_pin_type,
          { "PIN Type", "bthci_cmd.pin_type",
            FT_UINT8, BASE_HEX, VALS(cmd_pin_types), 0x0,
            "PIN Types", HFILL }
        },
        { &hf_bthci_cmd_encryption_enable,
          { "Encryption Enable",        "bthci_cmd.encryption_enable",
            FT_UINT8, BASE_HEX, VALS(cmd_encryption_enable), 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_key_flag,
          { "Key Flag",        "bthci_cmd.key_flag",
            FT_UINT8, BASE_HEX, VALS(cmd_key_flag), 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_max_interval_hold,
          { "Hold Mode Max Interval",        "bthci_cmd.hold_mode_max_int",
            FT_UINT16, BASE_DEC, NULL, 0x0,
            "Maximal acceptable number of Baseband slots to wait in Hold Mode.", HFILL }
        },
        { &hf_bthci_cmd_min_interval_hold,
          { "Hold Mode Min Interval",        "bthci_cmd.hold_mode_min_int",
            FT_UINT16, BASE_DEC, NULL, 0x0,
            "Minimum acceptable number of Baseband slots to wait in Hold Mode.", HFILL }
        },
        { &hf_bthci_cmd_max_interval_sniff,
          { "Sniff Max Interval",        "bthci_cmd.sniff_max_int",
            FT_UINT16, BASE_DEC, NULL, 0x0,
            "Maximal acceptable number of Baseband slots between each sniff period.", HFILL }
        },
        { &hf_bthci_cmd_min_interval_sniff,
          { "Sniff Min Interval",        "bthci_cmd.sniff_min_int",
            FT_UINT16, BASE_DEC, NULL, 0x0,
            "Minimum acceptable number of Baseband slots between each sniff period.", HFILL }
        },
        { &hf_bthci_cmd_sniff_attempt,
          { "Sniff Attempt",        "bthci_cmd.sniff_attempt",
            FT_UINT16, BASE_DEC, NULL, 0x0,
            "Number of Baseband receive slots for sniff attempt.", HFILL }
        },
        { &hf_bthci_cmd_timeout,
          { "Timeout",        "bthci_cmd.timeout",
            FT_UINT16, BASE_DEC, NULL, 0x0,
            "Number of Baseband slots for timeout.", HFILL }
        },
        { &hf_bthci_cmd_max_interval_beacon,
          { "Beacon Max Interval",        "bthci_cmd.beacon_max_int",
            FT_UINT16, BASE_DEC, NULL, 0x0,
            "Maximal acceptable number of Baseband slots between consecutive beacons.", HFILL }
        },
        { &hf_bthci_cmd_min_interval_beacon,
          { "Beacon Min Interval",        "bthci_cmd.beacon_min_int",
            FT_UINT16, BASE_DEC, NULL, 0x0,
            "Minimum acceptable number of Baseband slots between consecutive beacons.", HFILL }
        },
        { &hf_bthci_cmd_flags,
          { "Flags",        "bthci_cmd.flags",
            FT_UINT8, BASE_HEX, NULL, 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_service_type,
          { "Service Type",        "bthci_cmd.service_type",
            FT_UINT8, BASE_HEX, VALS(cmd_service_types), 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_token_rate,
          { "Available Token Rate",        "bthci_cmd.token_rate",
            FT_UINT32, BASE_DEC, NULL, 0x0,
            "Token Rate, in bytes per second", HFILL }
        },
        { &hf_bthci_cmd_token_bucket_size,
          { "Available Token Bucket Size",        "bthci_cmd.token_bucket_size",
            FT_UINT32, BASE_DEC, NULL, 0x0,
            "Token Bucket Size in bytes", HFILL }
        },
        { &hf_bthci_cmd_peak_bandwidth,
          { "Peak Bandwidth",        "bthci_cmd.peak_bandwidth",
            FT_UINT32, BASE_DEC, NULL, 0x0,
            "Peak Bandwidth, in bytes per second", HFILL }
        },
        { &hf_bthci_cmd_latency,
          { "Latency",        "bthci_cmd.latency",
            FT_UINT32, BASE_DEC, NULL, 0x0,
            "Latency, in microseconds", HFILL }
        },
        { &hf_bthci_cmd_delay_variation,
          { "Delay Variation",        "bthci_cmd.delay_variation",
            FT_UINT32, BASE_DEC, NULL, 0x0,
            "Delay Variation, in microseconds", HFILL }
        },
        { &hf_bthci_cmd_link_policy_setting_switch,
          { "Enable Master Slave Switch", "bthci_cmd.link_policy_switch",
            FT_UINT16, BASE_DEC, VALS(cmd_boolean), 0x0001,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_link_policy_setting_hold,
          { "Enable Hold Mode", "bthci_cmd.link_policy_hold",
            FT_UINT16, BASE_DEC, VALS(cmd_boolean), 0x0002,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_link_policy_setting_sniff,
          { "Enable Sniff Mode", "bthci_cmd.link_policy_sniff",
            FT_UINT16, BASE_DEC, VALS(cmd_boolean), 0x0004,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_link_policy_setting_park,
          { "Enable Park Mode", "bthci_cmd.link_policy_park",
            FT_UINT16, BASE_DEC, VALS(cmd_boolean), 0x0008,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_filter_type,
          { "Filter Type", "bthci_cmd.filter_type",
            FT_UINT8, BASE_HEX, VALS(cmd_filter_types), 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_inquiry_result_filter_condition_type,
          { "Filter Condition Type", "bthci_cmd.filter_condition_type",
            FT_UINT8, BASE_HEX, VALS(cmd_inquiry_result_filter_condition_types), 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_connection_setup_filter_condition_type,
          { "Filter Condition Type", "bthci_cmd.filter_condition_type",
            FT_UINT8, BASE_HEX, VALS(cmd_connection_setup_filter_condition_types), 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_class_of_device,
          { "Class of Device", "bthci_cmd.class_of_device",
            FT_UINT24, BASE_HEX, NULL, 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_cod_major_service_class_information,
          { "Major Service Classes: Information", "bthci_cmd.class_of_device.major_service_classes.information",
            FT_BOOLEAN, 16, NULL, 0x8000,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_cod_major_service_class_telephony,
          { "Major Service Classes: Telephony", "bthci_cmd.class_of_device.major_service_classes.telephony",
            FT_BOOLEAN, 16, NULL, 0x4000,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_cod_major_service_class_audio,
          { "Major Service Classes: Audio", "bthci_cmd.class_of_device.major_service_classes.audio",
            FT_BOOLEAN, 16, NULL, 0x2000,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_cod_major_service_class_object_transfer,
          { "Major Service Classes: Object Transfer", "bthci_cmd.class_of_device.major_service_classes.object_transfer",
            FT_BOOLEAN, 16, NULL, 0x1000,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_cod_major_service_class_capturing,
          { "Major Service Classes: Capturing", "bthci_cmd.class_of_device.major_service_classes.capturing",
            FT_BOOLEAN, 16, NULL, 0x0800,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_cod_major_service_class_rendering,
          { "Major Service Classes: Rendering", "bthci_cmd.class_of_device.major_service_classes.rendering",
            FT_BOOLEAN, 16, NULL, 0x0400,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_cod_major_service_class_networking,
          { "Major Service Classes: Networking", "bthci_cmd.class_of_device.major_service_classes.networking",
            FT_BOOLEAN, 16, NULL, 0x0200,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_cod_major_service_class_positioning,
          { "Major Service Classes: Positioning", "bthci_cmd.class_of_device.major_service_classes.positioning",
            FT_BOOLEAN, 16, NULL, 0x0100,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_cod_major_service_class_reserved,
          { "Major Service Classes: Reserved", "bthci_cmd.class_of_device.major_service_classes.reserved",
            FT_UINT16, BASE_HEX, NULL, 0x00C0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_cod_major_service_class_limited_discoverable_mode,
          { "Major Service Classes: Limited Discoverable Mode", "bthci_cmd.class_of_device.major_service_classes.limited_discoverable_mode",
            FT_BOOLEAN, 16, NULL, 0x0020,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_cod_major_device_class,
          { "Major Device Class", "bthci_cmd.class_of_device.major_device_class",
            FT_UINT16, BASE_HEX | BASE_EXT_STRING, &bthci_cmd_cod_major_device_class_vals_ext, 0x1F,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_cod_minor_device_class_computer,
          { "Minor Device Class", "bthci_cmd.class_of_device.minor_device_class",
            FT_UINT8, BASE_HEX | BASE_EXT_STRING, &bthci_cmd_cod_minor_device_class_computer_vals_ext, 0xFC,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_cod_minor_device_class_phone,
          { "Minor Device Class", "bthci_cmd.class_of_device.minor_device_class",
            FT_UINT8, BASE_HEX | BASE_EXT_STRING, &bthci_cmd_cod_minor_device_class_phone_vals_ext, 0xFC,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_cod_minor_device_class_lan_net_load_factor,
          { "Minor Device Class: Load Factor", "bthci_cmd.class_of_device.minor_device_class.load_factor",
            FT_UINT8, BASE_HEX | BASE_EXT_STRING, &bthci_cmd_cod_minor_device_class_lan_net_load_factor_vals_ext, 0xE0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_cod_minor_device_class_lan_net_type,
          { "Minor Device Class: Type", "bthci_cmd.class_of_device.minor_device_class.type",
            FT_UINT8, BASE_HEX | BASE_EXT_STRING, &bthci_cmd_cod_minor_device_class_lan_net_type_vals_ext, 0x1C,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_cod_minor_device_class_audio_video,
          { "Minor Device Class", "bthci_cmd.class_of_device.minor_device_class",
            FT_UINT8, BASE_HEX | BASE_EXT_STRING, &bthci_cmd_cod_minor_device_class_audio_video_vals_ext, 0xFC,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_cod_minor_device_class_peripheral_class,
          { "Minor Device Class", "bthci_cmd.class_of_device.minor_device_class",
            FT_UINT8, BASE_HEX | BASE_EXT_STRING, &bthci_cmd_cod_minor_device_class_peripheral_class_vals_ext, 0xC0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_cod_minor_device_class_peripheral_type,
          { "Minor Device Class", "bthci_cmd.class_of_device.minor_device_class",
            FT_UINT8, BASE_HEX | BASE_EXT_STRING, &bthci_cmd_cod_minor_device_class_peripheral_type_vals_ext, 0x3C,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_cod_minor_device_class_imaging_class_printer,
          { "Minor Device Class: Class: Printer", "bthci_cmd.class_of_device.minor_device_class.class.printer",
            FT_UINT8, BASE_HEX | BASE_EXT_STRING, &bthci_cmd_cod_minor_device_class_imaging_type_vals_ext, 0x80,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_cod_minor_device_class_imaging_class_scanner,
          { "Minor Device Class: Class: Scanner", "bthci_cmd.class_of_device.minor_device_class.class.scanner",
            FT_UINT8, BASE_HEX | BASE_EXT_STRING, &bthci_cmd_cod_minor_device_class_imaging_type_vals_ext, 0x40,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_cod_minor_device_class_imaging_class_camera,
          { "Minor Device Class: Class: Camera", "bthci_cmd.class_of_device.minor_device_class.class.camera",
            FT_UINT8, BASE_HEX | BASE_EXT_STRING, &bthci_cmd_cod_minor_device_class_imaging_type_vals_ext, 0x20,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_cod_minor_device_class_imaging_class_display,
          { "Minor Device Class: Class: Display", "bthci_cmd.class_of_device.minor_device_class.class.display",
            FT_UINT8, BASE_HEX | BASE_EXT_STRING, &bthci_cmd_cod_minor_device_class_imaging_type_vals_ext, 0x10,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_cod_minor_device_class_imaging_type,
          { "Minor Device Class: Type", "bthci_cmd.class_of_device.minor_device_class.type",
            FT_UINT8, BASE_HEX | BASE_EXT_STRING, &bthci_cmd_cod_minor_device_class_imaging_type_vals_ext, 0x0C,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_cod_minor_device_class_wearable,
          { "Minor Device Class", "bthci_cmd.class_of_device.minor_device_class",
            FT_UINT8, BASE_HEX | BASE_EXT_STRING, &bthci_cmd_cod_minor_device_class_wearable_vals_ext, 0xFC,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_cod_minor_device_class_toy,
          { "Minor Device Class", "bthci_cmd.class_of_device.minor_device_class",
            FT_UINT8, BASE_HEX | BASE_EXT_STRING, &bthci_cmd_cod_minor_device_class_toy_vals_ext, 0xFC,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_cod_minor_device_class_health,
          { "Minor Device Class", "bthci_cmd.class_of_device.minor_device_class",
            FT_UINT8, BASE_HEX | BASE_EXT_STRING, &bthci_cmd_cod_minor_device_class_health_vals_ext, 0xFC,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_cod_minor_device_class_unknown,
          { "Minor Device Class", "bthci_cmd.class_of_device.minor_device_class",
            FT_UINT8, BASE_HEX, NULL, 0xFC,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_cod_format_type,
          { "Format Type", "bthci_cmd.class_of_device.format_type",
            FT_UINT8, BASE_HEX, NULL, 0x03,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_class_of_device_mask,
          { "Class of Device Mask", "bthci_cmd.class_of_device_mask",
            FT_UINT24, BASE_HEX, NULL, 0x0,
            "Bit Mask used to determine which bits of the Class of Device parameter are of interest.", HFILL }
        },
        { &hf_bthci_cmd_cod_major_device_class_mask,
          { "Major Device Class Mask", "bthci_cmd.class_of_device_mask.major_device_class",
            FT_UINT16, BASE_HEX, NULL, 0x1F,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_cod_major_service_class_information_mask,
          { "Major Service Classes Mask: Information", "bthci_cmd.class_of_device_mask.major_service_classes.information",
            FT_BOOLEAN, 16, NULL, 0x8000,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_cod_major_service_class_telephony_mask,
          { "Major Service Classes Mask: Telephony", "bthci_cmd.class_of_device_mask.major_service_classes.telephony",
            FT_BOOLEAN, 16, NULL, 0x4000,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_cod_major_service_class_audio_mask,
          { "Major Service Classes Mask: Audio", "bthci_cmd.class_of_device_mask.major_service_classes.audio",
            FT_BOOLEAN, 16, NULL, 0x2000,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_cod_major_service_class_object_transfer_mask,
          { "Major Service Classes Mask: Object Transfer", "bthci_cmd.class_of_device_mask.major_service_classes.object_transfer",
            FT_BOOLEAN, 16, NULL, 0x1000,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_cod_major_service_class_capturing_mask,
          { "Major Service Classes Mask: Capturing", "bthci_cmd.class_of_device_mask.major_service_classes.capturing",
            FT_BOOLEAN, 16, NULL, 0x0800,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_cod_major_service_class_rendering_mask,
          { "Major Service Classes Mask: Rendering", "bthci_cmd.class_of_device_mask.major_service_classes.rendering",
            FT_BOOLEAN, 16, NULL, 0x0400,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_cod_major_service_class_networking_mask,
          { "Major Service Classes Mask: Networking", "bthci_cmd.class_of_device_mask.major_service_classes.networking",
            FT_BOOLEAN, 16, NULL, 0x0200,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_cod_major_service_class_positioning_mask,
          { "Major Service Classes Mask: Positioning", "bthci_cmd.class_of_device_mask.major_service_classes.positioning",
            FT_BOOLEAN, 16, NULL, 0x0100,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_cod_major_service_class_reserved_mask,
          { "Major Service Classes Mask: Reserved", "bthci_cmd.class_of_device_mask.major_service_classes.reserved",
            FT_UINT16, BASE_HEX, NULL, 0x00C0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_cod_major_service_class_limited_discoverable_mode_mask,
          { "Major Service Classes Mask: Limited Discoverable Mode", "bthci_cmd.class_of_device_mask.major_service_classes.limited_discoverable_mode",
            FT_BOOLEAN, 16, NULL, 0x0020,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_cod_minor_device_class_mask,
          { "Minor Device Class Mask", "bthci_cmd.class_of_device_mask.minor_device_class",
            FT_UINT8, BASE_HEX, NULL, 0xFC,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_cod_format_type_mask,
          { "Format Type Mask", "bthci_cmd.class_of_device_mask.format_type",
            FT_UINT8, BASE_HEX, NULL, 0x03,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_auto_acc_flag,
          { "Auto Accept Flag", "bthci_cmd.auto_accept_flag",
            FT_UINT8, BASE_HEX, VALS(cmd_auto_acc_flag_values), 0x0,
            "Class of Device of Interest", HFILL }
        },
        { &hf_bthci_cmd_read_all_flag,
          { "Read All Flag", "bthci_cmd.read_all_flag",
            FT_UINT8, BASE_HEX, VALS(cmd_read_all_flag_values), 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_delete_all_flag,
          { "Delete All Flag", "bthci_cmd.delete_all_flag",
            FT_UINT8, BASE_HEX, VALS(cmd_delete_all_flag_values), 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_authentication_enable,
          { "Authentication Enable", "bthci_cmd.auth_enable",
            FT_UINT8, BASE_HEX, VALS(cmd_authentication_enable_values), 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_input_unused,
          { "Unused bits", "bthci_cmd.voice.unused",
            FT_UINT16, BASE_HEX, NULL, 0xfc00,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_input_coding,
          { "Input Coding", "bthci_cmd.voice.input_coding",
            FT_UINT16, BASE_DEC, VALS(cmd_input_coding_values), 0x0300,
            "Authentication Enable", HFILL }
        },
        { &hf_bthci_cmd_input_data_format,
          { "Input Data Format", "bthci_cmd.voice.input_data_format",
            FT_UINT16, BASE_DEC, VALS(cmd_input_data_format_values), 0x00c0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_input_sample_size,
          { "Input Sample Size", "bthci_cmd.voice.input_sample_size",
            FT_UINT16, BASE_DEC, VALS(cmd_input_sample_size_values), 0x0020,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_linear_pcm_bit_pos,
          { "Linear PCM Bit Position", "bthci_cmd.voice.linear_pcm_bit_pos",
            FT_UINT16, BASE_DEC, NULL, 0x001c,
            "# bit pos. that MSB of sample is away from starting at MSB", HFILL }
        },
        { &hf_bthci_cmd_air_coding_format,
          { "Air Coding Format", "bthci_cmd.voice.air_coding_format",
            FT_UINT16, BASE_DEC, VALS(cmd_air_coding_format_values), 0x0003,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_num_broadcast_retransmissions,
          { "Num Broadcast Retran", "bthci_cmd.num_broad_retran",
            FT_UINT8, BASE_DEC, NULL, 0x0,
            "Number of Broadcast Retransmissions", HFILL }
        },
        { &hf_bthci_cmd_hold_mode_act_page,
          { "Suspend Page Scan", "bthci_cmd.hold_mode_page",
            FT_UINT8, BASE_DEC, VALS(cmd_boolean), 0x1,
            "Device can enter low power state", HFILL }
        },
        { &hf_bthci_cmd_hold_mode_act_inquiry,
          { "Suspend Inquiry Scan", "bthci_cmd.hold_mode_inquiry",
            FT_UINT8, BASE_DEC, VALS(cmd_boolean), 0x2,
            "Device can enter low power state", HFILL }
        },
        { &hf_bthci_cmd_hold_mode_act_periodic,
          { "Suspend Periodic Inquiries", "bthci_cmd.hold_mode_periodic",
            FT_UINT8, BASE_DEC, VALS(cmd_boolean), 0x4,
            "Device can enter low power state", HFILL }
        },
        { &hf_bthci_cmd_scan_enable,
          { "Scan Enable", "bthci_cmd.scan_enable",
            FT_UINT8, BASE_HEX, VALS(bthci_cmd_scan_enable_values), 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_interval,
          { "Interval", "bthci_cmd.interval",
            FT_UINT16, BASE_DEC, NULL, 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_window,
          { "Interval", "bthci_cmd.window",
            FT_UINT16, BASE_DEC, NULL, 0x0,
            "Window", HFILL }
        },
        { &hf_bthci_cmd_device_name,
          { "Device Name",           "bthci_cmd.device_name",
            FT_STRINGZ, BASE_NONE, NULL, 0x0,
            "Userfriendly descriptive name for the device", HFILL }
        },
        { &hf_bthci_cmd_num_curr_iac,
          { "Number of Current IAC", "bthci_cmd.num_curr_iac",
            FT_UINT8, BASE_DEC, NULL, 0x0,
            "Number of IACs which are currently in use", HFILL }
        },
        { &hf_bthci_cmd_iac_lap,
          { "IAC LAP", "bthci_cmd.num_curr_iac",
            FT_UINT24, BASE_HEX, NULL, 0x0,
            "LAP(s)used to create IAC", HFILL }
        },
        { &hf_bthci_cmd_evt_mask_00,
          { "Inquiry Complete", "bthci_cmd.evt_mask_00",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x01,
            "Inquiry Complete Bit", HFILL }
        },
        { &hf_bthci_cmd_evt_mask_01,
          { "Inquiry Result", "bthci_cmd.evt_mask_01",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x02,
            "Inquiry Result Bit", HFILL }
        },
        { &hf_bthci_cmd_evt_mask_02,
          { "Connect Complete", "bthci_cmd.evt_mask_02",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x04,
            "Connection Complete Bit", HFILL }
        },
        { &hf_bthci_cmd_evt_mask_03,
          { "Connect Request", "bthci_cmd.evt_mask_03",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x08,
            "Connect Request Bit", HFILL }
        },
        { &hf_bthci_cmd_evt_mask_04,
          { "Disconnect Complete", "bthci_cmd.evt_mask_04",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x10,
            "Disconnect Complete Bit", HFILL }
        },
        { &hf_bthci_cmd_evt_mask_05,
          { "Auth Complete", "bthci_cmd.evt_mask_05",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x20,
            "Auth Complete Bit", HFILL }
        },
        { &hf_bthci_cmd_evt_mask_06,
          { "Remote Name Req Complete", "bthci_cmd.evt_mask_06",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x40,
            "Remote Name Req Complete Bit", HFILL }
        },
        { &hf_bthci_cmd_evt_mask_07,
          { "Encrypt Change", "bthci_cmd.evt_mask_07",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x80,
            "Encrypt Change Bit", HFILL }
        },
        { &hf_bthci_cmd_evt_mask_10,
          { "Change Connection Link Key Complete", "bthci_cmd.evt_mask_10",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x01,
            "Change Connection Link Key Complete Bit", HFILL }
        },
        { &hf_bthci_cmd_evt_mask_11,
          { "Master Link Key Complete", "bthci_cmd.evt_mask_11",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x02,
            "Master Link Key Complete Bit", HFILL }
        },
        { &hf_bthci_cmd_evt_mask_12,
          { "Read Remote Supported Features", "bthci_cmd.evt_mask_12",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x04,
            "Read Remote Supported Features Bit", HFILL }
        },
        { &hf_bthci_cmd_evt_mask_13,
          { "Read Remote Ver Info Complete", "bthci_cmd.evt_mask_13",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x08,
            "Read Remote Ver Info Complete Bit", HFILL }
        },
        { &hf_bthci_cmd_evt_mask_14,
          { "QoS Setup Complete", "bthci_cmd.evt_mask_14",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x10,
            "QoS Setup Complete Bit", HFILL }
        },
        { &hf_bthci_cmd_evt_mask_17,
          { "Hardware Error", "bthci_cmd.evt_mask_17",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x80,
            "Hardware Error Bit", HFILL }
        },
        { &hf_bthci_cmd_evt_mask_20,
          { "Flush Occurred", "bthci_cmd.evt_mask_20",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x01,
            "Flush Occurred Bit", HFILL }
        },
        { &hf_bthci_cmd_evt_mask_21,
          { "Role Change", "bthci_cmd.evt_mask_21",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x02,
            "Role Change Bit", HFILL }
        },
        { &hf_bthci_cmd_evt_mask_23,
          { "Mode Change", "bthci_cmd.evt_mask_23",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x08,
            "Mode Change Bit", HFILL }
        },
        { &hf_bthci_cmd_evt_mask_24,
          { "Return Link Keys", "bthci_cmd.evt_mask_24",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x10,
            "Return Link Keys Bit", HFILL }
        },
        { &hf_bthci_cmd_evt_mask_25,
          { "PIN Code Request", "bthci_cmd.evt_mask_25",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x20,
            "PIN Code Request Bit", HFILL }
        },
        { &hf_bthci_cmd_evt_mask_26,
          { "Link Key Request", "bthci_cmd.evt_mask_26",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x40,
            "Link Key Request Bit", HFILL }
        },
        { &hf_bthci_cmd_evt_mask_27,
          { "Link Key Notification", "bthci_cmd.evt_mask_27",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x80,
            "Link Key Notification Bit", HFILL }
        },
        { &hf_bthci_cmd_evt_mask_30,
          { "Loopback Command", "bthci_cmd.evt_mask_30",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x01,
            "Loopback Command Bit", HFILL }
        },
        { &hf_bthci_cmd_evt_mask_31,
          { "Data Buffer Overflow" , "bthci_cmd.evt_mask_31",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x02,
            "Data Buffer Overflow Bit", HFILL }
        },
        { &hf_bthci_cmd_evt_mask_32,
          { "Max Slots Change", "bthci_cmd.evt_mask_32",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x04,
            "Max Slots Change Bit", HFILL }
        },
        { &hf_bthci_cmd_evt_mask_33,
          { "Read Clock Offset Complete", "bthci_cmd.evt_mask_33",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x08,
            "Read Clock Offset Complete Bit", HFILL }
        },
        { &hf_bthci_cmd_evt_mask_34,
          { "Connection Packet Type Changed", "bthci_cmd.evt_mask_34",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x10,
            "Connection Packet Type Changed Bit", HFILL }
        },
        { &hf_bthci_cmd_evt_mask_35,
          { "QoS Violation", "bthci_cmd.evt_mask_35",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x20,
            "QoS Violation Bit", HFILL }
        },
        { &hf_bthci_cmd_evt_mask_36,
          { "Page Scan Mode Change", "bthci_cmd.evt_mask_36",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x40,
            "Page Scan Mode Change Bit", HFILL }
        },
        { &hf_bthci_cmd_evt_mask_37,
          { "Page Scan Repetition Mode Change", "bthci_cmd.evt_mask_37",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x80,
            "Page Scan Repetition Mode Change Bit", HFILL }
        },
        { &hf_bthci_cmd_evt_mask_40,
          { "Flow Specification Complete", "bthci_cmd.evt_mask_40",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x01,
            "Flow Specification Complete Bit", HFILL }
        },
        { &hf_bthci_cmd_evt_mask_41,
          { "Inquiry Result With RSSI", "bthci_cmd.evt_mask_41",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x02,
            "Inquiry Result With RSSI Bit", HFILL }
        },
        { &hf_bthci_cmd_evt_mask_42,
          { "Read Remote Ext. Features Complete", "bthci_cmd.evt_mask_42",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x04,
            "Read Remote Ext. Features Complete Bit", HFILL }
        },
        { &hf_bthci_cmd_evt_mask_53,
          { "Synchronous Connection Complete", "bthci_cmd.evt_mask_53",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x08,
            "Synchronous Connection Complete Bit", HFILL }
        },
        { &hf_bthci_cmd_evt_mask_54,
          { "Synchronous Connection Changed", "bthci_cmd.evt_mask_54",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x10,
            "Synchronous Connection Changed Bit", HFILL }
        },
        { &hf_bthci_cmd_evt_mask_55,
          { "Sniff Subrate", "bthci_cmd.evt_mask_55",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x20,
            "Sniff Subrate Bit", HFILL }
        },
        { &hf_bthci_cmd_evt_mask_56,
          { "Extended Inquiry Result", "bthci_cmd.evt_mask_56",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x40,
            "Extended Inquiry Result Bit", HFILL }
        },
        { &hf_bthci_cmd_evt_mask_57,
          { "Encryption Key Refresh Complete", "bthci_cmd.evt_mask_57",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x80,
            "Encryption Key Refresh Complete Bit", HFILL }
        },
        { &hf_bthci_cmd_evt_mask_60,
          { "IO Capability Request", "bthci_cmd.evt_mask_60",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x01,
            "IO Capability Request Bit", HFILL }
        },
        { &hf_bthci_cmd_evt_mask_61,
          { "IO Capability Response", "bthci_cmd.evt_mask_61",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x02,
            "IO Capability Response Bit", HFILL }
        },
        { &hf_bthci_cmd_evt_mask_62,
          { "User Confirmation Request", "bthci_cmd.evt_mask_62",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x04,
            "User Confirmation Request Bit", HFILL }
        },
        { &hf_bthci_cmd_evt_mask_63,
          { "User Passkey Request", "bthci_cmd.evt_mask_63",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x08,
            "User Passkey Request Bit", HFILL }
        },
        { &hf_bthci_cmd_evt_mask_64,
          { "Remote OOB Data Request", "bthci_cmd.evt_mask_64",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x10,
            "Remote OOB Data Request Bit", HFILL }
        },
        { &hf_bthci_cmd_evt_mask_65,
          { "Simple Pairing Complete", "bthci_cmd.evt_mask_65",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x20,
            "Simple Pairing Complete Bit", HFILL }
        },
        { &hf_bthci_cmd_evt_mask_67,
          { "Link Supervision Timeout Changed", "bthci_cmd.evt_mask_67",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x80,
            "Link Supervision Timeout Changed Bit", HFILL }
        },
        { &hf_bthci_cmd_evt_mask_70,
          { "Enhanced Flush Complete", "bthci_cmd.evt_mask_70",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x01,
            "Enhanced Flush Complete Bit", HFILL }
        },
        { &hf_bthci_cmd_evt_mask_72,
          { "User Passkey Notification", "bthci_cmd.evt_mask_72",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x04,
            "User Passkey Notification Bit", HFILL }
        },
        { &hf_bthci_cmd_evt_mask_73,
          { "Keypress Notification", "bthci_cmd.evt_mask_73",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x08,
            "Keypress Notification Bit", HFILL }
        },
        { &hf_bthci_cmd_sco_flow_control,
          { "SCO Flow Control","bthci_cmd.flow_control",
            FT_UINT8, BASE_HEX, VALS(cmd_en_disabled), 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_num_handles,
          { "Number of Handles", "bthci_cmd.num_handles",
            FT_UINT8, BASE_DEC, NULL, 0x0,
            NULL, HFILL }
        },

        { &hf_bthci_cmd_num_compl_packets,
          { "Number of Completed Packets", "bthci_cmd.num_compl_packets",
            FT_UINT16, BASE_DEC, NULL, 0x0,
            "Number of Completed HCI Data Packets", HFILL }
        },
        { &hf_bthci_cmd_flow_contr_enable,
          { "Flow Control Enable", "bthci_cmd.flow_contr_enable",
            FT_UINT8, BASE_HEX, VALS(cmd_flow_contr_enable), 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_host_data_packet_length_acl,
          {"Host ACL Data Packet Length (bytes)", "bthci_cmd.max_data_length_acl",
           FT_UINT16, BASE_DEC, NULL, 0x0,
           "Max Host ACL Data Packet length of data portion host is able to accept", HFILL }
        },
        { &hf_bthci_cmd_host_data_packet_length_sco,
          {"Host SCO Data Packet Length (bytes)", "bthci_cmd.max_data_length_sco",
           FT_UINT8, BASE_DEC, NULL, 0x0,
           "Max Host SCO Data Packet length of data portion host is able to accept", HFILL }
        },
        { &hf_bthci_cmd_host_total_num_acl_data_packets,
          {"Host Total Num ACL Data Packets", "bthci_cmd.max_data_num_acl",
           FT_UINT16, BASE_DEC, NULL, 0x0,
           "Total Number of HCI ACL Data Packets that can be stored in the data buffers of the Host", HFILL }
        },
        { &hf_bthci_cmd_host_total_num_sco_data_packets,
          {"Host Total Num SCO Data Packets", "bthci_cmd.max_data_num_sco",
           FT_UINT16, BASE_DEC, NULL, 0x0,
           "Total Number of HCI SCO Data Packets that can be stored in the data buffers of the Host", HFILL }
        },
        { &hf_bthci_cmd_loopback_mode,
          {"Loopback Mode", "bthci_cmd.loopback_mode",
           FT_UINT8, BASE_HEX, VALS(cmd_loopback_modes), 0x0,
           NULL, HFILL}
        },
        { &hf_bthci_cmd_page_number,
          {"Page Number", "bthci_cmd.page_number",
           FT_UINT8, BASE_DEC, NULL, 0x0,
           NULL, HFILL}
        },
        { &hf_bthci_cmd_transmit_bandwidth,
          {"Tx Bandwidth (bytes/s)", "bthci_cmd.tx_bandwidth",
           FT_UINT32, BASE_DEC, NULL, 0x0,
           "Tx Bandwidth", HFILL}
        },
        { &hf_bthci_cmd_receive_bandwidth,
          {"Rx Bandwidth (bytes/s)", "bthci_cmd.rx_bandwidth",
           FT_UINT32, BASE_DEC, NULL, 0x0,
           "Rx Bandwidth", HFILL}
        },
        { &hf_bthci_cmd_max_latency_ms,
          {"Max. Latency (ms)", "bthci_cmd.max_latency_ms",
           FT_UINT16, BASE_DEC, NULL, 0x0,
           NULL, HFILL}
        },
        { &hf_bthci_cmd_max_latency,
          {"Max. Latency", "bthci_cmd.max_latency",
           FT_UINT16, BASE_DEC, NULL, 0x0,
           "Max. Latency in baseband slots", HFILL}
        },
        { &hf_bthci_cmd_retransmission_effort,
          {"Retransmission Effort", "bthci_cmd.retransmission_effort",
           FT_UINT8, BASE_DEC, VALS(cmd_rtx_effort), 0x0,
           NULL, HFILL}
        },
        { &hf_bthci_cmd_scan_type,
          {"Scan Type", "bthci_cmd.inq_scan_type",
           FT_UINT8, BASE_DEC, VALS(cmd_scan_types), 0x0,
           NULL, HFILL}
        },
        { &hf_bthci_cmd_inq_mode,
          {"Inquiry Mode", "bthci_cmd.inq_scan_type",
           FT_UINT8, BASE_DEC, VALS(cmd_inq_modes), 0x0,
           NULL, HFILL}
        },
        { &hf_bthci_cmd_fec_required,
          {"FEC Required", "bthci_cmd.fec_required",
           FT_UINT8, BASE_DEC, VALS(cmd_boolean), 0x0,
           NULL, HFILL}
        },
        { &hf_bthci_cmd_err_data_reporting,
          {"Erroneous Data Reporting", "bthci_cmd.err_data_reporting",
           FT_UINT8, BASE_DEC, VALS(cmd_en_disabled), 0x0,
           NULL, HFILL}
        },
        { &hf_bthci_cmd_tx_power,
          {"Power Level (dBm)", "bthci_cmd.power_level",
           FT_INT8, BASE_DEC, NULL, 0x0,
           NULL, HFILL}
        },
        { &hf_bthci_cmd_sco_packet_type_hv1,
          { "Packet Type HV1",        "bthci_cmd.sco_packet_type_hv1",
            FT_UINT16, BASE_DEC, VALS(cmd_boolean), 0x0001,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_sco_packet_type_hv2,
          { "Packet Type HV2",        "bthci_cmd.sco_packet_type_hv2",
            FT_UINT16, BASE_DEC, VALS(cmd_boolean), 0x0002,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_sco_packet_type_hv3,
          { "Packet Type HV3",        "bthci_cmd.sco_packet_type_hv3",
            FT_UINT16, BASE_DEC, VALS(cmd_boolean), 0x0004,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_sco_packet_type_ev3,
          { "Packet Type EV3",        "bthci_cmd.sco_packet_type_ev3",
            FT_UINT16, BASE_DEC, VALS(cmd_boolean), 0x0008,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_sco_packet_type_ev4,
          { "Packet Type EV4",        "bthci_cmd.sco_packet_type_ev4",
            FT_UINT16, BASE_DEC, VALS(cmd_boolean), 0x0010,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_sco_packet_type_ev5,
          { "Packet Type EV5",        "bthci_cmd.sco_packet_type_ev5",
            FT_UINT16, BASE_DEC, VALS(cmd_boolean), 0x0020,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_sco_packet_type_2ev3,
          { "Packet Type 2-EV3",        "bthci_cmd.sco_packet_type_2ev3",
            FT_UINT16, BASE_DEC, VALS(cmd_boolean), 0x0040,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_sco_packet_type_3ev3,
          { "Packet Type 3-EV3",        "bthci_cmd.sco_packet_type_3ev3",
            FT_UINT16, BASE_DEC, VALS(cmd_boolean), 0x0080,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_sco_packet_type_2ev5,
          { "Packet Type 2-EV5",        "bthci_cmd.sco_packet_type_2ev5",
            FT_UINT16, BASE_DEC, VALS(cmd_boolean), 0x0100,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_sco_packet_type_3ev5,
          { "Packet Type 3-EV5",        "bthci_cmd.sco_packet_type_3ev5",
            FT_UINT16, BASE_DEC, VALS(cmd_boolean), 0x0200,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_min_remote_timeout,
          {"Min. Remote Timeout", "bthci_cmd.min_remote_timeout",
           FT_UINT16, BASE_DEC, NULL, 0x0,
           "Min. Remote Timeout in baseband slots", HFILL}
        },
        { &hf_bthci_cmd_min_local_timeout,
          {"Min. Local Timeout", "bthci_cmd.min_local_timeout",
           FT_UINT16, BASE_DEC, NULL, 0x0,
           "Min. Local Timeout in baseband slots", HFILL}
        },
        { &hf_bthci_cmd_flush_packet_type,
          {"Packet Type", "bthci_cmd.flush_packet_type",
           FT_UINT8, BASE_DEC, VALS(cmd_flush_pkt_type), 0x0,
           NULL, HFILL}
        },
        { &hf_bthci_cmd_afh_ch_assessment_mode,
          {"AFH Channel Assessment Mode", "bthci_cmd.afh_ch_assessment_mode",
           FT_UINT8, BASE_DEC, VALS(cmd_en_disabled), 0x0,
           NULL, HFILL}
        },
        { &hf_bthci_cmd_afh_ch_classification,
          { "Channel Classification",           "bthci_cmd.afh_ch_classification",
            FT_NONE, BASE_NONE, NULL, 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_which_clock,
          {"Which Clock", "bthci_cmd.which_clock",
           FT_UINT8, BASE_DEC, VALS(cmd_which_clock), 0x0,
           NULL, HFILL}
        },
        { &hf_bthci_cmd_io_capability,
          {"IO Capability", "bthci_cmd.io_capability",
           FT_UINT8, BASE_DEC, VALS(bthci_cmd_io_capability_vals), 0x0,
           NULL, HFILL}
        },
        { &hf_bthci_cmd_oob_data_present,
          {"OOB Data Present", "bthci_cmd.oob_data_present",
           FT_UINT8, BASE_DEC, VALS(bthci_cmd_oob_data_present_vals), 0x0,
           NULL, HFILL}
        },
        { &hf_bthci_cmd_auth_requirements,
          {"Authentication Requirements", "bthci_cmd.auth_requirements",
           FT_UINT8, BASE_DEC|BASE_EXT_STRING, &bthci_cmd_auth_req_vals_ext, 0x0,
           NULL, HFILL}
        },
        { &hf_bthci_cmd_passkey,
          {"Passkey", "bthci_cmd.passkey",
           FT_UINT32, BASE_DEC, NULL, 0x0,
           NULL, HFILL}
        },
        { &hf_bthci_cmd_hash_c,
          {"Hash C", "bthci_cmd.hash_c",
           FT_BYTES, BASE_NONE, NULL, 0x0,
           NULL, HFILL}
        },
        { &hf_bthci_cmd_randomizer_r,
          {"Randomizer R", "bthci_cmd.randomizer_r",
           FT_BYTES, BASE_NONE, NULL, 0x0,
           NULL, HFILL}
        },
        { &hf_bthci_cmd_simple_pairing_mode,
          {"Simple Pairing Mode", "bthci_cmd.simple_pairing_mode",
           FT_UINT8, BASE_DEC, VALS(cmd_en_disabled), 0x0,
           NULL, HFILL}
        },
        { &hf_bthci_cmd_simple_pairing_debug_mode,
          {"Simple Pairing Debug Mode", "bthci_cmd.simple_pairing_debug_mode",
           FT_UINT8, BASE_DEC, VALS(cmd_en_disabled), 0x0,
           NULL, HFILL}
        },
        { &hf_bthci_cmd_notification_type,
          {"Notification Type", "bthci_cmd.notification_type",
           FT_UINT8, BASE_DEC, VALS(bthci_cmd_notification_types), 0x0,
           NULL, HFILL}
        },
        { &hf_bthci_cmd_eir_data,
          {"Data", "bthci_cmd.eir_data",
           FT_BYTES, BASE_NONE, NULL, 0x0,
           NULL, HFILL}
        },
        { &hf_bthci_cmd_eir_struct_length,
          { "Length",           "bthci_cmd.eir_struct_length",
            FT_UINT8, BASE_DEC, NULL, 0x0,
            "Structure Length", HFILL }
        },
        { &hf_bthci_cmd_eir_struct_type,
          { "Type",           "bthci_cmd.eir_data_type",
            FT_UINT8, BASE_HEX|BASE_EXT_STRING, &bthci_cmd_eir_data_type_vals_ext, 0x0,
            "Data Type", HFILL }
        },
        { &hf_bthci_cmd_sc_uuid16,
          { "UUID",           "bthci_cmd.service_class_uuid16",
            FT_UINT16, BASE_HEX|BASE_EXT_STRING, &bthci_cmd_service_class_type_vals_ext, 0x0,
            "16-bit Service Class UUID", HFILL }
        },
        { &hf_bthci_cmd_sc_uuid32,
          { "UUID",           "bthci_cmd.service_class_uuid32",
            FT_UINT32, BASE_HEX, NULL, 0x0,
            "32-bit Service Class UUID", HFILL }
        },
        { &hf_bthci_cmd_sc_uuid128,
          { "UUID",           "bthci_cmd.service_class_uuid128",
            FT_BYTES, BASE_NONE, NULL, 0x0,
            "128-bit Service Class UUID", HFILL }
        },
        { &hf_bthci_cmd_physical_link_handle,
          {"Physical Link Handle", "bthci_cmd.physical_link_handle",
            FT_UINT8, BASE_HEX, NULL, 0x0,
            NULL, HFILL}
        },
        { &hf_bthci_cmd_dedicated_amp_key_length,
          {"Dedicated AMP Key Length", "bthci_cmd.dedicated_amp_key_length",
            FT_UINT8, BASE_DEC, NULL, 0x0,
            NULL, HFILL}
        },
        { &hf_bthci_cmd_dedicated_amp_key_type,
          {"Dedicated AMP Key Type", "bthci_cmd.dedicated_amp_key_type",
            FT_UINT8, BASE_DEC, VALS(bthci_cmd_amp_key_type), 0x0,
            NULL, HFILL}
        },
        { &hf_bthci_cmd_dedicated_amp_key,
          {"Dedicated AMP Key Type", "bthci_cmd.dedicated_amp_key",
            FT_BYTES, BASE_NONE, NULL, 0x0,
            NULL, HFILL}
        },
        { &hf_bthci_cmd_flow_spec,
          { "Flow Spec", "bthci_cmd.flow_spec",
            FT_NONE, BASE_NONE, NULL, 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_flow_spec_sdu_size,
          { "Maximum SDU Size", "bthci_cmd.sdu_size",
            FT_UINT16, BASE_DEC, NULL, 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_flow_spec_sdu_arrival_time,
          { "SDU Inter-arrival Time (us)", "bthci_cmd.sdu_arrival_time",
            FT_UINT32, BASE_DEC, NULL, 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_flow_spec_identifier,
          { "Identifier", "bthci_cmd.ident",
            FT_UINT8, BASE_HEX, NULL, 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_flow_spec_access_latency,
          { "Access Latency (us)", "bthci_cmd.access_latency",
            FT_UINT32, BASE_DEC, NULL, 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_flow_spec_service_type,
          { "Service Type", "bthci_cmd.servicetype",
            FT_UINT8, BASE_HEX, VALS(cmd_flow_spec_servicetype), 0x0,
            "Level of service required", HFILL }
        },
        { &hf_bthci_cmd_flush_to_us,
          { "Flush Timeout (us)", "bthci_cmd.flushto",
            FT_UINT32, BASE_DEC, NULL, 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_logical_link_handle,
          { "Logical Link Handle", "bthci_cmd.logical_link_handle",
            FT_UINT16, BASE_HEX, NULL, 0x0FFF,
            NULL, HFILL }
        },

        { &hf_bthci_cmd_evt_mask2_00,
          { "Physical Link Complete", "bthci_cmd.evt_mask2_00",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x01,
            "Physical Link Complete Bit", HFILL }
        },
        { &hf_bthci_cmd_evt_mask2_01,
          { "Channel Selected", "bthci_cmd.evt_mask2_01",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x02,
            "Channel Selected Bit", HFILL }
        },
        { &hf_bthci_cmd_evt_mask2_02,
          { "Disconnection Physical Link", "bthci_cmd.evt_mask2_02",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x04,
            "Disconnection Physical Link Bit", HFILL }
        },
        { &hf_bthci_cmd_evt_mask2_03,
         { "Physical Link Loss Early Warning", "bthci_cmd.evt_mask2_03",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x08,
            "Physical Link Loss Early Warning Bit", HFILL }
        },
        { &hf_bthci_cmd_evt_mask2_04,
          { "Physical Link Recovery", "bthci_cmd.evt_mask2_04",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x10,
            "Physical Link Recovery Bit", HFILL }
        },
        { &hf_bthci_cmd_evt_mask2_05,
          { "Logical Link Complete", "bthci_cmd.evt_mask2_05",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x20,
            "Logical Link Complete Bit", HFILL }
        },
        { &hf_bthci_cmd_evt_mask2_06,
          { "Disconnection Logical Link Complete", "bthci_cmd.evt_mask2_06",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x40,
            "Disconnection Logical Link Complete Bit", HFILL }
        },
        { &hf_bthci_cmd_evt_mask2_07,
          { "Flow Spec Modify Complete", "bthci_cmd.evt_mask2_07",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x80,
            "Flow Spec Modify Complete Bit", HFILL }
        },
        { &hf_bthci_cmd_evt_mask2_10,
          { "Number Of Completed Data Blocks", "bthci_cmd.evt_mask2_10",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x01,
            "Number Of Completed Data Blocks Bit", HFILL }
        },
        { &hf_bthci_cmd_evt_mask2_11,
          { "AMP Start Test", "bthci_cmd.evt_mask2_11",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x02,
            "AMP Start Test Bit", HFILL }
        },
        { &hf_bthci_cmd_evt_mask2_12,
          { "AMP Test End", "bthci_cmd.evt_mask2_12",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x04,
            "AMP Test End Bit", HFILL }
        },
        { &hf_bthci_cmd_evt_mask2_13,
          { "AMP Receiver Report", "bthci_cmd.evt_mask2_13",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x08,
            "AMP Receiver Report Bit", HFILL }
        },
        { &hf_bthci_cmd_evt_mask2_14,
          { "Short Range Mode Change Complete", "bthci_cmd.evt_mask2_14",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x10,
            "Short Range Mode Change Complete Bit", HFILL }
        },
        { &hf_bthci_cmd_evt_mask2_15,
          { "AMP Status Change", "bthci_cmd.evt_mask2_15",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x20,
            "AMP Status Change Bit", HFILL }
        },
        { &hf_bthci_cmd_location_domain_aware,
          { "Location Domain Aware", "bthci_cmd.location_domain_aware",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_location_domain,
          { "Location Domain", "bthci_cmd.location_domain",
            FT_STRING, BASE_NONE, NULL, 0x0,
            "ISO 3166-1 Country Code", HFILL }
        },
        { &hf_bthci_cmd_location_domain_options,
          { "Location Domain Options", "bthci_cmd.location_domain_options",
            FT_STRING, BASE_NONE, NULL, 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_location_options,
          { "Location Options", "bthci_cmd.location_options",
            FT_UINT8, BASE_HEX, NULL, 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_flow_control_mode,
          { "Flow Control Mode", "bthci_cmd.flow_control_mode",
            FT_UINT8, BASE_HEX, VALS(cmd_flow_ctrl_mode), 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_tx_power_level_type,
          { "Tx Power Level Type", "bthci_cmd.tx_power_level_type",
            FT_UINT8, BASE_HEX, VALS(cmd_power_level_types), 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_short_range_mode,
          { "Short Range Mode", "bthci_cmd.short_range_mode",
            FT_UINT8, BASE_HEX, VALS(cmd_en_disabled), 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_enable_amp_recv_reports,
          { "Enable AMP Receiver Reports", "bthci_cmd.enable_amp_recv_reports",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_amp_recv_report_interval,
          { "AMP Receiver Report Interval (s)", "bthci_cmd.amp_recv_report_interval",
            FT_UINT8, BASE_DEC, 0x0, 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_length_so_far,
          { "Length So Far", "bthci_cmd.length_so_far",
            FT_UINT16, BASE_DEC, 0x0, 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_amp_assoc_length,
          { "AMP Assoc Length", "bthci_cmd.amp_assoc_length",
            FT_UINT16, BASE_DEC, 0x0, 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_amp_remaining_assoc_length,
          { "AMP Remaining Assoc Length", "bthci_cmd.amp_remaining_assoc_length",
            FT_UINT16, BASE_DEC, 0x0, 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_amp_assoc_fragment,
          { "AMP Assoc Fragment", "bthci_cmd.amp_assoc_fragment",
            FT_BYTES, BASE_NONE, 0x0, 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_le_supported_host,
          { "LE Supported Host", "bthci_cmd.le_supported_host",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_le_simultaneous_host,
          { "Simultaneous LE Host", "bthci_cmd.le_simlutaneous_host",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x0,
            "Support for both LE and BR/EDR to same device", HFILL }
        },
        { &hf_bthci_cmd_le_evt_mask_00,
          { "LE Connection Complete", "bthci_cmd.le_evt_mask_00",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x01,
            "LE Connection Complete Bit", HFILL }
        },
        { &hf_bthci_cmd_le_evt_mask_01,
          { "LE Advertising Report", "bthci_cmd.le_evt_mask_01",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x02,
            "LE Advertising Report Bit", HFILL }
        },
        { &hf_bthci_cmd_le_evt_mask_02,
          { "LE Connection Update Complete", "bthci_cmd.le_evt_mask_02",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x04,
            "LE Connection Update Complete Bit", HFILL }
        },
        { &hf_bthci_cmd_le_evt_mask_03,
          { "LE Read Remote Used Features Complete", "bthci_cmd.le_evt_mask_03",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x08,
            "LE Read Remote Used Features Complete Bit", HFILL }
        },
        { &hf_bthci_cmd_le_evt_mask_04,
          { "LE Long Term Key Request", "bthci_cmd.le_evt_mask_04",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x10,
            "LE Long Term Key Request Bit", HFILL }
        },
        { &hf_bthci_cmd_le_advts_interval_min,
          { "Advertising Interval Min", "bthci_cmd.le_advts_interval_min",
            FT_UINT16, BASE_DEC, NULL, 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_le_advts_interval_max,
          { "Advertising Interval Max", "bthci_cmd.le_advts_interval_max",
            FT_UINT16, BASE_DEC, NULL, 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_le_advts_type,
          { "Advertising Type", "bthci_cmd.le_advts_type",
            FT_UINT8, BASE_HEX, VALS(cmd_le_advertising_types), 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_le_address_type,
          { "Address Type", "bthci_cmd.le_address_type",
            FT_UINT8, BASE_HEX, VALS(bthci_cmd_address_types_vals), 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_le_own_address_type,
          { "Own Address Type", "bthci_cmd.le_own_address_type",
            FT_UINT8, BASE_HEX, VALS(bthci_cmd_address_types_vals), 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_le_peer_address_type,
          { "Peer Address Type", "bthci_cmd.le_peer_address_type",
            FT_UINT8, BASE_HEX, VALS(bthci_cmd_address_types_vals), 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_le_direct_address_type,
          { "Direct Address Type", "bthci_cmd.le_direct_address_type",
            FT_UINT8, BASE_HEX, VALS(bthci_cmd_address_types_vals), 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_le_advts_channel_map_1,
          { "Channel 37", "bthci_cmd.le_advts_ch_map_1",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x01,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_le_advts_channel_map_2,
          { "Channel 38", "bthci_cmd.le_advts_ch_map_2",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x02,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_le_advts_channel_map_3,
          { "Channel 39", "bthci_cmd.le_advts_ch_map_3",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x04,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_le_advts_filter_policy,
          { "Advertising Filter Policy", "bthci_cmd.le_advts_filter_policy",
            FT_UINT8, BASE_HEX, VALS(cmd_le_advertising_filter_policy), 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_le_data_length,
          { "Data Length", "bthci_cmd.le_data_length",
            FT_UINT8, BASE_DEC, NULL, 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_le_advts_enable,
          { "Advertising Enable", "bthci_cmd.le_advts_enable",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_le_scan_enable,
          { "Scan Enable", "bthci_cmd.le_scan_enable",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_le_filter_dublicates,
          { "Filter Dublicates", "bthci_cmd.le_filter_dublicates",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_le_scan_type,
          { "Scan Type", "bthci_cmd.le_scan_type",
            FT_UINT8, BASE_HEX, VALS(cmd_le_scan_types), 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_le_scan_interval,
          { "Scan Interval", "bthci_cmd.le_scan_interval",
            FT_UINT16, BASE_DEC, NULL, 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_le_scan_window,
          { "Scan Window", "bthci_cmd.le_scan_window",
            FT_UINT16, BASE_DEC, NULL, 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_le_scan_filter_policy,
          { "Scan Filter Policy", "bthci_cmd.le_scan_filter_policy",
            FT_UINT8, BASE_HEX, VALS(cmd_le_scan_filter_policy), 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_le_initiator_filter_policy,
          { "Initiator Filter Policy", "bthci_cmd.le_initiator_filter_policy",
            FT_UINT8, BASE_HEX, VALS(cmd_init_filter_policy), 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_le_con_interval_min,
          { "Connection Interval Min", "bthci_cmd.le_con_interval_min",
            FT_UINT16, BASE_DEC, NULL, 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_le_con_interval_max,
          { "Connection Interval Max", "bthci_cmd.le_con_interval_max",
            FT_UINT16, BASE_DEC, NULL, 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_le_con_latency,
          { "Connection Latency", "bthci_cmd.le_con_latency",
            FT_UINT16, BASE_DEC, NULL, 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_le_supervision_timeout,
          { "Supervision Timeout", "bthci_cmd.le_supv_timeout",
            FT_UINT16, BASE_DEC, NULL, 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_le_min_ce_length,
          { "Min CE Length", "bthci_cmd.le_min_ce_length",
            FT_UINT16, BASE_DEC, NULL, 0x0,
            "Min. Connection Event Length", HFILL }
        },
        { &hf_bthci_cmd_le_max_ce_length,
          { "Max CE Length", "bthci_cmd.le_max_ce_length",
            FT_UINT16, BASE_DEC, NULL, 0x0,
            "Max. Connection Event Length", HFILL }
        },
        { &hf_bthci_cmd_le_channel_map,
          { "Channel Map", "bthci_cmd.le_channel_map",
            FT_BYTES, BASE_NONE, NULL, 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_key,
          { "Key",        "bthci_cmd.le_key",
            FT_BYTES, BASE_NONE, NULL, 0x0,
            "Encryption Key", HFILL }
        },
        { &hf_bthci_cmd_plaintext_data,
          { "Plaintext",        "bthci_cmd.le_plaintext",
            FT_BYTES, BASE_NONE, NULL, 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_random_number,
          { "Random Number",        "bthci_cmd.le_random_number",
            FT_BYTES, BASE_NONE, NULL, 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_encrypted_diversifier,
          { "Encrypted Diversifier", "bthci_cmd.le_encrypted_diversifier",
            FT_UINT16, BASE_HEX, NULL, 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_le_long_term_key,
          { "Long Term Key",        "bthci_cmd.le_long_tem_key",
            FT_BYTES, BASE_NONE, NULL, 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_rx_freqency,
          { "Rx Frequency", "bthci_cmd.rx_freqency",
            FT_UINT8, BASE_HEX, NULL, 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_tx_freqency,
          { "Tx Frequency", "bthci_cmd.tx_freqency",
            FT_UINT8, BASE_HEX, NULL, 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_test_data_length,
          { "Test Data Length", "bthci_cmd.le_test_data_length",
            FT_UINT8, BASE_DEC, NULL, 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_test_packet_payload,
          { "Packet Payload", "bthci_cmd.le_test_data_length",
            FT_UINT8, BASE_HEX, VALS(cmd_le_test_pkt_payload), 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_appearance,
          { "Appearance", "bthci_cmd.le_appearance",
            FT_UINT16, BASE_HEX, VALS(bthci_cmd_appearance_vals), 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_flags_limited_disc_mode,
          { "LE Limited Discoverable Mode",        "bthci_cmd.le_flags_limit_disc_mode",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x01,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_flags_general_disc_mode,
          { "LE General Discoverable Mode",        "bthci_cmd.le_flags_general_disc_mode",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x02,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_flags_bredr_not_support,
          { "BR/EDR Not Supported",                "bthci_cmd.le_flags_bredr_not_supported",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x04,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_flags_le_bredr_support_ctrl,
          { "Simultaneous LE and BR/EDR to Same Device Capable (Controller)",  "bthci_cmd.le_flags_bredr_support_ctrl",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x08,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_flags_le_bredr_support_host,
          { "Simultaneous LE and BR/EDR to Same Device Capable (Host)",        "bthci_cmd.le_flags_bredr_support_host",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x10,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_flags_le_oob_data_present,
          { "OOB Data Present",                            "bthci_cmd.le_flags_le_oob_data_present",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x01,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_flags_le_oob_le_supported_host,
          { "LE Supported By Host",                        "bthci_cmd.le_flags_le_oob_le_supported_host",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x02,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_flags_le_oob_le_bredr_support,
          { "Simultaneous LE and BR/EDR to Same Device Capable (Host)",   "bthci_cmd.le_flags_le_oob_le_bredr_support",
            FT_UINT8, BASE_HEX, VALS(cmd_boolean), 0x04,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_flags_le_oob_address_type,
          { "Address Type",                                "bthci_cmd.le_flags_le_oob_address_type",
            FT_UINT8, BASE_HEX, VALS(bthci_cmd_address_types_vals), 0x08,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_eir_ad_ssp_oob_length,
          { "SSP OOB Length",                              "bthci_cmd.eir_ad.ssp_oob_length",
            FT_UINT16, BASE_DEC, NULL, 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_eir_ad_advertising_interval,
          { "Advertising Interval",                        "bthci_cmd.eir_ad.advertising_interval",
            FT_UINT16, BASE_DEC, NULL, 0x0,
            NULL, HFILL }
        },
        { &hf_bthci_cmd_eir_ad_company_id,
          { "Company ID",                                  "bthci_cmd.eir_ad.company_id",
            FT_UINT16, BASE_HEX | BASE_EXT_STRING, &bthci_evt_comp_id_ext, 0x0,
            NULL, HFILL }
        },
        { &hf_eir_ad_item,
          { "Item",                                        "bthci_cmd.eir_ad",
            FT_NONE, BASE_NONE, NULL, 0x0,
            NULL, HFILL }
        },
        { &hf_extended_inquiry_response_data,
          { "Extended Inquiry Response Data",              "bthci_cmd.extended_inquiry_response_data",
            FT_NONE, BASE_NONE, NULL, 0x0,
            NULL, HFILL }
        },
        { &hf_advertising_data,
          { "Advertising Data",                            "bthci_cmd.advertising_data",
            FT_NONE, BASE_NONE, NULL, 0x0,
            NULL, HFILL }
        },
        { &hf_3ds_association_notification,
          { "3DS Association Notification",                "bthci_cmd.eir_ad.3ds.association_notification",
            FT_BOOLEAN, 8, NULL, 0x01,
            NULL, HFILL }
        },
        { &hf_3ds_battery_level_reporting,
          { "3DS Battery Level Reporting",                 "bthci_cmd.eir_ad.3ds.battery_level_reporting",
            FT_BOOLEAN, 8, NULL, 0x02,
            NULL, HFILL }
        },
        { &hf_3ds_send_battery_level_report_on_startup,
          { "3DS Send Battery Level Report on Startup",    "bthci_cmd.eir_ad.3ds.send_battery_level_report_on_startup",
            FT_BOOLEAN, 8, NULL, 0x04,
            NULL, HFILL }
        },
        { &hf_3ds_reserved,
          { "Reserved",                                    "bthci_cmd.eir_ad.3ds.reserved",
            FT_BOOLEAN, 8, NULL, 0x78,
            NULL, HFILL }
        },
        { &hf_3ds_factory_test_mode,
          { "3DS Factory Test Mode",                       "bthci_cmd.eir_ad.3ds.factory_test_mode",
            FT_BOOLEAN, 8, NULL, 0x80,
            NULL, HFILL }
        },
        { &hf_3ds_path_loss_threshold,
          { "3DS Path Loss Threshold",                     "bthci_cmd.eir_ad.3ds.path_loss_threshold",
            FT_UINT8, BASE_DEC, NULL, 0x00,
            NULL, HFILL }
        },
        { &hf_3ds_legacy_fixed,
          { "3DS Legacy Fixed",                            "bthci_cmd.eir_ad.3ds_legacy.fixed_byte",
            FT_UINT8, BASE_DEC, NULL, 0x00,
            NULL, HFILL }
        },
        { &hf_3ds_legacy_3d_capable_tv,
          { "3DS Legacy Capable TV",                       "bthci_cmd.eir_ad.3ds_legacy.capable_tv",
            FT_BOOLEAN, 8, NULL, 0x01,
            NULL, HFILL }
        },
        { &hf_3ds_legacy_ignored_1_3,
          { "3DS Legacy Ignored",                          "bthci_cmd.eir_ad.3ds_legacy.ignored.1_3",
            FT_BOOLEAN, 8, NULL, 0x0E,
            NULL, HFILL }
        },
        { &hf_3ds_legacy_fixed_4,
          { "3DS Legacy Fixed",                            "bthci_cmd.eir_ad.3ds_legacy.fixed.4",
            FT_BOOLEAN, 8, NULL, 0x10,
            NULL, HFILL }
        },
        { &hf_3ds_legacy_ignored_5,
          { "3DS Legacy Ignored",                          "bthci_cmd.eir_ad.3ds_legacy.ignored.5",
            FT_BOOLEAN, 8, NULL, 0x20,
            NULL, HFILL }
        },
        { &hf_3ds_legacy_fixed_6,
          { "3DS Legacy Fixed",                            "bthci_cmd.eir_ad.3ds_legacy.fixed.4",
            FT_BOOLEAN, 8, NULL, 0x40,
            NULL, HFILL }
        },
        { &hf_3ds_legacy_test_mode,
          { "3DS Legacy Test Mode",                        "bthci_cmd.eir_ad.3ds_legacy.test_mode",
            FT_BOOLEAN, 8, NULL, 0x80,
            NULL, HFILL }
        },
        { &hf_3ds_legacy_path_loss_threshold,
          { "3DS Legacy Path Loss Threshold",              "bthci_cmd.eir_ad.3ds_legacy.path_loss_threshold",
            FT_UINT8, BASE_DEC, NULL, 0x00,
            NULL, HFILL }
        },
        { &hf_did_vendor_id_source,
            { "Vendor ID Source",                          "bthci_cmd.eir_ad.did.vendor_id_source",
            FT_UINT16, BASE_HEX | BASE_EXT_STRING, &did_vendor_id_source_vals_ext, 0,
            NULL, HFILL }
        },
        { &hf_did_vendor_id,
            { "Vendor ID",                                 "bthci_cmd.eir_ad.did.vendor_id",
            FT_UINT16, BASE_HEX, NULL, 0,
            NULL, HFILL }
        },
        { &hf_did_vendor_id_bluetooth_sig,
            { "Vendor ID",                                 "bthci_cmd.eir_ad.did.vendor_id",
            FT_UINT16, BASE_HEX | BASE_EXT_STRING, &bthci_evt_comp_id_ext, 0,
            NULL, HFILL }
        },
        { &hf_did_vendor_id_usb_forum,
            { "Vendor ID",                                 "bthci_cmd.eir_ad.did.vendor_id",
            FT_UINT16, BASE_HEX | BASE_EXT_STRING, &ext_usb_vendors_vals, 0,
            NULL, HFILL }
        },
        { &hf_did_product_id,
            { "Product ID",                                "bthci_cmd.eir_ad.did.product_id",
            FT_UINT16, BASE_HEX, NULL, 0,
            NULL, HFILL }
        },
        { &hf_did_version,
            { "Version",                                   "bthci_cmd.eir_ad.did.version",
            FT_UINT16, BASE_HEX, NULL, 0,
            NULL, HFILL }
        }
    };

    static ei_register_info ei[] = {
        { &ei_eir_undecoded,                { "bthci_cmd.expert.eir.undecoded", PI_PROTOCOL, PI_UNDECODED, "Undecoded", EXPFILL }},
        { &ei_eir_unknown,                  { "bthci_cmd.expert.eir.unknown", PI_PROTOCOL, PI_WARN, "Unknown data", EXPFILL }},
        { &ei_command_unknown,              { "bthci_cmd.expert.command.unknown.", PI_PROTOCOL, PI_WARN, "Unknown command", EXPFILL }},
        { &ei_command_parameter_unexpected, { "bthci_cmd.expert.parameter.unexpected", PI_PROTOCOL, PI_WARN, "Unexpected command parameter", EXPFILL }},
        { &ei_command_undecoded,            { "bthci_cmd.expert.command.undecoded", PI_PROTOCOL, PI_UNDECODED, "Command undecoded", EXPFILL }}
    };

    /* Setup protocol subtree array */
    static gint *ett[] = {
        &ett_bthci_cmd,
        &ett_opcode,
        &ett_cod,
        &ett_cod_mask,
        &ett_eir_subtree,
        &ett_eir_struct_subtree,
        &ett_flow_spec_subtree
    };

    /* Dynamically fill "bthci_cmd_opcode_vals" */
    static const struct _opcode_value_string_arrays {
        guint                ogf;
        const value_string  *string_array;
        guint                length;
    } opcode_value_string_arrays[] = {
        { 0x01, bthci_cmd_ocf_link_control_vals, array_length(bthci_cmd_ocf_link_control_vals) },
        { 0x02, bthci_cmd_ocf_link_policy_vals, array_length(bthci_cmd_ocf_link_policy_vals) },
        { 0x03, bthci_cmd_ocf_host_controller_and_baseband_vals, array_length(bthci_cmd_ocf_host_controller_and_baseband_vals) },
        { 0x04, bthci_cmd_ocf_informational_vals, array_length(bthci_cmd_ocf_informational_vals) },
        { 0x05, bthci_cmd_ocf_status_vals, array_length(bthci_cmd_ocf_status_vals) },
        { 0x06, bthci_cmd_ocf_testing_vals, array_length(bthci_cmd_ocf_testing_vals) },
        { 0x08, bthci_cmd_ocf_low_energy_vals, array_length(bthci_cmd_ocf_low_energy_vals) },
    };

    bthci_cmd_opcode_vals[i_opcode].value = 0;
    bthci_cmd_opcode_vals[i_opcode].strptr = "No Operation";
    i_opcode += 1;
    for (i_array = 0; i_array < array_length(opcode_value_string_arrays); i_array += 1) {
        for (i_string_array = 0; i_string_array < opcode_value_string_arrays[i_array].length - 1; i_string_array += 1) {
            bthci_cmd_opcode_vals[i_opcode].value = opcode_value_string_arrays[i_array].string_array[i_string_array].value | (opcode_value_string_arrays[i_array].ogf << 10);
            bthci_cmd_opcode_vals[i_opcode].strptr = opcode_value_string_arrays[i_array].string_array[i_string_array].strptr;
            i_opcode += 1;
        }
    }

    /* Register the protocol name and description */
    proto_bthci_cmd = proto_register_protocol("Bluetooth HCI Command", "HCI_CMD", "bthci_cmd");

    new_register_dissector("bthci_cmd", dissect_bthci_cmd, proto_bthci_cmd);

    /* Required function calls to register the header fields and subtrees used */
    proto_register_field_array(proto_bthci_cmd, hf, array_length(hf));
    proto_register_subtree_array(ett, array_length(ett));

    expert_bthci_cmd = expert_register_protocol(proto_bthci_cmd);
    expert_register_field_array(expert_bthci_cmd, ei, array_length(ei));

    module = prefs_register_protocol(proto_bthci_cmd, NULL);
    prefs_register_static_text_preference(module, "hci_cmd.version",
            "Bluetooth HCI version: 4.0 (Core)",
            "Version of protocol supported by this dissector.");
}


/* If this dissector uses sub-dissector registration add a registration routine.
   This format is required because a script is used to find these routines and
   create the code that calls these routines.
   */
void
proto_reg_handoff_bthci_cmd(void)
{
    dissector_handle_t bthci_cmd_handle;
    bthci_cmd_handle = find_dissector("bthci_cmd");
    dissector_add_uint("hci_h4.type", HCI_H4_TYPE_CMD, bthci_cmd_handle);
    dissector_add_uint("hci_h1.type", BTHCI_CHANNEL_COMMAND, bthci_cmd_handle);
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
