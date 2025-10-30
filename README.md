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

**- Módulo de entrada (Sensor):**

Compuesto por el sensor de gas MQ-3 y una resistencia de carga de 1kΩ. El sensor detecta vapores de etanol en el aire y genera una señal analógica proporcional a la concentración. Esta señal es enviada al pin A0 del Arduino, donde es convertida a valores digitales de 0 a 1023 mediante el conversor analógico-digital de 10 bits.

**- Módulo de procesamiento (Arduino UNO):**

Es el cerebro del sistema. Recibe las lecturas del sensor, analiza la información y decide las acciones que debe realizar. A partir de la lógica del programa, el Arduino compara el valor leído con el umbral de seguridad (232). Si el valor es mayor, activa el estado de peligro; si es menor o igual, mantiene el estado seguro. Este procesamiento ocurre continuamente en el loop principal.

**- Módulo de salida (Actuadores):**

Incluye dos LEDs (verde y rojo) que proporcionan retroalimentación visual del estado, un buzzer que emite alarma sonora intermitente en caso de peligro, y comunicación serial USB para monitoreo en tiempo real. Los LEDs están conectados a los pines digitales 2 y 3 con resistencias limitadoras de 220Ω. El buzzer está conectado al pin 4 y se activa con un patrón de 1 segundo encendido y 1 segundo apagado.

**- Flujo de funcionamiento:**

El sensor MQ-3 detecta concentración de alcohol → Arduino lee el valor analógico y lo convierte a digital → compara con el umbral (232) → activa LED verde si es seguro o LED rojo + buzzer si es peligroso → envía valores por serial para monitoreo → repite el ciclo continuamente.

### 🔄 Comunicación entre módulos

**Sensor MQ-3 → Arduino:**
- Pin A0 (entrada analógica)
- Señal: 0-1023 (conversión ADC)
- `analogRead(A0)`

**Arduino → LED Verde:**
- Pin 2 (salida digital)
- Señal: HIGH/LOW
- Activo cuando `alcohol ≤ 232`

**Arduino → LED Rojo:**
- Pin 3 (salida digital)
- Señal: HIGH/LOW
- Activo cuando `alcohol > 232`

**Arduino → Buzzer:**
- Pin 4 (salida digital)
- Señal: Intermitente 1s ON/OFF
- Activo cuando `alcohol > 232`

**Arduino → PC:**
- Puerto USB
- UART 9600 baudios
- `Serial.println(alcohol)`

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

**1. ¿Qué pasa si el LED verde no se enciende al inicio?**  
Espera entre **20 y 30 segundos** para que el sensor MQ-3 se caliente completamente. Durante este proceso es normal que los valores del sensor sean inestables o varíen rápidamente.

**2. El buzzer no suena.**  
Verifica la **polaridad de conexión**: el pin positivo (+) debe ir al **pin 4** del Arduino y el negativo (–) a **GND**. Si sigue sin funcionar, prueba el buzzer con el siguiente código de prueba, ya que algunos modelos requieren señal **PWM**: **analogWrite(4, 128);**
  
**2. El buzzer no suena.**
Verifica la polaridad (+ al pin 4, - a GND) y prueba con código de test individual. Algunos buzzers necesitan señal PWM: usa **analogWrite(4, 128)**.

**3. Los valores del sensor siempre son 0 o 1023.**
Asegúrate de que la resistencia de 1 kΩ esté correctamente conectada entre AOUT y GND. Verifica también con un multímetro que haya 5V entre los pines VCC y GND del módulo sensor.

**4. ¿Puedo ajustar la sensibilidad?**
Sí. Modifica el valor del umbral en la línea **if (alcohol > 145)** del código. Valores más bajos aumentan sensibilidad, valores más altos la reducen.

**5. ¿Funciona para medir alcohol en aliento real?**
El sensor MQ-3 puede detectar alcohol en aliento, pero este es un prototipo educativo. Para uso real en seguridad vial se requieren alcoholímetros certificados y calibrados profesionalmente.

---
