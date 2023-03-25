#include "arr_list.h"
#include <stdlib.h>
#include <stdio.h>

void append(node_t* head, card_t new_card)
{
        node_t* current = head;
        while(current->next != NULL) 
        {
                current = current->next;
        }


        // use the current unused node
        // then create a new one
        current->card.number = new_card.number;
        current->card.suit = new_card.suit;
        current->next = (node_t*)malloc(sizeof(node_t));
}



void print(node_t* head)
{
        printf("::hand::\n");

        node_t* current = head;
        while(current->next != NULL)
        {
                printf("%d of %d\n", current->card.number, current->card.suit);
                current = current->next;
        }

        printf("\n");
}



void remove_node(node_t *head, card_t card)
{
        node_t* current = head;
        node_t* prev = NULL;
        while (current->next != NULL) 
        {
                // if a matching card has been found
                if( (current->card.number == card.number) && (current->card.suit == card.suit) )      
                {
                        // if we are at the head of the list
                        // this prevents the head from being deleted and being "replaced"
                        if( prev == NULL )
                        {
                                prev = head;
                                head = current->next;
                                free(prev);
                                return;
                        }


                        // else free the current node
                        prev->next = current->next;
                        free(current);
                        return;
                }

                prev = current;
                current = current->next;
        }
}
