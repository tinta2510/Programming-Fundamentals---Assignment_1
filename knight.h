#ifndef __KNIGHT_H__
#define __KNIGHT_H__

#include "main.h"

void display(int HP, int level, int remedy, int maidenkiss, int phoenixdown, int rescue);
void adventureToKoopa(string file_input, int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue);

void event1_5(int & HP, int & level, int & phoenixdown, int & rescue, int i, int event, int maxHP);

void event6(int & HP, int & level, int & remedy, int i, int & count_event_6);

void event7(int & HP, int & level, int & maidenkiss, int i, int & count_event_7, int & level_event_7);

void event11(int & HP, int level, int phoenixdown, int maxHP);
void calculate_HP_event11(int & HP,int n1);
bool check_prime_number(int n);

int nearest_Fibonacci(int HP);

string cut_string(string s,short int & count_string);

void event18(string file_merlin_pack, int & HP, int maxHP);
bool substr_in_str(string substr,string str);

void event19(string file_asclepius_pack, int & remedy, int & maidenkiss, int & phoenixdown);
#endif // __KNIGHT_H__