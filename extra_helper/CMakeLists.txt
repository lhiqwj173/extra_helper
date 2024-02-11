
# 设置 库文件的默认输出路径
set (LIBRARY_OUTPUT_PATH lib)
set(HEADERS "defi.h" "time/time.h" "path/path.h" )

add_library(extra_helper SHARED  "time/time.cpp" "path/path.cpp" ${HEADERS} )

file(INSTALL ${HEADERS} DESTINATION include/extra_helper)

set(EXTRA_HELPER_LIB extra_helper CACHE INTERNAL "link extra_helper libraries")

