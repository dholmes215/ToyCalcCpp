set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BUILD_TYPE Debug)


# Build Calculator by itself to link into other executables.
add_library(Calculator STATIC Calculator.cpp Calculator.hpp)




# gtkmm

# TODO: Test and fix on Windows

find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0)

add_executable(GtkmmCalculator GtkmmCalculator.cpp)
target_include_directories(GtkmmCalculator PRIVATE ${GTKMM_INCLUDE_DIRS})
target_link_libraries(GtkmmCalculator Calculator ${GTKMM_LIBRARIES})




# gtkmm/glade

add_executable(GtkmmGladeCalculator GtkmmGladeCalculator.cpp)
target_include_directories(GtkmmGladeCalculator PRIVATE ${GTKMM_INCLUDE_DIRS})
target_link_libraries(GtkmmGladeCalculator Calculator ${GTKMM_LIBRARIES})




# Qt

find_package(Qt5Widgets REQUIRED)
add_executable(QtCalculator QtCalculator.cpp)
target_link_libraries(QtCalculator Calculator Qt5::Widgets)




# FLTK

find_package(FLTK REQUIRED)
add_executable(FltkCalculator FltkCalculator.cpp)
target_link_libraries(FltkCalculator Calculator ${FLTK_LIBRARIES})




# Wt
set (WT_CONNECTOR "wthttp" CACHE STRING "Connector used (wthttp or wtfcgi")
add_executable(WtCalculator WtCalculator.cpp)
target_include_directories(WtCalculator PRIVATE /usr/local/include/Wt)
target_link_libraries(WtCalculator Calculator ${WT_CONNECTOR} wt)




# wxWidgets

find_package(wxWidgets COMPONENTS core base REQUIRED)
include(${wxWidgets_USE_FILE})

add_executable(WxCalculator WxCalculator.cpp)

if (WIN32)
    # Needed by wxWidgets on Windows to call WinMain() instead of main()
    set_property(TARGET WxCalculator APPEND_STRING PROPERTY LINK_FLAGS "/SUBSYSTEM:windows")
endif()

target_link_libraries(WxCalculator Calculator ${wxWidgets_LIBRARIES})
