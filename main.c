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





void push(node_t** head, card_t* new_card);   // pushes the newest node to the head of the list
void remove_node(node_t** head, int pos);   //removes a node by value
void print_list(node_t* head);


card_t random_card(int deck[4][13]);

void generate_rand_hand(node_t** hand, int deck[4][13]);
void shuffle_deck(int deck[4][13]);
void initialise_table(card_t* table);

node_t* select_hand(node_t* hand,node_t* up_hand,node_t* down_hand );
int select_card(node_t* hand, card_t* table);
int validate_card(card_t* card, card_t* table);





///////////////////////////////////////////////////////////






int main(int argc, char** argv)
{
      int deck[4][13] = {{1,2,3,4,5,6,7,8,9,10,11,12,13},  //1=ace, 11=jack, 12=queen, 13=king
                          {1,2,3,4,5,6,7,8,9,10,11,12,13},  //rows= heart,clubs,diamonds,spades
                          {1,2,3,4,5,6,7,8,9,10,11,12,13},
                          {1,2,3,4,5,6,7,8,9,10,11,12,13}};

      //generate linked list heads for player and computer hands
      //
      node_t* player_hand = (node_t*)malloc(sizeof(node_t));
      node_t* computer_hand = (node_t*)malloc(sizeof(node_t));

      node_t* player_up_hand = (node_t*)malloc(sizeof(node_t));
      node_t* computer_up_hand = (node_t*)malloc(sizeof(node_t));

      node_t* player_down_hand = (node_t*)malloc(sizeof(node_t));
      node_t* computer_down_hand = (node_t*)malloc(sizeof(node_t));


      shuffle_deck(&deck);


      //generate random hands for computer and player
      //up_hands will be visible to both player and computer
      //down hands will be invisible to both
      //
      //generate_rand_hand(&player_hand, &deck);
      generate_rand_hand(&computer_hand, &deck);

      generate_rand_hand(&player_up_hand, &deck);
      generate_rand_hand(&computer_up_hand, &deck);

      generate_rand_hand(&player_down_hand, &deck);
      generate_rand_hand(&computer_down_hand, &deck);


      //create a random starting card
      //
      card_t table = random_card(&deck);



      
      //main game loop
      //
      int current_player = 0;      //0 = player, 1 = computer
      int card_position;
      node_t* current_hand;
      card_t current_card;

      while(1)
      {
            printf("your hand:\n");
            if(~(current_player))   //player
            {
                  current_hand = select_hand(player_hand, player_up_hand, player_down_hand);
                  card_position = select_card(current_hand, &table, &current_card);

                  if(card_position < 0)
                  {
                        printf("invalid position\n");
                        return 0;
                  }

                  int card_to_play = validate_card(&current_card, &table);
                  if(card_to_play)
                  {
                        play_card();
                  }
                  // pick up deck
            }
            else  //computer
            {
                  print_list(computer_hand);
            }

            return 0;

      }



      return 0;
}








node_t* select_hand(node_t* hand,node_t* up_hand,node_t* down_hand )
{

      if(hand != NULL)
      {
            print_list(hand);
            return hand;
      }
      else if(up_hand != NULL)
      {
            print_list(up_hand);
            return up_hand;
      }
      else
      {
            print_list(down_hand);
            return down_hand;
      }
}



////////////////////////////////////////////////////////////



int select_card(node_t* hand, card_t* table, card_t* current_card)
{
      int selected_card_pos;
      node_t* curent = hand;

      printf("\n\nselect card by its position: ");
      scanf("%d", selected_card_pos);
      
     while(curent->next != NULL)
     {
           if(curent->position == selected_card_pos)
           {
                 *current_card = curent->card;
                 return curent->position;
           }
     } 

     return -1;
}



////////////////////////////////////////////////////////////



//2,10,ace,7,8
int validate_card(card_t* card, card_t* table)
{
      switch(card->type)
      {
            case 2: return 2;

            case 10: return 10;

            case 1: return 1;
            
            default:
                  break;
      }

      if(card->type > table->type)
      {
            if(card->type == 8)
            {
                  return 8;
            }
            else if(card->type == 7)
            {
                  return 7;
            }

            return card->type;
      }
      
      return 0;
           
}



////////////////////////////////////////////////////////////



void play_card(node_t hand, node_t table, int card, int pos)
{

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
                        break;

                  }
                  else    // we are at the head of the list
                  {  

                        prev = (*head);
                        *head = (*head)->next;  //makes the head of the list the next item along
                        free(prev);             //frees the old head of list
                        break;

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




void print_list(node_t* head)
{
      node_t* curent = head;
      while(curent->next != NULL)
      {
            printf("%d: ", curent->position);

            switch (curent->card.suit) 
            {
                  case 0: printf("heart, "); break;
                  case 1: printf("clubs, "); break;
                  case 2: printf("diamonds, "); break;
                  case 3: printf("spades, "); break;
            }

            switch (curent->card.type)
            {
                  case 1: printf("Ace\n"); break;
                  case 11: printf("Jack\n"); break;
                  case 12: printf("Queen\n"); break;
                  case 13: printf("King\n"); break;
            
                  default: printf("%d\n", curent->card.type); break;
            }

            curent = curent->next;
      }
}






////////////////////////////////////////////////////////////
///============/ generate random deck/hands /===========///
//////////////////////////////////////////////////////////


void generate_rand_hand(node_t** hand, int deck[4][13])
{
      for(int i = 0; i < 3; i++)
      {
            card_t new_card;
            new_card = random_card(deck);
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



/////////////////////////////////////////////////////////////




card_t random_card(int deck[4][13])
{
      srand(time(NULL)); 
      int rand_suit = rand() % 4;            //create a random suit

      int j = 0;
      while(deck[rand_suit][j] == 0)         //find the first non-0 number
      {
            j++;
      }

      card_t rand_card = {deck[rand_suit][j], rand_suit};
      deck[rand_suit][j] = 0;                         // make the used card 0 to prevent duplicate numbers

      return rand_card;
}
