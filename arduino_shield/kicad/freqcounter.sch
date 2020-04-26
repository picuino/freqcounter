EESchema Schematic File Version 4
LIBS:freqcounter-cache
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "FREQUENCY COUNTER WITH PIC16F18446"
Date "2020-03-12"
Rev "1"
Comp "PICUINO"
Comment1 "License CC BY-SA 4.0"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text GLabel 4500 2700 0    40   Input ~ 0
MCLR
Text GLabel 4400 2400 0    40   Input ~ 0
VDD
$Comp
L Device:C C2
U 1 1 5E6A67BE
P 5000 2000
F 0 "C2" V 4950 2050 50  0000 L CNN
F 1 "100nF" V 4850 1900 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5038 1850 50  0001 C CNN
F 3 "~" H 5000 2000 50  0001 C CNN
	1    5000 2000
	0    1    1    0   
$EndComp
$Comp
L Device:R R3
U 1 1 5E71FB56
P 3750 3200
F 0 "R3" V 3850 3150 50  0000 L CNN
F 1 "1K" V 3750 3150 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3680 3200 50  0001 C CNN
F 3 "~" H 3750 3200 50  0001 C CNN
	1    3750 3200
	0    1    1    0   
$EndComp
$Comp
L Device:C C3
U 1 1 5E71FBD7
P 2850 3200
F 0 "C3" V 2700 3150 50  0000 L CNN
F 1 "2.2nF" V 2600 3150 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2888 3050 50  0001 C CNN
F 3 "~" H 2850 3200 50  0001 C CNN
	1    2850 3200
	0    1    -1   0   
$EndComp
$Comp
L power:Earth #PWR01
U 1 1 5E71FD1E
P 2700 3200
F 0 "#PWR01" H 2700 2950 50  0001 C CNN
F 1 "Earth" H 2700 3050 50  0001 C CNN
F 2 "" H 2700 3200 50  0001 C CNN
F 3 "~" H 2700 3200 50  0001 C CNN
	1    2700 3200
	0    1    -1   0   
$EndComp
Text GLabel 6300 2700 2    40   Input ~ 0
INPUT_ZCD
Text GLabel 5000 900  0    40   Input ~ 0
MCLR
Text GLabel 5000 1000 0    40   Input ~ 0
VDD
Text GLabel 5000 1100 0    40   Input ~ 0
GND
Text GLabel 4500 2800 0    40   Input ~ 0
INPUT_A
Text GLabel 4500 2900 0    40   Input ~ 0
INPUT_B
$Comp
L Diode:1N4148W D1
U 1 1 5E78AE06
P 3350 3200
F 0 "D1" H 3400 3100 50  0000 R CNN
F 1 "1N4148" H 3500 3000 50  0000 R CNN
F 2 "Diode_SMD:D_SOD-123" H 3350 3025 50  0001 C CNN
F 3 "https://www.vishay.com/docs/85748/1n4148w.pdf" H 3350 3200 50  0001 C CNN
	1    3350 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	3600 3200 3500 3200
Wire Wire Line
	3000 3200 3100 3200
Text GLabel 5600 2400 2    40   Input ~ 0
GND
$Comp
L Connector:Conn_01x05_Female J1
U 1 1 5EA272A8
P 5200 1100
F 0 "J1" H 5228 1125 50  0000 L CNN
F 1 "ICSP PICKIT" H 4800 1450 50  0000 L CNN
F 2 "" H 5200 1100 50  0001 C CNN
F 3 "~" H 5200 1100 50  0001 C CNN
	1    5200 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	5600 2400 5500 2400
Wire Wire Line
	5500 2400 5500 2000
Wire Wire Line
	5500 2000 5150 2000
Wire Wire Line
	4500 2400 4400 2400
Wire Wire Line
	4500 2400 4500 2000
Wire Wire Line
	4500 2000 4850 2000
Wire Wire Line
	3100 3000 3100 3200
Wire Wire Line
	3100 3000 4500 3000
Wire Wire Line
	4500 3100 3900 3100
Wire Wire Line
	3900 3100 3900 3200
Text GLabel 5000 1200 0    40   Input ~ 0
ICSPDAT
Text GLabel 5000 1300 0    40   Input ~ 0
ICSPCLK
Text GLabel 5500 2500 2    40   Input ~ 0
ICSPDAT
Text GLabel 5500 2600 2    40   Input ~ 0
ICSPCLK
$Comp
L Connector:Conn_01x08_Male J3
U 1 1 5EA433A3
P 2200 1500
F 0 "J3" H 2100 1500 50  0000 C CNN
F 1 "Arduino_Digital_2" H 2300 1950 50  0000 C CNN
F 2 "" H 2200 1500 50  0001 C CNN
F 3 "~" H 2200 1500 50  0001 C CNN
	1    2200 1500
	-1   0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x08_Male J5
U 1 1 5EA43462
P 2200 2500
F 0 "J5" H 2150 2500 50  0000 R CNN
F 1 "Arduino_Digital_1" H 2600 2950 50  0000 R CNN
F 2 "" H 2200 2500 50  0001 C CNN
F 3 "~" H 2200 2500 50  0001 C CNN
	1    2200 2500
	-1   0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x06_Male J4
U 1 1 5EA4359C
P 1000 2400
F 0 "J4" H 900 2400 50  0000 R CNN
F 1 "Arduino_Analog" H 1400 2750 50  0000 R CNN
F 2 "" H 1000 2400 50  0001 C CNN
F 3 "~" H 1000 2400 50  0001 C CNN
	1    1000 2400
	1    0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x06_Male J2
U 1 1 5EA440CC
P 1000 1400
F 0 "J2" H 900 1400 50  0000 R CNN
F 1 "Arduino_Power" H 1400 1750 50  0000 R CNN
F 2 "" H 1000 1400 50  0001 C CNN
F 3 "~" H 1000 1400 50  0001 C CNN
	1    1000 1400
	1    0    0    -1  
$EndComp
Text Notes 800  900  0    100  ~ 0
ARDUINO INTERFACE
Wire Notes Line
	650  650  650  3000
Wire Notes Line
	650  3000 2500 3000
Wire Notes Line
	2500 3000 2500 650 
Wire Notes Line
	2500 650  650  650 
Text GLabel 1200 2700 2    40   Input ~ 0
SCL
Text GLabel 1200 2600 2    40   Input ~ 0
SDA
Text GLabel 2000 2900 0    40   Input ~ 0
ARD_RX
Text GLabel 2000 2800 0    40   Input ~ 0
ARD_TX
Text GLabel 1200 1700 2    40   Input ~ 0
ARD_VIN
Text GLabel 1200 1600 2    40   Input ~ 0
GND
Text GLabel 1200 1500 2    40   Input ~ 0
GND
Text GLabel 1200 1400 2    40   Input ~ 0
5V
Text GLabel 1200 1300 2    40   Input ~ 0
3.3V
Text GLabel 1200 1200 2    40   Input ~ 0
RESET
Text GLabel 2000 1300 0    40   Input ~ 0
GND
Text GLabel 2000 1200 0    40   Input ~ 0
AREF
Text GLabel 6300 2800 2    40   Input ~ 0
ARD_TX
Text GLabel 5500 2900 2    40   Input ~ 0
ARD_RX
Text GLabel 5500 3100 2    40   Input ~ 0
SCL
Text GLabel 5500 3000 2    40   Input ~ 0
SDA
$Comp
L Device:R R1
U 1 1 5EA4B9B0
P 5950 2700
F 0 "R1" V 5900 2850 50  0000 L CNN
F 1 "10K" V 5945 2625 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 5880 2700 50  0001 C CNN
F 3 "~" H 5950 2700 50  0001 C CNN
	1    5950 2700
	0    1    1    0   
$EndComp
Wire Wire Line
	6100 2700 6300 2700
Wire Wire Line
	5500 2700 5800 2700
$Comp
L Device:R R2
U 1 1 5EA58FDB
P 5950 2800
F 0 "R2" V 5900 2950 50  0000 L CNN
F 1 "180" V 5945 2725 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 5880 2800 50  0001 C CNN
F 3 "~" H 5950 2800 50  0001 C CNN
	1    5950 2800
	0    1    1    0   
$EndComp
Wire Wire Line
	6300 2800 6100 2800
Wire Wire Line
	5800 2800 5500 2800
$Comp
L Device:C C1
U 1 1 5EA59BE1
P 5050 1700
F 0 "C1" V 5000 1750 50  0000 L CNN
F 1 "10uF" V 4900 1600 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5088 1550 50  0001 C CNN
F 3 "~" H 5050 1700 50  0001 C CNN
	1    5050 1700
	0    1    1    0   
$EndComp
Wire Wire Line
	5200 1700 5500 1700
Wire Wire Line
	5500 1700 5500 2000
Connection ~ 5500 2000
Wire Wire Line
	4900 1700 4500 1700
Wire Wire Line
	4500 1700 4500 2000
Connection ~ 4500 2000
$Comp
L freqcounter:PIC16F18446 U1
U 1 1 5EA5A951
P 5000 2350
F 0 "U1" H 5000 2523 50  0000 C CNN
F 1 "PIC16F18446" H 5000 2430 50  0000 C CNN
F 2 "" H 5000 2350 50  0001 C CNN
F 3 "" H 5000 2350 50  0001 C CNN
	1    5000 2350
	1    0    0    -1  
$EndComp
Connection ~ 4500 2400
Connection ~ 5500 2400
$Comp
L freqcounter:TCXO U2
U 1 1 5EA5AAAC
P 4800 4000
F 0 "U2" H 5100 4258 60  0000 C CNN
F 1 "TCXO" H 5100 4148 60  0000 C CNN
F 2 "" H 5000 3950 60  0000 C CNN
F 3 "" H 5000 3950 60  0000 C CNN
	1    4800 4000
	1    0    0    -1  
$EndComp
Text GLabel 4300 4000 0    40   Input ~ 0
3.3V
$Comp
L Device:C C5
U 1 1 5EA5ADAA
P 4500 4150
F 0 "C5" H 4650 4150 50  0000 L CNN
F 1 "100nF" V 4350 4050 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 4538 4000 50  0001 C CNN
F 3 "~" H 4500 4150 50  0001 C CNN
	1    4500 4150
	-1   0    0    1   
$EndComp
Wire Wire Line
	4300 4000 4500 4000
Wire Wire Line
	4500 4000 4800 4000
Connection ~ 4500 4000
Wire Wire Line
	4500 4300 5400 4300
Wire Wire Line
	5400 4300 5400 4150
Text GLabel 4300 4300 0    40   Input ~ 0
GND
Wire Wire Line
	4500 4300 4300 4300
Connection ~ 4500 4300
Text GLabel 5800 4000 2    40   Input ~ 0
32MHz
Wire Wire Line
	5500 4000 5400 4000
$Comp
L Device:C C4
U 1 1 5EA5C572
P 5650 4000
F 0 "C4" V 5800 3950 50  0000 L CNN
F 1 "100nF" V 5500 3850 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5688 3850 50  0001 C CNN
F 3 "~" H 5650 4000 50  0001 C CNN
	1    5650 4000
	0    -1   -1   0   
$EndComp
Text GLabel 4500 2500 0    40   Input ~ 0
32MHz
NoConn ~ 4500 2600
$Comp
L Connector:Conn_01x02_Male J6
U 1 1 5EA5D5B7
P 3200 4900
F 0 "J6" H 3300 5150 50  0000 C CNN
F 1 "INPUT_A" H 3300 5050 50  0000 C CNN
F 2 "" H 3200 4900 50  0001 C CNN
F 3 "~" H 3200 4900 50  0001 C CNN
	1    3200 4900
	1    0    0    -1  
$EndComp
Text GLabel 3500 4900 2    40   Input ~ 0
INPUT_A
Wire Wire Line
	3500 4900 3400 4900
Text GLabel 3500 5000 2    40   Input ~ 0
GND
Wire Wire Line
	3500 5000 3400 5000
$Comp
L Connector:Conn_01x02_Male J7
U 1 1 5EA5DFEE
P 4000 4900
F 0 "J7" H 4100 5150 50  0000 C CNN
F 1 "INPUT_B" H 4100 5050 50  0000 C CNN
F 2 "" H 4000 4900 50  0001 C CNN
F 3 "~" H 4000 4900 50  0001 C CNN
	1    4000 4900
	1    0    0    -1  
$EndComp
Text GLabel 4300 4900 2    40   Input ~ 0
INPUT_B
Wire Wire Line
	4300 4900 4200 4900
Text GLabel 4300 5000 2    40   Input ~ 0
GND
Wire Wire Line
	4300 5000 4200 5000
$Comp
L Connector:Conn_01x02_Male J8
U 1 1 5EA5E5F1
P 4800 4900
F 0 "J8" H 4900 5150 50  0000 C CNN
F 1 "INPUT_ZCD" H 4900 5050 50  0000 C CNN
F 2 "" H 4800 4900 50  0001 C CNN
F 3 "~" H 4800 4900 50  0001 C CNN
	1    4800 4900
	1    0    0    -1  
$EndComp
Text GLabel 5100 4900 2    40   Input ~ 0
INPUT_ZCD
Wire Wire Line
	5100 4900 5000 4900
Text GLabel 5100 5000 2    40   Input ~ 0
GND
Wire Wire Line
	5100 5000 5000 5000
Wire Wire Line
	6000 5100 5900 5100
Text GLabel 6000 5200 2    40   Input ~ 0
GND
Wire Wire Line
	6000 5200 5900 5200
$Comp
L Connector:Conn_01x04_Male J9
U 1 1 5EA5F480
P 5700 5000
F 0 "J9" H 5800 5350 50  0000 C CNN
F 1 "I2C_1" H 5800 5250 50  0000 C CNN
F 2 "" H 5700 5000 50  0001 C CNN
F 3 "~" H 5700 5000 50  0001 C CNN
	1    5700 5000
	1    0    0    -1  
$EndComp
Text GLabel 6000 5100 2    40   Input ~ 0
VDD
Wire Wire Line
	6000 4900 5900 4900
Wire Wire Line
	5900 5000 6000 5000
Text GLabel 6000 4900 2    40   Input ~ 0
SCL
Text GLabel 6000 5000 2    40   Input ~ 0
SDA
Wire Wire Line
	6700 5100 6600 5100
Text GLabel 6700 5200 2    40   Input ~ 0
GND
Wire Wire Line
	6700 5200 6600 5200
$Comp
L Connector:Conn_01x04_Male J10
U 1 1 5EA63200
P 6400 5000
F 0 "J10" H 6500 5350 50  0000 C CNN
F 1 "I2C_2" H 6500 5250 50  0000 C CNN
F 2 "" H 6400 5000 50  0001 C CNN
F 3 "~" H 6400 5000 50  0001 C CNN
	1    6400 5000
	1    0    0    -1  
$EndComp
Text GLabel 6700 5100 2    40   Input ~ 0
VDD
Wire Wire Line
	6700 4900 6600 4900
Wire Wire Line
	6600 5000 6700 5000
Text GLabel 6700 4900 2    40   Input ~ 0
SCL
Text GLabel 6700 5000 2    40   Input ~ 0
SDA
Text GLabel 5500 3200 2    40   Input ~ 0
P3
Text GLabel 5500 3300 2    40   Input ~ 0
P2
Text GLabel 4500 3200 0    40   Input ~ 0
P0
Text GLabel 4500 3300 0    40   Input ~ 0
P1
Text GLabel 7400 5300 2    40   Input ~ 0
P3
Text GLabel 7400 5200 2    40   Input ~ 0
P2
Text GLabel 7400 5000 2    40   Input ~ 0
P0
Text GLabel 7400 5100 2    40   Input ~ 0
P1
Text GLabel 7400 5600 2    40   Input ~ 0
GND
Text GLabel 7400 4900 2    40   Input ~ 0
VDD
Wire Wire Line
	7400 4900 7300 4900
Wire Wire Line
	7300 5000 7400 5000
Wire Wire Line
	7400 5100 7300 5100
Wire Wire Line
	7300 5200 7400 5200
Wire Wire Line
	7400 5300 7300 5300
Wire Wire Line
	7300 5600 7400 5600
Wire Wire Line
	3200 3200 3100 3200
Connection ~ 3100 3200
$Comp
L Device:R R4
U 1 1 5EA73E5B
P 3350 3600
F 0 "R4" V 3450 3550 50  0000 L CNN
F 1 "1M" V 3350 3550 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3280 3600 50  0001 C CNN
F 3 "~" H 3350 3600 50  0001 C CNN
	1    3350 3600
	0    1    1    0   
$EndComp
Wire Wire Line
	3200 3600 3100 3600
Wire Wire Line
	3100 3600 3100 3200
Wire Wire Line
	3500 3600 3600 3600
Wire Wire Line
	3600 3600 3600 3200
Connection ~ 3600 3200
$Comp
L Connector:Conn_01x08_Male J11
U 1 1 5EA7A830
P 7100 5200
F 0 "J11" H 7200 5750 50  0000 C CNN
F 1 "PARALEL" H 7200 5650 50  0000 C CNN
F 2 "" H 7100 5200 50  0001 C CNN
F 3 "~" H 7100 5200 50  0001 C CNN
	1    7100 5200
	1    0    0    -1  
$EndComp
Text GLabel 7400 5400 2    40   Input ~ 0
ICSPDAT
Text GLabel 7400 5500 2    40   Input ~ 0
ICSPCLK
Wire Wire Line
	7400 5400 7300 5400
Wire Wire Line
	7400 5500 7300 5500
$EndSCHEMATC
