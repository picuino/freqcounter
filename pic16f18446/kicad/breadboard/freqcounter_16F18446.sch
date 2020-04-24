EESchema Schematic File Version 4
LIBS:freqcounter_16F18446-cache
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
L Device:Crystal Y1
U 1 1 5E6A2A06
P 3900 2450
F 0 "Y1" H 3750 2550 50  0000 C CNN
F 1 "Crystal 8MHz" H 3900 2628 50  0000 C CNN
F 2 "Crystal:Crystal_HC18-U_Vertical" H 3900 2450 50  0001 C CNN
F 3 "~" H 3900 2450 50  0001 C CNN
	1    3900 2450
	1    0    0    -1  
$EndComp
$Comp
L Device:C C5
U 1 1 5E6A67BE
P 5000 2000
F 0 "C5" V 4950 2050 50  0000 L CNN
F 1 "100nF" V 4850 1900 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5038 1850 50  0001 C CNN
F 3 "~" H 5000 2000 50  0001 C CNN
	1    5000 2000
	0    1    1    0   
$EndComp
$Comp
L Device:R R1
U 1 1 5E71FB56
P 3650 3200
F 0 "R1" V 3750 3150 50  0000 L CNN
F 1 "1K" V 3650 3150 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 3580 3200 50  0001 C CNN
F 3 "~" H 3650 3200 50  0001 C CNN
	1    3650 3200
	0    1    1    0   
$EndComp
$Comp
L Device:C C1
U 1 1 5E71FBD7
P 2850 3200
F 0 "C1" V 2700 3150 50  0000 L CNN
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
Text GLabel 6900 2700 2    40   Input ~ 0
INPUT_ZCD
$Comp
L PIC16F18446:PIC16F18446 U1
U 1 1 5E723A55
P 5000 2350
F 0 "U1" H 5000 2523 50  0000 C CNN
F 1 "PIC16F18446" H 5000 2430 50  0000 C CNN
F 2 "Package_SO:SOIC-20W_7.5x12.8mm_P1.27mm" H 5000 2350 50  0001 C CNN
F 3 "" H 5000 2350 50  0001 C CNN
	1    5000 2350
	1    0    0    -1  
$EndComp
Text GLabel 6450 2200 0    40   Input ~ 0
MCLR
Text GLabel 6450 2300 0    40   Input ~ 0
VDD
Text GLabel 6450 2400 0    40   Input ~ 0
GND
Text GLabel 3600 2800 0    40   Input ~ 0
INPUT_A
Text GLabel 3600 2900 0    40   Input ~ 0
INPUT_B
$Comp
L Diode:1N4148W D1
U 1 1 5E78AE06
P 3250 3200
F 0 "D1" H 3300 3100 50  0000 R CNN
F 1 "1N4148" H 3400 3000 50  0000 R CNN
F 2 "Diode_SMD:D_SOD-123" H 3250 3025 50  0001 C CNN
F 3 "https://www.vishay.com/docs/85748/1n4148w.pdf" H 3250 3200 50  0001 C CNN
	1    3250 3200
	1    0    0    -1  
$EndComp
$Comp
L Device:R R11
U 1 1 5E8D7C95
P 5750 2800
F 0 "R11" V 5700 2950 50  0000 L CNN
F 1 "180" V 5745 2725 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 5680 2800 50  0001 C CNN
F 3 "~" H 5750 2800 50  0001 C CNN
	1    5750 2800
	0    1    1    0   
$EndComp
$Comp
L Device:R R12
U 1 1 5E8DA958
P 5750 2900
F 0 "R12" V 5700 3050 50  0000 L CNN
F 1 "180" V 5745 2825 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" V 5680 2900 50  0001 C CNN
F 3 "~" H 5750 2900 50  0001 C CNN
	1    5750 2900
	0    1    1    0   
$EndComp
Wire Wire Line
	3500 3200 3400 3200
Wire Wire Line
	3000 3200 3100 3200
Wire Wire Line
	3750 2600 3750 2450
$Comp
L Connector:Conn_01x04_Female J2
U 1 1 5EA1E8B8
P 6650 2900
F 0 "J2" H 6678 2875 50  0000 L CNN
F 1 "USB-Serial" H 6678 2782 50  0000 L CNN
F 2 "" H 6650 2900 50  0001 C CNN
F 3 "~" H 6650 2900 50  0001 C CNN
	1    6650 2900
	1    0    0    -1  
$EndComp
Text GLabel 5600 2400 2    40   Input ~ 0
GND
Text GLabel 6450 3100 0    40   Input ~ 0
GND
Text GLabel 6450 3000 0    40   Input ~ 0
VDD
$Comp
L Connector:Conn_01x05_Female J1
U 1 1 5EA272A8
P 6650 2400
F 0 "J1" H 6678 2425 50  0000 L CNN
F 1 "ICSP PICKIT" H 6678 2332 50  0000 L CNN
F 2 "" H 6650 2400 50  0001 C CNN
F 3 "~" H 6650 2400 50  0001 C CNN
	1    6650 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	5600 2400 5500 2400
Wire Wire Line
	5500 2400 5500 2000
Wire Wire Line
	5500 2000 5150 2000
Connection ~ 5500 2400
Wire Wire Line
	4500 2400 4400 2400
Wire Wire Line
	4500 2400 4500 2000
Wire Wire Line
	4500 2000 4850 2000
Connection ~ 4500 2400
Wire Wire Line
	3100 3000 3100 3200
Connection ~ 3100 3200
Wire Wire Line
	3100 3000 4500 3000
Wire Wire Line
	4500 3100 3900 3100
Wire Wire Line
	3900 3100 3900 3200
Wire Wire Line
	3900 3200 3800 3200
Wire Wire Line
	3600 2800 4500 2800
Wire Wire Line
	4500 2900 3600 2900
Wire Wire Line
	5500 2800 5600 2800
Wire Wire Line
	5500 2900 5600 2900
Text GLabel 6100 2800 2    40   Input ~ 0
TX
Wire Wire Line
	6100 2800 5900 2800
Text GLabel 6100 2900 2    40   Input ~ 0
RX
Wire Wire Line
	6100 2900 5900 2900
Text GLabel 6450 2800 0    40   Input ~ 0
TX
Text GLabel 6450 2900 0    40   Input ~ 0
RX
Text GLabel 6450 2500 0    40   Input ~ 0
ICSPDAT
Text GLabel 6450 2600 0    40   Input ~ 0
ICSPCLK
Text GLabel 5500 2500 2    40   Input ~ 0
ICSPDAT
Text GLabel 5500 2600 2    40   Input ~ 0
ICSPCLK
Wire Wire Line
	5500 2700 6900 2700
$Comp
L LCD_DISPLAY_16X2:LCD_DISPLAY_16X2 P1
U 1 1 5EA1FBB9
P 4200 4650
F 0 "P1" H 6533 4550 50  0000 L CNN
F 1 "LCD_DISPLAY_16X2" H 6533 4457 50  0000 L CNN
F 2 "SIL-16" H 6533 4364 50  0000 L CNN
F 3 "" H 4200 4650 50  0001 C CNN
	1    4200 4650
	1    0    0    -1  
$EndComp
Text GLabel 5500 3000 2    40   Input ~ 0
LCD_RS
Text GLabel 5500 3100 2    40   Input ~ 0
LCD_E
Text GLabel 4700 4400 1    40   Input ~ 0
LCD_E
Text GLabel 4500 4400 1    40   Input ~ 0
LCD_RS
Wire Wire Line
	4600 4400 4600 4100
Wire Wire Line
	4600 4100 4800 4100
Wire Wire Line
	4800 4100 4800 4400
Wire Wire Line
	4800 4100 4900 4100
Wire Wire Line
	4900 4100 4900 4400
Connection ~ 4800 4100
Wire Wire Line
	4900 4100 5000 4100
Wire Wire Line
	5000 4100 5000 4400
Connection ~ 4900 4100
Wire Wire Line
	5000 4100 5100 4100
Wire Wire Line
	5100 4100 5100 4400
Connection ~ 5000 4100
Text GLabel 4600 4000 1    40   Input ~ 0
GND
Wire Wire Line
	4600 4100 4600 4000
Connection ~ 4600 4100
Wire Wire Line
	4600 4100 4400 4100
Wire Wire Line
	4400 4100 4400 4400
Wire Wire Line
	5100 4100 5700 4100
Wire Wire Line
	5700 4100 5700 4400
Connection ~ 5100 4100
Text GLabel 5500 3200 2    40   Input ~ 0
LCD_D4
Text GLabel 5500 3300 2    40   Input ~ 0
LCD_D5
Text GLabel 4500 3300 0    40   Input ~ 0
LCD_D7
Text GLabel 4500 3200 0    40   Input ~ 0
LCD_D6
Text GLabel 5200 4400 1    40   Input ~ 0
LCD_D4
Text GLabel 5300 4400 1    40   Input ~ 0
LCD_D5
Text GLabel 5500 4400 1    40   Input ~ 0
LCD_D7
Text GLabel 5400 4400 1    40   Input ~ 0
LCD_D6
Wire Wire Line
	4400 4100 4200 4100
Wire Wire Line
	4200 4100 4200 4400
Connection ~ 4400 4100
Text GLabel 4300 4400 1    40   Input ~ 0
VDD
Wire Wire Line
	3750 2600 4500 2600
Wire Wire Line
	4050 2450 4050 2500
Wire Wire Line
	4050 2500 4500 2500
$EndSCHEMATC