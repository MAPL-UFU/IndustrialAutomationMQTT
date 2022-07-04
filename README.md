# IndustrialAutomationMQTT (Development)

This is a summary project for the development of a series of studies associated with inclusion of ESP32 microcontroler as a bridge for main Lab machinery and a MQTT network.

## Organization

This project was divided two main parts:
1. Custom Component Development:
    In this part we create a set of standalone repositorys for the most inportant functionalities for us using a C++ like architecture. By now the list of components are:

    - [MAPL cpp-esp-wifi](https://github.com/MAPL-UFU/cpp-esp-wifi)
    - [MAPL cpp-esp-mqtt](https://github.com/MAPL-UFU/cpp-esp-mqtt)
    - [MAPL cpp-esp-serial](https://github.com/MAPL-UFU/cpp-esp-serial)

    If you want to integrate only a module please follow link above and see module documentation about how to do it using esp-idf model.

2. Test Example Codes:
    The main folders in this repository contains real examples of esp32 (idf) projects using the components developed for each functionality. This part was thought to keep in continous development and each folder has its own README description. Current index:

    - Solution 1: Simple Cylinder Control 
    - Solution 2: Two Cylinder Control


Notes:

- Compiled With: GCC std=gnu17 (There is no guarantee that the code will work with previous versions)

- To execute a hard update repository (including submodules) you will need to use the command:

    ``` git submodule update --init --force --remote ```
([see-more](https://git-scm.com/book/en/v2/Git-Tools-Submodules))

## Compilers Installation

This project uses the official compilers for ESP32 released by Expressif in ESP-IDF package, it includes the correct GCC backend for ESP32. We will not describe how to use directly CPU compiler because it can change for different ESP32 versions (Xtensa LX6 for ESP32, Xtensa LX7 for ESP32-S2 and S3 and 
RISC-V for ESP32 C3).    

To install ESP-IDF Environment in your Windows or Linux SO you need to follow the instructions described in Expressif Official User Guide:

- [Windows Installation Procedure](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/windows-setup.html)
- [Linux Installation Procedure](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/linux-macos-setup.html)

As specified in documentation is recommended to use the [VScode official Extention](https://github.com/espressif/vscode-esp-idf-extension/blob/master/docs/tutorial/install.md) as a more simple way to compile and load your code but we realy discourage you to use PlatformIO esp32 environments, at the moment of writing this the compilers and librarys used there are outdated and not compatibles.

