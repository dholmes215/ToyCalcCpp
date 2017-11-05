# gtkmm
add_executable(GtkmmCalculator GtkmmCalculator.cpp)
target_include_directories(GtkmmCalculator PRIVATE ${GTKMM_INCLUDE_DIRS})
target_link_libraries(GtkmmCalculator Calculator ${GTKMM_LIBRARIES})

# gtkmm/glade
add_executable(GtkmmGladeCalculator GtkmmGladeCalculator.cpp)
target_include_directories(GtkmmGladeCalculator PRIVATE ${GTKMM_INCLUDE_DIRS})
target_link_libraries(GtkmmGladeCalculator Calculator ${GTKMM_LIBRARIES})

