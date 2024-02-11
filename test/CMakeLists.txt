project ("test")

add_executable(test_extra_time test_extra_time.cpp)
target_link_libraries(test_extra_time ${EXTRA_HELPER_LIB})

add_executable(test_extra_path test_extra_path.cpp)
target_link_libraries(test_extra_path ${EXTRA_HELPER_LIB})
