//
// MATLAB Compiler: 4.17 (R2012a)
// Date: Mon Oct 09 21:25:22 2017
// Arguments: "-B" "macro_default" "-W" "cpplib:TaddM" "-T" "link:lib" "-d"
// "G:\ȼ���Ż����ϣ�\�Ż������Ż��㷨\�Ż�����\TaddM\src" "-w"
// "enable:specified_file_mismatch" "-w" "enable:repeated_file" "-w"
// "enable:switch_ignored" "-w" "enable:missing_lib_sentinel" "-w"
// "enable:demo_license" "-v"
// "G:\ȼ���Ż����ϣ�\�Ż������Ż��㷨\�Ż�����\Tadd.m" 
//

#ifndef __TaddM_h
#define __TaddM_h 1

#if defined(__cplusplus) && !defined(mclmcrrt_h) && defined(__linux__)
#  pragma implementation "mclmcrrt.h"
#endif
#include "mclmcrrt.h"
#include "mclcppclass.h"
#ifdef __cplusplus
extern "C" {
#endif

#if defined(__SUNPRO_CC)
/* Solaris shared libraries use __global, rather than mapfiles
 * to define the API exported from a shared library. __global is
 * only necessary when building the library -- files including
 * this header file to use the library do not need the __global
 * declaration; hence the EXPORTING_<library> logic.
 */

#ifdef EXPORTING_TaddM
#define PUBLIC_TaddM_C_API __global
#else
#define PUBLIC_TaddM_C_API /* No import statement needed. */
#endif

#define LIB_TaddM_C_API PUBLIC_TaddM_C_API

#elif defined(_HPUX_SOURCE)

#ifdef EXPORTING_TaddM
#define PUBLIC_TaddM_C_API __declspec(dllexport)
#else
#define PUBLIC_TaddM_C_API __declspec(dllimport)
#endif

#define LIB_TaddM_C_API PUBLIC_TaddM_C_API


#else

#define LIB_TaddM_C_API

#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_TaddM_C_API 
#define LIB_TaddM_C_API /* No special import/export declaration */
#endif

extern LIB_TaddM_C_API 
bool MW_CALL_CONV TaddMInitializeWithHandlers(
       mclOutputHandlerFcn error_handler, 
       mclOutputHandlerFcn print_handler);

extern LIB_TaddM_C_API 
bool MW_CALL_CONV TaddMInitialize(void);

extern LIB_TaddM_C_API 
void MW_CALL_CONV TaddMTerminate(void);



extern LIB_TaddM_C_API 
void MW_CALL_CONV TaddMPrintStackTrace(void);

extern LIB_TaddM_C_API 
bool MW_CALL_CONV mlxTadd(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);


#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

/* On Windows, use __declspec to control the exported API */
#if defined(_MSC_VER) || defined(__BORLANDC__)

#ifdef EXPORTING_TaddM
#define PUBLIC_TaddM_CPP_API __declspec(dllexport)
#else
#define PUBLIC_TaddM_CPP_API __declspec(dllimport)
#endif

#define LIB_TaddM_CPP_API PUBLIC_TaddM_CPP_API

#else

#if !defined(LIB_TaddM_CPP_API)
#if defined(LIB_TaddM_C_API)
#define LIB_TaddM_CPP_API LIB_TaddM_C_API
#else
#define LIB_TaddM_CPP_API /* empty! */ 
#endif
#endif

#endif

extern LIB_TaddM_CPP_API void MW_CALL_CONV Tadd(int nargout, mwArray& m, const mwArray& a, const mwArray& b);

#endif
#endif
