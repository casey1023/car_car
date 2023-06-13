int dirpin = 11;
int steppin = 12;
const int stepsPerRevolution = 2000;
int stepperdelay = 10000;
int liftdelay = 100;
void lift();
void down();
void lift()
{
    //clockwise
    digitalWrite(dirPin, HIGH);
    
	digitalWrite(stepPin, HIGH);
    delay(liftdelay);
	digitalWrite(stepPin, LOW);
}
void down()
{
    //counter-clockwise
    digitalWrite(dirPin, LOW);

	digitalWrite(stepPin, HIGH);
	delayMicroseconds(stepperdelay);
	digitalWrite(stepPin, LOW);
	delayMicroseconds(stepperdelay);
    delay(liftdelay);
}