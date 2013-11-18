/* crc32.c
 * CRC-32 routine
 *
 * $Id: crc32.c 52774 2013-10-22 23:30:26Z mmann $
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
 *
 * Credits:
 *
 * Table from Solomon Peachy
 * Routine from Chris Waters
 */

#include "config.h"

#include <glib.h>
#include <wsutil/crc32.h>

/*****************************************************************/
/*                                                               */
/* CRC32C LOOKUP TABLE                                           */
/* +++================                                           */
/* The following CRC lookup table was generated automagically    */
/* by the Rocksoft^tm Model CRC Algorithm Table Generation       */
/* Program V1.0 using the following model parameters:            */
/*                                                               */
/*    Width   : 4 bytes.                                         */
/*    Poly    : 0x1EDC6F41L                                      */
/*    Reverse : TRUE.                                            */
/*                                                               */
/* For more information on the Rocksoft^tm Model CRC Algorithm,  */
/* see the document titled "A Painless Guide to CRC Error        */
/* Detection Algorithms" by Ross Williams                        */
/* (ross@guest.adelaide.edu.au.). This document is likely to be  */
/* in the FTP archive "ftp.adelaide.edu.au/pub/rocksoft".        */
/*                                                               */
/*****************************************************************/
#define CRC32C(c,d) (c=(c>>8)^crc32c_table[(c^(d))&0xFF])

static const guint32 crc32c_table[256] = {
		0x00000000L, 0xF26B8303L, 0xE13B70F7L, 0x1350F3F4L, 0xC79A971FL,
		0x35F1141CL, 0x26A1E7E8L, 0xD4CA64EBL, 0x8AD958CFL, 0x78B2DBCCL,
		0x6BE22838L, 0x9989AB3BL, 0x4D43CFD0L, 0xBF284CD3L, 0xAC78BF27L,
		0x5E133C24L, 0x105EC76FL, 0xE235446CL, 0xF165B798L, 0x030E349BL,
		0xD7C45070L, 0x25AFD373L, 0x36FF2087L, 0xC494A384L, 0x9A879FA0L,
		0x68EC1CA3L, 0x7BBCEF57L, 0x89D76C54L, 0x5D1D08BFL, 0xAF768BBCL,
		0xBC267848L, 0x4E4DFB4BL, 0x20BD8EDEL, 0xD2D60DDDL, 0xC186FE29L,
		0x33ED7D2AL, 0xE72719C1L, 0x154C9AC2L, 0x061C6936L, 0xF477EA35L,
		0xAA64D611L, 0x580F5512L, 0x4B5FA6E6L, 0xB93425E5L, 0x6DFE410EL,
		0x9F95C20DL, 0x8CC531F9L, 0x7EAEB2FAL, 0x30E349B1L, 0xC288CAB2L,
		0xD1D83946L, 0x23B3BA45L, 0xF779DEAEL, 0x05125DADL, 0x1642AE59L,
		0xE4292D5AL, 0xBA3A117EL, 0x4851927DL, 0x5B016189L, 0xA96AE28AL,
		0x7DA08661L, 0x8FCB0562L, 0x9C9BF696L, 0x6EF07595L, 0x417B1DBCL,
		0xB3109EBFL, 0xA0406D4BL, 0x522BEE48L, 0x86E18AA3L, 0x748A09A0L,
		0x67DAFA54L, 0x95B17957L, 0xCBA24573L, 0x39C9C670L, 0x2A993584L,
		0xD8F2B687L, 0x0C38D26CL, 0xFE53516FL, 0xED03A29BL, 0x1F682198L,
		0x5125DAD3L, 0xA34E59D0L, 0xB01EAA24L, 0x42752927L, 0x96BF4DCCL,
		0x64D4CECFL, 0x77843D3BL, 0x85EFBE38L, 0xDBFC821CL, 0x2997011FL,
		0x3AC7F2EBL, 0xC8AC71E8L, 0x1C661503L, 0xEE0D9600L, 0xFD5D65F4L,
		0x0F36E6F7L, 0x61C69362L, 0x93AD1061L, 0x80FDE395L, 0x72966096L,
		0xA65C047DL, 0x5437877EL, 0x4767748AL, 0xB50CF789L, 0xEB1FCBADL,
		0x197448AEL, 0x0A24BB5AL, 0xF84F3859L, 0x2C855CB2L, 0xDEEEDFB1L,
		0xCDBE2C45L, 0x3FD5AF46L, 0x7198540DL, 0x83F3D70EL, 0x90A324FAL,
		0x62C8A7F9L, 0xB602C312L, 0x44694011L, 0x5739B3E5L, 0xA55230E6L,
		0xFB410CC2L, 0x092A8FC1L, 0x1A7A7C35L, 0xE811FF36L, 0x3CDB9BDDL,
		0xCEB018DEL, 0xDDE0EB2AL, 0x2F8B6829L, 0x82F63B78L, 0x709DB87BL,
		0x63CD4B8FL, 0x91A6C88CL, 0x456CAC67L, 0xB7072F64L, 0xA457DC90L,
		0x563C5F93L, 0x082F63B7L, 0xFA44E0B4L, 0xE9141340L, 0x1B7F9043L,
		0xCFB5F4A8L, 0x3DDE77ABL, 0x2E8E845FL, 0xDCE5075CL, 0x92A8FC17L,
		0x60C37F14L, 0x73938CE0L, 0x81F80FE3L, 0x55326B08L, 0xA759E80BL,
		0xB4091BFFL, 0x466298FCL, 0x1871A4D8L, 0xEA1A27DBL, 0xF94AD42FL,
		0x0B21572CL, 0xDFEB33C7L, 0x2D80B0C4L, 0x3ED04330L, 0xCCBBC033L,
		0xA24BB5A6L, 0x502036A5L, 0x4370C551L, 0xB11B4652L, 0x65D122B9L,
		0x97BAA1BAL, 0x84EA524EL, 0x7681D14DL, 0x2892ED69L, 0xDAF96E6AL,
		0xC9A99D9EL, 0x3BC21E9DL, 0xEF087A76L, 0x1D63F975L, 0x0E330A81L,
		0xFC588982L, 0xB21572C9L, 0x407EF1CAL, 0x532E023EL, 0xA145813DL,
		0x758FE5D6L, 0x87E466D5L, 0x94B49521L, 0x66DF1622L, 0x38CC2A06L,
		0xCAA7A905L, 0xD9F75AF1L, 0x2B9CD9F2L, 0xFF56BD19L, 0x0D3D3E1AL,
		0x1E6DCDEEL, 0xEC064EEDL, 0xC38D26C4L, 0x31E6A5C7L, 0x22B65633L,
		0xD0DDD530L, 0x0417B1DBL, 0xF67C32D8L, 0xE52CC12CL, 0x1747422FL,
		0x49547E0BL, 0xBB3FFD08L, 0xA86F0EFCL, 0x5A048DFFL, 0x8ECEE914L,
		0x7CA56A17L, 0x6FF599E3L, 0x9D9E1AE0L, 0xD3D3E1ABL, 0x21B862A8L,
		0x32E8915CL, 0xC083125FL, 0x144976B4L, 0xE622F5B7L, 0xF5720643L,
		0x07198540L, 0x590AB964L, 0xAB613A67L, 0xB831C993L, 0x4A5A4A90L,
		0x9E902E7BL, 0x6CFBAD78L, 0x7FAB5E8CL, 0x8DC0DD8FL, 0xE330A81AL,
		0x115B2B19L, 0x020BD8EDL, 0xF0605BEEL, 0x24AA3F05L, 0xD6C1BC06L,
		0xC5914FF2L, 0x37FACCF1L, 0x69E9F0D5L, 0x9B8273D6L, 0x88D28022L,
		0x7AB90321L, 0xAE7367CAL, 0x5C18E4C9L, 0x4F48173DL, 0xBD23943EL,
		0xF36E6F75L, 0x0105EC76L, 0x12551F82L, 0xE03E9C81L, 0x34F4F86AL,
		0xC69F7B69L, 0xD5CF889DL, 0x27A40B9EL, 0x79B737BAL, 0x8BDCB4B9L,
		0x988C474DL, 0x6AE7C44EL, 0xBE2DA0A5L, 0x4C4623A6L, 0x5F16D052L,
		0xAD7D5351L };

/*
 * Table for the AUTODIN/HDLC/802.x CRC.
 *
 * Polynomial is
 *
 *  x^32 + x^26 + x^23 + x^22 + x^16 + x^12 + x^11 + x^8 + x^7 +
 *      x^5 + x^4 + x^2 + x + 1
 */
static const guint32 crc32_ccitt_table[256] = {
        0x00000000, 0x77073096, 0xee0e612c, 0x990951ba, 0x076dc419,
        0x706af48f, 0xe963a535, 0x9e6495a3, 0x0edb8832, 0x79dcb8a4,
        0xe0d5e91e, 0x97d2d988, 0x09b64c2b, 0x7eb17cbd, 0xe7b82d07,
        0x90bf1d91, 0x1db71064, 0x6ab020f2, 0xf3b97148, 0x84be41de,
        0x1adad47d, 0x6ddde4eb, 0xf4d4b551, 0x83d385c7, 0x136c9856,
        0x646ba8c0, 0xfd62f97a, 0x8a65c9ec, 0x14015c4f, 0x63066cd9,
        0xfa0f3d63, 0x8d080df5, 0x3b6e20c8, 0x4c69105e, 0xd56041e4,
        0xa2677172, 0x3c03e4d1, 0x4b04d447, 0xd20d85fd, 0xa50ab56b,
        0x35b5a8fa, 0x42b2986c, 0xdbbbc9d6, 0xacbcf940, 0x32d86ce3,
        0x45df5c75, 0xdcd60dcf, 0xabd13d59, 0x26d930ac, 0x51de003a,
        0xc8d75180, 0xbfd06116, 0x21b4f4b5, 0x56b3c423, 0xcfba9599,
        0xb8bda50f, 0x2802b89e, 0x5f058808, 0xc60cd9b2, 0xb10be924,
        0x2f6f7c87, 0x58684c11, 0xc1611dab, 0xb6662d3d, 0x76dc4190,
        0x01db7106, 0x98d220bc, 0xefd5102a, 0x71b18589, 0x06b6b51f,
        0x9fbfe4a5, 0xe8b8d433, 0x7807c9a2, 0x0f00f934, 0x9609a88e,
        0xe10e9818, 0x7f6a0dbb, 0x086d3d2d, 0x91646c97, 0xe6635c01,
        0x6b6b51f4, 0x1c6c6162, 0x856530d8, 0xf262004e, 0x6c0695ed,
        0x1b01a57b, 0x8208f4c1, 0xf50fc457, 0x65b0d9c6, 0x12b7e950,
        0x8bbeb8ea, 0xfcb9887c, 0x62dd1ddf, 0x15da2d49, 0x8cd37cf3,
        0xfbd44c65, 0x4db26158, 0x3ab551ce, 0xa3bc0074, 0xd4bb30e2,
        0x4adfa541, 0x3dd895d7, 0xa4d1c46d, 0xd3d6f4fb, 0x4369e96a,
        0x346ed9fc, 0xad678846, 0xda60b8d0, 0x44042d73, 0x33031de5,
        0xaa0a4c5f, 0xdd0d7cc9, 0x5005713c, 0x270241aa, 0xbe0b1010,
        0xc90c2086, 0x5768b525, 0x206f85b3, 0xb966d409, 0xce61e49f,
        0x5edef90e, 0x29d9c998, 0xb0d09822, 0xc7d7a8b4, 0x59b33d17,
        0x2eb40d81, 0xb7bd5c3b, 0xc0ba6cad, 0xedb88320, 0x9abfb3b6,
        0x03b6e20c, 0x74b1d29a, 0xead54739, 0x9dd277af, 0x04db2615,
        0x73dc1683, 0xe3630b12, 0x94643b84, 0x0d6d6a3e, 0x7a6a5aa8,
        0xe40ecf0b, 0x9309ff9d, 0x0a00ae27, 0x7d079eb1, 0xf00f9344,
        0x8708a3d2, 0x1e01f268, 0x6906c2fe, 0xf762575d, 0x806567cb,
        0x196c3671, 0x6e6b06e7, 0xfed41b76, 0x89d32be0, 0x10da7a5a,
        0x67dd4acc, 0xf9b9df6f, 0x8ebeeff9, 0x17b7be43, 0x60b08ed5,
        0xd6d6a3e8, 0xa1d1937e, 0x38d8c2c4, 0x4fdff252, 0xd1bb67f1,
        0xa6bc5767, 0x3fb506dd, 0x48b2364b, 0xd80d2bda, 0xaf0a1b4c,
        0x36034af6, 0x41047a60, 0xdf60efc3, 0xa867df55, 0x316e8eef,
        0x4669be79, 0xcb61b38c, 0xbc66831a, 0x256fd2a0, 0x5268e236,
        0xcc0c7795, 0xbb0b4703, 0x220216b9, 0x5505262f, 0xc5ba3bbe,
        0xb2bd0b28, 0x2bb45a92, 0x5cb36a04, 0xc2d7ffa7, 0xb5d0cf31,
        0x2cd99e8b, 0x5bdeae1d, 0x9b64c2b0, 0xec63f226, 0x756aa39c,
        0x026d930a, 0x9c0906a9, 0xeb0e363f, 0x72076785, 0x05005713,
        0x95bf4a82, 0xe2b87a14, 0x7bb12bae, 0x0cb61b38, 0x92d28e9b,
        0xe5d5be0d, 0x7cdcefb7, 0x0bdbdf21, 0x86d3d2d4, 0xf1d4e242,
        0x68ddb3f8, 0x1fda836e, 0x81be16cd, 0xf6b9265b, 0x6fb077e1,
        0x18b74777, 0x88085ae6, 0xff0f6a70, 0x66063bca, 0x11010b5c,
        0x8f659eff, 0xf862ae69, 0x616bffd3, 0x166ccf45, 0xa00ae278,
        0xd70dd2ee, 0x4e048354, 0x3903b3c2, 0xa7672661, 0xd06016f7,
        0x4969474d, 0x3e6e77db, 0xaed16a4a, 0xd9d65adc, 0x40df0b66,
        0x37d83bf0, 0xa9bcae53, 0xdebb9ec5, 0x47b2cf7f, 0x30b5ffe9,
        0xbdbdf21c, 0xcabac28a, 0x53b39330, 0x24b4a3a6, 0xbad03605,
        0xcdd70693, 0x54de5729, 0x23d967bf, 0xb3667a2e, 0xc4614ab8,
        0x5d681b02, 0x2a6f2b94, 0xb40bbe37, 0xc30c8ea1, 0x5a05df1b,
        0x2d02ef8d
};

/*
 * Table for the MPEG-2 CRC.
 *
 * Polynomial is
 *
 *  x^32 + x^26 + x^23 + x^22 + x^16 + x^12 + x^11 + x^10 + x^8 +
 *      x^7 + x^5 + x^4 + x^2 + x + 1
 */
static const guint32 crc32_mpeg2_table[256] = {
		0x00000000, 0x04c11db7, 0x09823b6e, 0x0d4326d9, 0x130476dc, 0x17c56b6b,
		0x1a864db2, 0x1e475005, 0x2608edb8, 0x22c9f00f, 0x2f8ad6d6, 0x2b4bcb61,
		0x350c9b64, 0x31cd86d3, 0x3c8ea00a, 0x384fbdbd, 0x4c11db70, 0x48d0c6c7,
		0x4593e01e, 0x4152fda9, 0x5f15adac, 0x5bd4b01b, 0x569796c2, 0x52568b75,
		0x6a1936c8, 0x6ed82b7f, 0x639b0da6, 0x675a1011, 0x791d4014, 0x7ddc5da3,
		0x709f7b7a, 0x745e66cd, 0x9823b6e0, 0x9ce2ab57, 0x91a18d8e, 0x95609039,
		0x8b27c03c, 0x8fe6dd8b, 0x82a5fb52, 0x8664e6e5, 0xbe2b5b58, 0xbaea46ef,
		0xb7a96036, 0xb3687d81, 0xad2f2d84, 0xa9ee3033, 0xa4ad16ea, 0xa06c0b5d,
		0xd4326d90, 0xd0f37027, 0xddb056fe, 0xd9714b49, 0xc7361b4c, 0xc3f706fb,
		0xceb42022, 0xca753d95, 0xf23a8028, 0xf6fb9d9f, 0xfbb8bb46, 0xff79a6f1,
		0xe13ef6f4, 0xe5ffeb43, 0xe8bccd9a, 0xec7dd02d, 0x34867077, 0x30476dc0,
		0x3d044b19, 0x39c556ae, 0x278206ab, 0x23431b1c, 0x2e003dc5, 0x2ac12072,
		0x128e9dcf, 0x164f8078, 0x1b0ca6a1, 0x1fcdbb16, 0x018aeb13, 0x054bf6a4,
		0x0808d07d, 0x0cc9cdca, 0x7897ab07, 0x7c56b6b0, 0x71159069, 0x75d48dde,
		0x6b93dddb, 0x6f52c06c, 0x6211e6b5, 0x66d0fb02, 0x5e9f46bf, 0x5a5e5b08,
		0x571d7dd1, 0x53dc6066, 0x4d9b3063, 0x495a2dd4, 0x44190b0d, 0x40d816ba,
		0xaca5c697, 0xa864db20, 0xa527fdf9, 0xa1e6e04e, 0xbfa1b04b, 0xbb60adfc,
		0xb6238b25, 0xb2e29692, 0x8aad2b2f, 0x8e6c3698, 0x832f1041, 0x87ee0df6,
		0x99a95df3, 0x9d684044, 0x902b669d, 0x94ea7b2a, 0xe0b41de7, 0xe4750050,
		0xe9362689, 0xedf73b3e, 0xf3b06b3b, 0xf771768c, 0xfa325055, 0xfef34de2,
		0xc6bcf05f, 0xc27dede8, 0xcf3ecb31, 0xcbffd686, 0xd5b88683, 0xd1799b34,
		0xdc3abded, 0xd8fba05a, 0x690ce0ee, 0x6dcdfd59, 0x608edb80, 0x644fc637,
		0x7a089632, 0x7ec98b85, 0x738aad5c, 0x774bb0eb, 0x4f040d56, 0x4bc510e1,
		0x46863638, 0x42472b8f, 0x5c007b8a, 0x58c1663d, 0x558240e4, 0x51435d53,
		0x251d3b9e, 0x21dc2629, 0x2c9f00f0, 0x285e1d47, 0x36194d42, 0x32d850f5,
		0x3f9b762c, 0x3b5a6b9b, 0x0315d626, 0x07d4cb91, 0x0a97ed48, 0x0e56f0ff,
		0x1011a0fa, 0x14d0bd4d, 0x19939b94, 0x1d528623, 0xf12f560e, 0xf5ee4bb9,
		0xf8ad6d60, 0xfc6c70d7, 0xe22b20d2, 0xe6ea3d65, 0xeba91bbc, 0xef68060b,
		0xd727bbb6, 0xd3e6a601, 0xdea580d8, 0xda649d6f, 0xc423cd6a, 0xc0e2d0dd,
		0xcda1f604, 0xc960ebb3, 0xbd3e8d7e, 0xb9ff90c9, 0xb4bcb610, 0xb07daba7,
		0xae3afba2, 0xaafbe615, 0xa7b8c0cc, 0xa379dd7b, 0x9b3660c6, 0x9ff77d71,
		0x92b45ba8, 0x9675461f, 0x8832161a, 0x8cf30bad, 0x81b02d74, 0x857130c3,
		0x5d8a9099, 0x594b8d2e, 0x5408abf7, 0x50c9b640, 0x4e8ee645, 0x4a4ffbf2,
		0x470cdd2b, 0x43cdc09c, 0x7b827d21, 0x7f436096, 0x7200464f, 0x76c15bf8,
		0x68860bfd, 0x6c47164a, 0x61043093, 0x65c52d24, 0x119b4be9, 0x155a565e,
		0x18197087, 0x1cd86d30, 0x029f3d35, 0x065e2082, 0x0b1d065b, 0x0fdc1bec,
		0x3793a651, 0x3352bbe6, 0x3e119d3f, 0x3ad08088, 0x2497d08d, 0x2056cd3a,
		0x2d15ebe3, 0x29d4f654, 0xc5a92679, 0xc1683bce, 0xcc2b1d17, 0xc8ea00a0,
		0xd6ad50a5, 0xd26c4d12, 0xdf2f6bcb, 0xdbee767c, 0xe3a1cbc1, 0xe760d676,
		0xea23f0af, 0xeee2ed18, 0xf0a5bd1d, 0xf464a0aa, 0xf9278673, 0xfde69bc4,
		0x89b8fd09, 0x8d79e0be, 0x803ac667, 0x84fbdbd0, 0x9abc8bd5, 0x9e7d9662,
		0x933eb0bb, 0x97ffad0c, 0xafb010b1, 0xab710d06, 0xa6322bdf, 0xa2f33668,
		0xbcb4666d, 0xb8757bda, 0xb5365d03, 0xb1f740b4
};

/* This table was compiled using the polynom: 0x0AA725CF*/
static const guint crc32_0AA725CF_reverse[] = {
		0x00000000L, 0xCEAA95CEL, 0x7A1CE13DL, 0xB4B674F3L,
		0xF439C27AL, 0x3A9357B4L, 0x8E252347L, 0x408FB689L,
		0x0F3A4E55L, 0xC190DB9BL, 0x7526AF68L, 0xBB8C3AA6L,
		0xFB038C2FL, 0x35A919E1L, 0x811F6D12L, 0x4FB5F8DCL,
		0x1E749CAAL, 0xD0DE0964L, 0x64687D97L, 0xAAC2E859L,
		0xEA4D5ED0L, 0x24E7CB1EL, 0x9051BFEDL, 0x5EFB2A23L,
		0x114ED2FFL, 0xDFE44731L, 0x6B5233C2L, 0xA5F8A60CL,
		0xE5771085L, 0x2BDD854BL, 0x9F6BF1B8L, 0x51C16476L,
		0x3CE93954L, 0xF243AC9AL, 0x46F5D869L, 0x885F4DA7L,
		0xC8D0FB2EL, 0x067A6EE0L, 0xB2CC1A13L, 0x7C668FDDL,
		0x33D37701L, 0xFD79E2CFL, 0x49CF963CL, 0x876503F2L,
		0xC7EAB57BL, 0x094020B5L, 0xBDF65446L, 0x735CC188L,
		0x229DA5FEL, 0xEC373030L, 0x588144C3L, 0x962BD10DL,
		0xD6A46784L, 0x180EF24AL, 0xACB886B9L, 0x62121377L,
		0x2DA7EBABL, 0xE30D7E65L, 0x57BB0A96L, 0x99119F58L,
		0xD99E29D1L, 0x1734BC1FL, 0xA382C8ECL, 0x6D285D22L,
		0x79D272A8L, 0xB778E766L, 0x03CE9395L, 0xCD64065BL,
		0x8DEBB0D2L, 0x4341251CL, 0xF7F751EFL, 0x395DC421L,
		0x76E83CFDL, 0xB842A933L, 0x0CF4DDC0L, 0xC25E480EL,
		0x82D1FE87L, 0x4C7B6B49L, 0xF8CD1FBAL, 0x36678A74L,
		0x67A6EE02L, 0xA90C7BCCL, 0x1DBA0F3FL, 0xD3109AF1L,
		0x939F2C78L, 0x5D35B9B6L, 0xE983CD45L, 0x2729588BL,
		0x689CA057L, 0xA6363599L, 0x1280416AL, 0xDC2AD4A4L,
		0x9CA5622DL, 0x520FF7E3L, 0xE6B98310L, 0x281316DEL,
		0x453B4BFCL, 0x8B91DE32L, 0x3F27AAC1L, 0xF18D3F0FL,
		0xB1028986L, 0x7FA81C48L, 0xCB1E68BBL, 0x05B4FD75L,
		0x4A0105A9L, 0x84AB9067L, 0x301DE494L, 0xFEB7715AL,
		0xBE38C7D3L, 0x7092521DL, 0xC42426EEL, 0x0A8EB320L,
		0x5B4FD756L, 0x95E54298L, 0x2153366BL, 0xEFF9A3A5L,
		0xAF76152CL, 0x61DC80E2L, 0xD56AF411L, 0x1BC061DFL,
		0x54759903L, 0x9ADF0CCDL, 0x2E69783EL, 0xE0C3EDF0L,
		0xA04C5B79L, 0x6EE6CEB7L, 0xDA50BA44L, 0x14FA2F8AL,
		0xF3A4E550L, 0x3D0E709EL, 0x89B8046DL, 0x471291A3L,
		0x079D272AL, 0xC937B2E4L, 0x7D81C617L, 0xB32B53D9L,
		0xFC9EAB05L, 0x32343ECBL, 0x86824A38L, 0x4828DFF6L,
		0x08A7697FL, 0xC60DFCB1L, 0x72BB8842L, 0xBC111D8CL,
		0xEDD079FAL, 0x237AEC34L, 0x97CC98C7L, 0x59660D09L,
		0x19E9BB80L, 0xD7432E4EL, 0x63F55ABDL, 0xAD5FCF73L,
		0xE2EA37AFL, 0x2C40A261L, 0x98F6D692L, 0x565C435CL,
		0x16D3F5D5L, 0xD879601BL, 0x6CCF14E8L, 0xA2658126L,
		0xCF4DDC04L, 0x01E749CAL, 0xB5513D39L, 0x7BFBA8F7L,
		0x3B741E7EL, 0xF5DE8BB0L, 0x4168FF43L, 0x8FC26A8DL,
		0xC0779251L, 0x0EDD079FL, 0xBA6B736CL, 0x74C1E6A2L,
		0x344E502BL, 0xFAE4C5E5L, 0x4E52B116L, 0x80F824D8L,
		0xD13940AEL, 0x1F93D560L, 0xAB25A193L, 0x658F345DL,
		0x250082D4L, 0xEBAA171AL, 0x5F1C63E9L, 0x91B6F627L,
		0xDE030EFBL, 0x10A99B35L, 0xA41FEFC6L, 0x6AB57A08L,
		0x2A3ACC81L, 0xE490594FL, 0x50262DBCL, 0x9E8CB872L,
		0x8A7697F8L, 0x44DC0236L, 0xF06A76C5L, 0x3EC0E30BL,
		0x7E4F5582L, 0xB0E5C04CL, 0x0453B4BFL, 0xCAF92171L,
		0x854CD9ADL, 0x4BE64C63L, 0xFF503890L, 0x31FAAD5EL,
		0x71751BD7L, 0xBFDF8E19L, 0x0B69FAEAL, 0xC5C36F24L,
		0x94020B52L, 0x5AA89E9CL, 0xEE1EEA6FL, 0x20B47FA1L,
		0x603BC928L, 0xAE915CE6L, 0x1A272815L, 0xD48DBDDBL,
		0x9B384507L, 0x5592D0C9L, 0xE124A43AL, 0x2F8E31F4L,
		0x6F01877DL, 0xA1AB12B3L, 0x151D6640L, 0xDBB7F38EL,
		0xB69FAEACL, 0x78353B62L, 0xCC834F91L, 0x0229DA5FL,
		0x42A66CD6L, 0x8C0CF918L, 0x38BA8DEBL, 0xF6101825L,
		0xB9A5E0F9L, 0x770F7537L, 0xC3B901C4L, 0x0D13940AL,
		0x4D9C2283L, 0x8336B74DL, 0x3780C3BEL, 0xF92A5670L,
		0xA8EB3206L, 0x6641A7C8L, 0xD2F7D33BL, 0x1C5D46F5L,
		0x5CD2F07CL, 0x927865B2L, 0x26CE1141L, 0xE864848FL,
		0xA7D17C53L, 0x697BE99DL, 0xDDCD9D6EL, 0x136708A0L,
		0x53E8BE29L, 0x9D422BE7L, 0x29F45F14L, 0xE75ECADAL
};

guint32
crc32c_table_lookup (guchar pos)
{
  return crc32c_table[pos];
}

guint32
crc32_ccitt_table_lookup (guchar pos)
{
  return crc32_ccitt_table[pos];
}

guint32
crc32c_calculate(const void *buf, int len, guint32 crc)
{
	const guint8 *p = (const guint8 *)buf;
	crc = CRC32C_SWAP(crc);
	while (len-- > 0) {
		CRC32C(crc, *p++);
	}
	return CRC32C_SWAP(crc);
}

guint32 
crc32c_calculate_no_swap(const void *buf, int len, guint32 crc)
{
	const guint8 *p = (const guint8 *)buf;
	while (len-- > 0) {
		CRC32C(crc, *p++);
	}

	return crc;
}

guint32
crc32_ccitt(const guint8 *buf, guint len)
{
	return (crc32_ccitt_seed(buf, len, CRC32_CCITT_SEED));
}

guint32
crc32_ccitt_seed(const guint8 *buf, guint len, guint32 seed)
{
	guint i;
	guint32 crc32 = seed;

	for (i = 0; i < len; i++)
		crc32 = crc32_ccitt_table[(crc32 ^ buf[i]) & 0xff] ^ (crc32 >> 8);

	return ( ~crc32 );
}

guint32
crc32_mpeg2_seed(const guint8 *buf, guint len, guint32 seed)
{
	guint i;
	guint32 crc32;

	crc32 = seed;

	for (i = 0; i < len; i++)
		crc32 = (crc32 << 8) ^ crc32_mpeg2_table[((crc32 >> 24) ^ buf[i]) & 0xff];

	return ( crc32 );
}

guint32
crc32_0x0AA725CF_seed(const guint8 *buf, guint len, guint32 seed)
{
	guint crc32;

	crc32 = (guint)seed;
		while( len-- != 0 )
			crc32 = crc32_0AA725CF_reverse[(crc32 ^ *buf++) & 0xff] ^ (crc32 >> 8);

	return (guint32)crc32;
}