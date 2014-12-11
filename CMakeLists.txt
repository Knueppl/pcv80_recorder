cmake_minimum_required(VERSION 2.8)

find_package(Qt4 REQUIRED)

include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

qt4_wrap_ui(UIS
            form/MainWindow.ui
            )

qt4_wrap_cpp(MOCS
             src/MainWindow.h
             )

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(pcv80-recorder
               src/main.cpp
               src/Rs485.cpp
               src/Pcv80.cpp
               src/MainWindow.cpp
               ${UIS}
               ${MOCS}
               )

target_link_libraries(pcv80-recorder
                      ${QT_LIBRARIES}
                      )
