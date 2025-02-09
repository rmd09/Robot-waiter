#define RH_MOTOR_A 5
#define RH_MOTOR_B 4
#define LH_MOTOR_A 7
#define LH_MOTOR_B 6

#define svet1 A15
#define svet2 A14

#define button 52

const int SPEED = 100;
const int Kp = 0.4;
const int Kd = 4;

int last_er = 0;
int sv1 = 0;
int sv2 = 0;
int white = 35;
int black = 150;

void setup()
{
  pinMode(RH_MOTOR_A, OUTPUT);
  pinMode(RH_MOTOR_B, OUTPUT);
  pinMode(LH_MOTOR_A, OUTPUT);
  pinMode(LH_MOTOR_B, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  pinMode(svet1, INPUT);
  pinMode(svet2, INPUT);


  Serial.begin(9600);

  correct();
}

void drive(int lh, int rh)
{
  if (lh < 0)
  {
    analogWrite(LH_MOTOR_B, abs(lh));
    digitalWrite(LH_MOTOR_A, LOW);
  }
  else if (lh > 0)
  {
    analogWrite(LH_MOTOR_A, abs(lh));
    digitalWrite(LH_MOTOR_B, LOW);    
  }
  else
  {
    digitalWrite(LH_MOTOR_A, LOW);
    digitalWrite(LH_MOTOR_B, LOW);
  }

  if (rh < 0)
  {
    analogWrite(RH_MOTOR_B, abs(rh));
    digitalWrite(RH_MOTOR_A, LOW);
  }
  else if (rh > 0)
  {
    analogWrite(RH_MOTOR_A, abs(rh));
    digitalWrite(RH_MOTOR_B, LOW);    
  }
  else
  {
    digitalWrite(RH_MOTOR_A, LOW);
    digitalWrite(RH_MOTOR_B, LOW);
  }
}

void read_svet()
{
  sv1 = map(analogRead(svet1), black, white, 0, 100);
  sv2 = map(analogRead(svet2), black, white, 0, 100);
}

int PD(int a, int b)
{
  int er = a - b;
  int res = Kp*er + Kd*(er-last_er);
  last_er = er;
  return res;
}

void go_lin()
{
  while (digitalRead(button))
  {
    read_svet();
    int dV = PD(sv1, sv2);
    drive(SPEED + dV, SPEED - dV);
  }
  drive(0, 0);
  delay(500);
}

void correct()
{
  while (digitalRead(button)) {}
  white = analogRead(svet1);
  delay(500);

  while (digitalRead(button)) {}

  black = analogRead(svet1);
  delay(200);
    
}

void loop()
{
  read_svet();

  if (!digitalRead(button))
  {
    delay(300);
    go_lin();
  }

  // Serial.print(sv1);
  // Serial.print("\t");
  // Serial.println(sv2);
}