project ("extra_helper")

set(CMAKE_CXX_STANDARD 17)

ADD_DEFINITIONS(-DEXPORT) 

include_directories(logger/include)

# lzma
add_definitions(-D_7ZIP_ST)

# lzma sdk源文件
set(LZMA_SOURCES
    lzma/lzma.cpp
    lzma/7z/C/LzFind.c
    lzma/7z/C/LzmaDec.c
    lzma/7z/C/LzmaEnc.c
    lzma/7z/C/CpuArch.c
)

# 编译动态库 
add_library(extra_helper SHARED "path/path.cpp" "time/time.cpp"  ${LZMA_SOURCES}  "file/file.cpp" "sys/sys.cpp" "logger/log.cpp")

# 定义自定义命令
add_custom_command(TARGET extra_helper POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:extra_helper> ${CMAKE_CURRENT_BINARY_DIR}/../test
    COMMENT "Copying extra_helper to test"
)

if (NOT WIN32)
add_custom_command(TARGET extra_helper POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:extra_helper> /usr/lib
    COMMENT "Copying extra_helper to /usr/lib"
)
endif()

file(INSTALL "defi.h" DESTINATION include/extra_helper)
file(INSTALL "time/time.h" DESTINATION include/extra_helper/time)
file(INSTALL "path/path.h" DESTINATION include/extra_helper/path)
file(INSTALL "lzma/lzma.h" DESTINATION include/extra_helper/lzma)
file(INSTALL "file/file.h" DESTINATION include/extra_helper/file)
file(INSTALL "sys/sys.h" DESTINATION include/extra_helper/sys)
file(INSTALL "logger/log.h" DESTINATION include/extra_helper/logger)
#file(INSTALL "logger/include/spdlog/spdlog.h" DESTINATION include/spdlog)
file(INSTALL "logger/include/spdlog" DESTINATION include)

if(WIN32)
# 移动到 C://windows/下
file(INSTALL "lzma/7zexe/7z.exe" DESTINATION C:/windows)
endif()

set(EH_LIBRARIES extra_helper CACHE INTERNAL "link extra_helper libraries")

