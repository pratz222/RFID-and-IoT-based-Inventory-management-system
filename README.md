# RFID and IoT-Based Inventory Management System

## Overview
The **RFID and IoT-Based Inventory Management System** is designed to track and manage items in a warehouse or store using wireless RFID tags and readers. This project utilizes the ESP32 microcontroller to communicate with an RFID module, reading data from tags attached to items. The collected data is then sent to a cloud platform, allowing for efficient storage, analysis, and management of inventory.

## Key Components
- **ESP32 Microcontroller**: A powerful microcontroller with built-in Wi-Fi capabilities for wireless communication.
- **RFID Module (MFRC522)**: Used to read data from RFID tags attached to inventory items.
- **Relay Module**: Controls devices based on RFID readings, enabling automation within the inventory system.
- **Firebase**: A cloud platform for real-time data storage and management.

## Features
- **Real-Time Inventory Tracking**: Efficiently track and manage inventory items using RFID technology.
- **Authorized Access Control**: Only authorized RFID tags can interact with the system, enhancing security.
- **Cloud Integration**: Store and analyze data in real-time using Firebase, providing insights into inventory levels.
- **User-Friendly Interface**: Simple serial output for monitoring the RFID interactions.

## Schematic and Design
The project involves a straightforward hardware setup connecting the ESP32 to the RFID module and the relay. The schematic can be found in the `schematics` directory.

## Getting Started
1. **Hardware Setup**: Connect the ESP32, RFID module, and relay according to the schematic provided.
2. **Programming the ESP32**: Upload the firmware to the ESP32 with your specific Wi-Fi and Firebase credentials.
3. **Testing**: Tap an RFID tag on the reader and monitor the serial output for authorized access and inventory updates.

## Contributing
Contributions are welcome! Feel free to submit issues or pull requests to enhance this project.


![image](https://github.com/pratz222/RFID-and-IoT-based-Inventory-management-system/assets/53640877/1bc7047a-7de9-4bd0-b420-b530a3e9fe88)

