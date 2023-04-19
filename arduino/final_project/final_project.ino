/***************************************************************************/
// File       [final_project.ino]
// Author     [Erik Kuo]
// Synopsis   [Code for managing main process]
// Functions  [setup, loop, Search_Mode, Hault_Mode, SetState]
// Modify     [2020/03/27 Erik Kuo]
/***************************************************************************/

#define DEBUG // debug flag

// for RFID
#include <SPI.h>
#include <MFRC522.h>

/*===========================define pin & create module object================================*/
// BlueTooth
// BT connect to Serial1 (Hardware Serial)
// Mega               HC05
// Pin  (Function)    Pin
// 18    TX       ->  RX
// 19    RX       <-  TX
// TB6612, 請按照自己車上的接線寫入腳位(左右不一定要跟註解寫的一樣)
#define MotorR_I1      2 //定義 A1 接腳（右）
#define MotorR_I2      3 //定義 A2 接腳（右）
#define MotorR_PWMR    11//定義 ENA (PWM調速) 接腳
#define MotorL_I3      5 //定義 B1 接腳（左）
#define MotorL_I4      6 //定義 B2 接腳（左）
#define MotorL_PWML    12//定義 ENB (PWM調速) 接腳
// 循線模組, 請按照自己車上的接線寫入腳位
int IRpin_LL = 32;
int IRpin_L  = 34;
int IRpin_M  = 36;
int IRpin_R  = 38;
int IRpin_RR = 40;
// RFID, 請按照自己車上的接線寫入腳位
#define RST_PIN      49        // 讀卡機的重置腳位
#define SS_PIN       53       // 晶片選擇腳位
MFRC522 mfrc522(SS_PIN, RST_PIN);  // 建立MFRC522物件

#define board_led 13
/*===========================define pin & create module object===========================*/

/*============setup============*/
void setup()
{
   //bluetooth initialization
   Serial1.begin(9600);
   //Serial window
   Serial.begin(9600);
   //RFID initial
   SPI.begin();
   mfrc522.PCD_Init();
   //TB6612 pin
   pinMode(MotorR_I1,   OUTPUT);
   pinMode(MotorR_I2,   OUTPUT);
   pinMode(MotorL_I3,   OUTPUT);
   pinMode(MotorL_I4,   OUTPUT);
   pinMode(MotorL_PWML, OUTPUT);
   pinMode(MotorR_PWMR, OUTPUT);
   //tracking pin
   pinMode(IRpin_LL, INPUT); 
   pinMode(IRpin_L, INPUT);
   pinMode(IRpin_M, INPUT);
   pinMode(IRpin_R, INPUT);
   pinMode(IRpin_RR, INPUT);
   pinMode(board_led, OUTPUT);

#ifdef DEBUG
  Serial.println("Start!");
#endif
}
/*============setup============*/

/*=====Import header files=====*/
#include "RFID.h"
#include "track.h"
#include "bluetooth.h"
#include "node.h"
/*=====Import header files=====*/

/*===========================initialize variables===========================*/
int l2=0,l1=0,m0=0,r1=0,r2=0; //紅外線模組的讀值(0->white,1->black)
int _Tp=90; //set your own value for motor power
bool state=false; //set state to false to halt the car, set state to true to activate the car
BT_CMD _cmd = NOTHING; //enum for bluetooth message, reference in bluetooth.h line 2
/*===========================initialize variables===========================*/

/*===========================declare function prototypes===========================*/
void Search();// search graph
void SetState();// switch the state
/*===========================declare function prototypes===========================*/

/*===========================define function===========================*/
int task[] = {2, 1, 0, 1, 3, 4};//0->ignore;1->turn_around;2->turn_right;3->turn_left; 4->stop
int task_counter = 0;
bool stop = false;
void loop()
{
  if(!state) motorWrite(0,0);
  else Search();
  SetState();

  l2 = digitalRead(IRpin_LL);
  l1 = digitalRead(IRpin_L);
  m0 = digitalRead(IRpin_M);
  r1 = digitalRead(IRpin_R);
  r2 = digitalRead(IRpin_RR);

  if(checknode()){
    Serial.println(task[task_counter]);
        switch(task[task_counter]){
            case 0: //ignore
                ignore();
                break;
            case 1:
                turn_around();
                break;
            case 2:
                turn_right();
                break;
            case 3:
                turn_left();
                break;
            case 4:
                stop = true;
                break;
        }
        if(task_counter + 1 < sizeof(task)/sizeof(int))task_counter++;
    }
    if(!stop)tracking();  



    byte a;
    byte* b=nullptr;
    b = rfid(a);
    if(b != nullptr){
      //Serial.print(*b);
      //Serial.println("hello");
      for(byte i = 0; i< a; i++){
        if(b[i] < byte(16))Serial.print('0');
        Serial.print(b[i], HEX);
        digitalWrite(board_led, HIGH);


      }
      send_byte(b, a);
  

      Serial.println();
      Serial.println();    
  }
}

void SetState()
{
  // TODO:
  // 1. Get command from bluetooth 
  // 2. Change state if need
}

void Search()
{
  // TODO: let your car search graph(maze) according to bluetooth command from computer(python code)
}
/*===========================define function===========================*/
