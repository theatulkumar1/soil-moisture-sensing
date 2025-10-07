# 🌱 Soil Moisture Sensing System

## Overview
A comprehensive soil moisture monitoring and automated irrigation alert system built with Arduino Uno. This project combines hardware sensing with a modern web-based dashboard to provide real-time monitoring of soil moisture levels, helping optimize irrigation schedules and conserve water.

## 🌟 Features

- **Real-time Monitoring**: Continuously reads soil moisture levels using an analog sensor
- **Visual Dashboard**: Modern, responsive web interface with real-time gauge display
- **Smart Alerts**: 
  - Audible buzzer alerts when soil moisture drops below 40%
  - Color-coded visual indicators (Red/Yellow/Green)
  - Status messages for different moisture levels
- **Web Serial Communication**: Direct browser-to-Arduino connection using Web Serial API
- **Automated Irrigation Guidance**: Clear indicators of when watering is needed

## 📋 Table of Contents

- [Hardware Requirements](#hardware-requirements)
- [Software Requirements](#software-requirements)
- [Circuit Connections](#circuit-connections)
- [Installation](#installation)
- [Usage Instructions](#usage-instructions)
- [Project Files](#project-files)
- [How It Works](#how-it-works)
- [Moisture Level Thresholds](#moisture-level-thresholds)
- [Troubleshooting](#troubleshooting)
- [Future Enhancements](#future-enhancements)
- [License](#license)

## 🔧 Hardware Requirements

- **Arduino Uno** (or compatible board)
- **Soil Moisture Sensor** (analog capacitive or resistive)
- **Piezo Buzzer** or active buzzer
- **Jumper Wires**
- **USB Cable** (for Arduino-to-PC connection)
- **Breadboard** (optional, for prototyping)

## 💻 Software Requirements

- **Arduino IDE** (version 1.8.x or later)
- **Modern Web Browser** with Web Serial API support:
  - Google Chrome (version 89+)
  - Microsoft Edge (version 89+)
  - Opera (version 75+)
- **USB Serial Drivers** (usually pre-installed with Arduino IDE)

## 🔌 Circuit Connections

### Soil Moisture Sensor
- **VCC** → Arduino 5V
- **GND** → Arduino GND
- **A0 (Analog Output)** → Arduino A0 pin

### Buzzer
- **Positive (+)** → Arduino Digital Pin 2
- **Negative (-)** → Arduino GND

### Connection Diagram
```
Arduino Uno
┌─────────────────┐
│                 │
│  A0 ←───────────┼─── Soil Moisture Sensor (Signal)
│  D2 ←───────────┼─── Buzzer (+)
│  5V ────────────┼─── Sensor VCC
│  GND ───────────┼─── Sensor GND & Buzzer (-)
│                 │
│  USB ←──────────┼─── Computer
└─────────────────┘
```

## 📥 Installation

### Step 1: Arduino Setup

1. **Install Arduino IDE**
   - Download from [arduino.cc](https://www.arduino.cc/en/software)
   - Install following the instructions for your OS

2. **Open the Arduino Sketch**
   - Open `sketch_oct7c.ino` in Arduino IDE

3. **Select Board and Port**
   - Go to `Tools > Board > Arduino AVR Boards > Arduino Uno`
   - Go to `Tools > Port` and select your Arduino's COM port

4. **Upload the Code**
   - Click the Upload button (→) or press `Ctrl+U`
   - Wait for "Done uploading" message

### Step 2: Web Interface Setup

1. **Download the HTML file**
   - Save `soil_monitor.html` to your computer

2. **Open in Browser**
   - Open the file with Chrome, Edge, or Opera
   - Ensure Arduino is connected via USB

## 🚀 Usage Instructions

### Starting the System

1. **Power Up Arduino**
   - Connect Arduino Uno to your computer via USB
   - The Arduino should power on (onboard LED should light up)

2. **Insert Soil Sensor**
   - Place the soil moisture sensor in the soil
   - Ensure good contact with the soil
   - Avoid submerging the electronics (only the prongs should be in soil)

3. **Launch Dashboard**
   - Open `soil_monitor.html` in a compatible browser
   - Click the **"🔌 Connect to Arduino"** button
   - Select the correct COM port from the popup
   - Click "Connect"

4. **Monitor Readings**
   - Dashboard will display real-time moisture percentage
   - Gauge color changes based on moisture level:
     - 🟢 **Green** (70-100%): Optimal moisture
     - 🟡 **Yellow** (40-69%): Moderate moisture
     - 🔴 **Red** (0-39%): Dry soil - water needed!
   - Buzzer will beep when moisture drops below 40%

### Disconnecting

- Click the **"🔴 Disconnect"** button on the web dashboard
- Safely remove USB cable if needed

## 📁 Project Files

### 1. `sketch_oct7c.ino` - Arduino Firmware

This is the main Arduino sketch that handles sensor reading and serial communication.

**Key Functions:**

```cpp
void setup() {
  Serial.begin(9600);        // Initialize serial at 9600 baud
  pinMode(buzzerPin, OUTPUT); // Set buzzer pin as output
}

void loop() {
  int sensorValue = analogRead(sensorPin);              // Read analog value (0-1023)
  int moisturePercent = map(sensorValue, 1023, 0, 0, 100); // Convert to percentage
  Serial.println(moisturePercent);                       // Send data to serial
  
  if (moisturePercent < 40) {
    tone(buzzerPin, 4000, 500); // Alert buzzer at 4kHz for 500ms
  }
  delay(1000); // Update every second
}
```

**What it does:**
- Reads analog values from soil moisture sensor (0-1023)
- Converts readings to moisture percentage (0-100%)
- Sends percentage value via serial port every second
- Triggers buzzer alarm when moisture falls below 40%
- Uses 4kHz tone for 500ms duration

### 2. `soil_monitor.html` - Web Dashboard

A standalone HTML file with embedded CSS and JavaScript for the monitoring interface.

**Key Technologies:**

- **Web Serial API**: Enables direct browser-to-Arduino communication
- **Real-time Updates**: Displays moisture readings as they arrive
- **Responsive Design**: Works on desktop and mobile devices
- **Dynamic Styling**: Visual feedback changes with moisture levels

**Core Functions:**

```javascript
async function connectSerial() {
  port = await navigator.serial.requestPort();  // Request port access
  await port.open({ baudRate: 9600 });          // Open at 9600 baud
  readLoop();                                    // Start reading data
}

function updateDisplay(moisture) {
  gauge.textContent = moisture + "%";
  if (moisture < 40) {
    gauge.style.background = "#e74c3c";         // Red for dry
    status.textContent = "⚠️ Soil is Dry! Water needed.";
  } else if (moisture < 70) {
    gauge.style.background = "#f1c40f";         // Yellow for moderate
    status.textContent = "🌤️ Moisture is Moderate.";
  } else {
    gauge.style.background = "#2ecc71";         // Green for good
    status.textContent = "✅ Soil Moisture is Good!";
  }
}
```

## ⚙️ How It Works

### System Architecture

```
┌─────────────────┐
│  Soil Moisture  │
│     Sensor      │
└────────┬────────┘
         │ Analog Signal (0-1023)
         ↓
┌─────────────────┐
│   Arduino Uno   │
│  - Reads sensor │
│  - Maps to %    │
│  - Controls     │
│    buzzer       │
└────────┬────────┘
         │ Serial Data (9600 baud)
         ↓
┌─────────────────┐
│  Web Browser    │
│  - Receives %   │
│  - Updates UI   │
│  - Shows alerts │
└─────────────────┘
```

### Workflow

1. **Sensor Reading**: Soil moisture sensor outputs an analog voltage proportional to moisture
2. **ADC Conversion**: Arduino's 10-bit ADC converts voltage to digital value (0-1023)
3. **Mapping**: Value is inversely mapped to percentage (dry=0%, wet=100%)
4. **Alert Check**: If below threshold (40%), buzzer activates
5. **Serial Transmission**: Percentage sent via USB serial (9600 baud, 1-second interval)
6. **Web Parsing**: JavaScript reads serial data and extracts moisture value
7. **UI Update**: Dashboard gauge, color, and status update in real-time

## 📊 Moisture Level Thresholds

| Moisture % | Color | Status | Action Required | Buzzer |
|-----------|-------|--------|-----------------|--------|
| **70-100%** | 🟢 Green | Optimal | None | Off |
| **40-69%** | 🟡 Yellow | Moderate | Monitor | Off |
| **0-39%** | 🔴 Red | Dry | Water Now! | On |

### Calibration Tips

- **Dry Reading**: Place sensor in completely dry soil to see minimum values
- **Wet Reading**: Water soil thoroughly and note maximum values
- **Adjust Thresholds**: Modify the percentages in both Arduino and HTML code based on your soil type:
  - Sandy soil: May need higher thresholds
  - Clay soil: May need lower thresholds
  - Indoor plants: Usually prefer 50-70% range

## 🐛 Troubleshooting

### Arduino Issues

**Problem**: Upload fails / Port not found
- **Solution**: 
  - Check USB cable connection
  - Restart Arduino IDE
  - Try different USB port
  - Install CH340/FTDI drivers if needed

**Problem**: Readings always show 0% or 100%
- **Solution**:
  - Verify sensor connections (VCC, GND, A0)
  - Test sensor in glass of water
  - Check if sensor is damaged
  - Reverse the mapping if values are inverted

**Problem**: Buzzer doesn't sound
- **Solution**:
  - Verify buzzer polarity
  - Test with different digital pin
  - Check if passive buzzer (needs PWM) vs active buzzer

### Web Interface Issues

**Problem**: "Connect" button doesn't work
- **Solution**:
  - Use Chrome, Edge, or Opera (Web Serial API required)
  - Ensure HTTPS or localhost (security requirement)
  - Update browser to latest version

**Problem**: Can't select COM port
- **Solution**:
  - Ensure Arduino is connected via USB
  - Close Arduino IDE Serial Monitor (releases port)
  - Restart browser
  - Check Windows Device Manager for COM port

**Problem**: Dashboard shows "---%" or no updates
- **Solution**:
  - Verify baud rate matches (9600 in both Arduino and HTML)
  - Check serial monitor to confirm Arduino is sending data
  - Look for JavaScript errors in browser console (F12)

### General Tips

- **Serial Monitor**: Open `Tools > Serial Monitor` in Arduino IDE to verify data transmission
- **Baud Rate**: Must match in all places (Arduino code, Serial Monitor, HTML)
- **Sensor Placement**: Avoid touching sensor electrodes to prevent corrosion
- **Power Supply**: Ensure stable 5V supply for consistent readings

## 🚧 Future Enhancements

Potential improvements for this project:

### Hardware
- [ ] Add relay module for automatic irrigation pump control
- [ ] Include DHT22 sensor for temperature and humidity monitoring
- [ ] Add LCD display for standalone operation
- [ ] Implement multiple sensor nodes for large areas
- [ ] Solar power integration for outdoor deployment
- [ ] Water level sensor for reservoir monitoring

### Software
- [ ] Data logging with timestamps
- [ ] Export historical data to CSV
- [ ] Email/SMS alerts using cloud integration
- [ ] Mobile app development (Android/iOS)
- [ ] Machine learning for irrigation prediction
- [ ] Multi-plant profiles with different thresholds
- [ ] Integration with weather APIs for smart scheduling

### Features
- [ ] User authentication and multi-user support
- [ ] Customizable alert thresholds via web interface
- [ ] Battery level monitoring for portable systems
- [ ] Voice notifications using Web Speech API
- [ ] Cloud database storage (Firebase, AWS IoT)
- [ ] PWA (Progressive Web App) for offline functionality

## 📸 Screenshots

*(Add screenshots of your working system here)*

- Dashboard in action
- Circuit assembly
- Sensor in soil
- Alert state demonstration

## 🤝 Contributing

Contributions are welcome! Feel free to:

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## 📄 License

This project is open source and available for educational and personal use.

## 👨‍💻 Author

**theatulkumar1**
- GitHub: [@theatulkumar1](https://github.com/theatulkumar1)

## 🙏 Acknowledgments

- Arduino community for extensive documentation
- Web Serial API developers for browser-hardware communication
- Open source contributors in the IoT agriculture space

## 📞 Support

If you encounter any issues or have questions:
- Open an issue on GitHub
- Check existing issues for solutions
- Review the troubleshooting section above

---

**Happy Gardening! 🌱💧**

*Last updated: October 2025*
