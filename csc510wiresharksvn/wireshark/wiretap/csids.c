/* csids.c
 *
 * $Id: csids.c 53166 2013-11-08 09:53:01Z guy $
 *
 * Copyright (c) 2000 by Mike Hall <mlh@io.com>
 * Copyright (c) 2000 by Cisco Systems
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
#include "wtap-int.h"
#include "buffer.h"
#include "csids.h"
#include "file_wrappers.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * This module reads the output from the Cisco Secure Intrusion Detection
 * System iplogging facility. The term iplogging is misleading since this
 * logger will only output TCP. There is no link layer information.
 * Packet format is 4 byte timestamp (seconds since epoch), and a 4 byte size
 * of data following for that packet.
 *
 * For a time there was an error in iplogging and the ip length, flags, and id
 * were byteswapped. We will check for this and handle it before handing to
 * wireshark.
 */

typedef struct {
	gboolean byteswapped;
} csids_t;

static gboolean csids_read(wtap *wth, int *err, gchar **err_info,
	gint64 *data_offset);
static gboolean csids_seek_read(wtap *wth, gint64 seek_off,
	struct wtap_pkthdr *phdr, Buffer *buf, int len,
	int *err, gchar **err_info);
static gboolean csids_read_packet(FILE_T fh, csids_t *csids,
	struct wtap_pkthdr *phdr, Buffer *buf, int *err, gchar **err_info);

struct csids_header {
  guint32 seconds; /* seconds since epoch */
  guint16 zeropad; /* 2 byte zero'ed pads */
  guint16 caplen;  /* the capture length  */
};

/* XXX - return -1 on I/O error and actually do something with 'err'. */
int csids_open(wtap *wth, int *err, gchar **err_info)
{
  /* There is no file header. There is only a header for each packet
   * so we read a packet header and compare the caplen with iplen. They
   * should always be equal except with the weird byteswap version.
   *
   * THIS IS BROKEN-- anytime the caplen is 0x0101 or 0x0202 up to 0x0505
   * this will byteswap it. I need to fix this. XXX --mlh
   */

  int tmp,iplen,bytesRead;

  gboolean byteswap = FALSE;
  struct csids_header hdr;
  csids_t *csids;

  /* check the file to make sure it is a csids file. */
  bytesRead = file_read( &hdr, sizeof( struct csids_header), wth->fh );
  if( bytesRead != sizeof( struct csids_header) ) {
    *err = file_error( wth->fh, err_info );
    if( *err != 0 && *err != WTAP_ERR_SHORT_READ ) {
      return -1;
    }
    return 0;
  }
  if( hdr.zeropad != 0 || hdr.caplen == 0 ) {
	return 0;
  }
  hdr.seconds = pntohl( &hdr.seconds );
  hdr.caplen = pntohs( &hdr.caplen );
  bytesRead = file_read( &tmp, 2, wth->fh );
  if( bytesRead != 2 ) {
    *err = file_error( wth->fh, err_info );
    if( *err != 0 && *err != WTAP_ERR_SHORT_READ ) {
      return -1;
    }
    return 0;
  }
  bytesRead = file_read( &iplen, 2, wth->fh );
  if( bytesRead != 2 ) {
    *err = file_error( wth->fh, err_info );
    if( *err != 0 && *err != WTAP_ERR_SHORT_READ ) {
      return -1;
    }
    return 0;
  }
  iplen = pntohs(&iplen);

  if ( iplen == 0 )
    return 0;

  /* if iplen and hdr.caplen are equal, default to no byteswap. */
  if( iplen > hdr.caplen ) {
    /* maybe this is just a byteswapped version. the iplen ipflags */
    /* and ipid are swapped. We cannot use the normal swaps because */
    /* we don't know the host */
    iplen = BSWAP16(iplen);
    if( iplen <= hdr.caplen ) {
      /* we know this format */
      byteswap = TRUE;
    } else {
      /* don't know this one */
      return 0;
    }
  } else {
    byteswap = FALSE;
  }

  /* no file header. So reset the fh to 0 so we can read the first packet */
  if (file_seek(wth->fh, 0, SEEK_SET, err) == -1)
    return -1;

  csids = (csids_t *)g_malloc(sizeof(csids_t));
  wth->priv = (void *)csids;
  csids->byteswapped = byteswap;
  wth->file_encap = WTAP_ENCAP_RAW_IP;
  wth->file_type_subtype = WTAP_FILE_TYPE_SUBTYPE_CSIDS;
  wth->snapshot_length = 0; /* not known */
  wth->subtype_read = csids_read;
  wth->subtype_seek_read = csids_seek_read;
  wth->tsprecision = WTAP_FILE_TSPREC_SEC;

  return 1;
}

/* Find the next packet and parse it; called from wtap_read(). */
static gboolean csids_read(wtap *wth, int *err, gchar **err_info,
    gint64 *data_offset)
{
  csids_t *csids = (csids_t *)wth->priv;

  *data_offset = file_tell(wth->fh);

  return csids_read_packet( wth->fh, csids, &wth->phdr, wth->frame_buffer,
                            err, err_info );
}

/* Used to read packets in random-access fashion */
static gboolean
csids_seek_read(wtap *wth,
		 gint64 seek_off,
		 struct wtap_pkthdr *phdr,
		 Buffer *buf,
		 int len _U_,
		 int *err,
		 gchar **err_info)
{
  csids_t *csids = (csids_t *)wth->priv;

  if( file_seek( wth->random_fh, seek_off, SEEK_SET, err ) == -1 )
    return FALSE;

  if( !csids_read_packet( wth->random_fh, csids, phdr, buf, err, err_info ) ) {
    if( *err == 0 )
      *err = WTAP_ERR_SHORT_READ;
    return FALSE;
  }
  return TRUE;
}

static gboolean
csids_read_packet(FILE_T fh, csids_t *csids, struct wtap_pkthdr *phdr,
                  Buffer *buf, int *err, gchar **err_info)
{
  struct csids_header hdr;
  int bytesRead = 0;
  guint8 *pd;

  bytesRead = file_read( &hdr, sizeof( struct csids_header), fh );
  if( bytesRead != sizeof( struct csids_header) ) {
    *err = file_error( fh, err_info );
    if (*err == 0 && bytesRead != 0)
      *err = WTAP_ERR_SHORT_READ;
    return FALSE;
  }
  hdr.seconds = pntohl(&hdr.seconds);
  hdr.caplen = pntohs(&hdr.caplen);

  phdr->presence_flags = WTAP_HAS_TS;
  phdr->len = hdr.caplen;
  phdr->caplen = hdr.caplen;
  phdr->ts.secs = hdr.seconds;
  phdr->ts.nsecs = 0;

  if( !wtap_read_packet_bytes( fh, buf, phdr->caplen, err, err_info ) )
    return FALSE;

  pd = buffer_start_ptr( buf );
  if( csids->byteswapped ) {
    if( phdr->caplen >= 2 ) {
      PBSWAP16(pd);   /* the ip len */
      if( phdr->caplen >= 4 ) {
        PBSWAP16(pd+2); /* ip id */
        if( phdr->caplen >= 6 )
          PBSWAP16(pd+4); /* ip flags and fragoff */
      }
    }
  }

  return TRUE;
}
