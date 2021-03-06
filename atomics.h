#pragma once

CASSERT(sizeof(cnt) <= sizeof(uptr));
CASSERT(sizeof(int) <= sizeof(uptr));

/* TODO: unfortunately, _Atomic is too strict but the __atomic builtins
   are quite buggy. */
/* TODO: pointer casts here still run afoul of alias analysis. Switch to
   builtins or mess with aliasing attrib. */
/* TODO: awful arg order. */

uptr _xadd(iptr s, volatile uptr *p);
uptr _xchg(uptr s, volatile uptr *p);
dptr _xchg2(dptr s, volatile dptr *p);
uptr _atomic_read(volatile uptr *p);
dptr _atomic_read2(volatile dptr *p);
void _atomic_write2(dptr n, volatile dptr *p);

uptr _xadd_iff_less(uptr a, volatile uptr *p, uptr lim);
uptr _xsub_iff(uptr s, volatile uptr *p);
void fuzz_atomics();

uptr _cas(uptr n, volatile uptr *p, uptr old);
dptr _cas2(dptr n, volatile dptr *p, dptr old);

typedef enum{
    NOT = 0,
    WON = 1,
    OK = 2,
} howok;

howok _cas_ok(uptr n, volatile uptr *p, uptr *old);
bool _cas_won(uptr n, volatile uptr *p, uptr *old);
howok _cas2_ok(dptr n, volatile dptr *p, dptr *old);
bool _cas2_won(dptr n, volatile dptr *p, dptr *old);

howok _upd_ok(uptr n, volatile uptr *p, uptr *old);
bool _upd_won(uptr n, volatile uptr *p, uptr *old);
howok _upd2_ok(dptr n, volatile dptr *p, dptr *old);
bool _upd2_won(dptr n, volatile dptr *p, dptr *old);

#define atomic_read(p)                                  \
    PUN(typeof(*p), _atomic_read((volatile uptr *) p))  \

#define xadd(s, d) PUN(typeof(*d),                                      \
                       trace(ATOMICS, 2, _xadd, s, (volatile uptr *) d))
#define xchg(s, d) PUN(typeof(*d), _xchg(PUN(uptr, s), (volatile uptr *) (d)))
#define xchg2(s, d) PUN(typeof(*d), _xchg2(PUN(dptr, s), (volatile dptr *) (d)))
#define xadd_iff_less(s, d, lim)                                         \
    ((typeof(*d)) _xadd_iff_less(s, (volatile uptr *) d, (uptr) lim))
#define xsub_iff(s, p)                                  \
    ((typeof(*p)) _xsub_iff(s, (volatile uptr *) p))    \


#define atomic_read2(p)                                 \
    PUN(typeof(*p), _atomic_read2((volatile dptr *) p)) \


#define atomic_write(n, p)                              \
    _atomic_write2(PUN(uptr, n), (volatile uptr *) p)   \

#define atomic_write2(n, p)                             \
    _atomic_write2(PUN(dptr, n), (volatile dptr *) p)   \

#define cas(n, p, old)                          \
    PUN(typeof(old),                            \
        trace(ATOMICS, 1, _cas,                 \
              PUN(uptr, n),                     \
              (volatile uptr *) (p),            \
              PUN(uptr, old)))

#define cas2(n, p, old)                         \
    PUN(typeof(old),                            \
        trace(ATOMICS, 1, _cas2,                \
              PUN(dptr, n),                     \
              (volatile dptr *) (p),            \
              PUN(dptr, old)))

#define cas_ok(n, p, op)                        \
    trace(ATOMICS, 1, _cas_ok,                  \
          PUN(uptr, n),                         \
          (volatile uptr *) (p),                \
          (uptr *) (op))

#define cas2_ok(n, p, op)                       \
    trace(ATOMICS, 1, _cas2_ok,                 \
          PUN(dptr, n),                         \
          (volatile dptr *) (p),                \
          (dptr *) (op))

#define cas_won(n, p, op)                       \
    trace(ATOMICS, 1, _cas_won,                 \
          PUN(uptr, n),                         \
          (volatile uptr *) (p),                \
          (uptr *) (op))

#define cas2_won(n, p, op)                      \
    trace(ATOMICS, 1, _cas2_won,                \
          PUN(dptr, n),                         \
          (volatile dptr *) (p),                \
          (dptr *) (op))

#define upd2_ok(n, p, op)                       \
    trace(ATOMICS, 1, _upd2_ok,                 \
          PUN(dptr, n),                         \
          (volatile dptr *) (p),                \
          (dptr *) (op))

#define upd2_won(n, p, op)                      \
    trace(ATOMICS, 1, _upd2_won,                \
          PUN(dptr, n),                         \
          (volatile dptr *) (p),                \
          (dptr *) (op))

#define upd_ok(n, p, op)                        \
    trace(ATOMICS, 1, _upd_ok,                  \
          PUN(uptr, n),                         \
          (volatile uptr *) (p),                \
          (uptr *) (op))

#define upd_won(n, p, op)                       \
    trace(ATOMICS, 1, _upd_won,                 \
          PUN(uptr, n),                         \
          (volatile uptr *) (p),                \
          (uptr *) (op))


#ifndef LOG_ATOMICS
#define LOG_ATOMICS 0
#endif 
