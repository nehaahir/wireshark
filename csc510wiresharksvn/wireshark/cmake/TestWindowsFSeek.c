/*
 * $Id: TestWindowsFSeek.c 52364 2013-10-04 15:51:59Z jmayer $
 *
 * This code was copied from http://www.gromacs.org/
 * and its toplevel COPYING file starts with:
 *
 * GROMACS is free software, distributed under the GNU General Public License
 * (GPL) Version 2.
 */

#include <stdio.h>

int main()
{
  __int64 off=0;

  _fseeki64(NULL, off, SEEK_SET);

  return 0;
}
