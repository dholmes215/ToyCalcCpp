set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BUILD_TYPE Debug)

# wxWidgets

find_package(wxWidgets COMPONENTS core base REQUIRED)
include(${wxWidgets_USE_FILE})

add_executable(WxCalculator Calculator.cpp Calculator.hpp WxCalculator.cpp WxCalculator.hpp)

if (WIN32)
    # Needed by wxWidgets on Windows to call WinMain() instead of main()
    set_property(TARGET WxCalculator APPEND_STRING PROPERTY LINK_FLAGS "/SUBSYSTEM:windows")
endif()

target_link_libraries(WxCalculator ${wxWidgets_LIBRARIES})




# gtkmm

# TODO: Test and fix on Windows

find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-3.0)

link_directories(${GTKMM_LIBRARY_DIRS})
include_directories(${GTKMM_INCLUDE_DIRS})

add_executable(GtkmmCalculator Calculator.cpp Calculator.hpp GtkmmCalculator.cpp GtkmmCalculator.hpp)
target_link_libraries(GtkmmCalculator ${GTKMM_LIBRARIES})




# Qt

find_package(Qt5Widgets REQUIRED)
add_executable(QtCalculator Calculator.cpp Calculator.hpp QtCalculator.cpp)
target_link_libraries(QtCalculator Qt5::Widgets)
