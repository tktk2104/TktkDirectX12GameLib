#ifndef TKTK_MATH_LIB_DEFINITION_H_
#define TKTK_MATH_LIB_DEFINITION_H_

#if defined(NDEBUG) || !defined(_DEBUG)
#pragma comment( lib, "TktkMathLib_mt.lib" )
#else
#pragma comment( lib, "TktkMathLib_mtd.lib" )
#endif
#endif // !TKTK_MATH_LIB_DEFINITION_H_