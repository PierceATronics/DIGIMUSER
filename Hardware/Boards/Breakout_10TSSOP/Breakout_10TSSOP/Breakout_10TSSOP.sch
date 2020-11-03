EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A 11000 8500
encoding utf-8
Sheet 1 1
Title "10TSSOP Breakout Board"
Date "2020-11-02"
Rev "A"
Comp "Designer: David Pierce Walker-Howell"
Comment1 "Senior Desing FA20/SP21"
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Connector:Conn_01x05_Male J1
U 1 1 5FA0D542
P 4400 4275
F 0 "J1" H 3700 4375 50  0000 R CNN
F 1 "Conn_01x05_Male" H 4150 4500 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x05_P2.54mm_Vertical" H 4400 4275 50  0001 C CNN
F 3 "~" H 4400 4275 50  0001 C CNN
	1    4400 4275
	1    0    0    1   
$EndComp
$Comp
L Connector:Conn_01x05_Male J2
U 1 1 5FA29B9C
P 6000 4275
F 0 "J2" H 5300 4375 50  0000 R CNN
F 1 "Conn_01x05_Male" H 5750 4500 50  0000 R CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x05_P2.54mm_Vertical" H 6000 4275 50  0001 C CNN
F 3 "~" H 6000 4275 50  0001 C CNN
	1    6000 4275
	-1   0    0    1   
$EndComp
$Comp
L CS5343CZZ:CS5343-CZZ U1
U 1 1 5FA0B152
P 6975 2350
F 0 "U1" H 8175 2738 60  0000 C CNN
F 1 "CS5343-CZZ" H 8175 2632 60  0000 C CNN
F 2 "CS5343CZZ:CS5343-CZZ" H 8175 2590 60  0001 C CNN
F 3 "" H 6975 2350 60  0000 C CNN
	1    6975 2350
	-1   0    0    -1  
$EndComp
Text GLabel 3975 3025 0    50   UnSpc ~ 0
1
Text GLabel 3975 2900 0    50   UnSpc ~ 0
2
Text GLabel 3975 2775 0    50   UnSpc ~ 0
3
Text GLabel 3975 2650 0    50   UnSpc ~ 0
5
Text GLabel 3975 2525 0    50   UnSpc ~ 0
7
Text GLabel 3975 2400 0    50   UnSpc ~ 0
9
Text GLabel 3975 2275 0    50   UnSpc ~ 0
10
Text GLabel 7300 2325 2    50   UnSpc ~ 0
4
Text GLabel 7300 2450 2    50   UnSpc ~ 0
6
Text GLabel 7300 2575 2    50   UnSpc ~ 0
8
Wire Wire Line
	6975 2450 7300 2450
Wire Wire Line
	6975 2350 7075 2350
Wire Wire Line
	7075 2350 7075 2325
Wire Wire Line
	7075 2325 7300 2325
Wire Wire Line
	6975 2550 7075 2550
Wire Wire Line
	7075 2550 7075 2575
Wire Wire Line
	7075 2575 7300 2575
Wire Wire Line
	3975 2650 4575 2650
Wire Wire Line
	4575 2550 4025 2550
Wire Wire Line
	4025 2550 4025 2525
Wire Wire Line
	4025 2525 3975 2525
Wire Wire Line
	4575 2450 4025 2450
Wire Wire Line
	4025 2450 4025 2400
Wire Wire Line
	4025 2400 3975 2400
Wire Wire Line
	4575 2350 4025 2350
Wire Wire Line
	4025 2350 4025 2275
Wire Wire Line
	4025 2275 3975 2275
Wire Wire Line
	4575 2750 4025 2750
Wire Wire Line
	4025 2750 4025 2775
Wire Wire Line
	4025 2775 3975 2775
Wire Wire Line
	4575 2850 4025 2850
Wire Wire Line
	4025 2850 4025 2900
Wire Wire Line
	4025 2900 3975 2900
Wire Wire Line
	4575 2950 4025 2950
Wire Wire Line
	4025 2950 4025 3025
Wire Wire Line
	4025 3025 3975 3025
Text GLabel 4775 4025 2    50   UnSpc ~ 0
1
Text GLabel 4775 4150 2    50   UnSpc ~ 0
2
Text GLabel 4775 4275 2    50   UnSpc ~ 0
3
Text GLabel 4775 4400 2    50   UnSpc ~ 0
4
Text GLabel 4775 4525 2    50   UnSpc ~ 0
5
Text GLabel 5625 4025 0    50   UnSpc ~ 0
10
Text GLabel 5625 4150 0    50   UnSpc ~ 0
9
Text GLabel 5625 4275 0    50   UnSpc ~ 0
8
Text GLabel 5625 4400 0    50   UnSpc ~ 0
7
Text GLabel 5625 4525 0    50   UnSpc ~ 0
6
Wire Wire Line
	4600 4275 4775 4275
Wire Wire Line
	4600 4075 4650 4075
Wire Wire Line
	4650 4075 4650 4025
Wire Wire Line
	4650 4025 4775 4025
Wire Wire Line
	4600 4175 4650 4175
Wire Wire Line
	4650 4175 4650 4150
Wire Wire Line
	4650 4150 4775 4150
Wire Wire Line
	4600 4375 4650 4375
Wire Wire Line
	4650 4375 4650 4400
Wire Wire Line
	4650 4400 4775 4400
Wire Wire Line
	4600 4475 4650 4475
Wire Wire Line
	4650 4475 4650 4525
Wire Wire Line
	4650 4525 4775 4525
Wire Wire Line
	5625 4025 5750 4025
Wire Wire Line
	5750 4025 5750 4075
Wire Wire Line
	5750 4075 5800 4075
Wire Wire Line
	5625 4150 5750 4150
Wire Wire Line
	5750 4150 5750 4175
Wire Wire Line
	5750 4175 5800 4175
Wire Wire Line
	5625 4275 5800 4275
Wire Wire Line
	5800 4375 5750 4375
Wire Wire Line
	5750 4375 5750 4400
Wire Wire Line
	5750 4400 5625 4400
Wire Wire Line
	5800 4475 5750 4475
Wire Wire Line
	5750 4475 5750 4525
Wire Wire Line
	5750 4525 5625 4525
$EndSCHEMATC
