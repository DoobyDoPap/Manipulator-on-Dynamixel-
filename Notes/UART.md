# Universal Asynchronous Receive Transmit ( UART )
## Introduction to UART
UART (Universal Asynchronous Receive Transmit) is a simple communication protocol between devices.

It enables the exchange of data using two essential wires: transmission line and receiving line.

Data is sent digitally, bit by bit, from one device to another.

## Advantage of UART
*Cross-Speed Communication:*

UART allows devices with varying operating frequencies to communicate effectively.
The "baud rate" sets the communication speed and is stored in the devices' flash memory.

**Baud Rate**: Baud rate refers to the rate at which data bits are transmitted or received over a communication channel.

Baud rate is typically measured in bits per second (bps) and represents the speed at which information is exchanged between devices.

It is a fundamental parameter in setting up and configuring communication protocols such as UART, SPI, I2C, and more.

In order for the data transfer to be a success both the transmitting and receiving UART must operate at almost the same baud rate.
However, if the baud rates differ between both UARTs they must only differ by 10%. 

## Transmitting and Receiving Data

### Data Transmission:
The transmitting device sends data as sequential bits, breaking it down into smaller units.

These units are sent over the transmission line.

### Data Reassembly:
The receiving device reassembles the bits it receives back into complete bytes.

This byte-level data is then processed and used by the receiving device.

## Communication Types

### Simplex Communication:
In simplex communication, data flows only in one direction.

Devices can either transmit or receive, but not both.

### Full-Duplex Communication:
Full-duplex communication allows devices to both transmit and receive data simultaneously.

This bidirectional communication enhances real-time interaction.
### Half-Duplex Communication:
Half-duplex communication involves devices taking turns to transmit and receive data.

While one device sends data, the other listens and vice versa.

![image](https://github.com/proatharv/Manipulator-on-Dynamixel-/assets/142431248/59ba9449-5e35-480a-8c18-b8bf92c7f19b)

## Components of UART

### Clock Generation:
UART includes a clock generator that provides timing information for data transmission.

### Shift Registers:
Shift registers are used to store and shift data bits during transmission and reception.

### Controls and Logic:
Controls manage the process of transmitting and receiving data.

Logic circuits handle reading and writing data.
### Optional Components:
Additional features can include buffers, memory, and DMA controllers for optimized data handling.

## Working of UART

### Two-Way Communication:
UART requires two devices to communicate directly.
One device serves as the transmitter, while the other acts as the receiver.

### Transmitting and Receiving:
The transmitting UART converts data from the CPU into serial form for transmission.
The receiving UART converts the received serial data back into parallel data.

![image](https://github.com/proatharv/Manipulator-on-Dynamixel-/assets/142431248/4b0a5576-0d08-44ef-a90f-2bb5684eac9f)


### Start and Stop Bits:
Data packets are framed using start and stop bits.
Start bit marks the beginning, and stop bits indicate the end of a data packet.

## ESP32 UART

### UART Ports on ESP32:
ESP32 provides three universal asynchronous receivers and transmitter (UART) ports such as UART0, UART1, and UART2 that work at 3.3V TTL level
These three serial interfaces are hardware supported.
Each of them exposes 4 pins: RX, TX, RTS and CTS.Ports provide pins for RX, TX, RTS, and CTS functionalities.
Arduino primarily uses RX and TX pins for UART communication.
It's easier to work with UART0 and UART2 due to pin availability and compatibility.

*UART1 Consideration:*
Using UART1 might require pin reassignment due to internal connections with other components.
UART1 use might necessitate reassigning pins due to their connection to SPI flash memory.

The table below specifies the RX and TX pins for each of the three UART ports available in ESP32.

![image](https://github.com/proatharv/Manipulator-on-Dynamixel-/assets/142431248/7ea89048-f547-44a7-b250-f32ab872da00)


## UART in Technology
### Historical Use:
UART was previously used in devices like keyboards and mice with thick cables.
These cables are now largely replaced by USB connections.

### Modern Applications:
UART remains relevant in modern DIY electronics projects like Raspberry Pi and Arduino.
It's used to establish connections with Bluetooth modules, GPS modules, and more.



