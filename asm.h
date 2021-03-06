/** @file x86/asm.h
 *  x86-specific assembly functions
 *  @author matthewj S2008
 */

#ifndef X86_ASM_H
#define X86_ASM_H

#include <stdint.h>


/** Loads a new gdt */
void lgdt(void *gdt, unsigned int limit);
/** Loads a new idt */
void lidt(void *idt, unsigned int limit);
/** Read address of IDT */
void *idt_base(void);

/** Disables interrupts */
static inline
void disable_interrupts(void){
    asm volatile("cli":::"memory");
}
/** Enables interrupts */
static inline
void enable_interrupts(void){
    asm volatile("sti":::"memory");
}

static inline
void *approx_sp(void){
    void *sp;
    asm("mov %%esp, %0" : "=rm"(sp));
    return sp;
}

static inline
void hlt(void){
    asm volatile("hlt":::"memory");
}

bool interrupts_enabled(void);

static inline
u64 rdtsc(){
    u32 l, h;
    __asm__ __volatile__("rdtsc":"=a"(l),"=d"(h));
    return ((u64) h << 32) | l;
}

/** Reads 1 byte from given port */
uint8_t inb(uint16_t port);
/** Reads 2 bytes from given port */
uint16_t inw(uint16_t port);
/** Reads 4 bytes from given port */
uint32_t ind(uint16_t port);

/** Writes 1 byte to target port */
void outb(uint16_t port, uint8_t val);
/** Writes 2 bytes to target port */
void outw(uint16_t port, uint16_t val);
/** Writes 4 bytes to target port */
void outd(uint16_t port, uint32_t val);

/** Delay 1/8 microsecond */
void iodelay(void);

/** @brief Load a segment selector into the task register. */
void ltr(unsigned int sel);

/* #define enable_interrupts() trace(SCHED, 3, enable_interrupts) */
/* #define disable_interrupts() trace(SCHED, 3, disable_interrupts) */

#endif /* !X86_ASM_H */
