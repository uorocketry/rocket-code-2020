char nbr = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.write(nbr++);
  delay(200);
}
