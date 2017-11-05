# Qt Calculator
add_executable(QtCalculator QtCalculator.cpp)
target_link_libraries(QtCalculator Calculator Qt5::Widgets)


# Qt Designer Calculator
set(CMAKE_AUTOMOC ON)               # To generate ui_QtDesignerCalculator.h
set(CMAKE_AUTOUIC ON)               # To generate ui_QtDesignerCalculator.h
set(CMAKE_INCLUDE_CURRENT_DIR ON)   # To find ui_QtDesignerCalculator.h
add_executable(QtDesignerCalculator QtDesignerCalculator.cpp)
target_link_libraries(QtDesignerCalculator Calculator Qt5::Widgets)

