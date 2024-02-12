include_directories(include)

ADD_DEFINITIONS(-DIMPORT) 

project ("test")

add_executable(test_extra_time test_extra_time.cpp)
#target_link_libraries(test_extra_time ${EXTRA_HELPER_LIB})
target_link_libraries(test_extra_time extra_helper)

add_executable(test_extra_path test_extra_path.cpp)
#target_link_libraries(test_extra_path ${EXTRA_HELPER_LIB})
target_link_libraries(test_extra_path extra_helper)
