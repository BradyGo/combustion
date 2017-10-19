//
// MATLAB Compiler: 4.17 (R2012a)
// Date: Sat Oct 14 15:21:28 2017
// Arguments: "-B" "macro_default" "-W" "cpplib:opt" "-T" "link:lib" "-d"
// "F:\combus\opt\opt\src" "-w" "enable:specified_file_mismatch" "-w"
// "enable:repeated_file" "-w" "enable:switch_ignored" "-w"
// "enable:missing_lib_sentinel" "-w" "enable:demo_license" "-v"
// "F:\combus\opt\EvalIms.m" "F:\combus\opt\EvalTree.m"
// "F:\combus\opt\FTreeIII.m" "F:\combus\opt\insensitivelearning.m"
// "F:\combus\opt\main.m" 
//

#ifndef __opt_h
#define __opt_h 1

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

#ifdef EXPORTING_opt
#define PUBLIC_opt_C_API __global
#else
#define PUBLIC_opt_C_API /* No import statement needed. */
#endif

#define LIB_opt_C_API PUBLIC_opt_C_API

#elif defined(_HPUX_SOURCE)

#ifdef EXPORTING_opt
#define PUBLIC_opt_C_API __declspec(dllexport)
#else
#define PUBLIC_opt_C_API __declspec(dllimport)
#endif

#define LIB_opt_C_API PUBLIC_opt_C_API


#else

#define LIB_opt_C_API

#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_opt_C_API 
#define LIB_opt_C_API /* No special import/export declaration */
#endif

extern LIB_opt_C_API 
bool MW_CALL_CONV optInitializeWithHandlers(
       mclOutputHandlerFcn error_handler, 
       mclOutputHandlerFcn print_handler);

extern LIB_opt_C_API 
bool MW_CALL_CONV optInitialize(void);

extern LIB_opt_C_API 
void MW_CALL_CONV optTerminate(void);



extern LIB_opt_C_API 
void MW_CALL_CONV optPrintStackTrace(void);

extern LIB_opt_C_API 
bool MW_CALL_CONV mlxEvalIms(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_opt_C_API 
bool MW_CALL_CONV mlxEvalTree(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_opt_C_API 
bool MW_CALL_CONV mlxFTreeIII(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);

extern LIB_opt_C_API 
bool MW_CALL_CONV mlxInsensitivelearning(int nlhs, mxArray *plhs[], int nrhs, mxArray 
                                         *prhs[]);

extern LIB_opt_C_API 
bool MW_CALL_CONV mlxMain(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[]);


#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

/* On Windows, use __declspec to control the exported API */
#if defined(_MSC_VER) || defined(__BORLANDC__)

#ifdef EXPORTING_opt
#define PUBLIC_opt_CPP_API __declspec(dllexport)
#else
#define PUBLIC_opt_CPP_API __declspec(dllimport)
#endif

#define LIB_opt_CPP_API PUBLIC_opt_CPP_API

#else

#if !defined(LIB_opt_CPP_API)
#if defined(LIB_opt_C_API)
#define LIB_opt_CPP_API LIB_opt_C_API
#else
#define LIB_opt_CPP_API /* empty! */ 
#endif
#endif

#endif

extern LIB_opt_CPP_API void MW_CALL_CONV EvalIms(int nargout, mwArray& ms, const mwArray& y, const mwArray& p);

extern LIB_opt_CPP_API void MW_CALL_CONV EvalTree(int nargout, mwArray& Err, mwArray& Mu, mwArray& YFT, const mwArray& AugX, const mwArray& Y, const mwArray& Tree, const mwArray& C);

extern LIB_opt_CPP_API void MW_CALL_CONV FTreeIII(int nargout, mwArray& Tree, mwArray& C, mwArray& Err, const mwArray& AugX, const mwArray& Y, const mwArray& Options, const mwArray& r);

extern LIB_opt_CPP_API void MW_CALL_CONV insensitivelearning(int nargout, mwArray& w, const mwArray& X, const mwArray& Y, const mwArray& nAugX, const mwArray& r);

extern LIB_opt_CPP_API void MW_CALL_CONV main(int nargout, mwArray& xxx, const mwArray& aaa, const mwArray& bbb);

#endif
#endif
