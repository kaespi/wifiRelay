# WiFi Relay ("wifiRelay")

This project is about a 230VAC relay which is controlled over WiFi using a [myStrom WiFi Button](https://mystrom.ch/de/wifi-button/). 

## WiFi Button

To open the WiFi Button physically, remove the rubber ring and carefully disconnect the lower from the bottom half (look for small slits which help). For debugging I quite often needed to disconnect the battery. 

### Configuration

To configure the WiFi button's WiFi setting (it has to connect to the WiFi hosted by the ESP8266!) I used the [myStrom Mobile](https://play.google.com/store/apps/details?id=com.cogniance.asoka.srs.android&hl=de_CH) app on Android. It was working quite ok. 

The configuraiton for the WiFi Button looks as follows:
* SSID: <*the programmed SSID*>
* Passphrase: <*the programmed passphrase*>
* IP address: 192.168.0.99
* Subnet mask: 255.255.255.0
* Gateway/DNS: 192.168.0.1

The action triggered by pressing the button can be configured from a machine in the same network afterwards, following the instructions from the myStrom API (see [links section below](#Links)). I've chosen to let the relay be triggered once with a short button press and toggled (open/closed) with a long button press:

```
# short button press
curl --location --request POST 'http://192.168.0.99/api/v1/action/single' --data-raw 'post://192.168.0.1:7788?trigger=1'
# long button press
curl --location --request POST 'http://192.168.0.99/api/v1/action/long' --data-raw 'post://192.168.0.1:7788?toggle=1'
```

### Re-Connection

I observed that the button seems not to "automagically" re-connect to the network when I re-started the ESP8266 with a new firmware. To achieve that however, I disconnected the battery in the WiFi button for a short time. After battery is again connected, pressing the button helps you reconnect to the WiFi network.

## Resources

Below a collection of links/hints/resources to help develop/build this project.

### Arduino

I was not using the Ubuntu arduino package. I found it's really outdated (at least on the system I was running). Therefore I recommend to download and install it directly from the [Arduino wegpage](https://www.arduino.cc/en/Main/Software).

The installation of the ESP8266 part can be done e.g. after [this tutorial](https://randomnerdtutorials.com/how-to-install-esp8266-board-arduino-ide/).

Note: even if you don't like the Arduino IDE but like to use VS code for the coding part (see below), you need the Arduino basic system to be installed!

### VS Code

Recommended [VS code](https://code.visualstudio.com/) extensions:
* [C/C++ for Visual Studio Code](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)
* [Visual Studio Code extension for Arduino](https://marketplace.visualstudio.com/items?itemName=vsciot-vscode.vscode-arduino)

### Serial port monitor

I found the [Picocom](https://github.com/npat-efault/picocom) tool to be quite useful (there are packages for Linux distros). E.g. in my setup I used the following command to listen to the Serial port:

```
$ picocom -b 115200 /dev/ttyUSB0 
```

### Links

* [myStrom API](https://api.mystrom.ch)
* [myStrom WiFi Button souce code (and some hints)](https://github.com/myStrom/mystrom-button)

(c) 2020, Kaspar Giger
