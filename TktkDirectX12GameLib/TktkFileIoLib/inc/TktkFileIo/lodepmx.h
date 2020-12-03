#ifndef LODE_PMX_H_
#define LODE_PMX_H_

#include <string>
#include <vector>
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector2.h>
#include <TktkMath/Structs/Vector3.h>
#include <TktkMath/Structs/Matrix3.h>

namespace tktkFileIo
{
	class lodepmx
	{
	public:

		struct loadData
		{
			struct OutVertex
			{
				tktkMath::Vector3	point		{};
				tktkMath::Vector3	normal		{};
				tktkMath::Vector2	texcoord	{};
				unsigned char		bones[4]	{};
				float				weight[4]	{};
				tktkMath::Vector3	tangent		{};
				tktkMath::Vector3	binormal	{};
			};

			struct OutMaterial
			{
				unsigned int		indexCount	{};
				tktkMath::Color		ambient		{};
				tktkMath::Color		diffuse		{};
				tktkMath::Color		speqular	{};
				tktkMath::Color		emissive	{};
				float				shiniess	{};
				unsigned int		textureId	{};
			};

			struct OutBone
			{
				std::string			name		{};
				unsigned short		parentNo	{};
				tktkMath::Vector3	pos			{};
			};

			std::vector<OutVertex>		vertexData		{};
			std::vector<unsigned short> indexData		{};
			std::vector<std::string>	textureFilePaths{};
			std::vector<OutMaterial>	materialData	{};
			std::vector<OutBone>		boneData		{};
		};

	public:

		static loadData load(const std::string& fileName);
	};
}
#endif // !LODE_PMX_H_
