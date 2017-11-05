# Wt
set (WT_CONNECTOR "wthttp" CACHE STRING "Connector used (wthttp or wtfcgi")
add_executable(WtCalculator WtCalculator.cpp)
target_include_directories(WtCalculator PRIVATE /usr/local/include/Wt)
target_link_libraries(WtCalculator Calculator ${WT_CONNECTOR} wt)
