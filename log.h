#pragma once

#include <logverb.h>

#define lprintf(fmt, as...) puprintf("% " fmt "\n", get_dbg_id(), ##as)

#if !LOG_MASTER
#define log(...) 0
#define pp(as...) (as)
#define ppl(lvl, as...) (as)
#define lppl(lvl, as...) (as)
#define trace(module, lvl, f, as...) f(as)
#else

#define NAMEFMT(a, _, __) a:%
#define ppl(lvl, as...)                                                 \
    log_cond(lvl, MODULE,                                               \
             ({                                                         \
                 MAP_NOCOMMA(estore, __pp, as);                         \
                 lprintf(STRLIT(MAP(NAMEFMT,, ##as)), MAP(eref, __pp, as)); \
                 MAP(eref, __pp, as);                                   \
             }),                                                        \
             (as))
#define pp(as...) ppl(1, ##as)

#define LINEFMT(a, _, __) a:%\n
#define lppl(lvl, as...)                                                \
    log_cond(lvl, MODULE,                                               \
             ({                                                         \
                 MAP_NOCOMMA(estore, __pp, as);                         \
                 lprintf(STRLIT(MAP_NOCOMMA(LINEFMT,, ##as)), MAP(eref, __pp, as)); \
                 MAP(eref, __pp, as);                                   \
             }),                                                        \
             (as))




#define log(lvl, fmt, as...) log_cond(lvl, MODULE, lprintf(fmt, ##as), 0)

#define trace(module, lvl, f, as...)            \
    log_cond(lvl, module, putrace(lprintf, f, ##as), f(as))
#endif

#define log_cond(lvl, module, e, o...)                             \
    CONCAT(log_cond, CONCAT2(CONCAT3(LOG_, module), lvl) ) (e, o)

/* The point of this is to cut down on compilation time. Consider the
   alternative of generating complicated _Generic() expressions that'll
   have to propogate to some DCE phase. */
#define log_cond00(e, o...) e
#define log_cond01(e, o...) o
#define log_cond02(e, o...) o
#define log_cond03(e, o...) o
#define log_cond04(e, o...) o
#define log_cond05(e, o...) o
#define log_cond10(e, o...) e
#define log_cond11(e, o...) e
#define log_cond12(e, o...) o
#define log_cond13(e, o...) o
#define log_cond14(e, o...) o
#define log_cond15(e, o...) o
#define log_cond20(e, o...) e
#define log_cond21(e, o...) e
#define log_cond22(e, o...) e
#define log_cond23(e, o...) o
#define log_cond24(e, o...) o
#define log_cond25(e, o...) o
#define log_cond30(e, o...) e
#define log_cond31(e, o...) e
#define log_cond32(e, o...) e
#define log_cond33(e, o...) e
#define log_cond34(e, o...) o
#define log_cond35(e, o...) o
#define log_cond40(e, o...) e
#define log_cond41(e, o...) e
#define log_cond42(e, o...) e
#define log_cond43(e, o...) e
#define log_cond44(e, o...) e
#define log_cond45(e, o...) o
#define log_cond50(e, o...) e
#define log_cond51(e, o...) e
#define log_cond52(e, o...) e
#define log_cond53(e, o...) e
#define log_cond54(e, o...) e
#define log_cond55(e, o...) e
