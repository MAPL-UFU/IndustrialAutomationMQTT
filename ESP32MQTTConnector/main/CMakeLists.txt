# Edit following two lines to set component requirements (see docs)

set(COMPONENT_SRCS "main.cpp" 
        "../include/EventHandler.cpp"
        "../include/MQTTEventHandler.cpp"
        "../include/SerialEventHandler.cpp"
        "../include/CustomEventHandler.cpp")
set(COMPONENT_ADD_INCLUDEDIRS "." "../include/")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

register_component()