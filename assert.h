#pragma once
#include <errors.h>

/* NB: takes a str param rather than just stringifying e because otherwise
   callers would be forced to macro-expand e when passing it. Among other
   reasons. */
#define assertlstr(req_dbg_lvl, str, e...)                              \
    ass_cond(req_dbg_lvl, E_DBG_LVL,                                    \
             (e) ?(void) 0: (TODO("Failed assertion: %.", str), (void) 0), \
             (void) 0)

#define assert(e...) assertlstr(1, #e, e)

#define assertl(req_dbg_lvl, e...) assertlstr(req_dbg_lvl, #e, e)

/* Checks e when debugging, but doesn't omit it in "release
   mode". __builtin_unreachable() should inform compiler dataflow
   analysis, but it's probably futile. */
#define mustlstr(req_dbg_lvl, str, e...)                            \
    ({                                                              \
        __auto_type _e = e;                                         \
        assertlstr(req_dbg_lvl, str, _e);                           \
        if(!_e)                                                     \
            __builtin_unreachable();                                \
        _e;                                                         \
    })

        
#define must(i...) mustlstr(1, #i, i)

#define muste(e...) !mustlstr(1, "!"#e, !(e))

#define mustp(p...) mustlstr(1, #p, p)


#define ass_cond(req, verb, e, o...)               \
    CONCAT(ass_cond, CONCAT2(verb, req)) (e, o)

#define ass_cond00(e, o...) e
#define ass_cond01(e, o...) o
#define ass_cond02(e, o...) o
#define ass_cond03(e, o...) o
#define ass_cond04(e, o...) o
#define ass_cond05(e, o...) o
#define ass_cond10(e, o...) e
#define ass_cond11(e, o...) e
#define ass_cond12(e, o...) o
#define ass_cond13(e, o...) o
#define ass_cond14(e, o...) o
#define ass_cond15(e, o...) o
#define ass_cond20(e, o...) e
#define ass_cond21(e, o...) e
#define ass_cond22(e, o...) e
#define ass_cond23(e, o...) o
#define ass_cond24(e, o...) o
#define ass_cond25(e, o...) o
#define ass_cond30(e, o...) e
#define ass_cond31(e, o...) e
#define ass_cond32(e, o...) e
#define ass_cond33(e, o...) e
#define ass_cond34(e, o...) o
#define ass_cond35(e, o...) o
#define ass_cond40(e, o...) e
#define ass_cond41(e, o...) e
#define ass_cond42(e, o...) e
#define ass_cond43(e, o...) e
#define ass_cond44(e, o...) e
#define ass_cond45(e, o...) o
#define ass_cond50(e, o...) e
#define ass_cond51(e, o...) e
#define ass_cond52(e, o...) e
#define ass_cond53(e, o...) e
#define ass_cond54(e, o...) e
#define ass_cond55(e, o...) e
