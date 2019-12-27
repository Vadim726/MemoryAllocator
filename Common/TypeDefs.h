////////////////////////////////////////////////////////////////////////////
//	Created 	: 05.12.2019
//	Author		: Vadim Stydnansky
//	Copyright (c) 2019 the GameRay project.
////////////////////////////////////////////////////////////////////////////

#ifndef GAMERAY_TYPE_DEFS_H_
#define GAMERAY_TYPE_DEFS_H_

typedef char          i8;
typedef	signed   char s8;
typedef unsigned char u8;

typedef short          i16;
typedef	signed   short s16;
typedef unsigned short u16;

typedef			 int i32;
typedef	signed	 int s32;
typedef unsigned int u32;

#ifdef _WIN32
typedef          long long i64;
typedef signed   long long s64;
typedef unsigned long long u64;
#else
#ifdef PLATFORM64
typedef			      long i64;
typedef signed        long s64;
typedef unsigned      long u64;
#else
typedef          long long i64;
typedef	signed   long long s64;
typedef unsigned long long u64;
#endif
#endif

typedef	char String16[16];
typedef	char String32[32];
typedef	char String64[64];
typedef	char String128[128];
typedef	char String256[256];
typedef	char String512[512];
typedef	char String1024[1024];
typedef	char String2048[2048];
typedef	char String4096[4096];
typedef	char StringPath[260];

#endif
