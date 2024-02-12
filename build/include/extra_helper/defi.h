#pragma once

#ifndef _MY_LIB_ 
#define _MY_LIB_ 

#ifdef __unix__
#define MYLIB_API       extern 
#elif defined(__unix)
#define MYLIB_API       extern 
#else 
	#ifdef DIMPORT
	#define MYLIB_API   __declspec(dllimport) 
	#else 
	#define MYLIB_API   __declspec(dllexport) 
	#endif 
#endif 

#endif  // _MY_LIB_ 