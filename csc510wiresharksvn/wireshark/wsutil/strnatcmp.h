/* strnatcmp.h
 *
 * $Id: strnatcmp.h 50650 2013-07-16 01:16:50Z morriss $
 *
 * Original code downloaded from: http://sourcefrog.net/projects/natsort/

  strnatcmp.c -- Perform 'natural order' comparisons of strings in C.
  Copyright (C) 2000, 2004 by Martin Pool <mbp sourcefrog net>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

#ifndef STRNATCMP_H
#define STRNATCMP_H

#include "ws_symbol_export.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* CUSTOMIZATION SECTION
 *
 * You can change this typedef, but must then also change the inline
 * functions in strnatcmp.c */
typedef char nat_char;

WS_DLL_PUBLIC int strnatcmp(nat_char const *a, nat_char const *b);
WS_DLL_PUBLIC int strnatcasecmp(nat_char const *a, nat_char const *b);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STRNATCMP_H */
