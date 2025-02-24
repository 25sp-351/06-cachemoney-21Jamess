#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "bozo_cache.h"
#include "cache.h"
#include "money_to_string.h"

// Test function: verifies the money_to_string conversion and cache behavior.
void test_money_to_string() {
    // Set up the caching provider.
    CacheProvider cp                        = BozoProvider();
    ProviderFunction cached_money_to_string = set_provider(cp, money_to_string);

    // First call: should compute the result (cache miss).
    char *result1        = cached_money_to_string(43292);
    const char *expected = "four hundred thirty-two dollars ninety-two cents";
    assert(strcmp(result1, expected) == 0);

    // Second call with the same input: should return the cached result.
    char *result2 = cached_money_to_string(43292);
    assert(strcmp(result2, expected) == 0);

    // Check cache statistics:
    // For two calls with the same input:
    CacheStats st = stats();
    assert(st.cache_requests == 2);
    assert(st.cache_hits == 1);

    cleanup();
    printf("All tests passed.\n");
}

int main(void) {
    test_money_to_string();
    return 0;
}
