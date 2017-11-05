# GTK+
add_definitions(${GTK_CFLAGS_OTHER})
add_executable(GtkCalculator GtkCalculator.c)
target_include_directories(GtkCalculator PRIVATE ${GTK_INCLUDE_DIRS})
target_link_libraries(GtkCalculator CCalculator ${GTK_LIBRARIES})
