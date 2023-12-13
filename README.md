# Helloe
Chat wireless by using one laptop and a microcontroller and display
## Components needed:

1. Any ESP8266 wifi microcontroller
2. OLED display (preferrably SSD1306 based)
3. Jumper Wires


## Connections:

1. Connect VCC and GND of OLED Display to 3.3V and GND of the M.C.
2. Connect the SCL pin to D1 and SDA pin to D2

## Softwares Requirements: 
1. for setting up arduino IDE for ESP8266 boards : https://randomnerdtutorials.com/how-to-install-esp8266-board-arduino-ide/ 
2. download the required libraries for ros and SSD1306 by adafruitt, GFX, etc via library manager
3. Install ROS neotic distro and one may set up workspace for the rospy pubslisher, however the provided code works independently also
4. Set up rosseiral server and launch file for initiating socket communication.(for more info: https://wiki.ros.org/rosserial_server)

## Setup:

1. Enter your network's SSID and password in the given node_disply.ino file, also by using '' hostname -I '' command in your terminal, enter the IPv4 address of your device on the SAME network as the one to be used by the Board.
2. Set up the publisher code using the given Rospy_code.py file, and upload the node_display.ino file after making above changes.
3. Start the rosserial server on port 11411 by using the follwing command:
   ''roslaunch rosserial_server socket.launch''
4. if everything is done right, one should be able to see 'connected' shown on the display after a while. Now one can send and see the messages wirelessly.

## What next:
This project is very simple , but may be extended even further,  by using a webserver it many become completely independent of ROS. One may also add some input methods like num pad to recieve and check input , or even voice commands, to make this kind of like a home security system. 
![WhatsApp Image 2023-12-14 at 01 02 54_4d86d984](https://github.com/Meh-Mehul/Helloe/assets/146803848/33f4bcce-5a62-4f1e-ae8c-d89bcebbf2bf)
