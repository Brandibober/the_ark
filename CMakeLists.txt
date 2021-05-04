cmake_minimum_required(VERSION 3.17)
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
        TechnicalService.h
        BiologicalService.cpp
        BiologicalService.h
        MedicalService.cpp
        MedicalService.h
        NavigationService.cpp
        NavigationService.h
        EmergencyService.cpp
        EmergencyService.h
        SocialService.cpp
        SocialService.h
        Population.cpp
        Population.h
        Resources.cpp
        Resources.h
        Human.cpp
        Human.h
        Enums.cpp
        menu.h)
target_link_libraries(the_ark sfml-graphics sfml-audio)