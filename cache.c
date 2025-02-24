#include "cache.h"

#include <stdlib.h>
#include <string.h>

static CacheProvider _provider;
static ProviderFunction _downstream;

char* cached_money_provider(int val) {
    if (_provider.is_present(val))
        return _provider.get(val);
    char* result = _downstream(val);
    _provider.insert(val, result);
    return result;
}

ProviderFunction set_provider(CacheProvider prov, ProviderFunction downstream) {
    _provider   = prov;
    _downstream = downstream;
    _provider.initialize();
    return cached_money_provider;
}

CacheStats stats(void) {
    return _provider.stats();
}

void cleanup(void) {
    _provider.cleanup();
}
