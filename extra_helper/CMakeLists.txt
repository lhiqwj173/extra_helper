
ADD_DEFINITIONS(-DEXPORT) 

# 如果非win，添加 set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
if (CMAKE_HOST_UNIX) 
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
endif()

add_subdirectory ("lzma")

# 设置 库文件的默认输出路径
set(HEADERS "defi.h" "time/time.h" "path/path.h" "lzma/lzma.h" )

# 编译动态库 
add_library(extra_helper SHARED "path/path.cpp" "time/time.cpp"  "lzma/lzma.cpp")

# 链接lzma lib
target_link_libraries(extra_helper "lzma")

# 定义自定义命令
add_custom_command(TARGET extra_helper POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:extra_helper> ${CMAKE_CURRENT_BINARY_DIR}/../test
    COMMENT "Copying extra_helper to test"
)

file(INSTALL "defi.h" DESTINATION include/extra_helper)
file(INSTALL "time/time.h" DESTINATION include/extra_helper/time)
file(INSTALL "path/path.h" DESTINATION include/extra_helper/path)
file(INSTALL "lzma/lzma.h" DESTINATION include/extra_helper/lzma)

set(EH_LIBRARIES extra_helper CACHE INTERNAL "link extra_helper libraries")

