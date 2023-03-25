#ifndef _ARR_LIST_
#define _ARR_LIST_


typedef enum suit {heart, spades, diamonds, clubs} suit_t;



typedef struct card
{
    int number;
    suit_t suit;
} card_t;



typedef struct node
{
      card_t card;
      struct node* next;
} node_t;



void append(node_t* head, card_t new_card);
void print(node_t* head);
void remove_node(node_t* head, card_t card);


#endif
