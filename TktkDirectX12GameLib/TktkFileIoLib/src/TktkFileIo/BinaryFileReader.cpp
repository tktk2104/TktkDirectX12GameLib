#include "TktkFileIo/BinaryFileReader.h"

#include <stdexcept>
#include <Windows.h>
#include <fileapi.h>
#include <wrl/wrappers/corewrappers.h>
#include <filesystem>

void BinaryFileReader::fileRead(const std::string & filePath, std::vector<unsigned char>* out)
{
	CREATEFILE2_EXTENDED_PARAMETERS extendedParams = { 0 };
	extendedParams.dwSize = sizeof(CREATEFILE2_EXTENDED_PARAMETERS);
	extendedParams.dwFileAttributes = FILE_ATTRIBUTE_NORMAL;
	extendedParams.dwFileFlags = FILE_FLAG_SEQUENTIAL_SCAN;
	extendedParams.dwSecurityQosFlags = SECURITY_ANONYMOUS;
	extendedParams.lpSecurityAttributes = nullptr;
	extendedParams.hTemplateFile = nullptr;

	std::filesystem::path shaderFilePath(filePath);

	Microsoft::WRL::Wrappers::FileHandle file(
		CreateFile2(
			(LPCWSTR)shaderFilePath.generic_u16string().c_str(),
			GENERIC_READ,
			FILE_SHARE_READ,
			OPEN_EXISTING,
			&extendedParams
		)
	);

	if (file.Get() == INVALID_HANDLE_VALUE)
	{
		throw std::runtime_error("open file error");
	}

	FILE_STANDARD_INFO fileInfo = { 0 };

	if (!GetFileInformationByHandleEx(
		file.Get(),
		FileStandardInfo,
		&fileInfo,
		sizeof(fileInfo)
	))
	{
		throw std::runtime_error("open file error");
	}

	if (fileInfo.EndOfFile.HighPart != 0)
	{
		throw std::runtime_error("open file error");
	}

	out->resize(static_cast<unsigned int>(fileInfo.EndOfFile.LowPart));

	if (!ReadFile(
		file.Get(),
		out->data(),
		static_cast<DWORD>(out->size()),
		nullptr,
		nullptr
	))
	{
		throw std::runtime_error("open file error");
	}
}