/* autogenerated by pidl */

/* DO NOT EDIT
	This filter was automatically generated
	from misc.idl and misc.cnf.
	
	Pidl is a perl based IDL compiler for DCE/RPC idl files. 
	It is maintained by the Samba team, not the Wireshark team.
	Instructions on how to download and install Pidl can be 
	found at http://wiki.wireshark.org/Pidl

	$Id: packet-dcerpc-misc.h 53100 2013-11-06 14:31:29Z mmann $
*/


#ifndef __PACKET_DCERPC_MISC_H
#define __PACKET_DCERPC_MISC_H

int misc_dissect_struct_GUID(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_);
int misc_dissect_struct_ndr_syntax_id(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_);
int misc_dissect_struct_policy_handle(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_);
#define SEC_CHAN_NULL (0)
#define SEC_CHAN_LOCAL (1)
#define SEC_CHAN_WKSTA (2)
#define SEC_CHAN_DNS_DOMAIN (3)
#define SEC_CHAN_DOMAIN (4)
#define SEC_CHAN_LANMAN (5)
#define SEC_CHAN_BDC (6)
#define SEC_CHAN_RODC (7)
extern const value_string misc_netr_SchannelType_vals[];
int misc_dissect_enum_netr_SchannelType(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 *param _U_);
int misc_dissect_struct_KRB5_EDATA_NTSTATUS(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_);
#define REG_NONE (0)
#define REG_SZ (1)
#define REG_EXPAND_SZ (2)
#define REG_BINARY (3)
#define REG_DWORD (4)
#define REG_DWORD_BIG_ENDIAN (5)
#define REG_LINK (6)
#define REG_MULTI_SZ (7)
#define REG_RESOURCE_LIST (8)
#define REG_FULL_RESOURCE_DESCRIPTOR (9)
#define REG_RESOURCE_REQUIREMENTS_LIST (10)
#define REG_QWORD (11)
extern const value_string misc_winreg_Type_vals[];
int misc_dissect_enum_winreg_Type(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 *param _U_);
#endif /* __PACKET_DCERPC_MISC_H */
