const int pinVN = 39;  // X Axis pin
const int pinVP = 36;  // Y Axis pin
const int pinD2 = 2;   // Reverse gear pin

void setup() {
  Serial.begin(9600);
  pinMode(pinD2, INPUT);
}

void loop() {
  int yValue = analogRead(pinVN);
  int xValue = analogRead(pinVP);
  int reverseGear = digitalRead(pinD2);

  // X Axis values
  // 1a: below 1800
  // 2a: below 1800
  // 3a: between 2000 and 3800
  // 4a: between 2000 and 3800
  // 5a: above 4000
  // 6a: above 4000

  // Y Axis values
  // 1a: above 3500
  // 2a: below 1000
  // 3a: above 3500
  // 4a: below 1000
  // 5a: above 3500
  // 6a: below 1000

  String selectedGear;
  if (reverseGear == 1 && xValue > 4000 && yValue < 1000) {
    selectedGear = "R";
  } else if (xValue < 2000 && yValue > 3500) {
    selectedGear = "1";
  } else if (xValue < 2000 && yValue < 1000) {
    selectedGear = "2";
  } else if (xValue > 2100 && xValue < 3800 && yValue > 3500) {
    selectedGear = "3";
  } else if (xValue > 2100 && xValue < 3800 && yValue < 1000) {
    selectedGear = "4";
  } else if (xValue > 4000 && yValue > 3500) {
    selectedGear = "5";
  } else if (xValue > 4000 && yValue < 1000) {
    selectedGear = "6";
  } else if (yValue > 1000 && yValue < 3500) {
    selectedGear = "N";
  } else {
    selectedGear = "Desconeguda";
  }

  Serial.print("Axis Y: ");
  Serial.print(yValue);
  Serial.print("\tAxis X: ");
  Serial.print(xValue);
  Serial.print("\tReverse gear: ");
  Serial.print(reverseGear);
  Serial.print("\tGear: ");
  Serial.println(selectedGear);

  delay(50); // Update values every 50ms
}