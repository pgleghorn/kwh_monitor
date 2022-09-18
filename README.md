# watts-up

A project to monitor and graph the electricity usage in the home over time.

## How it works

A long cable with a light sensitive
resistor runs from an Arduino into the outside electricity cabinet, the resistor
is positioned in front of the LED on the mains power meter. The LED pulses with varying
frequency according to the current consumption.  Some code on the arduino
(LightSensor.ino) detects the pulses, and announces them over the serial port.

Some code on the Raspberry Pi (kwh_monitor.py) 
listens on the serial connection, notes the pulse frequency and calculates
the effective kWh usage. It reports the value as a metric to a 
prometheus server running on the Raspberry Pi.

## Requirements

This project uses:
 - Raspberry Pi B
 - Arduino Mega, with arduino-cli
 - Python 3.7
 - Prometheus 2.38.0

## Arduino sensor

documentation todo

## Install

Build kwh_monitor.py:
```
pip install -r requirements.txt
```

Install promemtheus and configure a new scrape config:
```
scrape_configs:
  - job_name: "kwh_sensor"
    static_configs:
      - targets: ["localhost:8000"]
```

Build and upload the arduino code:
```
buildUpload.sh
```

## Run

```
./kwh_monitor.py &
```

Visit prometheus at localhost:9090
