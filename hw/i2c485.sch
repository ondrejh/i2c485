EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date "15 jul 2014"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L ATMEGA328-A IC?
U 1 1 53C50111
P 4850 3700
F 0 "IC?" H 4100 4950 40  0000 L BNN
F 1 "ATMEGA328-A" H 5250 2300 40  0000 L BNN
F 2 "TQFP32" H 4850 3700 30  0000 C CIN
F 3 "" H 4850 3700 60  0000 C CNN
	1    4850 3700
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR?
U 1 1 53C50121
P 3850 2500
F 0 "#PWR?" H 3850 2600 30  0001 C CNN
F 1 "VCC" H 3850 2600 30  0000 C CNN
F 2 "" H 3850 2500 60  0000 C CNN
F 3 "" H 3850 2500 60  0000 C CNN
	1    3850 2500
	1    0    0    -1  
$EndComp
Wire Wire Line
	3950 2900 3850 2900
Wire Wire Line
	3850 2900 3850 2500
Wire Wire Line
	3950 2600 3850 2600
Connection ~ 3850 2600
Wire Wire Line
	3950 2700 3850 2700
Connection ~ 3850 2700
$Comp
L GND #PWR?
U 1 1 53C5013A
P 3850 5000
F 0 "#PWR?" H 3850 5000 30  0001 C CNN
F 1 "GND" H 3850 4930 30  0001 C CNN
F 2 "" H 3850 5000 60  0000 C CNN
F 3 "" H 3850 5000 60  0000 C CNN
	1    3850 5000
	1    0    0    -1  
$EndComp
Wire Wire Line
	3850 4700 3850 5000
Wire Wire Line
	3850 4900 3950 4900
Wire Wire Line
	3850 4700 3950 4700
Connection ~ 3850 4900
Wire Wire Line
	3950 4800 3850 4800
Connection ~ 3850 4800
$Comp
L C C?
U 1 1 53C50168
P 3850 3500
F 0 "C?" H 3850 3600 40  0000 L CNN
F 1 "C" H 3856 3415 40  0000 L CNN
F 2 "~" H 3888 3350 30  0000 C CNN
F 3 "~" H 3850 3500 60  0000 C CNN
	1    3850 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	3950 3200 3850 3200
Wire Wire Line
	3850 3200 3850 3300
$Comp
L GND #PWR?
U 1 1 53C50185
P 3850 3700
F 0 "#PWR?" H 3850 3700 30  0001 C CNN
F 1 "GND" H 3850 3630 30  0001 C CNN
F 2 "" H 3850 3700 60  0000 C CNN
F 3 "" H 3850 3700 60  0000 C CNN
	1    3850 3700
	1    0    0    -1  
$EndComp
$EndSCHEMATC
