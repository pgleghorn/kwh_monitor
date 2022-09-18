#!/usr/bin/env python3

from prometheus_client import start_http_server, Summary, Gauge
import time
from datetime import datetime
import serial

metrics_port = 8000
serial_port = '/dev/ttyACM0'

kwh_gauge = Gauge('kwh_gauge', 'kWh observed from the power supply monitor')
sensor_gauge = Gauge('sensor_gauge', 'raw light value observed from the power supply monitor')

if __name__ == "__main__":
    print(f"serving prometheus metrics on http port {metrics_port}")
    start_http_server(metrics_port)

    print(f"listening for ticks on serial port {serial_port}")
    serialInst = serial.Serial()
    serialInst.baudrate = 9600
    serialInst.port = serial_port
    serialInst.open()

    then = datetime.now()
    while True:
        if serialInst.in_waiting:
            now = datetime.now()
            delta_seconds = (now - then).total_seconds()
            powerkwh = round(3600 / (delta_seconds * 1000), 4)
            then = now
            packet = serialInst.readline()
            packetStr = packet.decode('utf')
            print(f"detected {powerkwh} kWh")
            kwh_gauge.set(powerkwh)
