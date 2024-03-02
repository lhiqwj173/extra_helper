project ("test")

set(CMAKE_CXX_STANDARD 17)

#include_directories(include)
#include_directories("../extra_helper/include")
include_directories(${CMAKE_CURRENT_BINARY_DIR}/../extra_helper/include)

add_executable(test_extra_time test_extra_time.cpp)
target_link_libraries(test_extra_time ${EH_LIBRARIES} pthread)

add_executable(test_extra_path test_extra_path.cpp)
target_link_libraries(test_extra_path ${EH_LIBRARIES} pthread)

add_executable(test_extra_7z "test_extra_7z.cpp")
target_link_libraries(test_extra_7z ${EH_LIBRARIES} pthread )

add_executable(test_extra_lzma "test_extra_lzma.cpp")
target_link_libraries(test_extra_lzma ${EH_LIBRARIES} pthread)