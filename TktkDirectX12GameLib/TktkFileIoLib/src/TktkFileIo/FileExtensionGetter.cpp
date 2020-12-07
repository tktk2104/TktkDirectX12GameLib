#include "TktkFileIo/FileExtensionGetter.h"

namespace tktkFileIo
{
	std::string FileExtensionGetter::get(const std::string& filePath)
	{
		size_t extensionPos = filePath.rfind('.');

		return filePath.substr(extensionPos + 1U);
	}
}