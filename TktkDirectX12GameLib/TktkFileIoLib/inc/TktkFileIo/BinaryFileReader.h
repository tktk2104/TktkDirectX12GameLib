#ifndef BINARY_FILE_READER_H_
#define BINARY_FILE_READER_H_

#include <string>
#include <vector>

namespace tktkFileIo
{
	class BinaryFileReader
	{
	public:

		static void fileRead(const std::string& filePath, std::vector<unsigned char>* out);
	};
}
#endif // !BINARY_FILE_READER_H_