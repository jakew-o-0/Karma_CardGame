#include <stdlib.h>
#include <stdio.h>



struct card
{
    char* type;
    char* suit;
};
typedef struct card card_t;


struct node
{
    card_t card;
    int position;
    struct node* next;
};
typedef struct node node_t;


void push(node_t** head, card_t* new_card);   // pushes the newest node to the head of the list
void remove_node(node_t** head, int pos);   //removes a node by value
void generate_rand_hand(node_t** hand);
void shuffle_deck(int* deck);


static int deck[4][13] = {{1,2,3,4,5,6,7,8,9,10,11,12,13},  //1=ace, 11=jack, 12=queen, 13=king
                          {1,2,3,4,5,6,7,8,9,10,11,12,13},  //rows= heart,clubs,diamonds,spades
                          {1,2,3,4,5,6,7,8,9,10,11,12,13},
                          {1,2,3,4,5,6,7,8,9,10,11,12,13}};


///////////////////////////////////////////////////////////


int main(int argc, char** argv)
{
    node_t* player_hand = (node_t*)malloc(sizeof(node_t));
    node_t* computer_hand = (node_t*)malloc(sizeof(node_t));

    shuffle_deck();
    
    generate_rand_hand(&player_hand);
    generate_rand_hand(&computer_hand);

    return 0;
}


///////////////////////////////////////////////////////////


void remove_node(node_t** head, int pos)
{
    node_t* current = *head;
    node_t* prev = NULL;

    while(current->next != NULL)
    {
        if(current->position == pos)
        {
            if(prev != NULL)    // if were not at the head of the list
            {   

                prev->next = current->next; // cut current out of the list
                free(current);              // free currents memory
                return NULL;                // end func

            }
            else    // we are at the head of the list
            {  

                prev = (*head);
                *head = (*head)->next;  //makes the head of the list the next item along
                free(prev);             //frees the old head of list
                return NULL;

            }
        }

        prev = current;
        current = current->next;
    }
}

///////////////////////////////////////////////////////////


void push(node_t** head, card_t* new_card)
{
    node_t* tmp;                            // creates a temp new node
    tmp = (node_t*) malloc(sizeof(node_t)); // allocates momory


    if((*head)->next == NULL)   // if the new node is the first in the list
    {
        tmp->position = 0;
    }else
    {
        tmp->position = (*head)->position + 1;
    }

    tmp->card.suit = new_card->suit;   // links val to new nodes value
    tmp->card.type = new_card->type;   // links val to new nodes value
    tmp->next = *head;  // links the next node to the head of the list
    *head = tmp;        // replaces the head of the list as the new node
}


///////////////////////////////////////////////////////////


void generate_rand_hand(node_t** hand)
{
    card_t new_card;
    
    for(int i = 0; i < 4; i++)
    {
        int rand_suit = rand() % 3;
        new_card.type = deck[rand_suit][i];
        new_card.suit = rand_suit;

        push(hand, &new_card);
    }
}



////////////////////////////////////////////////////////////



void shuffle_deck()
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; i < 13; i++)
        {
            int rand_pos = rand() % 12;
            int tmp = deck[i][j];
            deck[i][j] = deck[i][rand_pos];
            deck[i][rand_pos] = tmp;
        }
    }
}