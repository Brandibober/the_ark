cmake_minimum_required(VERSION 3.16)
project(the_ark)

set(CMAKE_CXX_STANDARD 17)

if (WIN32)
    set(SFML_DIR ../SFML-2.5.1/lib/cmake/SFML)
endif()

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(the_ark
        main.cpp
        TheArk.h
        TheArk.cpp
        Service.cpp
        TechnicalService.cpp
        BiologicalService.cpp
        MedicalService.cpp
        NavigationService.cpp
        EmergencyService.cpp
        SocialService.cpp
        Population.cpp
        Resources.cpp
        Human.cpp
        Enums.cpp
        menu.cpp)
target_link_libraries(the_ark sfml-graphics sfml-audio)