file(GLOB_RECURSE SOURCES src/*.c)
idf_component_register(
        SRCS ${SOURCES}
        INCLUDE_DIRS "interface"
        REQUIRES u8g2-hal-esp-idf)