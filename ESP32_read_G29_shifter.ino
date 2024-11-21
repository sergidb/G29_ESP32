const int pinVN = 39;  // Pin de connexió per l'eix Y
const int pinVP = 36;  // Pin de connexió per l'eix X
const int pinD2 = 2;   // Pin de connexió per la senyal digital de marxa enrere

void setup() {
  Serial.begin(9600);
  pinMode(pinD2, INPUT);
}

void loop() {
  int valorY = analogRead(pinVN);
  int valorX = analogRead(pinVP);
  int marxaEnrere = digitalRead(pinD2);

  // Valors X
  // 1a: per sota de 1800
  // 2a: per sota de 1800
  // 3a: de 2000 a 3800
  // 4a: de 2000 a 3800
  // 5a: per sobre de 4000
  // 6a: per sobre de 4000

  // Valors Y
  // 1a: per sobre de 3500
  // 2a: per sota de 1000
  // 3a: per sobre de 3500
  // 4a: per sota de 1000
  // 5a: per sobre de 3500
  // 6a: per sota de 1000

  String marxaSeleccionada;
  if (marxaEnrere == 1 && valorX > 4000 && valorY < 1000) {
    marxaSeleccionada = "R";
  } else if (valorX < 2000 && valorY > 3500) {
    marxaSeleccionada = "1a";
  } else if (valorX < 2000 && valorY < 1000) {
    marxaSeleccionada = "2a";
  } else if (valorX > 2100 && valorX < 3800 && valorY > 3500) {
    marxaSeleccionada = "3a";
  } else if (valorX > 2100 && valorX < 3800 && valorY < 1000) {
    marxaSeleccionada = "4a";
  } else if (valorX > 4000 && valorY > 3500) {
    marxaSeleccionada = "5a";
  } else if (valorX > 4000 && valorY < 1000) {
    marxaSeleccionada = "6a";
  } else if (valorY > 1000 && valorY < 3500) {
    marxaSeleccionada = "N";
  } else {
    marxaSeleccionada = "Desconeguda";
  }

  Serial.print("Eix Y: ");
  Serial.print(valorY);
  Serial.print("\tEix X: ");
  Serial.print(valorX);
  Serial.print("\tMarxa enrere: ");
  Serial.print(marxaEnrere);
  Serial.print("\tMarxa: ");
  Serial.println(marxaSeleccionada);

  delay(50); // Actualitza els valors cada 50ms
}