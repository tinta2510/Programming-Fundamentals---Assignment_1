#include "knight.h"

void display(int HP, int level, int remedy, int maidenkiss, int phoenixdown, int rescue) {
    cout << "HP=" << HP
        << ", level=" << level
        << ", remedy=" << remedy
        << ", maidenkiss=" << maidenkiss
        << ", phoenixdown=" << phoenixdown
        << ", rescue=" << rescue << endl;
}

void adventureToKoopa(string file_input, int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue){
    ifstream input(file_input);
    //Information about the Knight of the Round Table
    input>>HP; 
    input>>level; 
    input>>remedy; 
    input>>maidenkiss; 
    input>>phoenixdown; 
    rescue = -1; 
    int maxHP = HP;
    //The itinerary to Koopa
    int round[100], num=0, pos; //num = the number of round; pos = position of the pointer in fstream
    while (input>>round[num]){ 
        num++;
        pos = input.tellg(); 
    }
    input.close();

    //Get the name of input files
    char files_input_name[100];
    string file_mush_ghost,file_asclepius_pack,file_merlin_pack;

    ifstream input1(file_input);
    input1.seekg(pos+1,ios::beg);
    input1>>files_input_name;

    file_mush_ghost = cut_string(files_input_name);
    file_asclepius_pack = cut_string(files_input_name);
    file_merlin_pack = cut_string(files_input_name);
    input1.close();

    bool lancelot = false;
    if (HP==999) rescue = 1; //King Authur
    else if (check_prime_number(HP)) lancelot = true; //lancelot

    //Event
    int count_event_6=0,count_event_7=0,level_event_7; //dem so vong phat cho su kien 6
    for(int i=0;(i<num)&&(rescue==-1);i++){
        if (round[i]==0){
            rescue = 1; 
            break;
        }
        else if ((1<=round[i])&&(round[i]<=5)){
            if (lancelot) level = level<10? level+1:level;
            else event1_5(HP,level,phoenixdown,rescue,i+1,round[i],maxHP);

            display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
        }
        else if ((round[i]==6)&&(count_event_6==0)&&(count_event_7==0)){
            if (lancelot){
                if (level<=8) level += 2;
                else if (level==9) level++;
            }
            else event6(HP, level, remedy, i+1, count_event_6);

            display(HP, level, remedy, maidenkiss, phoenixdown, rescue);  
        }
        else if ((round[i]==7)&&(count_event_6==0)&&(count_event_7==0)){
            if (lancelot){
                if (level<=8) level += 2;
                else if (level==9) level++;
            }
            else event7(HP, level, maidenkiss, i+1, count_event_7, level_event_7);

            display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
        }
        else if (round[i]==11){
            event11(HP, level, phoenixdown, maxHP);
            display(HP,level,remedy,maidenkiss,phoenixdown,rescue);  
        }
        else if (round[i]==12){
            if (HP>1) HP = nearest_Fibonacci(HP);
            display(HP,level,remedy,maidenkiss,phoenixdown,rescue);  
        }
        else if (round[i]>=130) {}
        else if (round[i]==15) {if (remedy<99)      remedy++;     }
        else if (round[i]==16) {if (maidenkiss<99)  maidenkiss++; }
        else if (round[i]==17) {if (phoenixdown<99) phoenixdown++;}
        else if (round[i]==18) {
            event18(file_merlin_pack, HP, maxHP);
            display(HP,level,remedy,maidenkiss,phoenixdown,rescue);  
        }
        else if (round[i]==19) {} ///unfinished
        else if (round[i]==99) {
            if (lancelot&&(level>=8)) level = 10;
            else if (!lancelot && (level==10));
            else rescue = 0;
            display(HP,level,remedy,maidenkiss,phoenixdown,rescue); 
        }


        //Dem so vong phat
        if ((round[i] == 6)&&(round[i] == 7)) continue;

        if ((count_event_6 >= 2)) count_event_6--;
        else if (count_event_6==1){
            count_event_6--;
            HP *= 5;
            if (HP>maxHP) HP=maxHP;
        } 
        if ((count_event_7 >= 2)) count_event_7--;
        else if (count_event_7==1){
            count_event_7--;
            level = level_event_7;
        } 
    }

    if (rescue==-1) rescue=1; //there are no more events to follow, the knight reaches Koopa

    display(HP,level,remedy,maidenkiss,phoenixdown,rescue);   
}

void event1_5(int & HP, int & level, int & phoenixdown, int & rescue, int i, int event, int maxHP){
    int levelO,b,damage=0;
    float baseDamage;
    //Opponent's level
    b = i%10;
    levelO = i>6? (b>5? b : 5) : b;

    //Opponent's baseDamage
    switch (event){
        case 1: {baseDamage = 1  ; break;}
        case 2: {baseDamage = 1.5; break;}
        case 3: {baseDamage = 4.5; break;}
        case 4: {baseDamage = 7.5; break;}
        case 5: {baseDamage = 9.5; break;}
    }

    if (level>levelO){
        if (level<10) level++;
    }
    else if (level<levelO){
        damage = baseDamage * levelO * 10;
        HP -= damage;
    }

    if (HP<=0){
        if (phoenixdown>0){
            HP = maxHP; 
            phoenixdown--;
        }
        else if (phoenixdown==0) rescue = 0;
    }

}

void event6(int & HP, int & level, int & remedy, int i, int & count_event_6){
    int levelO,b;
    b = i%10;
    levelO = i>6? (b>5? b : 5) : b;

    if (level>levelO){
        if (level<=8) level += 2;
        else if (level==9) level++;
    }
    else if (level<levelO){
        if (remedy>=1){
            remedy--;
        }
        else{
            HP = HP<=5? 1: HP/5;
            count_event_6 = 3;
        }
    }
} 

void event7(int & HP, int & level, int & maidenkiss, int i, int & count_event_7, int & level_event_7){
    int levelO,b;
    b = i%10;
    levelO = i>6? (b>5? b : 5) : b;

    if (level>levelO){
        if (level<=8) level += 2;
        else if (level==9) level++;
    }
    else if (level<levelO){
        if (maidenkiss>=1){
            maidenkiss--; 
        }
        else{
            level_event_7 = level;
            level = 1;
            count_event_7 = 3;
        }
    }
}

void event11(int & HP, int level, int phoenixdown, int maxHP){
    unsigned short int n1 = ((level + phoenixdown)%5 + 1) * 3;
    calculate_HP_event11(HP, n1);
    if (HP>maxHP) HP = maxHP;
}

void calculate_HP_event11(int & HP,int n1){
    unsigned short int s1=0;
    for (int i=0;i<n1;i++){
        s1 += 99-2*i;
    }
    HP += (s1%100);
    for (int i=HP+1;true;i++){
        if (check_prime_number(i)){
            HP = i;
            break;
        }
    }
}

bool check_prime_number(int n){
    char count=0;
    if (n>=2){
        for (int i=1;i<=n/2;i++){
            if (n%i==0) count++;
        }
    }
    else return 0;

    if (count == 1) return 1;
    else return 0;
}

int nearest_Fibonacci(int HP){
    unsigned short int arr[HP] = {1,1}; 
    int i = 2;
    while (arr[i-1]<HP){
        arr[i] = arr[i-1] + arr[i-2];
        i++;
    }
    return arr[i-2];
    
}

string cut_string(char * s){
	string temp;
	static unsigned short int i=0;
    for (;s[i]!='\0';i++){
    	if (s[i] != ',') temp += s[i]; 
    	else {i++; break;}
    }
    return temp;
}

void event18(string file_merlin_pack, int & HP, int maxHP){
    ifstream merlin_pack(file_merlin_pack);
    char n9;
    merlin_pack>>n9;
    for (int i=0;i<n9;i++){
        string s;
        merlin_pack>>s;
        if (substr_in_str("Merlin",s)) HP += 3;
        else if (substr_in_str("merlin",s)) HP += 3;
        else{
            char count = 0;
            if ((substr_in_str("M",s))||(substr_in_str("m",s))) count++;
            if ((substr_in_str("E",s))||(substr_in_str("e",s))) count++;
            if ((substr_in_str("R",s))||(substr_in_str("r",s))) count++;
            if ((substr_in_str("L",s))||(substr_in_str("l",s))) count++;
            if ((substr_in_str("I",s))||(substr_in_str("i",s))) count++;
            if ((substr_in_str("N",s))||(substr_in_str("n",s))) count++;

            if (count==6) HP += 2;
        }
    }
    if (HP>maxHP) HP = maxHP; //Khong tang qua maxHP
}

bool substr_in_str(string substr,string str){
	unsigned short int len = substr.length(),i=0;
	while (str[i] != '\0'){
		if (str[i] == substr[0]){
			char count=1;
			for (;count<len;count++){
				if (str[i+count] == substr[count]);
				else break;
			}
			if (count==len) return 1;
			else i++;
		}
		else i++;
	}
	return 0; 
}

//g++ -o main main.cpp knight.cpp -I . -std=c++11
//./main tc1_input