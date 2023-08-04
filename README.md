# NRF24-with-stm32

![NRF24L01](https://img.shields.io/badge/Module-NRF24L01-green)
![STM32](https://img.shields.io/badge/Microcontroller-STM32-orange)

This repository contains a library and example code for interfacing the NRF24L01 wireless communication module with STM32 microcontrollers. The NRF24L01 is a popular 2.4GHz wireless transceiver module, and this library aims to provide an easy-to-use interface to enable seamless communication between STM32-based devices, this project is used as a telematic system for formula student car as it communicates with car over can and sends data wireless to the receiver and data is received and displayed over GUI.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
- [Usage](#usage)
- [Examples](#examples)
- [Contributing](#contributing)
- [Acknowledgements](#acknowledgements)

## Introduction

The NRF24L01 is widely used in various applications such as wireless sensor networks, remote control systems, and IoT devices. This library provides a simple and efficient way to configure and utilize the NRF24L01 module with STM32 microcontrollers. By using this library, you can quickly establish wireless communication between multiple STM32 devices, enabling you to build complex and interconnected systems.

## Features

- Easy-to-use APIs: The library offers straightforward APIs to initialize, configure, and transmit/receive data using the NRF24L01 module.

- Support for multiple data pipes: You can set up different communication channels (data pipes) to address individual devices in a network.

- Enhanced reliability: The NRF24L01 protocol includes built-in features for data retransmission, ensuring reliable communication.

- Adjustable data rate: The library allows you to set the data rate (250kbps, 1Mbps, or 2Mbps) based on your application's requirements.

## Getting Started

### Prerequisites

To use this library and example code, you need the following:

- An STM32 development board (e.g., STM32F103, STM32F407, etc.).
- An NRF24L01 wireless module.
- STM32CubeIDE or any other compatible IDE with the STM32 HAL libraries installed.

### Installation

To get started, follow these steps:

1. Clone or download this repository to your local machine.

2. Copy the `NRF24` directory inside the `Libraries` folder to your STM32 project's source directory.

3. Include the required header files in your code:

   ```c
   #include "NRF24/nrf24.h"
   ```

4. Configure the necessary GPIO pins, SPI peripheral, and other settings in your STM32 project to connect with the NRF24L01 module.

## Usage

1. Initialize the NRF24L01 module by calling `NRF24_Init()` with appropriate configurations.

2. Set the address for transmitting and receiving data using `NRF24_SetTXAddress()` and `NRF24_SetRXAddress()` functions.

3. Use the `NRF24_Transmit()` function to send data from the transmitter side.

4. On the receiver side, use `NRF24_Receive()` to check for incoming data and read it using `NRF24_GetData()`.

For a detailed description of each API and its parameters, refer to the comments and documentation in the `nrf24.h` header file.


## Contributing

Contributions to this repository are highly appreciated. If you find any bugs, want to add new features, or improve the existing code, feel free to open a pull request following the guidelines mentioned in [CONTRIBUTING.md](CONTRIBUTING.md).


## Acknowledgements

We would like to express our gratitude to [Mahmoud Ismael](https://github.com/mahmoudisma3il18) for creating this library and making it available for the community. Additionally, we thank all the contributors who have helped improve and maintain this repository.

---

