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
Text GLabel 6200 2700 0    40   Input ~ 0
MCLR
$Comp
L Device:C C2
U 1 1 5E6A67BE
P 6700 2000
F 0 "C2" V 6650 2050 50  0000 L CNN
F 1 "100nF" V 6550 1900 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 6738 1850 50  0001 C CNN
F 3 "~" H 6700 2000 50  0001 C CNN
	1    6700 2000
	0    1    1    0   
$EndComp
$Comp
L Device:R R3
U 1 1 5E71FB56
P 5450 3200
F 0 "R3" V 5550 3150 50  0000 L CNN
F 1 "1K" V 5450 3150 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 5380 3200 50  0001 C CNN
F 3 "~" H 5450 3200 50  0001 C CNN
	1    5450 3200
	0    1    1    0   
$EndComp
$Comp
L Device:C C3
U 1 1 5E71FBD7
P 4550 3200
F 0 "C3" V 4400 3150 50  0000 L CNN
F 1 "2.2nF" V 4300 3150 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 4588 3050 50  0001 C CNN
F 3 "~" H 4550 3200 50  0001 C CNN
	1    4550 3200
	0    1    -1   0   
$EndComp
Text GLabel 8000 2700 2    40   Input ~ 0
INPUT_ZCD
Text GLabel 6700 900  0    40   Input ~ 0
MCLR
Text GLabel 6700 1000 0    40   Input ~ 0
5V
Text GLabel 6700 1100 0    40   Input ~ 0
GND
Text GLabel 5500 2800 0    40   Input ~ 0
INPUT_A
Text GLabel 5500 2900 0    40   Input ~ 0
INPUT_B
$Comp
L Diode:1N4148W D1
U 1 1 5E78AE06
P 5050 3200
F 0 "D1" H 5100 3100 50  0000 R CNN
F 1 "1N4148" H 5200 3000 50  0000 R CNN
F 2 "Footprints:SOD-80_HandSolder" H 5050 3025 50  0001 C CNN
F 3 "LS4148-GS18" H 5050 3200 50  0001 C CNN
	1    5050 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	5300 3200 5200 3200
Wire Wire Line
	4700 3200 4800 3200
Text GLabel 7300 2400 2    40   Input ~ 0
GND
$Comp
L Connector:Conn_01x05_Female J1
U 1 1 5EA272A8
P 6900 1100
F 0 "J1" H 6928 1125 50  0000 L CNN
F 1 "ICSP PICKIT" H 6500 1450 50  0000 L CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x05_P2.54mm_Vertical" H 6900 1100 50  0001 C CNN
F 3 "~" H 6900 1100 50  0001 C CNN
	1    6900 1100
	1    0    0    -1  
$EndComp
Wire Wire Line
	7300 2400 7200 2400
Wire Wire Line
	7200 2400 7200 2000
Wire Wire Line
	7200 2000 6850 2000
Wire Wire Line
	6200 2400 6100 2400
Wire Wire Line
	6200 2400 6200 2000
Wire Wire Line
	6200 2000 6550 2000
Wire Wire Line
	4800 3000 4800 3200
Wire Wire Line
	4800 3000 6200 3000
Wire Wire Line
	6200 3100 5600 3100
Wire Wire Line
	5600 3100 5600 3200
Text GLabel 6700 1200 0    40   Input ~ 0
ICSPDAT
Text GLabel 6700 1300 0    40   Input ~ 0
ICSPCLK
Text GLabel 7200 2500 2    40   Input ~ 0
ICSPDAT
Text GLabel 7200 2600 2    40   Input ~ 0
ICSPCLK
$Comp
L Connector:Conn_01x08_Male J4
U 1 1 5EA433A3
P 2900 1500
F 0 "J4" H 2800 1500 50  0000 C CNN
F 1 "Arduino_Digital_2" H 2800 1950 50  0000 C CNN
F 2 "Footprints:Connector_1x08" H 2900 1500 50  0001 C CNN
F 3 "~" H 2900 1500 50  0001 C CNN
	1    2900 1500
	-1   0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x08_Male J9
U 1 1 5EA43462
P 2900 2500
F 0 "J9" H 2850 2500 50  0000 R CNN
F 1 "Arduino_Digital_1" H 3100 2950 50  0000 R CNN
F 2 "Footprints:Connector_1x08" H 2900 2500 50  0001 C CNN
F 3 "~" H 2900 2500 50  0001 C CNN
	1    2900 2500
	-1   0    0    -1  
$EndComp
$Comp
L Connector:Conn_01x06_Male J7
U 1 1 5EA4359C
P 1000 2400
F 0 "J7" H 900 2400 50  0000 R CNN
F 1 "Arduino_Analog" H 1250 2750 50  0000 R CNN
F 2 "Footprints:Connector_1x06" H 1000 2400 50  0001 C CNN
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
F 2 "Footprints:Connector_1x06" H 1000 1400 50  0001 C CNN
F 3 "~" H 1000 1400 50  0001 C CNN
	1    1000 1400
	1    0    0    -1  
$EndComp
Text Notes 1200 900  0    100  ~ 0
ARDUINO INTERFACE
Text GLabel 1400 2900 2    40   Input ~ 0
SCL
Text GLabel 1400 2800 2    40   Input ~ 0
SDA
Text GLabel 2500 3100 0    40   Input ~ 0
ARD_RX
Text GLabel 2500 3000 0    40   Input ~ 0
ARD_TX
Text GLabel 1200 1600 2    40   Input ~ 0
GND
Text GLabel 1200 1500 2    40   Input ~ 0
GND
Text GLabel 1200 1400 2    40   Input ~ 0
5V
Text GLabel 1200 1300 2    40   Input ~ 0
3.3V
Text GLabel 8000 3200 2    40   Input ~ 0
ARD_TX
Text GLabel 8000 3300 2    40   Input ~ 0
ARD_RX
Text GLabel 6200 3300 0    40   Input ~ 0
SCL
Text GLabel 6200 3200 0    40   Input ~ 0
SDA
$Comp
L Device:R R1
U 1 1 5EA4B9B0
P 7650 2700
F 0 "R1" V 7600 2850 50  0000 L CNN
F 1 "10K" V 7645 2625 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 7580 2700 50  0001 C CNN
F 3 "~" H 7650 2700 50  0001 C CNN
	1    7650 2700
	0    1    1    0   
$EndComp
Wire Wire Line
	7800 2700 8000 2700
Wire Wire Line
	7200 2700 7500 2700
$Comp
L Device:R R2
U 1 1 5EA58FDB
P 7650 3200
F 0 "R2" V 7600 3350 50  0000 L CNN
F 1 "180" V 7645 3125 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 7580 3200 50  0001 C CNN
F 3 "~" H 7650 3200 50  0001 C CNN
	1    7650 3200
	0    1    1    0   
$EndComp
Wire Wire Line
	8000 3200 7800 3200
Wire Wire Line
	7500 3200 7200 3200
$Comp
L Device:C C1
U 1 1 5EA59BE1
P 6750 1700
F 0 "C1" V 6700 1750 50  0000 L CNN
F 1 "10uF" V 6600 1600 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 6788 1550 50  0001 C CNN
F 3 "~" H 6750 1700 50  0001 C CNN
	1    6750 1700
	0    1    1    0   
$EndComp
Wire Wire Line
	6900 1700 7200 1700
Wire Wire Line
	7200 1700 7200 2000
Connection ~ 7200 2000
Wire Wire Line
	6600 1700 6200 1700
Wire Wire Line
	6200 1700 6200 2000
Connection ~ 6200 2000
$Comp
L freqcounter:PIC16F18446 U1
U 1 1 5EA5A951
P 6700 2350
F 0 "U1" H 6700 2523 50  0000 C CNN
F 1 "PIC16F18446" H 6700 2430 50  0000 C CNN
F 2 "Package_SO:SOIC-20W_7.5x12.8mm_P1.27mm" H 6700 2350 50  0001 C CNN
F 3 "PIC16F18446-I/SO" H 6700 1300 50  0000 C CNN
	1    6700 2350
	1    0    0    -1  
$EndComp
Connection ~ 6200 2400
Connection ~ 7200 2400
$Comp
L freqcounter:TCXO U2
U 1 1 5EA5AAAC
P 6500 4000
F 0 "U2" H 6800 4258 60  0000 C CNN
F 1 "TCXO" H 6800 4148 60  0000 C CNN
F 2 "Footprints:TCXO-5032" H 6700 3950 60  0001 C CNN
F 3 "ECS-TXO-25CSMV-320-AM-TR" H 6800 3600 60  0000 C CNN
	1    6500 4000
	1    0    0    -1  
$EndComp
Text GLabel 6000 4000 0    40   Input ~ 0
3.3V
$Comp
L Device:C C5
U 1 1 5EA5ADAA
P 6200 4150
F 0 "C5" H 6350 4150 50  0000 L CNN
F 1 "100nF" V 6050 4050 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 6238 4000 50  0001 C CNN
F 3 "~" H 6200 4150 50  0001 C CNN
	1    6200 4150
	-1   0    0    1   
$EndComp
Wire Wire Line
	6000 4000 6200 4000
Wire Wire Line
	6200 4000 6500 4000
Connection ~ 6200 4000
Wire Wire Line
	6200 4300 6500 4300
Wire Wire Line
	7100 4300 7100 4150
Text GLabel 6000 4300 0    40   Input ~ 0
GND
Wire Wire Line
	6200 4300 6000 4300
Connection ~ 6200 4300
Text GLabel 8200 4000 2    40   Input ~ 0
32MHz
Wire Wire Line
	7200 4000 7100 4000
$Comp
L Device:C C4
U 1 1 5EA5C572
P 7350 4000
F 0 "C4" V 7500 3950 50  0000 L CNN
F 1 "1nF" V 7200 3950 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 7388 3850 50  0001 C CNN
F 3 "~" H 7350 4000 50  0001 C CNN
	1    7350 4000
	0    -1   -1   0   
$EndComp
Text GLabel 6200 2500 0    40   Input ~ 0
32MHz
NoConn ~ 6200 2600
$Comp
L Connector:Conn_01x02_Male J10
U 1 1 5EA5D5B7
P 4900 4900
F 0 "J10" H 5000 5150 50  0000 C CNN
F 1 "INPUT_A" H 5000 5050 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 4900 4900 50  0001 C CNN
F 3 "~" H 4900 4900 50  0001 C CNN
	1    4900 4900
	1    0    0    -1  
$EndComp
Text GLabel 5200 4900 2    40   Input ~ 0
INPUT_A
Wire Wire Line
	5200 4900 5100 4900
Text GLabel 5200 5000 2    40   Input ~ 0
GND
Wire Wire Line
	5200 5000 5100 5000
$Comp
L Connector:Conn_01x02_Male J11
U 1 1 5EA5DFEE
P 5700 4900
F 0 "J11" H 5800 5150 50  0000 C CNN
F 1 "INPUT_B" H 5800 5050 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 5700 4900 50  0001 C CNN
F 3 "~" H 5700 4900 50  0001 C CNN
	1    5700 4900
	1    0    0    -1  
$EndComp
Text GLabel 6000 4900 2    40   Input ~ 0
INPUT_B
Wire Wire Line
	6000 4900 5900 4900
Text GLabel 6000 5000 2    40   Input ~ 0
GND
Wire Wire Line
	6000 5000 5900 5000
$Comp
L Connector:Conn_01x02_Male J12
U 1 1 5EA5E5F1
P 6500 4900
F 0 "J12" H 6600 5150 50  0000 C CNN
F 1 "INPUT_ZCD" H 6600 5050 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Vertical" H 6500 4900 50  0001 C CNN
F 3 "~" H 6500 4900 50  0001 C CNN
	1    6500 4900
	1    0    0    -1  
$EndComp
Text GLabel 6800 4900 2    40   Input ~ 0
INPUT_ZCD
Wire Wire Line
	6800 4900 6700 4900
Text GLabel 6800 5000 2    40   Input ~ 0
GND
Wire Wire Line
	6800 5000 6700 5000
Wire Wire Line
	7700 5100 7600 5100
Text GLabel 7700 5200 2    40   Input ~ 0
GND
Wire Wire Line
	7700 5200 7600 5200
$Comp
L Connector:Conn_01x04_Male J13
U 1 1 5EA5F480
P 7400 5000
F 0 "J13" H 7500 5350 50  0000 C CNN
F 1 "I2C_1" H 7500 5250 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 7400 5000 50  0001 C CNN
F 3 "~" H 7400 5000 50  0001 C CNN
	1    7400 5000
	1    0    0    -1  
$EndComp
Text GLabel 7700 5100 2    40   Input ~ 0
5V
Wire Wire Line
	7700 4900 7600 4900
Wire Wire Line
	7600 5000 7700 5000
Text GLabel 7700 4900 2    40   Input ~ 0
SCL
Text GLabel 7700 5000 2    40   Input ~ 0
SDA
Wire Wire Line
	8400 5100 8300 5100
Text GLabel 8400 5200 2    40   Input ~ 0
GND
Wire Wire Line
	8400 5200 8300 5200
$Comp
L Connector:Conn_01x04_Male J14
U 1 1 5EA63200
P 8100 5000
F 0 "J14" H 8200 5350 50  0000 C CNN
F 1 "I2C_2" H 8200 5250 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Vertical" H 8100 5000 50  0001 C CNN
F 3 "~" H 8100 5000 50  0001 C CNN
	1    8100 5000
	1    0    0    -1  
$EndComp
Text GLabel 8400 5100 2    40   Input ~ 0
5V
Wire Wire Line
	8400 4900 8300 4900
Wire Wire Line
	8300 5000 8400 5000
Text GLabel 8400 4900 2    40   Input ~ 0
SCL
Text GLabel 8400 5000 2    40   Input ~ 0
SDA
Text GLabel 7200 2800 2    40   Input ~ 0
D5
Text GLabel 7200 2900 2    40   Input ~ 0
D4
Text GLabel 7200 3100 2    40   Input ~ 0
RS
Text GLabel 7200 3000 2    40   Input ~ 0
E
Text GLabel 9700 5000 0    40   Input ~ 0
D7
Text GLabel 9700 5100 0    40   Input ~ 0
D6
Text GLabel 9100 5500 2    40   Input ~ 0
RS
Text GLabel 9100 5400 2    40   Input ~ 0
E
Text GLabel 9100 5600 2    40   Input ~ 0
GND
Text GLabel 9100 4900 2    40   Input ~ 0
5V
Wire Wire Line
	9100 4900 9000 4900
Wire Wire Line
	9000 5000 9100 5000
Wire Wire Line
	9100 5100 9000 5100
Wire Wire Line
	9000 5200 9100 5200
Wire Wire Line
	9100 5300 9000 5300
Wire Wire Line
	9000 5600 9100 5600
Wire Wire Line
	4900 3200 4800 3200
Connection ~ 4800 3200
$Comp
L Device:R R4
U 1 1 5EA73E5B
P 5050 3600
F 0 "R4" V 5150 3550 50  0000 L CNN
F 1 "1M" V 5050 3550 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 4980 3600 50  0001 C CNN
F 3 "~" H 5050 3600 50  0001 C CNN
	1    5050 3600
	0    1    1    0   
$EndComp
Wire Wire Line
	4900 3600 4800 3600
Wire Wire Line
	4800 3600 4800 3200
Wire Wire Line
	5200 3600 5300 3600
Wire Wire Line
	5300 3600 5300 3200
Connection ~ 5300 3200
$Comp
L Connector:Conn_01x08_Male J15
U 1 1 5EA7A830
P 8800 5200
F 0 "J15" H 8900 5750 50  0000 C CNN
F 1 "LCD" H 8900 5650 50  0000 C CNN
F 2 "Footprints:Connector_1x08" H 8800 5200 50  0001 C CNN
F 3 "~" H 8800 5200 50  0001 C CNN
	1    8800 5200
	1    0    0    -1  
$EndComp
Text GLabel 9900 5000 2    40   Input ~ 0
ICSPDAT
Text GLabel 9900 5100 2    40   Input ~ 0
ICSPCLK
Wire Wire Line
	9100 5400 9000 5400
Wire Wire Line
	9100 5500 9000 5500
Text GLabel 6100 2400 0    40   Input ~ 0
5V
Text GLabel 1200 1200 2    40   Input ~ 0
Reset
Text GLabel 1200 1700 2    40   Input ~ 0
Vin
$Comp
L Connector:Conn_01x06_Male J3
U 1 1 5EAB3405
P 1600 1400
F 0 "J3" H 1550 1350 50  0000 R CNN
F 1 "Arduino_Power" H 2100 1750 50  0000 R CNN
F 2 "Footprints:Connector_1x06" H 1600 1400 50  0001 C CNN
F 3 "~" H 1600 1400 50  0001 C CNN
	1    1600 1400
	1    0    0    -1  
$EndComp
Text GLabel 1800 1600 2    40   Input ~ 0
GND
Text GLabel 1800 1500 2    40   Input ~ 0
GND
Text GLabel 1800 1400 2    40   Input ~ 0
5V
Text GLabel 1800 1300 2    40   Input ~ 0
3.3V
Text GLabel 1800 1200 2    40   Input ~ 0
Reset
Text GLabel 1800 1700 2    40   Input ~ 0
Vin
Wire Notes Line
	3500 600  600  600 
Text GLabel 8800 4100 3    40   Input ~ 0
SCL
Text GLabel 8900 4100 3    40   Input ~ 0
SDA
$Comp
L Device:R R5
U 1 1 5EA92C67
P 8800 3950
F 0 "R5" V 8750 4100 50  0000 L CNN
F 1 "2K2" V 8795 3875 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 8730 3950 50  0001 C CNN
F 3 "~" H 8800 3950 50  0001 C CNN
	1    8800 3950
	-1   0    0    -1  
$EndComp
$Comp
L Device:R R6
U 1 1 5EA92CFB
P 8900 3950
F 0 "R6" V 8850 4100 50  0000 L CNN
F 1 "2K2" V 8895 3875 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 8830 3950 50  0001 C CNN
F 3 "~" H 8900 3950 50  0001 C CNN
	1    8900 3950
	-1   0    0    -1  
$EndComp
Text GLabel 8800 3600 1    40   Input ~ 0
5V
Wire Wire Line
	8800 3600 8800 3650
Wire Wire Line
	8800 3650 8900 3650
Wire Wire Line
	8900 3650 8900 3800
Connection ~ 8800 3650
Wire Wire Line
	8800 3650 8800 3800
$Comp
L Connector:Conn_01x06_Female J6
U 1 1 5EAB060A
P 1600 2400
F 0 "J6" H 1628 2375 50  0000 L CNN
F 1 "Analog" H 1400 2750 50  0000 L CNN
F 2 "Footprints:Connector_1x06" H 1600 2400 50  0001 C CNN
F 3 "~" H 1600 2400 50  0001 C CNN
	1    1600 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	1200 2200 1400 2200
Wire Wire Line
	1200 2300 1400 2300
Wire Wire Line
	1200 2400 1400 2400
Wire Wire Line
	1200 2500 1400 2500
Wire Wire Line
	1200 2600 1300 2600
Wire Wire Line
	1200 2700 1400 2700
Wire Wire Line
	1200 2700 1200 2900
Wire Wire Line
	1200 2900 1400 2900
Connection ~ 1200 2700
Wire Wire Line
	1400 2800 1300 2800
Wire Wire Line
	1300 2800 1300 2600
Connection ~ 1300 2600
Wire Wire Line
	1300 2600 1400 2600
Wire Wire Line
	2500 3100 2700 3100
Wire Wire Line
	2700 3100 2700 2900
Wire Wire Line
	2500 3000 2600 3000
Wire Wire Line
	2600 3000 2600 2800
Wire Wire Line
	2600 2800 2700 2800
$Comp
L Connector:Conn_01x08_Female J8
U 1 1 5EACC1E4
P 2300 2500
F 0 "J8" H 2328 2475 50  0000 L CNN
F 1 "Digital_1" H 2100 2950 50  0000 L CNN
F 2 "Footprints:Connector_1x08" H 2300 2500 50  0001 C CNN
F 3 "~" H 2300 2500 50  0001 C CNN
	1    2300 2500
	-1   0    0    -1  
$EndComp
Wire Wire Line
	2500 2900 2700 2900
Connection ~ 2700 2900
Wire Wire Line
	2600 2800 2500 2800
Connection ~ 2600 2800
Wire Wire Line
	2500 2700 2700 2700
Wire Wire Line
	2500 2600 2700 2600
Wire Wire Line
	2500 2500 2700 2500
Wire Wire Line
	2500 2400 2700 2400
Wire Wire Line
	2500 2300 2700 2300
Wire Wire Line
	2500 2200 2700 2200
Wire Notes Line
	600  600  600  3300
Wire Notes Line
	600  3300 3500 3300
Wire Notes Line
	3500 3300 3500 600 
$Comp
L Connector:Conn_01x08_Female J5
U 1 1 5EAEC8C6
P 2300 1500
F 0 "J5" H 2328 1475 50  0000 L CNN
F 1 "Digital_2" H 2100 1950 50  0000 L CNN
F 2 "Footprints:Connector_1x08" H 2300 1500 50  0001 C CNN
F 3 "~" H 2300 1500 50  0001 C CNN
	1    2300 1500
	-1   0    0    -1  
$EndComp
Wire Wire Line
	2500 1400 2700 1400
Wire Wire Line
	2500 1500 2700 1500
Wire Wire Line
	2500 1600 2700 1600
Wire Wire Line
	2500 1700 2700 1700
Wire Wire Line
	2500 1800 2700 1800
Wire Wire Line
	2500 1900 2700 1900
Wire Wire Line
	2700 1200 2500 1200
Wire Wire Line
	2700 1300 2600 1300
Text GLabel 2250 1250 0    40   Input ~ 0
GND
Wire Wire Line
	2250 1250 2600 1250
Wire Wire Line
	2600 1250 2600 1300
Connection ~ 2600 1300
Wire Wire Line
	2600 1300 2500 1300
$Comp
L Device:R R8
U 1 1 5EABD611
P 5650 2800
F 0 "R8" V 5600 2950 50  0000 L CNN
F 1 "180" V 5645 2725 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 5580 2800 50  0001 C CNN
F 3 "~" H 5650 2800 50  0001 C CNN
	1    5650 2800
	0    1    1    0   
$EndComp
$Comp
L Device:R R9
U 1 1 5EABD6A7
P 5650 2900
F 0 "R9" V 5600 3050 50  0000 L CNN
F 1 "180" V 5645 2825 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 5580 2900 50  0001 C CNN
F 3 "~" H 5650 2900 50  0001 C CNN
	1    5650 2900
	0    1    1    0   
$EndComp
Wire Wire Line
	5800 2800 6200 2800
Wire Wire Line
	5800 2900 6200 2900
$Comp
L Device:R R7
U 1 1 5EAC87AA
P 7650 3300
F 0 "R7" V 7600 3450 50  0000 L CNN
F 1 "180" V 7645 3225 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 7580 3300 50  0001 C CNN
F 3 "~" H 7650 3300 50  0001 C CNN
	1    7650 3300
	0    1    1    0   
$EndComp
Wire Wire Line
	7800 3300 8000 3300
Wire Wire Line
	7500 3300 7200 3300
Text GLabel 4400 3200 0    40   Input ~ 0
GND
$Comp
L Device:Jumper JP1
U 1 1 5EAC4D9A
P 7800 4000
F 0 "JP1" H 7800 4272 50  0000 C CNN
F 1 "Jumper" H 7800 4179 50  0000 C CNN
F 2 "Footprints:PinHeader_1x02" H 7800 4000 50  0001 C CNN
F 3 "~" H 7800 4000 50  0001 C CNN
	1    7800 4000
	1    0    0    -1  
$EndComp
Wire Wire Line
	6500 4150 6500 4300
Connection ~ 6500 4300
Wire Wire Line
	6500 4300 7100 4300
Connection ~ 7100 4300
$Comp
L Connector:Conn_01x02_Male J16
U 1 1 5EAD5B8E
P 8300 4300
F 0 "J16" H 8272 4179 50  0000 R CNN
F 1 "Ext_Clk" H 8272 4272 50  0000 R CNN
F 2 "Footprints:PinHeader_1x02" H 8300 4300 50  0001 C CNN
F 3 "~" H 8300 4300 50  0001 C CNN
	1    8300 4300
	-1   0    0    1   
$EndComp
Wire Wire Line
	8100 4200 8100 4000
Wire Wire Line
	7100 4300 8100 4300
Wire Wire Line
	8200 4000 8100 4000
Connection ~ 8100 4000
Text GLabel 9100 5200 2    40   Input ~ 0
D5
Text GLabel 9100 5300 2    40   Input ~ 0
D4
Text GLabel 9100 5000 2    40   Input ~ 0
D7
Text GLabel 9100 5100 2    40   Input ~ 0
D6
Wire Wire Line
	9700 5100 9900 5100
Wire Wire Line
	9700 5000 9900 5000
$EndSCHEMATC
