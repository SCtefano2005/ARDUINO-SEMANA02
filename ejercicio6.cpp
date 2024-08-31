#define INTERVALO 500
unsigned long tiempoAnterior = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  unsigned long tiempoActual = millis();
  
  if (tiempoActual - tiempoAnterior >= INTERVALO) {
    tiempoAnterior = tiempoActual;
    
    for (int i = 5; i <= 15; i++) {
      Serial.println(i);
      delay(INTERVALO);
    }
  }
}
