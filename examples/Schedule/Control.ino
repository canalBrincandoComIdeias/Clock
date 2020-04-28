// IMPLEMENTO DE FUNÇÔES

void acionaRele(byte numDevice) {
  Serial.print("Acionado (");
  Serial.print(numDevice);
  Serial.println(")");
  digitalWrite(pinRele[numDevice], HIGH);
}

void desligaRele(byte numDevice) {
  Serial.println("Desligado (");
  Serial.print(numDevice);
  Serial.println(")");
  digitalWrite(pinRele[numDevice], LOW);
}
