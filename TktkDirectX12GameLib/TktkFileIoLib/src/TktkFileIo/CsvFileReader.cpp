#include "TktkFileIo/CsvFileReader.h"

#include <stdexcept>
#include <fstream>
#include <sstream>

inline std::vector<std::string> textSplit(const std::string& beforSplitText, char spritChar)
{
	std::vector<std::string> result;

	std::istringstream strengStream(beforSplitText);

	std::string afterSpritWord;

	while (std::getline(strengStream, afterSpritWord, spritChar))
	{
		result.push_back(afterSpritWord);
	}

	return result;
}

std::vector<std::vector<std::string>> tktkFileIo::CsvFileReader::fileRead(const std::string& filePath, char spritChar)
{
	std::ifstream ifs(filePath.c_str());

	if (!ifs.is_open())
	{
		throw std::runtime_error("load file error");
	}

	std::vector<std::vector<std::string>> result;

	std::string line;

	while (std::getline(ifs, line))
	{
		result.push_back(textSplit(line, spritChar));
	}

	return result;
}
