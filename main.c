#include <stdlib.h>
#include <stdio.h>
#include <time.h>



struct card
{
      int type;
      int suit;
};
typedef struct card card_t;


struct node
{
      card_t card;
      int position;
      struct node* next;
};
typedef struct node node_t;


struct table_hand
{
      card_t card;
      int is_playable;
};
typedef struct table_hand table_hand_t ;



void push(node_t** head, card_t* new_card);   // pushes the newest node to the head of the list
void remove_node(node_t** head, int pos);   //removes a node by value
void generate_rand_hand(node_t** hand, int deck[4][13]);
void shuffle_deck(int deck[4][13]);
void generate_table_hand(table_hand_t* hand, int deck[4][13]);





///////////////////////////////////////////////////////////






int main(int argc, char** argv)
{
      int deck[4][13] = {{1,2,3,4,5,6,7,8,9,10,11,12,13},  //1=ace, 11=jack, 12=queen, 13=king
                          {1,2,3,4,5,6,7,8,9,10,11,12,13},  //rows= heart,clubs,diamonds,spades
                          {1,2,3,4,5,6,7,8,9,10,11,12,13},
                          {1,2,3,4,5,6,7,8,9,10,11,12,13}};

      node_t* player_hand = (node_t*)malloc(sizeof(node_t));
      node_t* computer_hand = (node_t*)malloc(sizeof(node_t));

      shuffle_deck(&deck);

      generate_rand_hand(&player_hand, &deck);
      generate_rand_hand(&computer_hand, &deck);


      table_hand_t player_down_hand[3];
      table_hand_t player_up_hand[3];
      table_hand_t computer_down_hand[3];
      table_hand_t computer_up_hand[3];

      generate_table_hand(&player_down_hand, &deck);
      generate_table_hand(&player_up_hand, &deck);
      generate_table_hand(&computer_down_hand, &deck);
      generate_table_hand(&computer_up_hand, &deck);


      for(int i = 0; i < 4; i++)
      {
            printf("%d\n", i);
            for(int j = 0; j < 13; j++)
            {
                  printf("%d, ", deck[i][j]);
            }
            printf("\n");
      }

      while(1)
      {
           break; 
      }



      return 0;
}







///////////////////////////////////////////////////////////
///==============/ linked list functions /=============///
/////////////////////////////////////////////////////////


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


      if((*head)->next == NULL)               // if the new node is the first in the list
      {
            tmp->position = 0;
      }else
      {
            tmp->position = (*head)->position + 1;
      }

      tmp->card.suit = new_card->suit;      // links val to new nodes value
      tmp->card.type = new_card->type;      // links val to new nodes value
      tmp->next = *head;                    // links the next node to the head of the list
      *head = tmp;                          // replaces the head of the list as the new node
}






////////////////////////////////////////////////////////////
///============/ generate random deck/hands /===========///
//////////////////////////////////////////////////////////


void generate_rand_hand(node_t** hand, int deck[4][13])
{
      card_t new_card;
      srand(time(0));

      for(int i = 0; i < 3; i++)
      {
            int rand_suit = rand() % 4;            //create a random suit

            int j = 0;
            while(deck[rand_suit][j] == 0)         //find the first non-0 number
            {
                  j++;
            }

            new_card.type = deck[rand_suit][j];    //add the new cards suit and type
            new_card.suit = rand_suit;

            deck[rand_suit][j] = 0;                //set the curent number 0 to prevent duplicate cards

            push(hand, &new_card);                 //add the new card to a node in the given hand
      }
}



///////////////////////////////////////////////////////////



void shuffle_deck(int deck[4][13])
{
      srand(time(NULL));

      for(int i = 0; i < 4; i++)
      {
            for(int j = 0; j < 13; j++)
            {
                  int rand_pos = rand() % 13 + 1;            //generate random positions within the list
                  int rand_pos1 = rand() % 13 + 1;

                  int tmp = deck[i][rand_pos1];              //swap the items in the random positions
                  deck[i][rand_pos1] = deck[i][rand_pos];
                  deck[i][rand_pos] = tmp;
            }
      }
}



////////////////////////////////////////////////////////////



void generate_table_hand(table_hand_t* hand, int deck[4][13])
{
      srand(time(NULL));

      for(int i = 0; i < 3; i++)
      {
            int rand_suit = rand() % 4;            //create a random suit

            int j = 0;
            while(deck[rand_suit][j] == 0)         //find the first non-0 number
            {
                  j++;
            }

            hand[i].is_playable = 1;
            hand[i].card.suit = rand_suit;
            hand[i].card.type = deck[rand_suit][j];

            deck[rand_suit][j] = 0;
      }
}
