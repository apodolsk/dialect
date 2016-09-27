#define MODULE ATOMICS

#include <race.h>
#include <asm.h>

#define RACE_NS 900
#define RACE_PCNT (E_DBG_LVL ? 25 : 0)
#define RACE_MOD 3

/* TODO: Unfortunately, LTO causes gcc to not generate symbols for files
   implementing builtins like __sync_fetch_and_add_8. Appears to be
   related to:

   https://gcc.gnu.org/bugzilla/show_bug.cgi?id=63215   
   */
/* #include <atomics_x86.h> */
                      
#include <time.h>
void fuzz_atomics(){
    race(RACE_NS, RACE_PCNT, RACE_MOD);
}

uptr _xadd(iptr s, volatile uptr *p){
    assert(aligned_pow2(p, sizeof(*p)));
    fuzz_atomics();
    return __sync_fetch_and_add(p, s, __ATOMIC_SEQ_CST);
}

uptr _xchg(uptr s, volatile uptr *p){
    assert(aligned_pow2(p, sizeof(*p)));
    fuzz_atomics();
    return __atomic_exchange_n(p, s, __ATOMIC_SEQ_CST);
}

dptr _xchg2(dptr s, volatile dptr *p){
    assert(aligned_pow2(p, sizeof(*p)));
    fuzz_atomics();
    for(dptr o = *p;;)
        if(__atomic_compare_exchange_n(p, &o, s,
                                       0, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST))
            return o;
}


uptr _cas(uptr n, volatile uptr *p, uptr old){
    assert(aligned_pow2(p, sizeof(*p)));
    fuzz_atomics();
    return __sync_val_compare_and_swap(p, old, n);
}

dptr _cas2(dptr n, volatile dptr *p, dptr old){
    assert(aligned_pow2(p, sizeof(*p)));
    fuzz_atomics();
    return __sync_val_compare_and_swap(p, old, n);
}

bool _cas_won(uptr n, volatile uptr *p, uptr *old){
    assert(aligned_pow2(p, sizeof(*p)));
    fuzz_atomics();
    return __atomic_compare_exchange_n(p, old, n,
                                       0, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
}


bool _cas2_won(dptr n, volatile dptr *p, dptr *old){
    assert(aligned_pow2(p, sizeof(*p)));
    fuzz_atomics();
    return __atomic_compare_exchange_n(p, old, n,
                                       0, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);
}

howok _cas_ok(uptr n, volatile uptr *p, uptr *old){
    if(_cas_won(n, p, old))
        return WON;
    if(*old == n)
        return OK;
    return NOT;
}

howok _cas2_ok(dptr n, volatile dptr *p, dptr *old){
    if(_cas2_won(n, p, old))
        return WON;
    if(*old == n)
        return OK;
    return NOT;
}

bool _upd_won(uptr n, volatile uptr *p, uptr *old){
    if(!_cas_won(n, p, old))
        return false;
    *old = n;
    return true;
}

bool _upd2_won(dptr n, volatile dptr *p, dptr *old){
    if(!_cas2_won(n, p, old))
        return false;
    *old = n;
    return true;
}

howok _upd_ok(uptr n, volatile uptr *p, uptr *old){
    if(_upd_won(n, p, old))
        return WON;
    if(*old == n)
        return OK;
    return NOT;
}

howok _upd2_ok(dptr n, volatile dptr *p, dptr *old){
    if(_upd2_won(n, p, old))
        return WON;
    if(*old == n)
        return OK;
    return NOT;
}

uptr _atomic_read(volatile uptr *p){
    fuzz_atomics();
    return *p;
}

void _atomic_write(uptr n, volatile uptr *p){
    fuzz_atomics();
    *p = n;
}

dptr _atomic_read2(volatile dptr *p){
    return _cas2(0, p, 0);
}

void _atomic_write2(dptr n, volatile dptr *p){
    for(dptr o = *p;;)
        if(_cas2_won(n, p, &o))
            return;
}

uptr _xadd_iff(uptr a, volatile uptr *p, uptr lim){
    for(uptr r = *p;;){
        if(r + a > lim)
            return r;
        if(_cas_won(r + a, p, &r))
            return r;
    }
}

uptr _xsub_iff(uptr s, volatile uptr *p){
    for(uptr r = *p;;)
        if(r < s || _cas_won(r - s, p, &r))
            return r;
}
