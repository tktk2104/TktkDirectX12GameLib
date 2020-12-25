#ifndef CSV_FILE_READER_H_
#define CSV_FILE_READER_H_

#include <string>
#include <vector>

namespace tktkFileIo
{
	class CsvFileReader
	{
	public:

		static std::vector<std::vector<std::string>> fileRead(const std::string& filePath, char spritChar);
	};
}
#endif // !CSV_FILE_READER_H_