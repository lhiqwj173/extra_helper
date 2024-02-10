project ("test")

# 头文件路径 
INCLUDE_DIRECTORIES(./include) 

add_executable(test_extra_time test_extra_time.cpp)
target_link_libraries(test_extra_time ${EXTRA_HELPER_LIB})


