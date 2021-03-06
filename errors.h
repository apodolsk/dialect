#pragma once
#include <wkmacros.h>
#include <runtime.h>
#include <errverbs.h>

/* Default break, print, and dbg levels. */

#define LVL_EWTF 0
#define LVL_TODO 1
#define LVL_SUPER_EARG 1
#define LVL_OVERCOMMIT 2
#define LVL_SUPER_RARITY 2
#define LVL_EOOR 3
#define LVL_EARG 4
#define LVL_RARITY 5

#define FIRST(as...) _FIRST(as)
#define SECOND(as...) _SECOND(as)
#define THIRD(as...) _THIRD(as)
#define _FIRST(a, ...) a
#define _SECOND(a, b, ...) b
#define _THIRD(a, b, c) c

#define E_LOOKUP _LOOKUP(CONCAT(E_, MODULE))
#define _LOOKUP(emod) CONCAT2(_LOOKUP, NUM_ARGS(emod))(emod)
#define _LOOKUP1(emod) DBG, BRK, PRNT
#define _LOOKUP3(a, b, c) a, b, c

#define E_DBG_LVL FIRST(E_LOOKUP)
#define E_BREAK_LVL SECOND(E_LOOKUP)
#define E_PRINT_LVL THIRD(E_LOOKUP)

#define if_dbgl(l, e) err_cond(l, E_DBG_LVL, e, (void) 0)
#define if_dbg(e) if_dbgl(1, e)    

/* --- Fatal Errors (for the kernel) --- */

#define EWTF(fmt, as...)                            \
    ({                                              \
        elog(0, "This can't be. %:%:%. " fmt        \
             , __FILE__ ,__func__, __LINE__, ##as); \
        ebreakpoint(0);                             \
        panic("WTF!");                              \
    })

/* elog(0, "My creator has abandoned me. %:%:%. " fmt      \ */
/*      , __FILE__ , __func__ , __LINE__, ##as);           \ */

#define TODO(fmt, as...)                                        \
    ({                                                          \
        elog(0, "My creator has abandoned me. %:%:%. " fmt "\n" \
             ,  __FILE__ , __func__ , __LINE__, ##as);          \
                                                                \
        ebreakpoint(0);                                         \
        panic("TODO!");                                         \
    })

/* --- Recoverable Errors (for the kernel) --- */

/* Sequel to EARG on the NES. */
#define SUPER_EARG(fmt, as...)                                      \
    ({                                                              \
        elog(1, "Super bad input error. %:%:%. " fmt,               \
             __FILE__, __func__, __LINE__, ##as);                   \
        ebreakpoint(1);                                             \
        (dptr) -1;                                                  \
    })

#define OVERCOMMIT_ERROR(fmt, as...)                                \
    ({                                                              \
        elog(2,"Overcommit error. %:%:%. "                          \
             fmt, __FILE__, __func__, __LINE__, ##as);              \
        ebreakpoint(2);                                             \
        (dptr) -1;                                                  \
    })

#define SUPER_RARITY(fmt, as...)                                    \
    ({                                                              \
        elog(2,"Super rare event. %:%:%. "                          \
             fmt, __FILE__, __func__, __LINE__, ##as);              \
        ebreakpoint(2);                                             \
        (dptr) -1;                                                  \
    })                                                              \

#define EOOR(fmt, as...)                                        \
    ({                                                          \
      elog(3,"Out of resources. %:%:%. " fmt                    \
           , __FILE__, __func__, __LINE__, ##as);               \
      ebreakpoint(3);                                           \
      (dptr) EOOR;                                              \
    })                                                         

        
#define EARG(fmt, as...)                                        \
    ({                                                          \
      elog(4, "Input error. %:%:%. " fmt                        \
           , __FILE__, __func__, __LINE__, ##as);               \
      ebreakpoint(4);                                           \
      (dptr) EARG;                                              \
    })

#define RARITY(fmt, as...)                                  \
    ({                                                      \
      elog(5, "Rarity. %:%:%. "                             \
               fmt, __FILE__, __func__, __LINE__, ##as);    \
      ebreakpoint(5);                                       \
    })                                                      \

/* --- Helpers --- */

#define elog(lvl, fmt, ...)                                             \
    err_cond(lvl, E_PRINT_LVL, lprintf(fmt, ##__VA_ARGS__), 0)

#define ebreakpoint(lvl)                                    \
    err_cond(lvl, E_BREAK_LVL, breakpoint(), 0)

/* TODO: macro-expansion into multiple macro args not happening. Same old
   shit. */
#define KERNPTR_MSG(addr)                                               \
                /* "Forbidden pointer to kern memory: %", (void *) addr */

#define BADWRITE_MSG(addr)                                  \
                /* "Failed to write to %", (void *) addr */

#define BADREAD_MSG(addr)                                           \
                /* "Failed to read from: %", (void *) addr      */

#define BADMEM_MSG(addr)                                                \
                /* "Unreadable or unwriteable memory: %.", (void *) addr    */

#define err_cond(req, verb, e, o...)                           \
    CONCAT(err_cond, CONCAT2(verb, req)) (e, o)

#define err_cond00(e, o...) e
#define err_cond01(e, o...) o
#define err_cond02(e, o...) o
#define err_cond03(e, o...) o
#define err_cond04(e, o...) o
#define err_cond05(e, o...) o
#define err_cond10(e, o...) e
#define err_cond11(e, o...) e
#define err_cond12(e, o...) o
#define err_cond13(e, o...) o
#define err_cond14(e, o...) o
#define err_cond15(e, o...) o
#define err_cond20(e, o...) e
#define err_cond21(e, o...) e
#define err_cond22(e, o...) e
#define err_cond23(e, o...) o
#define err_cond24(e, o...) o
#define err_cond25(e, o...) o
#define err_cond30(e, o...) e
#define err_cond31(e, o...) e
#define err_cond32(e, o...) e
#define err_cond33(e, o...) e
#define err_cond34(e, o...) o
#define err_cond35(e, o...) o
#define err_cond40(e, o...) e
#define err_cond41(e, o...) e
#define err_cond42(e, o...) e
#define err_cond43(e, o...) e
#define err_cond44(e, o...) e
#define err_cond45(e, o...) o
#define err_cond50(e, o...) e
#define err_cond51(e, o...) e
#define err_cond52(e, o...) e
#define err_cond53(e, o...) e
#define err_cond54(e, o...) e
#define err_cond55(e, o...) e

