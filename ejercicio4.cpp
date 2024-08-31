#define VALOR_MIN 0   
#define VALOR_MAX 100 

int contador = VALOR_MIN;
unsigned long tiempoAnterior = 0;
const unsigned long INTERVALO = 500; 

void setup() {
  Serial.begin(9600); 
}

void loop() {
  unsigned long tiempoActual = millis(); 
 
  if (tiempoActual - tiempoAnterior >= INTERVALO) {
    tiempoAnterior = tiempoActual;

    Serial.println(contador);

    contador++;

    if (contador > VALOR_MAX) {
      contador = VALOR_MIN;
    }
  }
}
