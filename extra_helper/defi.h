#pragma once

#ifndef _MY_LIB_ 
#define _MY_LIB_ 

#ifdef __unix__
#define MYLIB_API       extern 
#elif defined(__unix)
#define MYLIB_API       extern 
#else 
#define MYLIB_API   __declspec(dllexport) 
#endif 

#endif  // _MY_LIB_ 