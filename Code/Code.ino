#define RH_MOTOR_A 11
#define RH_MOTOR_B 10
#define LH_MOTOR_A 6
#define LH_MOTOR_B 5

#define trig1 12
#define echo1 13

const double CONSTANT_FOR_CONVERTING_TO_SM = 0.01715;

int hc1_value;

int read_hc(int trig, int echo)
{
  digitalWrite(trig, LOW);
  delayMicroseconds(2);

  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  int duration = pulseIn(echo, HIGH);
  
  return (duration * CONSTANT_FOR_CONVERTING_TO_SM);
}

void setup()
{
  pinMode(RH_MOTOR_A, OUTPUT);
  pinMode(RH_MOTOR_B, OUTPUT);
  pinMode(LH_MOTOR_A, OUTPUT);
  pinMode(LH_MOTOR_B, OUTPUT);
  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT);

  Serial.begin(9600);
}

//true - вперед, false - назад
void rh_motor(int speed, bool direction = true)
{
  if (direction)
  {
    analogWrite(RH_MOTOR_A, speed);
    analogWrite(RH_MOTOR_B, LOW);
  }
  else 
  {
    analogWrite(RH_MOTOR_A, LOW);
    analogWrite(RH_MOTOR_B, speed);
  }
  
}
void rh_off()
{
  analogWrite(RH_MOTOR_A, LOW);
  analogWrite(RH_MOTOR_B, LOW);
}

void lh_motor(int speed, bool direction = true)
{
  if (direction)
  {
    analogWrite(LH_MOTOR_A, speed);
    analogWrite(LH_MOTOR_B, LOW);
  }
  else 
  {
    analogWrite(LH_MOTOR_A, LOW);
    analogWrite(LH_MOTOR_B, speed);
  }
  
}
void lh_off()
{
  analogWrite(LH_MOTOR_A, LOW);
  analogWrite(LH_MOTOR_B, LOW);
}

void loop()
{
  rh_motor(255);
  lh_motor(255);
  hc1_value = read_hc(trig1, echo1);

  Serial.println(hc1_value);

  //delay(2);
}