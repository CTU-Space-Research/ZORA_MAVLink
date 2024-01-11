
# 📖 [MAVLink C implementation for STM32] <a name="about-project"></a>

> Example how to use pre-generated MAVLink files (with slight modifications) in a embedded STM32 project.

### Important files:
- Libs / MAVLink
  - _generated_ = files generated by **_mavgen_** python program in MAVLinkSuite repo
  - _implementation_ = files that implement the MAVLink protocol using pre-defined functions and enums in _generated_ folder


<!-- GETTING STARTED -->
## 💻 Getting Started</a>

**Before using the code on ARM Cortex M0 MCUs, be aware that it might not work. I should have fixed the problem already, but it is not a certainty**

### Setup
- STM32CubeIDE
- Create Libs folder in your CubeIDE project
- Clone this repo and **import** the MAVLink folder from the repo into your Libs folder using Cube
###

### Usage
Add _after_ GPIO definition generated from CubeMX in _main.h_ in _/* USER CODE BEGIN Private defines */_ block
> #include "MAVLinkImplementation.h"

You can add the _MAVLinkImplementation.h_ to any other .h file

## 🛠 Compiling the library in an existing project</a>

> STM32CubeIDE as a compiler and programmer

In the CubeIDE, in *Project Properties/ C++ General/ Paths and Symbols* add these two lines

- **[/${ProjName}/Libs/MAVLink/generated]**
- **[/${ProjName}/Libs/MAVLink/implementation]**

In the CubeIDE, in *Project Properties/ C++ Build/ Settings / MCU GCC Compiler / Miscellaneous -> Other flags* add this line:

- **[-Wno-address-of-packed-member]**

This suppresses MAVLink warning during compiling.
