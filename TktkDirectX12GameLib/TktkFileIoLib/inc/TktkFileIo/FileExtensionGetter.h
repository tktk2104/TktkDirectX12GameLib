#ifndef FILE_EXTENSION_GETTER_H_
#define FILE_EXTENSION_GETTER_H_

#include <string>

namespace tktkFileIo
{
	class FileExtensionGetter
	{
	public:

		// �g���q���擾����
		static std::string get(const std::string& filePath);
	};
}
#endif // !FILE_EXTENSION_GETTER_H_