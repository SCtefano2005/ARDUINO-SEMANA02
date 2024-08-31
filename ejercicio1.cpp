int numero1;
int numero2;

void setup() {
  Serial.begin(9600);
}

void loop() {
  Serial.println("Ingrese el primer numero (numero1):");
  numero1 = leerEnteroDesdeSerial();
  Serial.print("Numero 1 ingresado: ");
  Serial.println(numero1);
  
  Serial.println("Ingrese el segundo numero (numero2):");
  numero2 = leerEnteroDesdeSerial();
  Serial.print("Numero 2 ingresado: ");
  Serial.println(numero2);
  
  int suma = numero1 + numero2;
  int resta = numero1 - numero2;
  int multiplicacion = numero1 * numero2;
  int division = 0;

  if (numero2 != 0) {
    division = numero1 / numero2;
  } else {
    Serial.println("Error: División por cero.");
  }

  Serial.print("Suma: ");
  Serial.println(suma);
  
  Serial.print("Resta: ");
  Serial.println(resta);
  
  Serial.print("Multiplicacion: ");
  Serial.println(multiplicacion);
  
  if (numero2 != 0) {
    Serial.print("Division: ");
    Serial.println(division);
  }
}

int leerEnteroDesdeSerial() {
  while (Serial.available() == 0) {
    ; 
  }
  String input = Serial.readStringUntil('\n'); 
  return input.toInt(); 
}
