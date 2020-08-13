#include "TktkFileIo/lodebmp.h"

#include <filesystem>

namespace tktkFileIo
{
#pragma pack(push, 1)
	struct BmpHeader
	{
		unsigned char	fileType[2];
		unsigned int	fileSize;
		unsigned int	pad;
		unsigned int	bfOffBits;
	};

	struct BmpInfoHeader
	{
		unsigned int	infoHeadSize;
		int				width;
		int				height;
		unsigned short	lanes;
		unsigned short	bitCount;
		unsigned int	compressionType;
		unsigned int	imageDataSize;
		int				xPixPerMeter;
		int				yPixPerMeter;
		unsigned int	clrUsed;
		unsigned int	cirImportant;
	};

	struct BmpPaletteData
	{
		unsigned char red;
		unsigned char green;
		unsigned char blue;
		unsigned char pad;
	};
#pragma pack(pop)

	void lodebmp::load(loadData* out, const std::string& fileName)
	{
		FILE* fp;
		fopen_s(&fp, fileName.c_str(), "rb");

		BmpHeader header{};
		fread(&header, sizeof(BmpHeader), 1, fp);

		BmpInfoHeader infoHeader{};
		fread(&infoHeader, sizeof(BmpInfoHeader), 1, fp);

		out->width	= infoHeader.width;
		out->height = infoHeader.height;
		out->data.resize(infoHeader.width * infoHeader.height * 4);

		for (unsigned int i = 0; i < static_cast<unsigned int>(infoHeader.width * infoHeader.height); i++)
		{
			out->data.at(out->data.size() - 1 - (i * 4 + 0)) = 255U;
			fread(&out->data.at(out->data.size() - 1 - (i * 4 + 3)), sizeof(unsigned char), 1, fp);
			fread(&out->data.at(out->data.size() - 1 - (i * 4 + 2)), sizeof(unsigned char), 1, fp);
			fread(&out->data.at(out->data.size() - 1 - (i * 4 + 1)), sizeof(unsigned char), 1, fp);
		}
	}
}