set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BUILD_TYPE Debug)




# gtkmm

# TODO: Test and fix on Windows

find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0)

link_directories(${GTKMM_LIBRARY_DIRS})
add_executable(GtkmmCalculator Calculator.cpp Calculator.hpp GtkmmCalculator.cpp)
target_include_directories(GtkmmCalculator PRIVATE ${GTKMM_INCLUDE_DIRS})
target_link_libraries(GtkmmCalculator ${GTKMM_LIBRARIES})




# Qt

find_package(Qt5Widgets REQUIRED)
add_executable(QtCalculator Calculator.cpp Calculator.hpp QtCalculator.cpp)
target_link_libraries(QtCalculator Qt5::Widgets)




# FLTK

find_package(FLTK REQUIRED)
add_executable(FltkCalculator Calculator.cpp Calculator.hpp FltkCalculator.cpp)
target_link_libraries(FltkCalculator ${FLTK_LIBRARIES})




# Wt
set (WT_CONNECTOR "wthttp" CACHE STRING "Connector used (wthttp or wtfcgi")
add_executable(WtCalculator Calculator.cpp Calculator.hpp WtCalculator.cpp)
target_include_directories(WtCalculator PRIVATE /usr/local/include/Wt)
target_link_libraries(WtCalculator ${WT_CONNECTOR} wt)




# wxWidgets

find_package(wxWidgets COMPONENTS core base REQUIRED)
include(${wxWidgets_USE_FILE})

add_executable(WxCalculator Calculator.cpp Calculator.hpp WxCalculator.cpp)

if (WIN32)
    # Needed by wxWidgets on Windows to call WinMain() instead of main()
    set_property(TARGET WxCalculator APPEND_STRING PROPERTY LINK_FLAGS "/SUBSYSTEM:windows")
endif()

target_link_libraries(WxCalculator ${wxWidgets_LIBRARIES})

