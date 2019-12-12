# buttonthing

An ESP8266-based hardware button thing to send commands to my [Lights](https://github.com/kenkl/lights) app.

Although the Lights app can be controlled from pretty much any WebKit browser, I wanted to be able to turn on/off lights *without* having to mess with my phone or laptop. I'm using the [Adafruit HUZZAH ESP8266 Breakout](https://www.adafruit.com/product/2471) to connect to my WiFi network to send commands to my Lights server. The wiring is pretty simple as seen in this [Fritzing](https://fritzing.org/home/) diagram:

![buttonthing Fritzing layout](https://i.imgur.com/HJkLPIa.png "buttonthing Fritzing layout")
(the fritzing file is included in the project - buttonthing.fzz)

It's pretty straightforward to adjust the endpoints it calls on the Lights server - just update the '/lights/...' URI in the block associated with the desired button. For example, Button1 currently calls medtog.php as shown:

```C++
const int button1 = 14;
const char* url1 = "/lights/medtog.php";
int button1State = 0;
```

To compile and upload the code, I use [Visual Studio Code](https://code.visualstudio.com/) with the [PlatformIO](https://platformio.org/) extension installed. [Adafruit's tutorial](https://learn.adafruit.com/adafruit-huzzah-esp8266-breakout/overview) on the ESP8266 breakout is useful, but be aware - it hasn't been updated to address VSC, and describes programming it with the Arduino IDE instead. Much of the same information applies, only it's easier to use VSC/PIO - the necessary libraries for the 8266 are already included. In my experience, VSC/PIO will program the thing "out of the box" - no hardware configuration needed if the correct board is selected/configured in platformio.ini (as seen in this project).

(11-Dec-2019: I don't *think* led2(GPIO16) is actually being used for anything. I dimly remember having it there to indicate *something*, but what exactly has been lost to the sands of time and untracked code revisions. I'll get it out of there soon.)

