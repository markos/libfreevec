/***************************************************************************
 *   Copyright (C) 2005 by Konstantinos Margaritis                         *
 *   markos@debian.gr                                                      *
 *                                                                         *
 *   This code is distributed under a BSD-type license                     *
 ***************************************************************************/

#include <stdint.h>
#include <stdio.h>

#include "libfreevec.h"
#include "macros/common.h"

size_t find_leftfirst_in_word(uint32_t x)
{
	uint8_t sum = 0;
	x |= (x >> 1);
	x |= (x >> 2);
	x |= (x >> 4);
	x |= (x >> 8);
	x |= (x >> 16);
	x = x ^ (x >> 1);
	x |= (x >> 1);
	x |= (x >> 2);
	x |= (x >> 4);
	x &= POSINWORD;
	sum = x + (x >> 8) + (x >> 16) + (x >> 24);
	return (sum);
}

size_t find_rightfirst_in_word(uint32_t x)
{
	uint8_t sum = 0;
	x &= -x;
	x |= (x >> 1);
	x |= (x >> 2);
	x |= (x >> 4);
	x &= POSINWORD;
	sum = x + (x >> 8) + (x >> 16) + (x >> 24);
	return (sum);
}

uint32_t inline find_leftfirst_nonzero_char( uint32_t x) {
        uint32_t tmp = 0;
        asm(
          "cntlzw %0, %1\n\t"
          "srawi  %0, %0, 3"
          : "+r" (tmp)  /* output */
          : "r" (x)     /* input */
          : "0"
        );
        return tmp;
}

uint32_t inline find_rightfirst_nonzero_char( uint32_t x) {
        uint32_t tmp = 0, xa = (uint32_t) &x;
        printf("x = %08x\n", x);
        asm(
          "li 2, 0\n\t"
          "lwbrx 1, 2, %1\n\t"
          "cntlzw %0, 1\n\t"
          "srawi  %0, %0, 3"
          : "+r" (tmp)  /* output */
          : "r" (xa)     /* input */
          : "1", "2"
        );
        printf("result =%d\n", tmp);
        return tmp;
}
