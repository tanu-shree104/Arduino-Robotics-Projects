# Arduino-Robotics-Projects
My Arduino, Robotics and IoT projects with source code, circuit diagrams and documentation.
# 🚗 Automated Parking Gate Using Arduino

## 📌 Project Description

The Automated Parking Gate is an Arduino-based project designed to control a parking barrier automatically. It uses an HC-SR04 ultrasonic sensor to detect approaching vehicles and an SG90 servo motor to open and close the gate.

The project also includes red and green LEDs to indicate the gate status and a push button for manual control.

## ✨ Features
- Automatic vehicle detection
- Automatic gate opening and closing
- Manual gate control using a push button
- Red LED indicates gate open
- Green LED indicates gate closed

## 🔧 Components Used
- Arduino UNO R4 Minima
- HC-SR04 Ultrasonic Sensor
- SG90 Servo Motor
- Red LED
- Green LED
- 220Ω resistors
- Push button
- Breadboard and jumper wires

## 🔌 Pin Connections

| Component | Arduino Pin |
|---|---|
| Ultrasonic TRIG | D7 |
| Ultrasonic ECHO | D6 |
| Servo Signal | D5 |
| Red LED | D10 |
| Green LED | D9 |
| Push Button | D2 |

## ⚙️ Working Principle
1. The ultrasonic sensor measures the distance in front of the gate.
2. When a vehicle is detected within the programmed distance, the gate opens.
3. The red LED indicates that the gate is open.
4. When the vehicle moves away, the gate closes.
5. The green LED indicates that the gate is closed.
6. The push button allows manual operation.

## 💻 Software Required
- Arduino IDE
- Servo library


## 🚀 Future Improvements
- RFID-based vehicle access
- LCD display for status
- Vehicle counting system

## 🎓 Learning Outcomes
This project demonstrates ultrasonic distance measurement, servo motor control, LED indicators,  and Arduino programming.
