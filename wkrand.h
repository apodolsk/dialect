#pragma once

typedef struct{
    uint seed;
    u64 last_update;
} rand_tls;
#define RAND_TLS {0xBA55C1EF, 0}

void rand_add_entropy(uint e);
void rand_update_local_seed(void);
bool randpcnt(uint pcnt);
