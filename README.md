# STM32F401CC BareMetal Drivers Project

This project provides a set of Baremetal drivers for the STM32F401CC microcontroller, developed using the **PlatformIO**.

## Project Structure

The project is organized into the following directories:

- **`include/`**: Contains header files for the drivers and common utilities.
  - **`COMMON/`**: Common utilities and type definitions.
  - **`HAL/`**: Hardware Abstraction Layer (HAL) drivers.
  - **`MCAL/`**: Microcontroller Abstraction Layer (MCAL) drivers.
- **`src/`**: Contains the source code for the drivers and the main application.
  - **`HAL/`**: Implementation of HAL drivers.
  - **`MCAL/`**: Implementation of MCAL drivers.
  - **`main.c`**: Main application code.
- **`test/`**: Directory for unit tests.
- **`lib/`**: Directory for project-specific libraries.
- **`.vscode/`**: Configuration files for Visual Studio Code.
- **`platformio.ini`**: PlatformIO project configuration file.

## Drivers Overview

### GPIO Driver(MCAL)


### RCC Driver(MCAL)


### NVIC Driver(MCAL)



### SYSTICK Driver(MCAL)



### LED Driver (HAL)



### Scheduler Driver (HAL)



### Switch Scheduler Driver (HAL)







