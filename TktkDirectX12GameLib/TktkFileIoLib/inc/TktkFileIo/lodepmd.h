#ifndef LODE_PMD_H_
#define LODE_PMD_H_

#include <string>
#include <vector>
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector2.h>
#include <TktkMath/Structs/Vector3.h>

namespace tktk
{
	class lodepmd
	{
	public:

		struct loadData
		{
			struct OutVertex
			{
				tktkMath::Vector3	point;
				tktkMath::Vector3	normal;
				tktkMath::Vector2	texcoord;
				unsigned char		bones[4];
				float				weight[4];
				tktkMath::Vector3	tangent;
				tktkMath::Vector3	binormal;
			};

			struct OutMaterial
			{
				unsigned int		indexCount;
				tktkMath::Color		ambient;
				tktkMath::Color		diffuse;
				tktkMath::Color		speqular;
				tktkMath::Color		emissive;
				float				shiniess;
				std::string			textureFilePath;
			};

			struct OutBone
			{
				std::string			name;
				unsigned short		parentNo;
				tktkMath::Vector3	pos;
			};

			std::vector<OutVertex> vertexData;
			std::vector<unsigned short> indexData;
			std::vector<OutMaterial> materialData;
			std::vector<OutBone> boneData;
		};

	public:

		static void load(loadData* out, const std::string& fileName);
	};
}
#endif // !LODE_PMD_H_
