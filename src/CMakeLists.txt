set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BUILD_TYPE Debug)


# Build Calculator by itself to link into other executables.
add_library(Calculator STATIC Calculator.cpp Calculator.hpp)
add_library(CCalculator STATIC CCalculator.cpp CCalculator.h Calculator.cpp Calculator.hpp)



find_package(PkgConfig)


# GTK+

pkg_check_modules(GTK gtk+-3.0)
add_definitions(${GTK_CFLAGS_OTHER})
add_executable(GtkCalculator GtkCalculator.c)
target_include_directories(GtkCalculator PRIVATE ${GTK_INCLUDE_DIRS})
target_link_libraries(GtkCalculator CCalculator ${GTK_LIBRARIES})



# gtkmm

# TODO: Test and fix on Windows

pkg_check_modules(GTKMM gtkmm-3.0)

add_executable(GtkmmCalculator GtkmmCalculator.cpp)
target_include_directories(GtkmmCalculator PRIVATE ${GTKMM_INCLUDE_DIRS})
target_link_libraries(GtkmmCalculator Calculator ${GTKMM_LIBRARIES})




# gtkmm/glade

add_executable(GtkmmGladeCalculator GtkmmGladeCalculator.cpp)
target_include_directories(GtkmmGladeCalculator PRIVATE ${GTKMM_INCLUDE_DIRS})
target_link_libraries(GtkmmGladeCalculator Calculator ${GTKMM_LIBRARIES})




# Qt

find_package(Qt5 COMPONENTS Widgets REQUIRED)
add_executable(QtCalculator QtCalculator.cpp)
target_link_libraries(QtCalculator Calculator Qt5::Widgets)




# QtDesigner

set(CMAKE_AUTOMOC ON)               # To generate ui_QtDesignerCalculator.h
set(CMAKE_AUTOUIC ON)               # To generate ui_QtDesignerCalculator.h
set(CMAKE_INCLUDE_CURRENT_DIR ON)   # To find ui_QtDesignerCalculator.h
add_executable(QtDesignerCalculator QtDesignerCalculator.cpp)
target_link_libraries(QtDesignerCalculator Calculator Qt5::Widgets)




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
