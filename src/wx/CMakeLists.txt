# wxWidgets
include(${wxWidgets_USE_FILE})

add_executable(WxCalculator WxCalculator.cpp)

if (WIN32)
    # Needed by wxWidgets on Windows to call WinMain() instead of main()
    set_property(TARGET WxCalculator APPEND_STRING PROPERTY LINK_FLAGS "/SUBSYSTEM:windows")
endif ()

target_link_libraries(WxCalculator Calculator ${wxWidgets_LIBRARIES})
