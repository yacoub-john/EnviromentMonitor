# EnviromentMonitor


**Project Description:**

This project is an environment monitoring application using an Arduino grove board (Arduino Uno) and it was developed using Arduino and Java with a graphical user interface using JavaFX. It reliably captures live data from the boards sensors performs actions using elements on the board.The project’s focus was to create a user-friendly application that allows the user to test some of the supported actuators on the grove board and to allow any user to collect meaningful data from the sensors as well as interact with that boards.  

<p align="center">
  <img src="https://user-images.githubusercontent.com/89855894/152086180-2dd04897-d3d1-4073-9eff-f64e133a01a4.png" />
 </p>
 
<p align="center"><b> Figure 1: Arduino Grove Board </b></p>


**Technical Requirement/Specifications:**

The system/application is broken into four distinct sections: Breadboarding and Setup, Using the ADC, ISR versus Manual Delays, C versus Assembler each with their own specifications:
1. Breadboarding and Setup: The ATMEGA328P is breadboarded and connected to the SNAP programmer. There are also additional connections like a potentiometer connected to ADC 5 and 8 LEDs, 4 of which are connected to the lower pins of PortB and 4 are connected to the upper pins of PortD. The chip can run the program without being connected to the SNAP programmer so all it needs to run is a connection to power over USB. There are also two other LEDs setup to blink in response to a manual delay function and an interrupt service routine using delay constants based on the value of the potentiometer.

2. Using the ADC: In the program the ADC is set to receive analog signals from the potentiometer (ADC pin 5) and converts to a digital signal. When there is a physical change to the potentiometer it senses that change and converts it into an equivalent analog electrical signal. This analog signal is converted into a digital signal using the analog to digital converter (on ATMEGA328P) and the signal is then fed to the microprocessor and processes it accordingly. The processed signal has a 10-bit resolution implying that there is 2^10 = 1024 possible values. The board uses 5V as reference and so any analog value in between 0 and 5V is converted into its equivalent ADC value as shown below. The 0-5V range is divided into 2^10 = 1024 steps which is then used a value of 10-bit integer. The program itself also sets up reference voltage AVCC, the ADC clock pre-scaler and enables the ADC in free running mode where the ADC is triggered automatically at every rising edge of clock pulse.

<p align="center">
  <img src="https://user-images.githubusercontent.com/89855894/152082508-dd325519-bf9f-44c1-88de-2b6de94edecc.png" />
  <img src="https://user-images.githubusercontent.com/89855894/152082533-2ce51a99-6b35-4701-9ebf-c247b9983725.png" />
</p>

<p align="center"><b> Figure 2: ATMEGA328 ADC Configuration </b></p>

**Components List:**

In terms of the hardware used for this project the some of the parts were used for to breadboard the microprocessor and others were needed for my program these include:

*	ATMEGA328P: 8-bit microprocessor used to run the program; the parts associated with breadboarding the microprocessor include:

    *	Breadboard: Used to put together all the parts for the microprocessor.

    *	16 MHz Crystal: Used as a clock for the microprocessor keeping time to prevent processes from jumping ahead or lagging.

    *	2x 39pF Load Capacitor: Used to ground the crystal.

    *	Button: Used to ground pin 1 of the microprocessor to reset it.

    *	Voltage Regulator: Used to provide power (5V) to circuit using USB. 
  

*	SNAP Programmer: Used as a debugger/programmer to upload programs from MPLABX to ATMEGA328.

*	8x Blue 3mm LED: Used to show the 8-bit value of the potentiometer where each LED represents a bit.

*	Potentiometer: Analog source used to control the frequency of an LED using a manual delay.

*	Red 3mm LED: Blinks at the frequency of a manual delay based on the value of the potentiometer.

*	Blue 3mm LED: Blinks at the frequency of a timer, turned on and off by an interrupt service routine

<p align="center">
  <img src="https://user-images.githubusercontent.com/89855894/152083078-88a2d1dd-e894-4d34-b058-8bde5f8fb9a8.png" />
</p>

<p align="center"><b> Figure 3: Fritzing Breadboard Setup </b></p>

**Testing:**

In terms of checking the disassembled code I disassembled sections of my code in both compiler explorer and MPLABX as a method of checking the disassembly process in compiler explorer and selecting the correct compiler (AVR gcc vs Arduino Uno.) The disassembled code for my delay function can be seen in Figure 4 where it is disassembled using compiler explorer and MPLABX. 


<p align="center">
  <img src="https://user-images.githubusercontent.com/89855894/152083233-98de7d08-f3d7-4577-a671-dd412a520d60.png" />
</p>

<p align="center"><b> Figure 4: Disassembly of Delay Function  </b></p>

**Conclusion:**

Overall, my goal was to develop a project that uses the ADC on the ATMEGA328P in unison with timers and a ISR routine to test the performance of mixing C and assembler. This project gave me a chance to apply and expand the my knowledge on the AVR architecture.I have plans to expand my project use the analog to digital converter, timers and interrupt service routines using the MIPS architecture.



