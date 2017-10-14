#!/usr/bin/env python
#-*- coding:utf-8 -*-

import serial
import time
import sys

ser = serial.Serial('/dev/ttyACM0', 9600)

time.sleep(2)
ser.write('h')
print ser.read()
sys.exit()
