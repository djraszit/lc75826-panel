/*
 * lc75826_segments.h
 *
 *  Created on: 9 lip 2017
 *      Author: root
 */

#ifndef LC75826_SEGMENTS_H_
#define LC75826_SEGMENTS_H_

//                         aaaaaaaaa
//                       f i   m   j b
//                       f  i  m  j  b
//                       f   i m j   b
//                         ggg m hhh
//                       e   k m l   c
//                       e  k  m  l  c
//                       e k   m   l c
//                         ddddddddd



#define _B	(1 << 0)
#define _H	(1 << 1)
#define _C	(1 << 2)
#define _J	(1 << 4)
#define _M	(1 << 5)
#define _L	(1 << 6)
#define _A	(1 << 7)
#define _I	(1 << 8)
#define _K	(1 << 9)
#define _D	(1 << 10)
#define _F	(1 << 12)
#define _G	(1 << 13)
#define _E	(1 << 14)

uint16_t digits[11] = {
/*0*/_A | _B | _C | _D | _E | _F | _K | _J,
/*1*/_B | _C | _J,
/*2*/_A | _B | _G | _H | _E | _D,
/*3*/_A | _B | _C | _D | _G | _H,
/*4*/_B | _C | _F | _G | _H,
/*5*/_A | _F | _G | _H | _C | _D,
/*6*/_A | _F | _E | _D | _C | _G | _H,
/*7*/_A | _B | _C,
/*8*/_A | _B | _C | _D | _E | _F | _G | _H,
/*9*/_A | _B | _C | _D | _F | _G | _H,
/*all*/_A | _B | _C | _D | _E | _F | _G | _H | _I | _J | _K | _L | _M };

uint16_t chars[26] = {
/*A*/_A | _B | _C | _F | _E | _G | _H,
/*B*/_A | _D | _M | _H | _B | _C,
/*C*/_A | _F | _E | _D,
/*D*/_A | _D | _M | _B | _C,
/*E*/_A | _F | _E | _D | _G,
/*F*/_A | _F | _E | _G,
/*G*/_A | _F | _E | _D | _C | _L | _H,
/*H*/_F | _E | _G | _H | _B | _C,
/*I*/_A | _M | _D,
/*J*/_B | _C | _D | _E,
/*K*/_F | _E | _G | _J | _L,
/*L*/_F | _E | _D,
/*M*/_F | _E | _B | _C | _I | _J,
/*N*/_F | _E | _I | _L | _B | _C,
/*O*/_A | _B | _C | _D | _E | _F,
/*P*/_A | _F | _E | _G | _H | _B,
/*Q*/_A | _B | _C | _D | _E | _F | _L,
/*R*/_A | _F | _E | _G | _H | _B | _L,
/*S*/_A | _F | _G | _H | _C | _D,
/*T*/_A | _M,
/*U*/_F | _E | _D| _C | _B,
/*V*/_F | _E | _K | _J,
/*W*/_F | _E | _K | _L | _C | _B,
/*X*/_I | _J | _K | _L,
/*Y*/_I | _J | _K,
/*Z*/_A | _J | _K | _D };

uint16_t others[6] = {
/*(*/_J|_L,
/*)*/_I|_K,
/*+*/_G|_H|_M,
/*-*/_G|_H,
/*/*/_J|_L,
/*\*/_I|_L,

};

#endif /* LC75826_SEGMENTS_H_ */
