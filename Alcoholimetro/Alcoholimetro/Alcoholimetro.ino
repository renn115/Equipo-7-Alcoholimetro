// Alcoholímetro Digital con Arduino - Equipo 7
// Controladores y Microcontroladores Programables

int alcohol = 0;

// Umbrales basados en alcoholemia real (g/L)
const int SOBRIO = 95;        // 0.00-0.07 g/L
const int LIMITE_LEGAL = 122; // 0.25 g/L (límite legal México)
const int MEDIO = 158;        // 0.50 g/L
const int ALTO = 195;         // 0.75 g/L

void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);    // Sensor MQ-3 conectado a A0
  pinMode(3, OUTPUT);    // LED rojo
  pinMode(2, OUTPUT);    // LED verde
  pinMode(4, OUTPUT);    // Buzzer
  
  Serial.println("========================================");
  Serial.println("  ALCOHOLIMETRO DIGITAL - INICIANDO");
  Serial.println("========================================");
  Serial.println();
  delay(2000);
}

void loop() {
  alcohol = analogRead(A0);
  
  // Calcular alcoholemia aproximada en g/L
  float alcoholemia = (alcohol - 85) / 293.0 * 2.0;
  if (alcoholemia < 0) alcoholemia = 0;
  
  // Mostrar valores
  Serial.print("Sensor: ");
  Serial.print(alcohol);
  Serial.print(" | Alcoholemia: ");
  Serial.print(alcoholemia, 2);
  Serial.print(" g/L | ");
  
  // Determinar estado y acción según rango
  if (alcohol < SOBRIO) {
    // RANGO 1: SOBRIO (85-94)
    Serial.print("Estado: SOBRIO ");
    Serial.println("| SEGURO CONDUCIR");
    
    digitalWrite(3, LOW);   // LED rojo apagado
    digitalWrite(2, HIGH);  // LED verde encendido
    digitalWrite(4, LOW);   // Buzzer apagado
  }
  else if (alcohol >= SOBRIO && alcohol <= LIMITE_LEGAL) {
    // RANGO 2: BAJO (95-122)
    Serial.print("Estado: NIVEL BAJO ");
    Serial.println("| CERCA DEL LIMITE");
    
    digitalWrite(3, LOW);   // LED rojo apagado
    digitalWrite(2, HIGH);  // LED verde encendido
    digitalWrite(4, LOW);   // Buzzer apagado
  }
  else if (alcohol > LIMITE_LEGAL && alcohol <= MEDIO) {
    // RANGO 3: MEDIO (123-158)
    Serial.print("Estado: NIVEL MEDIO ");
    Serial.println("| NO CONDUCIR");
    
    digitalWrite(3, HIGH);  // LED rojo encendido
    digitalWrite(2, LOW);   // LED verde apagado
    digitalWrite(4, HIGH);  // Buzzer encendido
    delay(500);
    digitalWrite(4, LOW);   // Buzzer apagado
    delay(500);
  }
  else if (alcohol > MEDIO && alcohol <= ALTO) {
    // RANGO 4: ALTO (159-195)
    Serial.print("Estado: NIVEL ALTO ");
    Serial.println("| PELIGROSO");
    
    digitalWrite(3, HIGH);  // LED rojo encendido
    digitalWrite(2, LOW);   // LED verde apagado
    digitalWrite(4, HIGH);  // Buzzer encendido
    delay(800);
    digitalWrite(4, LOW);   // Buzzer apagado
    delay(800);
  }
  else {
    // RANGO 5: MUY ALTO (>195)
    Serial.print("Estado: NIVEL MUY ALTO ");
    Serial.println("| INTOXICACION SEVERA ");
    
    digitalWrite(3, HIGH);  // LED rojo encendido
    digitalWrite(2, LOW);   // LED verde apagado
    digitalWrite(4, HIGH);  // Buzzer encendido
    delay(1000);
    digitalWrite(4, LOW);   // Buzzer apagado
    delay(1000);
  }
  
  Serial.println("----------------------------------------");
  delay(500);
}