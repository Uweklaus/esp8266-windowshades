# ESP8266 Window

An Arduino code for ESP8266 module which controls your motorized window shade into wireless motorized one.

# Why

I have motorized window shades in my house controlled by 2 switches for up and down. Few weeks ago I started with a homebridge on a Pi for apple homekit, working quite nicely.
So I was looking for a possibility to control my shades via homekit and found the sketch of psled, which is quit nice, but I have the motors already installed and wanted to control up to 2 shades per ESP8266.
So I used from psled only his HTTP part and wrote the controller part new using the Arduino IDE.
To improve accuracy I used tasks. Position is controlled by moving time. I call the moving/controll task every total-move-time divided by 100. So I have to add or subtract only 1 of the current position.


# Requirements

- ESP8266 module (I used WeMos D1 mini)
- double relay for Arduino (try to use the ones working with 3.3V)
- switches were already mounted in the wall
- 5V power supply (cheap mobile charger is working fine, but be aware that here you may have high voltage poweron the 5V side!!!!!!!!!!!!!!!!!  )

Keep in mind that the relays are switching high voltage of your window shades!!!!

My shades have an automatic stop at the end, but I can not read this.


# Installation

First, download and install [ESP8266 Arduino](https://github.com/esp8266/Arduino) if you haven't done this before.

Connect the components, but be aware the high voltage!!! So don t do if you are not a professional.

Finally, upload code from this repository to your ESP8266 module.

Check out the [Homebridge plugin](https://github.com/uweklaus/homebridge-esp8266-window2). It was created to allows you to integrate your ESP8266 module with Apple HomeKit platform and Siri.

# Usage

- Current position
```
GET /window/currentPosition HTTP/1.1
```

- Position state
```
GET /window/positionState HTTP/1.1
```

- Target position
```
GET /window/targetPosition HTTP/1.1
```


```
POST /window/targetPosition HTTP/1.1
Content-Type: application/json

{
  "value": 78
}
```
# DONE
V 0.0.9 stable
- running, but no targetPosition GET HttpMethod
- Up and Down with same timing 

V 0.1.0
- read targetPosition by GET HttpMethod
- Up and Down have different timings, to achieve differences in moving speed

# TODO

- Adding a AP webserver, if no WiFi is available to change the SSID and password
- Adding a webserver, if connected to change the timings and read the current and targetPosition.

# License

ISC
