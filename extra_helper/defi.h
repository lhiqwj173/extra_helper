#pragma once

#ifndef _MY_LIB_ 
#define _MY_LIB_ 

#ifdef _WIN32
	#ifdef EXPORT
		#define MYLIB_API   __declspec(dllexport) 
		#define MYLIB_OUT_API   __declspec(dllexport) // ģ�庯��
		#define MYLIB_IN_API   
	#else 
		#define MYLIB_API   __declspec(dllimport) 
		#define MYLIB_OUT_API   // ģ�庯��
		#define MYLIB_IN_API  __declspec(dllimport)  // ģ�庯��
	#endif 
#else 
	#define MYLIB_API       extern 
	#define MYLIB_OUT_API    
	#define MYLIB_IN_API    
#endif 

#endif  // _MY_LIB_ 