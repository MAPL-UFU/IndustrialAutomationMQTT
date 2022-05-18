# IndustrialAutomationMQTT

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

    - ESP32MQTTConnector

#Development

Notes:

- Compiled With: GCC std=gnu17 (There is no guarantee that the code will work with previous versions)

- To execute a hard update repository (including submodules) you will need to use the command:

    ``` git submodule update --init --force --remote ```
