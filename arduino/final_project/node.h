/***************************************************************************/
// File			  [node.h]
// Author		  [Erik Kuo, Joshua Lin]
// Synopsis		[Code for managing car movement when encounter a node]
// Functions  [/* add on your own! */]
// Modify		  [2020/03/027 Erik Kuo]
/***************************************************************************/
#ifndef NODE
#define NODE
#include "track.h"
/*===========================import variable===========================*/
int extern IRpin_LL,IRpin_L,IRpin_M,IRpin_R,IRpin_RR;
int extern _Tp;
/*===========================import variable===========================*/

// TODO: add some function to control your car when encounter a node
// here are something you can try: left_turn, right_turn... etc.

bool checknode(){
    int analogPins[] = {32, 34, 36, 38, 40};
    bool temp = true;
    for(int i = 0; i < 5; i++){
        temp = temp && digitalRead(analogPins[i]);
    }//and運算必須全部都是1才會輸出1
    //Serial.println(bool(temp));    
    return temp;
}

void turn_around(){
    while(checknode()){
        motorWrite(150, 150);
        delay(20);
    }
    motorWrite(150, -150);
    delay(1000);
}

void turn_right(){
    while(checknode()){
        motorWrite(150, 150);
        delay(20);
    }
    motorWrite(150, 0);
    delay(1000);
}

void turn_left(){
    while(checknode()){
        motorWrite(150, 150);
        delay(20);
    }
    motorWrite(0, 150);
    delay(1000);
}
void ignore(){
  while(checknode()){
        motorWrite(150, 150);
        delay(20);
    }
}
#endif