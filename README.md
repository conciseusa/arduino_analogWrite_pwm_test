# arduino_analogWrite_pwm_test

Sketch to test analog / pwm Arduino outputs and hardware.<br>
Has an auto mode where output will fad up and down.<br>
Also has a button control mode where a one button interface allows setting of the output.<br>

`git clone https://github.com/conciseusa/arduino_analogWrite_pwm_test.git`

Tested on:<br>
Arduino® UNO R3<br>
Arduino® Nano Every - Had a hard time programming, tried a few times on different computers and it worked, not sure why. Has 1kHz PWM.<br>
Arduino® UNO R4 Minima - Arduino IDE had a error uploading, fix on Linux below:<br>

Cannot open DFU device 2341:0069 found on devnum 49 (LIBUSB_ERROR_ACCESS)<br>
dfu-util: No DFU capable USB device available<br>
Failed uploading: uploading error: exit status 74<br>

`cd /etc/udev/rules.d`<br>
`sudo nano 99-arduino-uno-r4.rules`<br>
Copy paste below into file:<br>

# UDEV Rules for Arduino UNO R4 boards, fix from post:<br>
# https://forum.arduino.cc/t/dfu-error-cannot-upload-sketch-to-r4-minima/1143436/9<br>
# This will allow reflashing with DFU-util without using sudo<br>
#<br>
# This file must be placed in:<br>
#       /etc/udev/rules.d<br>
#<br>
# After this file is installed, physically unplug and reconnect the device.<br>
#       Arduino UNO R4<br>
#<br>
SUBSYSTEMS=="usb", ATTRS{idVendor}=="2341", ATTRS{idProduct}=="0069", GROUP="plugdev", MODE="0666"<br>
SUBSYSTEMS=="usb", ATTRS{idVendor}=="2341", ATTRS{idProduct}=="0369", GROUP="plugdev", MODE="0666"<br>
#<br>
# If you share your linux system with other users, or just don't like the<br>
# idea of write permission for everybody, you can replace MODE:="0666" with<br>
# OWNER:="yourusername" to create the device owned by you, or with<br>
# GROUP:="somegroupname" and mange access using standard unix groups.<br>
