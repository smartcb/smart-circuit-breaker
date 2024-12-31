# Welcome to the Smart Circuit Breaker Project

## Wiring Diagram

![image](https://github.com/user-attachments/assets/81232749-465c-4467-ac06-1850387e850b)

![image](https://github.com/user-attachments/assets/7a1b99eb-54e6-4619-a5a1-dfa1a0eb9420)


![image](https://github.com/user-attachments/assets/0d41abbc-ef8c-4e98-a425-acc40f5e0734)

![image](https://github.com/user-attachments/assets/b4e5e6bb-3bd8-41ff-9759-ae114cd27654)


### ESP32
![image](https://github.com/user-attachments/assets/ff318ec0-746d-4fcb-b0bd-e28d05273a8d)

### TFT 3.2 Inches
![image](https://github.com/user-attachments/assets/97290607-e8ca-4df4-af8c-4fba7f0a244e)

### ESP32 to TFT Wiring
![image](https://github.com/user-attachments/assets/4b1a4289-7582-4520-b085-fa2a7ea72061)



### PZEM-004T
![image](https://github.com/user-attachments/assets/5ac9594d-a2e9-4532-88d6-73fa412a05b2)

### ESP32 to PZEM-004T Wiring
![Smart Circuit Breaker](https://github.com/user-attachments/assets/4669f0d2-258d-4a4c-8c08-b779c27f6a73)

![image](https://github.com/user-attachments/assets/d816e7c3-71b4-45a4-95b8-3f272fa3f40c)
Note: Please disregard the Arduino Uno,we will be using ESP32

### How to update your local project from GitHub repository

1. Open command prompt
![image](https://github.com/user-attachments/assets/e8e88ab9-9e35-46f4-a4aa-be77b27ce23a)

2. Type the following in your command prompt
```
cd c:\git-repo\smart-circuit-breaker
```
![image](https://github.com/user-attachments/assets/4c2793c0-134b-46e2-af10-0ceffe9f8e52)

3. Check if you have local changes in your project by typing the below command
```
git status
```
If there are any local changes then we need to delete it by executing the below command
```
git checkout .
```
Run `git status` again to verify that it is clean
![image](https://github.com/user-attachments/assets/f5516821-8d82-4478-a62c-a3b7c351eaab)
4. Get the latest changes from GitHub by running the following command
```
git pull
```

### How to open project in VSCode
1. Open command prompt
2. Change the directory to your project folder
```
cd c:\git-repo\smart-circuit-breaker
code .
```
This should open your project in VSCode


### Testing Steps
#### Test the ESP32
1. Run and check the output of test_blink_esp32_led.cpp

Expected Output:
The Internal LED of the ESP32 should blink continuously

#### Test the TFT
1. Run and check the output of test_hello_world_tft.cpp

Expected Output:
The TFT should display Hello from Smart Circuit Breaker

#### Test the PZEM
1. Run and check the output of test_read_pzem_async.cpp

Expected Output:
We should see the PZEM reading

#### Test the SSR being driven by the transistor
1. Run and check the output of test_drive_transistor.cpp

Expected Output:
We should see the SSR blinking every 5 seconds


#### Setup the SSR wiring from the Load Side to the power side
Note: Adjust and double check for shorting


#### Test the blynk connection
1. Run and check the output of test_main.cpp

Expected Output:
Open the BLYNK Cloud Application https://blynk.cloud/dashboard and login using the credentials given by Ram
Click the Smart Circuit Breaker and verify that the output of the Line is being displayed (Current and Voltage)

#### Validate the Blynk Connection
You should see the following in your terminal serial monitor when you are able to connect to Blynk Server
```
--- Terminal on COM5 | 115200 8-N-1
--- Available filters and text transformations: colorize, debug, default, direct, esp32_exception_decoder, hexlify, log2file, nocontrol, printable, send_on_enter, time
--- More details at https://bit.ly/pio-monitor-filters
--- Quit: Ctrl+C | Menu: Ctrl+T | Help: Ctrl+T followed by Ctrl+H
E (365) esp_core_dump_flash: Incorrect�xize of core dump image: 572661795
[28] Connecting to donskytech-1stFloor
[4155] Connected to WiFi
[4155] IP: 192.168.100.42
[4155]
    ___  __          __
   / _ )/ /_ _____  / /__
  / _  / / // / _ \/  '_/
 /____/_/\_, /_//_/_/\_\
        /___/ v1.3.2 on ESP32

 #StandWithUkraine    https://bit.ly/swua


[4166] Connecting to blynk.cloud:80
[4848] Ready (ping: 33ms).
```
