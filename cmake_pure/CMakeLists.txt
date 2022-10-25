cmake_minimum_required(VERSION 3.20)

project(SimFrames 
    VERSION 0.1 
    DESCRIPTION "Framework utilizing LittleVGL library for firmware simulation frontend development"
    LANGUAGES CXX
    )

add_library(SimFrames STATIC)

target_include_directories(SimFrames
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/../include
    ${CMAKE_CURRENT_LIST_DIR}/../include/Core
    ${CMAKE_CURRENT_LIST_DIR}/../include/Widgets
    ${CMAKE_CURRENT_LIST_DIR}/../include/Extra
    )

target_sources(SimFrames
    PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/../src/Core/SimWindow.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/../src/Core/SimTab.cpp 
    ${CMAKE_CURRENT_LIST_DIR}/../src/Core/SimGrid.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/Core/SimContainer.cpp   
    ${CMAKE_CURRENT_LIST_DIR}/../src/Core/SimWidget.cpp

    ${CMAKE_CURRENT_LIST_DIR}/../src/Data/SimDataObject.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/Data/SimDataStorage.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/Data/SimDataMapping.cpp

    ${CMAKE_CURRENT_LIST_DIR}/../src/Widgets/SimLabel.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/Widgets/SimRelay.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/Widgets/SimSlider.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/Widgets/SimNumericInput.cpp
    
    
    )

target_link_libraries(SimFrames
    PRIVATE
    lvgl
    )

set_target_properties(SimFrames
    PROPERTIES
    LINKER_LANGUAGE CXX
    )