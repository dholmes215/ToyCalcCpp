set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# wxWidgets
find_package(wxWidgets COMPONENTS core base REQUIRED)
include(${wxWidgets_USE_FILE})

add_executable(WxCalculator Calculator.cpp Calculator.hpp WxCalculator.cpp WxCalculator.hpp)

if (WIN32)
    # Needed by wxWidgets on Windows to call WinMain() instead of main()
    set_property(TARGET WxCalculator APPEND_STRING PROPERTY LINK_FLAGS "/SUBSYSTEM:windows")
endif()

target_link_libraries(WxCalculator ${wxWidgets_LIBRARIES})
