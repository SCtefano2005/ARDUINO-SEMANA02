
// Ascensor A
const int ledPinsA[6] = {2, 3, 4, 5, 6, 7};
int currentFloorA = 1;

// Ascensor B
const int ledPinsB[6] = {8, 9, 10, 11, 12, 13};
int currentFloorB = 6;

int assignedElevator = 0; // Variable para almacenar el ascensor asignado

void setup() {
  // Inicializar los pines de los LEDs como salidas para ambos ascensores
  for(int i = 0; i < 6; i++) {
    pinMode(ledPinsA[i], OUTPUT);
    pinMode(ledPinsB[i], OUTPUT);
  }

  // Inicializar la comunicación serial
  Serial.begin(9600);

  // Encender los LEDs de los pisos iniciales
  digitalWrite(ledPinsA[currentFloorA - 1], HIGH);
  digitalWrite(ledPinsB[currentFloorB - 1], HIGH);
}

void loop() {
  // Preguntar al usuario en qué piso se encuentra
  Serial.println("Ingrese el piso en el que se encuentra (1-6):");
  while (Serial.available() == 0) {} // Esperar por la entrada del usuario
  int userFloor = Serial.parseInt();

  if (userFloor >= 1 && userFloor <= 6) {
    assignedElevator = selectElevator(userFloor); // Asignar el ascensor más cercano
    
    if (assignedElevator == 1) {
      Serial.print("Ascensor A asignado. Moviendo al piso ");
      Serial.println(userFloor);
      moveElevatorA(userFloor);
    } else {
      Serial.print("Ascensor B asignado. Moviendo al piso ");
      Serial.println(userFloor);
      moveElevatorB(userFloor);
    }
    
    // Preguntar el piso destino
    Serial.println("Ingrese el piso destino (1-6):");
    while (assignedElevator != 0) { // Esperar por la entrada del usuario
    while (Serial.available() == 0){}
      int finalDestination = Serial.parseInt();


      if (finalDestination >= 1 && finalDestination <= 6) {
        if (assignedElevator == 1) {
          moveElevatorA(finalDestination);
          assignedElevator = 0;
        } else {
          moveElevatorB(finalDestination);
          assignedElevator = 0;
        }
      } else {
        Serial.println("Piso invalido. Por favor ingrese un numero entre 1 y 6.");
      }
    }

    // Restablecer el ascensor asignado después de completar el viaje

  } else {
    Serial.println("Piso invalido. Por favor ingrese un numero entre 1 y 6.");
  }

  // Volver a iniciar el proceso para un nuevo viaje
}

int selectElevator(int targetFloor) {
  int distanceA = abs(targetFloor - currentFloorA);
  int distanceB = abs(targetFloor - currentFloorB);

  if (distanceA < distanceB) {
    return 1; // Ascensor A es el más cercano
  } else if (distanceB < distanceA) {
    return 2; // Ascensor B es el más cercano
  } else {
    return random(1, 3); // Si están a la misma distancia, seleccionar cualquiera de los dos al azar
  }
}

void moveElevatorA(int targetFloor) {
  if (currentFloorA == targetFloor) return; // No hacer nada si ya está en el piso
  digitalWrite(ledPinsA[currentFloorA - 1], LOW);
  
  while (currentFloorA != targetFloor) {
    if (currentFloorA < targetFloor) {
      currentFloorA++;
      if (currentFloorA > 1) digitalWrite(ledPinsA[currentFloorA - 2], LOW);
    } else {
      currentFloorA--;
      if (currentFloorA < 6) digitalWrite(ledPinsA[currentFloorA], LOW);
    }
    digitalWrite(ledPinsA[currentFloorA - 1], HIGH);
    delay(1000);
  }
}

void moveElevatorB(int targetFloor) {
  if (currentFloorB == targetFloor) return; // No hacer nada si ya está en el piso
  digitalWrite(ledPinsB[currentFloorB - 1], LOW);
  
  while (currentFloorB != targetFloor) {
    if (currentFloorB < targetFloor) {
      currentFloorB++;
      if (currentFloorB > 1) digitalWrite(ledPinsB[currentFloorB - 2], LOW);
    } else {
      currentFloorB--;
      if (currentFloorB < 6 && currentFloorB >= 1) digitalWrite(ledPinsB[currentFloorB], LOW);
    }
    digitalWrite(ledPinsB[currentFloorB - 1], HIGH);
    delay(1000);
  }
}
