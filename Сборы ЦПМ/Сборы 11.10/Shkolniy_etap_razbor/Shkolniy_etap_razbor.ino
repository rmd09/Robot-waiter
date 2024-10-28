#define base_led 6
#define pot A1
#define btn1 3
#define btn2 2

void init_led() {
  for (int i = 0; i < 6; i++) {
    pinMode(base_led + i, OUTPUT);
  }
}

void test_led() {
  for (int i = 0; i < 6; i++) {
    digitalWrite(base_led + i, HIGH);
    delay(500);
  }
  for (int i = 0; i < 6; i++) {
    digitalWrite(base_led + i, LOW);
  }
}
void led_off() {
  for (int i = 0; i < 6; i++) {
    digitalWrite(base_led + i, LOW);
  }
}

void setup() {
  init_led();
  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);
  pinMode(pot, INPUT);

  Serial.begin(9600);

  test_led();

}

int read_pot() {
  int sum = 0;
  for (int i = 0; i < 10; i++) {
    sum += analogRead(pot);
  }
  return floor(sum/10/16);
}

void display_number_led(int number) {
  for (int i = 0; i < 6; i++) {
    digitalWrite(base_led + i, number%2==0 ? LOW : HIGH);
    number = floor(number/2);
  }
}

bool isDisplay = false;
//false - read pot
//true - display number with leds
int temp_pot_value = read_pot();

void loop() {
  int pot = read_pot();
  bool but1 = !digitalRead(btn1);
  bool but2 = !digitalRead(btn2);
  
  if (!isDisplay) {
    if (temp_pot_value != pot) {
      Serial.flush();
      Serial.print("Current value: ");
      Serial.println(pot);
      temp_pot_value = pot;
    }

    if (but1) {
      display_number_led(pot);
      isDisplay = true;
    }

    if (but2) {
      test_led();
    }
  } else {
    if (pot != temp_pot_value) {
      isDisplay = false;
      led_off();
    }
  }
}
