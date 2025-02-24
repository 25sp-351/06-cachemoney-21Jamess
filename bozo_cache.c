#include "bozo_cache.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CACHE_ENTRIES 1000
#define BUFFER_SIZE 512

typedef struct {
    int key;
    char value[BUFFER_SIZE];
} CacheEntry;

static CacheEntry cache_entries[MAX_CACHE_ENTRIES];
static int cache_count    = 0;
static int cache_requests = 0;
static int cache_hits     = 0;

static void bozo_init() {
    cache_count    = 0;
    cache_requests = 0;
    cache_hits     = 0;
    for (int i = 0; i < MAX_CACHE_ENTRIES; i++) {
        cache_entries[i].key      = -1;
        cache_entries[i].value[0] = '\0';
    }
}

static void bozo_cleanup() {
    cache_count = 0;
}

static bool bozo_is_present(int val) {
    cache_requests++;
    for (int i = 0; i < cache_count; i++) {
        if (cache_entries[i].key == val) {
            cache_hits++;
            return true;
        }
    }
    return false;
}

static char* bozo_get(int val) {
    for (int i = 0; i < cache_count; i++)
        if (cache_entries[i].key == val)
            return cache_entries[i].value;
    return NULL;
}

static void bozo_insert(int val, char* result) {
    if (cache_count < MAX_CACHE_ENTRIES) {
        cache_entries[cache_count].key = val;
        strncpy(cache_entries[cache_count].value, result, BUFFER_SIZE - 1);
        cache_entries[cache_count].value[BUFFER_SIZE - 1] = '\0';
        cache_count++;
    }
}

static CacheStats bozo_stats() {
    CacheStats s = {cache_requests, cache_hits};
    return s;
}

CacheProvider BozoProvider(void) {
    CacheProvider cp;
    cp.initialize = bozo_init;
    cp.cleanup    = bozo_cleanup;
    cp.is_present = bozo_is_present;
    cp.get        = bozo_get;
    cp.insert     = bozo_insert;
    cp.stats      = bozo_stats;
    return cp;
}
