#define lights 10
int LDR1, LDR2, LDR3;

int leftOffset = 0, rightOffset = 0, centre = 0;
int speed1 = 3, speed2 = 11, direction1 = 12, direction2 = 13;
int brake1 = 8, brake2 = 9;
int startSpeed = 70, rotate = 30;
int threshhold = 5;
int left = startSpeed, right = startSpeed;

void calibrate()
{
  for (int x = 0; x < 10; x++)
  {
    digitalWrite(lights, HIGH);
    delay(100);
    LDR1 = analogRead(0);
    LDR2 = analogRead(1);
    LDR3 = analogRead(2);
    leftOffset = leftOffset + LDR1;
    centre = centre + LDR2;
    rightOffset = rightOffset + LDR3;
    
    delay(100);
    digitalWrite(lights, LOW);
    delay(100);
  }
  
  leftOffset = leftOffset / 10;
  rightOffset = rightOffset / 10;
  centre = centre / 10;
  
  leftOffset = centre - leftOffset;
  rightOffset = centre - rightOffset;
}

void setup()
{
  pinMode(lights, OUTPUT);
  pinMode(speed1, OUTPUT);
  pinMode(speed2, OUTPUT);
  pinMode(direction1, OUTPUT);
  pinMode(direction2, OUTPUT);
  pinMode(brake1, OUTPUT);
  pinMode(brake2, OUTPUT);
  
  calibrate();
  delay(3000);
  
  digitalWrite(lights, HIGH);
  delay(100);
  
  digitalWrite(direction1, HIGH);
  digitalWrite(direction2, HIGH);
  
  digitalWrite(brake1, LOW);
  digitalWrite(brake2, LOW);
  
  analogWrite(speed1, left);
  analogWrite(speed2, right);
}

void loop()
{
  left = startSpeed;
  right = startSpeed;
  
  LDR1 = analogRead(0) + leftOffset;
  LDR2 = analogRead(1);
  LDR3 = analogRead(2) + rightOffset;
  
  if (LDR1 > (LDR2 + threshhold))
  {
    left = startSpeed + rotate;
    right = startSpeed - rotate;
  }
  
  if (LDR3 > (LDR2 + threshhold))
  {
    left = startSpeed - rotate;
    right = startSpeed + rotate;
  }
  
  analogWrite(speed1, left);
  analogWrite(speed2, right);
}
