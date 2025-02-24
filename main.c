#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bozo_cache.h"
#include "cache.h"
#include "money_to_string.h"

#define BUFFER_SIZE 512

int main(void) {
    // Select the caching policy.
    CacheProvider cp = BozoProvider();
    // Wrap money-to-string function with the caching framework, using the
    // direct function.
    ProviderFunction cached_money_to_string = set_provider(cp, money_to_string);

    char input[BUFFER_SIZE];
    printf("Enter a money value (in cents):\n");
    while (fgets(input, BUFFER_SIZE, stdin)) {
        // Remove newline character.
        input[strcspn(input, "\n")] = '\0';
        if (strlen(input) == 0)
            continue;
        int money_value = atoi(input);
        char* result    = cached_money_to_string(money_value);
        printf("%d = %s\n", money_value, result);
        printf("Enter a money value (in cents):\n");
    }
    // Print cache stats.
    CacheStats cs = stats();
    printf("Cache requests: %d, Cache hits: %d\n", cs.cache_requests,
           cs.cache_hits);
    cleanup();
    return 0;
}
