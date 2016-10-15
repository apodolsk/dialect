#include <time.h>
#include <tid.h>
#include <thread.h>
#include <asm.h>

void race(cnt maxns, uint pcnt, uint idmod){
    if(!pcnt || T->racing || !randpcnt(pcnt))
        return;
    T->racing = true;
    if(interrupts_enabled()){
        yield((dptr) -1);
    }else
        nanosleep(&(struct timespec){.tv_nsec = rand() % maxns}, NULL);
    T->racing = false;
}
