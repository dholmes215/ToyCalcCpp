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
if (GTK_FOUND)
    add_subdirectory(gtk)
endif ()


# gtkmm
pkg_check_modules(GTKMM gtkmm-3.0)
if (GTKMM_FOUND)
    add_subdirectory(gtkmm)
endif ()


# Qt
find_package(Qt5 COMPONENTS Widgets)
if (Qt5_FOUND)
    add_subdirectory(qt)
endif ()


# FLTK
#find_package(FTLK)   # XXX This seems to be broken
find_package(FLTK REQUIRED)
if (FLTK_FOUND)
    add_subdirectory(fltk)
endif ()


# Wt
if (EXISTS /usr/local/include/Wt)
    # This is not great, but there is no FindWt.cmake script from either
    # CMake or Wt, and no pkg-config support, so...
    add_subdirectory(wt)
endif ()


# wxWidgets
find_package(wxWidgets COMPONENTS core base)
if (wxWidgets_FOUND)
    add_subdirectory(wx)
endif ()
