EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Interface_UART:MAX232 U2
U 1 1 6086BD1E
P 5500 3700
F 0 "U2" H 4950 4750 50  0000 C CNN
F 1 "MAX232" H 5950 4750 50  0000 C CNN
F 2 "Package_DIP:DIP-16_W7.62mm" H 5550 2650 50  0001 L CNN
F 3 "http://www.ti.com/lit/ds/symlink/max232.pdf" H 5500 3800 50  0001 C CNN
	1    5500 3700
	1    0    0    -1  
$EndComp
$Comp
L power:Earth #PWR03
U 1 1 6086DCFB
P 2600 4300
F 0 "#PWR03" H 2600 4050 50  0001 C CNN
F 1 "Earth" H 2600 4150 50  0001 C CNN
F 2 "" H 2600 4300 50  0001 C CNN
F 3 "~" H 2600 4300 50  0001 C CNN
	1    2600 4300
	1    0    0    -1  
$EndComp
$Comp
L power:Earth #PWR05
U 1 1 6086E329
P 5500 4900
F 0 "#PWR05" H 5500 4650 50  0001 C CNN
F 1 "Earth" H 5500 4750 50  0001 C CNN
F 2 "" H 5500 4900 50  0001 C CNN
F 3 "~" H 5500 4900 50  0001 C CNN
	1    5500 4900
	1    0    0    -1  
$EndComp
Text GLabel 2600 3100 1    50   Input ~ 0
5v
Text GLabel 5500 2200 1    50   Input ~ 0
5v
$Comp
L Device:CP C3
U 1 1 60870F52
P 4600 2950
F 0 "C3" H 4718 2996 50  0000 L CNN
F 1 "1uF" H 4718 2905 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D4.0mm_P2.00mm" H 4638 2800 50  0001 C CNN
F 3 "~" H 4600 2950 50  0001 C CNN
	1    4600 2950
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C4
U 1 1 60871443
P 6400 2950
F 0 "C4" H 6518 2996 50  0000 L CNN
F 1 "1uF" H 6518 2905 50  0000 L CNN
F 2 "Capacitor_THT:CP_Radial_D4.0mm_P2.00mm" H 6438 2800 50  0001 C CNN
F 3 "~" H 6400 2950 50  0001 C CNN
	1    6400 2950
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C5
U 1 1 60871D2E
P 6550 3600
F 0 "C5" V 6600 3500 50  0000 C CNN
F 1 "1uF" V 6600 3750 50  0000 C CNN
F 2 "Capacitor_THT:CP_Radial_D4.0mm_P2.00mm" H 6588 3450 50  0001 C CNN
F 3 "~" H 6550 3600 50  0001 C CNN
	1    6550 3600
	0    1    1    0   
$EndComp
$Comp
L Device:CP C1
U 1 1 60875E3C
P 5250 2350
F 0 "C1" V 4995 2350 50  0000 C CNN
F 1 "1uF" V 5086 2350 50  0000 C CNN
F 2 "Capacitor_THT:CP_Radial_D4.0mm_P2.00mm" H 5288 2200 50  0001 C CNN
F 3 "~" H 5250 2350 50  0001 C CNN
	1    5250 2350
	0    1    1    0   
$EndComp
Wire Wire Line
	5400 2350 5500 2350
Connection ~ 5500 2350
Wire Wire Line
	5500 2350 5500 2500
Wire Wire Line
	5500 2200 5500 2350
$Comp
L power:Earth #PWR01
U 1 1 60877566
P 5050 2400
F 0 "#PWR01" H 5050 2150 50  0001 C CNN
F 1 "Earth" H 5050 2250 50  0001 C CNN
F 2 "" H 5050 2400 50  0001 C CNN
F 3 "~" H 5050 2400 50  0001 C CNN
	1    5050 2400
	1    0    0    -1  
$EndComp
$Comp
L power:Earth #PWR02
U 1 1 60877C0E
P 6800 3650
F 0 "#PWR02" H 6800 3400 50  0001 C CNN
F 1 "Earth" H 6800 3500 50  0001 C CNN
F 2 "" H 6800 3650 50  0001 C CNN
F 3 "~" H 6800 3650 50  0001 C CNN
	1    6800 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	5050 2400 5050 2350
Wire Wire Line
	5050 2350 5100 2350
Wire Wire Line
	6300 2800 6400 2800
Wire Wire Line
	6300 3100 6400 3100
Wire Wire Line
	6300 3600 6400 3600
Wire Wire Line
	6700 3600 6800 3600
Wire Wire Line
	6800 3600 6800 3650
Wire Wire Line
	4600 2800 4700 2800
Wire Wire Line
	4700 3100 4600 3100
$Comp
L Switch:SW_SPST SW1
U 1 1 6087F671
P 3750 4000
F 0 "SW1" V 3796 3912 50  0000 R CNN
F 1 "Case Switch" V 3705 3912 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Horizontal" H 3750 4000 50  0001 C CNN
F 3 "~" H 3750 4000 50  0001 C CNN
	1    3750 4000
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3200 3700 3350 3700
$Comp
L power:Earth #PWR04
U 1 1 60883D0D
P 3750 4350
F 0 "#PWR04" H 3750 4100 50  0001 C CNN
F 1 "Earth" H 3750 4200 50  0001 C CNN
F 2 "" H 3750 4350 50  0001 C CNN
F 3 "~" H 3750 4350 50  0001 C CNN
	1    3750 4350
	1    0    0    -1  
$EndComp
Wire Wire Line
	3750 4350 3750 4200
Wire Wire Line
	3200 3400 4400 3400
Wire Wire Line
	4400 3400 4400 4200
Wire Wire Line
	4400 4200 4700 4200
Wire Wire Line
	4500 3500 4500 3800
Wire Wire Line
	4500 3800 4700 3800
Wire Wire Line
	3200 3500 4500 3500
$Comp
L Connector_Generic:Conn_02x05_Odd_Even J1
U 1 1 609B7777
P 7350 4250
F 0 "J1" V 7500 4600 50  0000 C CNN
F 1 "JCOM1" V 7300 4650 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x03_P2.54mm_Horizontal" H 7350 4250 50  0001 C CNN
F 3 "~" H 7350 4250 50  0001 C CNN
	1    7350 4250
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6700 4200 6300 4200
$Comp
L power:Earth #PWR06
U 1 1 609C5325
P 7350 4450
F 0 "#PWR06" H 7350 4200 50  0001 C CNN
F 1 "Earth" H 7350 4300 50  0001 C CNN
F 2 "" H 7350 4450 50  0001 C CNN
F 3 "~" H 7350 4450 50  0001 C CNN
	1    7350 4450
	1    0    0    -1  
$EndComp
Wire Wire Line
	6300 3800 7150 3800
Wire Wire Line
	7150 3800 7150 3950
Wire Wire Line
	7250 4450 7250 4600
Wire Wire Line
	7250 4600 6700 4600
Wire Wire Line
	6700 4600 6700 4200
$Comp
L Connector_Generic:Conn_01x04 J2
U 1 1 609C9362
P 3650 2700
F 0 "J2" H 3730 2692 50  0000 L CNN
F 1 "Molex 8981-P04" H 3730 2601 50  0000 L CNN
F 2 "xess:xess-MOLEX-8981-04P" H 3650 2700 50  0001 C CNN
F 3 "~" H 3650 2700 50  0001 C CNN
	1    3650 2700
	-1   0    0    1   
$EndComp
$Comp
L power:Earth #PWR08
U 1 1 609CBF30
P 3950 2900
F 0 "#PWR08" H 3950 2650 50  0001 C CNN
F 1 "Earth" H 3950 2750 50  0001 C CNN
F 2 "" H 3950 2900 50  0001 C CNN
F 3 "~" H 3950 2900 50  0001 C CNN
	1    3950 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	3850 2700 3950 2700
Wire Wire Line
	3950 2700 3950 2600
Wire Wire Line
	3850 2600 3950 2600
$Comp
L Device:R R1
U 1 1 609D1F16
P 3500 3700
F 0 "R1" V 3400 3600 50  0000 C CNN
F 1 "10k" V 3500 3700 50  0000 C CNN
F 2 "Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal" V 3430 3700 50  0001 C CNN
F 3 "~" H 3500 3700 50  0001 C CNN
	1    3500 3700
	0    1    1    0   
$EndComp
Wire Wire Line
	3650 3700 3750 3700
Wire Wire Line
	3750 3700 3750 3800
NoConn ~ 6300 4400
NoConn ~ 6300 4000
NoConn ~ 4700 4000
NoConn ~ 4700 4400
$Comp
L power:Earth #PWR07
U 1 1 609FAB3C
P 3250 3950
F 0 "#PWR07" H 3250 3700 50  0001 C CNN
F 1 "Earth" H 3250 3800 50  0001 C CNN
F 2 "" H 3250 3950 50  0001 C CNN
F 3 "~" H 3250 3950 50  0001 C CNN
	1    3250 3950
	1    0    0    -1  
$EndComp
Wire Wire Line
	3250 3950 3250 3900
Wire Wire Line
	3250 3600 3200 3600
Wire Wire Line
	3200 3800 3250 3800
Connection ~ 3250 3800
Wire Wire Line
	3250 3800 3250 3600
Wire Wire Line
	3250 3900 3200 3900
Connection ~ 3250 3900
Wire Wire Line
	3250 3900 3250 3800
Text GLabel 3850 2500 2    50   Output ~ 0
5v
Connection ~ 3950 2700
Wire Wire Line
	3950 2700 3950 2900
NoConn ~ 3850 2800
$Comp
L MCU_Microchip_ATtiny:ATtiny85-20PU U1
U 1 1 6086B104
P 2600 3700
F 0 "U1" H 2200 4250 50  0000 R CNN
F 1 "ATtiny85-20PU" H 3250 4250 50  0000 R CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 2600 3700 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/atmel-2586-avr-8-bit-microcontroller-attiny25-attiny45-attiny85_datasheet.pdf" H 2600 3700 50  0001 C CNN
	1    2600 3700
	1    0    0    -1  
$EndComp
$Comp
L Device:CP C2
U 1 1 60A1D9D1
P 6550 3300
F 0 "C2" V 6600 3400 50  0000 C CNN
F 1 "1uF" V 6600 3150 50  0000 C CNN
F 2 "Capacitor_THT:CP_Radial_D4.0mm_P2.00mm" H 6588 3150 50  0001 C CNN
F 3 "~" H 6550 3300 50  0001 C CNN
	1    6550 3300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	6700 3300 6800 3300
Wire Wire Line
	6800 3300 6800 3600
Connection ~ 6800 3600
Wire Wire Line
	6400 3300 6300 3300
$EndSCHEMATC
