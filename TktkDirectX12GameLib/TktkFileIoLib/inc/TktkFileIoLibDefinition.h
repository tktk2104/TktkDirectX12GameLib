#ifndef TKTK_FILE_IO_LIB_DEFINITION_H_
#define TKTK_FILE_IO_LIB_DEFINITION_H_

#if defined(NDEBUG) || !defined(_DEBUG)
#pragma comment( lib, "TktkFileIoLib_mt.lib" )
#else
#pragma comment( lib, "TktkFileIoLib_mtd.lib" )
#endif
#endif // !TKTK_FILE_IO_LIB_DEFINITION_H_