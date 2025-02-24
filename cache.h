#ifndef CACHE_H
#define CACHE_H

#include <stdbool.h>

typedef char* (*ProviderFunction)(int val);

typedef void (*InitializeFunc)();
typedef void (*CleanupFunc)();
typedef bool (*BoolFunc)(int val);
typedef char* (*GetFunc)(int val);
typedef void (*InsertFunc)(int val, char* result);

typedef struct stats {
    int cache_requests;
    int cache_hits;
} CacheStats;

typedef struct provider {
    InitializeFunc initialize;
    CleanupFunc cleanup;
    BoolFunc is_present;
    GetFunc get;
    InsertFunc insert;
    CacheStats (*stats)(void);
} CacheProvider;

// given a downstream provider, this returns a caching provider function
ProviderFunction set_provider(CacheProvider prov, ProviderFunction downstream);

CacheStats stats(void);

void cleanup(void);

#endif
