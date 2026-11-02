# AMLBIS-V1
An automatic and manual turn signal system for a bicycle.

Arduino as center hub; sends flow of electricity to turn signals

  3-way switch with left, right, and center positions
    Left position illuminates left front and back turn signals
    center position transfers led signal command to tilt sensor
    Right position illuminates right front and back turn signals

Need to find a way to factor in bumps and shakes for tilt sensor
  Can I make it more/less sensitive based on tilt angle?
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
