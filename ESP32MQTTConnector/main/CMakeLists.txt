# Edit following two lines to set component requirements (see docs)
set(COMPONENT_REQUIRES )
set(COMPONENT_PRIV_REQUIRES )

set(COMPONENT_SRCS "main.cpp")
set(COMPONENT_ADD_INCLUDEDIRS ".")
set(COMPONENT_ADD_INCLUDEDIRS "../include")

register_component()

set_source_files_properties(COMPONENT_SRCS PROPERTIES COMPILE_FLAGS -std=gnu17)