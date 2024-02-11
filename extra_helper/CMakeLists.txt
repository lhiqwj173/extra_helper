
# 设置 库文件的默认输出路径
set (LIBRARY_OUTPUT_PATH lib)
set(HEADERS "defi.h" "time/time.h" "path/path.h" )

add_library(extra_helper SHARED  "time/time.cpp" "path/path.cpp" ${HEADERS} )

file(INSTALL "defi.h" DESTINATION include/extra_helper)
file(INSTALL "time/time.h" DESTINATION include/extra_helper/time)
file(INSTALL "path/path.h" DESTINATION include/extra_helper/path)

set(EXTRA_HELPER_LIB extra_helper CACHE INTERNAL "link extra_helper libraries")

