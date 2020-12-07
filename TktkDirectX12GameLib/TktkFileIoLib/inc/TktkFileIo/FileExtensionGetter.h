#ifndef FILE_EXTENSION_GETTER_H_
#define FILE_EXTENSION_GETTER_H_

#include <string>

namespace tktkFileIo
{
	class FileExtensionGetter
	{
	public:

		// 拡張子を取得する
		static std::string get(const std::string& filePath);
	};
}
#endif // !FILE_EXTENSION_GETTER_H_