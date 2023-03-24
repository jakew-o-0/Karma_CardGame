#include<stdio.h>
#include<stdlib.h>
#include "arr_list.h"

int main(void)
{
        card_t hand[1];
        hand[0].number = 5;
        hand[0].suit = heart;

        card_t new_card = {10, clubs};
        append(hand, &new_card);

        new_card.number= 1;
        new_card.suit = spades;
        append(hand, &new_card);

        int len = sizeof(hand) / (int)sizeof(hand[0]);
        printf("hand: %d\nhand[0]: %d\nlen: %d\n",sizeof(hand), sizeof(hand[0]), len);
        for(int i = 0; i <= len; i++)
        {
                printf("card: %d of %d\n", hand[i].number, hand[i].suit);
        }
        return 0;
}