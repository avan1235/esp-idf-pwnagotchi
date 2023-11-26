cmake_minimum_required(VERSION 3.5)

set(EXTRA_COMPONENT_DIRS
        components/u8g2
        components/u8g2-hal-esp-idf
        components/wifi_controller)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(app-template)
