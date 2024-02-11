# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)

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

# 包含子项目。
add_subdirectory ("extra_helper")
add_subdirectory ("test")
