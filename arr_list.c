#include "arr_list.h"
#include <stdlib.h>
#include <stdio.h>

void append(card_t* list, card_t* new_card, int len)
{
    list = realloc(list, (sizeof(list) + sizeof(*new_card)));
    list[len] = *new_card;
}

void print(card_t *list)
{
}
