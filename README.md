| Supported Targets | ESP32-C6 | ESP32-H2 |
| ----------------- | -------- | -------- |

# OpenThread UDP Receiver

This codebase enables an 802.15.4 ESP32 MCU to receive packets broadcasted by the [UDP Sender](https://github.com/UCSC-CSE299A/ot-send).

## Setup

You will first need to form a Thread WLAN with at least two devices. Wait until *both* the sending and receiving devices are connected to the Thread WLAN.

If the receiving device is working properly, you should expect the following output, which will keep printing in an infinite loop:
```
I(2676) OPENTHREAD:[N] Platform------: Received Packet Number 46
I(7706) OPENTHREAD:[N] Platform------: Received Packet Number 47
I(12676) OPENTHREAD:[N] Platform------: Received Packet Number 48
I(17666) OPENTHREAD:[N] Platform------: Received Packet Number 49
```

Note that the `Packet Number` may vary depending on when you have created the UDP socket.

## Changing the TX Power

If you would like to change the 802.15.4 transmission power used by OpenThread, enter:

```bash
idf.py menuconfig
```

and navigate to:
```
CSE 299A OpenThread Sender → Set the 802.15.4 TX power used by OpenThread
```

to enter the TX Power (in dBm) that you would like to use.

## Enabling Automatic Start

The `UART` port should be used in order to enable automatic start of recieving UDP packets without turning on the serial monitor. The `USB-Serial` can be used, but there is no guarantee that it may work without use of the serial monitor.
