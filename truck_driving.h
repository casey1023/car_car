//車子兩顆輪子馬達腳位
int AIN1 = 2;
int AIN2 = 3;
int BIN1 = 4;
int BIN2 = 5;
int PWMA = 6;
int PWMB = 7;
void motorWrite(int vL, int vR)
{
  if(vL > 0)
  {
    digitalWrite(AIN1, HIGH);
    digitalWrite(AIN2, LOW);
  }
  else
  {
    digitalWrite(AIN2, HIGH);
    digitalWrite(AIN1, LOW);
    vL = -vL;
  }
  if(vR > 0)
  {
    digitalWrite(BIN1, HIGH);
    digitalWrite(BIN2, LOW);
  }
  else
  {
    digitalWrite(BIN2, HIGH);
    digitalWrite(BIN1, LOW);
    vR = -vR;
  }

  analogWrite(PWMA, vL );
  analogWrite(PWMB, vR);

}