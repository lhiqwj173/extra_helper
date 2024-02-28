# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.10)

# 如果支持，请为 MSVC 编译器启用热重载。
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("cpp_extra_helper")

## 自定义宏，代码中可以使用  
#if (CMAKE_HOST_UNIX) 
#    ADD_DEFINITIONS(-DLINUX) 
#else () 
#    ADD_DEFINITIONS(-DWINDOWS) 
#endif() 

## 设置 库文件的默认输出路径
#set(HEADERS "extra_helper/defi.h" "extra_helper/time/time.h" "extra_helper/path/path.h" )

#add_library(extra_helper SHARED  "extra_helper/time/time.cpp" "extra_helper/path/path.cpp" ${HEADERS} )

#file(INSTALL "extra_helper/defi.h" DESTINATION include/extra_helper)
#file(INSTALL "extra_helper/time/time.h" DESTINATION include/extra_helper/time)
#file(INSTALL "extra_helper/path/path.h" DESTINATION include/extra_helper/path)

#file(INSTALL "extra_helper/defi.h" DESTINATION test/include/extra_helper)
#file(INSTALL "extra_helper/time/time.h" DESTINATION test/include/extra_helper/time)
#file(INSTALL "extra_helper/path/path.h" DESTINATION test/include/extra_helper/path)

#set(EXTRA_HELPER_LIB extra_helper CACHE INTERNAL "link extra_helper libraries")

# 包含子项目。
add_subdirectory ("extra_helper")
add_subdirectory ("test")

