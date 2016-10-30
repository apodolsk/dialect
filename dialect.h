#pragma once

#ifndef __ASSEMBLER__

#ifdef __cplusplus

#include <atomic>
#include <type_traits>
#include <pustr.hpp>

/* Not proud of this. */
extern "C"{
#define typeof decltype
#define _Static_assert static_assert
#define __auto_type auto
    
#else
#include <pustr.h>
#include <putrace.h>
#endif


#define ainline __attribute__((always_inline))
#define returns_twice __attribute__((returns_twice))
#define noinline __attribute__((noinline))
#define pure __attribute__((pure))
#define constfun __attribute__((const))
#define noreturn __attribute__((noreturn))
#define packed __attribute__((packed))
#define flat __attribute__((flatten))
#define align(ment) __attribute__((__aligned__(ment)))
#define aliasing __attribute__((may_alias))
#define checked __attribute__((warn_unused_result))
#define dbg __attribute__((unused))
#define used __attribute__((used))
#define transparent __attribute__((transparent_union))
#define visible_fun __attribute__((visibility("default")))
#define artificial __attribute__((artificial))

#define likely(e) __builtin_expect(!!(e), 1)
#define unlikely(e) __builtin_expect(!!(e), 0)
#define lif(e) if(likely(e))
#define uif(e) if(unlikely(e))

#define prefetch(p, as...) __builtin_prefetch((void *)(p), ##as)

#include <wktypes.h>
#include <runtime_spec.h>
#include <runtime.h>    

#include <string.h>
#include <stdio.h>

#include <limits.h>

#include <assert.h>
#include <log.h>

#include <errors.h>
#include <wkutil.h>
#include <wkrand.h>

#include <syscall.h>

#include <atomics.h>

#include <stdlib.h>

#ifdef __cplusplus
#undef alignof    
}
#endif
#endif
