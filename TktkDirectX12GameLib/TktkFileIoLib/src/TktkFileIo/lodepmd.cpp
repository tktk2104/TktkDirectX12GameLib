#include "TktkFileIo/lodepmd.h"

#include <filesystem>
#include <unordered_map>

namespace tktkFileIo
{
	struct PmdHeader
	{
		float	version;
		char	modelName[20];
		char	comment[256];
	};

#pragma pack(push, 1)
	struct PmdVertex
	{
		tktkMath::Vector3	pos;
		tktkMath::Vector3	normal;
		tktkMath::Vector2	uv;
		unsigned short		boneNo[2];
		unsigned char		boneWeight;
		unsigned char		edgeFlg;
	};

	struct PmdMaterial
	{
		tktkMath::Color		diffuse;
		float				specularrity;
		float				speqular[3];
		float				ambient[3];
		unsigned char		toonIdx;
		unsigned char		edgeFlg;
		unsigned int		indicesNum;
		char				textureFilePath[20];
	};

	struct PmdBone
	{
		char				boneName[20];
		unsigned short		parentNo;
		unsigned short		nextNo;
		unsigned char		type;
		unsigned short		ikBoneNo;
		tktkMath::Vector3	pos;
	};
#pragma pack(pop)

	struct BoneNode
	{
		int						boneIndex;
		tktkMath::Vector3		startPos;
		tktkMath::Vector3		endPos;
		std::vector<BoneNode*>	children;
	};

	void lodepmd::load(lodepmd::loadData* out, const std::string& fileName)
	{
		FILE* fp;
		fopen_s(&fp, fileName.c_str(), "rb");

		char signature[3] = {};
		fread(signature, sizeof(signature), 1, fp);

		PmdHeader pmdHeader{};
		fread(&pmdHeader, sizeof(PmdHeader), 1, fp);

		unsigned int vertexNum;
		fread(&vertexNum, sizeof(unsigned int), 1, fp);

		std::vector<PmdVertex> tempVertices(vertexNum);
		fread(tempVertices.data(), tempVertices.size() * sizeof(PmdVertex), 1, fp);

		unsigned int indexNum;
		fread(&indexNum, sizeof(unsigned int), 1, fp);

		out->indexData.clear();
		out->indexData.resize(indexNum);
		fread(out->indexData.data(), out->indexData.size() * sizeof(unsigned short), 1, fp);

		unsigned int materialNum;
		fread(&materialNum, sizeof(unsigned int), 1, fp);

		std::vector<PmdMaterial> tempMaterialData(materialNum);
		fread(tempMaterialData.data(), tempMaterialData.size() * sizeof(PmdMaterial), 1, fp);

		unsigned short boneNum;
		fread(&boneNum, sizeof(unsigned short), 1, fp);

		std::vector<PmdBone> tempBoneData(boneNum);
		fread(tempBoneData.data(), tempBoneData.size() * sizeof(PmdBone), 1, fp);

		fclose(fp);

		out->vertexData.clear();
		out->vertexData.resize(vertexNum);
		for (unsigned int i = 0; i < vertexNum; i++)
		{
			out->vertexData.at(i).point = tempVertices.at(i).pos;
			out->vertexData.at(i).normal = tempVertices.at(i).normal;
			out->vertexData.at(i).texcoord = tempVertices.at(i).uv;

			out->vertexData.at(i).bones[0] = static_cast<unsigned int>(tempVertices.at(i).boneNo[0]);
			out->vertexData.at(i).bones[1] = static_cast<unsigned int>(tempVertices.at(i).boneNo[1]);
			out->vertexData.at(i).bones[2] = 0U;
			out->vertexData.at(i).bones[3] = 0U;

			// TODO : 教材の仕様上ボーン１のみでの実装
			out->vertexData.at(i).weight[0] = static_cast<float>(tempVertices.at(i).boneWeight) / 100.0f;
			out->vertexData.at(i).weight[1] = (1.0f - out->vertexData.at(i).weight[0]);
			out->vertexData.at(i).weight[2] = 0.0f;
			out->vertexData.at(i).weight[3] = 0.0f;

			tktkMath::Vector3::orthoNormalize(
				&out->vertexData.at(i).normal,
				&out->vertexData.at(i).tangent,
				&out->vertexData.at(i).binormal
			);
		}

		std::string baseTexturePath;
		std::filesystem::path meshPath(fileName);
		if (meshPath.has_parent_path())
		{
			baseTexturePath = meshPath.parent_path().string() + "/";
		}

		out->materialData.clear();
		out->materialData.resize(materialNum);
		for (unsigned int i = 0; i < materialNum; i++)
		{
			out->materialData.at(i).indexCount = tempMaterialData.at(i).indicesNum;
			out->materialData.at(i).ambient = {
				tempMaterialData.at(i).ambient[0],
				tempMaterialData.at(i).ambient[1],
				tempMaterialData.at(i).ambient[2],
				1.0f
			};
			out->materialData.at(i).diffuse = tempMaterialData.at(i).diffuse;
			out->materialData.at(i).speqular = {
				tempMaterialData.at(i).speqular[0],
				tempMaterialData.at(i).speqular[1],
				tempMaterialData.at(i).speqular[2],
				1.0f
			};
			out->materialData.at(i).emissive = { 0.1f, 1.0f };
			out->materialData.at(i).shiniess = 1.0f;
			out->materialData.at(i).textureFilePath = (std::string(tempMaterialData.at(i).textureFilePath) == "") ? "" : baseTexturePath + tempMaterialData.at(i).textureFilePath;
		}

		out->boneData.clear();
		out->boneData.resize(boneNum);

		for (unsigned int i = 0; i < boneNum; i++)
		{
			out->boneData.at(i).name		= tempBoneData.at(i).boneName;
			out->boneData.at(i).parentNo	= tempBoneData.at(i).parentNo;
			out->boneData.at(i).pos			= tempBoneData.at(i).pos;
		}
	}
}