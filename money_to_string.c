#include "money_to_string.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CENTS_IN_DOLLAR 100
#define BUFFER_SIZE 512

char *money_to_string(int total_cents) {
    static char output_buffer[BUFFER_SIZE];
    // Clear the buffer at the beginning.
    output_buffer[0]       = '\0';

    bool is_value_negative = false;
    if (total_cents < 0) {
        is_value_negative = true;
        total_cents       = -total_cents;
    }

    int dollars                       = total_cents / CENTS_IN_DOLLAR;
    int cents_part                    = total_cents % CENTS_IN_DOLLAR;

    char dollar_text[BUFFER_SIZE / 4] = "";
    char cent_text[BUFFER_SIZE / 4]   = "";

    // Convert numbers to words.
    number_to_words(dollars, dollar_text);
    number_to_words(cents_part, cent_text);

    const char *dollar_word = (dollars == 1) ? "dollar" : "dollars";
    const char *cent_word   = (cents_part == 1) ? "cent" : "cents";

    if (is_value_negative) {
        snprintf(output_buffer, BUFFER_SIZE, "negative %s %s", dollar_text,
                 dollar_word);
    } else {
        snprintf(output_buffer, BUFFER_SIZE, "%s %s", dollar_text, dollar_word);
    }
    if (cents_part > 0) {
        snprintf(output_buffer + strlen(output_buffer),
                 BUFFER_SIZE - strlen(output_buffer), " %s %s", cent_text,
                 cent_word);
    }

    printf("DEBUG: Converting %d cents -> %s\n", total_cents, output_buffer);

    return output_buffer;
}

void number_to_words(int num_value, char *buffer) {
    static const char *ones[] = {
        "zero",    "one",     "two",       "three",    "four",
        "five",    "six",     "seven",     "eight",    "nine",
        "ten",     "eleven",  "twelve",    "thirteen", "fourteen",
        "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
    static const char *tens[] = {"",       "",      "twenty", "thirty",
                                 "forty",  "fifty", "sixty",  "seventy",
                                 "eighty", "ninety"};

    buffer[0]                 = '\0';  // Clear the buffer

    if (num_value < 20) {
        snprintf(buffer, BUFFER_SIZE, "%s", ones[num_value]);
    } else if (num_value < 100) {
        snprintf(buffer, BUFFER_SIZE, "%s", tens[num_value / 10]);
        if (num_value % 10) {
            snprintf(buffer + strlen(buffer), BUFFER_SIZE - strlen(buffer),
                     "-%s", ones[num_value % 10]);
        }
    } else if (num_value < 1000) {
        snprintf(buffer, BUFFER_SIZE, "%s hundred", ones[num_value / 100]);
        if (num_value % 100) {
            snprintf(buffer + strlen(buffer), BUFFER_SIZE - strlen(buffer),
                     " ");
            number_to_words(num_value % 100, buffer + strlen(buffer));
        }
    } else {
        int thousands = num_value / 1000;
        int remainder = num_value % 1000;
        number_to_words(thousands, buffer);
        snprintf(buffer + strlen(buffer), BUFFER_SIZE - strlen(buffer),
                 " thousand");
        if (remainder > 0) {
            snprintf(buffer + strlen(buffer), BUFFER_SIZE - strlen(buffer),
                     " ");
            number_to_words(remainder, buffer + strlen(buffer));
        }
    }
}
