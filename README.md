# 🍸 Alcoholímetro Digital con Arduino

Simulador de alcoholímetro que detecta concentración de alcohol en el aire mediante sensor MQ-3 y proporciona retroalimentación visual y sonora para prevenir conducción bajo efectos del alcohol.

## 📘 Descripción del proyecto

El **Alcoholímetro Digital** es un prototipo que detecta la concentración de vapores de alcohol en el aire y proporciona alertas inmediatas mediante indicadores visuales y sonoros. 

Este proyecto lee continuamente las concentraciones de alcohol del ambiente, compara los valores con un umbral de seguridad predefinido, y activa un LED verde cuando es seguro o un LED rojo con alarma sonora cuando detecta niveles peligrosos.

### // Problema que resuelve

La conducción bajo los efectos del alcohol es una de las principales causas de accidentes de tránsito mortales. Este alcoholímetro ofrece una herramienta accesible para verificar niveles de alcohol antes de conducir, promoviendo decisiones responsables y previniendo accidentes.

## ⚙️ Requisitos e instalación

### 🧩 Hardware necesario

- 1 × Arduino UNO (ATmega328P)
- 1 × Sensor de gas MQ-3 (detector de alcohol)
- 1 × LED verde (5mm)
- 1 × LED rojo (5mm)
- 1 × Buzzer piezoeléctrico (5V)
- 2 × Resistencias 330Ω (para LEDs)
- 1 × Resistencia 1kΩ (para sensor)
- 1 × Protoboard (400 puntos)
- Cables jumper macho-macho
- Cable USB tipo A a tipo B


### 💻 Software necesario

- Arduino IDE (versión 1.8.13 o superior)
- Drivers CH340 (solo si tu Arduino es clon)
- Cable USB para subir el código

### 🔧 Instalación

**1. Descarga o clona este repositorio:**
```bash
git clone https://github.com/renn115/Equipo-7-Alcoholimetro.git
```

**2. Abre el archivo `Alcoholimetro.ino` en el Arduino IDE.**

**3. Selecciona tu placa y puerto:**
- Placa: Arduino UNO
- Puerto: COMx (Windows) o /dev/ttyUSBx (Linux/Mac)

**4. Carga el código en el Arduino con el botón Subir (Upload).**

**5. Conecta los componentes según el diagrama de pines:**

| Componente | Pin Arduino | Observaciones |
|------------|-------------|---------------|
| Sensor MQ-3 VCC | 5V | Alimentación |
| Sensor MQ-3 GND | GND | Tierra |
| Sensor MQ-3 AOUT | A0 | A través de resistencia 1kΩ |
| LED Verde (+) | Pin 2 | Con resistencia 220Ω |
| LED Rojo (+) | Pin 3 | Con resistencia 220Ω |
| Buzzer (+) | Pin 4 | Directo |
| Todos los (-) | GND | Tierra común |

## ▶️ Cómo usarlo

1. Conecta el Arduino a una fuente USB
2. Espera 20-30 segundos para que el sensor MQ-3 se caliente
3. Sopla cerca del sensor o acerca alcohol isopropílico
4. Observa la respuesta del sistema:
   - **LED Verde encendido**: Nivel seguro (≤ 232)
   - **LED Rojo + Alarma intermitente**: Nivel peligroso (> 232)
5. Puedes ver los valores en tiempo real abriendo el **Monitor Serial** (9600 baudios)

### 🧠 Comportamientos principales

| Estado | Condición | Rango (g/L) | Indicadores |
|--------|-----------|-------------| -------------|
| SOBRIO | alcohol < 95 | 0.00-0.07 | 0.00-0.07 | LED Verde ON, LED Rojo OFF, Buzzer OFF |
| NIVEL BAJO | 95 ≤ alcohol ≤ 122 | 0.08-0.25 | 0.00-0.07 | LED Verde ON, LED Rojo OFF, Buzzer OFF |
| NIVEL MEDIO | 122 < alcohol ≤ 158 | 0.26-0.50 | 0.00-0.07 | LED Verde OFF, LED Rojo ON, Buzzer intermitente (500ms) |
| NIVEL ALTO | 158 < alcohol ≤ 195 | 0.51-0.75 | 0.00-0.07 | LED Verde OFF, LED Rojo ON, Buzzer intermitente (800ms) |
| NIVEL MUY ALTO | alcohol > 195 | 0.76-2.00 | 0.00-0.07 | LED Verde OFF, LED Rojo ON, Buzzer intermitente (1000ms) |

**Valores del sensor:**
- Mínimo: 95
- Umbral: 145 (punto medio de alerta)
- Máximo: 195


## 📁 Estructura del proyecto
```
│
├── README.md              # Descripción del proyecto
├── alcoholimetro.ino      # Código fuente principal
├── /diagramas             # Diagramas del sistema
│   ├── diagrama-esquematico.png
│   └── diagrama-pictorico.png
│   └── diagrama-bloques.png
```

## 🧩 Arquitectura del sistema

El sistema del Alcoholímetro está conformado por tres módulos principales: entrada, procesamiento y salida.

## Arquitectura del Sistema

El Alcoholímetro se compone de tres módulos principales: entrada, procesamiento y salida.

**- Módulo de entrada (Sensor):**  
Sensor MQ-3 con resistencia de 1kΩ. Detecta alcohol en el aire y envía señal analógica al pin A0 del Arduino (0-1023).

**- Módulo de procesamiento (Arduino UNO):**  
Recibe lecturas del sensor, compara con el umbral (145) y decide acciones: LED verde si seguro, LED rojo + buzzer si peligroso. Operación continua en el loop principal.

**- Módulo de salida (Actuadores):**  
- LEDs verde (pin 2) y rojo (pin 3) con resistencias de 220Ω.  
- Buzzer en pin 4 con patrón intermitente.  
- Comunicación serial para monitoreo en tiempo real.

**- Flujo de funcionamiento:**  
Sensor MQ-3 → Arduino lee valor analógico → convierte a digital → compara con umbral → activa LEDs y buzzer → envía datos por serial → repite.

### 🔄 Comunicación entre módulos

**Sensor MQ-3 → Arduino:**
- Pin A0 (entrada analógica)
- Señal: 0-1023 (conversión ADC)
- **analogRead(A0)**

**Arduino → LED Verde:**
- Pin 2 (salida digital)
- Señal: HIGH/LOW
- Activo cuando **alcohol ≤ 232**

**Arduino → LED Rojo:**
- Pin 3 (salida digital)
- Señal: HIGH/LOW
- Activo cuando **alcohol > 232**

**Arduino → Buzzer:**
- Pin 4 (salida digital)
- Señal: Intermitente 1s ON/OFF
- Activo cuando **alcohol > 232**

**Arduino → PC:**
- Puerto USB
- UART 9600 baudios
- **Serial.println(alcohol)**

## 🧠 Resumen técnico del sistema

- Control principal con Arduino UNO (ATmega328P)
- Sensor analógico MQ-3 mide concentración de alcohol
- LEDs controlados por pines digitales 2 y 3
- Buzzer controlado por pin digital 4
- Lógica de decisión basada en umbral (232)
- Comunicación serial a 9600 baudios para monitoreo
- Sistema de lectura continua en loop infinito

## 🪜 Guía paso a paso de instalación

1. **Instala Arduino IDE** desde https://www.arduino.cc/en/software
2. **Conecta el sensor MQ-3** al pin A0 con resistencia de 1kΩ a GND
3. **Conecta el LED verde** al pin 2 con resistencia de 330Ω
4. **Conecta el LED rojo** al pin 3 con resistencia de 330Ω
5. **Conecta el buzzer** al pin 4
6. **Conecta todos los GND** a tierra común del Arduino
7. **Conecta VCC del sensor** a 5V del Arduino
8. **Sube el programa** al Arduino desde el IDE
9. **Alimenta el sistema** con USB (5V)
10. **Espera 30 segundos** para precalentamiento del sensor
11. **Observa el comportamiento** en el monitor serial (opcional)

## ## ❓ FAQ

**¿Qué pasa si el LED verde no se enciende al inicio?**  
Espera 20-30 segundos para que el sensor MQ-3 se caliente; es normal que los valores sean inestables al inicio.

**¿Por qué el buzzer no suena?**
Verifica la polaridad (+ al pin 4, – a GND). Algunos buzzer requieren señal PWM: **analogWrite(4, 128);**.

**¿Por qué los valores del sensor siempre son 0 o 1023?**  
Asegúrate de que la resistencia de 1 kΩ esté conectada entre AOUT y GND, y que haya 5V entre VCC y GND.

**¿Puedo ajustar la sensibilidad?**  
Sí. Modifica el umbral en el código `if (alcohol > 145)`; valores menores aumentan la sensibilidad, valores mayores la reducen.

**¿Funciona para medir alcohol en aliento real?**  
MQ-3 puede detectar alcohol, pero este proyecto es educativo. Para uso real se requieren alcoholímetros certificados.

---
