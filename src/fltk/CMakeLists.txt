# FLTK
add_executable(FltkCalculator FltkCalculator.cpp)
target_link_libraries(FltkCalculator Calculator ${FLTK_LIBRARIES})
