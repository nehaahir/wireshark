/* DO NOT EDIT
	This filter was automatically generated
	from lsa.idl and lsa.cnf.
	
	Pidl is a perl based IDL compiler for DCE/RPC idl files. 
	It is maintained by the Samba team, not the Wireshark team.
	Instructions on how to download and install Pidl can be 
	found at http://wiki.wireshark.org/Pidl

	$Id: packet-dcerpc-lsa.c 53100 2013-11-06 14:31:29Z mmann $
*/


#include "config.h"
#ifdef _MSC_VER
#pragma warning(disable:4005)
#pragma warning(disable:4013)
#pragma warning(disable:4018)
#pragma warning(disable:4101)
#endif

#include <glib.h>
#include <string.h>
#include <epan/packet.h>

#include "packet-dcerpc.h"
#include "packet-dcerpc-nt.h"
#include "packet-windows-common.h"
#include "packet-dcerpc-lsa.h"

/* Ett declarations */
static gint ett_lsarpc_names = -1;
static gint ett_dcerpc_lsarpc = -1;
static gint ett_lsarpc_lsa_PolicyAccessMask = -1;
static gint ett_lsarpc_lsa_AccountAccessMask = -1;
static gint ett_lsarpc_lsa_DomainAccessMask = -1;
static gint ett_lsarpc_lsa_SecretAccessMask = -1;
static gint ett_lsarpc_security_secinfo = -1;
static gint ett_lsarpc_lsa_String = -1;
static gint ett_lsarpc_lsa_StringLarge = -1;
static gint ett_lsarpc_lsa_Strings = -1;
static gint ett_lsarpc_lsa_AsciiString = -1;
static gint ett_lsarpc_lsa_AsciiStringLarge = -1;
static gint ett_lsarpc_lsa_LUID = -1;
static gint ett_lsarpc_lsa_PrivEntry = -1;
static gint ett_lsarpc_lsa_PrivArray = -1;
static gint ett_lsarpc_lsa_QosInfo = -1;
static gint ett_lsarpc_lsa_ObjectAttribute = -1;
static gint ett_lsarpc_lsa_AuditLogInfo = -1;
static gint ett_lsarpc_lsa_AuditEventsInfo = -1;
static gint ett_lsarpc_lsa_DomainInfo = -1;
static gint ett_lsarpc_lsa_PDAccountInfo = -1;
static gint ett_lsarpc_lsa_ServerRole = -1;
static gint ett_lsarpc_lsa_ReplicaSourceInfo = -1;
static gint ett_lsarpc_lsa_DefaultQuotaInfo = -1;
static gint ett_lsarpc_lsa_ModificationInfo = -1;
static gint ett_lsarpc_lsa_AuditFullSetInfo = -1;
static gint ett_lsarpc_lsa_AuditFullQueryInfo = -1;
static gint ett_lsarpc_lsa_DnsDomainInfo = -1;
static gint ett_lsarpc_lsa_PolicyInformation = -1;
static gint ett_lsarpc_lsa_SidPtr = -1;
static gint ett_lsarpc_lsa_SidArray = -1;
static gint ett_lsarpc_lsa_DomainList = -1;
static gint ett_lsarpc_lsa_TranslatedSid = -1;
static gint ett_lsarpc_lsa_TransSidArray = -1;
static gint ett_lsarpc_lsa_RefDomainList = -1;
static gint ett_lsarpc_lsa_TranslatedName = -1;
static gint ett_lsarpc_lsa_TransNameArray = -1;
static gint ett_lsarpc_lsa_LUIDAttribute = -1;
static gint ett_lsarpc_lsa_PrivilegeSet = -1;
static gint ett_lsarpc_lsa_DATA_BUF = -1;
static gint ett_lsarpc_lsa_DATA_BUF2 = -1;
static gint ett_lsarpc_lsa_TrustDomainInfoName = -1;
static gint ett_lsarpc_lsa_TrustDomainInfoPosixOffset = -1;
static gint ett_lsarpc_lsa_TrustDomainInfoPassword = -1;
static gint ett_lsarpc_lsa_TrustDomainInfoBasic = -1;
static gint ett_lsarpc_lsa_TrustDomainInfoInfoEx = -1;
static gint ett_lsarpc_lsa_TrustDomainInfoBuffer = -1;
static gint ett_lsarpc_lsa_TrustDomainInfoAuthInfo = -1;
static gint ett_lsarpc_lsa_TrustDomainInfoFullInfo = -1;
static gint ett_lsarpc_lsa_TrustDomainInfo11 = -1;
static gint ett_lsarpc_lsa_TrustDomainInfoInfoAll = -1;
static gint ett_lsarpc_lsa_TrustedDomainInfo = -1;
static gint ett_lsarpc_lsa_DATA_BUF_PTR = -1;
static gint ett_lsarpc_lsa_RightAttribute = -1;
static gint ett_lsarpc_lsa_RightSet = -1;
static gint ett_lsarpc_lsa_StringPointer = -1;
static gint ett_lsarpc_lsa_DomainListEx = -1;
static gint ett_lsarpc_lsa_DomainInfoKerberos = -1;
static gint ett_lsarpc_lsa_DomainInfoEfs = -1;
static gint ett_lsarpc_lsa_DomainInformationPolicy = -1;
static gint ett_lsarpc_lsa_TranslatedName2 = -1;
static gint ett_lsarpc_lsa_TransNameArray2 = -1;
static gint ett_lsarpc_lsa_TranslatedSid2 = -1;
static gint ett_lsarpc_lsa_TransSidArray2 = -1;
static gint ett_lsarpc_lsa_TranslatedSid3 = -1;
static gint ett_lsarpc_lsa_TransSidArray3 = -1;
static gint ett_lsarpc_lsa_ForestTrustBinaryData = -1;
static gint ett_lsarpc_lsa_ForestTrustDomainInfo = -1;
static gint ett_lsarpc_lsa_ForestTrustData = -1;
static gint ett_lsarpc_lsa_ForestTrustRecord = -1;
static gint ett_lsarpc_lsa_ForestTrustInformation = -1;


/* Header field declarations */
static gint hf_lsarpc_lsa_AsciiStringLarge_size = -1;
static gint hf_lsarpc_lsa_LookupPrivName_luid = -1;
static gint hf_lsarpc_lsa_TrustDomainInfoAuthInfo_outgoing_count = -1;
static gint hf_lsarpc_lsa_DomainAccessMask_LSA_DOMAIN_SET_CONTROLLERS = -1;
static gint hf_lsarpc_lsa_Delete_handle = -1;
static gint hf_lsarpc_lsa_PolicyInformation_account_domain = -1;
static gint hf_lsarpc_lsa_DomainInfoKerberos_clock_skew = -1;
static gint hf_lsarpc_lsa_ForestTrustData_domain_info = -1;
static gint hf_lsarpc_lsa_AddPrivilegesToAccount_handle = -1;
static gint hf_lsarpc_lsa_ObjectAttribute_sec_qos = -1;
static gint hf_lsarpc_lsa_LookupNames3_handle = -1;
static gint hf_lsarpc_lsa_QueryTrustedDomainInfoBySid_level = -1;
static gint hf_lsarpc_lsa_OpenTrustedDomain_sid = -1;
static gint hf_lsarpc_lsa_EnumAccounts_handle = -1;
static gint hf_lsarpc_lsa_CreateAccount_sid = -1;
static gint hf_lsarpc_lsa_ReplicaSourceInfo_account = -1;
static gint hf_lsarpc_lsa_QueryDomainInformationPolicy_handle = -1;
static gint hf_lsarpc_lsa_CreateTrustedDomain_info = -1;
static gint hf_lsarpc_lsa_PolicyAccessMask_LSA_POLICY_SET_DEFAULT_QUOTA_LIMITS = -1;
static gint hf_lsarpc_lsa_PrivilegeSet_set = -1;
static gint hf_lsarpc_lsa_QuerySecret_new_val = -1;
static gint hf_lsarpc_lsa_TranslatedSid2_unknown = -1;
static gint hf_lsarpc_lsa_LookupSids2_handle = -1;
static gint hf_lsarpc_lsa_DomainListEx_domains = -1;
static gint hf_lsarpc_lsa_LookupNames3_num_names = -1;
static gint hf_lsarpc_lsa_EnumTrustedDomainsEx_max_size = -1;
static gint hf_lsarpc_lsa_LookupPrivName_handle = -1;
static gint hf_lsarpc_lsa_OpenAccount_handle = -1;
static gint hf_lsarpc_lsa_OpenSecret_access_mask = -1;
static gint hf_lsarpc_lsa_QuerySecurity_sdbuf = -1;
static gint hf_lsarpc_lsa_SetTrustedDomainInfoByName_trusted_domain = -1;
static gint hf_lsarpc_lsa_CreateTrustedDomain_trustdom_handle = -1;
static gint hf_lsarpc_lsa_EnumPrivs_handle = -1;
static gint hf_lsarpc_lsa_LUID_high = -1;
static gint hf_lsarpc_lsa_QueryInfoPolicy_handle = -1;
static gint hf_lsarpc_lsa_PolicyInformation_audit_events = -1;
static gint hf_lsarpc_lsa_TrustedDomainInfo_auth_info = -1;
static gint hf_lsarpc_lsa_PolicyAccessMask_LSA_POLICY_CREATE_PRIVILEGE = -1;
static gint hf_lsarpc_lsa_DomainInfoKerberos_service_tkt_lifetime = -1;
static gint hf_lsarpc_lsa_CreateSecret_access_mask = -1;
static gint hf_lsarpc_lsa_GetUserName_authority_name = -1;
static gint hf_lsarpc_lsa_AuditFullSetInfo_shutdown_on_full = -1;
static gint hf_lsarpc_lsa_RemoveAccountRights_unknown = -1;
static gint hf_lsarpc_lsa_LookupNames4_unknown1 = -1;
static gint hf_lsarpc_secret_access_mask = -1;
static gint hf_lsarpc_lsa_DeleteTrustedDomain_dom_sid = -1;
static gint hf_lsarpc_lsa_LookupNames4_names = -1;
static gint hf_lsarpc_lsa_ForestTrustRecord_forest_trust_data = -1;
static gint hf_lsarpc_lsa_PolicyInformation_role = -1;
static gint hf_lsarpc_lsa_PolicyInformation_audit_log = -1;
static gint hf_lsarpc_lsa_DomainAccessMask_LSA_DOMAIN_QUERY_DOMAIN_NAME = -1;
static gint hf_lsarpc_lsa_PolicyInformation_dns = -1;
static gint hf_lsarpc_lsa_lsaRQueryForestTrustInformation_trusted_domain_name = -1;
static gint hf_lsarpc_lsa_QueryTrustedDomainInfoByName_trusted_domain = -1;
static gint hf_lsarpc_lsa_OpenPolicy2_handle = -1;
static gint hf_lsarpc_lsa_EnumAccountsWithUserRight_handle = -1;
static gint hf_lsarpc_lsa_TrustDomainInfoAuthInfo_incoming_count = -1;
static gint hf_lsarpc_lsa_RemoveAccountRights_rights = -1;
static gint hf_lsarpc_lsa_SetSecret_sec_handle = -1;
static gint hf_lsarpc_lsa_PolicyAccessMask_LSA_POLICY_CREATE_SECRET = -1;
static gint hf_lsarpc_lsa_OpenTrustedDomainByName_access_mask = -1;
static gint hf_lsarpc_lsa_RightAttribute_name = -1;
static gint hf_lsarpc_lsa_TrustDomainInfoPassword_old_password = -1;
static gint hf_lsarpc_lsa_DomainInfoKerberos_user_tkt_renewaltime = -1;
static gint hf_lsarpc_lsa_LUID_low = -1;
static gint hf_lsarpc_lsa_LookupNames3_names = -1;
static gint hf_lsarpc_lsa_QueryTrustedDomainInfoBySid_dom_sid = -1;
static gint hf_lsarpc_lsa_TrustDomainInfo11_info_ex = -1;
static gint hf_lsarpc_lsa_LookupSids_names = -1;
static gint hf_lsarpc_lsa_OpenTrustedDomain_access_mask = -1;
static gint hf_lsarpc_lsa_RefDomainList_max_size = -1;
static gint hf_lsarpc_lsa_TransSidArray_sids = -1;
static gint hf_lsarpc_lsa_TrustDomainInfoInfoEx_trust_attributes = -1;
static gint hf_lsarpc_lsa_CreateSecret_sec_handle = -1;
static gint hf_lsarpc_lsa_SetSecret_old_val = -1;
static gint hf_lsarpc_lsa_TrustDomainInfoBuffer_last_update_time = -1;
static gint hf_lsarpc_lsa_DnsDomainInfo_dns_forest = -1;
static gint hf_lsarpc_lsa_QueryDomainInformationPolicy_info = -1;
static gint hf_lsarpc_lsa_ForestTrustDomainInfo_netbios_domain_name = -1;
static gint hf_lsarpc_lsa_TrustDomainInfoInfoEx_trust_direction = -1;
static gint hf_lsarpc_lsa_LookupNames3_sids = -1;
static gint hf_lsarpc_lsa_AuditLogInfo_unknown = -1;
static gint hf_lsarpc_lsa_AuditLogInfo_retention_time = -1;
static gint hf_lsarpc_lsa_ObjectAttribute_sec_desc = -1;
static gint hf_lsarpc_lsa_DnsDomainInfo_name = -1;
static gint hf_lsarpc_efs_blob_len = -1;
static gint hf_lsarpc_lsa_TranslatedSid2_sid_index = -1;
static gint hf_lsarpc_lsa_QuerySecret_old_mtime = -1;
static gint hf_lsarpc_lsa_OpenTrustedDomain_handle = -1;
static gint hf_lsarpc_lsa_TransNameArray_names = -1;
static gint hf_lsarpc_lsa_DomainAccessMask_LSA_DOMAIN_QUERY_CONTROLLERS = -1;
static gint hf_lsarpc_lsa_RefDomainList_count = -1;
static gint hf_lsarpc_lsa_QueryInfoPolicy2_info = -1;
static gint hf_lsarpc_lsa_DomainInformationPolicy_kerberos_info = -1;
static gint hf_lsarpc_lsa_QueryInfoPolicy_info = -1;
static gint hf_lsarpc_lsa_CreateAccount_acct_handle = -1;
static gint hf_lsarpc_lsa_AuditLogInfo_shutdown_in_progress = -1;
static gint hf_lsarpc_lsa_OpenSecret_handle = -1;
static gint hf_lsarpc_lsa_TrustDomainInfoBuffer_secret_type = -1;
static gint hf_lsarpc_lsa_TrustDomainInfoName_netbios_name = -1;
static gint hf_lsarpc_lsa_LookupNames_handle = -1;
static gint hf_lsarpc_lsa_EnumTrustDom_max_size = -1;
static gint hf_lsarpc_lsa_TrustDomainInfoPassword_password = -1;
static gint hf_lsarpc_lsa_ObjectAttribute_object_name = -1;
static gint hf_lsarpc_lsa_CreateTrustedDomain_handle = -1;
static gint hf_lsarpc_lsa_EnumTrustDom_resume_handle = -1;
static gint hf_lsarpc_lsa_TrustedDomainInfo_info11 = -1;
static gint hf_lsarpc_lsa_QosInfo_impersonation_level = -1;
static gint hf_lsarpc_lsa_QueryInfoPolicy2_level = -1;
static gint hf_lsarpc_lsa_TranslatedSid3_sid = -1;
static gint hf_lsarpc_lsa_TrustDomainInfoBasic_netbios_name = -1;
static gint hf_lsarpc_lsa_PolicyAccessMask_LSA_POLICY_AUDIT_LOG_ADMIN = -1;
static gint hf_lsarpc_lsa_ForestTrustInformation_entries = -1;
static gint hf_lsarpc_lsa_ForestTrustData_top_level_name_ex = -1;
static gint hf_lsarpc_lsa_DefaultQuotaInfo_non_paged_pool = -1;
static gint hf_lsarpc_lsa_ForestTrustBinaryData_length = -1;
static gint hf_lsarpc_lsa_DefaultQuotaInfo_unknown = -1;
static gint hf_lsarpc_lsa_QosInfo_len = -1;
static gint hf_lsarpc_lsa_AuditFullQueryInfo_unknown = -1;
static gint hf_lsarpc_lsa_LookupNames3_level = -1;
static gint hf_lsarpc_lsa_LookupPrivDisplayName_disp_name = -1;
static gint hf_lsarpc_lsa_LookupNames_level = -1;
static gint hf_lsarpc_lsa_LookupNames4_count = -1;
static gint hf_lsarpc_lsa_LookupNames_names = -1;
static gint hf_lsarpc_lsa_AccountAccessMask_LSA_ACCOUNT_ADJUST_PRIVILEGES = -1;
static gint hf_lsarpc_lsa_TrustDomainInfo11_data1 = -1;
static gint hf_lsarpc_lsa_PrivEntry_luid = -1;
static gint hf_lsarpc_lsa_EnumAccounts_resume_handle = -1;
static gint hf_lsarpc_lsa_LookupSids3_level = -1;
static gint hf_lsarpc_lsa_DATA_BUF_data = -1;
static gint hf_lsarpc_lsa_OpenTrustedDomainByName_name = -1;
static gint hf_lsarpc_lsa_DomainListEx_count = -1;
static gint hf_lsarpc_lsa_DomainAccessMask_LSA_DOMAIN_QUERY_AUTH = -1;
static gint hf_lsarpc_lsa_DefaultQuotaInfo_pagefile = -1;
static gint hf_lsarpc_lsa_DefaultQuotaInfo_min_wss = -1;
static gint hf_lsarpc_lsa_ForestTrustData_top_level_name = -1;
static gint hf_lsarpc_lsa_TranslatedName2_sid_type = -1;
static gint hf_lsarpc_lsa_OpenTrustedDomain_trustdom_handle = -1;
static gint hf_lsarpc_lsa_TrustDomainInfoFullInfo_info_ex = -1;
static gint hf_lsarpc_lsa_DATA_BUF2_data = -1;
static gint hf_lsarpc_lsa_RemoveAccountRights_handle = -1;
static gint hf_lsarpc_lsa_LookupNames3_count = -1;
static gint hf_lsarpc_lsa_LookupNames2_unknown2 = -1;
static gint hf_lsarpc_lsa_EnumTrustedDomainsEx_resume_handle = -1;
static gint hf_lsarpc_lsa_TransNameArray2_count = -1;
static gint hf_lsarpc_lsa_DomainInfo_sid = -1;
static gint hf_lsarpc_lsa_QueryTrustedDomainInfoByName_level = -1;
static gint hf_lsarpc_lsa_TrustDomainInfoInfoEx_sid = -1;
static gint hf_lsarpc_lsa_TrustDomainInfoAuthInfo_incoming_previous_auth_info = -1;
static gint hf_lsarpc_lsa_LookupNames3_domains = -1;
static gint hf_lsarpc_lsa_SetSecret_new_val = -1;
static gint hf_lsarpc_lsa_String_string = -1;
static gint hf_lsarpc_lsa_PrivArray_count = -1;
static gint hf_lsarpc_lsa_QueryTrustedDomainInfo_level = -1;
static gint hf_lsarpc_lsa_DATA_BUF_size = -1;
static gint hf_lsarpc_lsa_QueryDomainInformationPolicy_level = -1;
static gint hf_lsarpc_lsa_DomainAccessMask_LSA_DOMAIN_SET_AUTH = -1;
static gint hf_lsarpc_lsa_StringLarge_string = -1;
static gint hf_lsarpc_lsa_DomainInfo_name = -1;
static gint hf_lsarpc_lsa_AsciiString_size = -1;
static gint hf_lsarpc_lsa_LookupNames2_sids = -1;
static gint hf_lsarpc_lsa_DomainAccessMask_LSA_DOMAIN_SET_POSIX = -1;
static gint hf_lsarpc_lsa_SetDomainInformationPolicy_level = -1;
static gint hf_lsarpc_account_access_mask = -1;
static gint hf_lsarpc_lsa_SetInfoPolicy2_info = -1;
static gint hf_lsarpc_lsa_AsciiStringLarge_string = -1;
static gint hf_lsarpc_lsa_LookupSids2_level = -1;
static gint hf_lsarpc_lsa_OpenSecret_sec_handle = -1;
static gint hf_lsarpc_lsa_TrustDomainInfoAuthInfo_incoming_current_auth_info = -1;
static gint hf_lsarpc_lsa_DomainInformationPolicy_efs_info = -1;
static gint hf_lsarpc_lsa_EnumAccounts_sids = -1;
static gint hf_lsarpc_lsa_ReplicaSourceInfo_source = -1;
static gint hf_lsarpc_lsa_LookupNames3_unknown1 = -1;
static gint hf_lsarpc_lsa_QuerySecurity_sec_info = -1;
static gint hf_lsarpc_lsa_DomainInfoKerberos_enforce_restrictions = -1;
static gint hf_lsarpc_lsa_LookupSids2_domains = -1;
static gint hf_lsarpc_policy_access_mask = -1;
static gint hf_lsarpc_lsa_EnumTrustedDomainsEx_domains = -1;
static gint hf_lsarpc_lsa_EnumAccounts_num_entries = -1;
static gint hf_lsarpc_domain_access_mask = -1;
static gint hf_lsarpc_lsa_TrustedDomainInfo_info_all = -1;
static gint hf_lsarpc_lsa_TrustDomainInfoFullInfo_posix_offset = -1;
static gint hf_lsarpc_lsa_TrustDomainInfoInfoEx_trust_type = -1;
static gint hf_lsarpc_lsa_DnsDomainInfo_sid = -1;
static gint hf_lsarpc_lsa_LookupNames_num_names = -1;
static gint hf_lsarpc_lsa_ForestTrustDomainInfo_domain_sid = -1;
static gint hf_lsarpc_lsa_LookupSids_handle = -1;
static gint hf_lsarpc_lsa_AsciiString_string = -1;
static gint hf_lsarpc_lsa_TrustedDomainInfo_info_ex = -1;
static gint hf_lsarpc_lsa_RemovePrivilegesFromAccount_handle = -1;
static gint hf_lsarpc_lsa_CreateAccount_handle = -1;
static gint hf_lsarpc_lsa_TrustedDomainInfo_name = -1;
static gint hf_lsarpc_lsa_LookupNames4_unknown2 = -1;
static gint hf_lsarpc_lsa_EnumAccountRights_rights = -1;
static gint hf_lsarpc_lsa_DomainAccessMask_LSA_DOMAIN_QUERY_POSIX = -1;
static gint hf_lsarpc_lsa_LookupPrivDisplayName_name = -1;
static gint hf_lsarpc_lsa_PolicyAccessMask_LSA_POLICY_GET_PRIVATE_INFORMATION = -1;
static gint hf_lsarpc_lsa_OpenPolicy2_access_mask = -1;
static gint hf_lsarpc_lsa_SetInfoPolicy2_handle = -1;
static gint hf_lsarpc_sec_desc_buf_len = -1;
static gint hf_lsarpc_lsa_LookupNames2_num_names = -1;
static gint hf_lsarpc_lsa_SetInfoPolicy2_level = -1;
static gint hf_lsarpc_lsa_EnumPrivsAccount_privs = -1;
static gint hf_lsarpc_lsa_OpenAccount_access_mask = -1;
static gint hf_lsarpc_lsa_EnumPrivs_privs = -1;
static gint hf_lsarpc_lsa_PolicyAccessMask_LSA_POLICY_TRUST_ADMIN = -1;
static gint hf_lsarpc_lsa_AuditLogInfo_percent_full = -1;
static gint hf_lsarpc_lsa_PolicyInformation_quota = -1;
static gint hf_lsarpc_lsa_RemovePrivilegesFromAccount_privs = -1;
static gint hf_lsarpc_lsa_TranslatedSid3_unknown = -1;
static gint hf_lsarpc_lsa_TranslatedName_sid_type = -1;
static gint hf_lsarpc_lsa_LookupSids2_names = -1;
static gint hf_lsarpc_lsa_EnumPrivsAccount_handle = -1;
static gint hf_lsarpc_lsa_SidArray_sids = -1;
static gint hf_lsarpc_lsa_RemoveAccountRights_sid = -1;
static gint hf_lsarpc_lsa_QueryTrustedDomainInfo_info = -1;
static gint hf_lsarpc_lsa_String_length = -1;
static gint hf_lsarpc_opnum = -1;
static gint hf_lsarpc_lsa_PrivilegeSet_count = -1;
static gint hf_lsarpc_lsa_SetTrustedDomainInfoByName_level = -1;
static gint hf_lsarpc_lsa_LookupPrivDisplayName_language_id = -1;
static gint hf_lsarpc_lsa_TransSidArray3_sids = -1;
static gint hf_lsarpc_status = -1;
static gint hf_lsarpc_lsa_LookupNames_count = -1;
static gint hf_lsarpc_lsa_TrustDomainInfoAuthInfo_outgoing_previous_auth_info = -1;
static gint hf_lsarpc_lsa_LookupPrivValue_name = -1;
static gint hf_lsarpc_lsa_ForestTrustBinaryData_data = -1;
static gint hf_lsarpc_lsa_AccountAccessMask_LSA_ACCOUNT_ADJUST_SYSTEM_ACCESS = -1;
static gint hf_lsarpc_lsa_TranslatedSid_sid_index = -1;
static gint hf_lsarpc_lsa_PolicyAccessMask_LSA_POLICY_CREATE_ACCOUNT = -1;
static gint hf_lsarpc_lsa_AsciiStringLarge_length = -1;
static gint hf_lsarpc_lsa_OpenTrustedDomainByName_trustdom_handle = -1;
static gint hf_lsarpc_lsa_TransNameArray2_names = -1;
static gint hf_lsarpc_lsa_EnumTrustDom_handle = -1;
static gint hf_lsarpc_lsa_CreateAccount_access_mask = -1;
static gint hf_lsarpc_lsa_OpenPolicy2_attr = -1;
static gint hf_lsarpc_lsa_TrustDomainInfoInfoEx_netbios_name = -1;
static gint hf_lsarpc_lsa_ForestTrustRecord_flags = -1;
static gint hf_lsarpc_lsa_OpenPolicy_system_name = -1;
static gint hf_lsarpc_lsa_LookupSids2_sids = -1;
static gint hf_lsarpc_lsa_TranslatedName_sid_index = -1;
static gint hf_lsarpc_lsa_TrustedDomainInfo_password = -1;
static gint hf_lsarpc_lsa_ModificationInfo_db_create_time = -1;
static gint hf_lsarpc_lsa_PolicyAccessMask_LSA_POLICY_NOTIFICATION = -1;
static gint hf_lsarpc_lsa_PolicyInformation_domain = -1;
static gint hf_lsarpc_lsa_DATA_BUF2_size = -1;
static gint hf_lsarpc_lsa_QueryTrustedDomainInfoByName_handle = -1;
static gint hf_lsarpc_lsa_PolicyAccessMask_LSA_POLICY_SET_AUDIT_REQUIREMENTS = -1;
static gint hf_lsarpc_lsa_LookupNames2_unknown1 = -1;
static gint hf_lsarpc_lsa_LookupNames4_domains = -1;
static gint hf_lsarpc_lsa_LookupSids3_unknown2 = -1;
static gint hf_lsarpc_lsa_TranslatedSid_sid_type = -1;
static gint hf_lsarpc_lsa_LookupNames2_count = -1;
static gint hf_lsarpc_lsa_ForestTrustDomainInfo_dns_domain_name = -1;
static gint hf_lsarpc_lsa_AuditLogInfo_next_audit_record = -1;
static gint hf_lsarpc_lsa_PrivArray_privs = -1;
static gint hf_lsarpc_lsa_TransSidArray2_sids = -1;
static gint hf_lsarpc_lsa_TransSidArray3_count = -1;
static gint hf_lsarpc_lsa_lsaRQueryForestTrustInformation_handle = -1;
static gint hf_lsarpc_lsa_DomainList_count = -1;
static gint hf_lsarpc_lsa_QuerySecret_sec_handle = -1;
static gint hf_lsarpc_lsa_AuditFullQueryInfo_shutdown_on_full = -1;
static gint hf_lsarpc_lsa_GetUserName_system_name = -1;
static gint hf_lsarpc_lsa_SidArray_num_sids = -1;
static gint hf_lsarpc_lsa_LookupNames4_level = -1;
static gint hf_lsarpc_lsa_QueryTrustedDomainInfoBySid_handle = -1;
static gint hf_lsarpc_lsa_RightSet_names = -1;
static gint hf_lsarpc_lsa_LookupNames_domains = -1;
static gint hf_lsarpc_lsa_LookupSids2_unknown2 = -1;
static gint hf_lsarpc_lsa_LookupNames_sids = -1;
static gint hf_lsarpc_lsa_EnumAccountsWithUserRight_name = -1;
static gint hf_lsarpc_lsa_LookupPrivName_name = -1;
static gint hf_lsarpc_lsa_PolicyAccessMask_LSA_POLICY_VIEW_LOCAL_INFORMATION = -1;
static gint hf_lsarpc_lsa_LookupNames4_sids = -1;
static gint hf_lsarpc_lsa_RefDomainList_domains = -1;
static gint hf_lsarpc_lsa_SetDomainInformationPolicy_info = -1;
static gint hf_lsarpc_lsa_SetDomainInformationPolicy_handle = -1;
static gint hf_lsarpc_lsa_PolicyInformation_replica = -1;
static gint hf_lsarpc_lsa_TrustDomainInfoInfoAll_info_ex = -1;
static gint hf_lsarpc_lsa_TransSidArray_count = -1;
static gint hf_lsarpc_lsa_TrustDomainInfoFullInfo_auth_info = -1;
static gint hf_lsarpc_lsa_EnumAccountRights_handle = -1;
static gint hf_lsarpc_lsa_AuditLogInfo_time_to_shutdown = -1;
static gint hf_lsarpc_lsa_AccountAccessMask_LSA_ACCOUNT_VIEW = -1;
static gint hf_lsarpc_lsa_TrustDomainInfoInfoEx_domain_name = -1;
static gint hf_lsarpc_lsa_LookupSids3_unknown1 = -1;
static gint hf_lsarpc_lsa_LookupSids2_count = -1;
static gint hf_lsarpc_lsa_TrustedDomainInfo_info_basic = -1;
static gint hf_lsarpc_lsa_TrustDomainInfoPosixOffset_posix_offset = -1;
static gint hf_lsarpc_lsa_OpenSecret_name = -1;
static gint hf_lsarpc_lsa_PolicyInformation_db = -1;
static gint hf_lsarpc_String_name = -1;
static gint hf_lsarpc_lsa_GetUserName_account_name = -1;
static gint hf_lsarpc_lsa_LUIDAttribute_attribute = -1;
static gint hf_lsarpc_lsa_DATA_BUF_PTR_buf = -1;
static gint hf_lsarpc_lsa_OpenPolicy_access_mask = -1;
static gint hf_lsarpc_lsa_LookupSids3_sids = -1;
static gint hf_lsarpc_lsa_String_size = -1;
static gint hf_lsarpc_lsa_TrustDomainInfoAuthInfo_outgoing_current_auth_info = -1;
static gint hf_lsarpc_lsa_TrustedDomainInfo_posix_offset = -1;
static gint hf_lsarpc_lsa_DomainInfoKerberos_unknown6 = -1;
static gint hf_lsarpc_lsa_LookupSids2_unknown1 = -1;
static gint hf_lsarpc_lsa_OpenAccount_sid = -1;
static gint hf_lsarpc_lsa_SetTrustedDomainInfoByName_handle = -1;
static gint hf_lsarpc_lsa_DnsDomainInfo_domain_guid = -1;
static gint hf_lsarpc_lsa_LUIDAttribute_luid = -1;
static gint hf_lsarpc_lsa_DomainInfoKerberos_user_tkt_lifetime = -1;
static gint hf_lsarpc_lsa_AddAccountRights_rights = -1;
static gint hf_lsarpc_lsa_TrustDomainInfoInfoAll_data1 = -1;
static gint hf_lsarpc_lsa_PrivilegeSet_unknown = -1;
static gint hf_lsarpc_lsa_ObjectAttribute_root_dir = -1;
static gint hf_lsarpc_lsa_LookupSids3_names = -1;
static gint hf_lsarpc_lsa_CreateSecret_handle = -1;
static gint hf_lsarpc_lsa_StringLarge_length = -1;
static gint hf_lsarpc_lsa_AccountAccessMask_LSA_ACCOUNT_ADJUST_QUOTAS = -1;
static gint hf_lsarpc_lsa_LookupNames2_names = -1;
static gint hf_lsarpc_lsa_OpenAccount_acct_handle = -1;
static gint hf_lsarpc_lsa_StringPointer_string = -1;
static gint hf_lsarpc_lsa_PolicyAccessMask_LSA_POLICY_SERVER_ADMIN = -1;
static gint hf_lsarpc_lsa_QuerySecret_old_val = -1;
static gint hf_lsarpc_lsa_DeleteTrustedDomain_handle = -1;
static gint hf_lsarpc_lsa_LookupPrivDisplayName_handle = -1;
static gint hf_lsarpc_lsa_LookupNames2_domains = -1;
static gint hf_lsarpc_lsa_EnumPrivs_resume_handle = -1;
static gint hf_lsarpc_lsa_LookupNames2_handle = -1;
static gint hf_lsarpc_lsa_SetTrustedDomainInfoByName_info = -1;
static gint hf_lsarpc_lsa_AddPrivilegesToAccount_privs = -1;
static gint hf_lsarpc_lsa_Close_handle = -1;
static gint hf_lsarpc_lsa_TranslatedName2_name = -1;
static gint hf_lsarpc_lsa_AddAccountRights_sid = -1;
static gint hf_lsarpc_lsa_LookupPrivValue_luid = -1;
static gint hf_lsarpc_lsa_PolicyAccessMask_LSA_POLICY_LOOKUP_NAMES = -1;
static gint hf_lsarpc_lsa_TranslatedName2_unknown = -1;
static gint hf_lsarpc_lsa_ForestTrustRecord_unknown = -1;
static gint hf_lsarpc_lsa_CreateTrustedDomain_access_mask = -1;
static gint hf_lsarpc_lsa_DomainList_domains = -1;
static gint hf_lsarpc_lsa_CreateSecret_name = -1;
static gint hf_lsarpc_lsa_AuditEventsInfo_auditing_mode = -1;
static gint hf_lsarpc_lsa_QueryTrustedDomainInfoBySid_info = -1;
static gint hf_lsarpc_lsa_EnumAccountsWithUserRight_sids = -1;
static gint hf_lsarpc_lsa_SetInfoPolicy_info = -1;
static gint hf_lsarpc_lsa_SidPtr_sid = -1;
static gint hf_lsarpc_lsa_QueryTrustedDomainInfoByName_info = -1;
static gint hf_lsarpc_names = -1;
static gint hf_lsarpc_lsa_PDAccountInfo_name = -1;
static gint hf_lsarpc_lsa_QuerySecurity_handle = -1;
static gint hf_lsarpc_lsa_ForestTrustInformation_count = -1;
static gint hf_lsarpc_lsa_lsaRQueryForestTrustInformation_unknown = -1;
static gint hf_lsarpc_lsa_LookupSids3_domains = -1;
static gint hf_lsarpc_lsa_Strings_count = -1;
static gint hf_lsarpc_lsa_QueryInfoPolicy2_handle = -1;
static gint hf_lsarpc_lsa_QueryTrustedDomainInfo_trustdom_handle = -1;
static gint hf_lsarpc_lsa_TrustDomainInfoBuffer_data = -1;
static gint hf_lsarpc_lsa_ObjectAttribute_attributes = -1;
static gint hf_lsarpc_lsa_StringLarge_size = -1;
static gint hf_lsarpc_lsa_QosInfo_effective_only = -1;
static gint hf_lsarpc_lsa_ObjectAttribute_len = -1;
static gint hf_lsarpc_lsa_OpenPolicy_attr = -1;
static gint hf_lsarpc_lsa_TrustDomainInfoBasic_sid = -1;
static gint hf_lsarpc_lsa_PrivEntry_name = -1;
static gint hf_lsarpc_lsa_ServerRole_role = -1;
static gint hf_lsarpc_lsa_TranslatedSid3_sid_type = -1;
static gint hf_lsarpc_lsa_LookupNames4_num_names = -1;
static gint hf_lsarpc_lsa_ForestTrustRecord_level = -1;
static gint hf_lsarpc_lsa_EnumPrivs_max_count = -1;
static gint hf_lsarpc_lsa_LookupNames2_level = -1;
static gint hf_lsarpc_lsa_LookupNames3_unknown2 = -1;
static gint hf_lsarpc_lsa_DATA_BUF_length = -1;
static gint hf_lsarpc_lsa_Strings_names = -1;
static gint hf_lsarpc_lsa_LookupPrivDisplayName_unknown = -1;
static gint hf_lsarpc_lsa_PolicyInformation_auditfullset = -1;
static gint hf_lsarpc_lsa_ForestTrustData_data = -1;
static gint hf_lsarpc_lsa_OpenPolicy_handle = -1;
static gint hf_lsarpc_lsa_LookupSids_count = -1;
static gint hf_lsarpc_lsa_DnsDomainInfo_dns_domain = -1;
static gint hf_lsarpc_lsa_TranslatedName_name = -1;
static gint hf_lsarpc_lsa_QueryInfoPolicy_level = -1;
static gint hf_lsarpc_lsa_LookupSids_domains = -1;
static gint hf_lsarpc_lsa_TranslatedSid_rid = -1;
static gint hf_lsarpc_lsa_DomainInfoEfs_efs_blob = -1;
static gint hf_lsarpc_lsa_RemovePrivilegesFromAccount_remove_all = -1;
static gint hf_lsarpc_lsa_SecretAccessMask_LSA_SECRET_QUERY_VALUE = -1;
static gint hf_lsarpc_lsa_AddAccountRights_handle = -1;
static gint hf_lsarpc_lsa_DomainInfoEfs_blob_size = -1;
static gint hf_lsarpc_lsa_OpenPolicy2_system_name = -1;
static gint hf_lsarpc_lsa_lsaRQueryForestTrustInformation_forest_trust_info = -1;
static gint hf_lsarpc_lsa_DefaultQuotaInfo_max_wss = -1;
static gint hf_lsarpc_lsa_DefaultQuotaInfo_paged_pool = -1;
static gint hf_lsarpc_lsa_LookupSids_level = -1;
static gint hf_lsarpc_lsa_AuditFullQueryInfo_log_is_full = -1;
static gint hf_lsarpc_lsa_RightSet_count = -1;
static gint hf_lsarpc_lsa_AuditLogInfo_log_size = -1;
static gint hf_lsarpc_lsa_AuditEventsInfo_settings = -1;
static gint hf_lsarpc_lsa_TranslatedSid2_rid = -1;
static gint hf_lsarpc_lsa_TranslatedSid2_sid_type = -1;
static gint hf_lsarpc_lsa_OpenTrustedDomainByName_handle = -1;
static gint hf_lsarpc_lsa_EnumTrustedDomainsEx_handle = -1;
static gint hf_lsarpc_lsa_AsciiString_length = -1;
static gint hf_lsarpc_lsa_TrustDomainInfoInfoAll_posix_offset = -1;
static gint hf_lsarpc_lsa_EnumAccountRights_sid = -1;
static gint hf_lsarpc_lsa_LookupSids_sids = -1;
static gint hf_lsarpc_lsa_TrustDomainInfoInfoAll_auth_info = -1;
static gint hf_lsarpc_lsa_CloseTrustedDomainEx_handle = -1;
static gint hf_lsarpc_lsa_QosInfo_context_mode = -1;
static gint hf_lsarpc_lsa_PolicyAccessMask_LSA_POLICY_VIEW_AUDIT_INFORMATION = -1;
static gint hf_lsarpc_lsa_SecretAccessMask_LSA_SECRET_SET_VALUE = -1;
static gint hf_lsarpc_lsa_EnumTrustDom_domains = -1;
static gint hf_lsarpc_lsa_TransNameArray_count = -1;
static gint hf_lsarpc_lsa_PolicyInformation_pd = -1;
static gint hf_lsarpc_lsa_TranslatedName2_sid_index = -1;
static gint hf_lsarpc_lsa_PolicyInformation_auditfullquery = -1;
static gint hf_lsarpc_lsa_ModificationInfo_modified_id = -1;
static gint hf_lsarpc_lsa_QuerySecret_new_mtime = -1;
static gint hf_lsarpc_lsa_LookupPrivValue_handle = -1;
static gint hf_lsarpc_lsa_TransSidArray2_count = -1;
static gint hf_lsarpc_lsa_AuditEventsInfo_count = -1;
static gint hf_lsarpc_lsa_TrustedDomainInfo_full_info = -1;
static gint hf_lsarpc_lsa_SetInfoPolicy_level = -1;
static gint hf_lsarpc_lsa_LookupSids3_count = -1;
static gint hf_lsarpc_lsa_TranslatedSid3_sid_index = -1;
static gint hf_lsarpc_lsa_SetInfoPolicy_handle = -1;

static gint proto_dcerpc_lsarpc = -1;
/* Version information */


static e_uuid_t uuid_dcerpc_lsarpc = {
	0x12345778, 0x1234, 0xabcd,
	{ 0xef, 0x00, 0x01, 0x23, 0x45, 0x67, 0x89, 0xab }
};
static guint16 ver_dcerpc_lsarpc = 0;

static const true_false_string lsa_PolicyAccessMask_LSA_POLICY_NOTIFICATION_tfs = {
   "LSA_POLICY_NOTIFICATION is SET",
   "LSA_POLICY_NOTIFICATION is NOT SET",
};
static const true_false_string lsa_PolicyAccessMask_LSA_POLICY_LOOKUP_NAMES_tfs = {
   "LSA_POLICY_LOOKUP_NAMES is SET",
   "LSA_POLICY_LOOKUP_NAMES is NOT SET",
};
static const true_false_string lsa_PolicyAccessMask_LSA_POLICY_SERVER_ADMIN_tfs = {
   "LSA_POLICY_SERVER_ADMIN is SET",
   "LSA_POLICY_SERVER_ADMIN is NOT SET",
};
static const true_false_string lsa_PolicyAccessMask_LSA_POLICY_AUDIT_LOG_ADMIN_tfs = {
   "LSA_POLICY_AUDIT_LOG_ADMIN is SET",
   "LSA_POLICY_AUDIT_LOG_ADMIN is NOT SET",
};
static const true_false_string lsa_PolicyAccessMask_LSA_POLICY_SET_AUDIT_REQUIREMENTS_tfs = {
   "LSA_POLICY_SET_AUDIT_REQUIREMENTS is SET",
   "LSA_POLICY_SET_AUDIT_REQUIREMENTS is NOT SET",
};
static const true_false_string lsa_PolicyAccessMask_LSA_POLICY_SET_DEFAULT_QUOTA_LIMITS_tfs = {
   "LSA_POLICY_SET_DEFAULT_QUOTA_LIMITS is SET",
   "LSA_POLICY_SET_DEFAULT_QUOTA_LIMITS is NOT SET",
};
static const true_false_string lsa_PolicyAccessMask_LSA_POLICY_CREATE_PRIVILEGE_tfs = {
   "LSA_POLICY_CREATE_PRIVILEGE is SET",
   "LSA_POLICY_CREATE_PRIVILEGE is NOT SET",
};
static const true_false_string lsa_PolicyAccessMask_LSA_POLICY_CREATE_SECRET_tfs = {
   "LSA_POLICY_CREATE_SECRET is SET",
   "LSA_POLICY_CREATE_SECRET is NOT SET",
};
static const true_false_string lsa_PolicyAccessMask_LSA_POLICY_CREATE_ACCOUNT_tfs = {
   "LSA_POLICY_CREATE_ACCOUNT is SET",
   "LSA_POLICY_CREATE_ACCOUNT is NOT SET",
};
static const true_false_string lsa_PolicyAccessMask_LSA_POLICY_TRUST_ADMIN_tfs = {
   "LSA_POLICY_TRUST_ADMIN is SET",
   "LSA_POLICY_TRUST_ADMIN is NOT SET",
};
static const true_false_string lsa_PolicyAccessMask_LSA_POLICY_GET_PRIVATE_INFORMATION_tfs = {
   "LSA_POLICY_GET_PRIVATE_INFORMATION is SET",
   "LSA_POLICY_GET_PRIVATE_INFORMATION is NOT SET",
};
static const true_false_string lsa_PolicyAccessMask_LSA_POLICY_VIEW_AUDIT_INFORMATION_tfs = {
   "LSA_POLICY_VIEW_AUDIT_INFORMATION is SET",
   "LSA_POLICY_VIEW_AUDIT_INFORMATION is NOT SET",
};
static const true_false_string lsa_PolicyAccessMask_LSA_POLICY_VIEW_LOCAL_INFORMATION_tfs = {
   "LSA_POLICY_VIEW_LOCAL_INFORMATION is SET",
   "LSA_POLICY_VIEW_LOCAL_INFORMATION is NOT SET",
};
static const true_false_string lsa_AccountAccessMask_LSA_ACCOUNT_ADJUST_SYSTEM_ACCESS_tfs = {
   "LSA_ACCOUNT_ADJUST_SYSTEM_ACCESS is SET",
   "LSA_ACCOUNT_ADJUST_SYSTEM_ACCESS is NOT SET",
};
static const true_false_string lsa_AccountAccessMask_LSA_ACCOUNT_ADJUST_QUOTAS_tfs = {
   "LSA_ACCOUNT_ADJUST_QUOTAS is SET",
   "LSA_ACCOUNT_ADJUST_QUOTAS is NOT SET",
};
static const true_false_string lsa_AccountAccessMask_LSA_ACCOUNT_ADJUST_PRIVILEGES_tfs = {
   "LSA_ACCOUNT_ADJUST_PRIVILEGES is SET",
   "LSA_ACCOUNT_ADJUST_PRIVILEGES is NOT SET",
};
static const true_false_string lsa_AccountAccessMask_LSA_ACCOUNT_VIEW_tfs = {
   "LSA_ACCOUNT_VIEW is SET",
   "LSA_ACCOUNT_VIEW is NOT SET",
};
static const true_false_string lsa_DomainAccessMask_LSA_DOMAIN_QUERY_AUTH_tfs = {
   "LSA_DOMAIN_QUERY_AUTH is SET",
   "LSA_DOMAIN_QUERY_AUTH is NOT SET",
};
static const true_false_string lsa_DomainAccessMask_LSA_DOMAIN_SET_AUTH_tfs = {
   "LSA_DOMAIN_SET_AUTH is SET",
   "LSA_DOMAIN_SET_AUTH is NOT SET",
};
static const true_false_string lsa_DomainAccessMask_LSA_DOMAIN_SET_POSIX_tfs = {
   "LSA_DOMAIN_SET_POSIX is SET",
   "LSA_DOMAIN_SET_POSIX is NOT SET",
};
static const true_false_string lsa_DomainAccessMask_LSA_DOMAIN_QUERY_POSIX_tfs = {
   "LSA_DOMAIN_QUERY_POSIX is SET",
   "LSA_DOMAIN_QUERY_POSIX is NOT SET",
};
static const true_false_string lsa_DomainAccessMask_LSA_DOMAIN_SET_CONTROLLERS_tfs = {
   "LSA_DOMAIN_SET_CONTROLLERS is SET",
   "LSA_DOMAIN_SET_CONTROLLERS is NOT SET",
};
static const true_false_string lsa_DomainAccessMask_LSA_DOMAIN_QUERY_CONTROLLERS_tfs = {
   "LSA_DOMAIN_QUERY_CONTROLLERS is SET",
   "LSA_DOMAIN_QUERY_CONTROLLERS is NOT SET",
};
static const true_false_string lsa_DomainAccessMask_LSA_DOMAIN_QUERY_DOMAIN_NAME_tfs = {
   "LSA_DOMAIN_QUERY_DOMAIN_NAME is SET",
   "LSA_DOMAIN_QUERY_DOMAIN_NAME is NOT SET",
};
static const true_false_string lsa_SecretAccessMask_LSA_SECRET_QUERY_VALUE_tfs = {
   "LSA_SECRET_QUERY_VALUE is SET",
   "LSA_SECRET_QUERY_VALUE is NOT SET",
};
static const true_false_string lsa_SecretAccessMask_LSA_SECRET_SET_VALUE_tfs = {
   "LSA_SECRET_SET_VALUE is SET",
   "LSA_SECRET_SET_VALUE is NOT SET",
};
static int lsarpc_dissect_element_lsa_String_length(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_String_size(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_String_string(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_String_string_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_String_string__(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_StringLarge_length(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_StringLarge_size(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_StringLarge_string(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_StringLarge_string_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_StringLarge_string__(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_Strings_count(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_Strings_names(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_Strings_names_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_Strings_names__(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_AsciiString_length(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_AsciiString_size(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_AsciiString_string(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_AsciiString_string_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_AsciiString_string__(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_AsciiStringLarge_length(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_AsciiStringLarge_size(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_AsciiStringLarge_string(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_AsciiStringLarge_string_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_AsciiStringLarge_string__(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LUID_low(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LUID_high(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_PrivEntry_name(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_PrivEntry_luid(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_PrivArray_count(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_PrivArray_privs(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_PrivArray_privs_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_PrivArray_privs__(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
const value_string lsarpc_lsa_SecurityImpersonationLevel_vals[] = {
	{ LSA_SECURITY_ANONYMOUS, "LSA_SECURITY_ANONYMOUS" },
	{ LSA_SECURITY_IDENTIFICATION, "LSA_SECURITY_IDENTIFICATION" },
	{ LSA_SECURITY_IMPERSONATION, "LSA_SECURITY_IMPERSONATION" },
	{ LSA_SECURITY_DELEGATION, "LSA_SECURITY_DELEGATION" },
{ 0, NULL }
};
static int lsarpc_dissect_element_lsa_QosInfo_len(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_QosInfo_impersonation_level(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_QosInfo_context_mode(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_QosInfo_effective_only(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_ObjectAttribute_len(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_ObjectAttribute_root_dir(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_ObjectAttribute_root_dir_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_ObjectAttribute_object_name(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_ObjectAttribute_object_name_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_ObjectAttribute_attributes(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_ObjectAttribute_sec_desc(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_ObjectAttribute_sec_desc_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_ObjectAttribute_sec_qos(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_ObjectAttribute_sec_qos_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_AuditLogInfo_percent_full(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_AuditLogInfo_log_size(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_AuditLogInfo_retention_time(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_AuditLogInfo_shutdown_in_progress(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_AuditLogInfo_time_to_shutdown(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_AuditLogInfo_next_audit_record(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_AuditLogInfo_unknown(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
const value_string lsarpc_lsa_PolicyAuditPolicy_vals[] = {
	{ LSA_AUDIT_POLICY_NONE, "LSA_AUDIT_POLICY_NONE" },
	{ LSA_AUDIT_POLICY_SUCCESS, "LSA_AUDIT_POLICY_SUCCESS" },
	{ LSA_AUDIT_POLICY_FAILURE, "LSA_AUDIT_POLICY_FAILURE" },
	{ LSA_AUDIT_POLICY_ALL, "LSA_AUDIT_POLICY_ALL" },
	{ LSA_AUDIT_POLICY_CLEAR, "LSA_AUDIT_POLICY_CLEAR" },
{ 0, NULL }
};
const value_string lsarpc_lsa_PolicyAuditEventType_vals[] = {
	{ LSA_AUDIT_CATEGORY_SYSTEM, "LSA_AUDIT_CATEGORY_SYSTEM" },
	{ LSA_AUDIT_CATEGORY_LOGON, "LSA_AUDIT_CATEGORY_LOGON" },
	{ LSA_AUDIT_CATEGORY_FILE_AND_OBJECT_ACCESS, "LSA_AUDIT_CATEGORY_FILE_AND_OBJECT_ACCESS" },
	{ LSA_AUDIT_CATEGORY_USE_OF_USER_RIGHTS, "LSA_AUDIT_CATEGORY_USE_OF_USER_RIGHTS" },
	{ LSA_AUDIT_CATEGORY_PROCCESS_TRACKING, "LSA_AUDIT_CATEGORY_PROCCESS_TRACKING" },
	{ LSA_AUDIT_CATEGORY_SECURITY_POLICY_CHANGES, "LSA_AUDIT_CATEGORY_SECURITY_POLICY_CHANGES" },
	{ LSA_AUDIT_CATEGORY_ACCOUNT_MANAGEMENT, "LSA_AUDIT_CATEGORY_ACCOUNT_MANAGEMENT" },
	{ LSA_AUDIT_CATEGORY_DIRECTORY_SERVICE_ACCESS, "LSA_AUDIT_CATEGORY_DIRECTORY_SERVICE_ACCESS" },
	{ LSA_AUDIT_CATEGORY_ACCOUNT_LOGON, "LSA_AUDIT_CATEGORY_ACCOUNT_LOGON" },
{ 0, NULL }
};
static int lsarpc_dissect_element_lsa_AuditEventsInfo_auditing_mode(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_AuditEventsInfo_settings(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_AuditEventsInfo_settings_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_AuditEventsInfo_settings__(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_AuditEventsInfo_count(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_DomainInfo_name(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_DomainInfo_sid(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_DomainInfo_sid_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_PDAccountInfo_name(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
const value_string lsarpc_lsa_PolicyServerRole_vals[] = {
	{ LSA_POLICY_ROLE_BACKUP, "LSA_POLICY_ROLE_BACKUP" },
	{ LSA_POLICY_ROLE_PRIMARY, "LSA_POLICY_ROLE_PRIMARY" },
{ 0, NULL }
};
static int lsarpc_dissect_element_lsa_ServerRole_role(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_ReplicaSourceInfo_source(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_ReplicaSourceInfo_account(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_DefaultQuotaInfo_paged_pool(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_DefaultQuotaInfo_non_paged_pool(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_DefaultQuotaInfo_min_wss(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_DefaultQuotaInfo_max_wss(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_DefaultQuotaInfo_pagefile(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_DefaultQuotaInfo_unknown(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_ModificationInfo_modified_id(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_ModificationInfo_db_create_time(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_AuditFullSetInfo_shutdown_on_full(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_AuditFullQueryInfo_unknown(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_AuditFullQueryInfo_shutdown_on_full(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_AuditFullQueryInfo_log_is_full(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_DnsDomainInfo_name(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_DnsDomainInfo_dns_domain(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_DnsDomainInfo_dns_forest(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_DnsDomainInfo_domain_guid(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_DnsDomainInfo_sid(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_DnsDomainInfo_sid_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
const value_string lsarpc_lsa_PolicyInfo_vals[] = {
	{ LSA_POLICY_INFO_AUDIT_LOG, "LSA_POLICY_INFO_AUDIT_LOG" },
	{ LSA_POLICY_INFO_AUDIT_EVENTS, "LSA_POLICY_INFO_AUDIT_EVENTS" },
	{ LSA_POLICY_INFO_DOMAIN, "LSA_POLICY_INFO_DOMAIN" },
	{ LSA_POLICY_INFO_PD, "LSA_POLICY_INFO_PD" },
	{ LSA_POLICY_INFO_ACCOUNT_DOMAIN, "LSA_POLICY_INFO_ACCOUNT_DOMAIN" },
	{ LSA_POLICY_INFO_ROLE, "LSA_POLICY_INFO_ROLE" },
	{ LSA_POLICY_INFO_REPLICA, "LSA_POLICY_INFO_REPLICA" },
	{ LSA_POLICY_INFO_QUOTA, "LSA_POLICY_INFO_QUOTA" },
	{ LSA_POLICY_INFO_DB, "LSA_POLICY_INFO_DB" },
	{ LSA_POLICY_INFO_AUDIT_FULL_SET, "LSA_POLICY_INFO_AUDIT_FULL_SET" },
	{ LSA_POLICY_INFO_AUDIT_FULL_QUERY, "LSA_POLICY_INFO_AUDIT_FULL_QUERY" },
	{ LSA_POLICY_INFO_DNS, "LSA_POLICY_INFO_DNS" },
	{ LSA_POLICY_INFO_DNS_INT, "LSA_POLICY_INFO_DNS_INT" },
	{ LSA_POLICY_INFO_LOCAL_ACCOUNT_DOMAIN, "LSA_POLICY_INFO_LOCAL_ACCOUNT_DOMAIN" },
{ 0, NULL }
};
static int lsarpc_dissect_element_lsa_PolicyInformation_audit_log(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_PolicyInformation_audit_events(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_PolicyInformation_domain(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_PolicyInformation_pd(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_PolicyInformation_account_domain(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_PolicyInformation_role(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_PolicyInformation_replica(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_PolicyInformation_quota(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_PolicyInformation_db(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_PolicyInformation_auditfullset(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_PolicyInformation_auditfullquery(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_PolicyInformation_dns(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_SidPtr_sid(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_SidPtr_sid_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_SidArray_num_sids(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_SidArray_sids(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_SidArray_sids_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_SidArray_sids__(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_DomainList_count(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_DomainList_domains(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_DomainList_domains_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_DomainList_domains__(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
const value_string lsarpc_lsa_SidType_vals[] = {
	{ SID_NAME_USE_NONE, "SID_NAME_USE_NONE" },
	{ SID_NAME_USER, "SID_NAME_USER" },
	{ SID_NAME_DOM_GRP, "SID_NAME_DOM_GRP" },
	{ SID_NAME_DOMAIN, "SID_NAME_DOMAIN" },
	{ SID_NAME_ALIAS, "SID_NAME_ALIAS" },
	{ SID_NAME_WKN_GRP, "SID_NAME_WKN_GRP" },
	{ SID_NAME_DELETED, "SID_NAME_DELETED" },
	{ SID_NAME_INVALID, "SID_NAME_INVALID" },
	{ SID_NAME_UNKNOWN, "SID_NAME_UNKNOWN" },
	{ SID_NAME_COMPUTER, "SID_NAME_COMPUTER" },
{ 0, NULL }
};
static int lsarpc_dissect_element_lsa_TranslatedSid_sid_type(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TranslatedSid_rid(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TranslatedSid_sid_index(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TransSidArray_count(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TransSidArray_sids(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TransSidArray_sids_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TransSidArray_sids__(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_RefDomainList_count(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_RefDomainList_domains(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_RefDomainList_domains_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_RefDomainList_domains__(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_RefDomainList_max_size(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
const value_string lsarpc_lsa_LookupNamesLevel_vals[] = {
	{ LSA_LOOKUP_NAMES_ALL, "LSA_LOOKUP_NAMES_ALL" },
	{ LSA_LOOKUP_NAMES_DOMAINS_ONLY, "LSA_LOOKUP_NAMES_DOMAINS_ONLY" },
	{ LSA_LOOKUP_NAMES_PRIMARY_DOMAIN_ONLY, "LSA_LOOKUP_NAMES_PRIMARY_DOMAIN_ONLY" },
	{ LSA_LOOKUP_NAMES_UPLEVEL_TRUSTS_ONLY, "LSA_LOOKUP_NAMES_UPLEVEL_TRUSTS_ONLY" },
	{ LSA_LOOKUP_NAMES_FOREST_TRUSTS_ONLY, "LSA_LOOKUP_NAMES_FOREST_TRUSTS_ONLY" },
	{ LSA_LOOKUP_NAMES_UPLEVEL_TRUSTS_ONLY2, "LSA_LOOKUP_NAMES_UPLEVEL_TRUSTS_ONLY2" },
{ 0, NULL }
};
static int lsarpc_dissect_element_lsa_TranslatedName_sid_type(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TranslatedName_name(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TranslatedName_sid_index(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TransNameArray_count(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TransNameArray_names(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TransNameArray_names_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TransNameArray_names__(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LUIDAttribute_luid(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LUIDAttribute_attribute(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_PrivilegeSet_count(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_PrivilegeSet_unknown(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_PrivilegeSet_set(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_PrivilegeSet_set_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_DATA_BUF_length(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_DATA_BUF_size(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_DATA_BUF_data(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_DATA_BUF_data_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_DATA_BUF_data__(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_DATA_BUF2_size(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_DATA_BUF2_data(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_DATA_BUF2_data_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_DATA_BUF2_data__(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
const value_string lsarpc_lsa_TrustDomInfoEnum_vals[] = {
	{ LSA_TRUSTED_DOMAIN_INFO_NAME, "LSA_TRUSTED_DOMAIN_INFO_NAME" },
	{ LSA_TRUSTED_DOMAIN_INFO_CONTROLLERS_INFO, "LSA_TRUSTED_DOMAIN_INFO_CONTROLLERS_INFO" },
	{ LSA_TRUSTED_DOMAIN_INFO_POSIX_OFFSET, "LSA_TRUSTED_DOMAIN_INFO_POSIX_OFFSET" },
	{ LSA_TRUSTED_DOMAIN_INFO_PASSWORD, "LSA_TRUSTED_DOMAIN_INFO_PASSWORD" },
	{ LSA_TRUSTED_DOMAIN_INFO_BASIC, "LSA_TRUSTED_DOMAIN_INFO_BASIC" },
	{ LSA_TRUSTED_DOMAIN_INFO_INFO_EX, "LSA_TRUSTED_DOMAIN_INFO_INFO_EX" },
	{ LSA_TRUSTED_DOMAIN_INFO_AUTH_INFO, "LSA_TRUSTED_DOMAIN_INFO_AUTH_INFO" },
	{ LSA_TRUSTED_DOMAIN_INFO_FULL_INFO, "LSA_TRUSTED_DOMAIN_INFO_FULL_INFO" },
	{ LSA_TRUSTED_DOMAIN_INFO_11, "LSA_TRUSTED_DOMAIN_INFO_11" },
	{ LSA_TRUSTED_DOMAIN_INFO_INFO_ALL, "LSA_TRUSTED_DOMAIN_INFO_INFO_ALL" },
{ 0, NULL }
};
static int lsarpc_dissect_element_lsa_TrustDomainInfoName_netbios_name(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TrustDomainInfoPosixOffset_posix_offset(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TrustDomainInfoPassword_password(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TrustDomainInfoPassword_password_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TrustDomainInfoPassword_old_password(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TrustDomainInfoPassword_old_password_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TrustDomainInfoBasic_netbios_name(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TrustDomainInfoBasic_sid(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TrustDomainInfoBasic_sid_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TrustDomainInfoInfoEx_domain_name(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TrustDomainInfoInfoEx_netbios_name(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TrustDomainInfoInfoEx_sid(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TrustDomainInfoInfoEx_sid_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TrustDomainInfoInfoEx_trust_direction(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TrustDomainInfoInfoEx_trust_type(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TrustDomainInfoInfoEx_trust_attributes(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TrustDomainInfoBuffer_last_update_time(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TrustDomainInfoBuffer_secret_type(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TrustDomainInfoBuffer_data(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TrustDomainInfoAuthInfo_incoming_count(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TrustDomainInfoAuthInfo_incoming_current_auth_info(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TrustDomainInfoAuthInfo_incoming_current_auth_info_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TrustDomainInfoAuthInfo_incoming_previous_auth_info(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TrustDomainInfoAuthInfo_incoming_previous_auth_info_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TrustDomainInfoAuthInfo_outgoing_count(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TrustDomainInfoAuthInfo_outgoing_current_auth_info(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TrustDomainInfoAuthInfo_outgoing_current_auth_info_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TrustDomainInfoAuthInfo_outgoing_previous_auth_info(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TrustDomainInfoAuthInfo_outgoing_previous_auth_info_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TrustDomainInfoFullInfo_info_ex(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TrustDomainInfoFullInfo_posix_offset(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TrustDomainInfoFullInfo_auth_info(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TrustDomainInfo11_info_ex(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TrustDomainInfo11_data1(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TrustDomainInfoInfoAll_info_ex(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TrustDomainInfoInfoAll_data1(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TrustDomainInfoInfoAll_posix_offset(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TrustDomainInfoInfoAll_auth_info(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TrustedDomainInfo_name(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TrustedDomainInfo_posix_offset(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TrustedDomainInfo_password(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TrustedDomainInfo_info_basic(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TrustedDomainInfo_info_ex(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TrustedDomainInfo_auth_info(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TrustedDomainInfo_full_info(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TrustedDomainInfo_info11(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TrustedDomainInfo_info_all(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_DATA_BUF_PTR_buf(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_DATA_BUF_PTR_buf_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_RightAttribute_name(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_RightAttribute_name_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_RightSet_count(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_RightSet_names(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_RightSet_names_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_RightSet_names__(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_StringPointer_string(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_StringPointer_string_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_DomainListEx_count(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_DomainListEx_domains(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_DomainListEx_domains_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_DomainListEx_domains__(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_DomainInfoKerberos_enforce_restrictions(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_DomainInfoKerberos_service_tkt_lifetime(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_DomainInfoKerberos_user_tkt_lifetime(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_DomainInfoKerberos_user_tkt_renewaltime(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_DomainInfoKerberos_clock_skew(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_DomainInfoKerberos_unknown6(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_DomainInfoEfs_blob_size(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_DomainInfoEfs_efs_blob(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_DomainInfoEfs_efs_blob_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_DomainInfoEfs_efs_blob__(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
const value_string lsarpc_lsa_DomainInfoEnum_vals[] = {
	{ LSA_DOMAIN_INFO_POLICY_QOS, "LSA_DOMAIN_INFO_POLICY_QOS" },
	{ LSA_DOMAIN_INFO_POLICY_EFS, "LSA_DOMAIN_INFO_POLICY_EFS" },
	{ LSA_DOMAIN_INFO_POLICY_KERBEROS, "LSA_DOMAIN_INFO_POLICY_KERBEROS" },
{ 0, NULL }
};
static int lsarpc_dissect_element_lsa_DomainInformationPolicy_efs_info(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_DomainInformationPolicy_kerberos_info(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TranslatedName2_sid_type(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TranslatedName2_name(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TranslatedName2_sid_index(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TranslatedName2_unknown(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TransNameArray2_count(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TransNameArray2_names(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TransNameArray2_names_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TransNameArray2_names__(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TranslatedSid2_sid_type(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TranslatedSid2_rid(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TranslatedSid2_sid_index(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TranslatedSid2_unknown(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TransSidArray2_count(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TransSidArray2_sids(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TransSidArray2_sids_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TransSidArray2_sids__(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TranslatedSid3_sid_type(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TranslatedSid3_sid(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TranslatedSid3_sid_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TranslatedSid3_sid_index(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TranslatedSid3_unknown(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TransSidArray3_count(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TransSidArray3_sids(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TransSidArray3_sids_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_TransSidArray3_sids__(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_ForestTrustBinaryData_length(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_ForestTrustBinaryData_data(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_ForestTrustBinaryData_data_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_ForestTrustBinaryData_data__(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_ForestTrustDomainInfo_domain_sid(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_ForestTrustDomainInfo_domain_sid_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_ForestTrustDomainInfo_dns_domain_name(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_ForestTrustDomainInfo_netbios_domain_name(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_ForestTrustData_top_level_name(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_ForestTrustData_top_level_name_ex(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_ForestTrustData_domain_info(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_ForestTrustData_data(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
const value_string lsarpc_lsa_ForestTrustRecordType_vals[] = {
	{ LSA_FOREST_TRUST_TOP_LEVEL_NAME, "LSA_FOREST_TRUST_TOP_LEVEL_NAME" },
	{ LSA_FOREST_TRUST_TOP_LEVEL_NAME_EX, "LSA_FOREST_TRUST_TOP_LEVEL_NAME_EX" },
	{ LSA_FOREST_TRUST_DOMAIN_INFO, "LSA_FOREST_TRUST_DOMAIN_INFO" },
	{ LSA_FOREST_TRUST_RECORD_TYPE_LAST, "LSA_FOREST_TRUST_RECORD_TYPE_LAST" },
{ 0, NULL }
};
static int lsarpc_dissect_element_lsa_ForestTrustRecord_flags(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_ForestTrustRecord_level(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, guint32 *level);
static int lsarpc_dissect_element_lsa_ForestTrustRecord_unknown(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_ForestTrustRecord_forest_trust_data(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, guint32 *level);
static int lsarpc_dissect_element_lsa_ForestTrustInformation_count(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_ForestTrustInformation_entries(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_ForestTrustInformation_entries_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_ForestTrustInformation_entries__(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_ForestTrustInformation_entries___(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_Close_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_Close_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_Delete_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_Delete_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_EnumPrivs_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_EnumPrivs_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_EnumPrivs_resume_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_EnumPrivs_resume_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_EnumPrivs_max_count(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_EnumPrivs_privs(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_EnumPrivs_privs_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_QuerySecurity_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_QuerySecurity_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_QuerySecurity_sec_info(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_QuerySecurity_sdbuf(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_QuerySecurity_sdbuf_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_OpenPolicy_system_name(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_OpenPolicy_system_name_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_OpenPolicy_attr(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_OpenPolicy_attr_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_OpenPolicy_access_mask(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_OpenPolicy_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_OpenPolicy_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_QueryInfoPolicy_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_QueryInfoPolicy_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_QueryInfoPolicy_level(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_QueryInfoPolicy_info(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_QueryInfoPolicy_info_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_SetInfoPolicy_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_SetInfoPolicy_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_SetInfoPolicy_level(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_SetInfoPolicy_info(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_SetInfoPolicy_info_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_CreateAccount_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_CreateAccount_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_CreateAccount_sid(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_CreateAccount_sid_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_CreateAccount_access_mask(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_CreateAccount_acct_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_CreateAccount_acct_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_EnumAccounts_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_EnumAccounts_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_EnumAccounts_resume_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_EnumAccounts_resume_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_EnumAccounts_num_entries(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_EnumAccounts_sids(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_EnumAccounts_sids_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_CreateTrustedDomain_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_CreateTrustedDomain_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_CreateTrustedDomain_info(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_CreateTrustedDomain_info_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_CreateTrustedDomain_access_mask(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_CreateTrustedDomain_trustdom_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_CreateTrustedDomain_trustdom_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_EnumTrustDom_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_EnumTrustDom_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_EnumTrustDom_resume_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_EnumTrustDom_resume_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_EnumTrustDom_max_size(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_EnumTrustDom_domains(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_EnumTrustDom_domains_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupNames_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupNames_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupNames_num_names(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupNames_names(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupNames_names_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupNames_domains(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupNames_domains_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupNames_sids(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupNames_sids_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupNames_level(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupNames_count(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupNames_count_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupSids_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupSids_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupSids_sids(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupSids_sids_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupSids_domains(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupSids_domains_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupSids_names(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupSids_names_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupSids_level(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupSids_count(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupSids_count_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_CreateSecret_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_CreateSecret_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_CreateSecret_name(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_CreateSecret_access_mask(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_CreateSecret_sec_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_CreateSecret_sec_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_OpenAccount_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_OpenAccount_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_OpenAccount_sid(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_OpenAccount_sid_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_OpenAccount_access_mask(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_OpenAccount_acct_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_OpenAccount_acct_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_EnumPrivsAccount_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_EnumPrivsAccount_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_EnumPrivsAccount_privs(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_EnumPrivsAccount_privs_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_AddPrivilegesToAccount_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_AddPrivilegesToAccount_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_AddPrivilegesToAccount_privs(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_AddPrivilegesToAccount_privs_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_RemovePrivilegesFromAccount_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_RemovePrivilegesFromAccount_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_RemovePrivilegesFromAccount_remove_all(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_RemovePrivilegesFromAccount_privs(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_RemovePrivilegesFromAccount_privs_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_OpenTrustedDomain_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_OpenTrustedDomain_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_OpenTrustedDomain_sid(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_OpenTrustedDomain_sid_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_OpenTrustedDomain_access_mask(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_OpenTrustedDomain_trustdom_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_OpenTrustedDomain_trustdom_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_QueryTrustedDomainInfo_trustdom_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_QueryTrustedDomainInfo_trustdom_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_QueryTrustedDomainInfo_level(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_QueryTrustedDomainInfo_info(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_QueryTrustedDomainInfo_info_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_OpenSecret_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_OpenSecret_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_OpenSecret_name(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_OpenSecret_access_mask(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_OpenSecret_sec_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_OpenSecret_sec_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_SetSecret_sec_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_SetSecret_sec_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_SetSecret_new_val(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_SetSecret_new_val_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_SetSecret_old_val(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_SetSecret_old_val_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_QuerySecret_sec_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_QuerySecret_sec_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_QuerySecret_new_val(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_QuerySecret_new_val_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_QuerySecret_new_mtime(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_QuerySecret_new_mtime_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_QuerySecret_old_val(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_QuerySecret_old_val_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_QuerySecret_old_mtime(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_QuerySecret_old_mtime_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupPrivValue_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupPrivValue_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupPrivValue_name(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupPrivValue_name_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupPrivValue_luid(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupPrivValue_luid_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupPrivName_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupPrivName_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupPrivName_luid(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupPrivName_luid_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupPrivName_name(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupPrivName_name_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupPrivDisplayName_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupPrivDisplayName_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupPrivDisplayName_name(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupPrivDisplayName_name_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupPrivDisplayName_disp_name(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupPrivDisplayName_disp_name_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupPrivDisplayName_language_id(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupPrivDisplayName_language_id_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupPrivDisplayName_unknown(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_EnumAccountsWithUserRight_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_EnumAccountsWithUserRight_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_EnumAccountsWithUserRight_name(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_EnumAccountsWithUserRight_name_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_EnumAccountsWithUserRight_sids(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_EnumAccountsWithUserRight_sids_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_EnumAccountRights_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_EnumAccountRights_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_EnumAccountRights_sid(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_EnumAccountRights_sid_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_EnumAccountRights_rights(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_EnumAccountRights_rights_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_AddAccountRights_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_AddAccountRights_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_AddAccountRights_sid(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_AddAccountRights_sid_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_AddAccountRights_rights(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_AddAccountRights_rights_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_RemoveAccountRights_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_RemoveAccountRights_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_RemoveAccountRights_sid(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_RemoveAccountRights_sid_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_RemoveAccountRights_unknown(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_RemoveAccountRights_rights(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_RemoveAccountRights_rights_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_QueryTrustedDomainInfoBySid_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_QueryTrustedDomainInfoBySid_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_QueryTrustedDomainInfoBySid_dom_sid(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_QueryTrustedDomainInfoBySid_dom_sid_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_QueryTrustedDomainInfoBySid_level(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_QueryTrustedDomainInfoBySid_info(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_QueryTrustedDomainInfoBySid_info_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_DeleteTrustedDomain_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_DeleteTrustedDomain_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_DeleteTrustedDomain_dom_sid(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_DeleteTrustedDomain_dom_sid_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_OpenPolicy2_system_name(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_OpenPolicy2_system_name_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_OpenPolicy2_attr(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_OpenPolicy2_attr_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_OpenPolicy2_access_mask(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_OpenPolicy2_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_OpenPolicy2_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_GetUserName_system_name(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_GetUserName_system_name_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_GetUserName_account_name(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_GetUserName_account_name_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_GetUserName_authority_name(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_GetUserName_authority_name_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_QueryInfoPolicy2_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_QueryInfoPolicy2_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_QueryInfoPolicy2_level(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_QueryInfoPolicy2_info(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_QueryInfoPolicy2_info_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_SetInfoPolicy2_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_SetInfoPolicy2_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_SetInfoPolicy2_level(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_SetInfoPolicy2_info(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_SetInfoPolicy2_info_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_QueryTrustedDomainInfoByName_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_QueryTrustedDomainInfoByName_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_QueryTrustedDomainInfoByName_trusted_domain(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_QueryTrustedDomainInfoByName_level(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_QueryTrustedDomainInfoByName_info(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_QueryTrustedDomainInfoByName_info_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_SetTrustedDomainInfoByName_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_SetTrustedDomainInfoByName_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_SetTrustedDomainInfoByName_trusted_domain(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_SetTrustedDomainInfoByName_level(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_SetTrustedDomainInfoByName_info(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_SetTrustedDomainInfoByName_info_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_EnumTrustedDomainsEx_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_EnumTrustedDomainsEx_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_EnumTrustedDomainsEx_resume_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_EnumTrustedDomainsEx_resume_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_EnumTrustedDomainsEx_domains(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_EnumTrustedDomainsEx_domains_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_EnumTrustedDomainsEx_max_size(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_CloseTrustedDomainEx_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_CloseTrustedDomainEx_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_QueryDomainInformationPolicy_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_QueryDomainInformationPolicy_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_QueryDomainInformationPolicy_level(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_QueryDomainInformationPolicy_info(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_QueryDomainInformationPolicy_info_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_SetDomainInformationPolicy_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_SetDomainInformationPolicy_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_SetDomainInformationPolicy_level(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_SetDomainInformationPolicy_info(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_SetDomainInformationPolicy_info_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_OpenTrustedDomainByName_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_OpenTrustedDomainByName_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_OpenTrustedDomainByName_name(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_OpenTrustedDomainByName_access_mask(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_OpenTrustedDomainByName_trustdom_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_OpenTrustedDomainByName_trustdom_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupSids2_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupSids2_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupSids2_sids(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupSids2_sids_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupSids2_domains(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupSids2_domains_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupSids2_names(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupSids2_names_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupSids2_level(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupSids2_count(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupSids2_count_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupSids2_unknown1(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupSids2_unknown2(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupNames2_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupNames2_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupNames2_num_names(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupNames2_names(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupNames2_names_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupNames2_domains(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupNames2_domains_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupNames2_sids(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupNames2_sids_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupNames2_level(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupNames2_count(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupNames2_count_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupNames2_unknown1(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupNames2_unknown2(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupNames3_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupNames3_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupNames3_num_names(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupNames3_names(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupNames3_names_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupNames3_domains(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupNames3_domains_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupNames3_sids(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupNames3_sids_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupNames3_level(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupNames3_count(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupNames3_count_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupNames3_unknown1(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupNames3_unknown2(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_lsaRQueryForestTrustInformation_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_lsaRQueryForestTrustInformation_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_lsaRQueryForestTrustInformation_trusted_domain_name(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_lsaRQueryForestTrustInformation_trusted_domain_name_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_lsaRQueryForestTrustInformation_unknown(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_lsaRQueryForestTrustInformation_forest_trust_info(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_lsaRQueryForestTrustInformation_forest_trust_info_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_lsaRQueryForestTrustInformation_forest_trust_info__(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupSids3_sids(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupSids3_sids_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupSids3_domains(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupSids3_domains_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupSids3_names(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupSids3_names_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupSids3_level(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupSids3_count(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupSids3_count_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupSids3_unknown1(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupSids3_unknown2(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupNames4_num_names(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupNames4_names(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupNames4_names_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupNames4_domains(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupNames4_domains_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupNames4_sids(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupNames4_sids_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupNames4_level(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupNames4_count(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupNames4_count_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupNames4_unknown1(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static int lsarpc_dissect_element_lsa_LookupNames4_unknown2(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_);
static void
lsarpc_policy_specific_rights(tvbuff_t *tvb _U_, gint offset _U_, proto_tree *tree _U_, guint32 access _U_)
{
	proto_tree_add_boolean(tree, hf_lsarpc_lsa_PolicyAccessMask_LSA_POLICY_NOTIFICATION, tvb, offset, 4, access);
	proto_tree_add_boolean(tree, hf_lsarpc_lsa_PolicyAccessMask_LSA_POLICY_LOOKUP_NAMES, tvb, offset, 4, access);
	proto_tree_add_boolean(tree, hf_lsarpc_lsa_PolicyAccessMask_LSA_POLICY_SERVER_ADMIN, tvb, offset, 4, access);
	proto_tree_add_boolean(tree, hf_lsarpc_lsa_PolicyAccessMask_LSA_POLICY_AUDIT_LOG_ADMIN, tvb, offset, 4, access);
	proto_tree_add_boolean(tree, hf_lsarpc_lsa_PolicyAccessMask_LSA_POLICY_SET_AUDIT_REQUIREMENTS, tvb, offset, 4, access);
	proto_tree_add_boolean(tree, hf_lsarpc_lsa_PolicyAccessMask_LSA_POLICY_SET_DEFAULT_QUOTA_LIMITS, tvb, offset, 4, access);
	proto_tree_add_boolean(tree, hf_lsarpc_lsa_PolicyAccessMask_LSA_POLICY_CREATE_PRIVILEGE, tvb, offset, 4, access);
	proto_tree_add_boolean(tree, hf_lsarpc_lsa_PolicyAccessMask_LSA_POLICY_CREATE_SECRET, tvb, offset, 4, access);
	proto_tree_add_boolean(tree, hf_lsarpc_lsa_PolicyAccessMask_LSA_POLICY_CREATE_ACCOUNT, tvb, offset, 4, access);
	proto_tree_add_boolean(tree, hf_lsarpc_lsa_PolicyAccessMask_LSA_POLICY_TRUST_ADMIN, tvb, offset, 4, access);
	proto_tree_add_boolean(tree, hf_lsarpc_lsa_PolicyAccessMask_LSA_POLICY_GET_PRIVATE_INFORMATION, tvb, offset, 4, access);
	proto_tree_add_boolean(tree, hf_lsarpc_lsa_PolicyAccessMask_LSA_POLICY_VIEW_AUDIT_INFORMATION, tvb, offset, 4, access);
	proto_tree_add_boolean(tree, hf_lsarpc_lsa_PolicyAccessMask_LSA_POLICY_VIEW_LOCAL_INFORMATION, tvb, offset, 4, access);
}
static void
lsarpc_account_specific_rights(tvbuff_t *tvb _U_, gint offset _U_, proto_tree *tree _U_, guint32 access _U_)
{
	proto_tree_add_boolean(tree, hf_lsarpc_lsa_AccountAccessMask_LSA_ACCOUNT_ADJUST_SYSTEM_ACCESS, tvb, offset, 4, access);
	proto_tree_add_boolean(tree, hf_lsarpc_lsa_AccountAccessMask_LSA_ACCOUNT_ADJUST_QUOTAS, tvb, offset, 4, access);
	proto_tree_add_boolean(tree, hf_lsarpc_lsa_AccountAccessMask_LSA_ACCOUNT_ADJUST_PRIVILEGES, tvb, offset, 4, access);
	proto_tree_add_boolean(tree, hf_lsarpc_lsa_AccountAccessMask_LSA_ACCOUNT_VIEW, tvb, offset, 4, access);
}
static void
lsarpc_secret_specific_rights(tvbuff_t *tvb _U_, gint offset _U_, proto_tree *tree _U_, guint32 access _U_)
{
	proto_tree_add_boolean(tree, hf_lsarpc_lsa_SecretAccessMask_LSA_SECRET_QUERY_VALUE, tvb, offset, 4, access);
	proto_tree_add_boolean(tree, hf_lsarpc_lsa_SecretAccessMask_LSA_SECRET_SET_VALUE, tvb, offset, 4, access);
}
static void
lsarpc_domain_specific_rights(tvbuff_t *tvb _U_, gint offset _U_, proto_tree *tree _U_, guint32 access _U_)
{
	proto_tree_add_boolean(tree, hf_lsarpc_lsa_DomainAccessMask_LSA_DOMAIN_QUERY_AUTH, tvb, offset, 4, access);
	proto_tree_add_boolean(tree, hf_lsarpc_lsa_DomainAccessMask_LSA_DOMAIN_SET_AUTH, tvb, offset, 4, access);
	proto_tree_add_boolean(tree, hf_lsarpc_lsa_DomainAccessMask_LSA_DOMAIN_SET_POSIX, tvb, offset, 4, access);
	proto_tree_add_boolean(tree, hf_lsarpc_lsa_DomainAccessMask_LSA_DOMAIN_QUERY_POSIX, tvb, offset, 4, access);
	proto_tree_add_boolean(tree, hf_lsarpc_lsa_DomainAccessMask_LSA_DOMAIN_SET_CONTROLLERS, tvb, offset, 4, access);
	proto_tree_add_boolean(tree, hf_lsarpc_lsa_DomainAccessMask_LSA_DOMAIN_QUERY_CONTROLLERS, tvb, offset, 4, access);
	proto_tree_add_boolean(tree, hf_lsarpc_lsa_DomainAccessMask_LSA_DOMAIN_QUERY_DOMAIN_NAME, tvb, offset, 4, access);
}
struct access_mask_info lsarpc_policy_access_mask_info = {
	"LSA Policy",			/* Name of specific rights */
	lsarpc_policy_specific_rights,	/* Dissection function */
	NULL,				/* Generic mapping table */
	NULL				/* Standard mapping table */
};
struct access_mask_info lsarpc_account_access_mask_info = {
	"LSA Account",			/* Name of specific rights */
	lsarpc_account_specific_rights,	/* Dissection function */
	NULL,				/* Generic mapping table */
	NULL				/* Standard mapping table */
};
struct access_mask_info lsarpc_secret_access_mask_info = {
	"LSA Secret",			/* Name of specific rights */
	lsarpc_secret_specific_rights,	/* Dissection function */
	NULL,				/* Generic mapping table */
	NULL				/* Standard mapping table */
};
struct access_mask_info lsarpc_domain_access_mask_info = {
	"LSA Domain",			/* Name of specific rights */
	lsarpc_domain_specific_rights,	/* Dissection function */
	NULL,				/* Generic mapping table */
	NULL				/* Standard mapping table */
};
int
lsarpc_dissect_bitmap_lsa_PolicyAccessMask(tvbuff_t *tvb, int offset, packet_info *pinfo, proto_tree *tree, dcerpc_info *di, guint8 *drep, int hf_index _U_, guint32 param _U_)
{
	offset = dissect_nt_access_mask(
		tvb, offset, pinfo, tree, di, drep, hf_lsarpc_policy_access_mask,
		&lsarpc_policy_access_mask_info, NULL);
	return offset;
}
int
lsarpc_dissect_bitmap_lsa_AccountAccessMask(tvbuff_t *tvb, int offset, packet_info *pinfo, proto_tree *tree, dcerpc_info *di, guint8 *drep, int hf_index _U_, guint32 param _U_)
{
	offset = dissect_nt_access_mask(
		tvb, offset, pinfo, tree, di, drep, hf_lsarpc_account_access_mask,
		&lsarpc_account_access_mask_info, NULL);
	return offset;
}
int
lsarpc_dissect_bitmap_lsa_SecretAccessMask(tvbuff_t *tvb, int offset, packet_info *pinfo, proto_tree *tree, dcerpc_info *di, guint8 *drep, int hf_index _U_, guint32 param _U_)
{
	offset = dissect_nt_access_mask(
		tvb, offset, pinfo, tree, di, drep, hf_lsarpc_secret_access_mask,
		&lsarpc_secret_access_mask_info, NULL);
	return offset;
}
int
lsarpc_dissect_bitmap_lsa_DomainAccessMask(tvbuff_t *tvb, int offset, packet_info *pinfo, proto_tree *tree, dcerpc_info *di, guint8 *drep, int hf_index _U_, guint32 param _U_)
{
	offset = dissect_nt_access_mask(
		tvb, offset, pinfo, tree, di, drep, hf_lsarpc_domain_access_mask,
		&lsarpc_domain_access_mask_info, NULL);
	return offset;
}
static int
cnf_dissect_sec_desc_buf_(tvbuff_t *tvb, int offset, packet_info *pinfo, proto_tree *tree, dcerpc_info *di, guint8 *drep)
{
	guint32 len;
	e_ctx_hnd *polhnd = NULL;
	dcerpc_call_value *dcv = NULL;
	guint32 type=0;
	struct access_mask_info *ami=NULL;
	if(di->conformant_run){
		/*just a run to handle conformant arrays, nothing to dissect */
		return offset;
	}
	offset = dissect_ndr_uint32 (tvb, offset, pinfo, tree, di, drep,
		hf_lsarpc_sec_desc_buf_len, &len);
	dcv = (dcerpc_call_value *)di->call_data;
	if(dcv){
		polhnd = dcv->pol;
	}
	if(polhnd){
		dcerpc_fetch_polhnd_data(polhnd, NULL, &type, NULL, NULL,
					pinfo->fd->num);
	}
	switch(type){
	case PIDL_POLHND_TYPE_LSA_POLICY:
		ami=&lsarpc_policy_access_mask_info;
		break;
	case PIDL_POLHND_TYPE_LSA_ACCOUNT:
		ami=&lsarpc_account_access_mask_info;
		break;
	case PIDL_POLHND_TYPE_LSA_SECRET:
		ami=&lsarpc_secret_access_mask_info;
		break;
	case PIDL_POLHND_TYPE_LSA_DOMAIN:
		ami=&lsarpc_domain_access_mask_info;
		break;
	}
	dissect_nt_sec_desc(tvb, offset, pinfo, tree, drep, TRUE, len, ami);
	offset += len;
	return offset;
}
static int
cnf_dissect_sec_desc_buf(tvbuff_t *tvb, int offset, packet_info *pinfo, proto_tree *tree, dcerpc_info *di, guint8 *drep)
{
	guint32 len;
	if(di->conformant_run){
		/*just a run to handle conformant arrays, nothing to dissect */
		return offset;
	}
	offset = dissect_ndr_uint32 (tvb, offset, pinfo, tree, di, drep,
		hf_lsarpc_sec_desc_buf_len, &len);
        offset = dissect_ndr_pointer(tvb, offset, pinfo, tree, di, drep,
                       cnf_dissect_sec_desc_buf_, NDR_POINTER_UNIQUE,
                       "LSA SECURITY DESCRIPTOR data:", -1);
	return offset;
}
int
lsarpc_dissect_sec_desc_buf(tvbuff_t *tvb, int offset, packet_info *pinfo, proto_tree *tree, dcerpc_info *di, guint8 *drep){
	return cnf_dissect_sec_desc_buf(tvb, offset, pinfo, tree, di, drep);
}
int
lsarpc_dissect_struct_security_descriptor(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info *di, guint8 *drep _U_, int unused1 _U_, int unused2 _U_){
	return cnf_dissect_sec_desc_buf(tvb, offset, pinfo, tree, di, drep);
} 
int
lsarpc_dissect_struct_dom_sid2(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info *di, guint8 *drep _U_, int unused1 _U_, int unused2 _U_) {
	/* sid */
	return dissect_ndr_nt_SID(tvb, offset, pinfo, tree, di, drep);
}
static int
cnf_dissect_hyper(tvbuff_t *tvb, int offset, packet_info *pinfo, proto_tree *tree, dcerpc_info *di, guint8 *drep, guint32 param _U_, int hfindex)
{
	offset = dissect_ndr_uint64(tvb, offset, pinfo, tree, di, drep, hfindex, NULL);
	return offset;
}
static int
lsarpc_dissect_element_lsa_LookupNames3_names_X(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info *di _U_, guint8 *drep _U_)
{
	proto_item *item = NULL;
	proto_tree *tree = NULL;
	int old_offset = offset;
	if (parent_tree) {
		item = proto_tree_add_item(parent_tree, hf_lsarpc_names, tvb, offset, -1, TRUE);
		tree = proto_item_add_subtree(item, ett_lsarpc_names);
	}
	offset = dissect_ndr_ucarray(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_LookupNames3_names_);
	proto_item_set_len(item, offset-old_offset);
	return offset;
}
static int
lsarpc_dissect_element_lsa_LookupNames_names(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_LookupNames3_names_X, NDR_POINTER_REF, "Pointer to Names", hf_lsarpc_names);
	return offset;
}
static int
lsarpc_dissect_element_lsa_LookupNames2_names(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_LookupNames3_names_X, NDR_POINTER_REF, "Pointer to Names", hf_lsarpc_names);
	return offset;
}
static int
lsarpc_dissect_element_lsa_LookupNames3_names(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_LookupNames3_names_X, NDR_POINTER_REF, "Pointer to Names", hf_lsarpc_names);
	return offset;
}
static int
lsarpc_dissect_element_lsa_LookupNames4_names(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_LookupNames3_names_X, NDR_POINTER_REF, "Pointer to Names", hf_lsarpc_names);
	return offset;
}
static int
lsarpc_dissect_element_lsa_String_string__(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	return offset;
}
static int
lsarpc_dissect_element_lsa_String_string_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	char *data;
	offset = dissect_ndr_cvstring(tvb, offset, pinfo, tree, di, drep, sizeof(guint16), hf_lsarpc_String_name, FALSE, &data);
	proto_item_append_text(tree, ": %s", data);
	return offset;
}
static int
lsarpc_dissect_element_lsa_StringLarge_string__(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	return offset;
}
static int
lsarpc_dissect_element_lsa_StringLarge_string_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	char *data;
	offset = dissect_ndr_cvstring(tvb, offset, pinfo, tree, di, drep, sizeof(guint16), hf_lsarpc_String_name, FALSE, &data);
	proto_item_append_text(tree, ": %s", data);
	return offset;
}
static int
lsarpc_dissect_element_lsa_DomainInfoEfs_efs_blob_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	tvbuff_t *next_tvb;
	gint len, reported_len;
	dissector_handle_t efsblob_handle;

    if(di->conformant_run){
		/*just a run to handle conformant arrays, nothing to dissect */
		return offset;
	}
	offset = dissect_ndr_uint32 (tvb, offset, pinfo, tree, di, drep,
		hf_lsarpc_efs_blob_len, &reported_len);
	len = reported_len;
	if (len > tvb_length_remaining(tvb, offset)) {
		len = tvb_length_remaining(tvb, offset);
	}
	next_tvb = tvb_new_subset(tvb, offset, len, reported_len);
	efsblob_handle = find_dissector("efsblob");
	if (efsblob_handle) {
		call_dissector(efsblob_handle, next_tvb, pinfo, tree);
	}
	offset += reported_len;
	return offset;
}


/* IDL: bitmap { */
/* IDL: 	LSA_POLICY_NOTIFICATION =  0x00001000 , */
/* IDL: 	LSA_POLICY_LOOKUP_NAMES =  0x00000800 , */
/* IDL: 	LSA_POLICY_SERVER_ADMIN =  0x00000400 , */
/* IDL: 	LSA_POLICY_AUDIT_LOG_ADMIN =  0x00000200 , */
/* IDL: 	LSA_POLICY_SET_AUDIT_REQUIREMENTS =  0x00000100 , */
/* IDL: 	LSA_POLICY_SET_DEFAULT_QUOTA_LIMITS =  0x00000080 , */
/* IDL: 	LSA_POLICY_CREATE_PRIVILEGE =  0x00000040 , */
/* IDL: 	LSA_POLICY_CREATE_SECRET =  0x00000020 , */
/* IDL: 	LSA_POLICY_CREATE_ACCOUNT =  0x00000010 , */
/* IDL: 	LSA_POLICY_TRUST_ADMIN =  0x00000008 , */
/* IDL: 	LSA_POLICY_GET_PRIVATE_INFORMATION =  0x00000004 , */
/* IDL: 	LSA_POLICY_VIEW_AUDIT_INFORMATION =  0x00000002 , */
/* IDL: 	LSA_POLICY_VIEW_LOCAL_INFORMATION =  0x00000001 , */
/* IDL: } */


/* IDL: bitmap { */
/* IDL: 	LSA_ACCOUNT_ADJUST_SYSTEM_ACCESS =  0x00000008 , */
/* IDL: 	LSA_ACCOUNT_ADJUST_QUOTAS =  0x00000004 , */
/* IDL: 	LSA_ACCOUNT_ADJUST_PRIVILEGES =  0x00000002 , */
/* IDL: 	LSA_ACCOUNT_VIEW =  0x00000001 , */
/* IDL: } */


/* IDL: bitmap { */
/* IDL: 	LSA_DOMAIN_QUERY_AUTH =  0x00000040 , */
/* IDL: 	LSA_DOMAIN_SET_AUTH =  0x00000020 , */
/* IDL: 	LSA_DOMAIN_SET_POSIX =  0x00000010 , */
/* IDL: 	LSA_DOMAIN_QUERY_POSIX =  0x00000008 , */
/* IDL: 	LSA_DOMAIN_SET_CONTROLLERS =  0x00000004 , */
/* IDL: 	LSA_DOMAIN_QUERY_CONTROLLERS =  0x00000002 , */
/* IDL: 	LSA_DOMAIN_QUERY_DOMAIN_NAME =  0x00000001 , */
/* IDL: } */


/* IDL: bitmap { */
/* IDL: 	LSA_SECRET_QUERY_VALUE =  0x00000002 , */
/* IDL: 	LSA_SECRET_SET_VALUE =  0x00000001 , */
/* IDL: } */


/* IDL: bitmap { */
/* IDL: } */

int
lsarpc_dissect_bitmap_security_secinfo(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_)
{
	proto_item *item = NULL;
	proto_tree *tree = NULL;

	guint32 flags;
	ALIGN_TO_4_BYTES;

	if (parent_tree) {
		item = proto_tree_add_item(parent_tree, hf_index, tvb, offset, 4, DREP_ENC_INTEGER(drep));
		tree = proto_item_add_subtree(item,ett_lsarpc_security_secinfo);
	}

	offset = dissect_ndr_uint32(tvb, offset, pinfo, NULL, di, drep, -1, &flags);
	proto_item_append_text(item, ": ");

	if (!flags)
		proto_item_append_text(item, "(No values set)");

	if (flags) {
		proto_item_append_text(item, "Unknown bitmap value 0x%x", flags);
	}

	return offset;
}


/* IDL: struct { */
/* IDL: 	[value(2*strlen_m(string))] uint16 length; */
/* IDL: 	[value(2*strlen_m(string))] uint16 size; */
/* IDL: 	[unique(1)] [charset(UTF16)] [length_is(length/2)] [size_is(size/2)] uint16 *string; */
/* IDL: } */

static int
lsarpc_dissect_element_lsa_String_length(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint16(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_String_length, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_String_size(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint16(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_String_size, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_String_string(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_embedded_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_String_string_, NDR_POINTER_UNIQUE, "Pointer to String (uint16)",hf_lsarpc_lsa_String_string);

	return offset;
}

int
lsarpc_dissect_struct_lsa_String(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_)
{
	proto_item *item = NULL;
	proto_tree *tree = NULL;
	int old_offset;

	ALIGN_TO_5_BYTES;

	old_offset = offset;

	if (parent_tree) {
		item = proto_tree_add_item(parent_tree, hf_index, tvb, offset, -1, ENC_NA);
		tree = proto_item_add_subtree(item, ett_lsarpc_lsa_String);
	}
	
	offset = lsarpc_dissect_element_lsa_String_length(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_String_size(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_String_string(tvb, offset, pinfo, tree, di, drep);


	proto_item_set_len(item, offset-old_offset);


	if (di->call_data->flags & DCERPC_IS_NDR64) {
		ALIGN_TO_5_BYTES;
	}

	return offset;
}


/* IDL: struct { */
/* IDL: 	[value(2*strlen_m(string))] uint16 length; */
/* IDL: 	[value(2*strlen_m_term(string))] uint16 size; */
/* IDL: 	[unique(1)] [charset(UTF16)] [length_is(length/2)] [size_is(size/2)] uint16 *string; */
/* IDL: } */

static int
lsarpc_dissect_element_lsa_StringLarge_length(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint16(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_StringLarge_length, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_StringLarge_size(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint16(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_StringLarge_size, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_StringLarge_string(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_embedded_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_StringLarge_string_, NDR_POINTER_UNIQUE, "Pointer to String (uint16)",hf_lsarpc_lsa_StringLarge_string);

	return offset;
}

int
lsarpc_dissect_struct_lsa_StringLarge(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_)
{
	proto_item *item = NULL;
	proto_tree *tree = NULL;
	int old_offset;

	ALIGN_TO_5_BYTES;

	old_offset = offset;

	if (parent_tree) {
		item = proto_tree_add_item(parent_tree, hf_index, tvb, offset, -1, ENC_NA);
		tree = proto_item_add_subtree(item, ett_lsarpc_lsa_StringLarge);
	}
	
	offset = lsarpc_dissect_element_lsa_StringLarge_length(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_StringLarge_size(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_StringLarge_string(tvb, offset, pinfo, tree, di, drep);


	proto_item_set_len(item, offset-old_offset);


	if (di->call_data->flags & DCERPC_IS_NDR64) {
		ALIGN_TO_5_BYTES;
	}

	return offset;
}


/* IDL: struct { */
/* IDL: 	uint32 count; */
/* IDL: 	[unique(1)] [size_is(count)] lsa_String *names; */
/* IDL: } */

static int
lsarpc_dissect_element_lsa_Strings_count(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_Strings_count, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_Strings_names(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_embedded_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_Strings_names_, NDR_POINTER_UNIQUE, "Pointer to Names (lsa_String)",hf_lsarpc_lsa_Strings_names);

	return offset;
}

static int
lsarpc_dissect_element_lsa_Strings_names_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_ucarray(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_Strings_names__);

	return offset;
}

static int
lsarpc_dissect_element_lsa_Strings_names__(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_String(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_Strings_names,0);

	return offset;
}

int
lsarpc_dissect_struct_lsa_Strings(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_)
{
	proto_item *item = NULL;
	proto_tree *tree = NULL;
	int old_offset;

	ALIGN_TO_5_BYTES;

	old_offset = offset;

	if (parent_tree) {
		item = proto_tree_add_item(parent_tree, hf_index, tvb, offset, -1, ENC_NA);
		tree = proto_item_add_subtree(item, ett_lsarpc_lsa_Strings);
	}
	
	offset = lsarpc_dissect_element_lsa_Strings_count(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_Strings_names(tvb, offset, pinfo, tree, di, drep);


	proto_item_set_len(item, offset-old_offset);


	if (di->call_data->flags & DCERPC_IS_NDR64) {
		ALIGN_TO_5_BYTES;
	}

	return offset;
}


/* IDL: struct { */
/* IDL: 	[value(strlen_m(string))] uint16 length; */
/* IDL: 	[value(strlen_m(string))] uint16 size; */
/* IDL: 	[unique(1)] [charset(DOS)] [length_is(length)] [size_is(size)] uint8 *string; */
/* IDL: } */

static int
lsarpc_dissect_element_lsa_AsciiString_length(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint16(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_AsciiString_length, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_AsciiString_size(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint16(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_AsciiString_size, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_AsciiString_string(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_embedded_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_AsciiString_string_, NDR_POINTER_UNIQUE, "Pointer to String (uint8)",hf_lsarpc_lsa_AsciiString_string);

	return offset;
}

static int
lsarpc_dissect_element_lsa_AsciiString_string_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_ucvarray(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_AsciiString_string__);

	return offset;
}

static int
lsarpc_dissect_element_lsa_AsciiString_string__(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint8(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_AsciiString_string, 0);

	return offset;
}

int
lsarpc_dissect_struct_lsa_AsciiString(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_)
{
	proto_item *item = NULL;
	proto_tree *tree = NULL;
	int old_offset;

	ALIGN_TO_5_BYTES;

	old_offset = offset;

	if (parent_tree) {
		item = proto_tree_add_item(parent_tree, hf_index, tvb, offset, -1, ENC_NA);
		tree = proto_item_add_subtree(item, ett_lsarpc_lsa_AsciiString);
	}
	
	offset = lsarpc_dissect_element_lsa_AsciiString_length(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_AsciiString_size(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_AsciiString_string(tvb, offset, pinfo, tree, di, drep);


	proto_item_set_len(item, offset-old_offset);


	if (di->call_data->flags & DCERPC_IS_NDR64) {
		ALIGN_TO_5_BYTES;
	}

	return offset;
}


/* IDL: struct { */
/* IDL: 	[value(strlen_m(string))] uint16 length; */
/* IDL: 	[value(strlen_m_term(string))] uint16 size; */
/* IDL: 	[unique(1)] [charset(DOS)] [length_is(length)] [size_is(size)] uint8 *string; */
/* IDL: } */

static int
lsarpc_dissect_element_lsa_AsciiStringLarge_length(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint16(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_AsciiStringLarge_length, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_AsciiStringLarge_size(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint16(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_AsciiStringLarge_size, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_AsciiStringLarge_string(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_embedded_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_AsciiStringLarge_string_, NDR_POINTER_UNIQUE, "Pointer to String (uint8)",hf_lsarpc_lsa_AsciiStringLarge_string);

	return offset;
}

static int
lsarpc_dissect_element_lsa_AsciiStringLarge_string_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_ucvarray(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_AsciiStringLarge_string__);

	return offset;
}

static int
lsarpc_dissect_element_lsa_AsciiStringLarge_string__(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint8(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_AsciiStringLarge_string, 0);

	return offset;
}

int
lsarpc_dissect_struct_lsa_AsciiStringLarge(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_)
{
	proto_item *item = NULL;
	proto_tree *tree = NULL;
	int old_offset;

	ALIGN_TO_5_BYTES;

	old_offset = offset;

	if (parent_tree) {
		item = proto_tree_add_item(parent_tree, hf_index, tvb, offset, -1, ENC_NA);
		tree = proto_item_add_subtree(item, ett_lsarpc_lsa_AsciiStringLarge);
	}
	
	offset = lsarpc_dissect_element_lsa_AsciiStringLarge_length(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_AsciiStringLarge_size(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_AsciiStringLarge_string(tvb, offset, pinfo, tree, di, drep);


	proto_item_set_len(item, offset-old_offset);


	if (di->call_data->flags & DCERPC_IS_NDR64) {
		ALIGN_TO_5_BYTES;
	}

	return offset;
}


/* IDL: struct { */
/* IDL: 	uint32 low; */
/* IDL: 	uint32 high; */
/* IDL: } */

static int
lsarpc_dissect_element_lsa_LUID_low(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_LUID_low, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LUID_high(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_LUID_high, 0);

	return offset;
}

int
lsarpc_dissect_struct_lsa_LUID(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_)
{
	proto_item *item = NULL;
	proto_tree *tree = NULL;

	int old_offset;

	ALIGN_TO_4_BYTES;

	old_offset = offset;

	if (parent_tree) {
		item = proto_tree_add_item(parent_tree, hf_index, tvb, offset, -1, ENC_NA);
		tree = proto_item_add_subtree(item, ett_lsarpc_lsa_LUID);
	}
	
	offset = lsarpc_dissect_element_lsa_LUID_low(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_LUID_high(tvb, offset, pinfo, tree, di, drep);


	proto_item_set_len(item, offset-old_offset);


	if (di->call_data->flags & DCERPC_IS_NDR64) {
		ALIGN_TO_4_BYTES;
	}

	return offset;
}


/* IDL: struct { */
/* IDL: 	lsa_StringLarge name; */
/* IDL: 	lsa_LUID luid; */
/* IDL: } */

static int
lsarpc_dissect_element_lsa_PrivEntry_name(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_StringLarge(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_PrivEntry_name,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_PrivEntry_luid(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_LUID(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_PrivEntry_luid,0);

	return offset;
}

int
lsarpc_dissect_struct_lsa_PrivEntry(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_)
{
	proto_item *item = NULL;
	proto_tree *tree = NULL;

	int old_offset;

	ALIGN_TO_5_BYTES;

	old_offset = offset;

	if (parent_tree) {
		item = proto_tree_add_item(parent_tree, hf_index, tvb, offset, -1, ENC_NA);
		tree = proto_item_add_subtree(item, ett_lsarpc_lsa_PrivEntry);
	}
	
	offset = lsarpc_dissect_element_lsa_PrivEntry_name(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_PrivEntry_luid(tvb, offset, pinfo, tree, di, drep);


	proto_item_set_len(item, offset-old_offset);


	if (di->call_data->flags & DCERPC_IS_NDR64) {
		ALIGN_TO_5_BYTES;
	}

	return offset;
}


/* IDL: struct { */
/* IDL: 	uint32 count; */
/* IDL: 	[unique(1)] [size_is(count)] lsa_PrivEntry *privs; */
/* IDL: } */

static int
lsarpc_dissect_element_lsa_PrivArray_count(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_PrivArray_count, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_PrivArray_privs(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_embedded_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_PrivArray_privs_, NDR_POINTER_UNIQUE, "Pointer to Privs (lsa_PrivEntry)",hf_lsarpc_lsa_PrivArray_privs);

	return offset;
}

static int
lsarpc_dissect_element_lsa_PrivArray_privs_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_ucarray(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_PrivArray_privs__);

	return offset;
}

static int
lsarpc_dissect_element_lsa_PrivArray_privs__(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_PrivEntry(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_PrivArray_privs,0);

	return offset;
}

int
lsarpc_dissect_struct_lsa_PrivArray(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_)
{
	proto_item *item = NULL;
	proto_tree *tree = NULL;

	int old_offset;

	ALIGN_TO_5_BYTES;

	old_offset = offset;

	if (parent_tree) {
		item = proto_tree_add_item(parent_tree, hf_index, tvb, offset, -1, ENC_NA);
		tree = proto_item_add_subtree(item, ett_lsarpc_lsa_PrivArray);
	}
	
	offset = lsarpc_dissect_element_lsa_PrivArray_count(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_PrivArray_privs(tvb, offset, pinfo, tree, di, drep);


	proto_item_set_len(item, offset-old_offset);


	if (di->call_data->flags & DCERPC_IS_NDR64) {
		ALIGN_TO_5_BYTES;
	}

	return offset;
}


/* IDL: enum { */
/* IDL: 	LSA_SECURITY_ANONYMOUS=0, */
/* IDL: 	LSA_SECURITY_IDENTIFICATION=1, */
/* IDL: 	LSA_SECURITY_IMPERSONATION=2, */
/* IDL: 	LSA_SECURITY_DELEGATION=3, */
/* IDL: } */

int
lsarpc_dissect_enum_lsa_SecurityImpersonationLevel(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 *param _U_)
{
	guint1632 parameter=0;
	if(param){
		parameter=(guint1632)*param;
	}
	offset = dissect_ndr_uint1632(tvb, offset, pinfo, tree, di, drep, hf_index, &parameter);
	if(param){
		*param=(guint32)parameter;
	}
	return offset;
}


/* IDL: struct { */
/* IDL: 	uint32 len; */
/* IDL: 	lsa_SecurityImpersonationLevel impersonation_level; */
/* IDL: 	uint8 context_mode; */
/* IDL: 	uint8 effective_only; */
/* IDL: } */

static int
lsarpc_dissect_element_lsa_QosInfo_len(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_QosInfo_len, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_QosInfo_impersonation_level(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_enum_lsa_SecurityImpersonationLevel(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_QosInfo_impersonation_level, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_QosInfo_context_mode(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint8(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_QosInfo_context_mode, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_QosInfo_effective_only(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint8(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_QosInfo_effective_only, 0);

	return offset;
}

int
lsarpc_dissect_struct_lsa_QosInfo(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_)
{
	proto_item *item = NULL;
	proto_tree *tree = NULL;

	int old_offset;

	ALIGN_TO_4_BYTES;

	old_offset = offset;

	if (parent_tree) {
		item = proto_tree_add_item(parent_tree, hf_index, tvb, offset, -1, ENC_NA);
		tree = proto_item_add_subtree(item, ett_lsarpc_lsa_QosInfo);
	}
	
	offset = lsarpc_dissect_element_lsa_QosInfo_len(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_QosInfo_impersonation_level(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_QosInfo_context_mode(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_QosInfo_effective_only(tvb, offset, pinfo, tree, di, drep);


	proto_item_set_len(item, offset-old_offset);


	if (di->call_data->flags & DCERPC_IS_NDR64) {
		ALIGN_TO_4_BYTES;
	}

	return offset;
}


/* IDL: struct { */
/* IDL: 	uint32 len; */
/* IDL: 	[unique(1)] uint8 *root_dir; */
/* IDL: 	[unique(1)] [charset(UTF16)] uint16 *object_name; */
/* IDL: 	uint32 attributes; */
/* IDL: 	[unique(1)] security_descriptor *sec_desc; */
/* IDL: 	[unique(1)] lsa_QosInfo *sec_qos; */
/* IDL: } */

static int
lsarpc_dissect_element_lsa_ObjectAttribute_len(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_ObjectAttribute_len, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_ObjectAttribute_root_dir(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_embedded_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_ObjectAttribute_root_dir_, NDR_POINTER_UNIQUE, "Pointer to Root Dir (uint8)",hf_lsarpc_lsa_ObjectAttribute_root_dir);

	return offset;
}

static int
lsarpc_dissect_element_lsa_ObjectAttribute_root_dir_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint8(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_ObjectAttribute_root_dir, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_ObjectAttribute_object_name(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_embedded_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_ObjectAttribute_object_name_, NDR_POINTER_UNIQUE, "Pointer to Object Name (uint16)",hf_lsarpc_lsa_ObjectAttribute_object_name);

	return offset;
}

static int
lsarpc_dissect_element_lsa_ObjectAttribute_object_name_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	char *data;

	offset = dissect_ndr_cvstring(tvb, offset, pinfo, tree, di, drep, sizeof(guint16), hf_lsarpc_lsa_ObjectAttribute_object_name, FALSE, &data);
	proto_item_append_text(tree, ": %s", data);

	return offset;
}

static int
lsarpc_dissect_element_lsa_ObjectAttribute_attributes(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_ObjectAttribute_attributes, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_ObjectAttribute_sec_desc(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_embedded_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_ObjectAttribute_sec_desc_, NDR_POINTER_UNIQUE, "Pointer to Sec Desc (security_descriptor)",hf_lsarpc_lsa_ObjectAttribute_sec_desc);

	return offset;
}

static int
lsarpc_dissect_element_lsa_ObjectAttribute_sec_desc_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_security_descriptor(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_ObjectAttribute_sec_desc,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_ObjectAttribute_sec_qos(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_embedded_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_ObjectAttribute_sec_qos_, NDR_POINTER_UNIQUE, "Pointer to Sec Qos (lsa_QosInfo)",hf_lsarpc_lsa_ObjectAttribute_sec_qos);

	return offset;
}

static int
lsarpc_dissect_element_lsa_ObjectAttribute_sec_qos_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_QosInfo(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_ObjectAttribute_sec_qos,0);

	return offset;
}

int
lsarpc_dissect_struct_lsa_ObjectAttribute(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_)
{
	proto_item *item = NULL;
	proto_tree *tree = NULL;

	int old_offset;

	ALIGN_TO_5_BYTES;

	old_offset = offset;

	if (parent_tree) {
		item = proto_tree_add_item(parent_tree, hf_index, tvb, offset, -1, ENC_NA);
		tree = proto_item_add_subtree(item, ett_lsarpc_lsa_ObjectAttribute);
	}
	
	offset = lsarpc_dissect_element_lsa_ObjectAttribute_len(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_ObjectAttribute_root_dir(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_ObjectAttribute_object_name(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_ObjectAttribute_attributes(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_ObjectAttribute_sec_desc(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_ObjectAttribute_sec_qos(tvb, offset, pinfo, tree, di, drep);


	proto_item_set_len(item, offset-old_offset);


	if (di->call_data->flags & DCERPC_IS_NDR64) {
		ALIGN_TO_5_BYTES;
	}

	return offset;
}


/* IDL: struct { */
/* IDL: 	uint32 percent_full; */
/* IDL: 	uint32 log_size; */
/* IDL: 	NTTIME retention_time; */
/* IDL: 	uint8 shutdown_in_progress; */
/* IDL: 	NTTIME time_to_shutdown; */
/* IDL: 	uint32 next_audit_record; */
/* IDL: 	uint32 unknown; */
/* IDL: } */

static int
lsarpc_dissect_element_lsa_AuditLogInfo_percent_full(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_AuditLogInfo_percent_full, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_AuditLogInfo_log_size(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_AuditLogInfo_log_size, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_AuditLogInfo_retention_time(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_nt_NTTIME(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_AuditLogInfo_retention_time);

	return offset;
}

static int
lsarpc_dissect_element_lsa_AuditLogInfo_shutdown_in_progress(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint8(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_AuditLogInfo_shutdown_in_progress, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_AuditLogInfo_time_to_shutdown(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_nt_NTTIME(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_AuditLogInfo_time_to_shutdown);

	return offset;
}

static int
lsarpc_dissect_element_lsa_AuditLogInfo_next_audit_record(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_AuditLogInfo_next_audit_record, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_AuditLogInfo_unknown(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_AuditLogInfo_unknown, 0);

	return offset;
}

int
lsarpc_dissect_struct_lsa_AuditLogInfo(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_)
{
	proto_item *item = NULL;
	proto_tree *tree = NULL;

	int old_offset;

	ALIGN_TO_4_BYTES;

	old_offset = offset;

	if (parent_tree) {
		item = proto_tree_add_item(parent_tree, hf_index, tvb, offset, -1, ENC_NA);
		tree = proto_item_add_subtree(item, ett_lsarpc_lsa_AuditLogInfo);
	}
	
	offset = lsarpc_dissect_element_lsa_AuditLogInfo_percent_full(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_AuditLogInfo_log_size(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_AuditLogInfo_retention_time(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_AuditLogInfo_shutdown_in_progress(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_AuditLogInfo_time_to_shutdown(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_AuditLogInfo_next_audit_record(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_AuditLogInfo_unknown(tvb, offset, pinfo, tree, di, drep);


	proto_item_set_len(item, offset-old_offset);


	if (di->call_data->flags & DCERPC_IS_NDR64) {
		ALIGN_TO_4_BYTES;
	}

	return offset;
}


/* IDL: enum { */
/* IDL: 	LSA_AUDIT_POLICY_NONE=0, */
/* IDL: 	LSA_AUDIT_POLICY_SUCCESS=1, */
/* IDL: 	LSA_AUDIT_POLICY_FAILURE=2, */
/* IDL: 	LSA_AUDIT_POLICY_ALL=(LSA_AUDIT_POLICY_SUCCESS|LSA_AUDIT_POLICY_FAILURE), */
/* IDL: 	LSA_AUDIT_POLICY_CLEAR=4, */
/* IDL: } */

int
lsarpc_dissect_enum_lsa_PolicyAuditPolicy(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 *param _U_)
{
	guint32 parameter=0;
	if(param){
		parameter=(guint32)*param;
	}
	offset = dissect_ndr_uint32(tvb, offset, pinfo, tree, di, drep, hf_index, &parameter);
	if(param){
		*param=(guint32)parameter;
	}
	return offset;
}


/* IDL: enum { */
/* IDL: 	LSA_AUDIT_CATEGORY_SYSTEM=0, */
/* IDL: 	LSA_AUDIT_CATEGORY_LOGON=1, */
/* IDL: 	LSA_AUDIT_CATEGORY_FILE_AND_OBJECT_ACCESS=2, */
/* IDL: 	LSA_AUDIT_CATEGORY_USE_OF_USER_RIGHTS=3, */
/* IDL: 	LSA_AUDIT_CATEGORY_PROCCESS_TRACKING=4, */
/* IDL: 	LSA_AUDIT_CATEGORY_SECURITY_POLICY_CHANGES=5, */
/* IDL: 	LSA_AUDIT_CATEGORY_ACCOUNT_MANAGEMENT=6, */
/* IDL: 	LSA_AUDIT_CATEGORY_DIRECTORY_SERVICE_ACCESS=7, */
/* IDL: 	LSA_AUDIT_CATEGORY_ACCOUNT_LOGON=8, */
/* IDL: } */

int
lsarpc_dissect_enum_lsa_PolicyAuditEventType(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 *param _U_)
{
	guint1632 parameter=0;
	if(param){
		parameter=(guint1632)*param;
	}
	offset = dissect_ndr_uint1632(tvb, offset, pinfo, tree, di, drep, hf_index, &parameter);
	if(param){
		*param=(guint32)parameter;
	}
	return offset;
}


/* IDL: struct { */
/* IDL: 	uint32 auditing_mode; */
/* IDL: 	[unique(1)] [size_is(count)] lsa_PolicyAuditPolicy *settings; */
/* IDL: 	uint32 count; */
/* IDL: } */

static int
lsarpc_dissect_element_lsa_AuditEventsInfo_auditing_mode(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_AuditEventsInfo_auditing_mode, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_AuditEventsInfo_settings(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_embedded_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_AuditEventsInfo_settings_, NDR_POINTER_UNIQUE, "Pointer to Settings (lsa_PolicyAuditPolicy)",hf_lsarpc_lsa_AuditEventsInfo_settings);

	return offset;
}

static int
lsarpc_dissect_element_lsa_AuditEventsInfo_settings_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_ucarray(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_AuditEventsInfo_settings__);

	return offset;
}

static int
lsarpc_dissect_element_lsa_AuditEventsInfo_settings__(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_enum_lsa_PolicyAuditPolicy(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_AuditEventsInfo_settings, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_AuditEventsInfo_count(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_AuditEventsInfo_count, 0);

	return offset;
}

int
lsarpc_dissect_struct_lsa_AuditEventsInfo(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_)
{
	proto_item *item = NULL;
	proto_tree *tree = NULL;

	int old_offset;

	ALIGN_TO_5_BYTES;

	old_offset = offset;

	if (parent_tree) {
		item = proto_tree_add_item(parent_tree, hf_index, tvb, offset, -1, ENC_NA);
		tree = proto_item_add_subtree(item, ett_lsarpc_lsa_AuditEventsInfo);
	}
	
	offset = lsarpc_dissect_element_lsa_AuditEventsInfo_auditing_mode(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_AuditEventsInfo_settings(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_AuditEventsInfo_count(tvb, offset, pinfo, tree, di, drep);


	proto_item_set_len(item, offset-old_offset);


	if (di->call_data->flags & DCERPC_IS_NDR64) {
		ALIGN_TO_5_BYTES;
	}

	return offset;
}


/* IDL: struct { */
/* IDL: 	lsa_StringLarge name; */
/* IDL: 	[unique(1)] dom_sid2 *sid; */
/* IDL: } */

static int
lsarpc_dissect_element_lsa_DomainInfo_name(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_StringLarge(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_DomainInfo_name,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_DomainInfo_sid(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_embedded_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_DomainInfo_sid_, NDR_POINTER_UNIQUE, "Pointer to Sid (dom_sid2)",hf_lsarpc_lsa_DomainInfo_sid);

	return offset;
}

static int
lsarpc_dissect_element_lsa_DomainInfo_sid_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_dom_sid2(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_DomainInfo_sid,0);

	return offset;
}

int
lsarpc_dissect_struct_lsa_DomainInfo(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_)
{
	proto_item *item = NULL;
	proto_tree *tree = NULL;

	int old_offset;

	ALIGN_TO_5_BYTES;

	old_offset = offset;

	if (parent_tree) {
		item = proto_tree_add_item(parent_tree, hf_index, tvb, offset, -1, ENC_NA);
		tree = proto_item_add_subtree(item, ett_lsarpc_lsa_DomainInfo);
	}
	
	offset = lsarpc_dissect_element_lsa_DomainInfo_name(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_DomainInfo_sid(tvb, offset, pinfo, tree, di, drep);


	proto_item_set_len(item, offset-old_offset);


	if (di->call_data->flags & DCERPC_IS_NDR64) {
		ALIGN_TO_5_BYTES;
	}

	return offset;
}


/* IDL: struct { */
/* IDL: 	lsa_String name; */
/* IDL: } */

static int
lsarpc_dissect_element_lsa_PDAccountInfo_name(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_String(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_PDAccountInfo_name,0);

	return offset;
}

int
lsarpc_dissect_struct_lsa_PDAccountInfo(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_)
{
	proto_item *item = NULL;
	proto_tree *tree = NULL;

	int old_offset;

	ALIGN_TO_5_BYTES;

	old_offset = offset;

	if (parent_tree) {
		item = proto_tree_add_item(parent_tree, hf_index, tvb, offset, -1, ENC_NA);
		tree = proto_item_add_subtree(item, ett_lsarpc_lsa_PDAccountInfo);
	}
	
	offset = lsarpc_dissect_element_lsa_PDAccountInfo_name(tvb, offset, pinfo, tree, di, drep);


	proto_item_set_len(item, offset-old_offset);


	if (di->call_data->flags & DCERPC_IS_NDR64) {
		ALIGN_TO_5_BYTES;
	}

	return offset;
}


/* IDL: enum { */
/* IDL: 	LSA_POLICY_ROLE_BACKUP=2, */
/* IDL: 	LSA_POLICY_ROLE_PRIMARY=3, */
/* IDL: } */

int
lsarpc_dissect_enum_lsa_PolicyServerRole(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 *param _U_)
{
	guint1632 parameter=0;
	if(param){
		parameter=(guint1632)*param;
	}
	offset = dissect_ndr_uint1632(tvb, offset, pinfo, tree, di, drep, hf_index, &parameter);
	if(param){
		*param=(guint32)parameter;
	}
	return offset;
}


/* IDL: struct { */
/* IDL: 	lsa_PolicyServerRole role; */
/* IDL: } */

static int
lsarpc_dissect_element_lsa_ServerRole_role(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_enum_lsa_PolicyServerRole(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_ServerRole_role, 0);

	return offset;
}

int
lsarpc_dissect_struct_lsa_ServerRole(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_)
{
	proto_item *item = NULL;
	proto_tree *tree = NULL;

	int old_offset;

	ALIGN_TO_3_BYTES;

	old_offset = offset;

	if (parent_tree) {
		item = proto_tree_add_item(parent_tree, hf_index, tvb, offset, -1, ENC_NA);
		tree = proto_item_add_subtree(item, ett_lsarpc_lsa_ServerRole);
	}
	
	offset = lsarpc_dissect_element_lsa_ServerRole_role(tvb, offset, pinfo, tree, di, drep);


	proto_item_set_len(item, offset-old_offset);


	if (di->call_data->flags & DCERPC_IS_NDR64) {
		ALIGN_TO_3_BYTES;
	}

	return offset;
}


/* IDL: struct { */
/* IDL: 	lsa_String source; */
/* IDL: 	lsa_String account; */
/* IDL: } */

static int
lsarpc_dissect_element_lsa_ReplicaSourceInfo_source(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_String(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_ReplicaSourceInfo_source,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_ReplicaSourceInfo_account(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_String(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_ReplicaSourceInfo_account,0);

	return offset;
}

int
lsarpc_dissect_struct_lsa_ReplicaSourceInfo(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_)
{
	proto_item *item = NULL;
	proto_tree *tree = NULL;

	int old_offset;

	ALIGN_TO_5_BYTES;

	old_offset = offset;

	if (parent_tree) {
		item = proto_tree_add_item(parent_tree, hf_index, tvb, offset, -1, ENC_NA);
		tree = proto_item_add_subtree(item, ett_lsarpc_lsa_ReplicaSourceInfo);
	}
	
	offset = lsarpc_dissect_element_lsa_ReplicaSourceInfo_source(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_ReplicaSourceInfo_account(tvb, offset, pinfo, tree, di, drep);


	proto_item_set_len(item, offset-old_offset);


	if (di->call_data->flags & DCERPC_IS_NDR64) {
		ALIGN_TO_5_BYTES;
	}

	return offset;
}


/* IDL: struct { */
/* IDL: 	uint32 paged_pool; */
/* IDL: 	uint32 non_paged_pool; */
/* IDL: 	uint32 min_wss; */
/* IDL: 	uint32 max_wss; */
/* IDL: 	uint32 pagefile; */
/* IDL: 	hyper unknown; */
/* IDL: } */

static int
lsarpc_dissect_element_lsa_DefaultQuotaInfo_paged_pool(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_DefaultQuotaInfo_paged_pool, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_DefaultQuotaInfo_non_paged_pool(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_DefaultQuotaInfo_non_paged_pool, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_DefaultQuotaInfo_min_wss(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_DefaultQuotaInfo_min_wss, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_DefaultQuotaInfo_max_wss(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_DefaultQuotaInfo_max_wss, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_DefaultQuotaInfo_pagefile(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_DefaultQuotaInfo_pagefile, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_DefaultQuotaInfo_unknown(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset=cnf_dissect_hyper(tvb, offset, pinfo, tree, di, drep, 0, hf_lsarpc_lsa_DefaultQuotaInfo_unknown);

	return offset;
}

int
lsarpc_dissect_struct_lsa_DefaultQuotaInfo(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_)
{
	proto_item *item = NULL;
	proto_tree *tree = NULL;

	int old_offset;

	ALIGN_TO_8_BYTES;

	old_offset = offset;

	if (parent_tree) {
		item = proto_tree_add_item(parent_tree, hf_index, tvb, offset, -1, ENC_NA);
		tree = proto_item_add_subtree(item, ett_lsarpc_lsa_DefaultQuotaInfo);
	}
	
	offset = lsarpc_dissect_element_lsa_DefaultQuotaInfo_paged_pool(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_DefaultQuotaInfo_non_paged_pool(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_DefaultQuotaInfo_min_wss(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_DefaultQuotaInfo_max_wss(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_DefaultQuotaInfo_pagefile(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_DefaultQuotaInfo_unknown(tvb, offset, pinfo, tree, di, drep);


	proto_item_set_len(item, offset-old_offset);


	if (di->call_data->flags & DCERPC_IS_NDR64) {
		ALIGN_TO_8_BYTES;
	}

	return offset;
}


/* IDL: struct { */
/* IDL: 	hyper modified_id; */
/* IDL: 	NTTIME db_create_time; */
/* IDL: } */

static int
lsarpc_dissect_element_lsa_ModificationInfo_modified_id(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset=cnf_dissect_hyper(tvb, offset, pinfo, tree, di, drep, 0, hf_lsarpc_lsa_ModificationInfo_modified_id);

	return offset;
}

static int
lsarpc_dissect_element_lsa_ModificationInfo_db_create_time(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_nt_NTTIME(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_ModificationInfo_db_create_time);

	return offset;
}

int
lsarpc_dissect_struct_lsa_ModificationInfo(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_)
{
	proto_item *item = NULL;
	proto_tree *tree = NULL;

	int old_offset;

	ALIGN_TO_8_BYTES;

	old_offset = offset;

	if (parent_tree) {
		item = proto_tree_add_item(parent_tree, hf_index, tvb, offset, -1, ENC_NA);
		tree = proto_item_add_subtree(item, ett_lsarpc_lsa_ModificationInfo);
	}
	
	offset = lsarpc_dissect_element_lsa_ModificationInfo_modified_id(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_ModificationInfo_db_create_time(tvb, offset, pinfo, tree, di, drep);


	proto_item_set_len(item, offset-old_offset);


	if (di->call_data->flags & DCERPC_IS_NDR64) {
		ALIGN_TO_8_BYTES;
	}

	return offset;
}


/* IDL: struct { */
/* IDL: 	uint8 shutdown_on_full; */
/* IDL: } */

static int
lsarpc_dissect_element_lsa_AuditFullSetInfo_shutdown_on_full(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint8(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_AuditFullSetInfo_shutdown_on_full, 0);

	return offset;
}

int
lsarpc_dissect_struct_lsa_AuditFullSetInfo(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_)
{
	proto_item *item = NULL;
	proto_tree *tree = NULL;
	int old_offset;


	old_offset = offset;

	if (parent_tree) {
		item = proto_tree_add_item(parent_tree, hf_index, tvb, offset, -1, ENC_NA);
		tree = proto_item_add_subtree(item, ett_lsarpc_lsa_AuditFullSetInfo);
	}
	
	offset = lsarpc_dissect_element_lsa_AuditFullSetInfo_shutdown_on_full(tvb, offset, pinfo, tree, di, drep);


	proto_item_set_len(item, offset-old_offset);


	return offset;
}


/* IDL: struct { */
/* IDL: 	uint16 unknown; */
/* IDL: 	uint8 shutdown_on_full; */
/* IDL: 	uint8 log_is_full; */
/* IDL: } */

static int
lsarpc_dissect_element_lsa_AuditFullQueryInfo_unknown(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint16(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_AuditFullQueryInfo_unknown, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_AuditFullQueryInfo_shutdown_on_full(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint8(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_AuditFullQueryInfo_shutdown_on_full, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_AuditFullQueryInfo_log_is_full(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint8(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_AuditFullQueryInfo_log_is_full, 0);

	return offset;
}

int
lsarpc_dissect_struct_lsa_AuditFullQueryInfo(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_)
{
	proto_item *item = NULL;
	proto_tree *tree = NULL;

	int old_offset;

	ALIGN_TO_2_BYTES;

	old_offset = offset;

	if (parent_tree) {
		item = proto_tree_add_item(parent_tree, hf_index, tvb, offset, -1, ENC_NA);
		tree = proto_item_add_subtree(item, ett_lsarpc_lsa_AuditFullQueryInfo);
	}
	
	offset = lsarpc_dissect_element_lsa_AuditFullQueryInfo_unknown(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_AuditFullQueryInfo_shutdown_on_full(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_AuditFullQueryInfo_log_is_full(tvb, offset, pinfo, tree, di, drep);


	proto_item_set_len(item, offset-old_offset);


	if (di->call_data->flags & DCERPC_IS_NDR64) {
		ALIGN_TO_2_BYTES;
	}

	return offset;
}


/* IDL: struct { */
/* IDL: 	lsa_StringLarge name; */
/* IDL: 	lsa_StringLarge dns_domain; */
/* IDL: 	lsa_StringLarge dns_forest; */
/* IDL: 	GUID domain_guid; */
/* IDL: 	[unique(1)] dom_sid2 *sid; */
/* IDL: } */

static int
lsarpc_dissect_element_lsa_DnsDomainInfo_name(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_StringLarge(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_DnsDomainInfo_name,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_DnsDomainInfo_dns_domain(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_StringLarge(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_DnsDomainInfo_dns_domain,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_DnsDomainInfo_dns_forest(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_StringLarge(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_DnsDomainInfo_dns_forest,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_DnsDomainInfo_domain_guid(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_uuid_t(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_DnsDomainInfo_domain_guid, NULL);

	return offset;
}

static int
lsarpc_dissect_element_lsa_DnsDomainInfo_sid(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_embedded_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_DnsDomainInfo_sid_, NDR_POINTER_UNIQUE, "Pointer to Sid (dom_sid2)",hf_lsarpc_lsa_DnsDomainInfo_sid);

	return offset;
}

static int
lsarpc_dissect_element_lsa_DnsDomainInfo_sid_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_dom_sid2(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_DnsDomainInfo_sid,0);

	return offset;
}

int
lsarpc_dissect_struct_lsa_DnsDomainInfo(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_)
{
	proto_item *item = NULL;
	proto_tree *tree = NULL;

	int old_offset;

	ALIGN_TO_5_BYTES;

	old_offset = offset;

	if (parent_tree) {
		item = proto_tree_add_item(parent_tree, hf_index, tvb, offset, -1, ENC_NA);
		tree = proto_item_add_subtree(item, ett_lsarpc_lsa_DnsDomainInfo);
	}
	
	offset = lsarpc_dissect_element_lsa_DnsDomainInfo_name(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_DnsDomainInfo_dns_domain(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_DnsDomainInfo_dns_forest(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_DnsDomainInfo_domain_guid(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_DnsDomainInfo_sid(tvb, offset, pinfo, tree, di, drep);


	proto_item_set_len(item, offset-old_offset);


	if (di->call_data->flags & DCERPC_IS_NDR64) {
		ALIGN_TO_5_BYTES;
	}

	return offset;
}


/* IDL: enum { */
/* IDL: 	LSA_POLICY_INFO_AUDIT_LOG=1, */
/* IDL: 	LSA_POLICY_INFO_AUDIT_EVENTS=2, */
/* IDL: 	LSA_POLICY_INFO_DOMAIN=3, */
/* IDL: 	LSA_POLICY_INFO_PD=4, */
/* IDL: 	LSA_POLICY_INFO_ACCOUNT_DOMAIN=5, */
/* IDL: 	LSA_POLICY_INFO_ROLE=6, */
/* IDL: 	LSA_POLICY_INFO_REPLICA=7, */
/* IDL: 	LSA_POLICY_INFO_QUOTA=8, */
/* IDL: 	LSA_POLICY_INFO_DB=9, */
/* IDL: 	LSA_POLICY_INFO_AUDIT_FULL_SET=10, */
/* IDL: 	LSA_POLICY_INFO_AUDIT_FULL_QUERY=11, */
/* IDL: 	LSA_POLICY_INFO_DNS=12, */
/* IDL: 	LSA_POLICY_INFO_DNS_INT=13, */
/* IDL: 	LSA_POLICY_INFO_LOCAL_ACCOUNT_DOMAIN=14, */
/* IDL: } */

int
lsarpc_dissect_enum_lsa_PolicyInfo(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 *param _U_)
{
	guint1632 parameter=0;
	if(param){
		parameter=(guint1632)*param;
	}
	offset = dissect_ndr_uint1632(tvb, offset, pinfo, tree, di, drep, hf_index, &parameter);
	if(param){
		*param=(guint32)parameter;
	}
	return offset;
}


/* IDL: [switch_type(uint16)] union { */
/* IDL: [case(LSA_POLICY_INFO_AUDIT_LOG)] [case(LSA_POLICY_INFO_AUDIT_LOG)] lsa_AuditLogInfo audit_log; */
/* IDL: [case(LSA_POLICY_INFO_AUDIT_EVENTS)] [case(LSA_POLICY_INFO_AUDIT_EVENTS)] lsa_AuditEventsInfo audit_events; */
/* IDL: [case(LSA_POLICY_INFO_DOMAIN)] [case(LSA_POLICY_INFO_DOMAIN)] lsa_DomainInfo domain; */
/* IDL: [case(LSA_POLICY_INFO_PD)] [case(LSA_POLICY_INFO_PD)] lsa_PDAccountInfo pd; */
/* IDL: [case(LSA_POLICY_INFO_ACCOUNT_DOMAIN)] [case(LSA_POLICY_INFO_ACCOUNT_DOMAIN)] lsa_DomainInfo account_domain; */
/* IDL: [case(LSA_POLICY_INFO_ROLE)] [case(LSA_POLICY_INFO_ROLE)] lsa_ServerRole role; */
/* IDL: [case(LSA_POLICY_INFO_REPLICA)] [case(LSA_POLICY_INFO_REPLICA)] lsa_ReplicaSourceInfo replica; */
/* IDL: [case(LSA_POLICY_INFO_QUOTA)] [case(LSA_POLICY_INFO_QUOTA)] lsa_DefaultQuotaInfo quota; */
/* IDL: [case(LSA_POLICY_INFO_DB)] [case(LSA_POLICY_INFO_DB)] lsa_ModificationInfo db; */
/* IDL: [case(LSA_POLICY_INFO_AUDIT_FULL_SET)] [case(LSA_POLICY_INFO_AUDIT_FULL_SET)] lsa_AuditFullSetInfo auditfullset; */
/* IDL: [case(LSA_POLICY_INFO_AUDIT_FULL_QUERY)] [case(LSA_POLICY_INFO_AUDIT_FULL_QUERY)] lsa_AuditFullQueryInfo auditfullquery; */
/* IDL: [case(LSA_POLICY_INFO_DNS)] [case(LSA_POLICY_INFO_DNS)] lsa_DnsDomainInfo dns; */
/* IDL: } */

static int
lsarpc_dissect_element_lsa_PolicyInformation_audit_log(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_AuditLogInfo(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_PolicyInformation_audit_log,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_PolicyInformation_audit_events(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_AuditEventsInfo(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_PolicyInformation_audit_events,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_PolicyInformation_domain(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_DomainInfo(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_PolicyInformation_domain,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_PolicyInformation_pd(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_PDAccountInfo(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_PolicyInformation_pd,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_PolicyInformation_account_domain(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_DomainInfo(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_PolicyInformation_account_domain,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_PolicyInformation_role(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_ServerRole(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_PolicyInformation_role,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_PolicyInformation_replica(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_ReplicaSourceInfo(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_PolicyInformation_replica,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_PolicyInformation_quota(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_DefaultQuotaInfo(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_PolicyInformation_quota,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_PolicyInformation_db(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_ModificationInfo(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_PolicyInformation_db,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_PolicyInformation_auditfullset(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_AuditFullSetInfo(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_PolicyInformation_auditfullset,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_PolicyInformation_auditfullquery(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_AuditFullQueryInfo(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_PolicyInformation_auditfullquery,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_PolicyInformation_dns(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_DnsDomainInfo(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_PolicyInformation_dns,0);

	return offset;
}

static int
lsarpc_dissect_lsa_PolicyInformation(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_)
{
	proto_item *item = NULL;
	proto_tree *tree = NULL;
	int old_offset;
	guint16 level;

	old_offset = offset;
	if (parent_tree) {
		item = proto_tree_add_text(parent_tree, tvb, offset, -1, "lsa_PolicyInformation");
		tree = proto_item_add_subtree(item, ett_lsarpc_lsa_PolicyInformation);
	}

	offset = dissect_ndr_uint16(tvb, offset, pinfo, tree, di, drep, hf_index, &level);
	ALIGN_TO_8_BYTES;

	switch(level) {
		case LSA_POLICY_INFO_AUDIT_LOG:
			offset = lsarpc_dissect_element_lsa_PolicyInformation_audit_log(tvb, offset, pinfo, tree, di, drep);
		break;

		case LSA_POLICY_INFO_AUDIT_EVENTS:
			offset = lsarpc_dissect_element_lsa_PolicyInformation_audit_events(tvb, offset, pinfo, tree, di, drep);
		break;

		case LSA_POLICY_INFO_DOMAIN:
			offset = lsarpc_dissect_element_lsa_PolicyInformation_domain(tvb, offset, pinfo, tree, di, drep);
		break;

		case LSA_POLICY_INFO_PD:
			offset = lsarpc_dissect_element_lsa_PolicyInformation_pd(tvb, offset, pinfo, tree, di, drep);
		break;

		case LSA_POLICY_INFO_ACCOUNT_DOMAIN:
			offset = lsarpc_dissect_element_lsa_PolicyInformation_account_domain(tvb, offset, pinfo, tree, di, drep);
		break;

		case LSA_POLICY_INFO_ROLE:
			offset = lsarpc_dissect_element_lsa_PolicyInformation_role(tvb, offset, pinfo, tree, di, drep);
		break;

		case LSA_POLICY_INFO_REPLICA:
			offset = lsarpc_dissect_element_lsa_PolicyInformation_replica(tvb, offset, pinfo, tree, di, drep);
		break;

		case LSA_POLICY_INFO_QUOTA:
			offset = lsarpc_dissect_element_lsa_PolicyInformation_quota(tvb, offset, pinfo, tree, di, drep);
		break;

		case LSA_POLICY_INFO_DB:
			offset = lsarpc_dissect_element_lsa_PolicyInformation_db(tvb, offset, pinfo, tree, di, drep);
		break;

		case LSA_POLICY_INFO_AUDIT_FULL_SET:
			offset = lsarpc_dissect_element_lsa_PolicyInformation_auditfullset(tvb, offset, pinfo, tree, di, drep);
		break;

		case LSA_POLICY_INFO_AUDIT_FULL_QUERY:
			offset = lsarpc_dissect_element_lsa_PolicyInformation_auditfullquery(tvb, offset, pinfo, tree, di, drep);
		break;

		case LSA_POLICY_INFO_DNS:
			offset = lsarpc_dissect_element_lsa_PolicyInformation_dns(tvb, offset, pinfo, tree, di, drep);
		break;
	}
	proto_item_set_len(item, offset-old_offset);


	return offset;
}

/* IDL: struct { */
/* IDL: 	[unique(1)] dom_sid2 *sid; */
/* IDL: } */

static int
lsarpc_dissect_element_lsa_SidPtr_sid(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_embedded_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_SidPtr_sid_, NDR_POINTER_UNIQUE, "Pointer to Sid (dom_sid2)",hf_lsarpc_lsa_SidPtr_sid);

	return offset;
}

static int
lsarpc_dissect_element_lsa_SidPtr_sid_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_dom_sid2(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_SidPtr_sid,0);

	return offset;
}

int
lsarpc_dissect_struct_lsa_SidPtr(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_)
{
	proto_item *item = NULL;
	proto_tree *tree = NULL;

	int old_offset;

	ALIGN_TO_5_BYTES;

	old_offset = offset;

	if (parent_tree) {
		item = proto_tree_add_item(parent_tree, hf_index, tvb, offset, -1, ENC_NA);
		tree = proto_item_add_subtree(item, ett_lsarpc_lsa_SidPtr);
	}
	
	offset = lsarpc_dissect_element_lsa_SidPtr_sid(tvb, offset, pinfo, tree, di, drep);


	proto_item_set_len(item, offset-old_offset);


	if (di->call_data->flags & DCERPC_IS_NDR64) {
		ALIGN_TO_5_BYTES;
	}

	return offset;
}


/* IDL: struct { */
/* IDL: 	[range(0,1000)] uint32 num_sids; */
/* IDL: 	[unique(1)] [size_is(num_sids)] lsa_SidPtr *sids; */
/* IDL: } */

static int
lsarpc_dissect_element_lsa_SidArray_num_sids(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_SidArray_num_sids, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_SidArray_sids(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_embedded_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_SidArray_sids_, NDR_POINTER_UNIQUE, "Pointer to Sids (lsa_SidPtr)",hf_lsarpc_lsa_SidArray_sids);

	return offset;
}

static int
lsarpc_dissect_element_lsa_SidArray_sids_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_ucarray(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_SidArray_sids__);

	return offset;
}

static int
lsarpc_dissect_element_lsa_SidArray_sids__(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_SidPtr(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_SidArray_sids,0);

	return offset;
}

int
lsarpc_dissect_struct_lsa_SidArray(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_)
{
	proto_item *item = NULL;
	proto_tree *tree = NULL;

	int old_offset;

	ALIGN_TO_5_BYTES;

	old_offset = offset;

	if (parent_tree) {
		item = proto_tree_add_item(parent_tree, hf_index, tvb, offset, -1, ENC_NA);
		tree = proto_item_add_subtree(item, ett_lsarpc_lsa_SidArray);
	}
	
	offset = lsarpc_dissect_element_lsa_SidArray_num_sids(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_SidArray_sids(tvb, offset, pinfo, tree, di, drep);


	proto_item_set_len(item, offset-old_offset);


	if (di->call_data->flags & DCERPC_IS_NDR64) {
		ALIGN_TO_5_BYTES;
	}

	return offset;
}


/* IDL: struct { */
/* IDL: 	uint32 count; */
/* IDL: 	[unique(1)] [size_is(count)] lsa_DomainInfo *domains; */
/* IDL: } */

static int
lsarpc_dissect_element_lsa_DomainList_count(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_DomainList_count, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_DomainList_domains(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_embedded_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_DomainList_domains_, NDR_POINTER_UNIQUE, "Pointer to Domains (lsa_DomainInfo)",hf_lsarpc_lsa_DomainList_domains);

	return offset;
}

static int
lsarpc_dissect_element_lsa_DomainList_domains_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_ucarray(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_DomainList_domains__);

	return offset;
}

static int
lsarpc_dissect_element_lsa_DomainList_domains__(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_DomainInfo(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_DomainList_domains,0);

	return offset;
}

int
lsarpc_dissect_struct_lsa_DomainList(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_)
{
	proto_item *item = NULL;
	proto_tree *tree = NULL;

	int old_offset;

	ALIGN_TO_5_BYTES;

	old_offset = offset;

	if (parent_tree) {
		item = proto_tree_add_item(parent_tree, hf_index, tvb, offset, -1, ENC_NA);
		tree = proto_item_add_subtree(item, ett_lsarpc_lsa_DomainList);
	}
	
	offset = lsarpc_dissect_element_lsa_DomainList_count(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_DomainList_domains(tvb, offset, pinfo, tree, di, drep);


	proto_item_set_len(item, offset-old_offset);


	if (di->call_data->flags & DCERPC_IS_NDR64) {
		ALIGN_TO_5_BYTES;
	}

	return offset;
}


/* IDL: enum { */
/* IDL: 	SID_NAME_USE_NONE=0, */
/* IDL: 	SID_NAME_USER=1, */
/* IDL: 	SID_NAME_DOM_GRP=2, */
/* IDL: 	SID_NAME_DOMAIN=3, */
/* IDL: 	SID_NAME_ALIAS=4, */
/* IDL: 	SID_NAME_WKN_GRP=5, */
/* IDL: 	SID_NAME_DELETED=6, */
/* IDL: 	SID_NAME_INVALID=7, */
/* IDL: 	SID_NAME_UNKNOWN=8, */
/* IDL: 	SID_NAME_COMPUTER=9, */
/* IDL: } */

int
lsarpc_dissect_enum_lsa_SidType(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 *param _U_)
{
	guint1632 parameter=0;
	if(param){
		parameter=(guint1632)*param;
	}
	offset = dissect_ndr_uint1632(tvb, offset, pinfo, tree, di, drep, hf_index, &parameter);
	if(param){
		*param=(guint32)parameter;
	}
	return offset;
}


/* IDL: struct { */
/* IDL: 	lsa_SidType sid_type; */
/* IDL: 	uint32 rid; */
/* IDL: 	uint32 sid_index; */
/* IDL: } */

static int
lsarpc_dissect_element_lsa_TranslatedSid_sid_type(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_enum_lsa_SidType(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_TranslatedSid_sid_type, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_TranslatedSid_rid(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_TranslatedSid_rid, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_TranslatedSid_sid_index(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_TranslatedSid_sid_index, 0);

	return offset;
}

int
lsarpc_dissect_struct_lsa_TranslatedSid(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_)
{
	proto_item *item = NULL;
	proto_tree *tree = NULL;

	int old_offset;

	ALIGN_TO_4_BYTES;

	old_offset = offset;

	if (parent_tree) {
		item = proto_tree_add_item(parent_tree, hf_index, tvb, offset, -1, ENC_NA);
		tree = proto_item_add_subtree(item, ett_lsarpc_lsa_TranslatedSid);
	}
	
	offset = lsarpc_dissect_element_lsa_TranslatedSid_sid_type(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_TranslatedSid_rid(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_TranslatedSid_sid_index(tvb, offset, pinfo, tree, di, drep);


	proto_item_set_len(item, offset-old_offset);


	if (di->call_data->flags & DCERPC_IS_NDR64) {
		ALIGN_TO_4_BYTES;
	}

	return offset;
}


/* IDL: struct { */
/* IDL: 	[range(0,1000)] uint32 count; */
/* IDL: 	[unique(1)] [size_is(count)] lsa_TranslatedSid *sids; */
/* IDL: } */

static int
lsarpc_dissect_element_lsa_TransSidArray_count(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_TransSidArray_count, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_TransSidArray_sids(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_embedded_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_TransSidArray_sids_, NDR_POINTER_UNIQUE, "Pointer to Sids (lsa_TranslatedSid)",hf_lsarpc_lsa_TransSidArray_sids);

	return offset;
}

static int
lsarpc_dissect_element_lsa_TransSidArray_sids_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_ucarray(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_TransSidArray_sids__);

	return offset;
}

static int
lsarpc_dissect_element_lsa_TransSidArray_sids__(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_TranslatedSid(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_TransSidArray_sids,0);

	return offset;
}

int
lsarpc_dissect_struct_lsa_TransSidArray(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_)
{
	proto_item *item = NULL;
	proto_tree *tree = NULL;

	int old_offset;

	ALIGN_TO_5_BYTES;

	old_offset = offset;

	if (parent_tree) {
		item = proto_tree_add_item(parent_tree, hf_index, tvb, offset, -1, ENC_NA);
		tree = proto_item_add_subtree(item, ett_lsarpc_lsa_TransSidArray);
	}
	
	offset = lsarpc_dissect_element_lsa_TransSidArray_count(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_TransSidArray_sids(tvb, offset, pinfo, tree, di, drep);


	proto_item_set_len(item, offset-old_offset);


	if (di->call_data->flags & DCERPC_IS_NDR64) {
		ALIGN_TO_5_BYTES;
	}

	return offset;
}


/* IDL: struct { */
/* IDL: 	[range(0,1000)] uint32 count; */
/* IDL: 	[unique(1)] [size_is(count)] lsa_DomainInfo *domains; */
/* IDL: 	uint32 max_size; */
/* IDL: } */

static int
lsarpc_dissect_element_lsa_RefDomainList_count(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_RefDomainList_count, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_RefDomainList_domains(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_embedded_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_RefDomainList_domains_, NDR_POINTER_UNIQUE, "Pointer to Domains (lsa_DomainInfo)",hf_lsarpc_lsa_RefDomainList_domains);

	return offset;
}

static int
lsarpc_dissect_element_lsa_RefDomainList_domains_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_ucarray(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_RefDomainList_domains__);

	return offset;
}

static int
lsarpc_dissect_element_lsa_RefDomainList_domains__(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_DomainInfo(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_RefDomainList_domains,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_RefDomainList_max_size(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_RefDomainList_max_size, 0);

	return offset;
}

int
lsarpc_dissect_struct_lsa_RefDomainList(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_)
{
	proto_item *item = NULL;
	proto_tree *tree = NULL;

	int old_offset;

	ALIGN_TO_5_BYTES;

	old_offset = offset;

	if (parent_tree) {
		item = proto_tree_add_item(parent_tree, hf_index, tvb, offset, -1, ENC_NA);
		tree = proto_item_add_subtree(item, ett_lsarpc_lsa_RefDomainList);
	}
	
	offset = lsarpc_dissect_element_lsa_RefDomainList_count(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_RefDomainList_domains(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_RefDomainList_max_size(tvb, offset, pinfo, tree, di, drep);


	proto_item_set_len(item, offset-old_offset);


	if (di->call_data->flags & DCERPC_IS_NDR64) {
		ALIGN_TO_5_BYTES;
	}

	return offset;
}


/* IDL: enum { */
/* IDL: 	LSA_LOOKUP_NAMES_ALL=1, */
/* IDL: 	LSA_LOOKUP_NAMES_DOMAINS_ONLY=2, */
/* IDL: 	LSA_LOOKUP_NAMES_PRIMARY_DOMAIN_ONLY=3, */
/* IDL: 	LSA_LOOKUP_NAMES_UPLEVEL_TRUSTS_ONLY=4, */
/* IDL: 	LSA_LOOKUP_NAMES_FOREST_TRUSTS_ONLY=5, */
/* IDL: 	LSA_LOOKUP_NAMES_UPLEVEL_TRUSTS_ONLY2=6, */
/* IDL: } */

int
lsarpc_dissect_enum_lsa_LookupNamesLevel(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 *param _U_)
{
	guint1632 parameter=0;
	if(param){
		parameter=(guint1632)*param;
	}
	offset = dissect_ndr_uint1632(tvb, offset, pinfo, tree, di, drep, hf_index, &parameter);
	if(param){
		*param=(guint32)parameter;
	}
	return offset;
}


/* IDL: struct { */
/* IDL: 	lsa_SidType sid_type; */
/* IDL: 	lsa_String name; */
/* IDL: 	uint32 sid_index; */
/* IDL: } */

static int
lsarpc_dissect_element_lsa_TranslatedName_sid_type(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_enum_lsa_SidType(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_TranslatedName_sid_type, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_TranslatedName_name(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_String(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_TranslatedName_name,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_TranslatedName_sid_index(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_TranslatedName_sid_index, 0);

	return offset;
}

int
lsarpc_dissect_struct_lsa_TranslatedName(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_)
{
	proto_item *item = NULL;
	proto_tree *tree = NULL;

	int old_offset;

	ALIGN_TO_5_BYTES;

	old_offset = offset;

	if (parent_tree) {
		item = proto_tree_add_item(parent_tree, hf_index, tvb, offset, -1, ENC_NA);
		tree = proto_item_add_subtree(item, ett_lsarpc_lsa_TranslatedName);
	}
	
	offset = lsarpc_dissect_element_lsa_TranslatedName_sid_type(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_TranslatedName_name(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_TranslatedName_sid_index(tvb, offset, pinfo, tree, di, drep);


	proto_item_set_len(item, offset-old_offset);


	if (di->call_data->flags & DCERPC_IS_NDR64) {
		ALIGN_TO_5_BYTES;
	}

	return offset;
}


/* IDL: struct { */
/* IDL: 	[range(0,1000)] uint32 count; */
/* IDL: 	[unique(1)] [size_is(count)] lsa_TranslatedName *names; */
/* IDL: } */

static int
lsarpc_dissect_element_lsa_TransNameArray_count(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_TransNameArray_count, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_TransNameArray_names(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_embedded_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_TransNameArray_names_, NDR_POINTER_UNIQUE, "Pointer to Names (lsa_TranslatedName)",hf_lsarpc_lsa_TransNameArray_names);

	return offset;
}

static int
lsarpc_dissect_element_lsa_TransNameArray_names_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_ucarray(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_TransNameArray_names__);

	return offset;
}

static int
lsarpc_dissect_element_lsa_TransNameArray_names__(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_TranslatedName(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_TransNameArray_names,0);

	return offset;
}

int
lsarpc_dissect_struct_lsa_TransNameArray(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_)
{
	proto_item *item = NULL;
	proto_tree *tree = NULL;

	int old_offset;

	ALIGN_TO_5_BYTES;

	old_offset = offset;

	if (parent_tree) {
		item = proto_tree_add_item(parent_tree, hf_index, tvb, offset, -1, ENC_NA);
		tree = proto_item_add_subtree(item, ett_lsarpc_lsa_TransNameArray);
	}
	
	offset = lsarpc_dissect_element_lsa_TransNameArray_count(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_TransNameArray_names(tvb, offset, pinfo, tree, di, drep);


	proto_item_set_len(item, offset-old_offset);


	if (di->call_data->flags & DCERPC_IS_NDR64) {
		ALIGN_TO_5_BYTES;
	}

	return offset;
}


/* IDL: struct { */
/* IDL: 	lsa_LUID luid; */
/* IDL: 	uint32 attribute; */
/* IDL: } */

static int
lsarpc_dissect_element_lsa_LUIDAttribute_luid(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_LUID(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_LUIDAttribute_luid,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LUIDAttribute_attribute(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_LUIDAttribute_attribute, 0);

	return offset;
}

int
lsarpc_dissect_struct_lsa_LUIDAttribute(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_)
{
	proto_item *item = NULL;
	proto_tree *tree = NULL;

	int old_offset;

	ALIGN_TO_4_BYTES;

	old_offset = offset;

	if (parent_tree) {
		item = proto_tree_add_item(parent_tree, hf_index, tvb, offset, -1, ENC_NA);
		tree = proto_item_add_subtree(item, ett_lsarpc_lsa_LUIDAttribute);
	}
	
	offset = lsarpc_dissect_element_lsa_LUIDAttribute_luid(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_LUIDAttribute_attribute(tvb, offset, pinfo, tree, di, drep);


	proto_item_set_len(item, offset-old_offset);


	if (di->call_data->flags & DCERPC_IS_NDR64) {
		ALIGN_TO_4_BYTES;
	}

	return offset;
}


/* IDL: struct { */
/* IDL: 	[range(0,1000)] uint32 count; */
/* IDL: 	uint32 unknown; */
/* IDL: 	[size_is(count)] lsa_LUIDAttribute set[*]; */
/* IDL: } */

static int
lsarpc_dissect_element_lsa_PrivilegeSet_count(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_PrivilegeSet_count, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_PrivilegeSet_unknown(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_PrivilegeSet_unknown, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_PrivilegeSet_set(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_ucarray(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_PrivilegeSet_set_);

	return offset;
}

static int
lsarpc_dissect_element_lsa_PrivilegeSet_set_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_LUIDAttribute(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_PrivilegeSet_set,0);

	return offset;
}

int
lsarpc_dissect_struct_lsa_PrivilegeSet(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_)
{
	proto_item *item = NULL;
	proto_tree *tree = NULL;

	int old_offset;

	ALIGN_TO_4_BYTES;

	old_offset = offset;

	if (parent_tree) {
		item = proto_tree_add_item(parent_tree, hf_index, tvb, offset, -1, ENC_NA);
		tree = proto_item_add_subtree(item, ett_lsarpc_lsa_PrivilegeSet);
	}
	
	offset = lsarpc_dissect_element_lsa_PrivilegeSet_count(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_PrivilegeSet_unknown(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_PrivilegeSet_set(tvb, offset, pinfo, tree, di, drep);


	proto_item_set_len(item, offset-old_offset);


	if (di->call_data->flags & DCERPC_IS_NDR64) {
		ALIGN_TO_4_BYTES;
	}

	return offset;
}


/* IDL: struct { */
/* IDL: 	uint32 length; */
/* IDL: 	uint32 size; */
/* IDL: 	[unique(1)] [length_is(length)] [size_is(size)] uint8 *data; */
/* IDL: } */

static int
lsarpc_dissect_element_lsa_DATA_BUF_length(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_DATA_BUF_length, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_DATA_BUF_size(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_DATA_BUF_size, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_DATA_BUF_data(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_embedded_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_DATA_BUF_data_, NDR_POINTER_UNIQUE, "Pointer to Data (uint8)",hf_lsarpc_lsa_DATA_BUF_data);

	return offset;
}

static int
lsarpc_dissect_element_lsa_DATA_BUF_data_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_ucvarray(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_DATA_BUF_data__);

	return offset;
}

static int
lsarpc_dissect_element_lsa_DATA_BUF_data__(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint8(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_DATA_BUF_data, 0);

	return offset;
}

int
lsarpc_dissect_struct_lsa_DATA_BUF(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_)
{
	proto_item *item = NULL;
	proto_tree *tree = NULL;

	int old_offset;

	ALIGN_TO_5_BYTES;

	old_offset = offset;

	if (parent_tree) {
		item = proto_tree_add_item(parent_tree, hf_index, tvb, offset, -1, ENC_NA);
		tree = proto_item_add_subtree(item, ett_lsarpc_lsa_DATA_BUF);
	}
	
	offset = lsarpc_dissect_element_lsa_DATA_BUF_length(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_DATA_BUF_size(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_DATA_BUF_data(tvb, offset, pinfo, tree, di, drep);


	proto_item_set_len(item, offset-old_offset);


	if (di->call_data->flags & DCERPC_IS_NDR64) {
		ALIGN_TO_5_BYTES;
	}

	return offset;
}


/* IDL: struct { */
/* IDL: 	[range(0,65536)] uint32 size; */
/* IDL: 	[unique(1)] [size_is(size)] uint8 *data; */
/* IDL: } */

static int
lsarpc_dissect_element_lsa_DATA_BUF2_size(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_DATA_BUF2_size, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_DATA_BUF2_data(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_embedded_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_DATA_BUF2_data_, NDR_POINTER_UNIQUE, "Pointer to Data (uint8)",hf_lsarpc_lsa_DATA_BUF2_data);

	return offset;
}

static int
lsarpc_dissect_element_lsa_DATA_BUF2_data_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_ucarray(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_DATA_BUF2_data__);

	return offset;
}

static int
lsarpc_dissect_element_lsa_DATA_BUF2_data__(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint8(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_DATA_BUF2_data, 0);

	return offset;
}

int
lsarpc_dissect_struct_lsa_DATA_BUF2(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_)
{
	proto_item *item = NULL;
	proto_tree *tree = NULL;

	int old_offset;

	ALIGN_TO_5_BYTES;

	old_offset = offset;

	if (parent_tree) {
		item = proto_tree_add_item(parent_tree, hf_index, tvb, offset, -1, ENC_NA);
		tree = proto_item_add_subtree(item, ett_lsarpc_lsa_DATA_BUF2);
	}
	
	offset = lsarpc_dissect_element_lsa_DATA_BUF2_size(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_DATA_BUF2_data(tvb, offset, pinfo, tree, di, drep);


	proto_item_set_len(item, offset-old_offset);


	if (di->call_data->flags & DCERPC_IS_NDR64) {
		ALIGN_TO_5_BYTES;
	}

	return offset;
}


/* IDL: enum { */
/* IDL: 	LSA_TRUSTED_DOMAIN_INFO_NAME=1, */
/* IDL: 	LSA_TRUSTED_DOMAIN_INFO_CONTROLLERS_INFO=2, */
/* IDL: 	LSA_TRUSTED_DOMAIN_INFO_POSIX_OFFSET=3, */
/* IDL: 	LSA_TRUSTED_DOMAIN_INFO_PASSWORD=4, */
/* IDL: 	LSA_TRUSTED_DOMAIN_INFO_BASIC=5, */
/* IDL: 	LSA_TRUSTED_DOMAIN_INFO_INFO_EX=6, */
/* IDL: 	LSA_TRUSTED_DOMAIN_INFO_AUTH_INFO=7, */
/* IDL: 	LSA_TRUSTED_DOMAIN_INFO_FULL_INFO=8, */
/* IDL: 	LSA_TRUSTED_DOMAIN_INFO_11=11, */
/* IDL: 	LSA_TRUSTED_DOMAIN_INFO_INFO_ALL=12, */
/* IDL: } */

int
lsarpc_dissect_enum_lsa_TrustDomInfoEnum(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 *param _U_)
{
	guint1632 parameter=0;
	if(param){
		parameter=(guint1632)*param;
	}
	offset = dissect_ndr_uint1632(tvb, offset, pinfo, tree, di, drep, hf_index, &parameter);
	if(param){
		*param=(guint32)parameter;
	}
	return offset;
}


/* IDL: struct { */
/* IDL: 	lsa_StringLarge netbios_name; */
/* IDL: } */

static int
lsarpc_dissect_element_lsa_TrustDomainInfoName_netbios_name(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_StringLarge(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_TrustDomainInfoName_netbios_name,0);

	return offset;
}

int
lsarpc_dissect_struct_lsa_TrustDomainInfoName(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_)
{
	proto_item *item = NULL;
	proto_tree *tree = NULL;

	int old_offset;

	ALIGN_TO_5_BYTES;

	old_offset = offset;

	if (parent_tree) {
		item = proto_tree_add_item(parent_tree, hf_index, tvb, offset, -1, ENC_NA);
		tree = proto_item_add_subtree(item, ett_lsarpc_lsa_TrustDomainInfoName);
	}
	
	offset = lsarpc_dissect_element_lsa_TrustDomainInfoName_netbios_name(tvb, offset, pinfo, tree, di, drep);


	proto_item_set_len(item, offset-old_offset);


	if (di->call_data->flags & DCERPC_IS_NDR64) {
		ALIGN_TO_5_BYTES;
	}

	return offset;
}


/* IDL: struct { */
/* IDL: 	uint32 posix_offset; */
/* IDL: } */

static int
lsarpc_dissect_element_lsa_TrustDomainInfoPosixOffset_posix_offset(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_TrustDomainInfoPosixOffset_posix_offset, 0);

	return offset;
}

int
lsarpc_dissect_struct_lsa_TrustDomainInfoPosixOffset(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_)
{
	proto_item *item = NULL;
	proto_tree *tree = NULL;

	int old_offset;

	ALIGN_TO_4_BYTES;

	old_offset = offset;

	if (parent_tree) {
		item = proto_tree_add_item(parent_tree, hf_index, tvb, offset, -1, ENC_NA);
		tree = proto_item_add_subtree(item, ett_lsarpc_lsa_TrustDomainInfoPosixOffset);
	}
	
	offset = lsarpc_dissect_element_lsa_TrustDomainInfoPosixOffset_posix_offset(tvb, offset, pinfo, tree, di, drep);


	proto_item_set_len(item, offset-old_offset);


	if (di->call_data->flags & DCERPC_IS_NDR64) {
		ALIGN_TO_4_BYTES;
	}

	return offset;
}


/* IDL: struct { */
/* IDL: 	[unique(1)] lsa_DATA_BUF *password; */
/* IDL: 	[unique(1)] lsa_DATA_BUF *old_password; */
/* IDL: } */

static int
lsarpc_dissect_element_lsa_TrustDomainInfoPassword_password(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_embedded_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_TrustDomainInfoPassword_password_, NDR_POINTER_UNIQUE, "Pointer to Password (lsa_DATA_BUF)",hf_lsarpc_lsa_TrustDomainInfoPassword_password);

	return offset;
}

static int
lsarpc_dissect_element_lsa_TrustDomainInfoPassword_password_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_DATA_BUF(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_TrustDomainInfoPassword_password,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_TrustDomainInfoPassword_old_password(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_embedded_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_TrustDomainInfoPassword_old_password_, NDR_POINTER_UNIQUE, "Pointer to Old Password (lsa_DATA_BUF)",hf_lsarpc_lsa_TrustDomainInfoPassword_old_password);

	return offset;
}

static int
lsarpc_dissect_element_lsa_TrustDomainInfoPassword_old_password_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_DATA_BUF(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_TrustDomainInfoPassword_old_password,0);

	return offset;
}

int
lsarpc_dissect_struct_lsa_TrustDomainInfoPassword(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_)
{
	proto_item *item = NULL;
	proto_tree *tree = NULL;

	int old_offset;

	ALIGN_TO_5_BYTES;

	old_offset = offset;

	if (parent_tree) {
		item = proto_tree_add_item(parent_tree, hf_index, tvb, offset, -1, ENC_NA);
		tree = proto_item_add_subtree(item, ett_lsarpc_lsa_TrustDomainInfoPassword);
	}
	
	offset = lsarpc_dissect_element_lsa_TrustDomainInfoPassword_password(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_TrustDomainInfoPassword_old_password(tvb, offset, pinfo, tree, di, drep);


	proto_item_set_len(item, offset-old_offset);


	if (di->call_data->flags & DCERPC_IS_NDR64) {
		ALIGN_TO_5_BYTES;
	}

	return offset;
}


/* IDL: struct { */
/* IDL: 	lsa_String netbios_name; */
/* IDL: 	[unique(1)] dom_sid2 *sid; */
/* IDL: } */

static int
lsarpc_dissect_element_lsa_TrustDomainInfoBasic_netbios_name(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_String(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_TrustDomainInfoBasic_netbios_name,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_TrustDomainInfoBasic_sid(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_embedded_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_TrustDomainInfoBasic_sid_, NDR_POINTER_UNIQUE, "Pointer to Sid (dom_sid2)",hf_lsarpc_lsa_TrustDomainInfoBasic_sid);

	return offset;
}

static int
lsarpc_dissect_element_lsa_TrustDomainInfoBasic_sid_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_dom_sid2(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_TrustDomainInfoBasic_sid,0);

	return offset;
}

int
lsarpc_dissect_struct_lsa_TrustDomainInfoBasic(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_)
{
	proto_item *item = NULL;
	proto_tree *tree = NULL;

	int old_offset;

	ALIGN_TO_5_BYTES;

	old_offset = offset;

	if (parent_tree) {
		item = proto_tree_add_item(parent_tree, hf_index, tvb, offset, -1, ENC_NA);
		tree = proto_item_add_subtree(item, ett_lsarpc_lsa_TrustDomainInfoBasic);
	}
	
	offset = lsarpc_dissect_element_lsa_TrustDomainInfoBasic_netbios_name(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_TrustDomainInfoBasic_sid(tvb, offset, pinfo, tree, di, drep);


	proto_item_set_len(item, offset-old_offset);


	if (di->call_data->flags & DCERPC_IS_NDR64) {
		ALIGN_TO_5_BYTES;
	}

	return offset;
}


/* IDL: struct { */
/* IDL: 	lsa_StringLarge domain_name; */
/* IDL: 	lsa_StringLarge netbios_name; */
/* IDL: 	[unique(1)] dom_sid2 *sid; */
/* IDL: 	uint32 trust_direction; */
/* IDL: 	uint32 trust_type; */
/* IDL: 	uint32 trust_attributes; */
/* IDL: } */

static int
lsarpc_dissect_element_lsa_TrustDomainInfoInfoEx_domain_name(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_StringLarge(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_TrustDomainInfoInfoEx_domain_name,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_TrustDomainInfoInfoEx_netbios_name(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_StringLarge(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_TrustDomainInfoInfoEx_netbios_name,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_TrustDomainInfoInfoEx_sid(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_embedded_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_TrustDomainInfoInfoEx_sid_, NDR_POINTER_UNIQUE, "Pointer to Sid (dom_sid2)",hf_lsarpc_lsa_TrustDomainInfoInfoEx_sid);

	return offset;
}

static int
lsarpc_dissect_element_lsa_TrustDomainInfoInfoEx_sid_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_dom_sid2(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_TrustDomainInfoInfoEx_sid,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_TrustDomainInfoInfoEx_trust_direction(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_TrustDomainInfoInfoEx_trust_direction, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_TrustDomainInfoInfoEx_trust_type(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_TrustDomainInfoInfoEx_trust_type, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_TrustDomainInfoInfoEx_trust_attributes(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_TrustDomainInfoInfoEx_trust_attributes, 0);

	return offset;
}

int
lsarpc_dissect_struct_lsa_TrustDomainInfoInfoEx(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_)
{
	proto_item *item = NULL;
	proto_tree *tree = NULL;

	int old_offset;

	ALIGN_TO_5_BYTES;

	old_offset = offset;

	if (parent_tree) {
		item = proto_tree_add_item(parent_tree, hf_index, tvb, offset, -1, ENC_NA);
		tree = proto_item_add_subtree(item, ett_lsarpc_lsa_TrustDomainInfoInfoEx);
	}
	
	offset = lsarpc_dissect_element_lsa_TrustDomainInfoInfoEx_domain_name(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_TrustDomainInfoInfoEx_netbios_name(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_TrustDomainInfoInfoEx_sid(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_TrustDomainInfoInfoEx_trust_direction(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_TrustDomainInfoInfoEx_trust_type(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_TrustDomainInfoInfoEx_trust_attributes(tvb, offset, pinfo, tree, di, drep);


	proto_item_set_len(item, offset-old_offset);


	if (di->call_data->flags & DCERPC_IS_NDR64) {
		ALIGN_TO_5_BYTES;
	}

	return offset;
}


/* IDL: struct { */
/* IDL: 	NTTIME_hyper last_update_time; */
/* IDL: 	uint32 secret_type; */
/* IDL: 	lsa_DATA_BUF2 data; */
/* IDL: } */

static int
lsarpc_dissect_element_lsa_TrustDomainInfoBuffer_last_update_time(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_nt_NTTIME(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_TrustDomainInfoBuffer_last_update_time);

	return offset;
}

static int
lsarpc_dissect_element_lsa_TrustDomainInfoBuffer_secret_type(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_TrustDomainInfoBuffer_secret_type, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_TrustDomainInfoBuffer_data(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_DATA_BUF2(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_TrustDomainInfoBuffer_data,0);

	return offset;
}

int
lsarpc_dissect_struct_lsa_TrustDomainInfoBuffer(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_)
{
	proto_item *item = NULL;
	proto_tree *tree = NULL;

	int old_offset;

	ALIGN_TO_8_BYTES;

	old_offset = offset;

	if (parent_tree) {
		item = proto_tree_add_item(parent_tree, hf_index, tvb, offset, -1, ENC_NA);
		tree = proto_item_add_subtree(item, ett_lsarpc_lsa_TrustDomainInfoBuffer);
	}
	
	offset = lsarpc_dissect_element_lsa_TrustDomainInfoBuffer_last_update_time(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_TrustDomainInfoBuffer_secret_type(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_TrustDomainInfoBuffer_data(tvb, offset, pinfo, tree, di, drep);


	proto_item_set_len(item, offset-old_offset);


	if (di->call_data->flags & DCERPC_IS_NDR64) {
		ALIGN_TO_8_BYTES;
	}

	return offset;
}


/* IDL: struct { */
/* IDL: 	uint32 incoming_count; */
/* IDL: 	[unique(1)] lsa_TrustDomainInfoBuffer *incoming_current_auth_info; */
/* IDL: 	[unique(1)] lsa_TrustDomainInfoBuffer *incoming_previous_auth_info; */
/* IDL: 	uint32 outgoing_count; */
/* IDL: 	[unique(1)] lsa_TrustDomainInfoBuffer *outgoing_current_auth_info; */
/* IDL: 	[unique(1)] lsa_TrustDomainInfoBuffer *outgoing_previous_auth_info; */
/* IDL: } */

static int
lsarpc_dissect_element_lsa_TrustDomainInfoAuthInfo_incoming_count(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_TrustDomainInfoAuthInfo_incoming_count, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_TrustDomainInfoAuthInfo_incoming_current_auth_info(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_embedded_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_TrustDomainInfoAuthInfo_incoming_current_auth_info_, NDR_POINTER_UNIQUE, "Pointer to Incoming Current Auth Info (lsa_TrustDomainInfoBuffer)",hf_lsarpc_lsa_TrustDomainInfoAuthInfo_incoming_current_auth_info);

	return offset;
}

static int
lsarpc_dissect_element_lsa_TrustDomainInfoAuthInfo_incoming_current_auth_info_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_TrustDomainInfoBuffer(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_TrustDomainInfoAuthInfo_incoming_current_auth_info,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_TrustDomainInfoAuthInfo_incoming_previous_auth_info(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_embedded_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_TrustDomainInfoAuthInfo_incoming_previous_auth_info_, NDR_POINTER_UNIQUE, "Pointer to Incoming Previous Auth Info (lsa_TrustDomainInfoBuffer)",hf_lsarpc_lsa_TrustDomainInfoAuthInfo_incoming_previous_auth_info);

	return offset;
}

static int
lsarpc_dissect_element_lsa_TrustDomainInfoAuthInfo_incoming_previous_auth_info_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_TrustDomainInfoBuffer(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_TrustDomainInfoAuthInfo_incoming_previous_auth_info,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_TrustDomainInfoAuthInfo_outgoing_count(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_TrustDomainInfoAuthInfo_outgoing_count, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_TrustDomainInfoAuthInfo_outgoing_current_auth_info(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_embedded_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_TrustDomainInfoAuthInfo_outgoing_current_auth_info_, NDR_POINTER_UNIQUE, "Pointer to Outgoing Current Auth Info (lsa_TrustDomainInfoBuffer)",hf_lsarpc_lsa_TrustDomainInfoAuthInfo_outgoing_current_auth_info);

	return offset;
}

static int
lsarpc_dissect_element_lsa_TrustDomainInfoAuthInfo_outgoing_current_auth_info_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_TrustDomainInfoBuffer(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_TrustDomainInfoAuthInfo_outgoing_current_auth_info,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_TrustDomainInfoAuthInfo_outgoing_previous_auth_info(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_embedded_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_TrustDomainInfoAuthInfo_outgoing_previous_auth_info_, NDR_POINTER_UNIQUE, "Pointer to Outgoing Previous Auth Info (lsa_TrustDomainInfoBuffer)",hf_lsarpc_lsa_TrustDomainInfoAuthInfo_outgoing_previous_auth_info);

	return offset;
}

static int
lsarpc_dissect_element_lsa_TrustDomainInfoAuthInfo_outgoing_previous_auth_info_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_TrustDomainInfoBuffer(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_TrustDomainInfoAuthInfo_outgoing_previous_auth_info,0);

	return offset;
}

int
lsarpc_dissect_struct_lsa_TrustDomainInfoAuthInfo(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_)
{
	proto_item *item = NULL;
	proto_tree *tree = NULL;

	int old_offset;

	ALIGN_TO_5_BYTES;

	old_offset = offset;

	if (parent_tree) {
		item = proto_tree_add_item(parent_tree, hf_index, tvb, offset, -1, ENC_NA);
		tree = proto_item_add_subtree(item, ett_lsarpc_lsa_TrustDomainInfoAuthInfo);
	}
	
	offset = lsarpc_dissect_element_lsa_TrustDomainInfoAuthInfo_incoming_count(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_TrustDomainInfoAuthInfo_incoming_current_auth_info(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_TrustDomainInfoAuthInfo_incoming_previous_auth_info(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_TrustDomainInfoAuthInfo_outgoing_count(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_TrustDomainInfoAuthInfo_outgoing_current_auth_info(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_TrustDomainInfoAuthInfo_outgoing_previous_auth_info(tvb, offset, pinfo, tree, di, drep);


	proto_item_set_len(item, offset-old_offset);


	if (di->call_data->flags & DCERPC_IS_NDR64) {
		ALIGN_TO_5_BYTES;
	}

	return offset;
}


/* IDL: struct { */
/* IDL: 	lsa_TrustDomainInfoInfoEx info_ex; */
/* IDL: 	lsa_TrustDomainInfoPosixOffset posix_offset; */
/* IDL: 	lsa_TrustDomainInfoAuthInfo auth_info; */
/* IDL: } */

static int
lsarpc_dissect_element_lsa_TrustDomainInfoFullInfo_info_ex(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_TrustDomainInfoInfoEx(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_TrustDomainInfoFullInfo_info_ex,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_TrustDomainInfoFullInfo_posix_offset(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_TrustDomainInfoPosixOffset(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_TrustDomainInfoFullInfo_posix_offset,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_TrustDomainInfoFullInfo_auth_info(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_TrustDomainInfoAuthInfo(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_TrustDomainInfoFullInfo_auth_info,0);

	return offset;
}

int
lsarpc_dissect_struct_lsa_TrustDomainInfoFullInfo(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_)
{
	proto_item *item = NULL;
	proto_tree *tree = NULL;

	int old_offset;

	ALIGN_TO_5_BYTES;

	old_offset = offset;

	if (parent_tree) {
		item = proto_tree_add_item(parent_tree, hf_index, tvb, offset, -1, ENC_NA);
		tree = proto_item_add_subtree(item, ett_lsarpc_lsa_TrustDomainInfoFullInfo);
	}
	
	offset = lsarpc_dissect_element_lsa_TrustDomainInfoFullInfo_info_ex(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_TrustDomainInfoFullInfo_posix_offset(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_TrustDomainInfoFullInfo_auth_info(tvb, offset, pinfo, tree, di, drep);


	proto_item_set_len(item, offset-old_offset);


	if (di->call_data->flags & DCERPC_IS_NDR64) {
		ALIGN_TO_5_BYTES;
	}

	return offset;
}


/* IDL: struct { */
/* IDL: 	lsa_TrustDomainInfoInfoEx info_ex; */
/* IDL: 	lsa_DATA_BUF2 data1; */
/* IDL: } */

static int
lsarpc_dissect_element_lsa_TrustDomainInfo11_info_ex(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_TrustDomainInfoInfoEx(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_TrustDomainInfo11_info_ex,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_TrustDomainInfo11_data1(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_DATA_BUF2(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_TrustDomainInfo11_data1,0);

	return offset;
}

int
lsarpc_dissect_struct_lsa_TrustDomainInfo11(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_)
{
	proto_item *item = NULL;
	proto_tree *tree = NULL;

	int old_offset;

	ALIGN_TO_5_BYTES;

	old_offset = offset;

	if (parent_tree) {
		item = proto_tree_add_item(parent_tree, hf_index, tvb, offset, -1, ENC_NA);
		tree = proto_item_add_subtree(item, ett_lsarpc_lsa_TrustDomainInfo11);
	}
	
	offset = lsarpc_dissect_element_lsa_TrustDomainInfo11_info_ex(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_TrustDomainInfo11_data1(tvb, offset, pinfo, tree, di, drep);


	proto_item_set_len(item, offset-old_offset);


	if (di->call_data->flags & DCERPC_IS_NDR64) {
		ALIGN_TO_5_BYTES;
	}

	return offset;
}


/* IDL: struct { */
/* IDL: 	lsa_TrustDomainInfoInfoEx info_ex; */
/* IDL: 	lsa_DATA_BUF2 data1; */
/* IDL: 	lsa_TrustDomainInfoPosixOffset posix_offset; */
/* IDL: 	lsa_TrustDomainInfoAuthInfo auth_info; */
/* IDL: } */

static int
lsarpc_dissect_element_lsa_TrustDomainInfoInfoAll_info_ex(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_TrustDomainInfoInfoEx(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_TrustDomainInfoInfoAll_info_ex,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_TrustDomainInfoInfoAll_data1(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_DATA_BUF2(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_TrustDomainInfoInfoAll_data1,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_TrustDomainInfoInfoAll_posix_offset(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_TrustDomainInfoPosixOffset(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_TrustDomainInfoInfoAll_posix_offset,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_TrustDomainInfoInfoAll_auth_info(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_TrustDomainInfoAuthInfo(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_TrustDomainInfoInfoAll_auth_info,0);

	return offset;
}

int
lsarpc_dissect_struct_lsa_TrustDomainInfoInfoAll(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_)
{
	proto_item *item = NULL;
	proto_tree *tree = NULL;

	int old_offset;

	ALIGN_TO_5_BYTES;

	old_offset = offset;

	if (parent_tree) {
		item = proto_tree_add_item(parent_tree, hf_index, tvb, offset, -1, ENC_NA);
		tree = proto_item_add_subtree(item, ett_lsarpc_lsa_TrustDomainInfoInfoAll);
	}
	
	offset = lsarpc_dissect_element_lsa_TrustDomainInfoInfoAll_info_ex(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_TrustDomainInfoInfoAll_data1(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_TrustDomainInfoInfoAll_posix_offset(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_TrustDomainInfoInfoAll_auth_info(tvb, offset, pinfo, tree, di, drep);


	proto_item_set_len(item, offset-old_offset);


	if (di->call_data->flags & DCERPC_IS_NDR64) {
		ALIGN_TO_5_BYTES;
	}

	return offset;
}


/* IDL: [switch_type(lsa_TrustDomInfoEnum)] union { */
/* IDL: [case(LSA_TRUSTED_DOMAIN_INFO_NAME)] [case(LSA_TRUSTED_DOMAIN_INFO_NAME)] lsa_TrustDomainInfoName name; */
/* IDL: [case(LSA_TRUSTED_DOMAIN_INFO_POSIX_OFFSET)] [case(LSA_TRUSTED_DOMAIN_INFO_POSIX_OFFSET)] lsa_TrustDomainInfoPosixOffset posix_offset; */
/* IDL: [case(LSA_TRUSTED_DOMAIN_INFO_PASSWORD)] [case(LSA_TRUSTED_DOMAIN_INFO_PASSWORD)] lsa_TrustDomainInfoPassword password; */
/* IDL: [case(LSA_TRUSTED_DOMAIN_INFO_BASIC)] [case(LSA_TRUSTED_DOMAIN_INFO_BASIC)] lsa_TrustDomainInfoBasic info_basic; */
/* IDL: [case(LSA_TRUSTED_DOMAIN_INFO_INFO_EX)] [case(LSA_TRUSTED_DOMAIN_INFO_INFO_EX)] lsa_TrustDomainInfoInfoEx info_ex; */
/* IDL: [case(LSA_TRUSTED_DOMAIN_INFO_AUTH_INFO)] [case(LSA_TRUSTED_DOMAIN_INFO_AUTH_INFO)] lsa_TrustDomainInfoAuthInfo auth_info; */
/* IDL: [case(LSA_TRUSTED_DOMAIN_INFO_FULL_INFO)] [case(LSA_TRUSTED_DOMAIN_INFO_FULL_INFO)] lsa_TrustDomainInfoFullInfo full_info; */
/* IDL: [case(LSA_TRUSTED_DOMAIN_INFO_11)] [case(LSA_TRUSTED_DOMAIN_INFO_11)] lsa_TrustDomainInfo11 info11; */
/* IDL: [case(LSA_TRUSTED_DOMAIN_INFO_INFO_ALL)] [case(LSA_TRUSTED_DOMAIN_INFO_INFO_ALL)] lsa_TrustDomainInfoInfoAll info_all; */
/* IDL: } */

static int
lsarpc_dissect_element_lsa_TrustedDomainInfo_name(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_TrustDomainInfoName(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_TrustedDomainInfo_name,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_TrustedDomainInfo_posix_offset(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_TrustDomainInfoPosixOffset(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_TrustedDomainInfo_posix_offset,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_TrustedDomainInfo_password(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_TrustDomainInfoPassword(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_TrustedDomainInfo_password,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_TrustedDomainInfo_info_basic(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_TrustDomainInfoBasic(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_TrustedDomainInfo_info_basic,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_TrustedDomainInfo_info_ex(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_TrustDomainInfoInfoEx(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_TrustedDomainInfo_info_ex,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_TrustedDomainInfo_auth_info(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_TrustDomainInfoAuthInfo(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_TrustedDomainInfo_auth_info,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_TrustedDomainInfo_full_info(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_TrustDomainInfoFullInfo(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_TrustedDomainInfo_full_info,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_TrustedDomainInfo_info11(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_TrustDomainInfo11(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_TrustedDomainInfo_info11,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_TrustedDomainInfo_info_all(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_TrustDomainInfoInfoAll(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_TrustedDomainInfo_info_all,0);

	return offset;
}

static int
lsarpc_dissect_lsa_TrustedDomainInfo(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_)
{
	proto_item *item = NULL;
	proto_tree *tree = NULL;
	int old_offset;
	guint1632 level;

	old_offset = offset;
	if (parent_tree) {
		item = proto_tree_add_text(parent_tree, tvb, offset, -1, "lsa_TrustedDomainInfo");
		tree = proto_item_add_subtree(item, ett_lsarpc_lsa_TrustedDomainInfo);
	}

	offset = dissect_ndr_uint1632(tvb, offset, pinfo, tree, di, drep, hf_index, &level);
	ALIGN_TO_5_BYTES;

	switch(level) {
		case LSA_TRUSTED_DOMAIN_INFO_NAME:
			offset = lsarpc_dissect_element_lsa_TrustedDomainInfo_name(tvb, offset, pinfo, tree, di, drep);
		break;

		case LSA_TRUSTED_DOMAIN_INFO_POSIX_OFFSET:
			offset = lsarpc_dissect_element_lsa_TrustedDomainInfo_posix_offset(tvb, offset, pinfo, tree, di, drep);
		break;

		case LSA_TRUSTED_DOMAIN_INFO_PASSWORD:
			offset = lsarpc_dissect_element_lsa_TrustedDomainInfo_password(tvb, offset, pinfo, tree, di, drep);
		break;

		case LSA_TRUSTED_DOMAIN_INFO_BASIC:
			offset = lsarpc_dissect_element_lsa_TrustedDomainInfo_info_basic(tvb, offset, pinfo, tree, di, drep);
		break;

		case LSA_TRUSTED_DOMAIN_INFO_INFO_EX:
			offset = lsarpc_dissect_element_lsa_TrustedDomainInfo_info_ex(tvb, offset, pinfo, tree, di, drep);
		break;

		case LSA_TRUSTED_DOMAIN_INFO_AUTH_INFO:
			offset = lsarpc_dissect_element_lsa_TrustedDomainInfo_auth_info(tvb, offset, pinfo, tree, di, drep);
		break;

		case LSA_TRUSTED_DOMAIN_INFO_FULL_INFO:
			offset = lsarpc_dissect_element_lsa_TrustedDomainInfo_full_info(tvb, offset, pinfo, tree, di, drep);
		break;

		case LSA_TRUSTED_DOMAIN_INFO_11:
			offset = lsarpc_dissect_element_lsa_TrustedDomainInfo_info11(tvb, offset, pinfo, tree, di, drep);
		break;

		case LSA_TRUSTED_DOMAIN_INFO_INFO_ALL:
			offset = lsarpc_dissect_element_lsa_TrustedDomainInfo_info_all(tvb, offset, pinfo, tree, di, drep);
		break;
	}
	proto_item_set_len(item, offset-old_offset);


	return offset;
}

/* IDL: struct { */
/* IDL: 	[unique(1)] lsa_DATA_BUF *buf; */
/* IDL: } */

static int
lsarpc_dissect_element_lsa_DATA_BUF_PTR_buf(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_embedded_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_DATA_BUF_PTR_buf_, NDR_POINTER_UNIQUE, "Pointer to Buf (lsa_DATA_BUF)",hf_lsarpc_lsa_DATA_BUF_PTR_buf);

	return offset;
}

static int
lsarpc_dissect_element_lsa_DATA_BUF_PTR_buf_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_DATA_BUF(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_DATA_BUF_PTR_buf,0);

	return offset;
}

int
lsarpc_dissect_struct_lsa_DATA_BUF_PTR(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_)
{
	proto_item *item = NULL;
	proto_tree *tree = NULL;

	int old_offset;

	ALIGN_TO_5_BYTES;

	old_offset = offset;

	if (parent_tree) {
		item = proto_tree_add_item(parent_tree, hf_index, tvb, offset, -1, ENC_NA);
		tree = proto_item_add_subtree(item, ett_lsarpc_lsa_DATA_BUF_PTR);
	}
	
	offset = lsarpc_dissect_element_lsa_DATA_BUF_PTR_buf(tvb, offset, pinfo, tree, di, drep);


	proto_item_set_len(item, offset-old_offset);


	if (di->call_data->flags & DCERPC_IS_NDR64) {
		ALIGN_TO_5_BYTES;
	}

	return offset;
}


/* IDL: struct { */
/* IDL: 	[unique(1)] [charset(UTF16)] uint16 *name; */
/* IDL: } */

static int
lsarpc_dissect_element_lsa_RightAttribute_name(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_embedded_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_RightAttribute_name_, NDR_POINTER_UNIQUE, "Pointer to Name (uint16)",hf_lsarpc_lsa_RightAttribute_name);

	return offset;
}

static int
lsarpc_dissect_element_lsa_RightAttribute_name_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	char *data;

	offset = dissect_ndr_cvstring(tvb, offset, pinfo, tree, di, drep, sizeof(guint16), hf_lsarpc_lsa_RightAttribute_name, FALSE, &data);
	proto_item_append_text(tree, ": %s", data);

	return offset;
}

int
lsarpc_dissect_struct_lsa_RightAttribute(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_)
{
	proto_item *item = NULL;
	proto_tree *tree = NULL;

	int old_offset;

	ALIGN_TO_5_BYTES;

	old_offset = offset;

	if (parent_tree) {
		item = proto_tree_add_item(parent_tree, hf_index, tvb, offset, -1, ENC_NA);
		tree = proto_item_add_subtree(item, ett_lsarpc_lsa_RightAttribute);
	}
	
	offset = lsarpc_dissect_element_lsa_RightAttribute_name(tvb, offset, pinfo, tree, di, drep);


	proto_item_set_len(item, offset-old_offset);


	if (di->call_data->flags & DCERPC_IS_NDR64) {
		ALIGN_TO_5_BYTES;
	}

	return offset;
}


/* IDL: struct { */
/* IDL: 	uint32 count; */
/* IDL: 	[unique(1)] [size_is(count)] lsa_StringLarge *names; */
/* IDL: } */

static int
lsarpc_dissect_element_lsa_RightSet_count(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_RightSet_count, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_RightSet_names(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_embedded_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_RightSet_names_, NDR_POINTER_UNIQUE, "Pointer to Names (lsa_StringLarge)",hf_lsarpc_lsa_RightSet_names);

	return offset;
}

static int
lsarpc_dissect_element_lsa_RightSet_names_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_ucarray(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_RightSet_names__);

	return offset;
}

static int
lsarpc_dissect_element_lsa_RightSet_names__(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_StringLarge(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_RightSet_names,0);

	return offset;
}

int
lsarpc_dissect_struct_lsa_RightSet(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_)
{
	proto_item *item = NULL;
	proto_tree *tree = NULL;

	int old_offset;

	ALIGN_TO_5_BYTES;

	old_offset = offset;

	if (parent_tree) {
		item = proto_tree_add_item(parent_tree, hf_index, tvb, offset, -1, ENC_NA);
		tree = proto_item_add_subtree(item, ett_lsarpc_lsa_RightSet);
	}
	
	offset = lsarpc_dissect_element_lsa_RightSet_count(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_RightSet_names(tvb, offset, pinfo, tree, di, drep);


	proto_item_set_len(item, offset-old_offset);


	if (di->call_data->flags & DCERPC_IS_NDR64) {
		ALIGN_TO_5_BYTES;
	}

	return offset;
}


/* IDL: struct { */
/* IDL: 	[unique(1)] lsa_String *string; */
/* IDL: } */

static int
lsarpc_dissect_element_lsa_StringPointer_string(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_embedded_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_StringPointer_string_, NDR_POINTER_UNIQUE, "Pointer to String (lsa_String)",hf_lsarpc_lsa_StringPointer_string);

	return offset;
}

static int
lsarpc_dissect_element_lsa_StringPointer_string_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_String(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_StringPointer_string,0);

	return offset;
}

int
lsarpc_dissect_struct_lsa_StringPointer(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_)
{
	proto_item *item = NULL;
	proto_tree *tree = NULL;

	int old_offset;

	ALIGN_TO_5_BYTES;

	old_offset = offset;

	if (parent_tree) {
		item = proto_tree_add_item(parent_tree, hf_index, tvb, offset, -1, ENC_NA);
		tree = proto_item_add_subtree(item, ett_lsarpc_lsa_StringPointer);
	}
	
	offset = lsarpc_dissect_element_lsa_StringPointer_string(tvb, offset, pinfo, tree, di, drep);


	proto_item_set_len(item, offset-old_offset);


	if (di->call_data->flags & DCERPC_IS_NDR64) {
		ALIGN_TO_5_BYTES;
	}

	return offset;
}


/* IDL: struct { */
/* IDL: 	uint32 count; */
/* IDL: 	[unique(1)] [size_is(count)] lsa_TrustDomainInfoInfoEx *domains; */
/* IDL: } */

static int
lsarpc_dissect_element_lsa_DomainListEx_count(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_DomainListEx_count, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_DomainListEx_domains(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_embedded_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_DomainListEx_domains_, NDR_POINTER_UNIQUE, "Pointer to Domains (lsa_TrustDomainInfoInfoEx)",hf_lsarpc_lsa_DomainListEx_domains);

	return offset;
}

static int
lsarpc_dissect_element_lsa_DomainListEx_domains_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_ucarray(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_DomainListEx_domains__);

	return offset;
}

static int
lsarpc_dissect_element_lsa_DomainListEx_domains__(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_TrustDomainInfoInfoEx(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_DomainListEx_domains,0);

	return offset;
}

int
lsarpc_dissect_struct_lsa_DomainListEx(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_)
{
	proto_item *item = NULL;
	proto_tree *tree = NULL;

	int old_offset;

	ALIGN_TO_5_BYTES;

	old_offset = offset;

	if (parent_tree) {
		item = proto_tree_add_item(parent_tree, hf_index, tvb, offset, -1, ENC_NA);
		tree = proto_item_add_subtree(item, ett_lsarpc_lsa_DomainListEx);
	}
	
	offset = lsarpc_dissect_element_lsa_DomainListEx_count(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_DomainListEx_domains(tvb, offset, pinfo, tree, di, drep);


	proto_item_set_len(item, offset-old_offset);


	if (di->call_data->flags & DCERPC_IS_NDR64) {
		ALIGN_TO_5_BYTES;
	}

	return offset;
}


/* IDL: struct { */
/* IDL: 	uint32 enforce_restrictions; */
/* IDL: 	hyper service_tkt_lifetime; */
/* IDL: 	hyper user_tkt_lifetime; */
/* IDL: 	hyper user_tkt_renewaltime; */
/* IDL: 	hyper clock_skew; */
/* IDL: 	hyper unknown6; */
/* IDL: } */

static int
lsarpc_dissect_element_lsa_DomainInfoKerberos_enforce_restrictions(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_DomainInfoKerberos_enforce_restrictions, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_DomainInfoKerberos_service_tkt_lifetime(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset=cnf_dissect_hyper(tvb, offset, pinfo, tree, di, drep, 0, hf_lsarpc_lsa_DomainInfoKerberos_service_tkt_lifetime);

	return offset;
}

static int
lsarpc_dissect_element_lsa_DomainInfoKerberos_user_tkt_lifetime(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset=cnf_dissect_hyper(tvb, offset, pinfo, tree, di, drep, 0, hf_lsarpc_lsa_DomainInfoKerberos_user_tkt_lifetime);

	return offset;
}

static int
lsarpc_dissect_element_lsa_DomainInfoKerberos_user_tkt_renewaltime(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset=cnf_dissect_hyper(tvb, offset, pinfo, tree, di, drep, 0, hf_lsarpc_lsa_DomainInfoKerberos_user_tkt_renewaltime);

	return offset;
}

static int
lsarpc_dissect_element_lsa_DomainInfoKerberos_clock_skew(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset=cnf_dissect_hyper(tvb, offset, pinfo, tree, di, drep, 0, hf_lsarpc_lsa_DomainInfoKerberos_clock_skew);

	return offset;
}

static int
lsarpc_dissect_element_lsa_DomainInfoKerberos_unknown6(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset=cnf_dissect_hyper(tvb, offset, pinfo, tree, di, drep, 0, hf_lsarpc_lsa_DomainInfoKerberos_unknown6);

	return offset;
}

int
lsarpc_dissect_struct_lsa_DomainInfoKerberos(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_)
{
	proto_item *item = NULL;
	proto_tree *tree = NULL;

	int old_offset;

	ALIGN_TO_8_BYTES;

	old_offset = offset;

	if (parent_tree) {
		item = proto_tree_add_item(parent_tree, hf_index, tvb, offset, -1, ENC_NA);
		tree = proto_item_add_subtree(item, ett_lsarpc_lsa_DomainInfoKerberos);
	}
	
	offset = lsarpc_dissect_element_lsa_DomainInfoKerberos_enforce_restrictions(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_DomainInfoKerberos_service_tkt_lifetime(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_DomainInfoKerberos_user_tkt_lifetime(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_DomainInfoKerberos_user_tkt_renewaltime(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_DomainInfoKerberos_clock_skew(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_DomainInfoKerberos_unknown6(tvb, offset, pinfo, tree, di, drep);


	proto_item_set_len(item, offset-old_offset);


	if (di->call_data->flags & DCERPC_IS_NDR64) {
		ALIGN_TO_8_BYTES;
	}

	return offset;
}


/* IDL: struct { */
/* IDL: 	uint32 blob_size; */
/* IDL: 	[unique(1)] [size_is(blob_size)] uint8 *efs_blob; */
/* IDL: } */

static int
lsarpc_dissect_element_lsa_DomainInfoEfs_blob_size(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_DomainInfoEfs_blob_size, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_DomainInfoEfs_efs_blob(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_embedded_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_DomainInfoEfs_efs_blob_, NDR_POINTER_UNIQUE, "Pointer to Efs Blob (uint8)",hf_lsarpc_lsa_DomainInfoEfs_efs_blob);

	return offset;
}

static int
lsarpc_dissect_element_lsa_DomainInfoEfs_efs_blob__(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint8(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_DomainInfoEfs_efs_blob, 0);

	return offset;
}

int
lsarpc_dissect_struct_lsa_DomainInfoEfs(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_)
{
	proto_item *item = NULL;
	proto_tree *tree = NULL;

	int old_offset;

	ALIGN_TO_5_BYTES;

	old_offset = offset;

	if (parent_tree) {
		item = proto_tree_add_item(parent_tree, hf_index, tvb, offset, -1, ENC_NA);
		tree = proto_item_add_subtree(item, ett_lsarpc_lsa_DomainInfoEfs);
	}
	
	offset = lsarpc_dissect_element_lsa_DomainInfoEfs_blob_size(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_DomainInfoEfs_efs_blob(tvb, offset, pinfo, tree, di, drep);


	proto_item_set_len(item, offset-old_offset);


	if (di->call_data->flags & DCERPC_IS_NDR64) {
		ALIGN_TO_5_BYTES;
	}

	return offset;
}


/* IDL: enum { */
/* IDL: 	LSA_DOMAIN_INFO_POLICY_QOS=1, */
/* IDL: 	LSA_DOMAIN_INFO_POLICY_EFS=2, */
/* IDL: 	LSA_DOMAIN_INFO_POLICY_KERBEROS=3, */
/* IDL: } */

int
lsarpc_dissect_enum_lsa_DomainInfoEnum(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 *param _U_)
{
	guint1632 parameter=0;
	if(param){
		parameter=(guint1632)*param;
	}
	offset = dissect_ndr_uint1632(tvb, offset, pinfo, tree, di, drep, hf_index, &parameter);
	if(param){
		*param=(guint32)parameter;
	}
	return offset;
}


/* IDL: [switch_type(uint16)] union { */
/* IDL: [case(LSA_DOMAIN_INFO_POLICY_EFS)] [case(LSA_DOMAIN_INFO_POLICY_EFS)] lsa_DomainInfoEfs efs_info; */
/* IDL: [case(LSA_DOMAIN_INFO_POLICY_KERBEROS)] [case(LSA_DOMAIN_INFO_POLICY_KERBEROS)] lsa_DomainInfoKerberos kerberos_info; */
/* IDL: } */

static int
lsarpc_dissect_element_lsa_DomainInformationPolicy_efs_info(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_DomainInfoEfs(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_DomainInformationPolicy_efs_info,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_DomainInformationPolicy_kerberos_info(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_DomainInfoKerberos(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_DomainInformationPolicy_kerberos_info,0);

	return offset;
}

static int
lsarpc_dissect_lsa_DomainInformationPolicy(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_)
{
	proto_item *item = NULL;
	proto_tree *tree = NULL;
	int old_offset;
	guint16 level;

	old_offset = offset;
	if (parent_tree) {
		item = proto_tree_add_text(parent_tree, tvb, offset, -1, "lsa_DomainInformationPolicy");
		tree = proto_item_add_subtree(item, ett_lsarpc_lsa_DomainInformationPolicy);
	}

	offset = dissect_ndr_uint16(tvb, offset, pinfo, tree, di, drep, hf_index, &level);
	ALIGN_TO_8_BYTES;

	switch(level) {
		case LSA_DOMAIN_INFO_POLICY_EFS:
			offset = lsarpc_dissect_element_lsa_DomainInformationPolicy_efs_info(tvb, offset, pinfo, tree, di, drep);
		break;

		case LSA_DOMAIN_INFO_POLICY_KERBEROS:
			offset = lsarpc_dissect_element_lsa_DomainInformationPolicy_kerberos_info(tvb, offset, pinfo, tree, di, drep);
		break;
	}
	proto_item_set_len(item, offset-old_offset);


	return offset;
}

/* IDL: struct { */
/* IDL: 	lsa_SidType sid_type; */
/* IDL: 	lsa_String name; */
/* IDL: 	uint32 sid_index; */
/* IDL: 	uint32 unknown; */
/* IDL: } */

static int
lsarpc_dissect_element_lsa_TranslatedName2_sid_type(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_enum_lsa_SidType(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_TranslatedName2_sid_type, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_TranslatedName2_name(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_String(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_TranslatedName2_name,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_TranslatedName2_sid_index(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_TranslatedName2_sid_index, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_TranslatedName2_unknown(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_TranslatedName2_unknown, 0);

	return offset;
}

int
lsarpc_dissect_struct_lsa_TranslatedName2(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_)
{
	proto_item *item = NULL;
	proto_tree *tree = NULL;

	int old_offset;

	ALIGN_TO_5_BYTES;

	old_offset = offset;

	if (parent_tree) {
		item = proto_tree_add_item(parent_tree, hf_index, tvb, offset, -1, ENC_NA);
		tree = proto_item_add_subtree(item, ett_lsarpc_lsa_TranslatedName2);
	}
	
	offset = lsarpc_dissect_element_lsa_TranslatedName2_sid_type(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_TranslatedName2_name(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_TranslatedName2_sid_index(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_TranslatedName2_unknown(tvb, offset, pinfo, tree, di, drep);


	proto_item_set_len(item, offset-old_offset);


	if (di->call_data->flags & DCERPC_IS_NDR64) {
		ALIGN_TO_5_BYTES;
	}

	return offset;
}


/* IDL: struct { */
/* IDL: 	[range(0,1000)] uint32 count; */
/* IDL: 	[unique(1)] [size_is(count)] lsa_TranslatedName2 *names; */
/* IDL: } */

static int
lsarpc_dissect_element_lsa_TransNameArray2_count(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_TransNameArray2_count, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_TransNameArray2_names(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_embedded_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_TransNameArray2_names_, NDR_POINTER_UNIQUE, "Pointer to Names (lsa_TranslatedName2)",hf_lsarpc_lsa_TransNameArray2_names);

	return offset;
}

static int
lsarpc_dissect_element_lsa_TransNameArray2_names_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_ucarray(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_TransNameArray2_names__);

	return offset;
}

static int
lsarpc_dissect_element_lsa_TransNameArray2_names__(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_TranslatedName2(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_TransNameArray2_names,0);

	return offset;
}

int
lsarpc_dissect_struct_lsa_TransNameArray2(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_)
{
	proto_item *item = NULL;
	proto_tree *tree = NULL;

	int old_offset;

	ALIGN_TO_5_BYTES;

	old_offset = offset;

	if (parent_tree) {
		item = proto_tree_add_item(parent_tree, hf_index, tvb, offset, -1, ENC_NA);
		tree = proto_item_add_subtree(item, ett_lsarpc_lsa_TransNameArray2);
	}
	
	offset = lsarpc_dissect_element_lsa_TransNameArray2_count(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_TransNameArray2_names(tvb, offset, pinfo, tree, di, drep);


	proto_item_set_len(item, offset-old_offset);


	if (di->call_data->flags & DCERPC_IS_NDR64) {
		ALIGN_TO_5_BYTES;
	}

	return offset;
}


/* IDL: struct { */
/* IDL: 	lsa_SidType sid_type; */
/* IDL: 	uint32 rid; */
/* IDL: 	uint32 sid_index; */
/* IDL: 	uint32 unknown; */
/* IDL: } */

static int
lsarpc_dissect_element_lsa_TranslatedSid2_sid_type(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_enum_lsa_SidType(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_TranslatedSid2_sid_type, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_TranslatedSid2_rid(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_TranslatedSid2_rid, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_TranslatedSid2_sid_index(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_TranslatedSid2_sid_index, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_TranslatedSid2_unknown(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_TranslatedSid2_unknown, 0);

	return offset;
}

int
lsarpc_dissect_struct_lsa_TranslatedSid2(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_)
{
	proto_item *item = NULL;
	proto_tree *tree = NULL;

	int old_offset;

	ALIGN_TO_4_BYTES;

	old_offset = offset;

	if (parent_tree) {
		item = proto_tree_add_item(parent_tree, hf_index, tvb, offset, -1, ENC_NA);
		tree = proto_item_add_subtree(item, ett_lsarpc_lsa_TranslatedSid2);
	}
	
	offset = lsarpc_dissect_element_lsa_TranslatedSid2_sid_type(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_TranslatedSid2_rid(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_TranslatedSid2_sid_index(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_TranslatedSid2_unknown(tvb, offset, pinfo, tree, di, drep);


	proto_item_set_len(item, offset-old_offset);


	if (di->call_data->flags & DCERPC_IS_NDR64) {
		ALIGN_TO_4_BYTES;
	}

	return offset;
}


/* IDL: struct { */
/* IDL: 	[range(0,1000)] uint32 count; */
/* IDL: 	[unique(1)] [size_is(count)] lsa_TranslatedSid2 *sids; */
/* IDL: } */

static int
lsarpc_dissect_element_lsa_TransSidArray2_count(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_TransSidArray2_count, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_TransSidArray2_sids(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_embedded_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_TransSidArray2_sids_, NDR_POINTER_UNIQUE, "Pointer to Sids (lsa_TranslatedSid2)",hf_lsarpc_lsa_TransSidArray2_sids);

	return offset;
}

static int
lsarpc_dissect_element_lsa_TransSidArray2_sids_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_ucarray(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_TransSidArray2_sids__);

	return offset;
}

static int
lsarpc_dissect_element_lsa_TransSidArray2_sids__(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_TranslatedSid2(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_TransSidArray2_sids,0);

	return offset;
}

int
lsarpc_dissect_struct_lsa_TransSidArray2(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_)
{
	proto_item *item = NULL;
	proto_tree *tree = NULL;

	int old_offset;

	ALIGN_TO_5_BYTES;

	old_offset = offset;

	if (parent_tree) {
		item = proto_tree_add_item(parent_tree, hf_index, tvb, offset, -1, ENC_NA);
		tree = proto_item_add_subtree(item, ett_lsarpc_lsa_TransSidArray2);
	}
	
	offset = lsarpc_dissect_element_lsa_TransSidArray2_count(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_TransSidArray2_sids(tvb, offset, pinfo, tree, di, drep);


	proto_item_set_len(item, offset-old_offset);


	if (di->call_data->flags & DCERPC_IS_NDR64) {
		ALIGN_TO_5_BYTES;
	}

	return offset;
}


/* IDL: struct { */
/* IDL: 	lsa_SidType sid_type; */
/* IDL: 	[unique(1)] dom_sid2 *sid; */
/* IDL: 	uint32 sid_index; */
/* IDL: 	uint32 unknown; */
/* IDL: } */

static int
lsarpc_dissect_element_lsa_TranslatedSid3_sid_type(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_enum_lsa_SidType(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_TranslatedSid3_sid_type, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_TranslatedSid3_sid(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_embedded_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_TranslatedSid3_sid_, NDR_POINTER_UNIQUE, "Pointer to Sid (dom_sid2)",hf_lsarpc_lsa_TranslatedSid3_sid);

	return offset;
}

static int
lsarpc_dissect_element_lsa_TranslatedSid3_sid_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_dom_sid2(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_TranslatedSid3_sid,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_TranslatedSid3_sid_index(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_TranslatedSid3_sid_index, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_TranslatedSid3_unknown(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_TranslatedSid3_unknown, 0);

	return offset;
}

int
lsarpc_dissect_struct_lsa_TranslatedSid3(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_)
{
	proto_item *item = NULL;
	proto_tree *tree = NULL;

	int old_offset;

	ALIGN_TO_5_BYTES;

	old_offset = offset;

	if (parent_tree) {
		item = proto_tree_add_item(parent_tree, hf_index, tvb, offset, -1, ENC_NA);
		tree = proto_item_add_subtree(item, ett_lsarpc_lsa_TranslatedSid3);
	}
	
	offset = lsarpc_dissect_element_lsa_TranslatedSid3_sid_type(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_TranslatedSid3_sid(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_TranslatedSid3_sid_index(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_TranslatedSid3_unknown(tvb, offset, pinfo, tree, di, drep);


	proto_item_set_len(item, offset-old_offset);


	if (di->call_data->flags & DCERPC_IS_NDR64) {
		ALIGN_TO_5_BYTES;
	}

	return offset;
}


/* IDL: struct { */
/* IDL: 	[range(0,1000)] uint32 count; */
/* IDL: 	[unique(1)] [size_is(count)] lsa_TranslatedSid3 *sids; */
/* IDL: } */

static int
lsarpc_dissect_element_lsa_TransSidArray3_count(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_TransSidArray3_count, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_TransSidArray3_sids(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_embedded_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_TransSidArray3_sids_, NDR_POINTER_UNIQUE, "Pointer to Sids (lsa_TranslatedSid3)",hf_lsarpc_lsa_TransSidArray3_sids);

	return offset;
}

static int
lsarpc_dissect_element_lsa_TransSidArray3_sids_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_ucarray(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_TransSidArray3_sids__);

	return offset;
}

static int
lsarpc_dissect_element_lsa_TransSidArray3_sids__(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_TranslatedSid3(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_TransSidArray3_sids,0);

	return offset;
}

int
lsarpc_dissect_struct_lsa_TransSidArray3(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_)
{
	proto_item *item = NULL;
	proto_tree *tree = NULL;

	int old_offset;

	ALIGN_TO_5_BYTES;

	old_offset = offset;

	if (parent_tree) {
		item = proto_tree_add_item(parent_tree, hf_index, tvb, offset, -1, ENC_NA);
		tree = proto_item_add_subtree(item, ett_lsarpc_lsa_TransSidArray3);
	}
	
	offset = lsarpc_dissect_element_lsa_TransSidArray3_count(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_TransSidArray3_sids(tvb, offset, pinfo, tree, di, drep);


	proto_item_set_len(item, offset-old_offset);


	if (di->call_data->flags & DCERPC_IS_NDR64) {
		ALIGN_TO_5_BYTES;
	}

	return offset;
}


/* IDL: struct { */
/* IDL: 	[range(0,131072)] uint32 length; */
/* IDL: 	[unique(1)] [size_is(length)] uint8 *data; */
/* IDL: } */

static int
lsarpc_dissect_element_lsa_ForestTrustBinaryData_length(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_ForestTrustBinaryData_length, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_ForestTrustBinaryData_data(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_embedded_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_ForestTrustBinaryData_data_, NDR_POINTER_UNIQUE, "Pointer to Data (uint8)",hf_lsarpc_lsa_ForestTrustBinaryData_data);

	return offset;
}

static int
lsarpc_dissect_element_lsa_ForestTrustBinaryData_data_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_ucarray(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_ForestTrustBinaryData_data__);

	return offset;
}

static int
lsarpc_dissect_element_lsa_ForestTrustBinaryData_data__(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint8(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_ForestTrustBinaryData_data, 0);

	return offset;
}

int
lsarpc_dissect_struct_lsa_ForestTrustBinaryData(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_)
{
	proto_item *item = NULL;
	proto_tree *tree = NULL;

	int old_offset;

	ALIGN_TO_5_BYTES;

	old_offset = offset;

	if (parent_tree) {
		item = proto_tree_add_item(parent_tree, hf_index, tvb, offset, -1, ENC_NA);
		tree = proto_item_add_subtree(item, ett_lsarpc_lsa_ForestTrustBinaryData);
	}
	
	offset = lsarpc_dissect_element_lsa_ForestTrustBinaryData_length(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_ForestTrustBinaryData_data(tvb, offset, pinfo, tree, di, drep);


	proto_item_set_len(item, offset-old_offset);


	if (di->call_data->flags & DCERPC_IS_NDR64) {
		ALIGN_TO_5_BYTES;
	}

	return offset;
}


/* IDL: struct { */
/* IDL: 	[unique(1)] dom_sid2 *domain_sid; */
/* IDL: 	lsa_StringLarge dns_domain_name; */
/* IDL: 	lsa_StringLarge netbios_domain_name; */
/* IDL: } */

static int
lsarpc_dissect_element_lsa_ForestTrustDomainInfo_domain_sid(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_embedded_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_ForestTrustDomainInfo_domain_sid_, NDR_POINTER_UNIQUE, "Pointer to Domain Sid (dom_sid2)",hf_lsarpc_lsa_ForestTrustDomainInfo_domain_sid);

	return offset;
}

static int
lsarpc_dissect_element_lsa_ForestTrustDomainInfo_domain_sid_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_dom_sid2(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_ForestTrustDomainInfo_domain_sid,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_ForestTrustDomainInfo_dns_domain_name(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_StringLarge(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_ForestTrustDomainInfo_dns_domain_name,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_ForestTrustDomainInfo_netbios_domain_name(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_StringLarge(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_ForestTrustDomainInfo_netbios_domain_name,0);

	return offset;
}

int
lsarpc_dissect_struct_lsa_ForestTrustDomainInfo(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_)
{
	proto_item *item = NULL;
	proto_tree *tree = NULL;

	int old_offset;

	ALIGN_TO_5_BYTES;

	old_offset = offset;

	if (parent_tree) {
		item = proto_tree_add_item(parent_tree, hf_index, tvb, offset, -1, ENC_NA);
		tree = proto_item_add_subtree(item, ett_lsarpc_lsa_ForestTrustDomainInfo);
	}
	
	offset = lsarpc_dissect_element_lsa_ForestTrustDomainInfo_domain_sid(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_ForestTrustDomainInfo_dns_domain_name(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_ForestTrustDomainInfo_netbios_domain_name(tvb, offset, pinfo, tree, di, drep);


	proto_item_set_len(item, offset-old_offset);


	if (di->call_data->flags & DCERPC_IS_NDR64) {
		ALIGN_TO_5_BYTES;
	}

	return offset;
}


/* IDL: [switch_type(uint32)] union { */
/* IDL: [case(LSA_FOREST_TRUST_TOP_LEVEL_NAME)] [case(LSA_FOREST_TRUST_TOP_LEVEL_NAME)] lsa_String top_level_name; */
/* IDL: [case(LSA_FOREST_TRUST_TOP_LEVEL_NAME_EX)] [case(LSA_FOREST_TRUST_TOP_LEVEL_NAME_EX)] lsa_StringLarge top_level_name_ex; */
/* IDL: [case(LSA_FOREST_TRUST_DOMAIN_INFO)] [case(LSA_FOREST_TRUST_DOMAIN_INFO)] lsa_ForestTrustDomainInfo domain_info; */
/* IDL: [default] ; */
/* IDL: } */

static int
lsarpc_dissect_element_lsa_ForestTrustData_top_level_name(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_String(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_ForestTrustData_top_level_name,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_ForestTrustData_top_level_name_ex(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_StringLarge(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_ForestTrustData_top_level_name_ex,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_ForestTrustData_domain_info(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_ForestTrustDomainInfo(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_ForestTrustData_domain_info,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_ForestTrustData_data(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_ForestTrustBinaryData(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_ForestTrustData_data,0);

	return offset;
}

static int
lsarpc_dissect_lsa_ForestTrustData(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_)
{
	proto_item *item = NULL;
	proto_tree *tree = NULL;
	int old_offset;
	guint32 level;

	old_offset = offset;
	if (parent_tree) {
		item = proto_tree_add_text(parent_tree, tvb, offset, -1, "lsa_ForestTrustData");
		tree = proto_item_add_subtree(item, ett_lsarpc_lsa_ForestTrustData);
	}

	offset = dissect_ndr_uint32(tvb, offset, pinfo, tree, di, drep, hf_index, &level);
	ALIGN_TO_5_BYTES;

	switch(level) {
		case LSA_FOREST_TRUST_TOP_LEVEL_NAME:
			offset = lsarpc_dissect_element_lsa_ForestTrustData_top_level_name(tvb, offset, pinfo, tree, di, drep);
		break;

		case LSA_FOREST_TRUST_TOP_LEVEL_NAME_EX:
			offset = lsarpc_dissect_element_lsa_ForestTrustData_top_level_name_ex(tvb, offset, pinfo, tree, di, drep);
		break;

		case LSA_FOREST_TRUST_DOMAIN_INFO:
			offset = lsarpc_dissect_element_lsa_ForestTrustData_domain_info(tvb, offset, pinfo, tree, di, drep);
		break;

		default:
			offset = lsarpc_dissect_element_lsa_ForestTrustData_data(tvb, offset, pinfo, tree, di, drep);
		break;
	}
	proto_item_set_len(item, offset-old_offset);


	return offset;
}

/* IDL: enum { */
/* IDL: 	LSA_FOREST_TRUST_TOP_LEVEL_NAME=0, */
/* IDL: 	LSA_FOREST_TRUST_TOP_LEVEL_NAME_EX=1, */
/* IDL: 	LSA_FOREST_TRUST_DOMAIN_INFO=2, */
/* IDL: 	LSA_FOREST_TRUST_RECORD_TYPE_LAST=3, */
/* IDL: } */

int
lsarpc_dissect_enum_lsa_ForestTrustRecordType(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 *param _U_)
{
	guint32 parameter=0;
	if(param){
		parameter=(guint32)*param;
	}
	offset = dissect_ndr_uint32(tvb, offset, pinfo, tree, di, drep, hf_index, &parameter);
	if(param){
		*param=(guint32)parameter;
	}
	return offset;
}


/* IDL: struct { */
/* IDL: 	uint32 flags; */
/* IDL: 	lsa_ForestTrustRecordType level; */
/* IDL: 	hyper unknown; */
/* IDL: 	[switch_is(level)] lsa_ForestTrustData forest_trust_data; */
/* IDL: } */

static int
lsarpc_dissect_element_lsa_ForestTrustRecord_flags(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_ForestTrustRecord_flags, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_ForestTrustRecord_level(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, guint32 *level)
{
	offset = lsarpc_dissect_enum_lsa_ForestTrustRecordType(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_ForestTrustRecord_level, level);

	return offset;
}

static int
lsarpc_dissect_element_lsa_ForestTrustRecord_unknown(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset=cnf_dissect_hyper(tvb, offset, pinfo, tree, di, drep, 0, hf_lsarpc_lsa_ForestTrustRecord_unknown);

	return offset;
}

static int
lsarpc_dissect_element_lsa_ForestTrustRecord_forest_trust_data(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, guint32 *level)
{
	offset = lsarpc_dissect_lsa_ForestTrustData(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_ForestTrustRecord_forest_trust_data, *level);

	return offset;
}

int
lsarpc_dissect_struct_lsa_ForestTrustRecord(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_)
{
	guint32 level;
	proto_item *item = NULL;
	proto_tree *tree = NULL;

	int old_offset;

	ALIGN_TO_8_BYTES;

	old_offset = offset;

	if (parent_tree) {
		item = proto_tree_add_item(parent_tree, hf_index, tvb, offset, -1, ENC_NA);
		tree = proto_item_add_subtree(item, ett_lsarpc_lsa_ForestTrustRecord);
	}
	
	offset = lsarpc_dissect_element_lsa_ForestTrustRecord_flags(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_ForestTrustRecord_level(tvb, offset, pinfo, tree, di, drep, &level);

	offset = lsarpc_dissect_element_lsa_ForestTrustRecord_unknown(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_ForestTrustRecord_forest_trust_data(tvb, offset, pinfo, tree, di, drep, &level);


	proto_item_set_len(item, offset-old_offset);


	if (di->call_data->flags & DCERPC_IS_NDR64) {
		ALIGN_TO_8_BYTES;
	}

	return offset;
}


/* IDL: struct { */
/* IDL: 	[range(0,4000)] uint32 count; */
/* IDL: 	[unique(1)] [size_is(count)] lsa_ForestTrustRecord **entries; */
/* IDL: } */

static int
lsarpc_dissect_element_lsa_ForestTrustInformation_count(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_ForestTrustInformation_count, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_ForestTrustInformation_entries(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_embedded_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_ForestTrustInformation_entries_, NDR_POINTER_UNIQUE, "Pointer to Entries (lsa_ForestTrustRecord)",hf_lsarpc_lsa_ForestTrustInformation_entries);

	return offset;
}

static int
lsarpc_dissect_element_lsa_ForestTrustInformation_entries_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_ucarray(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_ForestTrustInformation_entries__);

	return offset;
}

static int
lsarpc_dissect_element_lsa_ForestTrustInformation_entries__(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_embedded_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_ForestTrustInformation_entries___, NDR_POINTER_UNIQUE, "Pointer to Entries (lsa_ForestTrustRecord)",hf_lsarpc_lsa_ForestTrustInformation_entries);

	return offset;
}

static int
lsarpc_dissect_element_lsa_ForestTrustInformation_entries___(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_ForestTrustRecord(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_ForestTrustInformation_entries,0);

	return offset;
}

int
lsarpc_dissect_struct_lsa_ForestTrustInformation(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_)
{
	proto_item *item = NULL;
	proto_tree *tree = NULL;

	int old_offset;

	ALIGN_TO_5_BYTES;

	old_offset = offset;

	if (parent_tree) {
		item = proto_tree_add_item(parent_tree, hf_index, tvb, offset, -1, ENC_NA);
		tree = proto_item_add_subtree(item, ett_lsarpc_lsa_ForestTrustInformation);
	}
	
	offset = lsarpc_dissect_element_lsa_ForestTrustInformation_count(tvb, offset, pinfo, tree, di, drep);

	offset = lsarpc_dissect_element_lsa_ForestTrustInformation_entries(tvb, offset, pinfo, tree, di, drep);


	proto_item_set_len(item, offset-old_offset);


	if (di->call_data->flags & DCERPC_IS_NDR64) {
		ALIGN_TO_5_BYTES;
	}

	return offset;
}

static int
lsarpc_dissect_element_lsa_Close_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_Close_handle_, NDR_POINTER_REF, "Pointer to Handle (policy_handle)",hf_lsarpc_lsa_Close_handle);

	return offset;
}

static int
lsarpc_dissect_element_lsa_Close_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_policy_hnd(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_Close_handle, PIDL_POLHND_CLOSE);

	return offset;
}

/* IDL: NTSTATUS lsa_Close( */
/* IDL: [out] [ref] [in] policy_handle *handle */
/* IDL: ); */

static int
lsarpc_dissect_lsa_Close_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_Close";
	offset = lsarpc_dissect_element_lsa_Close_handle(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);

	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_Close_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_Close";
	offset = lsarpc_dissect_element_lsa_Close_handle(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	return offset;
}

static int
lsarpc_dissect_element_lsa_Delete_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_Delete_handle_, NDR_POINTER_REF, "Pointer to Handle (policy_handle)",hf_lsarpc_lsa_Delete_handle);

	return offset;
}

static int
lsarpc_dissect_element_lsa_Delete_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_policy_hnd(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_Delete_handle, PIDL_POLHND_CLOSE);

	return offset;
}

/* IDL: NTSTATUS lsa_Delete( */
/* IDL: [ref] [in] policy_handle *handle */
/* IDL: ); */

static int
lsarpc_dissect_lsa_Delete_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_Delete";
	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_Delete_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_Delete";
	offset = lsarpc_dissect_element_lsa_Delete_handle(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	return offset;
}

static int
lsarpc_dissect_element_lsa_EnumPrivs_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_EnumPrivs_handle_, NDR_POINTER_REF, "Pointer to Handle (policy_handle)",hf_lsarpc_lsa_EnumPrivs_handle);

	return offset;
}

static int
lsarpc_dissect_element_lsa_EnumPrivs_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_policy_hnd(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_EnumPrivs_handle, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_EnumPrivs_resume_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_EnumPrivs_resume_handle_, NDR_POINTER_REF, "Pointer to Resume Handle (uint32)",hf_lsarpc_lsa_EnumPrivs_resume_handle);

	return offset;
}

static int
lsarpc_dissect_element_lsa_EnumPrivs_resume_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_EnumPrivs_resume_handle, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_EnumPrivs_max_count(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_EnumPrivs_max_count, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_EnumPrivs_privs(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_EnumPrivs_privs_, NDR_POINTER_REF, "Pointer to Privs (lsa_PrivArray)",hf_lsarpc_lsa_EnumPrivs_privs);

	return offset;
}

static int
lsarpc_dissect_element_lsa_EnumPrivs_privs_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_PrivArray(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_EnumPrivs_privs,0);

	return offset;
}

/* IDL: NTSTATUS lsa_EnumPrivs( */
/* IDL: [ref] [in] policy_handle *handle, */
/* IDL: [out] [ref] [in] uint32 *resume_handle, */
/* IDL: [in] uint32 max_count, */
/* IDL: [out] [ref] lsa_PrivArray *privs */
/* IDL: ); */

static int
lsarpc_dissect_lsa_EnumPrivs_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_EnumPrivs";
	offset = lsarpc_dissect_element_lsa_EnumPrivs_resume_handle(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);

	offset = lsarpc_dissect_element_lsa_EnumPrivs_privs(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);

	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_EnumPrivs_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_EnumPrivs";
	offset = lsarpc_dissect_element_lsa_EnumPrivs_handle(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_EnumPrivs_resume_handle(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_EnumPrivs_max_count(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	return offset;
}

static int
lsarpc_dissect_element_lsa_QuerySecurity_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_QuerySecurity_handle_, NDR_POINTER_REF, "Pointer to Handle (policy_handle)",hf_lsarpc_lsa_QuerySecurity_handle);

	return offset;
}

static int
lsarpc_dissect_element_lsa_QuerySecurity_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_policy_hnd(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_QuerySecurity_handle, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_QuerySecurity_sec_info(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_bitmap_security_secinfo(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_QuerySecurity_sec_info, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_QuerySecurity_sdbuf(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_QuerySecurity_sdbuf_, NDR_POINTER_UNIQUE, "Pointer to Sdbuf (sec_desc_buf)",hf_lsarpc_lsa_QuerySecurity_sdbuf);

	return offset;
}

static int
lsarpc_dissect_element_lsa_QuerySecurity_sdbuf_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset=cnf_dissect_sec_desc_buf(tvb, offset, pinfo, tree, di, drep);

	return offset;
}

/* IDL: NTSTATUS lsa_QuerySecurity( */
/* IDL: [ref] [in] policy_handle *handle, */
/* IDL: [in] security_secinfo sec_info, */
/* IDL: [out] [unique(1)] sec_desc_buf *sdbuf */
/* IDL: ); */

static int
lsarpc_dissect_lsa_QuerySecurity_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_QuerySecurity";
	offset = lsarpc_dissect_element_lsa_QuerySecurity_sdbuf(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);

	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_QuerySecurity_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_QuerySecurity";
	offset = lsarpc_dissect_element_lsa_QuerySecurity_handle(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_QuerySecurity_sec_info(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	return offset;
}

/* IDL: NTSTATUS lsa_SetSecObj( */
/* IDL:  */
/* IDL: ); */

static int
lsarpc_dissect_lsa_SetSecObj_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_SetSecObj";
	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_SetSecObj_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_SetSecObj";
	return offset;
}

/* IDL: NTSTATUS lsa_ChangePassword( */
/* IDL:  */
/* IDL: ); */

static int
lsarpc_dissect_lsa_ChangePassword_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_ChangePassword";
	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_ChangePassword_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_ChangePassword";
	return offset;
}

static int
lsarpc_dissect_element_lsa_OpenPolicy_system_name(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_OpenPolicy_system_name_, NDR_POINTER_UNIQUE, "Pointer to System Name (uint16)",hf_lsarpc_lsa_OpenPolicy_system_name);

	return offset;
}

static int
lsarpc_dissect_element_lsa_OpenPolicy_system_name_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint16(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_OpenPolicy_system_name, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_OpenPolicy_attr(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_OpenPolicy_attr_, NDR_POINTER_REF, "Pointer to Attr (lsa_ObjectAttribute)",hf_lsarpc_lsa_OpenPolicy_attr);

	return offset;
}

static int
lsarpc_dissect_element_lsa_OpenPolicy_attr_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_ObjectAttribute(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_OpenPolicy_attr,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_OpenPolicy_access_mask(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_bitmap_lsa_PolicyAccessMask(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_OpenPolicy_access_mask, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_OpenPolicy_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_OpenPolicy_handle_, NDR_POINTER_REF, "Pointer to Handle (policy_handle)",hf_lsarpc_lsa_OpenPolicy_handle);

	return offset;
}

static int
lsarpc_dissect_element_lsa_OpenPolicy_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_policy_hnd(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_OpenPolicy_handle, PIDL_POLHND_OPEN|PIDL_POLHND_TYPE_LSA_POLICY);

	return offset;
}

/* IDL: NTSTATUS lsa_OpenPolicy( */
/* IDL: [unique(1)] [in] uint16 *system_name, */
/* IDL: [ref] [in] lsa_ObjectAttribute *attr, */
/* IDL: [in] lsa_PolicyAccessMask access_mask, */
/* IDL: [out] [ref] policy_handle *handle */
/* IDL: ); */

static int
lsarpc_dissect_lsa_OpenPolicy_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_OpenPolicy";
	offset = lsarpc_dissect_element_lsa_OpenPolicy_handle(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);

	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_OpenPolicy_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_OpenPolicy";
	offset = lsarpc_dissect_element_lsa_OpenPolicy_system_name(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_OpenPolicy_attr(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_OpenPolicy_access_mask(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	return offset;
}

static int
lsarpc_dissect_element_lsa_QueryInfoPolicy_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_QueryInfoPolicy_handle_, NDR_POINTER_REF, "Pointer to Handle (policy_handle)",hf_lsarpc_lsa_QueryInfoPolicy_handle);

	return offset;
}

static int
lsarpc_dissect_element_lsa_QueryInfoPolicy_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_policy_hnd(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_QueryInfoPolicy_handle, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_QueryInfoPolicy_level(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_enum_lsa_PolicyInfo(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_QueryInfoPolicy_level, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_QueryInfoPolicy_info(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_QueryInfoPolicy_info_, NDR_POINTER_UNIQUE, "Pointer to Info (lsa_PolicyInformation)",hf_lsarpc_lsa_QueryInfoPolicy_info);

	return offset;
}

static int
lsarpc_dissect_element_lsa_QueryInfoPolicy_info_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_lsa_PolicyInformation(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_QueryInfoPolicy_info, 0);

	return offset;
}

/* IDL: NTSTATUS lsa_QueryInfoPolicy( */
/* IDL: [ref] [in] policy_handle *handle, */
/* IDL: [in] lsa_PolicyInfo level, */
/* IDL: [unique(1)] [out] [switch_is(level)] lsa_PolicyInformation *info */
/* IDL: ); */

static int
lsarpc_dissect_lsa_QueryInfoPolicy_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_QueryInfoPolicy";
	offset = lsarpc_dissect_element_lsa_QueryInfoPolicy_info(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);

	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_QueryInfoPolicy_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_QueryInfoPolicy";
	offset = lsarpc_dissect_element_lsa_QueryInfoPolicy_handle(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_QueryInfoPolicy_level(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	return offset;
}

static int
lsarpc_dissect_element_lsa_SetInfoPolicy_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_SetInfoPolicy_handle_, NDR_POINTER_REF, "Pointer to Handle (policy_handle)",hf_lsarpc_lsa_SetInfoPolicy_handle);

	return offset;
}

static int
lsarpc_dissect_element_lsa_SetInfoPolicy_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_policy_hnd(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_SetInfoPolicy_handle, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_SetInfoPolicy_level(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_enum_lsa_PolicyInfo(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_SetInfoPolicy_level, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_SetInfoPolicy_info(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_SetInfoPolicy_info_, NDR_POINTER_REF, "Pointer to Info (lsa_PolicyInformation)",hf_lsarpc_lsa_SetInfoPolicy_info);

	return offset;
}

static int
lsarpc_dissect_element_lsa_SetInfoPolicy_info_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_lsa_PolicyInformation(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_SetInfoPolicy_info, 0);

	return offset;
}

/* IDL: NTSTATUS lsa_SetInfoPolicy( */
/* IDL: [ref] [in] policy_handle *handle, */
/* IDL: [in] lsa_PolicyInfo level, */
/* IDL: [ref] [in] [switch_is(level)] lsa_PolicyInformation *info */
/* IDL: ); */

static int
lsarpc_dissect_lsa_SetInfoPolicy_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_SetInfoPolicy";
	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_SetInfoPolicy_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_SetInfoPolicy";
	offset = lsarpc_dissect_element_lsa_SetInfoPolicy_handle(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_SetInfoPolicy_level(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_SetInfoPolicy_info(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	return offset;
}

/* IDL: NTSTATUS lsa_ClearAuditLog( */
/* IDL:  */
/* IDL: ); */

static int
lsarpc_dissect_lsa_ClearAuditLog_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_ClearAuditLog";
	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_ClearAuditLog_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_ClearAuditLog";
	return offset;
}

static int
lsarpc_dissect_element_lsa_CreateAccount_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_CreateAccount_handle_, NDR_POINTER_REF, "Pointer to Handle (policy_handle)",hf_lsarpc_lsa_CreateAccount_handle);

	return offset;
}

static int
lsarpc_dissect_element_lsa_CreateAccount_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_policy_hnd(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_CreateAccount_handle, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_CreateAccount_sid(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_CreateAccount_sid_, NDR_POINTER_REF, "Pointer to Sid (dom_sid2)",hf_lsarpc_lsa_CreateAccount_sid);

	return offset;
}

static int
lsarpc_dissect_element_lsa_CreateAccount_sid_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_dom_sid2(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_CreateAccount_sid,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_CreateAccount_access_mask(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_bitmap_lsa_AccountAccessMask(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_CreateAccount_access_mask, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_CreateAccount_acct_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_CreateAccount_acct_handle_, NDR_POINTER_REF, "Pointer to Acct Handle (policy_handle)",hf_lsarpc_lsa_CreateAccount_acct_handle);

	return offset;
}

static int
lsarpc_dissect_element_lsa_CreateAccount_acct_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_policy_hnd(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_CreateAccount_acct_handle, PIDL_POLHND_OPEN|PIDL_POLHND_TYPE_LSA_ACCOUNT);

	return offset;
}

/* IDL: NTSTATUS lsa_CreateAccount( */
/* IDL: [ref] [in] policy_handle *handle, */
/* IDL: [ref] [in] dom_sid2 *sid, */
/* IDL: [in] lsa_AccountAccessMask access_mask, */
/* IDL: [out] [ref] policy_handle *acct_handle */
/* IDL: ); */

static int
lsarpc_dissect_lsa_CreateAccount_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_CreateAccount";
	offset = lsarpc_dissect_element_lsa_CreateAccount_acct_handle(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);

	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_CreateAccount_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_CreateAccount";
	offset = lsarpc_dissect_element_lsa_CreateAccount_handle(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_CreateAccount_sid(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_CreateAccount_access_mask(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	return offset;
}

static int
lsarpc_dissect_element_lsa_EnumAccounts_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_EnumAccounts_handle_, NDR_POINTER_REF, "Pointer to Handle (policy_handle)",hf_lsarpc_lsa_EnumAccounts_handle);

	return offset;
}

static int
lsarpc_dissect_element_lsa_EnumAccounts_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_policy_hnd(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_EnumAccounts_handle, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_EnumAccounts_resume_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_EnumAccounts_resume_handle_, NDR_POINTER_REF, "Pointer to Resume Handle (uint32)",hf_lsarpc_lsa_EnumAccounts_resume_handle);

	return offset;
}

static int
lsarpc_dissect_element_lsa_EnumAccounts_resume_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_EnumAccounts_resume_handle, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_EnumAccounts_num_entries(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_EnumAccounts_num_entries, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_EnumAccounts_sids(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_EnumAccounts_sids_, NDR_POINTER_REF, "Pointer to Sids (lsa_SidArray)",hf_lsarpc_lsa_EnumAccounts_sids);

	return offset;
}

static int
lsarpc_dissect_element_lsa_EnumAccounts_sids_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_SidArray(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_EnumAccounts_sids,0);

	return offset;
}

/* IDL: NTSTATUS lsa_EnumAccounts( */
/* IDL: [ref] [in] policy_handle *handle, */
/* IDL: [out] [ref] [in] uint32 *resume_handle, */
/* IDL: [in] [range(0,8192)] uint32 num_entries, */
/* IDL: [out] [ref] lsa_SidArray *sids */
/* IDL: ); */

static int
lsarpc_dissect_lsa_EnumAccounts_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_EnumAccounts";
	offset = lsarpc_dissect_element_lsa_EnumAccounts_resume_handle(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);

	offset = lsarpc_dissect_element_lsa_EnumAccounts_sids(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);

	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_EnumAccounts_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_EnumAccounts";
	offset = lsarpc_dissect_element_lsa_EnumAccounts_handle(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_EnumAccounts_resume_handle(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_EnumAccounts_num_entries(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	return offset;
}

static int
lsarpc_dissect_element_lsa_CreateTrustedDomain_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_CreateTrustedDomain_handle_, NDR_POINTER_REF, "Pointer to Handle (policy_handle)",hf_lsarpc_lsa_CreateTrustedDomain_handle);

	return offset;
}

static int
lsarpc_dissect_element_lsa_CreateTrustedDomain_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_policy_hnd(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_CreateTrustedDomain_handle, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_CreateTrustedDomain_info(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_CreateTrustedDomain_info_, NDR_POINTER_REF, "Pointer to Info (lsa_DomainInfo)",hf_lsarpc_lsa_CreateTrustedDomain_info);

	return offset;
}

static int
lsarpc_dissect_element_lsa_CreateTrustedDomain_info_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_DomainInfo(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_CreateTrustedDomain_info,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_CreateTrustedDomain_access_mask(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_bitmap_lsa_DomainAccessMask(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_CreateTrustedDomain_access_mask, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_CreateTrustedDomain_trustdom_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_CreateTrustedDomain_trustdom_handle_, NDR_POINTER_REF, "Pointer to Trustdom Handle (policy_handle)",hf_lsarpc_lsa_CreateTrustedDomain_trustdom_handle);

	return offset;
}

static int
lsarpc_dissect_element_lsa_CreateTrustedDomain_trustdom_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_policy_hnd(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_CreateTrustedDomain_trustdom_handle, PIDL_POLHND_OPEN|PIDL_POLHND_TYPE_LSA_DOMAIN);

	return offset;
}

/* IDL: NTSTATUS lsa_CreateTrustedDomain( */
/* IDL: [ref] [in] policy_handle *handle, */
/* IDL: [ref] [in] lsa_DomainInfo *info, */
/* IDL: [in] lsa_DomainAccessMask access_mask, */
/* IDL: [out] [ref] policy_handle *trustdom_handle */
/* IDL: ); */

static int
lsarpc_dissect_lsa_CreateTrustedDomain_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_CreateTrustedDomain";
	offset = lsarpc_dissect_element_lsa_CreateTrustedDomain_trustdom_handle(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);

	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_CreateTrustedDomain_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_CreateTrustedDomain";
	offset = lsarpc_dissect_element_lsa_CreateTrustedDomain_handle(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_CreateTrustedDomain_info(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_CreateTrustedDomain_access_mask(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	return offset;
}

static int
lsarpc_dissect_element_lsa_EnumTrustDom_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_EnumTrustDom_handle_, NDR_POINTER_REF, "Pointer to Handle (policy_handle)",hf_lsarpc_lsa_EnumTrustDom_handle);

	return offset;
}

static int
lsarpc_dissect_element_lsa_EnumTrustDom_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_policy_hnd(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_EnumTrustDom_handle, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_EnumTrustDom_resume_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_EnumTrustDom_resume_handle_, NDR_POINTER_REF, "Pointer to Resume Handle (uint32)",hf_lsarpc_lsa_EnumTrustDom_resume_handle);

	return offset;
}

static int
lsarpc_dissect_element_lsa_EnumTrustDom_resume_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_EnumTrustDom_resume_handle, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_EnumTrustDom_max_size(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_EnumTrustDom_max_size, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_EnumTrustDom_domains(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_EnumTrustDom_domains_, NDR_POINTER_REF, "Pointer to Domains (lsa_DomainList)",hf_lsarpc_lsa_EnumTrustDom_domains);

	return offset;
}

static int
lsarpc_dissect_element_lsa_EnumTrustDom_domains_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_DomainList(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_EnumTrustDom_domains,0);

	return offset;
}

/* IDL: NTSTATUS lsa_EnumTrustDom( */
/* IDL: [ref] [in] policy_handle *handle, */
/* IDL: [out] [ref] [in] uint32 *resume_handle, */
/* IDL: [in] uint32 max_size, */
/* IDL: [out] [ref] lsa_DomainList *domains */
/* IDL: ); */

static int
lsarpc_dissect_lsa_EnumTrustDom_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_EnumTrustDom";
	offset = lsarpc_dissect_element_lsa_EnumTrustDom_resume_handle(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);

	offset = lsarpc_dissect_element_lsa_EnumTrustDom_domains(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);

	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_EnumTrustDom_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_EnumTrustDom";
	offset = lsarpc_dissect_element_lsa_EnumTrustDom_handle(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_EnumTrustDom_resume_handle(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_EnumTrustDom_max_size(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupNames_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_LookupNames_handle_, NDR_POINTER_REF, "Pointer to Handle (policy_handle)",hf_lsarpc_lsa_LookupNames_handle);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupNames_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_policy_hnd(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_LookupNames_handle, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupNames_num_names(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_LookupNames_num_names, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupNames_names_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_String(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_LookupNames_names,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupNames_domains(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_LookupNames_domains_, NDR_POINTER_UNIQUE, "Pointer to Domains (lsa_RefDomainList)",hf_lsarpc_lsa_LookupNames_domains);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupNames_domains_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_RefDomainList(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_LookupNames_domains,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupNames_sids(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_LookupNames_sids_, NDR_POINTER_REF, "Pointer to Sids (lsa_TransSidArray)",hf_lsarpc_lsa_LookupNames_sids);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupNames_sids_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_TransSidArray(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_LookupNames_sids,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupNames_level(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_enum_lsa_LookupNamesLevel(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_LookupNames_level, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupNames_count(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_LookupNames_count_, NDR_POINTER_REF, "Pointer to Count (uint32)",hf_lsarpc_lsa_LookupNames_count);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupNames_count_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_LookupNames_count, 0);

	return offset;
}

/* IDL: NTSTATUS lsa_LookupNames( */
/* IDL: [ref] [in] policy_handle *handle, */
/* IDL: [in] [range(0,1000)] uint32 num_names, */
/* IDL: [in] [size_is(num_names)] lsa_String names[*], */
/* IDL: [out] [unique(1)] lsa_RefDomainList *domains, */
/* IDL: [out] [ref] [in] lsa_TransSidArray *sids, */
/* IDL: [in] lsa_LookupNamesLevel level, */
/* IDL: [out] [ref] [in] uint32 *count */
/* IDL: ); */

static int
lsarpc_dissect_lsa_LookupNames_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_LookupNames";
	offset = lsarpc_dissect_element_lsa_LookupNames_domains(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);

	offset = lsarpc_dissect_element_lsa_LookupNames_sids(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);

	offset = lsarpc_dissect_element_lsa_LookupNames_count(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);

	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_LookupNames_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_LookupNames";
	offset = lsarpc_dissect_element_lsa_LookupNames_handle(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_LookupNames_num_names(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_LookupNames_names(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_LookupNames_sids(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_LookupNames_level(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_LookupNames_count(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupSids_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_LookupSids_handle_, NDR_POINTER_REF, "Pointer to Handle (policy_handle)",hf_lsarpc_lsa_LookupSids_handle);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupSids_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_policy_hnd(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_LookupSids_handle, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupSids_sids(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_LookupSids_sids_, NDR_POINTER_REF, "Pointer to Sids (lsa_SidArray)",hf_lsarpc_lsa_LookupSids_sids);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupSids_sids_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_SidArray(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_LookupSids_sids,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupSids_domains(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_LookupSids_domains_, NDR_POINTER_UNIQUE, "Pointer to Domains (lsa_RefDomainList)",hf_lsarpc_lsa_LookupSids_domains);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupSids_domains_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_RefDomainList(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_LookupSids_domains,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupSids_names(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_LookupSids_names_, NDR_POINTER_REF, "Pointer to Names (lsa_TransNameArray)",hf_lsarpc_lsa_LookupSids_names);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupSids_names_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_TransNameArray(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_LookupSids_names,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupSids_level(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint16(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_LookupSids_level, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupSids_count(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_LookupSids_count_, NDR_POINTER_REF, "Pointer to Count (uint32)",hf_lsarpc_lsa_LookupSids_count);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupSids_count_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_LookupSids_count, 0);

	return offset;
}

/* IDL: NTSTATUS lsa_LookupSids( */
/* IDL: [ref] [in] policy_handle *handle, */
/* IDL: [ref] [in] lsa_SidArray *sids, */
/* IDL: [out] [unique(1)] lsa_RefDomainList *domains, */
/* IDL: [out] [ref] [in] lsa_TransNameArray *names, */
/* IDL: [in] uint16 level, */
/* IDL: [out] [ref] [in] uint32 *count */
/* IDL: ); */

static int
lsarpc_dissect_lsa_LookupSids_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_LookupSids";
	offset = lsarpc_dissect_element_lsa_LookupSids_domains(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);

	offset = lsarpc_dissect_element_lsa_LookupSids_names(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);

	offset = lsarpc_dissect_element_lsa_LookupSids_count(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);

	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_LookupSids_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_LookupSids";
	offset = lsarpc_dissect_element_lsa_LookupSids_handle(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_LookupSids_sids(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_LookupSids_names(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_LookupSids_level(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_LookupSids_count(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	return offset;
}

static int
lsarpc_dissect_element_lsa_CreateSecret_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_CreateSecret_handle_, NDR_POINTER_REF, "Pointer to Handle (policy_handle)",hf_lsarpc_lsa_CreateSecret_handle);

	return offset;
}

static int
lsarpc_dissect_element_lsa_CreateSecret_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_policy_hnd(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_CreateSecret_handle, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_CreateSecret_name(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_String(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_CreateSecret_name,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_CreateSecret_access_mask(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_bitmap_lsa_SecretAccessMask(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_CreateSecret_access_mask, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_CreateSecret_sec_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_CreateSecret_sec_handle_, NDR_POINTER_REF, "Pointer to Sec Handle (policy_handle)",hf_lsarpc_lsa_CreateSecret_sec_handle);

	return offset;
}

static int
lsarpc_dissect_element_lsa_CreateSecret_sec_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_policy_hnd(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_CreateSecret_sec_handle, PIDL_POLHND_OPEN|PIDL_POLHND_TYPE_LSA_SECRET);

	return offset;
}

/* IDL: NTSTATUS lsa_CreateSecret( */
/* IDL: [ref] [in] policy_handle *handle, */
/* IDL: [in] lsa_String name, */
/* IDL: [in] lsa_SecretAccessMask access_mask, */
/* IDL: [out] [ref] policy_handle *sec_handle */
/* IDL: ); */

static int
lsarpc_dissect_lsa_CreateSecret_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_CreateSecret";
	offset = lsarpc_dissect_element_lsa_CreateSecret_sec_handle(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);

	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_CreateSecret_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_CreateSecret";
	offset = lsarpc_dissect_element_lsa_CreateSecret_handle(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_CreateSecret_name(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_CreateSecret_access_mask(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	return offset;
}

static int
lsarpc_dissect_element_lsa_OpenAccount_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_OpenAccount_handle_, NDR_POINTER_REF, "Pointer to Handle (policy_handle)",hf_lsarpc_lsa_OpenAccount_handle);

	return offset;
}

static int
lsarpc_dissect_element_lsa_OpenAccount_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_policy_hnd(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_OpenAccount_handle, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_OpenAccount_sid(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_OpenAccount_sid_, NDR_POINTER_REF, "Pointer to Sid (dom_sid2)",hf_lsarpc_lsa_OpenAccount_sid);

	return offset;
}

static int
lsarpc_dissect_element_lsa_OpenAccount_sid_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_dom_sid2(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_OpenAccount_sid,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_OpenAccount_access_mask(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_bitmap_lsa_AccountAccessMask(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_OpenAccount_access_mask, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_OpenAccount_acct_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_OpenAccount_acct_handle_, NDR_POINTER_REF, "Pointer to Acct Handle (policy_handle)",hf_lsarpc_lsa_OpenAccount_acct_handle);

	return offset;
}

static int
lsarpc_dissect_element_lsa_OpenAccount_acct_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_policy_hnd(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_OpenAccount_acct_handle, PIDL_POLHND_OPEN|PIDL_POLHND_TYPE_LSA_ACCOUNT);

	return offset;
}

/* IDL: NTSTATUS lsa_OpenAccount( */
/* IDL: [ref] [in] policy_handle *handle, */
/* IDL: [ref] [in] dom_sid2 *sid, */
/* IDL: [in] lsa_AccountAccessMask access_mask, */
/* IDL: [out] [ref] policy_handle *acct_handle */
/* IDL: ); */

static int
lsarpc_dissect_lsa_OpenAccount_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_OpenAccount";
	offset = lsarpc_dissect_element_lsa_OpenAccount_acct_handle(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);

	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_OpenAccount_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_OpenAccount";
	offset = lsarpc_dissect_element_lsa_OpenAccount_handle(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_OpenAccount_sid(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_OpenAccount_access_mask(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	return offset;
}

static int
lsarpc_dissect_element_lsa_EnumPrivsAccount_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_EnumPrivsAccount_handle_, NDR_POINTER_REF, "Pointer to Handle (policy_handle)",hf_lsarpc_lsa_EnumPrivsAccount_handle);

	return offset;
}

static int
lsarpc_dissect_element_lsa_EnumPrivsAccount_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_policy_hnd(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_EnumPrivsAccount_handle, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_EnumPrivsAccount_privs(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_EnumPrivsAccount_privs_, NDR_POINTER_UNIQUE, "Pointer to Privs (lsa_PrivilegeSet)",hf_lsarpc_lsa_EnumPrivsAccount_privs);

	return offset;
}

static int
lsarpc_dissect_element_lsa_EnumPrivsAccount_privs_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_PrivilegeSet(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_EnumPrivsAccount_privs,0);

	return offset;
}

/* IDL: NTSTATUS lsa_EnumPrivsAccount( */
/* IDL: [ref] [in] policy_handle *handle, */
/* IDL: [out] [unique(1)] lsa_PrivilegeSet *privs */
/* IDL: ); */

static int
lsarpc_dissect_lsa_EnumPrivsAccount_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_EnumPrivsAccount";
	offset = lsarpc_dissect_element_lsa_EnumPrivsAccount_privs(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);

	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_EnumPrivsAccount_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_EnumPrivsAccount";
	offset = lsarpc_dissect_element_lsa_EnumPrivsAccount_handle(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	return offset;
}

static int
lsarpc_dissect_element_lsa_AddPrivilegesToAccount_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_AddPrivilegesToAccount_handle_, NDR_POINTER_REF, "Pointer to Handle (policy_handle)",hf_lsarpc_lsa_AddPrivilegesToAccount_handle);

	return offset;
}

static int
lsarpc_dissect_element_lsa_AddPrivilegesToAccount_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_policy_hnd(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_AddPrivilegesToAccount_handle, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_AddPrivilegesToAccount_privs(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_AddPrivilegesToAccount_privs_, NDR_POINTER_REF, "Pointer to Privs (lsa_PrivilegeSet)",hf_lsarpc_lsa_AddPrivilegesToAccount_privs);

	return offset;
}

static int
lsarpc_dissect_element_lsa_AddPrivilegesToAccount_privs_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_PrivilegeSet(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_AddPrivilegesToAccount_privs,0);

	return offset;
}

/* IDL: NTSTATUS lsa_AddPrivilegesToAccount( */
/* IDL: [ref] [in] policy_handle *handle, */
/* IDL: [ref] [in] lsa_PrivilegeSet *privs */
/* IDL: ); */

static int
lsarpc_dissect_lsa_AddPrivilegesToAccount_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_AddPrivilegesToAccount";
	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_AddPrivilegesToAccount_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_AddPrivilegesToAccount";
	offset = lsarpc_dissect_element_lsa_AddPrivilegesToAccount_handle(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_AddPrivilegesToAccount_privs(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	return offset;
}

static int
lsarpc_dissect_element_lsa_RemovePrivilegesFromAccount_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_RemovePrivilegesFromAccount_handle_, NDR_POINTER_REF, "Pointer to Handle (policy_handle)",hf_lsarpc_lsa_RemovePrivilegesFromAccount_handle);

	return offset;
}

static int
lsarpc_dissect_element_lsa_RemovePrivilegesFromAccount_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_policy_hnd(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_RemovePrivilegesFromAccount_handle, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_RemovePrivilegesFromAccount_remove_all(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint8(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_RemovePrivilegesFromAccount_remove_all, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_RemovePrivilegesFromAccount_privs(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_RemovePrivilegesFromAccount_privs_, NDR_POINTER_UNIQUE, "Pointer to Privs (lsa_PrivilegeSet)",hf_lsarpc_lsa_RemovePrivilegesFromAccount_privs);

	return offset;
}

static int
lsarpc_dissect_element_lsa_RemovePrivilegesFromAccount_privs_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_PrivilegeSet(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_RemovePrivilegesFromAccount_privs,0);

	return offset;
}

/* IDL: NTSTATUS lsa_RemovePrivilegesFromAccount( */
/* IDL: [ref] [in] policy_handle *handle, */
/* IDL: [in] uint8 remove_all, */
/* IDL: [unique(1)] [in] lsa_PrivilegeSet *privs */
/* IDL: ); */

static int
lsarpc_dissect_lsa_RemovePrivilegesFromAccount_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_RemovePrivilegesFromAccount";
	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_RemovePrivilegesFromAccount_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_RemovePrivilegesFromAccount";
	offset = lsarpc_dissect_element_lsa_RemovePrivilegesFromAccount_handle(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_RemovePrivilegesFromAccount_remove_all(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_RemovePrivilegesFromAccount_privs(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	return offset;
}

/* IDL: NTSTATUS lsa_GetQuotasForAccount( */
/* IDL:  */
/* IDL: ); */

static int
lsarpc_dissect_lsa_GetQuotasForAccount_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_GetQuotasForAccount";
	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_GetQuotasForAccount_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_GetQuotasForAccount";
	return offset;
}

/* IDL: NTSTATUS lsa_SetQuotasForAccount( */
/* IDL:  */
/* IDL: ); */

static int
lsarpc_dissect_lsa_SetQuotasForAccount_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_SetQuotasForAccount";
	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_SetQuotasForAccount_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_SetQuotasForAccount";
	return offset;
}

/* IDL: NTSTATUS lsa_GetSystemAccessAccount( */
/* IDL:  */
/* IDL: ); */

static int
lsarpc_dissect_lsa_GetSystemAccessAccount_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_GetSystemAccessAccount";
	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_GetSystemAccessAccount_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_GetSystemAccessAccount";
	return offset;
}

/* IDL: NTSTATUS lsa_SetSystemAccessAccount( */
/* IDL:  */
/* IDL: ); */

static int
lsarpc_dissect_lsa_SetSystemAccessAccount_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_SetSystemAccessAccount";
	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_SetSystemAccessAccount_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_SetSystemAccessAccount";
	return offset;
}

static int
lsarpc_dissect_element_lsa_OpenTrustedDomain_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_OpenTrustedDomain_handle_, NDR_POINTER_REF, "Pointer to Handle (policy_handle)",hf_lsarpc_lsa_OpenTrustedDomain_handle);

	return offset;
}

static int
lsarpc_dissect_element_lsa_OpenTrustedDomain_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_policy_hnd(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_OpenTrustedDomain_handle, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_OpenTrustedDomain_sid(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_OpenTrustedDomain_sid_, NDR_POINTER_REF, "Pointer to Sid (dom_sid2)",hf_lsarpc_lsa_OpenTrustedDomain_sid);

	return offset;
}

static int
lsarpc_dissect_element_lsa_OpenTrustedDomain_sid_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_dom_sid2(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_OpenTrustedDomain_sid,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_OpenTrustedDomain_access_mask(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_bitmap_lsa_DomainAccessMask(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_OpenTrustedDomain_access_mask, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_OpenTrustedDomain_trustdom_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_OpenTrustedDomain_trustdom_handle_, NDR_POINTER_REF, "Pointer to Trustdom Handle (policy_handle)",hf_lsarpc_lsa_OpenTrustedDomain_trustdom_handle);

	return offset;
}

static int
lsarpc_dissect_element_lsa_OpenTrustedDomain_trustdom_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_policy_hnd(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_OpenTrustedDomain_trustdom_handle, PIDL_POLHND_OPEN|PIDL_POLHND_TYPE_LSA_DOMAIN);

	return offset;
}

/* IDL: NTSTATUS lsa_OpenTrustedDomain( */
/* IDL: [ref] [in] policy_handle *handle, */
/* IDL: [ref] [in] dom_sid2 *sid, */
/* IDL: [in] lsa_DomainAccessMask access_mask, */
/* IDL: [out] [ref] policy_handle *trustdom_handle */
/* IDL: ); */

static int
lsarpc_dissect_lsa_OpenTrustedDomain_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_OpenTrustedDomain";
	offset = lsarpc_dissect_element_lsa_OpenTrustedDomain_trustdom_handle(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);

	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_OpenTrustedDomain_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_OpenTrustedDomain";
	offset = lsarpc_dissect_element_lsa_OpenTrustedDomain_handle(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_OpenTrustedDomain_sid(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_OpenTrustedDomain_access_mask(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	return offset;
}

static int
lsarpc_dissect_element_lsa_QueryTrustedDomainInfo_trustdom_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_QueryTrustedDomainInfo_trustdom_handle_, NDR_POINTER_REF, "Pointer to Trustdom Handle (policy_handle)",hf_lsarpc_lsa_QueryTrustedDomainInfo_trustdom_handle);

	return offset;
}

static int
lsarpc_dissect_element_lsa_QueryTrustedDomainInfo_trustdom_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_policy_hnd(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_QueryTrustedDomainInfo_trustdom_handle, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_QueryTrustedDomainInfo_level(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_enum_lsa_TrustDomInfoEnum(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_QueryTrustedDomainInfo_level, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_QueryTrustedDomainInfo_info(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_QueryTrustedDomainInfo_info_, NDR_POINTER_UNIQUE, "Pointer to Info (lsa_TrustedDomainInfo)",hf_lsarpc_lsa_QueryTrustedDomainInfo_info);

	return offset;
}

static int
lsarpc_dissect_element_lsa_QueryTrustedDomainInfo_info_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_lsa_TrustedDomainInfo(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_QueryTrustedDomainInfo_info, 0);

	return offset;
}

/* IDL: NTSTATUS lsa_QueryTrustedDomainInfo( */
/* IDL: [ref] [in] policy_handle *trustdom_handle, */
/* IDL: [in] lsa_TrustDomInfoEnum level, */
/* IDL: [out] [unique(1)] [switch_is(level)] lsa_TrustedDomainInfo *info */
/* IDL: ); */

static int
lsarpc_dissect_lsa_QueryTrustedDomainInfo_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_QueryTrustedDomainInfo";
	offset = lsarpc_dissect_element_lsa_QueryTrustedDomainInfo_info(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);

	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_QueryTrustedDomainInfo_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_QueryTrustedDomainInfo";
	offset = lsarpc_dissect_element_lsa_QueryTrustedDomainInfo_trustdom_handle(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_QueryTrustedDomainInfo_level(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	return offset;
}

/* IDL: NTSTATUS lsa_SetInformationTrustedDomain( */
/* IDL:  */
/* IDL: ); */

static int
lsarpc_dissect_lsa_SetInformationTrustedDomain_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_SetInformationTrustedDomain";
	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_SetInformationTrustedDomain_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_SetInformationTrustedDomain";
	return offset;
}

static int
lsarpc_dissect_element_lsa_OpenSecret_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_OpenSecret_handle_, NDR_POINTER_REF, "Pointer to Handle (policy_handle)",hf_lsarpc_lsa_OpenSecret_handle);

	return offset;
}

static int
lsarpc_dissect_element_lsa_OpenSecret_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_policy_hnd(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_OpenSecret_handle, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_OpenSecret_name(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_String(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_OpenSecret_name,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_OpenSecret_access_mask(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_bitmap_lsa_SecretAccessMask(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_OpenSecret_access_mask, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_OpenSecret_sec_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_OpenSecret_sec_handle_, NDR_POINTER_REF, "Pointer to Sec Handle (policy_handle)",hf_lsarpc_lsa_OpenSecret_sec_handle);

	return offset;
}

static int
lsarpc_dissect_element_lsa_OpenSecret_sec_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_policy_hnd(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_OpenSecret_sec_handle, PIDL_POLHND_OPEN|PIDL_POLHND_TYPE_LSA_SECRET);

	return offset;
}

/* IDL: NTSTATUS lsa_OpenSecret( */
/* IDL: [ref] [in] policy_handle *handle, */
/* IDL: [in] lsa_String name, */
/* IDL: [in] lsa_SecretAccessMask access_mask, */
/* IDL: [out] [ref] policy_handle *sec_handle */
/* IDL: ); */

static int
lsarpc_dissect_lsa_OpenSecret_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_OpenSecret";
	offset = lsarpc_dissect_element_lsa_OpenSecret_sec_handle(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);

	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_OpenSecret_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_OpenSecret";
	offset = lsarpc_dissect_element_lsa_OpenSecret_handle(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_OpenSecret_name(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_OpenSecret_access_mask(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	return offset;
}

static int
lsarpc_dissect_element_lsa_SetSecret_sec_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_SetSecret_sec_handle_, NDR_POINTER_REF, "Pointer to Sec Handle (policy_handle)",hf_lsarpc_lsa_SetSecret_sec_handle);

	return offset;
}

static int
lsarpc_dissect_element_lsa_SetSecret_sec_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_policy_hnd(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_SetSecret_sec_handle, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_SetSecret_new_val(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_SetSecret_new_val_, NDR_POINTER_UNIQUE, "Pointer to New Val (lsa_DATA_BUF)",hf_lsarpc_lsa_SetSecret_new_val);

	return offset;
}

static int
lsarpc_dissect_element_lsa_SetSecret_new_val_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_DATA_BUF(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_SetSecret_new_val,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_SetSecret_old_val(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_SetSecret_old_val_, NDR_POINTER_UNIQUE, "Pointer to Old Val (lsa_DATA_BUF)",hf_lsarpc_lsa_SetSecret_old_val);

	return offset;
}

static int
lsarpc_dissect_element_lsa_SetSecret_old_val_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_DATA_BUF(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_SetSecret_old_val,0);

	return offset;
}

/* IDL: NTSTATUS lsa_SetSecret( */
/* IDL: [ref] [in] policy_handle *sec_handle, */
/* IDL: [unique(1)] [in] lsa_DATA_BUF *new_val, */
/* IDL: [unique(1)] [in] lsa_DATA_BUF *old_val */
/* IDL: ); */

static int
lsarpc_dissect_lsa_SetSecret_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_SetSecret";
	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_SetSecret_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_SetSecret";
	offset = lsarpc_dissect_element_lsa_SetSecret_sec_handle(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_SetSecret_new_val(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_SetSecret_old_val(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	return offset;
}

static int
lsarpc_dissect_element_lsa_QuerySecret_sec_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_QuerySecret_sec_handle_, NDR_POINTER_REF, "Pointer to Sec Handle (policy_handle)",hf_lsarpc_lsa_QuerySecret_sec_handle);

	return offset;
}

static int
lsarpc_dissect_element_lsa_QuerySecret_sec_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_policy_hnd(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_QuerySecret_sec_handle, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_QuerySecret_new_val(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_QuerySecret_new_val_, NDR_POINTER_UNIQUE, "Pointer to New Val (lsa_DATA_BUF_PTR)",hf_lsarpc_lsa_QuerySecret_new_val);

	return offset;
}

static int
lsarpc_dissect_element_lsa_QuerySecret_new_val_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_DATA_BUF_PTR(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_QuerySecret_new_val,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_QuerySecret_new_mtime(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_QuerySecret_new_mtime_, NDR_POINTER_UNIQUE, "Pointer to New Mtime (NTTIME_hyper)",hf_lsarpc_lsa_QuerySecret_new_mtime);

	return offset;
}

static int
lsarpc_dissect_element_lsa_QuerySecret_new_mtime_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_nt_NTTIME(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_QuerySecret_new_mtime);

	return offset;
}

static int
lsarpc_dissect_element_lsa_QuerySecret_old_val(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_QuerySecret_old_val_, NDR_POINTER_UNIQUE, "Pointer to Old Val (lsa_DATA_BUF_PTR)",hf_lsarpc_lsa_QuerySecret_old_val);

	return offset;
}

static int
lsarpc_dissect_element_lsa_QuerySecret_old_val_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_DATA_BUF_PTR(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_QuerySecret_old_val,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_QuerySecret_old_mtime(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_QuerySecret_old_mtime_, NDR_POINTER_UNIQUE, "Pointer to Old Mtime (NTTIME_hyper)",hf_lsarpc_lsa_QuerySecret_old_mtime);

	return offset;
}

static int
lsarpc_dissect_element_lsa_QuerySecret_old_mtime_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_nt_NTTIME(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_QuerySecret_old_mtime);

	return offset;
}

/* IDL: NTSTATUS lsa_QuerySecret( */
/* IDL: [ref] [in] policy_handle *sec_handle, */
/* IDL: [out] [unique(1)] [in] lsa_DATA_BUF_PTR *new_val, */
/* IDL: [out] [unique(1)] [in] NTTIME_hyper *new_mtime, */
/* IDL: [out] [unique(1)] [in] lsa_DATA_BUF_PTR *old_val, */
/* IDL: [out] [unique(1)] [in] NTTIME_hyper *old_mtime */
/* IDL: ); */

static int
lsarpc_dissect_lsa_QuerySecret_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_QuerySecret";
	offset = lsarpc_dissect_element_lsa_QuerySecret_new_val(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);

	offset = lsarpc_dissect_element_lsa_QuerySecret_new_mtime(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);

	offset = lsarpc_dissect_element_lsa_QuerySecret_old_val(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);

	offset = lsarpc_dissect_element_lsa_QuerySecret_old_mtime(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);

	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_QuerySecret_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_QuerySecret";
	offset = lsarpc_dissect_element_lsa_QuerySecret_sec_handle(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_QuerySecret_new_val(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_QuerySecret_new_mtime(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_QuerySecret_old_val(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_QuerySecret_old_mtime(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupPrivValue_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_LookupPrivValue_handle_, NDR_POINTER_REF, "Pointer to Handle (policy_handle)",hf_lsarpc_lsa_LookupPrivValue_handle);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupPrivValue_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_policy_hnd(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_LookupPrivValue_handle, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupPrivValue_name(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_LookupPrivValue_name_, NDR_POINTER_REF, "Pointer to Name (lsa_String)",hf_lsarpc_lsa_LookupPrivValue_name);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupPrivValue_name_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_String(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_LookupPrivValue_name,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupPrivValue_luid(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_LookupPrivValue_luid_, NDR_POINTER_REF, "Pointer to Luid (lsa_LUID)",hf_lsarpc_lsa_LookupPrivValue_luid);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupPrivValue_luid_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_LUID(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_LookupPrivValue_luid,0);

	return offset;
}

/* IDL: NTSTATUS lsa_LookupPrivValue( */
/* IDL: [ref] [in] policy_handle *handle, */
/* IDL: [ref] [in] lsa_String *name, */
/* IDL: [out] [ref] lsa_LUID *luid */
/* IDL: ); */

static int
lsarpc_dissect_lsa_LookupPrivValue_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_LookupPrivValue";
	offset = lsarpc_dissect_element_lsa_LookupPrivValue_luid(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);

	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_LookupPrivValue_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_LookupPrivValue";
	offset = lsarpc_dissect_element_lsa_LookupPrivValue_handle(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_LookupPrivValue_name(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupPrivName_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_LookupPrivName_handle_, NDR_POINTER_REF, "Pointer to Handle (policy_handle)",hf_lsarpc_lsa_LookupPrivName_handle);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupPrivName_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_policy_hnd(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_LookupPrivName_handle, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupPrivName_luid(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_LookupPrivName_luid_, NDR_POINTER_REF, "Pointer to Luid (lsa_LUID)",hf_lsarpc_lsa_LookupPrivName_luid);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupPrivName_luid_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_LUID(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_LookupPrivName_luid,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupPrivName_name(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_LookupPrivName_name_, NDR_POINTER_UNIQUE, "Pointer to Name (lsa_StringLarge)",hf_lsarpc_lsa_LookupPrivName_name);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupPrivName_name_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_StringLarge(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_LookupPrivName_name,0);

	return offset;
}

/* IDL: NTSTATUS lsa_LookupPrivName( */
/* IDL: [ref] [in] policy_handle *handle, */
/* IDL: [ref] [in] lsa_LUID *luid, */
/* IDL: [out] [unique(1)] lsa_StringLarge *name */
/* IDL: ); */

static int
lsarpc_dissect_lsa_LookupPrivName_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_LookupPrivName";
	offset = lsarpc_dissect_element_lsa_LookupPrivName_name(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);

	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_LookupPrivName_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_LookupPrivName";
	offset = lsarpc_dissect_element_lsa_LookupPrivName_handle(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_LookupPrivName_luid(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupPrivDisplayName_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_LookupPrivDisplayName_handle_, NDR_POINTER_REF, "Pointer to Handle (policy_handle)",hf_lsarpc_lsa_LookupPrivDisplayName_handle);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupPrivDisplayName_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_policy_hnd(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_LookupPrivDisplayName_handle, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupPrivDisplayName_name(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_LookupPrivDisplayName_name_, NDR_POINTER_REF, "Pointer to Name (lsa_String)",hf_lsarpc_lsa_LookupPrivDisplayName_name);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupPrivDisplayName_name_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_String(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_LookupPrivDisplayName_name,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupPrivDisplayName_disp_name(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_LookupPrivDisplayName_disp_name_, NDR_POINTER_UNIQUE, "Pointer to Disp Name (lsa_StringLarge)",hf_lsarpc_lsa_LookupPrivDisplayName_disp_name);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupPrivDisplayName_disp_name_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_StringLarge(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_LookupPrivDisplayName_disp_name,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupPrivDisplayName_language_id(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_LookupPrivDisplayName_language_id_, NDR_POINTER_REF, "Pointer to Language Id (uint16)",hf_lsarpc_lsa_LookupPrivDisplayName_language_id);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupPrivDisplayName_language_id_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint16(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_LookupPrivDisplayName_language_id, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupPrivDisplayName_unknown(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint16(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_LookupPrivDisplayName_unknown, 0);

	return offset;
}

/* IDL: NTSTATUS lsa_LookupPrivDisplayName( */
/* IDL: [ref] [in] policy_handle *handle, */
/* IDL: [ref] [in] lsa_String *name, */
/* IDL: [out] [unique(1)] lsa_StringLarge *disp_name, */
/* IDL: [out] [ref] [in] uint16 *language_id, */
/* IDL: [in] uint16 unknown */
/* IDL: ); */

static int
lsarpc_dissect_lsa_LookupPrivDisplayName_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_LookupPrivDisplayName";
	offset = lsarpc_dissect_element_lsa_LookupPrivDisplayName_disp_name(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);

	offset = lsarpc_dissect_element_lsa_LookupPrivDisplayName_language_id(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);

	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_LookupPrivDisplayName_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_LookupPrivDisplayName";
	offset = lsarpc_dissect_element_lsa_LookupPrivDisplayName_handle(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_LookupPrivDisplayName_name(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_LookupPrivDisplayName_language_id(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_LookupPrivDisplayName_unknown(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	return offset;
}

/* IDL: NTSTATUS lsa_DeleteObject( */
/* IDL:  */
/* IDL: ); */

static int
lsarpc_dissect_lsa_DeleteObject_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_DeleteObject";
	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_DeleteObject_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_DeleteObject";
	return offset;
}

static int
lsarpc_dissect_element_lsa_EnumAccountsWithUserRight_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_EnumAccountsWithUserRight_handle_, NDR_POINTER_REF, "Pointer to Handle (policy_handle)",hf_lsarpc_lsa_EnumAccountsWithUserRight_handle);

	return offset;
}

static int
lsarpc_dissect_element_lsa_EnumAccountsWithUserRight_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_policy_hnd(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_EnumAccountsWithUserRight_handle, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_EnumAccountsWithUserRight_name(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_EnumAccountsWithUserRight_name_, NDR_POINTER_UNIQUE, "Pointer to Name (lsa_String)",hf_lsarpc_lsa_EnumAccountsWithUserRight_name);

	return offset;
}

static int
lsarpc_dissect_element_lsa_EnumAccountsWithUserRight_name_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_String(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_EnumAccountsWithUserRight_name,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_EnumAccountsWithUserRight_sids(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_EnumAccountsWithUserRight_sids_, NDR_POINTER_REF, "Pointer to Sids (lsa_SidArray)",hf_lsarpc_lsa_EnumAccountsWithUserRight_sids);

	return offset;
}

static int
lsarpc_dissect_element_lsa_EnumAccountsWithUserRight_sids_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_SidArray(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_EnumAccountsWithUserRight_sids,0);

	return offset;
}

/* IDL: NTSTATUS lsa_EnumAccountsWithUserRight( */
/* IDL: [ref] [in] policy_handle *handle, */
/* IDL: [unique(1)] [in] lsa_String *name, */
/* IDL: [out] [ref] lsa_SidArray *sids */
/* IDL: ); */

static int
lsarpc_dissect_lsa_EnumAccountsWithUserRight_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_EnumAccountsWithUserRight";
	offset = lsarpc_dissect_element_lsa_EnumAccountsWithUserRight_sids(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);

	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_EnumAccountsWithUserRight_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_EnumAccountsWithUserRight";
	offset = lsarpc_dissect_element_lsa_EnumAccountsWithUserRight_handle(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_EnumAccountsWithUserRight_name(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	return offset;
}

static int
lsarpc_dissect_element_lsa_EnumAccountRights_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_EnumAccountRights_handle_, NDR_POINTER_REF, "Pointer to Handle (policy_handle)",hf_lsarpc_lsa_EnumAccountRights_handle);

	return offset;
}

static int
lsarpc_dissect_element_lsa_EnumAccountRights_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_policy_hnd(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_EnumAccountRights_handle, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_EnumAccountRights_sid(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_EnumAccountRights_sid_, NDR_POINTER_REF, "Pointer to Sid (dom_sid2)",hf_lsarpc_lsa_EnumAccountRights_sid);

	return offset;
}

static int
lsarpc_dissect_element_lsa_EnumAccountRights_sid_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_dom_sid2(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_EnumAccountRights_sid,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_EnumAccountRights_rights(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_EnumAccountRights_rights_, NDR_POINTER_REF, "Pointer to Rights (lsa_RightSet)",hf_lsarpc_lsa_EnumAccountRights_rights);

	return offset;
}

static int
lsarpc_dissect_element_lsa_EnumAccountRights_rights_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_RightSet(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_EnumAccountRights_rights,0);

	return offset;
}

/* IDL: NTSTATUS lsa_EnumAccountRights( */
/* IDL: [ref] [in] policy_handle *handle, */
/* IDL: [ref] [in] dom_sid2 *sid, */
/* IDL: [out] [ref] lsa_RightSet *rights */
/* IDL: ); */

static int
lsarpc_dissect_lsa_EnumAccountRights_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_EnumAccountRights";
	offset = lsarpc_dissect_element_lsa_EnumAccountRights_rights(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);

	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_EnumAccountRights_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_EnumAccountRights";
	offset = lsarpc_dissect_element_lsa_EnumAccountRights_handle(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_EnumAccountRights_sid(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	return offset;
}

static int
lsarpc_dissect_element_lsa_AddAccountRights_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_AddAccountRights_handle_, NDR_POINTER_REF, "Pointer to Handle (policy_handle)",hf_lsarpc_lsa_AddAccountRights_handle);

	return offset;
}

static int
lsarpc_dissect_element_lsa_AddAccountRights_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_policy_hnd(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_AddAccountRights_handle, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_AddAccountRights_sid(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_AddAccountRights_sid_, NDR_POINTER_REF, "Pointer to Sid (dom_sid2)",hf_lsarpc_lsa_AddAccountRights_sid);

	return offset;
}

static int
lsarpc_dissect_element_lsa_AddAccountRights_sid_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_dom_sid2(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_AddAccountRights_sid,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_AddAccountRights_rights(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_AddAccountRights_rights_, NDR_POINTER_REF, "Pointer to Rights (lsa_RightSet)",hf_lsarpc_lsa_AddAccountRights_rights);

	return offset;
}

static int
lsarpc_dissect_element_lsa_AddAccountRights_rights_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_RightSet(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_AddAccountRights_rights,0);

	return offset;
}

/* IDL: NTSTATUS lsa_AddAccountRights( */
/* IDL: [ref] [in] policy_handle *handle, */
/* IDL: [ref] [in] dom_sid2 *sid, */
/* IDL: [ref] [in] lsa_RightSet *rights */
/* IDL: ); */

static int
lsarpc_dissect_lsa_AddAccountRights_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_AddAccountRights";
	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_AddAccountRights_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_AddAccountRights";
	offset = lsarpc_dissect_element_lsa_AddAccountRights_handle(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_AddAccountRights_sid(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_AddAccountRights_rights(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	return offset;
}

static int
lsarpc_dissect_element_lsa_RemoveAccountRights_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_RemoveAccountRights_handle_, NDR_POINTER_REF, "Pointer to Handle (policy_handle)",hf_lsarpc_lsa_RemoveAccountRights_handle);

	return offset;
}

static int
lsarpc_dissect_element_lsa_RemoveAccountRights_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_policy_hnd(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_RemoveAccountRights_handle, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_RemoveAccountRights_sid(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_RemoveAccountRights_sid_, NDR_POINTER_REF, "Pointer to Sid (dom_sid2)",hf_lsarpc_lsa_RemoveAccountRights_sid);

	return offset;
}

static int
lsarpc_dissect_element_lsa_RemoveAccountRights_sid_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_dom_sid2(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_RemoveAccountRights_sid,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_RemoveAccountRights_unknown(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_RemoveAccountRights_unknown, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_RemoveAccountRights_rights(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_RemoveAccountRights_rights_, NDR_POINTER_REF, "Pointer to Rights (lsa_RightSet)",hf_lsarpc_lsa_RemoveAccountRights_rights);

	return offset;
}

static int
lsarpc_dissect_element_lsa_RemoveAccountRights_rights_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_RightSet(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_RemoveAccountRights_rights,0);

	return offset;
}

/* IDL: NTSTATUS lsa_RemoveAccountRights( */
/* IDL: [ref] [in] policy_handle *handle, */
/* IDL: [ref] [in] dom_sid2 *sid, */
/* IDL: [in] uint32 unknown, */
/* IDL: [ref] [in] lsa_RightSet *rights */
/* IDL: ); */

static int
lsarpc_dissect_lsa_RemoveAccountRights_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_RemoveAccountRights";
	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_RemoveAccountRights_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_RemoveAccountRights";
	offset = lsarpc_dissect_element_lsa_RemoveAccountRights_handle(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_RemoveAccountRights_sid(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_RemoveAccountRights_unknown(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_RemoveAccountRights_rights(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	return offset;
}

static int
lsarpc_dissect_element_lsa_QueryTrustedDomainInfoBySid_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_QueryTrustedDomainInfoBySid_handle_, NDR_POINTER_REF, "Pointer to Handle (policy_handle)",hf_lsarpc_lsa_QueryTrustedDomainInfoBySid_handle);

	return offset;
}

static int
lsarpc_dissect_element_lsa_QueryTrustedDomainInfoBySid_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_policy_hnd(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_QueryTrustedDomainInfoBySid_handle, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_QueryTrustedDomainInfoBySid_dom_sid(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_QueryTrustedDomainInfoBySid_dom_sid_, NDR_POINTER_REF, "Pointer to Dom Sid (dom_sid2)",hf_lsarpc_lsa_QueryTrustedDomainInfoBySid_dom_sid);

	return offset;
}

static int
lsarpc_dissect_element_lsa_QueryTrustedDomainInfoBySid_dom_sid_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_dom_sid2(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_QueryTrustedDomainInfoBySid_dom_sid,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_QueryTrustedDomainInfoBySid_level(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_enum_lsa_TrustDomInfoEnum(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_QueryTrustedDomainInfoBySid_level, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_QueryTrustedDomainInfoBySid_info(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_QueryTrustedDomainInfoBySid_info_, NDR_POINTER_UNIQUE, "Pointer to Info (lsa_TrustedDomainInfo)",hf_lsarpc_lsa_QueryTrustedDomainInfoBySid_info);

	return offset;
}

static int
lsarpc_dissect_element_lsa_QueryTrustedDomainInfoBySid_info_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_lsa_TrustedDomainInfo(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_QueryTrustedDomainInfoBySid_info, 0);

	return offset;
}

/* IDL: NTSTATUS lsa_QueryTrustedDomainInfoBySid( */
/* IDL: [ref] [in] policy_handle *handle, */
/* IDL: [ref] [in] dom_sid2 *dom_sid, */
/* IDL: [in] lsa_TrustDomInfoEnum level, */
/* IDL: [out] [unique(1)] [switch_is(level)] lsa_TrustedDomainInfo *info */
/* IDL: ); */

static int
lsarpc_dissect_lsa_QueryTrustedDomainInfoBySid_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_QueryTrustedDomainInfoBySid";
	offset = lsarpc_dissect_element_lsa_QueryTrustedDomainInfoBySid_info(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);

	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_QueryTrustedDomainInfoBySid_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_QueryTrustedDomainInfoBySid";
	offset = lsarpc_dissect_element_lsa_QueryTrustedDomainInfoBySid_handle(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_QueryTrustedDomainInfoBySid_dom_sid(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_QueryTrustedDomainInfoBySid_level(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	return offset;
}

/* IDL: NTSTATUS lsa_SetTrustedDomainInfo( */
/* IDL:  */
/* IDL: ); */

static int
lsarpc_dissect_lsa_SetTrustedDomainInfo_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_SetTrustedDomainInfo";
	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_SetTrustedDomainInfo_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_SetTrustedDomainInfo";
	return offset;
}

static int
lsarpc_dissect_element_lsa_DeleteTrustedDomain_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_DeleteTrustedDomain_handle_, NDR_POINTER_REF, "Pointer to Handle (policy_handle)",hf_lsarpc_lsa_DeleteTrustedDomain_handle);

	return offset;
}

static int
lsarpc_dissect_element_lsa_DeleteTrustedDomain_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_policy_hnd(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_DeleteTrustedDomain_handle, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_DeleteTrustedDomain_dom_sid(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_DeleteTrustedDomain_dom_sid_, NDR_POINTER_REF, "Pointer to Dom Sid (dom_sid2)",hf_lsarpc_lsa_DeleteTrustedDomain_dom_sid);

	return offset;
}

static int
lsarpc_dissect_element_lsa_DeleteTrustedDomain_dom_sid_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_dom_sid2(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_DeleteTrustedDomain_dom_sid,0);

	return offset;
}

/* IDL: NTSTATUS lsa_DeleteTrustedDomain( */
/* IDL: [ref] [in] policy_handle *handle, */
/* IDL: [ref] [in] dom_sid2 *dom_sid */
/* IDL: ); */

static int
lsarpc_dissect_lsa_DeleteTrustedDomain_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_DeleteTrustedDomain";
	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_DeleteTrustedDomain_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_DeleteTrustedDomain";
	offset = lsarpc_dissect_element_lsa_DeleteTrustedDomain_handle(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_DeleteTrustedDomain_dom_sid(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	return offset;
}

/* IDL: NTSTATUS lsa_StorePrivateData( */
/* IDL:  */
/* IDL: ); */

static int
lsarpc_dissect_lsa_StorePrivateData_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_StorePrivateData";
	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_StorePrivateData_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_StorePrivateData";
	return offset;
}

/* IDL: NTSTATUS lsa_RetrievePrivateData( */
/* IDL:  */
/* IDL: ); */

static int
lsarpc_dissect_lsa_RetrievePrivateData_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_RetrievePrivateData";
	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_RetrievePrivateData_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_RetrievePrivateData";
	return offset;
}

static int
lsarpc_dissect_element_lsa_OpenPolicy2_system_name(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_OpenPolicy2_system_name_, NDR_POINTER_UNIQUE, "Pointer to System Name (uint16)",hf_lsarpc_lsa_OpenPolicy2_system_name);

	return offset;
}

static int
lsarpc_dissect_element_lsa_OpenPolicy2_system_name_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	char *data;

	offset = dissect_ndr_cvstring(tvb, offset, pinfo, tree, di, drep, sizeof(guint16), hf_lsarpc_lsa_OpenPolicy2_system_name, FALSE, &data);
	proto_item_append_text(tree, ": %s", data);

	return offset;
}

static int
lsarpc_dissect_element_lsa_OpenPolicy2_attr(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_OpenPolicy2_attr_, NDR_POINTER_REF, "Pointer to Attr (lsa_ObjectAttribute)",hf_lsarpc_lsa_OpenPolicy2_attr);

	return offset;
}

static int
lsarpc_dissect_element_lsa_OpenPolicy2_attr_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_ObjectAttribute(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_OpenPolicy2_attr,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_OpenPolicy2_access_mask(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_bitmap_lsa_PolicyAccessMask(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_OpenPolicy2_access_mask, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_OpenPolicy2_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_OpenPolicy2_handle_, NDR_POINTER_REF, "Pointer to Handle (policy_handle)",hf_lsarpc_lsa_OpenPolicy2_handle);

	return offset;
}

static int
lsarpc_dissect_element_lsa_OpenPolicy2_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_policy_hnd(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_OpenPolicy2_handle, PIDL_POLHND_OPEN|PIDL_POLHND_TYPE_LSA_POLICY);

	return offset;
}

/* IDL: NTSTATUS lsa_OpenPolicy2( */
/* IDL: [unique(1)] [in] [charset(UTF16)] uint16 *system_name, */
/* IDL: [ref] [in] lsa_ObjectAttribute *attr, */
/* IDL: [in] lsa_PolicyAccessMask access_mask, */
/* IDL: [out] [ref] policy_handle *handle */
/* IDL: ); */

static int
lsarpc_dissect_lsa_OpenPolicy2_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_OpenPolicy2";
	offset = lsarpc_dissect_element_lsa_OpenPolicy2_handle(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);

	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_OpenPolicy2_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_OpenPolicy2";
	offset = lsarpc_dissect_element_lsa_OpenPolicy2_system_name(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_OpenPolicy2_attr(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_OpenPolicy2_access_mask(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	return offset;
}

static int
lsarpc_dissect_element_lsa_GetUserName_system_name(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_GetUserName_system_name_, NDR_POINTER_UNIQUE, "Pointer to System Name (uint16)",hf_lsarpc_lsa_GetUserName_system_name);

	return offset;
}

static int
lsarpc_dissect_element_lsa_GetUserName_system_name_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	char *data;

	offset = dissect_ndr_cvstring(tvb, offset, pinfo, tree, di, drep, sizeof(guint16), hf_lsarpc_lsa_GetUserName_system_name, FALSE, &data);
	proto_item_append_text(tree, ": %s", data);

	return offset;
}

static int
lsarpc_dissect_element_lsa_GetUserName_account_name(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_GetUserName_account_name_, NDR_POINTER_UNIQUE, "Pointer to Account Name (lsa_String)",hf_lsarpc_lsa_GetUserName_account_name);

	return offset;
}

static int
lsarpc_dissect_element_lsa_GetUserName_account_name_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_String(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_GetUserName_account_name,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_GetUserName_authority_name(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_GetUserName_authority_name_, NDR_POINTER_UNIQUE, "Pointer to Authority Name (lsa_StringPointer)",hf_lsarpc_lsa_GetUserName_authority_name);

	return offset;
}

static int
lsarpc_dissect_element_lsa_GetUserName_authority_name_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_StringPointer(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_GetUserName_authority_name,0);

	return offset;
}

/* IDL: NTSTATUS lsa_GetUserName( */
/* IDL: [unique(1)] [in] [charset(UTF16)] uint16 *system_name, */
/* IDL: [out] [unique(1)] [in] lsa_String *account_name, */
/* IDL: [out] [unique(1)] [in] lsa_StringPointer *authority_name */
/* IDL: ); */

static int
lsarpc_dissect_lsa_GetUserName_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_GetUserName";
	offset = lsarpc_dissect_element_lsa_GetUserName_account_name(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);

	offset = lsarpc_dissect_element_lsa_GetUserName_authority_name(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);

	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_GetUserName_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_GetUserName";
	offset = lsarpc_dissect_element_lsa_GetUserName_system_name(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_GetUserName_account_name(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_GetUserName_authority_name(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	return offset;
}

static int
lsarpc_dissect_element_lsa_QueryInfoPolicy2_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_QueryInfoPolicy2_handle_, NDR_POINTER_REF, "Pointer to Handle (policy_handle)",hf_lsarpc_lsa_QueryInfoPolicy2_handle);

	return offset;
}

static int
lsarpc_dissect_element_lsa_QueryInfoPolicy2_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_policy_hnd(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_QueryInfoPolicy2_handle, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_QueryInfoPolicy2_level(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_enum_lsa_PolicyInfo(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_QueryInfoPolicy2_level, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_QueryInfoPolicy2_info(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_QueryInfoPolicy2_info_, NDR_POINTER_UNIQUE, "Pointer to Info (lsa_PolicyInformation)",hf_lsarpc_lsa_QueryInfoPolicy2_info);

	return offset;
}

static int
lsarpc_dissect_element_lsa_QueryInfoPolicy2_info_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_lsa_PolicyInformation(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_QueryInfoPolicy2_info, 0);

	return offset;
}

/* IDL: NTSTATUS lsa_QueryInfoPolicy2( */
/* IDL: [ref] [in] policy_handle *handle, */
/* IDL: [in] lsa_PolicyInfo level, */
/* IDL: [unique(1)] [out] [switch_is(level)] lsa_PolicyInformation *info */
/* IDL: ); */

static int
lsarpc_dissect_lsa_QueryInfoPolicy2_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_QueryInfoPolicy2";
	offset = lsarpc_dissect_element_lsa_QueryInfoPolicy2_info(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);

	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_QueryInfoPolicy2_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_QueryInfoPolicy2";
	offset = lsarpc_dissect_element_lsa_QueryInfoPolicy2_handle(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_QueryInfoPolicy2_level(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	return offset;
}

static int
lsarpc_dissect_element_lsa_SetInfoPolicy2_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_SetInfoPolicy2_handle_, NDR_POINTER_REF, "Pointer to Handle (policy_handle)",hf_lsarpc_lsa_SetInfoPolicy2_handle);

	return offset;
}

static int
lsarpc_dissect_element_lsa_SetInfoPolicy2_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_policy_hnd(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_SetInfoPolicy2_handle, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_SetInfoPolicy2_level(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_enum_lsa_PolicyInfo(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_SetInfoPolicy2_level, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_SetInfoPolicy2_info(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_SetInfoPolicy2_info_, NDR_POINTER_REF, "Pointer to Info (lsa_PolicyInformation)",hf_lsarpc_lsa_SetInfoPolicy2_info);

	return offset;
}

static int
lsarpc_dissect_element_lsa_SetInfoPolicy2_info_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_lsa_PolicyInformation(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_SetInfoPolicy2_info, 0);

	return offset;
}

/* IDL: NTSTATUS lsa_SetInfoPolicy2( */
/* IDL: [ref] [in] policy_handle *handle, */
/* IDL: [in] lsa_PolicyInfo level, */
/* IDL: [ref] [in] [switch_is(level)] lsa_PolicyInformation *info */
/* IDL: ); */

static int
lsarpc_dissect_lsa_SetInfoPolicy2_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_SetInfoPolicy2";
	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_SetInfoPolicy2_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_SetInfoPolicy2";
	offset = lsarpc_dissect_element_lsa_SetInfoPolicy2_handle(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_SetInfoPolicy2_level(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_SetInfoPolicy2_info(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	return offset;
}

static int
lsarpc_dissect_element_lsa_QueryTrustedDomainInfoByName_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_QueryTrustedDomainInfoByName_handle_, NDR_POINTER_REF, "Pointer to Handle (policy_handle)",hf_lsarpc_lsa_QueryTrustedDomainInfoByName_handle);

	return offset;
}

static int
lsarpc_dissect_element_lsa_QueryTrustedDomainInfoByName_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_policy_hnd(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_QueryTrustedDomainInfoByName_handle, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_QueryTrustedDomainInfoByName_trusted_domain(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_String(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_QueryTrustedDomainInfoByName_trusted_domain,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_QueryTrustedDomainInfoByName_level(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_enum_lsa_TrustDomInfoEnum(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_QueryTrustedDomainInfoByName_level, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_QueryTrustedDomainInfoByName_info(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_QueryTrustedDomainInfoByName_info_, NDR_POINTER_UNIQUE, "Pointer to Info (lsa_TrustedDomainInfo)",hf_lsarpc_lsa_QueryTrustedDomainInfoByName_info);

	return offset;
}

static int
lsarpc_dissect_element_lsa_QueryTrustedDomainInfoByName_info_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_lsa_TrustedDomainInfo(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_QueryTrustedDomainInfoByName_info, 0);

	return offset;
}

/* IDL: NTSTATUS lsa_QueryTrustedDomainInfoByName( */
/* IDL: [ref] [in] policy_handle *handle, */
/* IDL: [in] lsa_String trusted_domain, */
/* IDL: [in] lsa_TrustDomInfoEnum level, */
/* IDL: [unique(1)] [out] [switch_is(level)] lsa_TrustedDomainInfo *info */
/* IDL: ); */

static int
lsarpc_dissect_lsa_QueryTrustedDomainInfoByName_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_QueryTrustedDomainInfoByName";
	offset = lsarpc_dissect_element_lsa_QueryTrustedDomainInfoByName_info(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);

	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_QueryTrustedDomainInfoByName_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_QueryTrustedDomainInfoByName";
	offset = lsarpc_dissect_element_lsa_QueryTrustedDomainInfoByName_handle(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_QueryTrustedDomainInfoByName_trusted_domain(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_QueryTrustedDomainInfoByName_level(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	return offset;
}

static int
lsarpc_dissect_element_lsa_SetTrustedDomainInfoByName_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_SetTrustedDomainInfoByName_handle_, NDR_POINTER_REF, "Pointer to Handle (policy_handle)",hf_lsarpc_lsa_SetTrustedDomainInfoByName_handle);

	return offset;
}

static int
lsarpc_dissect_element_lsa_SetTrustedDomainInfoByName_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_policy_hnd(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_SetTrustedDomainInfoByName_handle, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_SetTrustedDomainInfoByName_trusted_domain(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_String(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_SetTrustedDomainInfoByName_trusted_domain,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_SetTrustedDomainInfoByName_level(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_enum_lsa_TrustDomInfoEnum(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_SetTrustedDomainInfoByName_level, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_SetTrustedDomainInfoByName_info(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_SetTrustedDomainInfoByName_info_, NDR_POINTER_UNIQUE, "Pointer to Info (lsa_TrustedDomainInfo)",hf_lsarpc_lsa_SetTrustedDomainInfoByName_info);

	return offset;
}

static int
lsarpc_dissect_element_lsa_SetTrustedDomainInfoByName_info_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_lsa_TrustedDomainInfo(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_SetTrustedDomainInfoByName_info, 0);

	return offset;
}

/* IDL: NTSTATUS lsa_SetTrustedDomainInfoByName( */
/* IDL: [ref] [in] policy_handle *handle, */
/* IDL: [in] lsa_String trusted_domain, */
/* IDL: [in] lsa_TrustDomInfoEnum level, */
/* IDL: [unique(1)] [in] [switch_is(level)] lsa_TrustedDomainInfo *info */
/* IDL: ); */

static int
lsarpc_dissect_lsa_SetTrustedDomainInfoByName_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_SetTrustedDomainInfoByName";
	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_SetTrustedDomainInfoByName_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_SetTrustedDomainInfoByName";
	offset = lsarpc_dissect_element_lsa_SetTrustedDomainInfoByName_handle(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_SetTrustedDomainInfoByName_trusted_domain(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_SetTrustedDomainInfoByName_level(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_SetTrustedDomainInfoByName_info(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	return offset;
}

static int
lsarpc_dissect_element_lsa_EnumTrustedDomainsEx_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_EnumTrustedDomainsEx_handle_, NDR_POINTER_REF, "Pointer to Handle (policy_handle)",hf_lsarpc_lsa_EnumTrustedDomainsEx_handle);

	return offset;
}

static int
lsarpc_dissect_element_lsa_EnumTrustedDomainsEx_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_policy_hnd(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_EnumTrustedDomainsEx_handle, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_EnumTrustedDomainsEx_resume_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_EnumTrustedDomainsEx_resume_handle_, NDR_POINTER_REF, "Pointer to Resume Handle (uint32)",hf_lsarpc_lsa_EnumTrustedDomainsEx_resume_handle);

	return offset;
}

static int
lsarpc_dissect_element_lsa_EnumTrustedDomainsEx_resume_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_EnumTrustedDomainsEx_resume_handle, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_EnumTrustedDomainsEx_domains(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_EnumTrustedDomainsEx_domains_, NDR_POINTER_REF, "Pointer to Domains (lsa_DomainListEx)",hf_lsarpc_lsa_EnumTrustedDomainsEx_domains);

	return offset;
}

static int
lsarpc_dissect_element_lsa_EnumTrustedDomainsEx_domains_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_DomainListEx(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_EnumTrustedDomainsEx_domains,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_EnumTrustedDomainsEx_max_size(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_EnumTrustedDomainsEx_max_size, 0);

	return offset;
}

/* IDL: NTSTATUS lsa_EnumTrustedDomainsEx( */
/* IDL: [ref] [in] policy_handle *handle, */
/* IDL: [out] [ref] [in] uint32 *resume_handle, */
/* IDL: [out] [ref] lsa_DomainListEx *domains, */
/* IDL: [in] uint32 max_size */
/* IDL: ); */

static int
lsarpc_dissect_lsa_EnumTrustedDomainsEx_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_EnumTrustedDomainsEx";
	offset = lsarpc_dissect_element_lsa_EnumTrustedDomainsEx_resume_handle(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);

	offset = lsarpc_dissect_element_lsa_EnumTrustedDomainsEx_domains(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);

	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_EnumTrustedDomainsEx_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_EnumTrustedDomainsEx";
	offset = lsarpc_dissect_element_lsa_EnumTrustedDomainsEx_handle(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_EnumTrustedDomainsEx_resume_handle(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_EnumTrustedDomainsEx_max_size(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	return offset;
}

/* IDL: NTSTATUS lsa_CreateTrustedDomainEx( */
/* IDL:  */
/* IDL: ); */

static int
lsarpc_dissect_lsa_CreateTrustedDomainEx_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_CreateTrustedDomainEx";
	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_CreateTrustedDomainEx_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_CreateTrustedDomainEx";
	return offset;
}

static int
lsarpc_dissect_element_lsa_CloseTrustedDomainEx_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_CloseTrustedDomainEx_handle_, NDR_POINTER_REF, "Pointer to Handle (policy_handle)",hf_lsarpc_lsa_CloseTrustedDomainEx_handle);

	return offset;
}

static int
lsarpc_dissect_element_lsa_CloseTrustedDomainEx_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_policy_hnd(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_CloseTrustedDomainEx_handle, PIDL_POLHND_CLOSE);

	return offset;
}

/* IDL: NTSTATUS lsa_CloseTrustedDomainEx( */
/* IDL: [out] [ref] [in] policy_handle *handle */
/* IDL: ); */

static int
lsarpc_dissect_lsa_CloseTrustedDomainEx_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_CloseTrustedDomainEx";
	offset = lsarpc_dissect_element_lsa_CloseTrustedDomainEx_handle(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);

	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_CloseTrustedDomainEx_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_CloseTrustedDomainEx";
	offset = lsarpc_dissect_element_lsa_CloseTrustedDomainEx_handle(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	return offset;
}

static int
lsarpc_dissect_element_lsa_QueryDomainInformationPolicy_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_QueryDomainInformationPolicy_handle_, NDR_POINTER_REF, "Pointer to Handle (policy_handle)",hf_lsarpc_lsa_QueryDomainInformationPolicy_handle);

	return offset;
}

static int
lsarpc_dissect_element_lsa_QueryDomainInformationPolicy_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_policy_hnd(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_QueryDomainInformationPolicy_handle, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_QueryDomainInformationPolicy_level(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_enum_lsa_DomainInfoEnum(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_QueryDomainInformationPolicy_level, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_QueryDomainInformationPolicy_info(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_QueryDomainInformationPolicy_info_, NDR_POINTER_UNIQUE, "Pointer to Info (lsa_DomainInformationPolicy)",hf_lsarpc_lsa_QueryDomainInformationPolicy_info);

	return offset;
}

static int
lsarpc_dissect_element_lsa_QueryDomainInformationPolicy_info_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_lsa_DomainInformationPolicy(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_QueryDomainInformationPolicy_info, 0);

	return offset;
}

/* IDL: NTSTATUS lsa_QueryDomainInformationPolicy( */
/* IDL: [ref] [in] policy_handle *handle, */
/* IDL: [in] lsa_DomainInfoEnum level, */
/* IDL: [unique(1)] [out] [switch_is(level)] lsa_DomainInformationPolicy *info */
/* IDL: ); */

static int
lsarpc_dissect_lsa_QueryDomainInformationPolicy_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_QueryDomainInformationPolicy";
	offset = lsarpc_dissect_element_lsa_QueryDomainInformationPolicy_info(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);

	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_QueryDomainInformationPolicy_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_QueryDomainInformationPolicy";
	offset = lsarpc_dissect_element_lsa_QueryDomainInformationPolicy_handle(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_QueryDomainInformationPolicy_level(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	return offset;
}

static int
lsarpc_dissect_element_lsa_SetDomainInformationPolicy_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_SetDomainInformationPolicy_handle_, NDR_POINTER_REF, "Pointer to Handle (policy_handle)",hf_lsarpc_lsa_SetDomainInformationPolicy_handle);

	return offset;
}

static int
lsarpc_dissect_element_lsa_SetDomainInformationPolicy_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_policy_hnd(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_SetDomainInformationPolicy_handle, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_SetDomainInformationPolicy_level(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_enum_lsa_DomainInfoEnum(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_SetDomainInformationPolicy_level, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_SetDomainInformationPolicy_info(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_SetDomainInformationPolicy_info_, NDR_POINTER_UNIQUE, "Pointer to Info (lsa_DomainInformationPolicy)",hf_lsarpc_lsa_SetDomainInformationPolicy_info);

	return offset;
}

static int
lsarpc_dissect_element_lsa_SetDomainInformationPolicy_info_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_lsa_DomainInformationPolicy(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_SetDomainInformationPolicy_info, 0);

	return offset;
}

/* IDL: NTSTATUS lsa_SetDomainInformationPolicy( */
/* IDL: [ref] [in] policy_handle *handle, */
/* IDL: [in] lsa_DomainInfoEnum level, */
/* IDL: [unique(1)] [in] [switch_is(level)] lsa_DomainInformationPolicy *info */
/* IDL: ); */

static int
lsarpc_dissect_lsa_SetDomainInformationPolicy_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_SetDomainInformationPolicy";
	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_SetDomainInformationPolicy_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_SetDomainInformationPolicy";
	offset = lsarpc_dissect_element_lsa_SetDomainInformationPolicy_handle(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_SetDomainInformationPolicy_level(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_SetDomainInformationPolicy_info(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	return offset;
}

static int
lsarpc_dissect_element_lsa_OpenTrustedDomainByName_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_OpenTrustedDomainByName_handle_, NDR_POINTER_REF, "Pointer to Handle (policy_handle)",hf_lsarpc_lsa_OpenTrustedDomainByName_handle);

	return offset;
}

static int
lsarpc_dissect_element_lsa_OpenTrustedDomainByName_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_policy_hnd(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_OpenTrustedDomainByName_handle, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_OpenTrustedDomainByName_name(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_String(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_OpenTrustedDomainByName_name,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_OpenTrustedDomainByName_access_mask(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_bitmap_lsa_DomainAccessMask(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_OpenTrustedDomainByName_access_mask, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_OpenTrustedDomainByName_trustdom_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_OpenTrustedDomainByName_trustdom_handle_, NDR_POINTER_REF, "Pointer to Trustdom Handle (policy_handle)",hf_lsarpc_lsa_OpenTrustedDomainByName_trustdom_handle);

	return offset;
}

static int
lsarpc_dissect_element_lsa_OpenTrustedDomainByName_trustdom_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_policy_hnd(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_OpenTrustedDomainByName_trustdom_handle, PIDL_POLHND_OPEN|PIDL_POLHND_TYPE_LSA_DOMAIN);

	return offset;
}

/* IDL: NTSTATUS lsa_OpenTrustedDomainByName( */
/* IDL: [ref] [in] policy_handle *handle, */
/* IDL: [in] lsa_String name, */
/* IDL: [in] lsa_DomainAccessMask access_mask, */
/* IDL: [out] [ref] policy_handle *trustdom_handle */
/* IDL: ); */

static int
lsarpc_dissect_lsa_OpenTrustedDomainByName_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_OpenTrustedDomainByName";
	offset = lsarpc_dissect_element_lsa_OpenTrustedDomainByName_trustdom_handle(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);

	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_OpenTrustedDomainByName_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_OpenTrustedDomainByName";
	offset = lsarpc_dissect_element_lsa_OpenTrustedDomainByName_handle(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_OpenTrustedDomainByName_name(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_OpenTrustedDomainByName_access_mask(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	return offset;
}

/* IDL: NTSTATUS lsa_TestCall( */
/* IDL:  */
/* IDL: ); */

static int
lsarpc_dissect_lsa_TestCall_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_TestCall";
	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_TestCall_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_TestCall";
	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupSids2_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_LookupSids2_handle_, NDR_POINTER_REF, "Pointer to Handle (policy_handle)",hf_lsarpc_lsa_LookupSids2_handle);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupSids2_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_policy_hnd(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_LookupSids2_handle, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupSids2_sids(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_LookupSids2_sids_, NDR_POINTER_REF, "Pointer to Sids (lsa_SidArray)",hf_lsarpc_lsa_LookupSids2_sids);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupSids2_sids_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_SidArray(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_LookupSids2_sids,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupSids2_domains(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_LookupSids2_domains_, NDR_POINTER_UNIQUE, "Pointer to Domains (lsa_RefDomainList)",hf_lsarpc_lsa_LookupSids2_domains);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupSids2_domains_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_RefDomainList(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_LookupSids2_domains,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupSids2_names(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_LookupSids2_names_, NDR_POINTER_REF, "Pointer to Names (lsa_TransNameArray2)",hf_lsarpc_lsa_LookupSids2_names);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupSids2_names_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_TransNameArray2(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_LookupSids2_names,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupSids2_level(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint16(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_LookupSids2_level, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupSids2_count(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_LookupSids2_count_, NDR_POINTER_REF, "Pointer to Count (uint32)",hf_lsarpc_lsa_LookupSids2_count);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupSids2_count_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_LookupSids2_count, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupSids2_unknown1(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_LookupSids2_unknown1, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupSids2_unknown2(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_LookupSids2_unknown2, 0);

	return offset;
}

/* IDL: NTSTATUS lsa_LookupSids2( */
/* IDL: [ref] [in] policy_handle *handle, */
/* IDL: [ref] [in] lsa_SidArray *sids, */
/* IDL: [out] [unique(1)] lsa_RefDomainList *domains, */
/* IDL: [out] [ref] [in] lsa_TransNameArray2 *names, */
/* IDL: [in] uint16 level, */
/* IDL: [out] [ref] [in] uint32 *count, */
/* IDL: [in] uint32 unknown1, */
/* IDL: [in] uint32 unknown2 */
/* IDL: ); */

static int
lsarpc_dissect_lsa_LookupSids2_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_LookupSids2";
	offset = lsarpc_dissect_element_lsa_LookupSids2_domains(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);

	offset = lsarpc_dissect_element_lsa_LookupSids2_names(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);

	offset = lsarpc_dissect_element_lsa_LookupSids2_count(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);

	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_LookupSids2_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_LookupSids2";
	offset = lsarpc_dissect_element_lsa_LookupSids2_handle(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_LookupSids2_sids(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_LookupSids2_names(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_LookupSids2_level(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_LookupSids2_count(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_LookupSids2_unknown1(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_LookupSids2_unknown2(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupNames2_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_LookupNames2_handle_, NDR_POINTER_REF, "Pointer to Handle (policy_handle)",hf_lsarpc_lsa_LookupNames2_handle);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupNames2_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_policy_hnd(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_LookupNames2_handle, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupNames2_num_names(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_LookupNames2_num_names, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupNames2_names_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_String(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_LookupNames2_names,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupNames2_domains(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_LookupNames2_domains_, NDR_POINTER_UNIQUE, "Pointer to Domains (lsa_RefDomainList)",hf_lsarpc_lsa_LookupNames2_domains);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupNames2_domains_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_RefDomainList(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_LookupNames2_domains,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupNames2_sids(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_LookupNames2_sids_, NDR_POINTER_REF, "Pointer to Sids (lsa_TransSidArray2)",hf_lsarpc_lsa_LookupNames2_sids);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupNames2_sids_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_TransSidArray2(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_LookupNames2_sids,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupNames2_level(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_enum_lsa_LookupNamesLevel(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_LookupNames2_level, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupNames2_count(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_LookupNames2_count_, NDR_POINTER_REF, "Pointer to Count (uint32)",hf_lsarpc_lsa_LookupNames2_count);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupNames2_count_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_LookupNames2_count, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupNames2_unknown1(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_LookupNames2_unknown1, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupNames2_unknown2(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_LookupNames2_unknown2, 0);

	return offset;
}

/* IDL: NTSTATUS lsa_LookupNames2( */
/* IDL: [ref] [in] policy_handle *handle, */
/* IDL: [in] [range(0,1000)] uint32 num_names, */
/* IDL: [in] [size_is(num_names)] lsa_String names[*], */
/* IDL: [out] [unique(1)] lsa_RefDomainList *domains, */
/* IDL: [out] [ref] [in] lsa_TransSidArray2 *sids, */
/* IDL: [in] lsa_LookupNamesLevel level, */
/* IDL: [out] [ref] [in] uint32 *count, */
/* IDL: [in] uint32 unknown1, */
/* IDL: [in] uint32 unknown2 */
/* IDL: ); */

static int
lsarpc_dissect_lsa_LookupNames2_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_LookupNames2";
	offset = lsarpc_dissect_element_lsa_LookupNames2_domains(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);

	offset = lsarpc_dissect_element_lsa_LookupNames2_sids(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);

	offset = lsarpc_dissect_element_lsa_LookupNames2_count(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);

	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_LookupNames2_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_LookupNames2";
	offset = lsarpc_dissect_element_lsa_LookupNames2_handle(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_LookupNames2_num_names(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_LookupNames2_names(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_LookupNames2_sids(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_LookupNames2_level(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_LookupNames2_count(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_LookupNames2_unknown1(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_LookupNames2_unknown2(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	return offset;
}

/* IDL: NTSTATUS lsa_CreateTrustedDomainEx2( */
/* IDL:  */
/* IDL: ); */

static int
lsarpc_dissect_lsa_CreateTrustedDomainEx2_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_CreateTrustedDomainEx2";
	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_CreateTrustedDomainEx2_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_CreateTrustedDomainEx2";
	return offset;
}

/* IDL: NTSTATUS lsa_CREDRWRITE( */
/* IDL:  */
/* IDL: ); */

static int
lsarpc_dissect_lsa_CREDRWRITE_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_CREDRWRITE";
	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_CREDRWRITE_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_CREDRWRITE";
	return offset;
}

/* IDL: NTSTATUS lsa_CREDRREAD( */
/* IDL:  */
/* IDL: ); */

static int
lsarpc_dissect_lsa_CREDRREAD_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_CREDRREAD";
	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_CREDRREAD_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_CREDRREAD";
	return offset;
}

/* IDL: NTSTATUS lsa_CREDRENUMERATE( */
/* IDL:  */
/* IDL: ); */

static int
lsarpc_dissect_lsa_CREDRENUMERATE_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_CREDRENUMERATE";
	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_CREDRENUMERATE_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_CREDRENUMERATE";
	return offset;
}

/* IDL: NTSTATUS lsa_CREDRWRITEDOMAINCREDENTIALS( */
/* IDL:  */
/* IDL: ); */

static int
lsarpc_dissect_lsa_CREDRWRITEDOMAINCREDENTIALS_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_CREDRWRITEDOMAINCREDENTIALS";
	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_CREDRWRITEDOMAINCREDENTIALS_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_CREDRWRITEDOMAINCREDENTIALS";
	return offset;
}

/* IDL: NTSTATUS lsa_CREDRREADDOMAINCREDENTIALS( */
/* IDL:  */
/* IDL: ); */

static int
lsarpc_dissect_lsa_CREDRREADDOMAINCREDENTIALS_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_CREDRREADDOMAINCREDENTIALS";
	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_CREDRREADDOMAINCREDENTIALS_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_CREDRREADDOMAINCREDENTIALS";
	return offset;
}

/* IDL: NTSTATUS lsa_CREDRDELETE( */
/* IDL:  */
/* IDL: ); */

static int
lsarpc_dissect_lsa_CREDRDELETE_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_CREDRDELETE";
	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_CREDRDELETE_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_CREDRDELETE";
	return offset;
}

/* IDL: NTSTATUS lsa_CREDRGETTARGETINFO( */
/* IDL:  */
/* IDL: ); */

static int
lsarpc_dissect_lsa_CREDRGETTARGETINFO_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_CREDRGETTARGETINFO";
	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_CREDRGETTARGETINFO_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_CREDRGETTARGETINFO";
	return offset;
}

/* IDL: NTSTATUS lsa_CREDRPROFILELOADED( */
/* IDL:  */
/* IDL: ); */

static int
lsarpc_dissect_lsa_CREDRPROFILELOADED_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_CREDRPROFILELOADED";
	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_CREDRPROFILELOADED_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_CREDRPROFILELOADED";
	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupNames3_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_LookupNames3_handle_, NDR_POINTER_REF, "Pointer to Handle (policy_handle)",hf_lsarpc_lsa_LookupNames3_handle);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupNames3_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_policy_hnd(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_LookupNames3_handle, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupNames3_num_names(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_LookupNames3_num_names, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupNames3_names_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_String(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_LookupNames3_names,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupNames3_domains(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_LookupNames3_domains_, NDR_POINTER_UNIQUE, "Pointer to Domains (lsa_RefDomainList)",hf_lsarpc_lsa_LookupNames3_domains);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupNames3_domains_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_RefDomainList(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_LookupNames3_domains,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupNames3_sids(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_LookupNames3_sids_, NDR_POINTER_REF, "Pointer to Sids (lsa_TransSidArray3)",hf_lsarpc_lsa_LookupNames3_sids);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupNames3_sids_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_TransSidArray3(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_LookupNames3_sids,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupNames3_level(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_enum_lsa_LookupNamesLevel(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_LookupNames3_level, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupNames3_count(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_LookupNames3_count_, NDR_POINTER_REF, "Pointer to Count (uint32)",hf_lsarpc_lsa_LookupNames3_count);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupNames3_count_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_LookupNames3_count, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupNames3_unknown1(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_LookupNames3_unknown1, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupNames3_unknown2(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_LookupNames3_unknown2, 0);

	return offset;
}

/* IDL: NTSTATUS lsa_LookupNames3( */
/* IDL: [ref] [in] policy_handle *handle, */
/* IDL: [in] [range(0,1000)] uint32 num_names, */
/* IDL: [in] [size_is(num_names)] lsa_String names[*], */
/* IDL: [out] [unique(1)] lsa_RefDomainList *domains, */
/* IDL: [out] [ref] [in] lsa_TransSidArray3 *sids, */
/* IDL: [in] lsa_LookupNamesLevel level, */
/* IDL: [out] [ref] [in] uint32 *count, */
/* IDL: [in] uint32 unknown1, */
/* IDL: [in] uint32 unknown2 */
/* IDL: ); */

static int
lsarpc_dissect_lsa_LookupNames3_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_LookupNames3";
	offset = lsarpc_dissect_element_lsa_LookupNames3_domains(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);

	offset = lsarpc_dissect_element_lsa_LookupNames3_sids(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);

	offset = lsarpc_dissect_element_lsa_LookupNames3_count(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);

	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_LookupNames3_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_LookupNames3";
	offset = lsarpc_dissect_element_lsa_LookupNames3_handle(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_LookupNames3_num_names(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_LookupNames3_names(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_LookupNames3_sids(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_LookupNames3_level(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_LookupNames3_count(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_LookupNames3_unknown1(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_LookupNames3_unknown2(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	return offset;
}

/* IDL: NTSTATUS lsa_CREDRGETSESSIONTYPES( */
/* IDL:  */
/* IDL: ); */

static int
lsarpc_dissect_lsa_CREDRGETSESSIONTYPES_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_CREDRGETSESSIONTYPES";
	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_CREDRGETSESSIONTYPES_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_CREDRGETSESSIONTYPES";
	return offset;
}

/* IDL: NTSTATUS lsa_LSARREGISTERAUDITEVENT( */
/* IDL:  */
/* IDL: ); */

static int
lsarpc_dissect_lsa_LSARREGISTERAUDITEVENT_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_LSARREGISTERAUDITEVENT";
	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_LSARREGISTERAUDITEVENT_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_LSARREGISTERAUDITEVENT";
	return offset;
}

/* IDL: NTSTATUS lsa_LSARGENAUDITEVENT( */
/* IDL:  */
/* IDL: ); */

static int
lsarpc_dissect_lsa_LSARGENAUDITEVENT_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_LSARGENAUDITEVENT";
	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_LSARGENAUDITEVENT_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_LSARGENAUDITEVENT";
	return offset;
}

/* IDL: NTSTATUS lsa_LSARUNREGISTERAUDITEVENT( */
/* IDL:  */
/* IDL: ); */

static int
lsarpc_dissect_lsa_LSARUNREGISTERAUDITEVENT_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_LSARUNREGISTERAUDITEVENT";
	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_LSARUNREGISTERAUDITEVENT_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_LSARUNREGISTERAUDITEVENT";
	return offset;
}

static int
lsarpc_dissect_element_lsa_lsaRQueryForestTrustInformation_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_lsaRQueryForestTrustInformation_handle_, NDR_POINTER_REF, "Pointer to Handle (policy_handle)",hf_lsarpc_lsa_lsaRQueryForestTrustInformation_handle);

	return offset;
}

static int
lsarpc_dissect_element_lsa_lsaRQueryForestTrustInformation_handle_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_policy_hnd(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_lsaRQueryForestTrustInformation_handle, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_lsaRQueryForestTrustInformation_trusted_domain_name(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_lsaRQueryForestTrustInformation_trusted_domain_name_, NDR_POINTER_REF, "Pointer to Trusted Domain Name (lsa_String)",hf_lsarpc_lsa_lsaRQueryForestTrustInformation_trusted_domain_name);

	return offset;
}

static int
lsarpc_dissect_element_lsa_lsaRQueryForestTrustInformation_trusted_domain_name_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_String(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_lsaRQueryForestTrustInformation_trusted_domain_name,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_lsaRQueryForestTrustInformation_unknown(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint16(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_lsaRQueryForestTrustInformation_unknown, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_lsaRQueryForestTrustInformation_forest_trust_info(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_lsaRQueryForestTrustInformation_forest_trust_info_, NDR_POINTER_REF, "Pointer to Forest Trust Info (lsa_ForestTrustInformation)",hf_lsarpc_lsa_lsaRQueryForestTrustInformation_forest_trust_info);

	return offset;
}

static int
lsarpc_dissect_element_lsa_lsaRQueryForestTrustInformation_forest_trust_info_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_embedded_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_lsaRQueryForestTrustInformation_forest_trust_info__, NDR_POINTER_UNIQUE, "Pointer to Forest Trust Info (lsa_ForestTrustInformation)",hf_lsarpc_lsa_lsaRQueryForestTrustInformation_forest_trust_info);

	return offset;
}

static int
lsarpc_dissect_element_lsa_lsaRQueryForestTrustInformation_forest_trust_info__(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_ForestTrustInformation(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_lsaRQueryForestTrustInformation_forest_trust_info,0);

	return offset;
}

/* IDL: NTSTATUS lsa_lsaRQueryForestTrustInformation( */
/* IDL: [ref] [in] policy_handle *handle, */
/* IDL: [in] [ref] lsa_String *trusted_domain_name, */
/* IDL: [in] uint16 unknown, */
/* IDL: [out] [ref] lsa_ForestTrustInformation **forest_trust_info */
/* IDL: ); */

static int
lsarpc_dissect_lsa_lsaRQueryForestTrustInformation_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_lsaRQueryForestTrustInformation";
	offset = lsarpc_dissect_element_lsa_lsaRQueryForestTrustInformation_forest_trust_info(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);

	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_lsaRQueryForestTrustInformation_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_lsaRQueryForestTrustInformation";
	offset = lsarpc_dissect_element_lsa_lsaRQueryForestTrustInformation_handle(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_lsaRQueryForestTrustInformation_trusted_domain_name(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_lsaRQueryForestTrustInformation_unknown(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	return offset;
}

/* IDL: NTSTATUS lsa_LSARSETFORESTTRUSTINFORMATION( */
/* IDL:  */
/* IDL: ); */

static int
lsarpc_dissect_lsa_LSARSETFORESTTRUSTINFORMATION_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_LSARSETFORESTTRUSTINFORMATION";
	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_LSARSETFORESTTRUSTINFORMATION_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_LSARSETFORESTTRUSTINFORMATION";
	return offset;
}

/* IDL: NTSTATUS lsa_CREDRRENAME( */
/* IDL:  */
/* IDL: ); */

static int
lsarpc_dissect_lsa_CREDRRENAME_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_CREDRRENAME";
	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_CREDRRENAME_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_CREDRRENAME";
	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupSids3_sids(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_LookupSids3_sids_, NDR_POINTER_REF, "Pointer to Sids (lsa_SidArray)",hf_lsarpc_lsa_LookupSids3_sids);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupSids3_sids_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_SidArray(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_LookupSids3_sids,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupSids3_domains(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_LookupSids3_domains_, NDR_POINTER_UNIQUE, "Pointer to Domains (lsa_RefDomainList)",hf_lsarpc_lsa_LookupSids3_domains);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupSids3_domains_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_RefDomainList(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_LookupSids3_domains,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupSids3_names(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_LookupSids3_names_, NDR_POINTER_REF, "Pointer to Names (lsa_TransNameArray2)",hf_lsarpc_lsa_LookupSids3_names);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupSids3_names_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_TransNameArray2(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_LookupSids3_names,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupSids3_level(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint16(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_LookupSids3_level, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupSids3_count(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_LookupSids3_count_, NDR_POINTER_REF, "Pointer to Count (uint32)",hf_lsarpc_lsa_LookupSids3_count);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupSids3_count_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_LookupSids3_count, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupSids3_unknown1(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_LookupSids3_unknown1, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupSids3_unknown2(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_LookupSids3_unknown2, 0);

	return offset;
}

/* IDL: NTSTATUS lsa_LookupSids3( */
/* IDL: [ref] [in] lsa_SidArray *sids, */
/* IDL: [out] [unique(1)] lsa_RefDomainList *domains, */
/* IDL: [out] [ref] [in] lsa_TransNameArray2 *names, */
/* IDL: [in] uint16 level, */
/* IDL: [out] [ref] [in] uint32 *count, */
/* IDL: [in] uint32 unknown1, */
/* IDL: [in] uint32 unknown2 */
/* IDL: ); */

static int
lsarpc_dissect_lsa_LookupSids3_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_LookupSids3";
	offset = lsarpc_dissect_element_lsa_LookupSids3_domains(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);

	offset = lsarpc_dissect_element_lsa_LookupSids3_names(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);

	offset = lsarpc_dissect_element_lsa_LookupSids3_count(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);

	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_LookupSids3_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_LookupSids3";
	offset = lsarpc_dissect_element_lsa_LookupSids3_sids(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_LookupSids3_names(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_LookupSids3_level(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_LookupSids3_count(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_LookupSids3_unknown1(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_LookupSids3_unknown2(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupNames4_num_names(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_LookupNames4_num_names, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupNames4_names_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_String(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_LookupNames4_names,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupNames4_domains(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_LookupNames4_domains_, NDR_POINTER_UNIQUE, "Pointer to Domains (lsa_RefDomainList)",hf_lsarpc_lsa_LookupNames4_domains);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupNames4_domains_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_RefDomainList(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_LookupNames4_domains,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupNames4_sids(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_LookupNames4_sids_, NDR_POINTER_REF, "Pointer to Sids (lsa_TransSidArray3)",hf_lsarpc_lsa_LookupNames4_sids);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupNames4_sids_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_struct_lsa_TransSidArray3(tvb,offset,pinfo,tree,di,drep,hf_lsarpc_lsa_LookupNames4_sids,0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupNames4_level(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = lsarpc_dissect_enum_lsa_LookupNamesLevel(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_LookupNames4_level, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupNames4_count(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = dissect_ndr_toplevel_pointer(tvb, offset, pinfo, tree, di, drep, lsarpc_dissect_element_lsa_LookupNames4_count_, NDR_POINTER_REF, "Pointer to Count (uint32)",hf_lsarpc_lsa_LookupNames4_count);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupNames4_count_(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_LookupNames4_count, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupNames4_unknown1(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_LookupNames4_unknown1, 0);

	return offset;
}

static int
lsarpc_dissect_element_lsa_LookupNames4_unknown2(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	offset = PIDL_dissect_uint32(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_lsa_LookupNames4_unknown2, 0);

	return offset;
}

/* IDL: NTSTATUS lsa_LookupNames4( */
/* IDL: [in] [range(0,1000)] uint32 num_names, */
/* IDL: [in] [size_is(num_names)] lsa_String names[*], */
/* IDL: [out] [unique(1)] lsa_RefDomainList *domains, */
/* IDL: [out] [ref] [in] lsa_TransSidArray3 *sids, */
/* IDL: [in] lsa_LookupNamesLevel level, */
/* IDL: [out] [ref] [in] uint32 *count, */
/* IDL: [in] uint32 unknown1, */
/* IDL: [in] uint32 unknown2 */
/* IDL: ); */

static int
lsarpc_dissect_lsa_LookupNames4_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_LookupNames4";
	offset = lsarpc_dissect_element_lsa_LookupNames4_domains(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);

	offset = lsarpc_dissect_element_lsa_LookupNames4_sids(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);

	offset = lsarpc_dissect_element_lsa_LookupNames4_count(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);

	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_LookupNames4_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_LookupNames4";
	offset = lsarpc_dissect_element_lsa_LookupNames4_num_names(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_LookupNames4_names(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_LookupNames4_sids(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_LookupNames4_level(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_LookupNames4_count(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_LookupNames4_unknown1(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	offset = lsarpc_dissect_element_lsa_LookupNames4_unknown2(tvb, offset, pinfo, tree, di, drep);
	offset = dissect_deferred_pointers(pinfo, tvb, offset, di, drep);
	return offset;
}

/* IDL: NTSTATUS lsa_LSAROPENPOLICYSCE( */
/* IDL:  */
/* IDL: ); */

static int
lsarpc_dissect_lsa_LSAROPENPOLICYSCE_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_LSAROPENPOLICYSCE";
	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_LSAROPENPOLICYSCE_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_LSAROPENPOLICYSCE";
	return offset;
}

/* IDL: NTSTATUS lsa_LSARADTREGISTERSECURITYEVENTSOURCE( */
/* IDL:  */
/* IDL: ); */

static int
lsarpc_dissect_lsa_LSARADTREGISTERSECURITYEVENTSOURCE_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_LSARADTREGISTERSECURITYEVENTSOURCE";
	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_LSARADTREGISTERSECURITYEVENTSOURCE_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_LSARADTREGISTERSECURITYEVENTSOURCE";
	return offset;
}

/* IDL: NTSTATUS lsa_LSARADTUNREGISTERSECURITYEVENTSOURCE( */
/* IDL:  */
/* IDL: ); */

static int
lsarpc_dissect_lsa_LSARADTUNREGISTERSECURITYEVENTSOURCE_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_LSARADTUNREGISTERSECURITYEVENTSOURCE";
	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_LSARADTUNREGISTERSECURITYEVENTSOURCE_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_LSARADTUNREGISTERSECURITYEVENTSOURCE";
	return offset;
}

/* IDL: NTSTATUS lsa_LSARADTREPORTSECURITYEVENT( */
/* IDL:  */
/* IDL: ); */

static int
lsarpc_dissect_lsa_LSARADTREPORTSECURITYEVENT_response(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	guint32 status;

	pinfo->dcerpc_procedure_name="lsa_LSARADTREPORTSECURITYEVENT";
	offset = dissect_ntstatus(tvb, offset, pinfo, tree, di, drep, hf_lsarpc_status, &status);

	if (status != 0)
		col_append_fstr(pinfo->cinfo, COL_INFO, ", Error: %s", val_to_str(status, NT_errors, "Unknown NT status 0x%08x"));

	return offset;
}

static int
lsarpc_dissect_lsa_LSARADTREPORTSECURITYEVENT_request(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_)
{
	pinfo->dcerpc_procedure_name="lsa_LSARADTREPORTSECURITYEVENT";
	return offset;
}


static dcerpc_sub_dissector lsarpc_dissectors[] = {
	{ 0, "lsa_Close",
	   lsarpc_dissect_lsa_Close_request, lsarpc_dissect_lsa_Close_response},
	{ 1, "lsa_Delete",
	   lsarpc_dissect_lsa_Delete_request, lsarpc_dissect_lsa_Delete_response},
	{ 2, "lsa_EnumPrivs",
	   lsarpc_dissect_lsa_EnumPrivs_request, lsarpc_dissect_lsa_EnumPrivs_response},
	{ 3, "lsa_QuerySecurity",
	   lsarpc_dissect_lsa_QuerySecurity_request, lsarpc_dissect_lsa_QuerySecurity_response},
	{ 4, "lsa_SetSecObj",
	   lsarpc_dissect_lsa_SetSecObj_request, lsarpc_dissect_lsa_SetSecObj_response},
	{ 5, "lsa_ChangePassword",
	   lsarpc_dissect_lsa_ChangePassword_request, lsarpc_dissect_lsa_ChangePassword_response},
	{ 6, "lsa_OpenPolicy",
	   lsarpc_dissect_lsa_OpenPolicy_request, lsarpc_dissect_lsa_OpenPolicy_response},
	{ 7, "lsa_QueryInfoPolicy",
	   lsarpc_dissect_lsa_QueryInfoPolicy_request, lsarpc_dissect_lsa_QueryInfoPolicy_response},
	{ 8, "lsa_SetInfoPolicy",
	   lsarpc_dissect_lsa_SetInfoPolicy_request, lsarpc_dissect_lsa_SetInfoPolicy_response},
	{ 9, "lsa_ClearAuditLog",
	   lsarpc_dissect_lsa_ClearAuditLog_request, lsarpc_dissect_lsa_ClearAuditLog_response},
	{ 10, "lsa_CreateAccount",
	   lsarpc_dissect_lsa_CreateAccount_request, lsarpc_dissect_lsa_CreateAccount_response},
	{ 11, "lsa_EnumAccounts",
	   lsarpc_dissect_lsa_EnumAccounts_request, lsarpc_dissect_lsa_EnumAccounts_response},
	{ 12, "lsa_CreateTrustedDomain",
	   lsarpc_dissect_lsa_CreateTrustedDomain_request, lsarpc_dissect_lsa_CreateTrustedDomain_response},
	{ 13, "lsa_EnumTrustDom",
	   lsarpc_dissect_lsa_EnumTrustDom_request, lsarpc_dissect_lsa_EnumTrustDom_response},
	{ 14, "lsa_LookupNames",
	   lsarpc_dissect_lsa_LookupNames_request, lsarpc_dissect_lsa_LookupNames_response},
	{ 15, "lsa_LookupSids",
	   lsarpc_dissect_lsa_LookupSids_request, lsarpc_dissect_lsa_LookupSids_response},
	{ 16, "lsa_CreateSecret",
	   lsarpc_dissect_lsa_CreateSecret_request, lsarpc_dissect_lsa_CreateSecret_response},
	{ 17, "lsa_OpenAccount",
	   lsarpc_dissect_lsa_OpenAccount_request, lsarpc_dissect_lsa_OpenAccount_response},
	{ 18, "lsa_EnumPrivsAccount",
	   lsarpc_dissect_lsa_EnumPrivsAccount_request, lsarpc_dissect_lsa_EnumPrivsAccount_response},
	{ 19, "lsa_AddPrivilegesToAccount",
	   lsarpc_dissect_lsa_AddPrivilegesToAccount_request, lsarpc_dissect_lsa_AddPrivilegesToAccount_response},
	{ 20, "lsa_RemovePrivilegesFromAccount",
	   lsarpc_dissect_lsa_RemovePrivilegesFromAccount_request, lsarpc_dissect_lsa_RemovePrivilegesFromAccount_response},
	{ 21, "lsa_GetQuotasForAccount",
	   lsarpc_dissect_lsa_GetQuotasForAccount_request, lsarpc_dissect_lsa_GetQuotasForAccount_response},
	{ 22, "lsa_SetQuotasForAccount",
	   lsarpc_dissect_lsa_SetQuotasForAccount_request, lsarpc_dissect_lsa_SetQuotasForAccount_response},
	{ 23, "lsa_GetSystemAccessAccount",
	   lsarpc_dissect_lsa_GetSystemAccessAccount_request, lsarpc_dissect_lsa_GetSystemAccessAccount_response},
	{ 24, "lsa_SetSystemAccessAccount",
	   lsarpc_dissect_lsa_SetSystemAccessAccount_request, lsarpc_dissect_lsa_SetSystemAccessAccount_response},
	{ 25, "lsa_OpenTrustedDomain",
	   lsarpc_dissect_lsa_OpenTrustedDomain_request, lsarpc_dissect_lsa_OpenTrustedDomain_response},
	{ 26, "lsa_QueryTrustedDomainInfo",
	   lsarpc_dissect_lsa_QueryTrustedDomainInfo_request, lsarpc_dissect_lsa_QueryTrustedDomainInfo_response},
	{ 27, "lsa_SetInformationTrustedDomain",
	   lsarpc_dissect_lsa_SetInformationTrustedDomain_request, lsarpc_dissect_lsa_SetInformationTrustedDomain_response},
	{ 28, "lsa_OpenSecret",
	   lsarpc_dissect_lsa_OpenSecret_request, lsarpc_dissect_lsa_OpenSecret_response},
	{ 29, "lsa_SetSecret",
	   lsarpc_dissect_lsa_SetSecret_request, lsarpc_dissect_lsa_SetSecret_response},
	{ 30, "lsa_QuerySecret",
	   lsarpc_dissect_lsa_QuerySecret_request, lsarpc_dissect_lsa_QuerySecret_response},
	{ 31, "lsa_LookupPrivValue",
	   lsarpc_dissect_lsa_LookupPrivValue_request, lsarpc_dissect_lsa_LookupPrivValue_response},
	{ 32, "lsa_LookupPrivName",
	   lsarpc_dissect_lsa_LookupPrivName_request, lsarpc_dissect_lsa_LookupPrivName_response},
	{ 33, "lsa_LookupPrivDisplayName",
	   lsarpc_dissect_lsa_LookupPrivDisplayName_request, lsarpc_dissect_lsa_LookupPrivDisplayName_response},
	{ 34, "lsa_DeleteObject",
	   lsarpc_dissect_lsa_DeleteObject_request, lsarpc_dissect_lsa_DeleteObject_response},
	{ 35, "lsa_EnumAccountsWithUserRight",
	   lsarpc_dissect_lsa_EnumAccountsWithUserRight_request, lsarpc_dissect_lsa_EnumAccountsWithUserRight_response},
	{ 36, "lsa_EnumAccountRights",
	   lsarpc_dissect_lsa_EnumAccountRights_request, lsarpc_dissect_lsa_EnumAccountRights_response},
	{ 37, "lsa_AddAccountRights",
	   lsarpc_dissect_lsa_AddAccountRights_request, lsarpc_dissect_lsa_AddAccountRights_response},
	{ 38, "lsa_RemoveAccountRights",
	   lsarpc_dissect_lsa_RemoveAccountRights_request, lsarpc_dissect_lsa_RemoveAccountRights_response},
	{ 39, "lsa_QueryTrustedDomainInfoBySid",
	   lsarpc_dissect_lsa_QueryTrustedDomainInfoBySid_request, lsarpc_dissect_lsa_QueryTrustedDomainInfoBySid_response},
	{ 40, "lsa_SetTrustedDomainInfo",
	   lsarpc_dissect_lsa_SetTrustedDomainInfo_request, lsarpc_dissect_lsa_SetTrustedDomainInfo_response},
	{ 41, "lsa_DeleteTrustedDomain",
	   lsarpc_dissect_lsa_DeleteTrustedDomain_request, lsarpc_dissect_lsa_DeleteTrustedDomain_response},
	{ 42, "lsa_StorePrivateData",
	   lsarpc_dissect_lsa_StorePrivateData_request, lsarpc_dissect_lsa_StorePrivateData_response},
	{ 43, "lsa_RetrievePrivateData",
	   lsarpc_dissect_lsa_RetrievePrivateData_request, lsarpc_dissect_lsa_RetrievePrivateData_response},
	{ 44, "lsa_OpenPolicy2",
	   lsarpc_dissect_lsa_OpenPolicy2_request, lsarpc_dissect_lsa_OpenPolicy2_response},
	{ 45, "lsa_GetUserName",
	   lsarpc_dissect_lsa_GetUserName_request, lsarpc_dissect_lsa_GetUserName_response},
	{ 46, "lsa_QueryInfoPolicy2",
	   lsarpc_dissect_lsa_QueryInfoPolicy2_request, lsarpc_dissect_lsa_QueryInfoPolicy2_response},
	{ 47, "lsa_SetInfoPolicy2",
	   lsarpc_dissect_lsa_SetInfoPolicy2_request, lsarpc_dissect_lsa_SetInfoPolicy2_response},
	{ 48, "lsa_QueryTrustedDomainInfoByName",
	   lsarpc_dissect_lsa_QueryTrustedDomainInfoByName_request, lsarpc_dissect_lsa_QueryTrustedDomainInfoByName_response},
	{ 49, "lsa_SetTrustedDomainInfoByName",
	   lsarpc_dissect_lsa_SetTrustedDomainInfoByName_request, lsarpc_dissect_lsa_SetTrustedDomainInfoByName_response},
	{ 50, "lsa_EnumTrustedDomainsEx",
	   lsarpc_dissect_lsa_EnumTrustedDomainsEx_request, lsarpc_dissect_lsa_EnumTrustedDomainsEx_response},
	{ 51, "lsa_CreateTrustedDomainEx",
	   lsarpc_dissect_lsa_CreateTrustedDomainEx_request, lsarpc_dissect_lsa_CreateTrustedDomainEx_response},
	{ 52, "lsa_CloseTrustedDomainEx",
	   lsarpc_dissect_lsa_CloseTrustedDomainEx_request, lsarpc_dissect_lsa_CloseTrustedDomainEx_response},
	{ 53, "lsa_QueryDomainInformationPolicy",
	   lsarpc_dissect_lsa_QueryDomainInformationPolicy_request, lsarpc_dissect_lsa_QueryDomainInformationPolicy_response},
	{ 54, "lsa_SetDomainInformationPolicy",
	   lsarpc_dissect_lsa_SetDomainInformationPolicy_request, lsarpc_dissect_lsa_SetDomainInformationPolicy_response},
	{ 55, "lsa_OpenTrustedDomainByName",
	   lsarpc_dissect_lsa_OpenTrustedDomainByName_request, lsarpc_dissect_lsa_OpenTrustedDomainByName_response},
	{ 56, "lsa_TestCall",
	   lsarpc_dissect_lsa_TestCall_request, lsarpc_dissect_lsa_TestCall_response},
	{ 57, "lsa_LookupSids2",
	   lsarpc_dissect_lsa_LookupSids2_request, lsarpc_dissect_lsa_LookupSids2_response},
	{ 58, "lsa_LookupNames2",
	   lsarpc_dissect_lsa_LookupNames2_request, lsarpc_dissect_lsa_LookupNames2_response},
	{ 59, "lsa_CreateTrustedDomainEx2",
	   lsarpc_dissect_lsa_CreateTrustedDomainEx2_request, lsarpc_dissect_lsa_CreateTrustedDomainEx2_response},
	{ 60, "lsa_CREDRWRITE",
	   lsarpc_dissect_lsa_CREDRWRITE_request, lsarpc_dissect_lsa_CREDRWRITE_response},
	{ 61, "lsa_CREDRREAD",
	   lsarpc_dissect_lsa_CREDRREAD_request, lsarpc_dissect_lsa_CREDRREAD_response},
	{ 62, "lsa_CREDRENUMERATE",
	   lsarpc_dissect_lsa_CREDRENUMERATE_request, lsarpc_dissect_lsa_CREDRENUMERATE_response},
	{ 63, "lsa_CREDRWRITEDOMAINCREDENTIALS",
	   lsarpc_dissect_lsa_CREDRWRITEDOMAINCREDENTIALS_request, lsarpc_dissect_lsa_CREDRWRITEDOMAINCREDENTIALS_response},
	{ 64, "lsa_CREDRREADDOMAINCREDENTIALS",
	   lsarpc_dissect_lsa_CREDRREADDOMAINCREDENTIALS_request, lsarpc_dissect_lsa_CREDRREADDOMAINCREDENTIALS_response},
	{ 65, "lsa_CREDRDELETE",
	   lsarpc_dissect_lsa_CREDRDELETE_request, lsarpc_dissect_lsa_CREDRDELETE_response},
	{ 66, "lsa_CREDRGETTARGETINFO",
	   lsarpc_dissect_lsa_CREDRGETTARGETINFO_request, lsarpc_dissect_lsa_CREDRGETTARGETINFO_response},
	{ 67, "lsa_CREDRPROFILELOADED",
	   lsarpc_dissect_lsa_CREDRPROFILELOADED_request, lsarpc_dissect_lsa_CREDRPROFILELOADED_response},
	{ 68, "lsa_LookupNames3",
	   lsarpc_dissect_lsa_LookupNames3_request, lsarpc_dissect_lsa_LookupNames3_response},
	{ 69, "lsa_CREDRGETSESSIONTYPES",
	   lsarpc_dissect_lsa_CREDRGETSESSIONTYPES_request, lsarpc_dissect_lsa_CREDRGETSESSIONTYPES_response},
	{ 70, "lsa_LSARREGISTERAUDITEVENT",
	   lsarpc_dissect_lsa_LSARREGISTERAUDITEVENT_request, lsarpc_dissect_lsa_LSARREGISTERAUDITEVENT_response},
	{ 71, "lsa_LSARGENAUDITEVENT",
	   lsarpc_dissect_lsa_LSARGENAUDITEVENT_request, lsarpc_dissect_lsa_LSARGENAUDITEVENT_response},
	{ 72, "lsa_LSARUNREGISTERAUDITEVENT",
	   lsarpc_dissect_lsa_LSARUNREGISTERAUDITEVENT_request, lsarpc_dissect_lsa_LSARUNREGISTERAUDITEVENT_response},
	{ 73, "lsa_lsaRQueryForestTrustInformation",
	   lsarpc_dissect_lsa_lsaRQueryForestTrustInformation_request, lsarpc_dissect_lsa_lsaRQueryForestTrustInformation_response},
	{ 74, "lsa_LSARSETFORESTTRUSTINFORMATION",
	   lsarpc_dissect_lsa_LSARSETFORESTTRUSTINFORMATION_request, lsarpc_dissect_lsa_LSARSETFORESTTRUSTINFORMATION_response},
	{ 75, "lsa_CREDRRENAME",
	   lsarpc_dissect_lsa_CREDRRENAME_request, lsarpc_dissect_lsa_CREDRRENAME_response},
	{ 76, "lsa_LookupSids3",
	   lsarpc_dissect_lsa_LookupSids3_request, lsarpc_dissect_lsa_LookupSids3_response},
	{ 77, "lsa_LookupNames4",
	   lsarpc_dissect_lsa_LookupNames4_request, lsarpc_dissect_lsa_LookupNames4_response},
	{ 78, "lsa_LSAROPENPOLICYSCE",
	   lsarpc_dissect_lsa_LSAROPENPOLICYSCE_request, lsarpc_dissect_lsa_LSAROPENPOLICYSCE_response},
	{ 79, "lsa_LSARADTREGISTERSECURITYEVENTSOURCE",
	   lsarpc_dissect_lsa_LSARADTREGISTERSECURITYEVENTSOURCE_request, lsarpc_dissect_lsa_LSARADTREGISTERSECURITYEVENTSOURCE_response},
	{ 80, "lsa_LSARADTUNREGISTERSECURITYEVENTSOURCE",
	   lsarpc_dissect_lsa_LSARADTUNREGISTERSECURITYEVENTSOURCE_request, lsarpc_dissect_lsa_LSARADTUNREGISTERSECURITYEVENTSOURCE_response},
	{ 81, "lsa_LSARADTREPORTSECURITYEVENT",
	   lsarpc_dissect_lsa_LSARADTREPORTSECURITYEVENT_request, lsarpc_dissect_lsa_LSARADTREPORTSECURITYEVENT_response},
	{ 0, NULL, NULL, NULL }
};

void proto_register_dcerpc_lsarpc(void)
{
	static hf_register_info hf[] = {
	{ &hf_lsarpc_lsa_AsciiStringLarge_size, 
	  { "Size", "lsarpc.lsa_AsciiStringLarge.size", FT_UINT16, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_LookupPrivName_luid, 
	  { "Luid", "lsarpc.lsa_LookupPrivName.luid", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_TrustDomainInfoAuthInfo_outgoing_count, 
	  { "Outgoing Count", "lsarpc.lsa_TrustDomainInfoAuthInfo.outgoing_count", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_DomainAccessMask_LSA_DOMAIN_SET_CONTROLLERS, 
	  { "Lsa Domain Set Controllers", "lsarpc.lsa_DomainAccessMask.LSA_DOMAIN_SET_CONTROLLERS", FT_BOOLEAN, 32, TFS(&lsa_DomainAccessMask_LSA_DOMAIN_SET_CONTROLLERS_tfs), ( 0x00000004 ), NULL, HFILL }},
	{ &hf_lsarpc_lsa_Delete_handle, 
	  { "Handle", "lsarpc.lsa_Delete.handle", FT_BYTES, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_PolicyInformation_account_domain, 
	  { "Account Domain", "lsarpc.lsa_PolicyInformation.account_domain", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_DomainInfoKerberos_clock_skew, 
	  { "Clock Skew", "lsarpc.lsa_DomainInfoKerberos.clock_skew", FT_UINT64, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_ForestTrustData_domain_info, 
	  { "Domain Info", "lsarpc.lsa_ForestTrustData.domain_info", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_AddPrivilegesToAccount_handle, 
	  { "Handle", "lsarpc.lsa_AddPrivilegesToAccount.handle", FT_BYTES, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_ObjectAttribute_sec_qos, 
	  { "Sec Qos", "lsarpc.lsa_ObjectAttribute.sec_qos", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_LookupNames3_handle, 
	  { "Handle", "lsarpc.lsa_LookupNames3.handle", FT_BYTES, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_QueryTrustedDomainInfoBySid_level, 
	  { "Level", "lsarpc.lsa_QueryTrustedDomainInfoBySid.level", FT_UINT1632, BASE_DEC, VALS(lsarpc_lsa_TrustDomInfoEnum_vals), 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_OpenTrustedDomain_sid, 
	  { "Sid", "lsarpc.lsa_OpenTrustedDomain.sid", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_EnumAccounts_handle, 
	  { "Handle", "lsarpc.lsa_EnumAccounts.handle", FT_BYTES, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_CreateAccount_sid, 
	  { "Sid", "lsarpc.lsa_CreateAccount.sid", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_ReplicaSourceInfo_account, 
	  { "Account", "lsarpc.lsa_ReplicaSourceInfo.account", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_QueryDomainInformationPolicy_handle, 
	  { "Handle", "lsarpc.lsa_QueryDomainInformationPolicy.handle", FT_BYTES, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_CreateTrustedDomain_info, 
	  { "Info", "lsarpc.lsa_CreateTrustedDomain.info", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_PolicyAccessMask_LSA_POLICY_SET_DEFAULT_QUOTA_LIMITS, 
	  { "Lsa Policy Set Default Quota Limits", "lsarpc.lsa_PolicyAccessMask.LSA_POLICY_SET_DEFAULT_QUOTA_LIMITS", FT_BOOLEAN, 32, TFS(&lsa_PolicyAccessMask_LSA_POLICY_SET_DEFAULT_QUOTA_LIMITS_tfs), ( 0x00000080 ), NULL, HFILL }},
	{ &hf_lsarpc_lsa_PrivilegeSet_set, 
	  { "Set", "lsarpc.lsa_PrivilegeSet.set", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_QuerySecret_new_val, 
	  { "New Val", "lsarpc.lsa_QuerySecret.new_val", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_TranslatedSid2_unknown, 
	  { "Unknown", "lsarpc.lsa_TranslatedSid2.unknown", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_LookupSids2_handle, 
	  { "Handle", "lsarpc.lsa_LookupSids2.handle", FT_BYTES, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_DomainListEx_domains, 
	  { "Domains", "lsarpc.lsa_DomainListEx.domains", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_LookupNames3_num_names, 
	  { "Num Names", "lsarpc.lsa_LookupNames3.num_names", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_EnumTrustedDomainsEx_max_size, 
	  { "Max Size", "lsarpc.lsa_EnumTrustedDomainsEx.max_size", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_LookupPrivName_handle, 
	  { "Handle", "lsarpc.lsa_LookupPrivName.handle", FT_BYTES, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_OpenAccount_handle, 
	  { "Handle", "lsarpc.lsa_OpenAccount.handle", FT_BYTES, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_OpenSecret_access_mask, 
	  { "Access Mask", "lsarpc.lsa_OpenSecret.access_mask", FT_UINT32, BASE_HEX, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_QuerySecurity_sdbuf, 
	  { "Sdbuf", "lsarpc.lsa_QuerySecurity.sdbuf", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_SetTrustedDomainInfoByName_trusted_domain, 
	  { "Trusted Domain", "lsarpc.lsa_SetTrustedDomainInfoByName.trusted_domain", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_CreateTrustedDomain_trustdom_handle, 
	  { "Trustdom Handle", "lsarpc.lsa_CreateTrustedDomain.trustdom_handle", FT_BYTES, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_EnumPrivs_handle, 
	  { "Handle", "lsarpc.lsa_EnumPrivs.handle", FT_BYTES, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_LUID_high, 
	  { "High", "lsarpc.lsa_LUID.high", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_QueryInfoPolicy_handle, 
	  { "Handle", "lsarpc.lsa_QueryInfoPolicy.handle", FT_BYTES, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_PolicyInformation_audit_events, 
	  { "Audit Events", "lsarpc.lsa_PolicyInformation.audit_events", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_TrustedDomainInfo_auth_info, 
	  { "Auth Info", "lsarpc.lsa_TrustedDomainInfo.auth_info", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_PolicyAccessMask_LSA_POLICY_CREATE_PRIVILEGE, 
	  { "Lsa Policy Create Privilege", "lsarpc.lsa_PolicyAccessMask.LSA_POLICY_CREATE_PRIVILEGE", FT_BOOLEAN, 32, TFS(&lsa_PolicyAccessMask_LSA_POLICY_CREATE_PRIVILEGE_tfs), ( 0x00000040 ), NULL, HFILL }},
	{ &hf_lsarpc_lsa_DomainInfoKerberos_service_tkt_lifetime, 
	  { "Service Tkt Lifetime", "lsarpc.lsa_DomainInfoKerberos.service_tkt_lifetime", FT_UINT64, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_CreateSecret_access_mask, 
	  { "Access Mask", "lsarpc.lsa_CreateSecret.access_mask", FT_UINT32, BASE_HEX, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_GetUserName_authority_name, 
	  { "Authority Name", "lsarpc.lsa_GetUserName.authority_name", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_AuditFullSetInfo_shutdown_on_full, 
	  { "Shutdown On Full", "lsarpc.lsa_AuditFullSetInfo.shutdown_on_full", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_RemoveAccountRights_unknown, 
	  { "Unknown", "lsarpc.lsa_RemoveAccountRights.unknown", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_LookupNames4_unknown1, 
	  { "Unknown1", "lsarpc.lsa_LookupNames4.unknown1", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_secret_access_mask, 
	  { "Access Mask", "lsarpc.policy.access_mask", FT_UINT32, BASE_HEX, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_DeleteTrustedDomain_dom_sid, 
	  { "Dom Sid", "lsarpc.lsa_DeleteTrustedDomain.dom_sid", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_LookupNames4_names, 
	  { "Names", "lsarpc.lsa_LookupNames4.names", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_ForestTrustRecord_forest_trust_data, 
	  { "Forest Trust Data", "lsarpc.lsa_ForestTrustRecord.forest_trust_data", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_PolicyInformation_role, 
	  { "Role", "lsarpc.lsa_PolicyInformation.role", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_PolicyInformation_audit_log, 
	  { "Audit Log", "lsarpc.lsa_PolicyInformation.audit_log", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_DomainAccessMask_LSA_DOMAIN_QUERY_DOMAIN_NAME, 
	  { "Lsa Domain Query Domain Name", "lsarpc.lsa_DomainAccessMask.LSA_DOMAIN_QUERY_DOMAIN_NAME", FT_BOOLEAN, 32, TFS(&lsa_DomainAccessMask_LSA_DOMAIN_QUERY_DOMAIN_NAME_tfs), ( 0x00000001 ), NULL, HFILL }},
	{ &hf_lsarpc_lsa_PolicyInformation_dns, 
	  { "Dns", "lsarpc.lsa_PolicyInformation.dns", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_lsaRQueryForestTrustInformation_trusted_domain_name, 
	  { "Trusted Domain Name", "lsarpc.lsa_lsaRQueryForestTrustInformation.trusted_domain_name", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_QueryTrustedDomainInfoByName_trusted_domain, 
	  { "Trusted Domain", "lsarpc.lsa_QueryTrustedDomainInfoByName.trusted_domain", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_OpenPolicy2_handle, 
	  { "Handle", "lsarpc.lsa_OpenPolicy2.handle", FT_BYTES, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_EnumAccountsWithUserRight_handle, 
	  { "Handle", "lsarpc.lsa_EnumAccountsWithUserRight.handle", FT_BYTES, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_TrustDomainInfoAuthInfo_incoming_count, 
	  { "Incoming Count", "lsarpc.lsa_TrustDomainInfoAuthInfo.incoming_count", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_RemoveAccountRights_rights, 
	  { "Rights", "lsarpc.lsa_RemoveAccountRights.rights", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_SetSecret_sec_handle, 
	  { "Sec Handle", "lsarpc.lsa_SetSecret.sec_handle", FT_BYTES, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_PolicyAccessMask_LSA_POLICY_CREATE_SECRET, 
	  { "Lsa Policy Create Secret", "lsarpc.lsa_PolicyAccessMask.LSA_POLICY_CREATE_SECRET", FT_BOOLEAN, 32, TFS(&lsa_PolicyAccessMask_LSA_POLICY_CREATE_SECRET_tfs), ( 0x00000020 ), NULL, HFILL }},
	{ &hf_lsarpc_lsa_OpenTrustedDomainByName_access_mask, 
	  { "Access Mask", "lsarpc.lsa_OpenTrustedDomainByName.access_mask", FT_UINT32, BASE_HEX, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_RightAttribute_name, 
	  { "Name", "lsarpc.lsa_RightAttribute.name", FT_STRING, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_TrustDomainInfoPassword_old_password, 
	  { "Old Password", "lsarpc.lsa_TrustDomainInfoPassword.old_password", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_DomainInfoKerberos_user_tkt_renewaltime, 
	  { "User Tkt Renewaltime", "lsarpc.lsa_DomainInfoKerberos.user_tkt_renewaltime", FT_UINT64, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_LUID_low, 
	  { "Low", "lsarpc.lsa_LUID.low", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_LookupNames3_names, 
	  { "Names", "lsarpc.lsa_LookupNames3.names", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_QueryTrustedDomainInfoBySid_dom_sid, 
	  { "Dom Sid", "lsarpc.lsa_QueryTrustedDomainInfoBySid.dom_sid", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_TrustDomainInfo11_info_ex, 
	  { "Info Ex", "lsarpc.lsa_TrustDomainInfo11.info_ex", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_LookupSids_names, 
	  { "Names", "lsarpc.lsa_LookupSids.names", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_OpenTrustedDomain_access_mask, 
	  { "Access Mask", "lsarpc.lsa_OpenTrustedDomain.access_mask", FT_UINT32, BASE_HEX, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_RefDomainList_max_size, 
	  { "Max Size", "lsarpc.lsa_RefDomainList.max_size", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_TransSidArray_sids, 
	  { "Sids", "lsarpc.lsa_TransSidArray.sids", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_TrustDomainInfoInfoEx_trust_attributes, 
	  { "Trust Attributes", "lsarpc.lsa_TrustDomainInfoInfoEx.trust_attributes", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_CreateSecret_sec_handle, 
	  { "Sec Handle", "lsarpc.lsa_CreateSecret.sec_handle", FT_BYTES, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_SetSecret_old_val, 
	  { "Old Val", "lsarpc.lsa_SetSecret.old_val", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_TrustDomainInfoBuffer_last_update_time, 
	  { "Last Update Time", "lsarpc.lsa_TrustDomainInfoBuffer.last_update_time", FT_ABSOLUTE_TIME, ABSOLUTE_TIME_LOCAL, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_DnsDomainInfo_dns_forest, 
	  { "Dns Forest", "lsarpc.lsa_DnsDomainInfo.dns_forest", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_QueryDomainInformationPolicy_info, 
	  { "Info", "lsarpc.lsa_QueryDomainInformationPolicy.info", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_ForestTrustDomainInfo_netbios_domain_name, 
	  { "Netbios Domain Name", "lsarpc.lsa_ForestTrustDomainInfo.netbios_domain_name", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_TrustDomainInfoInfoEx_trust_direction, 
	  { "Trust Direction", "lsarpc.lsa_TrustDomainInfoInfoEx.trust_direction", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_LookupNames3_sids, 
	  { "Sids", "lsarpc.lsa_LookupNames3.sids", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_AuditLogInfo_unknown, 
	  { "Unknown", "lsarpc.lsa_AuditLogInfo.unknown", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_AuditLogInfo_retention_time, 
	  { "Retention Time", "lsarpc.lsa_AuditLogInfo.retention_time", FT_ABSOLUTE_TIME, ABSOLUTE_TIME_LOCAL, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_ObjectAttribute_sec_desc, 
	  { "Sec Desc", "lsarpc.lsa_ObjectAttribute.sec_desc", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_DnsDomainInfo_name, 
	  { "Name", "lsarpc.lsa_DnsDomainInfo.name", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_efs_blob_len, 
	  { "EFS blob size", "lsarpc.efs.blob_size", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_TranslatedSid2_sid_index, 
	  { "Sid Index", "lsarpc.lsa_TranslatedSid2.sid_index", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_QuerySecret_old_mtime, 
	  { "Old Mtime", "lsarpc.lsa_QuerySecret.old_mtime", FT_ABSOLUTE_TIME, ABSOLUTE_TIME_LOCAL, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_OpenTrustedDomain_handle, 
	  { "Handle", "lsarpc.lsa_OpenTrustedDomain.handle", FT_BYTES, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_TransNameArray_names, 
	  { "Names", "lsarpc.lsa_TransNameArray.names", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_DomainAccessMask_LSA_DOMAIN_QUERY_CONTROLLERS, 
	  { "Lsa Domain Query Controllers", "lsarpc.lsa_DomainAccessMask.LSA_DOMAIN_QUERY_CONTROLLERS", FT_BOOLEAN, 32, TFS(&lsa_DomainAccessMask_LSA_DOMAIN_QUERY_CONTROLLERS_tfs), ( 0x00000002 ), NULL, HFILL }},
	{ &hf_lsarpc_lsa_RefDomainList_count, 
	  { "Count", "lsarpc.lsa_RefDomainList.count", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_QueryInfoPolicy2_info, 
	  { "Info", "lsarpc.lsa_QueryInfoPolicy2.info", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_DomainInformationPolicy_kerberos_info, 
	  { "Kerberos Info", "lsarpc.lsa_DomainInformationPolicy.kerberos_info", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_QueryInfoPolicy_info, 
	  { "Info", "lsarpc.lsa_QueryInfoPolicy.info", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_CreateAccount_acct_handle, 
	  { "Acct Handle", "lsarpc.lsa_CreateAccount.acct_handle", FT_BYTES, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_AuditLogInfo_shutdown_in_progress, 
	  { "Shutdown In Progress", "lsarpc.lsa_AuditLogInfo.shutdown_in_progress", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_OpenSecret_handle, 
	  { "Handle", "lsarpc.lsa_OpenSecret.handle", FT_BYTES, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_TrustDomainInfoBuffer_secret_type, 
	  { "Secret Type", "lsarpc.lsa_TrustDomainInfoBuffer.secret_type", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_TrustDomainInfoName_netbios_name, 
	  { "Netbios Name", "lsarpc.lsa_TrustDomainInfoName.netbios_name", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_LookupNames_handle, 
	  { "Handle", "lsarpc.lsa_LookupNames.handle", FT_BYTES, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_EnumTrustDom_max_size, 
	  { "Max Size", "lsarpc.lsa_EnumTrustDom.max_size", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_TrustDomainInfoPassword_password, 
	  { "Password", "lsarpc.lsa_TrustDomainInfoPassword.password", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_ObjectAttribute_object_name, 
	  { "Object Name", "lsarpc.lsa_ObjectAttribute.object_name", FT_STRING, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_CreateTrustedDomain_handle, 
	  { "Handle", "lsarpc.lsa_CreateTrustedDomain.handle", FT_BYTES, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_EnumTrustDom_resume_handle, 
	  { "Resume Handle", "lsarpc.lsa_EnumTrustDom.resume_handle", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_TrustedDomainInfo_info11, 
	  { "Info11", "lsarpc.lsa_TrustedDomainInfo.info11", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_QosInfo_impersonation_level, 
	  { "Impersonation Level", "lsarpc.lsa_QosInfo.impersonation_level", FT_UINT1632, BASE_DEC, VALS(lsarpc_lsa_SecurityImpersonationLevel_vals), 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_QueryInfoPolicy2_level, 
	  { "Level", "lsarpc.lsa_QueryInfoPolicy2.level", FT_UINT1632, BASE_DEC, VALS(lsarpc_lsa_PolicyInfo_vals), 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_TranslatedSid3_sid, 
	  { "Sid", "lsarpc.lsa_TranslatedSid3.sid", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_TrustDomainInfoBasic_netbios_name, 
	  { "Netbios Name", "lsarpc.lsa_TrustDomainInfoBasic.netbios_name", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_PolicyAccessMask_LSA_POLICY_AUDIT_LOG_ADMIN, 
	  { "Lsa Policy Audit Log Admin", "lsarpc.lsa_PolicyAccessMask.LSA_POLICY_AUDIT_LOG_ADMIN", FT_BOOLEAN, 32, TFS(&lsa_PolicyAccessMask_LSA_POLICY_AUDIT_LOG_ADMIN_tfs), ( 0x00000200 ), NULL, HFILL }},
	{ &hf_lsarpc_lsa_ForestTrustInformation_entries, 
	  { "Entries", "lsarpc.lsa_ForestTrustInformation.entries", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_ForestTrustData_top_level_name_ex, 
	  { "Top Level Name Ex", "lsarpc.lsa_ForestTrustData.top_level_name_ex", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_DefaultQuotaInfo_non_paged_pool, 
	  { "Non Paged Pool", "lsarpc.lsa_DefaultQuotaInfo.non_paged_pool", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_ForestTrustBinaryData_length, 
	  { "Length", "lsarpc.lsa_ForestTrustBinaryData.length", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_DefaultQuotaInfo_unknown, 
	  { "Unknown", "lsarpc.lsa_DefaultQuotaInfo.unknown", FT_UINT64, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_QosInfo_len, 
	  { "Len", "lsarpc.lsa_QosInfo.len", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_AuditFullQueryInfo_unknown, 
	  { "Unknown", "lsarpc.lsa_AuditFullQueryInfo.unknown", FT_UINT16, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_LookupNames3_level, 
	  { "Level", "lsarpc.lsa_LookupNames3.level", FT_UINT1632, BASE_DEC, VALS(lsarpc_lsa_LookupNamesLevel_vals), 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_LookupPrivDisplayName_disp_name, 
	  { "Disp Name", "lsarpc.lsa_LookupPrivDisplayName.disp_name", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_LookupNames_level, 
	  { "Level", "lsarpc.lsa_LookupNames.level", FT_UINT1632, BASE_DEC, VALS(lsarpc_lsa_LookupNamesLevel_vals), 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_LookupNames4_count, 
	  { "Count", "lsarpc.lsa_LookupNames4.count", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_LookupNames_names, 
	  { "Names", "lsarpc.lsa_LookupNames.names", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_AccountAccessMask_LSA_ACCOUNT_ADJUST_PRIVILEGES, 
	  { "Lsa Account Adjust Privileges", "lsarpc.lsa_AccountAccessMask.LSA_ACCOUNT_ADJUST_PRIVILEGES", FT_BOOLEAN, 32, TFS(&lsa_AccountAccessMask_LSA_ACCOUNT_ADJUST_PRIVILEGES_tfs), ( 0x00000002 ), NULL, HFILL }},
	{ &hf_lsarpc_lsa_TrustDomainInfo11_data1, 
	  { "Data1", "lsarpc.lsa_TrustDomainInfo11.data1", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_PrivEntry_luid, 
	  { "Luid", "lsarpc.lsa_PrivEntry.luid", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_EnumAccounts_resume_handle, 
	  { "Resume Handle", "lsarpc.lsa_EnumAccounts.resume_handle", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_LookupSids3_level, 
	  { "Level", "lsarpc.lsa_LookupSids3.level", FT_UINT16, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_DATA_BUF_data, 
	  { "Data", "lsarpc.lsa_DATA_BUF.data", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_OpenTrustedDomainByName_name, 
	  { "Name", "lsarpc.lsa_OpenTrustedDomainByName.name", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_DomainListEx_count, 
	  { "Count", "lsarpc.lsa_DomainListEx.count", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_DomainAccessMask_LSA_DOMAIN_QUERY_AUTH, 
	  { "Lsa Domain Query Auth", "lsarpc.lsa_DomainAccessMask.LSA_DOMAIN_QUERY_AUTH", FT_BOOLEAN, 32, TFS(&lsa_DomainAccessMask_LSA_DOMAIN_QUERY_AUTH_tfs), ( 0x00000040 ), NULL, HFILL }},
	{ &hf_lsarpc_lsa_DefaultQuotaInfo_pagefile, 
	  { "Pagefile", "lsarpc.lsa_DefaultQuotaInfo.pagefile", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_DefaultQuotaInfo_min_wss, 
	  { "Min Wss", "lsarpc.lsa_DefaultQuotaInfo.min_wss", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_ForestTrustData_top_level_name, 
	  { "Top Level Name", "lsarpc.lsa_ForestTrustData.top_level_name", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_TranslatedName2_sid_type, 
	  { "Sid Type", "lsarpc.lsa_TranslatedName2.sid_type", FT_UINT1632, BASE_DEC, VALS(lsarpc_lsa_SidType_vals), 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_OpenTrustedDomain_trustdom_handle, 
	  { "Trustdom Handle", "lsarpc.lsa_OpenTrustedDomain.trustdom_handle", FT_BYTES, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_TrustDomainInfoFullInfo_info_ex, 
	  { "Info Ex", "lsarpc.lsa_TrustDomainInfoFullInfo.info_ex", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_DATA_BUF2_data, 
	  { "Data", "lsarpc.lsa_DATA_BUF2.data", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_RemoveAccountRights_handle, 
	  { "Handle", "lsarpc.lsa_RemoveAccountRights.handle", FT_BYTES, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_LookupNames3_count, 
	  { "Count", "lsarpc.lsa_LookupNames3.count", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_LookupNames2_unknown2, 
	  { "Unknown2", "lsarpc.lsa_LookupNames2.unknown2", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_EnumTrustedDomainsEx_resume_handle, 
	  { "Resume Handle", "lsarpc.lsa_EnumTrustedDomainsEx.resume_handle", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_TransNameArray2_count, 
	  { "Count", "lsarpc.lsa_TransNameArray2.count", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_DomainInfo_sid, 
	  { "Sid", "lsarpc.lsa_DomainInfo.sid", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_QueryTrustedDomainInfoByName_level, 
	  { "Level", "lsarpc.lsa_QueryTrustedDomainInfoByName.level", FT_UINT1632, BASE_DEC, VALS(lsarpc_lsa_TrustDomInfoEnum_vals), 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_TrustDomainInfoInfoEx_sid, 
	  { "Sid", "lsarpc.lsa_TrustDomainInfoInfoEx.sid", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_TrustDomainInfoAuthInfo_incoming_previous_auth_info, 
	  { "Incoming Previous Auth Info", "lsarpc.lsa_TrustDomainInfoAuthInfo.incoming_previous_auth_info", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_LookupNames3_domains, 
	  { "Domains", "lsarpc.lsa_LookupNames3.domains", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_SetSecret_new_val, 
	  { "New Val", "lsarpc.lsa_SetSecret.new_val", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_String_string, 
	  { "String", "lsarpc.lsa_String.string", FT_UINT16, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_PrivArray_count, 
	  { "Count", "lsarpc.lsa_PrivArray.count", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_QueryTrustedDomainInfo_level, 
	  { "Level", "lsarpc.lsa_QueryTrustedDomainInfo.level", FT_UINT1632, BASE_DEC, VALS(lsarpc_lsa_TrustDomInfoEnum_vals), 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_DATA_BUF_size, 
	  { "Size", "lsarpc.lsa_DATA_BUF.size", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_QueryDomainInformationPolicy_level, 
	  { "Level", "lsarpc.lsa_QueryDomainInformationPolicy.level", FT_UINT1632, BASE_DEC, VALS(lsarpc_lsa_DomainInfoEnum_vals), 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_DomainAccessMask_LSA_DOMAIN_SET_AUTH, 
	  { "Lsa Domain Set Auth", "lsarpc.lsa_DomainAccessMask.LSA_DOMAIN_SET_AUTH", FT_BOOLEAN, 32, TFS(&lsa_DomainAccessMask_LSA_DOMAIN_SET_AUTH_tfs), ( 0x00000020 ), NULL, HFILL }},
	{ &hf_lsarpc_lsa_StringLarge_string, 
	  { "String", "lsarpc.lsa_StringLarge.string", FT_UINT16, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_DomainInfo_name, 
	  { "Name", "lsarpc.lsa_DomainInfo.name", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_AsciiString_size, 
	  { "Size", "lsarpc.lsa_AsciiString.size", FT_UINT16, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_LookupNames2_sids, 
	  { "Sids", "lsarpc.lsa_LookupNames2.sids", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_DomainAccessMask_LSA_DOMAIN_SET_POSIX, 
	  { "Lsa Domain Set Posix", "lsarpc.lsa_DomainAccessMask.LSA_DOMAIN_SET_POSIX", FT_BOOLEAN, 32, TFS(&lsa_DomainAccessMask_LSA_DOMAIN_SET_POSIX_tfs), ( 0x00000010 ), NULL, HFILL }},
	{ &hf_lsarpc_lsa_SetDomainInformationPolicy_level, 
	  { "Level", "lsarpc.lsa_SetDomainInformationPolicy.level", FT_UINT1632, BASE_DEC, VALS(lsarpc_lsa_DomainInfoEnum_vals), 0, NULL, HFILL }},
	{ &hf_lsarpc_account_access_mask, 
	  { "Access Mask", "lsarpc.policy.access_mask", FT_UINT32, BASE_HEX, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_SetInfoPolicy2_info, 
	  { "Info", "lsarpc.lsa_SetInfoPolicy2.info", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_AsciiStringLarge_string, 
	  { "String", "lsarpc.lsa_AsciiStringLarge.string", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_LookupSids2_level, 
	  { "Level", "lsarpc.lsa_LookupSids2.level", FT_UINT16, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_OpenSecret_sec_handle, 
	  { "Sec Handle", "lsarpc.lsa_OpenSecret.sec_handle", FT_BYTES, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_TrustDomainInfoAuthInfo_incoming_current_auth_info, 
	  { "Incoming Current Auth Info", "lsarpc.lsa_TrustDomainInfoAuthInfo.incoming_current_auth_info", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_DomainInformationPolicy_efs_info, 
	  { "Efs Info", "lsarpc.lsa_DomainInformationPolicy.efs_info", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_EnumAccounts_sids, 
	  { "Sids", "lsarpc.lsa_EnumAccounts.sids", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_ReplicaSourceInfo_source, 
	  { "Source", "lsarpc.lsa_ReplicaSourceInfo.source", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_LookupNames3_unknown1, 
	  { "Unknown1", "lsarpc.lsa_LookupNames3.unknown1", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_QuerySecurity_sec_info, 
	  { "Sec Info", "lsarpc.lsa_QuerySecurity.sec_info", FT_UINT32, BASE_HEX, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_DomainInfoKerberos_enforce_restrictions, 
	  { "Enforce Restrictions", "lsarpc.lsa_DomainInfoKerberos.enforce_restrictions", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_LookupSids2_domains, 
	  { "Domains", "lsarpc.lsa_LookupSids2.domains", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_policy_access_mask, 
	  { "Access Mask", "lsarpc.policy.access_mask", FT_UINT32, BASE_HEX, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_EnumTrustedDomainsEx_domains, 
	  { "Domains", "lsarpc.lsa_EnumTrustedDomainsEx.domains", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_EnumAccounts_num_entries, 
	  { "Num Entries", "lsarpc.lsa_EnumAccounts.num_entries", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_domain_access_mask, 
	  { "Access Mask", "lsarpc.policy.access_mask", FT_UINT32, BASE_HEX, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_TrustedDomainInfo_info_all, 
	  { "Info All", "lsarpc.lsa_TrustedDomainInfo.info_all", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_TrustDomainInfoFullInfo_posix_offset, 
	  { "Posix Offset", "lsarpc.lsa_TrustDomainInfoFullInfo.posix_offset", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_TrustDomainInfoInfoEx_trust_type, 
	  { "Trust Type", "lsarpc.lsa_TrustDomainInfoInfoEx.trust_type", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_DnsDomainInfo_sid, 
	  { "Sid", "lsarpc.lsa_DnsDomainInfo.sid", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_LookupNames_num_names, 
	  { "Num Names", "lsarpc.lsa_LookupNames.num_names", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_ForestTrustDomainInfo_domain_sid, 
	  { "Domain Sid", "lsarpc.lsa_ForestTrustDomainInfo.domain_sid", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_LookupSids_handle, 
	  { "Handle", "lsarpc.lsa_LookupSids.handle", FT_BYTES, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_AsciiString_string, 
	  { "String", "lsarpc.lsa_AsciiString.string", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_TrustedDomainInfo_info_ex, 
	  { "Info Ex", "lsarpc.lsa_TrustedDomainInfo.info_ex", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_RemovePrivilegesFromAccount_handle, 
	  { "Handle", "lsarpc.lsa_RemovePrivilegesFromAccount.handle", FT_BYTES, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_CreateAccount_handle, 
	  { "Handle", "lsarpc.lsa_CreateAccount.handle", FT_BYTES, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_TrustedDomainInfo_name, 
	  { "Name", "lsarpc.lsa_TrustedDomainInfo.name", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_LookupNames4_unknown2, 
	  { "Unknown2", "lsarpc.lsa_LookupNames4.unknown2", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_EnumAccountRights_rights, 
	  { "Rights", "lsarpc.lsa_EnumAccountRights.rights", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_DomainAccessMask_LSA_DOMAIN_QUERY_POSIX, 
	  { "Lsa Domain Query Posix", "lsarpc.lsa_DomainAccessMask.LSA_DOMAIN_QUERY_POSIX", FT_BOOLEAN, 32, TFS(&lsa_DomainAccessMask_LSA_DOMAIN_QUERY_POSIX_tfs), ( 0x00000008 ), NULL, HFILL }},
	{ &hf_lsarpc_lsa_LookupPrivDisplayName_name, 
	  { "Name", "lsarpc.lsa_LookupPrivDisplayName.name", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_PolicyAccessMask_LSA_POLICY_GET_PRIVATE_INFORMATION, 
	  { "Lsa Policy Get Private Information", "lsarpc.lsa_PolicyAccessMask.LSA_POLICY_GET_PRIVATE_INFORMATION", FT_BOOLEAN, 32, TFS(&lsa_PolicyAccessMask_LSA_POLICY_GET_PRIVATE_INFORMATION_tfs), ( 0x00000004 ), NULL, HFILL }},
	{ &hf_lsarpc_lsa_OpenPolicy2_access_mask, 
	  { "Access Mask", "lsarpc.lsa_OpenPolicy2.access_mask", FT_UINT32, BASE_HEX, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_SetInfoPolicy2_handle, 
	  { "Handle", "lsarpc.lsa_SetInfoPolicy2.handle", FT_BYTES, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_sec_desc_buf_len, 
	  { "Sec Desc Buf Len", "lsarpc.sec_desc_buf_len", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_LookupNames2_num_names, 
	  { "Num Names", "lsarpc.lsa_LookupNames2.num_names", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_SetInfoPolicy2_level, 
	  { "Level", "lsarpc.lsa_SetInfoPolicy2.level", FT_UINT1632, BASE_DEC, VALS(lsarpc_lsa_PolicyInfo_vals), 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_EnumPrivsAccount_privs, 
	  { "Privs", "lsarpc.lsa_EnumPrivsAccount.privs", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_OpenAccount_access_mask, 
	  { "Access Mask", "lsarpc.lsa_OpenAccount.access_mask", FT_UINT32, BASE_HEX, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_EnumPrivs_privs, 
	  { "Privs", "lsarpc.lsa_EnumPrivs.privs", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_PolicyAccessMask_LSA_POLICY_TRUST_ADMIN, 
	  { "Lsa Policy Trust Admin", "lsarpc.lsa_PolicyAccessMask.LSA_POLICY_TRUST_ADMIN", FT_BOOLEAN, 32, TFS(&lsa_PolicyAccessMask_LSA_POLICY_TRUST_ADMIN_tfs), ( 0x00000008 ), NULL, HFILL }},
	{ &hf_lsarpc_lsa_AuditLogInfo_percent_full, 
	  { "Percent Full", "lsarpc.lsa_AuditLogInfo.percent_full", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_PolicyInformation_quota, 
	  { "Quota", "lsarpc.lsa_PolicyInformation.quota", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_RemovePrivilegesFromAccount_privs, 
	  { "Privs", "lsarpc.lsa_RemovePrivilegesFromAccount.privs", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_TranslatedSid3_unknown, 
	  { "Unknown", "lsarpc.lsa_TranslatedSid3.unknown", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_TranslatedName_sid_type, 
	  { "Sid Type", "lsarpc.lsa_TranslatedName.sid_type", FT_UINT1632, BASE_DEC, VALS(lsarpc_lsa_SidType_vals), 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_LookupSids2_names, 
	  { "Names", "lsarpc.lsa_LookupSids2.names", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_EnumPrivsAccount_handle, 
	  { "Handle", "lsarpc.lsa_EnumPrivsAccount.handle", FT_BYTES, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_SidArray_sids, 
	  { "Sids", "lsarpc.lsa_SidArray.sids", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_RemoveAccountRights_sid, 
	  { "Sid", "lsarpc.lsa_RemoveAccountRights.sid", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_QueryTrustedDomainInfo_info, 
	  { "Info", "lsarpc.lsa_QueryTrustedDomainInfo.info", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_String_length, 
	  { "Length", "lsarpc.lsa_String.length", FT_UINT16, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_opnum, 
	  { "Operation", "lsarpc.opnum", FT_UINT16, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_PrivilegeSet_count, 
	  { "Count", "lsarpc.lsa_PrivilegeSet.count", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_SetTrustedDomainInfoByName_level, 
	  { "Level", "lsarpc.lsa_SetTrustedDomainInfoByName.level", FT_UINT1632, BASE_DEC, VALS(lsarpc_lsa_TrustDomInfoEnum_vals), 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_LookupPrivDisplayName_language_id, 
	  { "Language Id", "lsarpc.lsa_LookupPrivDisplayName.language_id", FT_UINT16, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_TransSidArray3_sids, 
	  { "Sids", "lsarpc.lsa_TransSidArray3.sids", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_status, 
	  { "NT Error", "lsarpc.status", FT_UINT32, BASE_HEX, VALS(NT_errors), 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_LookupNames_count, 
	  { "Count", "lsarpc.lsa_LookupNames.count", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_TrustDomainInfoAuthInfo_outgoing_previous_auth_info, 
	  { "Outgoing Previous Auth Info", "lsarpc.lsa_TrustDomainInfoAuthInfo.outgoing_previous_auth_info", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_LookupPrivValue_name, 
	  { "Name", "lsarpc.lsa_LookupPrivValue.name", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_ForestTrustBinaryData_data, 
	  { "Data", "lsarpc.lsa_ForestTrustBinaryData.data", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_AccountAccessMask_LSA_ACCOUNT_ADJUST_SYSTEM_ACCESS, 
	  { "Lsa Account Adjust System Access", "lsarpc.lsa_AccountAccessMask.LSA_ACCOUNT_ADJUST_SYSTEM_ACCESS", FT_BOOLEAN, 32, TFS(&lsa_AccountAccessMask_LSA_ACCOUNT_ADJUST_SYSTEM_ACCESS_tfs), ( 0x00000008 ), NULL, HFILL }},
	{ &hf_lsarpc_lsa_TranslatedSid_sid_index, 
	  { "Sid Index", "lsarpc.lsa_TranslatedSid.sid_index", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_PolicyAccessMask_LSA_POLICY_CREATE_ACCOUNT, 
	  { "Lsa Policy Create Account", "lsarpc.lsa_PolicyAccessMask.LSA_POLICY_CREATE_ACCOUNT", FT_BOOLEAN, 32, TFS(&lsa_PolicyAccessMask_LSA_POLICY_CREATE_ACCOUNT_tfs), ( 0x00000010 ), NULL, HFILL }},
	{ &hf_lsarpc_lsa_AsciiStringLarge_length, 
	  { "Length", "lsarpc.lsa_AsciiStringLarge.length", FT_UINT16, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_OpenTrustedDomainByName_trustdom_handle, 
	  { "Trustdom Handle", "lsarpc.lsa_OpenTrustedDomainByName.trustdom_handle", FT_BYTES, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_TransNameArray2_names, 
	  { "Names", "lsarpc.lsa_TransNameArray2.names", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_EnumTrustDom_handle, 
	  { "Handle", "lsarpc.lsa_EnumTrustDom.handle", FT_BYTES, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_CreateAccount_access_mask, 
	  { "Access Mask", "lsarpc.lsa_CreateAccount.access_mask", FT_UINT32, BASE_HEX, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_OpenPolicy2_attr, 
	  { "Attr", "lsarpc.lsa_OpenPolicy2.attr", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_TrustDomainInfoInfoEx_netbios_name, 
	  { "Netbios Name", "lsarpc.lsa_TrustDomainInfoInfoEx.netbios_name", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_ForestTrustRecord_flags, 
	  { "Flags", "lsarpc.lsa_ForestTrustRecord.flags", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_OpenPolicy_system_name, 
	  { "System Name", "lsarpc.lsa_OpenPolicy.system_name", FT_UINT16, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_LookupSids2_sids, 
	  { "Sids", "lsarpc.lsa_LookupSids2.sids", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_TranslatedName_sid_index, 
	  { "Sid Index", "lsarpc.lsa_TranslatedName.sid_index", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_TrustedDomainInfo_password, 
	  { "Password", "lsarpc.lsa_TrustedDomainInfo.password", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_ModificationInfo_db_create_time, 
	  { "Db Create Time", "lsarpc.lsa_ModificationInfo.db_create_time", FT_ABSOLUTE_TIME, ABSOLUTE_TIME_LOCAL, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_PolicyAccessMask_LSA_POLICY_NOTIFICATION, 
	  { "Lsa Policy Notification", "lsarpc.lsa_PolicyAccessMask.LSA_POLICY_NOTIFICATION", FT_BOOLEAN, 32, TFS(&lsa_PolicyAccessMask_LSA_POLICY_NOTIFICATION_tfs), ( 0x00001000 ), NULL, HFILL }},
	{ &hf_lsarpc_lsa_PolicyInformation_domain, 
	  { "Domain", "lsarpc.lsa_PolicyInformation.domain", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_DATA_BUF2_size, 
	  { "Size", "lsarpc.lsa_DATA_BUF2.size", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_QueryTrustedDomainInfoByName_handle, 
	  { "Handle", "lsarpc.lsa_QueryTrustedDomainInfoByName.handle", FT_BYTES, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_PolicyAccessMask_LSA_POLICY_SET_AUDIT_REQUIREMENTS, 
	  { "Lsa Policy Set Audit Requirements", "lsarpc.lsa_PolicyAccessMask.LSA_POLICY_SET_AUDIT_REQUIREMENTS", FT_BOOLEAN, 32, TFS(&lsa_PolicyAccessMask_LSA_POLICY_SET_AUDIT_REQUIREMENTS_tfs), ( 0x00000100 ), NULL, HFILL }},
	{ &hf_lsarpc_lsa_LookupNames2_unknown1, 
	  { "Unknown1", "lsarpc.lsa_LookupNames2.unknown1", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_LookupNames4_domains, 
	  { "Domains", "lsarpc.lsa_LookupNames4.domains", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_LookupSids3_unknown2, 
	  { "Unknown2", "lsarpc.lsa_LookupSids3.unknown2", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_TranslatedSid_sid_type, 
	  { "Sid Type", "lsarpc.lsa_TranslatedSid.sid_type", FT_UINT1632, BASE_DEC, VALS(lsarpc_lsa_SidType_vals), 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_LookupNames2_count, 
	  { "Count", "lsarpc.lsa_LookupNames2.count", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_ForestTrustDomainInfo_dns_domain_name, 
	  { "Dns Domain Name", "lsarpc.lsa_ForestTrustDomainInfo.dns_domain_name", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_AuditLogInfo_next_audit_record, 
	  { "Next Audit Record", "lsarpc.lsa_AuditLogInfo.next_audit_record", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_PrivArray_privs, 
	  { "Privs", "lsarpc.lsa_PrivArray.privs", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_TransSidArray2_sids, 
	  { "Sids", "lsarpc.lsa_TransSidArray2.sids", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_TransSidArray3_count, 
	  { "Count", "lsarpc.lsa_TransSidArray3.count", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_lsaRQueryForestTrustInformation_handle, 
	  { "Handle", "lsarpc.lsa_lsaRQueryForestTrustInformation.handle", FT_BYTES, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_DomainList_count, 
	  { "Count", "lsarpc.lsa_DomainList.count", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_QuerySecret_sec_handle, 
	  { "Sec Handle", "lsarpc.lsa_QuerySecret.sec_handle", FT_BYTES, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_AuditFullQueryInfo_shutdown_on_full, 
	  { "Shutdown On Full", "lsarpc.lsa_AuditFullQueryInfo.shutdown_on_full", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_GetUserName_system_name, 
	  { "System Name", "lsarpc.lsa_GetUserName.system_name", FT_STRING, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_SidArray_num_sids, 
	  { "Num Sids", "lsarpc.lsa_SidArray.num_sids", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_LookupNames4_level, 
	  { "Level", "lsarpc.lsa_LookupNames4.level", FT_UINT1632, BASE_DEC, VALS(lsarpc_lsa_LookupNamesLevel_vals), 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_QueryTrustedDomainInfoBySid_handle, 
	  { "Handle", "lsarpc.lsa_QueryTrustedDomainInfoBySid.handle", FT_BYTES, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_RightSet_names, 
	  { "Names", "lsarpc.lsa_RightSet.names", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_LookupNames_domains, 
	  { "Domains", "lsarpc.lsa_LookupNames.domains", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_LookupSids2_unknown2, 
	  { "Unknown2", "lsarpc.lsa_LookupSids2.unknown2", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_LookupNames_sids, 
	  { "Sids", "lsarpc.lsa_LookupNames.sids", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_EnumAccountsWithUserRight_name, 
	  { "Name", "lsarpc.lsa_EnumAccountsWithUserRight.name", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_LookupPrivName_name, 
	  { "Name", "lsarpc.lsa_LookupPrivName.name", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_PolicyAccessMask_LSA_POLICY_VIEW_LOCAL_INFORMATION, 
	  { "Lsa Policy View Local Information", "lsarpc.lsa_PolicyAccessMask.LSA_POLICY_VIEW_LOCAL_INFORMATION", FT_BOOLEAN, 32, TFS(&lsa_PolicyAccessMask_LSA_POLICY_VIEW_LOCAL_INFORMATION_tfs), ( 0x00000001 ), NULL, HFILL }},
	{ &hf_lsarpc_lsa_LookupNames4_sids, 
	  { "Sids", "lsarpc.lsa_LookupNames4.sids", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_RefDomainList_domains, 
	  { "Domains", "lsarpc.lsa_RefDomainList.domains", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_SetDomainInformationPolicy_info, 
	  { "Info", "lsarpc.lsa_SetDomainInformationPolicy.info", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_SetDomainInformationPolicy_handle, 
	  { "Handle", "lsarpc.lsa_SetDomainInformationPolicy.handle", FT_BYTES, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_PolicyInformation_replica, 
	  { "Replica", "lsarpc.lsa_PolicyInformation.replica", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_TrustDomainInfoInfoAll_info_ex, 
	  { "Info Ex", "lsarpc.lsa_TrustDomainInfoInfoAll.info_ex", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_TransSidArray_count, 
	  { "Count", "lsarpc.lsa_TransSidArray.count", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_TrustDomainInfoFullInfo_auth_info, 
	  { "Auth Info", "lsarpc.lsa_TrustDomainInfoFullInfo.auth_info", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_EnumAccountRights_handle, 
	  { "Handle", "lsarpc.lsa_EnumAccountRights.handle", FT_BYTES, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_AuditLogInfo_time_to_shutdown, 
	  { "Time To Shutdown", "lsarpc.lsa_AuditLogInfo.time_to_shutdown", FT_ABSOLUTE_TIME, ABSOLUTE_TIME_LOCAL, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_AccountAccessMask_LSA_ACCOUNT_VIEW, 
	  { "Lsa Account View", "lsarpc.lsa_AccountAccessMask.LSA_ACCOUNT_VIEW", FT_BOOLEAN, 32, TFS(&lsa_AccountAccessMask_LSA_ACCOUNT_VIEW_tfs), ( 0x00000001 ), NULL, HFILL }},
	{ &hf_lsarpc_lsa_TrustDomainInfoInfoEx_domain_name, 
	  { "Domain Name", "lsarpc.lsa_TrustDomainInfoInfoEx.domain_name", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_LookupSids3_unknown1, 
	  { "Unknown1", "lsarpc.lsa_LookupSids3.unknown1", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_LookupSids2_count, 
	  { "Count", "lsarpc.lsa_LookupSids2.count", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_TrustedDomainInfo_info_basic, 
	  { "Info Basic", "lsarpc.lsa_TrustedDomainInfo.info_basic", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_TrustDomainInfoPosixOffset_posix_offset, 
	  { "Posix Offset", "lsarpc.lsa_TrustDomainInfoPosixOffset.posix_offset", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_OpenSecret_name, 
	  { "Name", "lsarpc.lsa_OpenSecret.name", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_PolicyInformation_db, 
	  { "Db", "lsarpc.lsa_PolicyInformation.db", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_String_name, 
	  { "String", "lsarpc.lsa.string", FT_STRING, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_GetUserName_account_name, 
	  { "Account Name", "lsarpc.lsa_GetUserName.account_name", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_LUIDAttribute_attribute, 
	  { "Attribute", "lsarpc.lsa_LUIDAttribute.attribute", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_DATA_BUF_PTR_buf, 
	  { "Buf", "lsarpc.lsa_DATA_BUF_PTR.buf", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_OpenPolicy_access_mask, 
	  { "Access Mask", "lsarpc.lsa_OpenPolicy.access_mask", FT_UINT32, BASE_HEX, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_LookupSids3_sids, 
	  { "Sids", "lsarpc.lsa_LookupSids3.sids", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_String_size, 
	  { "Size", "lsarpc.lsa_String.size", FT_UINT16, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_TrustDomainInfoAuthInfo_outgoing_current_auth_info, 
	  { "Outgoing Current Auth Info", "lsarpc.lsa_TrustDomainInfoAuthInfo.outgoing_current_auth_info", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_TrustedDomainInfo_posix_offset, 
	  { "Posix Offset", "lsarpc.lsa_TrustedDomainInfo.posix_offset", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_DomainInfoKerberos_unknown6, 
	  { "Unknown6", "lsarpc.lsa_DomainInfoKerberos.unknown6", FT_UINT64, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_LookupSids2_unknown1, 
	  { "Unknown1", "lsarpc.lsa_LookupSids2.unknown1", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_OpenAccount_sid, 
	  { "Sid", "lsarpc.lsa_OpenAccount.sid", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_SetTrustedDomainInfoByName_handle, 
	  { "Handle", "lsarpc.lsa_SetTrustedDomainInfoByName.handle", FT_BYTES, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_DnsDomainInfo_domain_guid, 
	  { "Domain Guid", "lsarpc.lsa_DnsDomainInfo.domain_guid", FT_GUID, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_LUIDAttribute_luid, 
	  { "Luid", "lsarpc.lsa_LUIDAttribute.luid", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_DomainInfoKerberos_user_tkt_lifetime, 
	  { "User Tkt Lifetime", "lsarpc.lsa_DomainInfoKerberos.user_tkt_lifetime", FT_UINT64, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_AddAccountRights_rights, 
	  { "Rights", "lsarpc.lsa_AddAccountRights.rights", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_TrustDomainInfoInfoAll_data1, 
	  { "Data1", "lsarpc.lsa_TrustDomainInfoInfoAll.data1", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_PrivilegeSet_unknown, 
	  { "Unknown", "lsarpc.lsa_PrivilegeSet.unknown", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_ObjectAttribute_root_dir, 
	  { "Root Dir", "lsarpc.lsa_ObjectAttribute.root_dir", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_LookupSids3_names, 
	  { "Names", "lsarpc.lsa_LookupSids3.names", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_CreateSecret_handle, 
	  { "Handle", "lsarpc.lsa_CreateSecret.handle", FT_BYTES, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_StringLarge_length, 
	  { "Length", "lsarpc.lsa_StringLarge.length", FT_UINT16, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_AccountAccessMask_LSA_ACCOUNT_ADJUST_QUOTAS, 
	  { "Lsa Account Adjust Quotas", "lsarpc.lsa_AccountAccessMask.LSA_ACCOUNT_ADJUST_QUOTAS", FT_BOOLEAN, 32, TFS(&lsa_AccountAccessMask_LSA_ACCOUNT_ADJUST_QUOTAS_tfs), ( 0x00000004 ), NULL, HFILL }},
	{ &hf_lsarpc_lsa_LookupNames2_names, 
	  { "Names", "lsarpc.lsa_LookupNames2.names", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_OpenAccount_acct_handle, 
	  { "Acct Handle", "lsarpc.lsa_OpenAccount.acct_handle", FT_BYTES, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_StringPointer_string, 
	  { "String", "lsarpc.lsa_StringPointer.string", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_PolicyAccessMask_LSA_POLICY_SERVER_ADMIN, 
	  { "Lsa Policy Server Admin", "lsarpc.lsa_PolicyAccessMask.LSA_POLICY_SERVER_ADMIN", FT_BOOLEAN, 32, TFS(&lsa_PolicyAccessMask_LSA_POLICY_SERVER_ADMIN_tfs), ( 0x00000400 ), NULL, HFILL }},
	{ &hf_lsarpc_lsa_QuerySecret_old_val, 
	  { "Old Val", "lsarpc.lsa_QuerySecret.old_val", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_DeleteTrustedDomain_handle, 
	  { "Handle", "lsarpc.lsa_DeleteTrustedDomain.handle", FT_BYTES, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_LookupPrivDisplayName_handle, 
	  { "Handle", "lsarpc.lsa_LookupPrivDisplayName.handle", FT_BYTES, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_LookupNames2_domains, 
	  { "Domains", "lsarpc.lsa_LookupNames2.domains", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_EnumPrivs_resume_handle, 
	  { "Resume Handle", "lsarpc.lsa_EnumPrivs.resume_handle", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_LookupNames2_handle, 
	  { "Handle", "lsarpc.lsa_LookupNames2.handle", FT_BYTES, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_SetTrustedDomainInfoByName_info, 
	  { "Info", "lsarpc.lsa_SetTrustedDomainInfoByName.info", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_AddPrivilegesToAccount_privs, 
	  { "Privs", "lsarpc.lsa_AddPrivilegesToAccount.privs", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_Close_handle, 
	  { "Handle", "lsarpc.lsa_Close.handle", FT_BYTES, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_TranslatedName2_name, 
	  { "Name", "lsarpc.lsa_TranslatedName2.name", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_AddAccountRights_sid, 
	  { "Sid", "lsarpc.lsa_AddAccountRights.sid", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_LookupPrivValue_luid, 
	  { "Luid", "lsarpc.lsa_LookupPrivValue.luid", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_PolicyAccessMask_LSA_POLICY_LOOKUP_NAMES, 
	  { "Lsa Policy Lookup Names", "lsarpc.lsa_PolicyAccessMask.LSA_POLICY_LOOKUP_NAMES", FT_BOOLEAN, 32, TFS(&lsa_PolicyAccessMask_LSA_POLICY_LOOKUP_NAMES_tfs), ( 0x00000800 ), NULL, HFILL }},
	{ &hf_lsarpc_lsa_TranslatedName2_unknown, 
	  { "Unknown", "lsarpc.lsa_TranslatedName2.unknown", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_ForestTrustRecord_unknown, 
	  { "Unknown", "lsarpc.lsa_ForestTrustRecord.unknown", FT_UINT64, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_CreateTrustedDomain_access_mask, 
	  { "Access Mask", "lsarpc.lsa_CreateTrustedDomain.access_mask", FT_UINT32, BASE_HEX, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_DomainList_domains, 
	  { "Domains", "lsarpc.lsa_DomainList.domains", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_CreateSecret_name, 
	  { "Name", "lsarpc.lsa_CreateSecret.name", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_AuditEventsInfo_auditing_mode, 
	  { "Auditing Mode", "lsarpc.lsa_AuditEventsInfo.auditing_mode", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_QueryTrustedDomainInfoBySid_info, 
	  { "Info", "lsarpc.lsa_QueryTrustedDomainInfoBySid.info", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_EnumAccountsWithUserRight_sids, 
	  { "Sids", "lsarpc.lsa_EnumAccountsWithUserRight.sids", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_SetInfoPolicy_info, 
	  { "Info", "lsarpc.lsa_SetInfoPolicy.info", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_SidPtr_sid, 
	  { "Sid", "lsarpc.lsa_SidPtr.sid", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_QueryTrustedDomainInfoByName_info, 
	  { "Info", "lsarpc.lsa_QueryTrustedDomainInfoByName.info", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_names, 
	  { "Names", "lsarpc.lookup.names", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_PDAccountInfo_name, 
	  { "Name", "lsarpc.lsa_PDAccountInfo.name", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_QuerySecurity_handle, 
	  { "Handle", "lsarpc.lsa_QuerySecurity.handle", FT_BYTES, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_ForestTrustInformation_count, 
	  { "Count", "lsarpc.lsa_ForestTrustInformation.count", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_lsaRQueryForestTrustInformation_unknown, 
	  { "Unknown", "lsarpc.lsa_lsaRQueryForestTrustInformation.unknown", FT_UINT16, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_LookupSids3_domains, 
	  { "Domains", "lsarpc.lsa_LookupSids3.domains", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_Strings_count, 
	  { "Count", "lsarpc.lsa_Strings.count", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_QueryInfoPolicy2_handle, 
	  { "Handle", "lsarpc.lsa_QueryInfoPolicy2.handle", FT_BYTES, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_QueryTrustedDomainInfo_trustdom_handle, 
	  { "Trustdom Handle", "lsarpc.lsa_QueryTrustedDomainInfo.trustdom_handle", FT_BYTES, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_TrustDomainInfoBuffer_data, 
	  { "Data", "lsarpc.lsa_TrustDomainInfoBuffer.data", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_ObjectAttribute_attributes, 
	  { "Attributes", "lsarpc.lsa_ObjectAttribute.attributes", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_StringLarge_size, 
	  { "Size", "lsarpc.lsa_StringLarge.size", FT_UINT16, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_QosInfo_effective_only, 
	  { "Effective Only", "lsarpc.lsa_QosInfo.effective_only", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_ObjectAttribute_len, 
	  { "Len", "lsarpc.lsa_ObjectAttribute.len", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_OpenPolicy_attr, 
	  { "Attr", "lsarpc.lsa_OpenPolicy.attr", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_TrustDomainInfoBasic_sid, 
	  { "Sid", "lsarpc.lsa_TrustDomainInfoBasic.sid", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_PrivEntry_name, 
	  { "Name", "lsarpc.lsa_PrivEntry.name", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_ServerRole_role, 
	  { "Role", "lsarpc.lsa_ServerRole.role", FT_UINT1632, BASE_DEC, VALS(lsarpc_lsa_PolicyServerRole_vals), 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_TranslatedSid3_sid_type, 
	  { "Sid Type", "lsarpc.lsa_TranslatedSid3.sid_type", FT_UINT1632, BASE_DEC, VALS(lsarpc_lsa_SidType_vals), 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_LookupNames4_num_names, 
	  { "Num Names", "lsarpc.lsa_LookupNames4.num_names", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_ForestTrustRecord_level, 
	  { "Level", "lsarpc.lsa_ForestTrustRecord.level", FT_UINT32, BASE_DEC, VALS(lsarpc_lsa_ForestTrustRecordType_vals), 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_EnumPrivs_max_count, 
	  { "Max Count", "lsarpc.lsa_EnumPrivs.max_count", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_LookupNames2_level, 
	  { "Level", "lsarpc.lsa_LookupNames2.level", FT_UINT1632, BASE_DEC, VALS(lsarpc_lsa_LookupNamesLevel_vals), 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_LookupNames3_unknown2, 
	  { "Unknown2", "lsarpc.lsa_LookupNames3.unknown2", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_DATA_BUF_length, 
	  { "Length", "lsarpc.lsa_DATA_BUF.length", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_Strings_names, 
	  { "Names", "lsarpc.lsa_Strings.names", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_LookupPrivDisplayName_unknown, 
	  { "Unknown", "lsarpc.lsa_LookupPrivDisplayName.unknown", FT_UINT16, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_PolicyInformation_auditfullset, 
	  { "Auditfullset", "lsarpc.lsa_PolicyInformation.auditfullset", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_ForestTrustData_data, 
	  { "Data", "lsarpc.lsa_ForestTrustData.data", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_OpenPolicy_handle, 
	  { "Handle", "lsarpc.lsa_OpenPolicy.handle", FT_BYTES, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_LookupSids_count, 
	  { "Count", "lsarpc.lsa_LookupSids.count", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_DnsDomainInfo_dns_domain, 
	  { "Dns Domain", "lsarpc.lsa_DnsDomainInfo.dns_domain", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_TranslatedName_name, 
	  { "Name", "lsarpc.lsa_TranslatedName.name", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_QueryInfoPolicy_level, 
	  { "Level", "lsarpc.lsa_QueryInfoPolicy.level", FT_UINT1632, BASE_DEC, VALS(lsarpc_lsa_PolicyInfo_vals), 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_LookupSids_domains, 
	  { "Domains", "lsarpc.lsa_LookupSids.domains", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_TranslatedSid_rid, 
	  { "Rid", "lsarpc.lsa_TranslatedSid.rid", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_DomainInfoEfs_efs_blob, 
	  { "Efs Blob", "lsarpc.lsa_DomainInfoEfs.efs_blob", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_RemovePrivilegesFromAccount_remove_all, 
	  { "Remove All", "lsarpc.lsa_RemovePrivilegesFromAccount.remove_all", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_SecretAccessMask_LSA_SECRET_QUERY_VALUE, 
	  { "Lsa Secret Query Value", "lsarpc.lsa_SecretAccessMask.LSA_SECRET_QUERY_VALUE", FT_BOOLEAN, 32, TFS(&lsa_SecretAccessMask_LSA_SECRET_QUERY_VALUE_tfs), ( 0x00000002 ), NULL, HFILL }},
	{ &hf_lsarpc_lsa_AddAccountRights_handle, 
	  { "Handle", "lsarpc.lsa_AddAccountRights.handle", FT_BYTES, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_DomainInfoEfs_blob_size, 
	  { "Blob Size", "lsarpc.lsa_DomainInfoEfs.blob_size", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_OpenPolicy2_system_name, 
	  { "System Name", "lsarpc.lsa_OpenPolicy2.system_name", FT_STRING, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_lsaRQueryForestTrustInformation_forest_trust_info, 
	  { "Forest Trust Info", "lsarpc.lsa_lsaRQueryForestTrustInformation.forest_trust_info", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_DefaultQuotaInfo_max_wss, 
	  { "Max Wss", "lsarpc.lsa_DefaultQuotaInfo.max_wss", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_DefaultQuotaInfo_paged_pool, 
	  { "Paged Pool", "lsarpc.lsa_DefaultQuotaInfo.paged_pool", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_LookupSids_level, 
	  { "Level", "lsarpc.lsa_LookupSids.level", FT_UINT16, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_AuditFullQueryInfo_log_is_full, 
	  { "Log Is Full", "lsarpc.lsa_AuditFullQueryInfo.log_is_full", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_RightSet_count, 
	  { "Count", "lsarpc.lsa_RightSet.count", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_AuditLogInfo_log_size, 
	  { "Log Size", "lsarpc.lsa_AuditLogInfo.log_size", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_AuditEventsInfo_settings, 
	  { "Settings", "lsarpc.lsa_AuditEventsInfo.settings", FT_UINT32, BASE_DEC, VALS(lsarpc_lsa_PolicyAuditPolicy_vals), 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_TranslatedSid2_rid, 
	  { "Rid", "lsarpc.lsa_TranslatedSid2.rid", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_TranslatedSid2_sid_type, 
	  { "Sid Type", "lsarpc.lsa_TranslatedSid2.sid_type", FT_UINT1632, BASE_DEC, VALS(lsarpc_lsa_SidType_vals), 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_OpenTrustedDomainByName_handle, 
	  { "Handle", "lsarpc.lsa_OpenTrustedDomainByName.handle", FT_BYTES, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_EnumTrustedDomainsEx_handle, 
	  { "Handle", "lsarpc.lsa_EnumTrustedDomainsEx.handle", FT_BYTES, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_AsciiString_length, 
	  { "Length", "lsarpc.lsa_AsciiString.length", FT_UINT16, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_TrustDomainInfoInfoAll_posix_offset, 
	  { "Posix Offset", "lsarpc.lsa_TrustDomainInfoInfoAll.posix_offset", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_EnumAccountRights_sid, 
	  { "Sid", "lsarpc.lsa_EnumAccountRights.sid", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_LookupSids_sids, 
	  { "Sids", "lsarpc.lsa_LookupSids.sids", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_TrustDomainInfoInfoAll_auth_info, 
	  { "Auth Info", "lsarpc.lsa_TrustDomainInfoInfoAll.auth_info", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_CloseTrustedDomainEx_handle, 
	  { "Handle", "lsarpc.lsa_CloseTrustedDomainEx.handle", FT_BYTES, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_QosInfo_context_mode, 
	  { "Context Mode", "lsarpc.lsa_QosInfo.context_mode", FT_UINT8, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_PolicyAccessMask_LSA_POLICY_VIEW_AUDIT_INFORMATION, 
	  { "Lsa Policy View Audit Information", "lsarpc.lsa_PolicyAccessMask.LSA_POLICY_VIEW_AUDIT_INFORMATION", FT_BOOLEAN, 32, TFS(&lsa_PolicyAccessMask_LSA_POLICY_VIEW_AUDIT_INFORMATION_tfs), ( 0x00000002 ), NULL, HFILL }},
	{ &hf_lsarpc_lsa_SecretAccessMask_LSA_SECRET_SET_VALUE, 
	  { "Lsa Secret Set Value", "lsarpc.lsa_SecretAccessMask.LSA_SECRET_SET_VALUE", FT_BOOLEAN, 32, TFS(&lsa_SecretAccessMask_LSA_SECRET_SET_VALUE_tfs), ( 0x00000001 ), NULL, HFILL }},
	{ &hf_lsarpc_lsa_EnumTrustDom_domains, 
	  { "Domains", "lsarpc.lsa_EnumTrustDom.domains", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_TransNameArray_count, 
	  { "Count", "lsarpc.lsa_TransNameArray.count", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_PolicyInformation_pd, 
	  { "Pd", "lsarpc.lsa_PolicyInformation.pd", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_TranslatedName2_sid_index, 
	  { "Sid Index", "lsarpc.lsa_TranslatedName2.sid_index", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_PolicyInformation_auditfullquery, 
	  { "Auditfullquery", "lsarpc.lsa_PolicyInformation.auditfullquery", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_ModificationInfo_modified_id, 
	  { "Modified Id", "lsarpc.lsa_ModificationInfo.modified_id", FT_UINT64, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_QuerySecret_new_mtime, 
	  { "New Mtime", "lsarpc.lsa_QuerySecret.new_mtime", FT_ABSOLUTE_TIME, ABSOLUTE_TIME_LOCAL, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_LookupPrivValue_handle, 
	  { "Handle", "lsarpc.lsa_LookupPrivValue.handle", FT_BYTES, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_TransSidArray2_count, 
	  { "Count", "lsarpc.lsa_TransSidArray2.count", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_AuditEventsInfo_count, 
	  { "Count", "lsarpc.lsa_AuditEventsInfo.count", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_TrustedDomainInfo_full_info, 
	  { "Full Info", "lsarpc.lsa_TrustedDomainInfo.full_info", FT_NONE, BASE_NONE, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_SetInfoPolicy_level, 
	  { "Level", "lsarpc.lsa_SetInfoPolicy.level", FT_UINT1632, BASE_DEC, VALS(lsarpc_lsa_PolicyInfo_vals), 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_LookupSids3_count, 
	  { "Count", "lsarpc.lsa_LookupSids3.count", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_TranslatedSid3_sid_index, 
	  { "Sid Index", "lsarpc.lsa_TranslatedSid3.sid_index", FT_UINT32, BASE_DEC, NULL, 0, NULL, HFILL }},
	{ &hf_lsarpc_lsa_SetInfoPolicy_handle, 
	  { "Handle", "lsarpc.lsa_SetInfoPolicy.handle", FT_BYTES, BASE_NONE, NULL, 0, NULL, HFILL }},
	};


	static gint *ett[] = {
		&ett_lsarpc_names,
		&ett_dcerpc_lsarpc,
		&ett_lsarpc_lsa_PolicyAccessMask,
		&ett_lsarpc_lsa_AccountAccessMask,
		&ett_lsarpc_lsa_DomainAccessMask,
		&ett_lsarpc_lsa_SecretAccessMask,
		&ett_lsarpc_security_secinfo,
		&ett_lsarpc_lsa_String,
		&ett_lsarpc_lsa_StringLarge,
		&ett_lsarpc_lsa_Strings,
		&ett_lsarpc_lsa_AsciiString,
		&ett_lsarpc_lsa_AsciiStringLarge,
		&ett_lsarpc_lsa_LUID,
		&ett_lsarpc_lsa_PrivEntry,
		&ett_lsarpc_lsa_PrivArray,
		&ett_lsarpc_lsa_QosInfo,
		&ett_lsarpc_lsa_ObjectAttribute,
		&ett_lsarpc_lsa_AuditLogInfo,
		&ett_lsarpc_lsa_AuditEventsInfo,
		&ett_lsarpc_lsa_DomainInfo,
		&ett_lsarpc_lsa_PDAccountInfo,
		&ett_lsarpc_lsa_ServerRole,
		&ett_lsarpc_lsa_ReplicaSourceInfo,
		&ett_lsarpc_lsa_DefaultQuotaInfo,
		&ett_lsarpc_lsa_ModificationInfo,
		&ett_lsarpc_lsa_AuditFullSetInfo,
		&ett_lsarpc_lsa_AuditFullQueryInfo,
		&ett_lsarpc_lsa_DnsDomainInfo,
		&ett_lsarpc_lsa_PolicyInformation,
		&ett_lsarpc_lsa_SidPtr,
		&ett_lsarpc_lsa_SidArray,
		&ett_lsarpc_lsa_DomainList,
		&ett_lsarpc_lsa_TranslatedSid,
		&ett_lsarpc_lsa_TransSidArray,
		&ett_lsarpc_lsa_RefDomainList,
		&ett_lsarpc_lsa_TranslatedName,
		&ett_lsarpc_lsa_TransNameArray,
		&ett_lsarpc_lsa_LUIDAttribute,
		&ett_lsarpc_lsa_PrivilegeSet,
		&ett_lsarpc_lsa_DATA_BUF,
		&ett_lsarpc_lsa_DATA_BUF2,
		&ett_lsarpc_lsa_TrustDomainInfoName,
		&ett_lsarpc_lsa_TrustDomainInfoPosixOffset,
		&ett_lsarpc_lsa_TrustDomainInfoPassword,
		&ett_lsarpc_lsa_TrustDomainInfoBasic,
		&ett_lsarpc_lsa_TrustDomainInfoInfoEx,
		&ett_lsarpc_lsa_TrustDomainInfoBuffer,
		&ett_lsarpc_lsa_TrustDomainInfoAuthInfo,
		&ett_lsarpc_lsa_TrustDomainInfoFullInfo,
		&ett_lsarpc_lsa_TrustDomainInfo11,
		&ett_lsarpc_lsa_TrustDomainInfoInfoAll,
		&ett_lsarpc_lsa_TrustedDomainInfo,
		&ett_lsarpc_lsa_DATA_BUF_PTR,
		&ett_lsarpc_lsa_RightAttribute,
		&ett_lsarpc_lsa_RightSet,
		&ett_lsarpc_lsa_StringPointer,
		&ett_lsarpc_lsa_DomainListEx,
		&ett_lsarpc_lsa_DomainInfoKerberos,
		&ett_lsarpc_lsa_DomainInfoEfs,
		&ett_lsarpc_lsa_DomainInformationPolicy,
		&ett_lsarpc_lsa_TranslatedName2,
		&ett_lsarpc_lsa_TransNameArray2,
		&ett_lsarpc_lsa_TranslatedSid2,
		&ett_lsarpc_lsa_TransSidArray2,
		&ett_lsarpc_lsa_TranslatedSid3,
		&ett_lsarpc_lsa_TransSidArray3,
		&ett_lsarpc_lsa_ForestTrustBinaryData,
		&ett_lsarpc_lsa_ForestTrustDomainInfo,
		&ett_lsarpc_lsa_ForestTrustData,
		&ett_lsarpc_lsa_ForestTrustRecord,
		&ett_lsarpc_lsa_ForestTrustInformation,
	};

	proto_dcerpc_lsarpc = proto_register_protocol("Local Security Authority", "LSARPC", "lsarpc");
	proto_register_field_array(proto_dcerpc_lsarpc, hf, array_length (hf));
	proto_register_subtree_array(ett, array_length(ett));
}

void proto_reg_handoff_dcerpc_lsarpc(void)
{
	dcerpc_init_uuid(proto_dcerpc_lsarpc, ett_dcerpc_lsarpc,
		&uuid_dcerpc_lsarpc, ver_dcerpc_lsarpc,
		lsarpc_dissectors, hf_lsarpc_opnum);
}
