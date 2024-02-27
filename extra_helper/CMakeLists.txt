
ADD_DEFINITIONS(-DEXPORT) 

# 设置 库文件的默认输出路径
set(HEADERS "defi.h" "time/time.h" "path/path.h" "lzma/lzma.h" "file/file.h" "sys/sys.h" )

# 编译动态库 
add_library(extra_helper SHARED "path/path.cpp" "time/time.cpp"  "lzma/lzma.cpp" "file/file.h" "file/file.cpp" "sys/sys.h" "sys/sys.cpp")

# 定义自定义命令
add_custom_command(TARGET extra_helper POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:extra_helper> ${CMAKE_CURRENT_BINARY_DIR}/../test
    COMMENT "Copying extra_helper to test"
)

file(INSTALL "defi.h" DESTINATION include/extra_helper)
file(INSTALL "time/time.h" DESTINATION include/extra_helper/time)
file(INSTALL "path/path.h" DESTINATION include/extra_helper/path)
file(INSTALL "lzma/lzma.h" DESTINATION include/extra_helper/lzma)
file(INSTALL "file/file.h" DESTINATION include/extra_helper/file)
file(INSTALL "sys/sys.h" DESTINATION include/extra_helper/file)

if(WIN32)
# 移动到 C://windows/下
file(INSTALL "lzma/7zexe/7z.exe" DESTINATION C:/windows)
endif()

set(EH_LIBRARIES extra_helper CACHE INTERNAL "link extra_helper libraries")

