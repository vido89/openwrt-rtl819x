/* Macros to swap the order of bytes in integer values.
   Copyright (C) 1997,1998,2000,2001,2002,2005 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */

#if !defined _BYTESWAP_H && !defined _NETINET_IN_H
# error "Never use <bits/byteswap.h> directly; include <byteswap.h> instead."
#endif

#ifndef _BITS_BYTESWAP_H
#define _BITS_BYTESWAP_H 1

#if __GNUC_PREREQ(4,2)
# undef __bswap_non_constant_32
# define __bswap_non_constant_32 __builtin_bswap32

# undef __bswap_non_constant_64
# define __bswap_non_constant_64 __builtin_bswap64
#endif

/* Swap bytes in 16 bit value.  */
#define __bswap_constant_16(x) \
     ((((x) >> 8) & 0xffu) | (((x) & 0xffu) << 8))

#ifndef __bswap_non_constant_16
# define __bswap_non_constant_16(x) __bswap_constant_16(x)
#endif
#ifdef __GNUC__
# define __bswap_16(x) \
    (__extension__							      \
     ({ unsigned short int __bsv, __bsx = (x);				      \
	if (__builtin_constant_p (__bsx))				      \
	  __bsv = __bswap_constant_16 (__bsx);				      \
	else								      \
	  __bsv = __bswap_non_constant_16 (__bsx);			      \
	__bsv; }))
#else
static __inline unsigned short int
__bswap_16 (unsigned short int __bsx)
{
  return __bswap_constant_16 (__bsx);
}
#endif

/* Swap bytes in 32 bit value.  */
#define __bswap_constant_32(x) \
     ((((x) & 0xff000000u) >> 24) | (((x) & 0x00ff0000u) >>  8) |	      \
      (((x) & 0x0000ff00u) <<  8) | (((x) & 0x000000ffu) << 24))

#ifndef __bswap_non_constant_32
# define __bswap_non_constant_32(x) __bswap_constant_32(x)
#endif
#ifdef __GNUC__
# define __bswap_32(x) \
    (__extension__							      \
     ({ unsigned int __bsv, __bsx = (x);				      \
	if (__builtin_constant_p (__bsx))				      \
	  __bsv = __bswap_constant_32 (__bsx);				      \
	else								      \
	  __bsv = __bswap_non_constant_32 (__bsx);			      \
	__bsv; }))
#else
static __inline unsigned int
__bswap_32 (unsigned int __bsx)
{
  return __bswap_constant_32 (__bsx);
}
#endif

#if defined __GNUC__ && __GNUC__ >= 2
/* Swap bytes in 64 bit value.  */
# define __bswap_constant_64(x) \
     ((((x) & 0xff00000000000000ull) >> 56)				      \
      | (((x) & 0x00ff000000000000ull) >> 40)				      \
      | (((x) & 0x0000ff0000000000ull) >> 24)				      \
      | (((x) & 0x000000ff00000000ull) >> 8)				      \
      | (((x) & 0x00000000ff000000ull) << 8)				      \
      | (((x) & 0x0000000000ff0000ull) << 24)				      \
      | (((x) & 0x000000000000ff00ull) << 40)				      \
      | (((x) & 0x00000000000000ffull) << 56))

# ifndef __bswap_non_constant_64
#  define __bswap_non_constant_64(x) \
     (__extension__							      \
      ({ union { __extension__ unsigned long long int __ll;		      \
		 unsigned int __l[2]; } __w, __r;			      \
	 __w.__ll = (x);						      \
	 __r.__l[0] = __bswap_non_constant_32 (__w.__l[1]);		      \
	 __r.__l[1] = __bswap_non_constant_32 (__w.__l[0]);		      \
	 __r.__ll; }))
# endif
# define __bswap_64(x) \
     (__extension__							      \
      ({ __extension__ unsigned long long int __ll;			      \
         if (__builtin_constant_p (x))					      \
	   __ll = __bswap_constant_64 (x);				      \
	 else								      \
	   __ll = __bswap_non_constant_64 (x);				      \
	 __ll; }))
#endif

#endif /* _BITS_BYTESWAP_H */
