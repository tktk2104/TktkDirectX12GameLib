#include "TktkFileIo/lodepmx.h"

#include <array>
#include <vector>
#include <string>
#include <filesystem>
#include <unordered_map>

namespace tktkFileIo
{
	constexpr char PmxSignature_1[4]{ 'P', 'M', 'X', ' ' };
	constexpr char PmxSignature_2[4]{ 'P', 'm', 'x', ' ' };

	inline std::string loadString(FILE* fp)
	{
		// �e�L�X�g�̒������擾
		int textSize{};
		fread(&textSize, sizeof(int), 1, fp);

		if (textSize == 0) return "";

		// ���C�h������Ƃ��ăe�L�X�g���擾
		size_t loadSize = sizeof(char) * textSize;
		std::array<wchar_t, 512> wBuffer{};
		fread(wBuffer.data(), loadSize, 1, fp);
		auto wStr = std::wstring(&wBuffer[0], &wBuffer[0] + textSize / 2);

		// ���̎󂯎M��p��
		std::vector<char> rawStr{};
		rawStr.resize(textSize);

		// �ϊ���̕�����
		size_t convLength;

		// �ϊ�
		wcstombs_s(&convLength, rawStr.data(), rawStr.size(), wStr.c_str(), textSize);

		// std::string�ɕϊ�����
		return std::string(rawStr.data());
	}

	lodepmx::loadData lodepmx::load(const std::string& fileName)
	{
		// ���炩���ߓǂݍ��݌��ʍ\���̂�p�ӂ���
		lodepmx::loadData result{};

		FILE* fp { nullptr };
		fopen_s(&fp, fileName.c_str(), "rb");

		// �t�@�C���ǂݍ��݂Ɏ��s������I��
		if (fp == nullptr) return lodepmx::loadData();

		// �V�O�l�`��
		char signature[4]{};
		fread(signature, sizeof(char[4]), 1, fp);

		// �s���ȃV�O�l�`����������I��
		for (size_t i = 0; i < 4U; i++)
		{
			if (signature[i] != PmxSignature_1[i] && signature[i] != PmxSignature_2[i]) return lodepmx::loadData();
		}

		// �o�[�W�������
		float version{};
		fread(&version, sizeof(float), 1, fp);

		// Pmx�w�b�_�[�̑傫��
		char pmxHeaderSize{};
		fread(&pmxHeaderSize, sizeof(char), 1, fp);

		// Pmx�w�b�_�[
		std::vector<char> pmxHeaderdata{};
		pmxHeaderdata.resize(pmxHeaderSize);
		fread(pmxHeaderdata.data(), sizeof(char) * pmxHeaderdata.size(), 1, fp);

		// ����Ȃ�Pmx�w�b�_�[�̏�����͂���
		for (size_t i = pmxHeaderdata.size(); i < 8U; i++) pmxHeaderdata.push_back(4U);

		// �G���R�[�h�̎��
		const char& encodeType			= pmxHeaderdata.at(0U);
		// �ǉ���UV�̐�
		const char& appendUvNum			= pmxHeaderdata.at(1U);
		// ���_�C���f�b�N�X�̌^�̃T�C�Y
		const char& vertIndexSize		= pmxHeaderdata.at(2U);
		// �e�N�X�`���C���f�b�N�X�̌^�̃T�C�Y
		const char& textureIndexSize	= pmxHeaderdata.at(3U);
		// �}�e���A���C���f�b�N�X�T�C�Y
		const char& materialIndexSize	= pmxHeaderdata.at(4U);
		// �{�[���C���f�b�N�X�T�C�Y
		const char& boneIndexSize		= pmxHeaderdata.at(5U);
		// ���[�t�C���f�b�N�X�T�C�Y
		const char& morphIndexSize		= pmxHeaderdata.at(6U);
		// ���̃C���f�b�N�X�T�C�Y
		const char& rigidBodyIndexSize	= pmxHeaderdata.at(7U);

		// UTF8�G���R�[�h��������I��
		if ((encodeType != 0)) return lodepmx::loadData();

		// ���f����
		std::string rawModelName = loadString(fp);

		// ���f�����i�p��j
		std::string engModelName = loadString(fp);
		
		// �R�����g
		std::string comment = loadString(fp);
		
		// �R�����g�i�p��j
		std::string engComment = loadString(fp);

		// ���_��
		int vertexNum{};
		fread(&vertexNum, sizeof(int), 1, fp);

		// �ǂݍ��݌��ʍ\���̂̒��_���̔z��̃��������m�ۂ���
		result.vertexData.reserve(vertexNum);

		for (size_t vertIndex = 0; vertIndex < static_cast<size_t>(vertexNum); vertIndex++)
		{
			// ���W
			tktkMath::Vector3	pos{ };
			fread(&pos,		sizeof(tktkMath::Vector3), 1, fp);

			// �@��
			tktkMath::Vector3	normal{ };
			fread(&normal,	sizeof(tktkMath::Vector3), 1, fp);

			// UV���W
			tktkMath::Vector2	uv{ };
			fread(&uv,		sizeof(tktkMath::Vector2), 1, fp);

			for (size_t appendUvIndex = 0; appendUvIndex < static_cast<const size_t&>(appendUvNum); appendUvIndex++)
			{
				// �ǉ�UV
				float	appendUv[4]{};
				fread(appendUv, sizeof(float[4]), 1, fp);
			}

			// �E�F�C�g�̌`��
			char weightType{};
			fread(&weightType, sizeof(char), 1, fp);

			int					boneNo[4]		{ 0,	0,	  0,    0 };	// �{�[���ԍ�
			float				boneWeight[4]	{ 0.0f, 0.0f, 0.0f, 0.0f };	// �{�[���E�F�C�g
			tktkMath::Matrix3	sdefParam		{ };						// SDEF�l

			// �������T�C�Y�̍��C���f�b�N�X�ǂݍ��ݗp�o�b�t�@�i4�o�C�g�ŕۑ�����Ă���ꍇ�A���̕ϐ��͎g��Ȃ��j
			char	sizeOneBoneIndex{};
			short	sizeTwoBoneIndex{};

			switch (weightType)
			{
			case 0:	//�gBDEF1�h�`��

				// �{�[���C���f�b�N�X��ǂݍ���
				switch (vertIndexSize)
				{
				case 1:

					fread(&sizeOneBoneIndex, sizeof(char), 1, fp);
					boneNo[0] = static_cast<int>(sizeOneBoneIndex);
					break;

				case 2:

					fread(&sizeTwoBoneIndex, sizeof(short), 1, fp);
					boneNo[0] = static_cast<int>(sizeTwoBoneIndex);
					break;

				case 4:

					fread(boneNo, sizeof(int), 1, fp);
					break;
				}

				// �{�[���E�F�C�g�͒萔
				boneWeight[0] = 1.0f;
				break;

			case 1:	//�gBDEF2�h�`��

				for (size_t boneNoIndex = 0; boneNoIndex < 2U; boneNoIndex++)
				{
					// �{�[���C���f�b�N�X��ǂݍ���
					switch (vertIndexSize)
					{
					case 1:

						fread(&sizeOneBoneIndex, sizeof(char), 1, fp);
						boneNo[boneNoIndex] = static_cast<int>(sizeOneBoneIndex);
						break;

					case 2:

						fread(&sizeTwoBoneIndex, sizeof(short), 1, fp);
						boneNo[boneNoIndex] = static_cast<int>(sizeTwoBoneIndex);
						break;

					case 4:

						fread(&boneNo[boneNoIndex], sizeof(int), 1, fp);
						break;
					}
				}

				// �{�[���E�F�C�g��ǂݍ���
				fread(boneWeight, sizeof(float), 1, fp);
				boneWeight[1] = 1.0f - boneWeight[0];
				break;

			case 2:	//�gBDEF4�h�`��

				for (size_t boneNoIndex = 0; boneNoIndex < 4U; boneNoIndex++)
				{
					// �{�[���C���f�b�N�X��ǂݍ���
					switch (vertIndexSize)
					{
					case 1:

						fread(&sizeOneBoneIndex, sizeof(char), 1, fp);
						boneNo[boneNoIndex] = static_cast<int>(sizeOneBoneIndex);
						break;

					case 2:

						fread(&sizeTwoBoneIndex, sizeof(short), 1, fp);
						boneNo[boneNoIndex] = static_cast<int>(sizeTwoBoneIndex);
						break;

					case 4:

						fread(&boneNo[boneNoIndex], sizeof(int), 1, fp);
						break;
					}
				}

				// �{�[���E�F�C�g��ǂݍ���
				fread(boneWeight, sizeof(float[4]), 1, fp);
				break;

			case 3:	//�gSDEF�h�`��

				for (size_t boneNoIndex = 0; boneNoIndex < 2U; boneNoIndex++)
				{
					// �{�[���C���f�b�N�X��ǂݍ���
					switch (vertIndexSize)
					{
					case 1:

						fread(&sizeOneBoneIndex, sizeof(char), 1, fp);
						boneNo[boneNoIndex] = static_cast<int>(sizeOneBoneIndex);
						break;

					case 2:

						fread(&sizeTwoBoneIndex, sizeof(short), 1, fp);
						boneNo[boneNoIndex] = static_cast<int>(sizeTwoBoneIndex);
						break;

					case 4:

						fread(&boneNo[boneNoIndex], sizeof(int), 1, fp);
						break;
					}
				}

				// �{�[���E�F�C�g��ǂݍ���
				fread(boneWeight, sizeof(float), 1, fp);
				boneWeight[1] = 1.0f - boneWeight[0];

				// SDEF�l��ǂݍ���
				fread(&sdefParam, sizeof(tktkMath::Matrix3), 1, fp);
				break;
			}

			// �G�b�W�{��
			float edge{};
			fread(&edge, sizeof(float), 1, fp);

			tktkMath::Vector3 tangent;
			tktkMath::Vector3 binormal;
			tktkMath::Vector3::orthoNormalize(&normal, &tangent, &binormal);

			// �ǂݍ��񂾒��_���\���̂ɋl�߂ĕۑ�����
			result.vertexData.push_back(
				{
					pos,
					normal,
					uv,
					{ static_cast<unsigned char>(boneNo[0]), static_cast<unsigned char>(boneNo[1]), static_cast<unsigned char>(boneNo[2]), static_cast<unsigned char>(boneNo[3]) },
					{ boneWeight[0], boneWeight[1], boneWeight[2], boneWeight[3] },
					tangent,
					binormal
				}
			);
		}

		// �C���f�b�N�X����ǂݍ���
		int indexNum;
		fread(&indexNum, sizeof(int), 1, fp);

		// �ǂݍ��݌��ʍ\���̂̃C���f�b�N�X���̔z��̃��������m�ۂ���
		result.indexData.reserve(indexNum);

		for (size_t vertIndexIndex = 0; vertIndexIndex < static_cast<size_t>(indexNum); vertIndexIndex++)
		{
			int index{};

			// �������T�C�Y�̒��_�C���f�b�N�X�ǂݍ��ݗp�o�b�t�@�i4�o�C�g�ŕۑ�����Ă���ꍇ�A���̕ϐ��͎g��Ȃ��j
			char	sizeOneVertIndex{};
			short	sizeTwoVertIndex{};

			// ���_�C���f�b�N�X��ǂݍ���
			switch (vertIndexSize)
			{
			case 1:

				fread(&sizeOneVertIndex, sizeof(char), 1, fp);
				index = static_cast<int>(sizeOneVertIndex);
				break;

			case 2:

				fread(&sizeTwoVertIndex, sizeof(short), 1, fp);
				index = static_cast<int>(sizeTwoVertIndex);
				break;

			case 4:

				fread(&index, sizeof(int), 1, fp);
				break;
			}

			// �ǂݍ��񂾃C���f�b�N�X��ۑ�����
			result.indexData.push_back(static_cast<unsigned short>(index));
		}

		// �e�N�X�`���[�̐���ǂݍ���
		int textureNum;
		fread(&textureNum, sizeof(int), 1, fp);

		// �ǂݍ��݌��ʍ\���̂̃e�N�X�`���[���̔z��̃��������m�ۂ���
		result.textureFilePaths.reserve(textureNum);

		for (size_t textureIndex = 0; textureIndex < static_cast<size_t>(textureNum); textureIndex++)
		{
			// �e�N�X�`���p�X��ǂݍ���ŕۑ�����
			result.textureFilePaths.push_back(loadString(fp));
		}

		// �}�e���A������ǂݍ���
		int materialNum;
		fread(&materialNum, sizeof(int), 1, fp);

		// �ǂݍ��݌��ʍ\���̂̃}�e���A�����̔z��̃��������m�ۂ���
		result.materialData.reserve(materialNum);

		for (size_t materialIndex = 0; materialIndex < static_cast<size_t>(materialNum); materialIndex++)
		{
			// �������T�C�Y�̃e�N�X�`���C���f�b�N�X�ǂݍ��ݗp�o�b�t�@�i4�o�C�g�ŕۑ�����Ă���ꍇ�A���̕ϐ��͎g��Ȃ��j
			char	sizeOneTextureIndex{};
			short	sizeTwoTextureIndex{};

			// �}�e���A������ǂݍ���
			std::string materialName = loadString(fp);

			// �}�e���A�����i�p��j��ǂݍ���
			std::string engMaterialName = loadString(fp);

			// �g�U���ːF��ǂݍ���
			tktkMath::Color diffuse{};
			fread(&diffuse, sizeof(tktkMath::Color), 1, fp);

			// ���ʔ��ːF��ǂݍ���
			float specular[3]{};
			fread(specular, sizeof(float[3]), 1, fp);

			// ���ʔ��ˌW����ǂݍ���
			float specularrity{};
			fread(&specularrity, sizeof(float), 1, fp);

			// ���F��ǂݍ���
			float ambient[3]{};
			fread(ambient, sizeof(float[3]), 1, fp);

			// �`��t���O��ǂݍ���
			char drawFlag{};
			fread(&drawFlag, sizeof(char), 1, fp);

			// �G�b�W�J���[��ǂݍ���
			tktkMath::Color edgeColor{};
			fread(&edgeColor, sizeof(tktkMath::Color), 1, fp);

			// �G�b�W�T�C�Y��ǂݍ���
			float edgeSize{};
			fread(&edgeSize, sizeof(float), 1, fp);

			// �A���x�h�}�b�v�̃e�N�X�`���ԍ�
			int	albedoTextureIndex{};
			switch(textureIndexSize)
			{
			case 1:

				fread(&sizeOneTextureIndex, sizeof(char), 1, fp);
				albedoTextureIndex = static_cast<int>(sizeOneTextureIndex);
				break;

			case 2:

				fread(&sizeTwoTextureIndex, sizeof(short), 1, fp);
				albedoTextureIndex = static_cast<int>(sizeTwoTextureIndex);
				break;

			case 4:

				fread(&albedoTextureIndex, sizeof(int), 1, fp);
				break;
			}

			// �X�t�B�A�}�b�v�̃e�N�X�`���ԍ�
			int sphereMapTextureIndex{};
			switch (textureIndexSize)
			{
			case 1:

				fread(&sizeOneTextureIndex, sizeof(char), 1, fp);
				sphereMapTextureIndex = static_cast<int>(sizeOneTextureIndex);
				break;

			case 2:

				fread(&sizeTwoTextureIndex, sizeof(short), 1, fp);
				sphereMapTextureIndex = static_cast<int>(sizeTwoTextureIndex);
				break;

			case 4:

				fread(&sphereMapTextureIndex, sizeof(int), 1, fp);
				break;
			}

			// �X�t�B�A���[�h�̎�ނ�ǂݍ���
			char sphereModeType{};
			fread(&sphereModeType, sizeof(char), 1, fp);

			// ���p�g�D�[���t���O��ǂݍ���
			char toonFlag{};
			fread(&toonFlag, sizeof(char), 1, fp);

			// �g�D�[���e�N�X�`���C���f�b�N�X��ǂݍ���
			int toonTextureIndex{};
			if (toonFlag == 0)
			{
				switch (textureIndexSize)
				{
				case 1:

					fread(&sizeOneTextureIndex, sizeof(char), 1, fp);
					toonTextureIndex = static_cast<int>(sizeOneTextureIndex);
					break;

				case 2:

					fread(&sizeTwoTextureIndex, sizeof(short), 1, fp);
					toonTextureIndex = static_cast<int>(sizeTwoTextureIndex);
					break;

				case 4:

					fread(&toonTextureIndex, sizeof(int), 1, fp);
					break;
				}
			}
			else
			{
				fread(&sizeOneTextureIndex, sizeof(char), 1, fp);
				toonTextureIndex = static_cast<int>(sizeOneTextureIndex);
			}

			// ��������ǂݍ���
			std::string text = loadString(fp);

			// �Ή����钸�_����ǂݍ���
			int indicesNum{};
			fread(&indicesNum, sizeof(int), 1, fp);

			// �ǂݍ��񂾃}�e���A�����\���̂ɋl�߂ĕۑ�����
			result.materialData.push_back(
				{
					static_cast<unsigned int>(indexNum),
					{ ambient[0], ambient[1], ambient[2], 1.0f },
					diffuse,
					{ specular[0], specular[1], specular[2], 1.0f },
					{ 0.1f, 1.0f },
					1.0f,
					static_cast<unsigned int>(albedoTextureIndex)
				}
			);
		}

		// �{�[������ǂݍ���
		int boneNum;
		fread(&boneNum, sizeof(int), 1, fp);

		// �ǂݍ��݌��ʍ\���̂̃{�[�����̔z��̃��������m�ۂ���
		result.boneData.reserve(boneNum);
		
		for (size_t boneIndex = 0; boneIndex < static_cast<size_t>(boneNum); boneIndex++)
		{
			// �������T�C�Y�̃{�[���C���f�b�N�X�ǂݍ��ݗp�o�b�t�@�i4�o�C�g�ŕۑ�����Ă���ꍇ�A���̕ϐ��͎g��Ȃ��j
			char	sizeOneBoneIndex{};
			short	sizeTwoBoneIndex{};

			// �{�[������ǂݍ���
			std::string boneName = loadString(fp);

			// �{�[�����i�p��j��ǂݍ���
			std::string engBoneName = loadString(fp);

			// ���W��ǂݍ���
			tktkMath::Vector3	pos{ };
			fread(&pos, sizeof(tktkMath::Vector3), 1, fp);

			// �e�{�[���C���f�b�N�X��ǂݍ���
			int parentNo{};
			switch (boneIndexSize)
			{
			case 1:

				fread(&sizeOneBoneIndex, sizeof(char), 1, fp);
				parentNo = static_cast<int>(sizeOneBoneIndex);
				break;

			case 2:

				fread(&sizeTwoBoneIndex, sizeof(short), 1, fp);
				parentNo = static_cast<int>(sizeTwoBoneIndex);
				break;

			case 4:

				fread(&parentNo, sizeof(int), 1, fp);
				break;
			}

			// �ό`�K�w��ǂݍ���
			int transformHierarchy{};
			fread(&transformHierarchy, sizeof(int), 1, fp);

			// �{�[���t���O��ǂݍ���
			unsigned short boneFlag{};
			fread(&boneFlag, sizeof(unsigned short), 1, fp);


			// �q�{�[���A�ڑ�����i�{�[���t���O�ɂ���Ďg�p����ϐ����ς��j
			int nextNo{};
			tktkMath::Vector3	posOfset{};

			// �{�[���Ŏw�肷��t���O�������Ă�����
			if ((boneFlag & 0x0001) != 0U)
			{
				switch (boneIndexSize)
				{
				case 1:

					fread(&sizeOneBoneIndex, sizeof(char), 1, fp);
					nextNo = static_cast<int>(sizeOneBoneIndex);
					break;

				case 2:

					fread(&sizeTwoBoneIndex, sizeof(short), 1, fp);
					nextNo = static_cast<int>(sizeTwoBoneIndex);
					break;

				case 4:

					fread(&nextNo, sizeof(int), 1, fp);
					break;
				}
			}
			else
			{
				fread(&posOfset, sizeof(tktkMath::Vector3), 1, fp);
			}

			// �t�^�e�{�[��
			int grantParentNo{};

			// �t�^��
			float grantRate{};

			// ��]�t�^�A�ړ��t�^�t���O�������Ă�����
			if ((boneFlag & 0x0100) != 0U || (boneFlag & 0x0200) != 0U)
			{
				fread(&grantParentNo, sizeof(int), 1, fp);
				fread(&grantRate, sizeof(float), 1, fp);
			}

			// ���̕���
			tktkMath::Vector3	axisVec{};

			// ���Œ�t���O�������Ă�����
			if ((boneFlag & 0x0400) != 0U)
			{
				fread(&axisVec, sizeof(tktkMath::Vector3), 1, fp);
			}

			// ���ꂼ��̎��̕���
			tktkMath::Vector3	axisXVec{};
			tktkMath::Vector3	axisZVec{};

			// ���[�J�����t���O�������Ă�����
			if ((boneFlag & 0x0800) != 0U)
			{
				fread(&axisXVec, sizeof(tktkMath::Vector3), 1, fp);
				fread(&axisZVec, sizeof(tktkMath::Vector3), 1, fp);
			}

			// �L�[�l
			int keyValue{};

			// �O���e�ό`�t���O�������Ă�����
			if ((boneFlag & 0x2000) != 0U)
			{
				fread(&keyValue, sizeof(int), 1, fp);
			}

			// IK�^�[�Q�b�g�{�[��
			int ikTargetNo{};

			// Ik���[�v��
			int ikLoopCount{};

			// Ik��]�p�x�����i���W�A���p�j
			float ikLimitRotateAngleRad{};

			// Ik�����N��
			int ikLinkNum{};

			// Ik�t���O�������Ă�����
			if ((boneFlag & 0x0020) != 0U)
			{
				switch (boneIndexSize)
				{
				case 1:

					fread(&sizeOneBoneIndex, sizeof(char), 1, fp);
					ikTargetNo = static_cast<int>(sizeOneBoneIndex);
					break;

				case 2:

					fread(&sizeTwoBoneIndex, sizeof(short), 1, fp);
					ikTargetNo = static_cast<int>(sizeTwoBoneIndex);
					break;

				case 4:

					fread(&ikTargetNo, sizeof(int), 1, fp);
					break;
				}

				fread(&ikLoopCount, sizeof(int), 1, fp);
				fread(&ikLimitRotateAngleRad, sizeof(float), 1, fp);
				fread(&ikLinkNum, sizeof(int), 1, fp);

				for (size_t ikLinkIndex = 0; ikLinkIndex < static_cast<size_t>(ikLinkNum); ikLinkIndex++)
				{
					// IK�����N�{�[��
					int ikLinkNo{};

					switch (boneIndexSize)
					{
					case 1:

						fread(&sizeOneBoneIndex, sizeof(char), 1, fp);
						ikLinkNo = static_cast<int>(sizeOneBoneIndex);
						break;

					case 2:

						fread(&sizeTwoBoneIndex, sizeof(short), 1, fp);
						ikLinkNo = static_cast<int>(sizeTwoBoneIndex);
						break;

					case 4:

						fread(&ikLinkNo, sizeof(int), 1, fp);
						break;
					}

					// ��]�����t���O
					char ikRoateLimitFlag{};
					fread(&ikRoateLimitFlag, sizeof(char), 1, fp);

					// ��]����
					tktkMath::Vector3	ikRoateLimit{};
					fread(&ikRoateLimit, sizeof(tktkMath::Vector3), 1, fp);
				}
			}

			// �ǂݍ��񂾃{�[�����\���̂ɋl�߂ĕۑ�����
			result.boneData.push_back(
				{
					boneName,
					static_cast<unsigned short>(parentNo),
					pos
				}
			);
		}

		return result;
	}
}