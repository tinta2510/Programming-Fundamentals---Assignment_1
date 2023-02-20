#ifndef __KNIGHT_H__
#define __KNIGHT_H__

#include "main.h"

void display(int HP, int level, int remedy, int maidenkiss, int phoenixdown, int rescue);
void adventureToKoopa(string file_input, int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue);

void event0(int & rescue);

void event1_5(int & HP, int & level, int & phoenixdown, int & rescue, int i, int event, int maxHP);

void event6(int & HP, int & level, int & remedy, int i, int & count_event_6);

void event7(int & HP, int & level, int & maidenkiss, int i, int & count_event_7, int & level_event_7);

void event11(int & HP, int level, int phoenixdown, int maxHP);
void calculate_HP_event11(int & HP,int n1);
bool check_prime_number(int n);


#endif // __KNIGHT_H__