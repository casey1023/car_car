int CIN1 = 8;
int CIN2 = 9;
int PWMC = 10;
int clipdelay = 700;
void clip(bool decide)//0夾1鬆開
{
    if(!decide)
    {
        motorWrite(150, 150);
        delay(clipdelay);
    }
    else if(decide)
    {
        motorWrite(-150, -150);
        delay(clipdelay);
    }
    motorWrite(0, 0);
}   
