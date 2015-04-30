#!/bin/bash

adb start-server
adb shell screencap -p /sdcard/tmp.log
adb pull /sdcard/tmp.png /home/joey/Screenshot-$(date +%F-%H-%M-%S).png
adb shell rm /sdcard/tmp.png
