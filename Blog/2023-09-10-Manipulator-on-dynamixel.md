---
layout: post
title:  Manipulator On Dynamixel
tags: ROS2 , C++, Robotics , InverseKinematics
description: Overview of Project Manipulator on Dynamixel and Tasks throughout Week 1-2
---


[Manipulator on Dynamixel](https://github.com/proatharv/Manipulator-on-Dynamixel-)

-Mentees

[Atharv Dubey](https://github.com/proatharv)

[Isha Nair](https://github.com/IshaNair09)

-Mentors

[Alqama Shaikh]

[Mahesh Tupe]


# MANIPULATOR ON DYNAMIXEL

Controlling and designing a 3-DOF manipulator utilizing three dynamixel motors. It will involve use of ROS for first designing, simulating and controlling the manipulator in ROS2. 
Implementing Inverse Kinematics on the model with pose-force control

## WEEK 1 

We started off with LED Blink task which we had to implement without using the sra.h header file in our code. 

**TASK CHALLENGE:** Learning how to configure GPIO pins.
- SOLUTION:
We referred the following resource  to understand the how to code to be able to configure GPIO:  https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/gpio.html

Then we were successfully able to write the code and implement it along with the help of our mentors. We ended up getting our output as shown:

![1694102746397](https://github.com/proatharv/Manipulator-on-Dynamixel-/assets/142431248/4a4d3dbd-1fd7-4525-931c-4749e99ad010)



## WEEK 2

###  BEGINNING WITH ROS

We started learning ROS2 by first learning how to setup and install it and then creating a ROS workspace.

Started our first ROS node and created a package.

In ROS 2 (Robot Operating System 2), a topic is a communication mechanism that allows nodes (software modules) to exchange data with each other in a publish-subscribe fashion.

Topics facilitate communication between different parts of a robotic system, enabling the exchange of information such as sensor data, commands, status updates, and more.

Our first ROS task was to write a simple publisher and a subscriber code in C++.

Given is the snap of our output of the task:

![Screenshot from 2023-09-07 20-57-09](https://github.com/proatharv/Manipulator-on-Dynamixel-/assets/142431248/db485688-9fa4-4639-94d6-11a8a59a865c)

![Screenshot from 2023-09-07 20-55-56](https://github.com/proatharv/Manipulator-on-Dynamixel-/assets/142431248/f8864336-5213-4520-b918-8fda371e1214)

### HARDWARE SETUP

- We then learnt about *UART Communication Protocol.*

**UART (Universal Asynchronous Receiver/Transmitter)** allows devices with varying operating frequencies to communicate effectively. 
The baud rate sets the communication speed and is stored in the devices' flash memory.

ESP32 provides three universal asynchronous receivers and transmitter (UART) ports such as UART0, UART1, and UART2 that work at 3.3V TTL level.

These three serial interfaces are hardware supported.

#### Half-Duplex Communication:
Half-duplex communication involves devices taking turns to transmit and receive data.

While one device sends data, the other listens and vice versa.

![image](https://github.com/proatharv/Manipulator-on-Dynamixel-/assets/142431248/59ba9449-5e35-480a-8c18-b8bf92c7f19b)


#### DYNAMIXEL MOTOR CONTROL 

Currently we are working on learning how to control dynamixel using UART communication with ESP32 microcontroller.

**TASK CHALLENGES:**
1. Learning to code from scratch to transmit and receive data through UART communication from esp32 to Dynamixel motor.
- Solution:
Referring this resource :  https://www.buildlog.net/blog/2020/01/dynamixel-servos-in-grbl-esp32/ and  along with help from our mentors

 *PS: Work In Progress*
 
2. Since there is only one Data pin on Dynamixel motor and two separate RX and TX pins on ESP we needed to find a solution to be able to successfully control the motor.
- Solution:
We used a multiplexer SN741 which has a select pin A/B , two separate pins where we can connect the RX and TX pins of ESP and an output pin which can be directly connected to the data pin of the motor.

Given below is just a glimpse of our hardware setup.

![](https://hackmd.io/_uploads/SkaOCNcA3.jpg)




### KEY TAKEAWAYS
-Learnt hands on soldering which was fun and interesting.

-Learnt how to read datasheet of motor and the multiplexer and navigate our way through the hardware connections.

-This week marked the beginning of ROS exploration.Grasped some core concepts of nodes packages and coding a subscriber-publisher model.


## NEXT WEEK GOALS
1. Controlling multiple dynamixel motors.
2. Learning more about ROS2 nodes and packages using python.
