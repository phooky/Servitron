#define PWM_PIN 4
#define ENA_PIN 5
#define ENB_PIN 6
#define INA_PIN 7
#define INB_PIN 8


void setup() {
  pinMode(PWM_PIN, OUTPUT);
  digitalWrite(PWM_PIN, LOW);
  pinMode(INA_PIN, OUTPUT);
  digitalWrite(INA_PIN, LOW);
  pinMode(INB_PIN, OUTPUT);
  digitalWrite(INB_PIN, LOW);
}

void brake() {
  digitalWrite(INA_PIN,LOW);
  digitalWrite(INB_PIN,LOW);
}

void forward() {
  digitalWrite(INA_PIN,LOW);
  digitalWrite(INB_PIN,HIGH);
}

void backward() {
  digitalWrite(INA_PIN,HIGH);
  digitalWrite(INB_PIN,LOW);
}

void setSpeed(int spd) {
 analogWrite(PWM_PIN,spd);
}

void loop() {
  setSpeed(0);
  forward();
  setSpeed(150);
  delay(500);
  brake();
  delay(500);
  backward();
  delay(500);
  brake();
  delay(500);
}
