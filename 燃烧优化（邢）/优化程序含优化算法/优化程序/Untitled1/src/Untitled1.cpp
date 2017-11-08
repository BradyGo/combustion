//
// MATLAB Compiler: 4.17 (R2012a)
// Date: Mon Oct 09 21:06:07 2017
// Arguments: "-B" "macro_default" "-W" "cpplib:Untitled1" "-T" "link:lib" "-d"
// "G:\燃烧优化（邢）\优化程序含优化算法\优化程序\Untitled1\src" "-w"
// "enable:specified_file_mismatch" "-w" "enable:repeated_file" "-w"
// "enable:switch_ignored" "-w" "enable:missing_lib_sentinel" "-w"
// "enable:demo_license" "-v"
// "G:\燃烧优化（邢）\优化程序含优化算法\优化程序\EvalIms.m"
// "G:\燃烧优化（邢）\优化程序含优化算法\优化程序\EvalTree.m"
// "G:\燃烧优化（邢）\优化程序含优化算法\优化程序\FTreeIII.m"
// "G:\燃烧优化（邢）\优化程序含优化算法\优化程序\insensitivelearning.m"
// "G:\燃烧优化（邢）\优化程序含优化算法\优化程序\main.m" 
//

#include <stdio.h>
#define EXPORTING_Untitled1 1
#include "Untitled1.h"

static HMCRINSTANCE _mcr_inst = NULL;


#if defined( _MSC_VER) || defined(__BORLANDC__) || defined(__WATCOMC__) || defined(__LCC__)
#ifdef __LCC__
#undef EXTERN_C
#endif
#include <windows.h>

static char path_to_dll[_MAX_PATH];

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, void *pv)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        if (GetModuleFileName(hInstance, path_to_dll, _MAX_PATH) == 0)
            return FALSE;
    }
    else if (dwReason == DLL_PROCESS_DETACH)
    {
    }
    return TRUE;
}
#endif
#ifdef __cplusplus
extern "C" {
#endif

static int mclDefaultPrintHandler(const char *s)
{
  return mclWrite(1 /* stdout */, s, sizeof(char)*strlen(s));
}

#ifdef __cplusplus
} /* End extern "C" block */
#endif

#ifdef __cplusplus
extern "C" {
#endif

static int mclDefaultErrorHandler(const char *s)
{
  int written = 0;
  size_t len = 0;
  len = strlen(s);
  written = mclWrite(2 /* stderr */, s, sizeof(char)*len);
  if (len > 0 && s[ len-1 ] != '\n')
    written += mclWrite(2 /* stderr */, "\n", sizeof(char));
  return written;
}

#ifdef __cplusplus
} /* End extern "C" block */
#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_Untitled1_C_API
#define LIB_Untitled1_C_API /* No special import/export declaration */
#endif

LIB_Untitled1_C_API 
bool MW_CALL_CONV Untitled1InitializeWithHandlers(
    mclOutputHandlerFcn error_handler,
    mclOutputHandlerFcn print_handler)
{
    int bResult = 0;
  if (_mcr_inst != NULL)
    return true;
  if (!mclmcrInitialize())
    return false;
  if (!GetModuleFileName(GetModuleHandle("Untitled1"), path_to_dll, _MAX_PATH))
    return false;
    {
        mclCtfStream ctfStream = 
            mclGetEmbeddedCtfStream(path_to_dll);
        if (ctfStream) {
            bResult = mclInitializeComponentInstanceEmbedded(   &_mcr_inst,
                                                                error_handler, 
                                                                print_handler,
                                                                ctfStream);
            mclDestroyStream(ctfStream);
        } else {
            bResult = 0;
        }
    }  
    if (!bResult)
    return false;
  return true;
}

LIB_Untitled1_C_API 
bool MW_CALL_CONV Untitled1Initialize(void)
{
  return Untitled1InitializeWithHandlers(mclDefaultErrorHandler, mclDefaultPrintHandler);
}

LIB_Untitled1_C_API 
void MW_CALL_CONV Untitled1Terminate(void)
{
  if (_mcr_inst != NULL)
    mclTerminateInstance(&_mcr_inst);
}

LIB_Untitled1_C_API 
void MW_CALL_CONV Untitled1PrintStackTrace(void) 
{
  char** stackTrace;
  int stackDepth = mclGetStackTrace(&stackTrace);
  int i;
  for(i=0; i<stackDepth; i++)
  {
    mclWrite(2 /* stderr */, stackTrace[i], sizeof(char)*strlen(stackTrace[i]));
    mclWrite(2 /* stderr */, "\n", sizeof(char)*strlen("\n"));
  }
  mclFreeStackTrace(&stackTrace, stackDepth);
}


LIB_Untitled1_C_API 
bool MW_CALL_CONV mlxEvalIms(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "EvalIms", nlhs, plhs, nrhs, prhs);
}

LIB_Untitled1_C_API 
bool MW_CALL_CONV mlxEvalTree(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "EvalTree", nlhs, plhs, nrhs, prhs);
}

LIB_Untitled1_C_API 
bool MW_CALL_CONV mlxFTreeIII(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "FTreeIII", nlhs, plhs, nrhs, prhs);
}

LIB_Untitled1_C_API 
bool MW_CALL_CONV mlxInsensitivelearning(int nlhs, mxArray *plhs[], int nrhs, mxArray 
                                         *prhs[])
{
  return mclFeval(_mcr_inst, "insensitivelearning", nlhs, plhs, nrhs, prhs);
}

LIB_Untitled1_C_API 
bool MW_CALL_CONV mlxMain(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "main", nlhs, plhs, nrhs, prhs);
}

LIB_Untitled1_CPP_API 
void MW_CALL_CONV EvalIms(int nargout, mwArray& ms, const mwArray& y, const mwArray& p)
{
  mclcppMlfFeval(_mcr_inst, "EvalIms", nargout, 1, 2, &ms, &y, &p);
}

LIB_Untitled1_CPP_API 
void MW_CALL_CONV EvalTree(int nargout, mwArray& Err, mwArray& Mu, mwArray& YFT, const 
                           mwArray& AugX, const mwArray& Y, const mwArray& Tree, const 
                           mwArray& C)
{
  mclcppMlfFeval(_mcr_inst, "EvalTree", nargout, 3, 4, &Err, &Mu, &YFT, &AugX, &Y, &Tree, &C);
}

LIB_Untitled1_CPP_API 
void MW_CALL_CONV FTreeIII(int nargout, mwArray& Tree, mwArray& C, mwArray& Err, const 
                           mwArray& AugX, const mwArray& Y, const mwArray& Options, const 
                           mwArray& r)
{
  mclcppMlfFeval(_mcr_inst, "FTreeIII", nargout, 3, 4, &Tree, &C, &Err, &AugX, &Y, &Options, &r);
}

LIB_Untitled1_CPP_API 
void MW_CALL_CONV insensitivelearning(int nargout, mwArray& w, const mwArray& X, const 
                                      mwArray& Y, const mwArray& nAugX, const mwArray& r)
{
  mclcppMlfFeval(_mcr_inst, "insensitivelearning", nargout, 1, 4, &w, &X, &Y, &nAugX, &r);
}

LIB_Untitled1_CPP_API 
void MW_CALL_CONV main()
{
  mclcppMlfFeval(_mcr_inst, "main", 0, 0, 0);
}

