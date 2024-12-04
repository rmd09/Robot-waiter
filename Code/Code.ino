#define dW digitalWrite
#define dR digitalRead


//Пины
//in - input на драйвере l293d
//en - enable
#define in1 13
#define in2 12
#define in3 11
#define in4 10
#define en1 5
#define en2 6

#define debug_btn 7 //Кнопка на макетке для отладки

void init_motors()
{
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}
void init_debug_components() 
{
  pinMode(debug_btn, INPUT_PULLUP);
}

///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////

void setup() 
{
  delay(2000);
  init_motors();
  init_debug_components();


}

///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
/***************************CONST*****************************/
const int B_max = 255;
const int A_max = 225;
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////

void B_on(int en_value = B_max, bool isStraight = true)
{
  digitalWrite(in1, isStraight ? HIGH : LOW);
  digitalWrite(in2, isStraight ? LOW : HIGH);
  analogWrite(en1, en_value);
}
void B_off()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(en1, LOW);
}
void A_on(int en_value = A_max, bool isStraight = true)
{
  digitalWrite(in3, isStraight ? LOW : HIGH);
  digitalWrite(in4, isStraight ? HIGH : LOW);
  analogWrite(en2, en_value);
}
void A_off()
{
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  digitalWrite(en2, LOW);
}
void Start(int t)
{
  for (int i = B_max/3, j = A_max/3; i < B_max; i++, j++)
  {
    delay(t/(A_max/3));
    A_on(j);
    B_on(i);
  }
}

void test_program()
{
  Start(5000);
  delay(2000);
  A_off();
  B_off();
}

///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////

void loop() 
{

  bool but = !digitalRead(debug_btn);
  if (but) 
  {
    delay(200);
    test_program();
  }
}
