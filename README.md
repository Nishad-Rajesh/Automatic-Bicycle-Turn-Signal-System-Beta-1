# AMLBIS-V1
Automatic/Manual Led Bicycle Indicator System

An automatic and manual turn signal system for a bicycle.

Arduino as center hub; sends flow of electricity to turn signals

# Automated Bicycle Turn-Signal & Headlight System

An automated bicycle safety system powered by an **Arduino Uno R3** and an **MPU-6050 accelerometer/gyroscope**. It features automated gybroscopic turn signals, a manual joystick override, and persistent headlight controls.

---

## Control Scheme

* **Push Joystick Up (Once):** Headlight **ON** (stays solid as a running light).
* **Push Joystick Up (Again):** Headlight **OFF**.
* **Push Joystick Down (Once):** Tilt/Auto-Lean Sensor **ACTIVE**.
* **Push Joystick Down (Again):** Tilt/Auto-Lean Sensor **INACTIVE**.
* **Joystick Left / Right:** Manual turn signal override (instantly takes priority over auto-lean mode).
* **Automatic Lean:** Tilting the sensor past $\pm 3.8\text{ m/s}^2$ automatically triggers the corresponding turn signal.
* **Joystick Switch:** Hazard lights (all lights blink).

---

## Parts List

| Category | Quantity | Component Name | Description / Purpose |
| :--- | :---: | :--- | :--- |
| **Microcontroller** | 1x | **Arduino Uno R3** | Main board running the control logic and sketch. |
| **Sensors** | 1x | **MPU-6050 Module** | 6-axis accelerometer and gyroscope used for auto-lean detection. |
| **Input Controls** | 1x | **Analog Joystick Module** | 2-axis joystick with built-in push-button switch (VRx, VRy, SW). |
| **Lighting** | 1x | **White LED (5mm)** | Headlight running light (Pin 10). |
| **Lighting** | 2x | **Amber / Yellow LEDs (5mm)** | Left and Right Turn Signal indicators (Pins 8 & 9). |
| **Passives** | 3x | **220Ω – 330Ω Resistors** | Current-limiting resistors placed in series with each LED. |
| **Prototyping** | 1x | **Solderless Breadboard** | Standard full-size or half-size breadboard for circuit assembly. |
| **Prototyping** | 1x Set | **Assorted Jumper Wires** | Male-to-Male and Male-to-Female jumper wires for connections. |
| **Connectivity** | 1x | **USB Programming Cable** | Connects Arduino to your computer for code uploads (`arduino-cli`). |
| **Power** | 1x | **Portable Power Source** | *Optional for bicycle mounting:* USB power bank or 9V battery with a barrel jack adapter. |

---

## Complete Wiring Guide

### Master Pin Connection Table

| Component | Component Pin | Arduino Pin | Connection & Notes |
| :--- | :--- | :--- | :--- |
| **Arduino Uno** | 5V | — | Breadboard Red (+) Power Rail |
| **Arduino Uno** | GND | — | Breadboard Blue (-) Ground Rail |
| **Arduino Uno** | A0 | — | Connected to Joystick VRx |
| **Arduino Uno** | A1 | — | Connected to Joystick VRy |
| **Arduino Uno** | Pin 7 | — | Connected to Joystick SW |
| **Arduino Uno** | Pin 8 | — | Connected to Left LED (via resistor) |
| **Arduino Uno** | Pin 9 | — | Connected to Right LED (via resistor) |
| **Arduino Uno** | Pin 10 | — | Connected to Headlight LED (via resistor) |
| **Arduino Uno** | A4 | — | Connected to MPU-6050 SDA |
| **Arduino Uno** | A5 | — | Connected to MPU-6050 SCL |
| **MPU-6050** | VCC | 5V | Breadboard Red (+) Power Rail |
| **MPU-6050** | GND | GND | Breadboard Blue (-) Ground Rail |
| **MPU-6050** | SDA | A4 | Arduino Analog Pin A4 |
| **MPU-6050** | SCL | A5 | Arduino Analog Pin A5 |
| **Joystick** | VCC | 5V | Breadboard Red (+) Power Rail |
| **Joystick** | GND | GND | Breadboard Blue (-) Ground Rail |
| **Joystick** | VRx | A0 | Arduino Analog Pin A0 |
| **Joystick** | VRy | A1 | Arduino Analog Pin A1 |
| **Joystick** | SW | Pin 7 | Arduino Digital Pin 7 |
| **Left LED** | Anode (+) | Pin 8 | Connected via 220Ω–330Ω resistor |
| **Left LED** | Cathode (-) | GND | Breadboard Blue (-) Ground Rail |
| **Right LED** | Anode (+) | Pin 9 | Connected via 220Ω–330Ω resistor |
| **Right LED** | Cathode (-) | GND | Breadboard Blue (-) Ground Rail |
| **Headlight LED** | Anode (+) | Pin 10 | Connected via 220Ω–330Ω resistor |
| **Headlight LED** | Cathode (-) | GND | Breadboard Blue (-) Ground Rail |

### Breadboard Assembly Instructions

1. **Power & Ground Rails:** 
   * Run a jumper wire from Arduino `5V` to the breadboard's **Red (+) Power Rail**.
   * Run a jumper wire from Arduino `GND` to the breadboard's **Blue (-) Ground Rail**.
2. **MPU-6050 Gyroscope:** 
   * Straddle the center divider of the breadboard. 
   * Connect `VCC` to power, `GND` to ground, `SDA` to `A4`, and `SCL` to `A5`.
3. **Analog Joystick Module:** 
   * Connect `VCC` to power, `GND` to ground, `VRx` to `A0`, `VRy` to `A1`, and `SW` to digital pin `7`.
4. **LED Assemblies:** 
   * Always place a **220Ω–330Ω resistor** in series with the positive Anode (long leg) of each LED:
     * Left LED Anode $\rightarrow$ Resistor $\rightarrow$ **Pin 8**
     * Right LED Anode $\rightarrow$ Resistor $\rightarrow$ **Pin 9**
     * Headlight LED Anode $\rightarrow$ Resistor $\rightarrow$ **Pin 10**
     * All LED Cathodes (short legs) $\rightarrow$ **Ground Rail**
