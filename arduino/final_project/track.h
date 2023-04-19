/***************************************************************************/
// File			  [track.h]
// Author		  [Erik Kuo]
// Synopsis		[Code used for tracking]
// Functions  [MotorWriting, MotorInverter, tracking]
// Modify		  [2020/03/27 Erik Kuo]
/***************************************************************************/

/*if you have no idea how to start*/
/*check out what you have learned from week 1 & 6*/
/*feel free to add your own function for convenience*/

/*===========================import variable===========================*/
#ifndef TRACK
#define TRACK
int extern _Tp;

int analogPin1 = 32;
int analogPin2 = 34;
int analogPin3 = 36;
int analogPin4 = 38;
int analogPin5 = 40;
int analogPins[] = {32, 34, 36, 38, 40};

int PWMA = 11;
int AIN1 = 2;
int AIN2 = 3;
int BIN1 = 5;
int BIN2 = 6;
int PWMB = 12;

int top_speed = 150;

double Kp = 0.35;
double Kd = 0.65;
double Ki = 0.005;

struct PID_increment{
	double kp;
	double ki;
	double kd;
	double target;
	double actual;
	double e;
	double e_pre_1;
	double e_pre_2;
	double A;
	double B;
	double C;
	PID_increment(double p, double i, double d):kp(p), ki(i), kd(d), target(0), actual(0), e(0), e_pre_1(0), e_pre_2(0), A(0), B(0), C(0){}
	double PID_control(double tar, double act){

	}
};
struct PID_increment PID(Kp, Ki, Kd);

/*===========================import variable===========================*/

// Write the voltage to motor.
void motorWrite(double vL, double vR) {
  // TODO: use TB6612 to control motor voltage & direction
  if(vL > 0){
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
  } else{
    digitalWrite(AIN2, HIGH);
    digitalWrite(AIN1, LOW);
    vL = -vL;
  }

  if(vR > 0){
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
  } else{
    digitalWrite(BIN2, HIGH);
    digitalWrite(BIN1, LOW);
    vR = -vR;
  }

  analogWrite(PWMA, vL * 0.95);
  analogWrite(PWMB, vR);
}// MotorWriting

void tracking(){    
  motorWrite(150, 150);
  if(digitalRead(analogPins[1]))motorWrite(150, 180);
  if(digitalRead(analogPins[3]))motorWrite(180, 150);
  if(digitalRead(analogPins[0]))motorWrite(0, 150);
  if(digitalRead(analogPins[4]))motorWrite(150, 0);
}

//temp ignore
// Handle negative motor_PWMR value. 
void MotorInverter(int motor, bool& dir) {
  //Hint: the value of motor_PWMR must between 0~255, cannot write negative value.
}// MotorInverter

// P/PID control Tracking
/*
void tracking(int l2, int l1, int m0, int r1, int r2){
  // find your own parameters!
  double _w0 = 0; //
  double _w1 = 1; // 
  double _w2 = 5; //
  double _Kp; // p term parameter 
  double _Kd; // d term parameter (optional) 
  double _Ki; // i term parameter (optional) (Hint: 不要調太大)
  double error=l2*_w2+l1*_w1+m0*_w0+r1*(-_w1)+r2*(-_w2);
  double vR, vL; // 馬達左右轉速原始值(從PID control 計算出來)。Between -255 to 255.
  double adj_R=1, adj_L=1; // 馬達轉速修正係數。MotorWriting(_Tp,_Tp)如果歪掉就要用參數修正。
    
  // TODO: complete your P/PID tracking code
  double powercorrection = PID.PID_control(0, error);

	if(vR + powercorrection > 255)vR = 255;
	else if (vR + powercorrection > 255 < -255)vR = -255;
	else vR += powercorrection

	if(vL + powercorrection > 255)vL = 255;
	else if (vL + powercorrection > 255 < -255)vL = -255;
	else vL += powercorrection

  // end TODO
  MotorWriting(adj_L*vL, adj_R*vR);
  
}// tracking
*/
#endif