# ESP32-mousemover

This is my first public ESP32 project. It compiles on PlatformIO and uses a [ESP32-S3-Zero](https://www.waveshare.com/wiki/ESP32-S3-Zero) as hardware.

![ESP32-S3-Zero](https://www.waveshare.com/w/upload/thumb/c/ce/ESP32-S3-Zero.jpg/300px-ESP32-S3-Zero.jpg)

I hear you saying *"you could simply disable your screensaver"*. Correct. But I was tired to change the settings every time Microsoft, HP or whoever decided that my laptop had to be a bit "greener". And so I coded this device which is connected to my docking station. Problem solved. :wink:

# Releases

## 1.1

Identification of Mouse Mover can be configured

## 1.0

First release

# Known issues & ideas for later

* The onboard (RGB) LED, connected to GPIO 21, doesn't blink as intended. Once I knew how to let it blink in all colors - but somehow lost the code and didn't quickly find a working example on the Internet.
* Today, my "mouse" device identifies as "Espressif ESP32-S3-USB-OTG". Idea is to change the name so that it looks more like a real mouse.

# Compile Parameters

## TEST

By default, the mouse pointer is moved by nealy-invisible 2pt every 270 seconds. Compiling the code with option -D TEST will

* increase the distance of the mouse motion so that the effect can better be observed. Additionally, the interval is reduced from 270 to just a few seconds so that it moves more often.

## LED_BUILTIN

If set to a GPIO Pin, the idea is that the onboard LED will blink when the mouse pointer is moved.

## RGB_BUILTIN

If set to a GPIO Pin, the idea is that the onboard LED will blink when the mouse pointer is moved. Current color is set to blue, but can be customized.

## USB_PRODUCT + USB_MANUFACTURER

Both flags can be used to define the device name. By default, the mouse move will identify depending on the ESP 32 model. With the parameters in the platformio.ini file, it will identify as follows on Windows systems:

![Windows Representation of Device Name](./images/USB-Name.png "Title")