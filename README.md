Initial version of esp8266 integrated with AWS. Heavily based on the example at
https://github.com/SuperHouse/esp-open-rtos/tree/master/examples/aws_iot


Assumes that you have a cross-compiling enviornment working for Esp8266 xtensa processor.
To test you should be able to build and run the examples at 
https://github.com/SuperHouse/esp-open-rtos/tree/master/examples on your esp-12 board.

Assumes that you have configured the WIFI ssid and password as per.
https://github.com/SuperHouse/esp-open-rtos/blob/master/include/ssid_config.h


You will need to modify client_config.c with relevant client certificats, keys and endpoint.

Before building set the enviornment variable 'ESP_OPEN_RTOS' to the absolute path of the esp_rtos_sdk 
directory.

Now run flash.sh.


To view the serial console
picocom -b 115200 /dev/ttyUSB0 --omap crcrlf

To messages are published to esp8266/status amazon IOT queue and are received from
esp8266/control queue. You can send either "on" or "off" message to toggle the built-in
led on esp-12 board.

If you are stuck maybe you could read up the instructions at 
https://github.com/SuperHouse/esp-open-rtos/blob/master/examples/aws_iot/README.md

== Code Organization ==

You can start reading the code from user_init.c which initializes the esp8266 and starts the tasks.

There are two queues that are responsible for sending and receiving messages. See queues.h


