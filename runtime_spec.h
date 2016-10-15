#pragma once

#include <tid.h>

struct cpu;
struct thread;

struct thread *this_thread(void);
dbg_id get_dbg_id(void);
void set_dbg_id(dbg_id id);

void slabs_init(void);
struct slab *new_slabs(cnt batch);

err pause_universe(void);
void resume_universe(void);

void *heap_start(void);
void *heap_end(void);

bool poisoned(void);

void breakpoint(void);
noreturn void panic(const char *_, ...);
err yield(tid to);
