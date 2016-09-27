#pragma once
#ifndef __ASSEMBLER__

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef unsigned int uint;
typedef uintptr_t uptr;
/* Counts any set of objects simultaneously in memory. */
typedef uptr cnt;
typedef cnt idx;
typedef intptr_t iptr;
typedef size_t size;
typedef ptrdiff_t ptrdiff;
enum{
    EOK = 0,
    EARG = -1,
    EOOR = -2,
    
    EMAX = EOK,
    EMIN = EOOR,
};
typedef int err;
typedef int ecnt;

typedef unsigned char u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

#if UINTPTR_MAX == 0xffffffffffffffff
typedef __int128_t dptr;
typedef __uint128_t udptr;
#elif UINTPTR_MAX == 0xffffffff
typedef int64_t dptr;
typedef uint64_t udptr;
#else
#error "Expected 2^32 - 1 or 2^64 - 1 for UINTPTR_MAX"
#endif

#define UPTR_MAX UINTPTR_MAX
#define CNT_MAX UPTR_MAX

#define WORDBITS (CHAR_BIT * sizeof(void *))

#endif
