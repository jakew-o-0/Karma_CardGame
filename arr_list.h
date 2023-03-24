#ifndef _ARR_LIST_
#define _ARR_LIST_


typedef enum suit {heart, spades, diamonds, clubs} suit_t;
struct card
{
    int number;
    suit_t suit;
};
typedef struct card card_t;

void append(card_t* list, card_t* new_card, int len);
void print(card_t* list);


#endif