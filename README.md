# Alcoholímetro Digital con Arduino

Simulador de alcoholímetro que detecta concentración de alcohol en el aire mediante sensor MQ-3 y proporciona retroalimentación visual y sonora para prevenir conducción bajo efectos del alcohol.

## Descripción

El Alcoholímetro Digital es un prototipo educativo diseñado para detectar la concentración de alcohol en el aire mediante un sensor de gas MQ-3. El sistema analiza los niveles detectados y proporciona retroalimentación visual y sonora según el grado de peligrosidad: un LED verde indica niveles seguros, mientras que un LED rojo acompañado de una alarma intermitente señala concentraciones peligrosas que superan el umbral establecido.

### Problema que Resuelve

La conducción bajo los efectos del alcohol es una de las principales causas de accidentes de tránsito mortales a nivel mundial. Este proyecto ofrece una herramienta accesible y educativa para detectar niveles peligrosos de alcohol antes de conducir, promoviendo la prevención de accidentes y la toma de decisiones responsables.

### Alcance

Este prototipo tiene fines didácticos y demostrativos. Su alcance es académico: demostrar cómo se pueden integrar sensores analógicos, indicadores LED y alertas sonoras mediante programación en Arduino para abordar un problema de seguridad vial de forma práctica y comprensible.

## Requisitos

### Hardware
- 1x Arduino UNO
- 1x Sensor de gas MQ-3
- 1x LED verde (5mm)
- 1x LED rojo (5mm)
- 1x Buzzer piezoeléctrico (5V)
- 2x Resistencias 220Ω
- 1x Resistencia 1kΩ
- 1x Protoboard (830 puntos)
- Cables jumper macho-macho
- Cable USB tipo A a tipo B

### Software
- Arduino IDE 1.8.13 o superior
- Drivers CH340 (si es necesario)

## Instalación

### 1. Configuración del Software
```bash
# Descargar e instalar Arduino IDE desde:
https://www.arduino.cc/en/software
```

### 2. Montaje del Circuito

**Conexiones:**

| Componente | Pin Arduino | Observaciones |
|------------|-------------|---------------|
| Sensor MQ-3 | A0 | Conectar a través de resistencia 1kΩ |
| Sensor MQ-3 VCC | 5V | Alimentación del sensor |
| Sensor MQ-3 GND | GND | Tierra común |
| LED Verde | Pin 2 | Con resistencia 220Ω en serie |
| LED Rojo | Pin 3 | Con resistencia 220Ω en serie |
| Buzzer | Pin 4 | Directo (sin resistencia) |
| Todos GND | GND | Tierra común compartida |

### 3. Cargar el Código

1. Abre Arduino IDE
2. Copia el código del archivo `alcoholimetro.ino`
3. Conecta el Arduino UNO a tu PC mediante USB
4. Selecciona la placa: `Herramientas > Placa > Arduino UNO`
5. Selecciona el puerto: `Herramientas > Puerto > COMx` (Windows) o `/dev/ttyUSBx` (Linux/Mac)
6. Haz clic en el botón "Subir" (→)

## Cómo Usarlo

### Ejecución del Sistema

1. **Encender**: Conecta el Arduino a USB o fuente de alimentación
2. **Calibración**: Espera 20-30 segundos para que el sensor MQ-3 se caliente
3. **Prueba**: Sopla suavemente cerca del sensor o acerca alcohol
4. **Interpretación**:
   - 🟢 **LED Verde**: Nivel seguro (valor ≤ 232)
   - 🔴 **LED Rojo + Alarma**: Nivel peligroso (valor > 232)

### Monitor Serial

Para visualizar valores en tiempo real:
```bash
# En Arduino IDE:
Herramientas > Monitor Serial
# Configurar velocidad: 9600 baudios
```

**Salida esperada:**
```
85
92
103
...
245  # LED rojo + alarma activos
```

### Ajuste de Sensibilidad

Modifica el umbral en el código según necesites:
```cpp
// Línea 14 del código
if (alcohol > 232) {  // Cambia 232 por el valor deseado
```

- **Valores más bajos** (ej: 150): Mayor sensibilidad
- **Valores más altos** (ej: 300): Menor sensibilidad

### Simulación en Tinkercad

Prueba el proyecto virtualmente:

1. Accede a [Tinkercad Circuits](https://www.tinkercad.com/circuits)
2. Crea un nuevo circuito
3. Importa los componentes y conecta según diagrama
4. Copia el código en el editor
5. Inicia la simulación

## Estructura del Proyecto
```
alcoholimetro-arduino/
│
├── alcoholimetro.ino          # Código principal del Arduino
├── README.md                  # Este archivo
├── diagrams/
│   ├── diagrama_bloques.svg   # Diagrama de bloques del sistema
│   └── esquematico.png        # Esquema de conexiones
├── docs/
│   ├── documentacion.pdf      # Documentación completa
│   └── tabla_componentes.md   # Especificaciones de componentes
└── images/
    ├── montaje_fisico.jpg     # Foto del circuito armado
    └── tinkercad_sim.png      # Captura de simulación
```

## Arquitectura del Sistema

### Módulos Principales

**1. Módulo de Entrada**
- Sensor MQ-3 conectado a pin A0
- Resistencia de carga 1kΩ

**2. Módulo de Procesamiento**
- Arduino UNO (ATmega328P)
- Algoritmo de comparación con umbral (232)

**3. Módulo de Salida**
- LED Verde (Pin 2) - Estado seguro
- LED Rojo (Pin 3) - Estado peligroso
- Buzzer (Pin 4) - Alarma sonora

### Comunicación Entre Módulos

| Conexión | Tipo | Protocolo | Función |
|----------|------|-----------|---------|
| Sensor → Arduino | Analógica | ADC 10-bit | `analogRead(A0)` |
| Arduino → LED Verde | Digital | ON/OFF | `digitalWrite(2, HIGH/LOW)` |
| Arduino → LED Rojo | Digital | ON/OFF | `digitalWrite(3, HIGH/LOW)` |
| Arduino → Buzzer | Digital | Intermitente | `digitalWrite(4, HIGH/LOW)` |
| Arduino → PC | Serial | UART 9600 | `Serial.println()` |

## Funcionamiento Interno

El sistema opera en un ciclo continuo:

1. Lee valor analógico del sensor MQ-3 (rango 85-378)
2. Compara con umbral de seguridad (232)
3. Si `alcohol > 232`: Activa LED rojo + alarma intermitente
4. Si `alcohol ≤ 232`: Activa LED verde
5. Envía valores al Monitor Serial
6. Repite el ciclo

## Tecnologías Utilizadas

- **Lenguaje**: C++ (Arduino)
- **Hardware**: Arduino UNO (ATmega328P)
- **Sensor**: MQ-3 (Electroquímico de gas)
- **Comunicación**: UART (Serial 9600 baudios)
- **Plataforma de desarrollo**: Arduino IDE
- **Simulación**: Tinkercad Circuits

## Contribución

Este es un proyecto educativo de código abierto. Puedes contribuir:

- Documentando mejoras o variaciones del circuito
- Reportando errores o problemas encontrados
- Proponiendo nuevas funcionalidades (LCD, Bluetooth, etc.)
- Compartiendo tu implementación física
- Creando material educativo adicional

## Autor

[Tu Nombre]

## Licencia

Este proyecto es de código abierto con fines educativos.

## Recursos Adicionales

- [Arduino Reference](https://www.arduino.cc/reference/en/)
- [Datasheet Sensor MQ-3](https://www.sparkfun.com/datasheets/Sensors/MQ-3.pdf)
- [Tutorial Arduino IDE](https://docs.arduino.cc/software/ide-v1/tutorials/Environment)

---

**Nota**: Este proyecto es un prototipo educativo. Para aplicaciones de seguridad reales, se requieren alcoholímetros certificados y calibrados profesionalmente.
