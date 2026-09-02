#include <stdio.h>
#include <stdlib.h>

#include "hunt_config.h"

typedef struct heap_link {
    char             valid;
    int              payload;
    struct heap_link *next;
} heap_link_t;


unsigned int equation(unsigned seed);

void calculate_treasure(void)
{
    unsigned correct_input = KEY_NUMBER_7;
    (void)correct_input;
    unsigned used_input;
    int Treasure7_valid = (used_input == KEY_NUMBER_7);
    int Treasure7 = equation(used_input);
    (void)Treasure7;
    (void)Treasure7_valid;
    puts("Hope you calculated the right treasure\n");
}
