# Environment Monitoring and Graphing Application


**Project Description:**

This project is an environment monitoring application using an Arduino grove board (Arduino Uno) and it was developed using Arduino and Java with a graphical user interface using JavaFX. It reliably captures live data from the boards sensors performs actions using elements on the board.The project’s focus was to create a user-friendly application that allows the user to test some of the supported actuators on the grove board and to allow any user to collect meaningful data from the sensors as well as interact with that boards.  

<p align="center">
  <img src="https://user-images.githubusercontent.com/89855894/152086180-2dd04897-d3d1-4073-9eff-f64e133a01a4.png" />
 </p>
 
<p align="center"><b> Figure 1: Arduino Grove Board </b></p>


**Technical Requirement/Specifications:** 
The system/application is broken into three distinct sections: Arduino only reading values, Java and Arduino reading values and preforming actions, and Java and Arduino graphing each with their own specifications:  

1.	Arduino Only: With the arduino running on its own it would be constantly looping and checking the values coming from the sound sensor, light sensor, and temperature sensor and would then print those values with their respective identifier on the display. These updates (time between each loop) are also delayed to not check too often where it would be hard to read the value from the display but also to make sure that the data is accurate. Between each update I added a delay of 10 seconds to make sure that the value on the display is accurate and is easy to read. 


2.	Arduino and Java Actions: The Java program would allow the users to manually turn on elements on the board and to update the information manually by pressing the respective button in the actions tab of the program. I used the jSerialComm and JavaFX APIs in my program to allow the user to manually turn on and off the red led, green led, buzzer and mosfet using buttons in the actions tab in my program. When one of the buttons is pressed it would send a value to the arduino program (in this case it would send a value between 110-115) using the serial stream. I also identified the port and stream speed in Java and the stream speed in Arduino. The values would be received in the arduino program (in ASCII) and based on the values received the arduino would then send a signal out to turn on or off the corresponding components on the board. A similar method was used to update the values on the display where the when the user would click a button the presses would be bound and would send a value to the stream (121-123) and then the arduino would be able to read the values from the stream and update the display with those values. 


3.	Arduino and Java Graphing: For the graphing of the different sensor values, radio buttons were used to represent each option and when a radio button is selected a massage would be show in the console and the first value in an array would be changed based on the selection. Then when the update button is pressed, it is bound to update the labels on the graph to reflect the option that is selected. Then once the graph button is pressed it would send values (131-135) to the arduino program based on the first value of the array that was used for the selections. Then on the arduino side the arduino would receive the values (in ASCII) and would change the value of a variable. Once that variable is changed the loop that is always checking for its value would start sending out values that correspond to sensor that was selected. However, to graph a user must also choose a duration using a slider or textbox. Once they press the graph button it disables the slider and textbox starts a timer with the value of the slider which would then send the value of the timer to the arduino via a value to output stream and this value would be printed on the display. And so, to graph the user would select the sensor they want using a radio button and then they would press the update button to update the labels of the graph and then the user selects the duration value and then they would press the graph button. The timer would start at the duration selected and the values would be graphed on the graph on the GUI until the timer reaches one where the graph would stop graphing and the red led would turn on. The user could then use another sensor by clearing the plot and choosing another sensor, update button, duration, and then the graph button.



**Components List:**

For the hardware I mainly used the Arduino board with two extra sensors, overall, all of the components I used in this project are as follows (from Seeed Studio documentation of the board): 
*	Red LED: Simple LED module that is turned on and off.
*	Green LED: Simple LED built into the board that is turned on and off.
*	Piezo Buzzer: Used to generate basic beeps and tones upon command from the Java program.
*	Display: Used to display the values from the sensors on the board.
*	Light Sensor: Detects surrounding light intensity. 
*	Sound Sensor: Detects surrounding sound intensity.
*	DHT22 Humidity Sensor: Detects surrounding humidity values.
*	(External) LM35 Temperature Sensor: Detects surrounding temperature values.
*	(External) Moisture Sensor: Detects the moisture values of where it is placed.
*	(External) Mosfet: Used with a combination of a battery pack so that when it is given a signal it would turn on a pump.


<p align="center">
  <img src="https://user-images.githubusercontent.com/89855894/152086466-2db5153a-690e-4c28-9edd-45f41444ae92.png" />
</p>

<p align="center"><b> Figure 2: Components Diagram </b></p>

**Testing:**

In the testing part of my project, I made sure that I was getting precise data as I ran live plots multiple times under one condition and then changed the condition and compared the data and made sure that I could see the difference between each case. I tested all the components of my application by running small unit tests on the individual components of the application and ensured that I was getting expected results using specific input data like playing music with a specific noise level and comparing the graphed data to the expected results (picture below for reference).  This could also be seen from the included pictures as I ran both my program and a phone application at the same and the spikes occur at the same relative time the only difference is one shows the ADC values received vs the actual decibel values from the phone application.


<p align="center">
  <img src="https://user-images.githubusercontent.com/89855894/152083233-98de7d08-f3d7-4577-a671-dd412a520d60.png" />
</p>

![image](https://user-images.githubusercontent.com/89855894/152086631-78b4afe9-3784-40b1-9d08-46b99a0dd118.png)


<p align="center"><b> Figure 4: Disassembly of Delay Function  </b></p>



**Conclusion:**

Overall, my goal was to develop a project that uses the ADC on the ATMEGA328P in unison with timers and a ISR routine to test the performance of mixing C and assembler. This project gave me a chance to apply and expand the my knowledge on the AVR architecture.I have plans to expand my project use the analog to digital converter, timers and interrupt service routines using the MIPS architecture.



