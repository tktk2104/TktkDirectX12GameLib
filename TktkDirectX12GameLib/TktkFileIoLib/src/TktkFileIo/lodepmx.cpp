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
		// テキストの長さを取得
		int textSize{};
		fread(&textSize, sizeof(int), 1, fp);

		if (textSize == 0) return "";

		// ワイド文字列としてテキストを取得
		size_t loadSize = sizeof(char) * textSize;
		std::array<wchar_t, 512> wBuffer{};
		fread(wBuffer.data(), loadSize, 1, fp);
		auto wStr = std::wstring(&wBuffer[0], &wBuffer[0] + textSize / 2);

		// 仮の受け皿を用意
		std::vector<char> rawStr{};
		rawStr.resize(textSize);

		// 変換後の文字列
		size_t convLength;

		// 変換
		wcstombs_s(&convLength, rawStr.data(), rawStr.size(), wStr.c_str(), textSize);

		// std::stringに変換する
		return std::string(rawStr.data());
	}

	lodepmx::loadData lodepmx::load(const std::string& fileName)
	{
		// あらかじめ読み込み結果構造体を用意する
		lodepmx::loadData result{};

		FILE* fp { nullptr };
		fopen_s(&fp, fileName.c_str(), "rb");

		// ファイル読み込みに失敗したら終了
		if (fp == nullptr) return lodepmx::loadData();

		// シグネチャ
		char signature[4]{};
		fread(signature, sizeof(char[4]), 1, fp);

		// 不正なシグネチャだったら終了
		for (size_t i = 0; i < 4U; i++)
		{
			if (signature[i] != PmxSignature_1[i] && signature[i] != PmxSignature_2[i]) return lodepmx::loadData();
		}

		// バージョン情報
		float version{};
		fread(&version, sizeof(float), 1, fp);

		// Pmxヘッダーの大きさ
		char pmxHeaderSize{};
		fread(&pmxHeaderSize, sizeof(char), 1, fp);

		// Pmxヘッダー
		std::vector<char> pmxHeaderdata{};
		pmxHeaderdata.resize(pmxHeaderSize);
		fread(pmxHeaderdata.data(), sizeof(char) * pmxHeaderdata.size(), 1, fp);

		// 足りないPmxヘッダーの情報を入力する
		for (size_t i = pmxHeaderdata.size(); i < 8U; i++) pmxHeaderdata.push_back(4U);

		// エンコードの種類
		const char& encodeType			= pmxHeaderdata.at(0U);
		// 追加のUVの数
		const char& appendUvNum			= pmxHeaderdata.at(1U);
		// 頂点インデックスの型のサイズ
		const char& vertIndexSize		= pmxHeaderdata.at(2U);
		// テクスチャインデックスの型のサイズ
		const char& textureIndexSize	= pmxHeaderdata.at(3U);
		// マテリアルインデックスサイズ
		const char& materialIndexSize	= pmxHeaderdata.at(4U);
		// ボーンインデックスサイズ
		const char& boneIndexSize		= pmxHeaderdata.at(5U);
		// モーフインデックスサイズ
		const char& morphIndexSize		= pmxHeaderdata.at(6U);
		// 剛体インデックスサイズ
		const char& rigidBodyIndexSize	= pmxHeaderdata.at(7U);

		// UTF8エンコードだったら終了
		if ((encodeType != 0)) return lodepmx::loadData();

		// モデル名
		std::string rawModelName = loadString(fp);

		// モデル名（英語）
		std::string engModelName = loadString(fp);
		
		// コメント
		std::string comment = loadString(fp);
		
		// コメント（英語）
		std::string engComment = loadString(fp);

		// 頂点数
		int vertexNum{};
		fread(&vertexNum, sizeof(int), 1, fp);

		// 読み込み結果構造体の頂点情報の配列のメモリを確保する
		result.vertexData.reserve(vertexNum);

		for (size_t vertIndex = 0; vertIndex < static_cast<size_t>(vertexNum); vertIndex++)
		{
			// 座標
			tktkMath::Vector3	pos{ };
			fread(&pos,		sizeof(tktkMath::Vector3), 1, fp);

			// 法線
			tktkMath::Vector3	normal{ };
			fread(&normal,	sizeof(tktkMath::Vector3), 1, fp);

			// UV座標
			tktkMath::Vector2	uv{ };
			fread(&uv,		sizeof(tktkMath::Vector2), 1, fp);

			for (size_t appendUvIndex = 0; appendUvIndex < static_cast<const size_t&>(appendUvNum); appendUvIndex++)
			{
				// 追加UV
				float	appendUv[4]{};
				fread(appendUv, sizeof(float[4]), 1, fp);
			}

			// ウェイトの形式
			char weightType{};
			fread(&weightType, sizeof(char), 1, fp);

			int					boneNo[4]		{ 0,	0,	  0,    0 };	// ボーン番号
			float				boneWeight[4]	{ 0.0f, 0.0f, 0.0f, 0.0f };	// ボーンウェイト
			tktkMath::Matrix3	sdefParam		{ };						// SDEF値

			// 小さいサイズの骨インデックス読み込み用バッファ（4バイトで保存されている場合、この変数は使わない）
			char	sizeOneBoneIndex{};
			short	sizeTwoBoneIndex{};

			switch (weightType)
			{
			case 0:	//“BDEF1”形式

				// ボーンインデックスを読み込む
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

				// ボーンウェイトは定数
				boneWeight[0] = 1.0f;
				break;

			case 1:	//“BDEF2”形式

				for (size_t boneNoIndex = 0; boneNoIndex < 2U; boneNoIndex++)
				{
					// ボーンインデックスを読み込む
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

				// ボーンウェイトを読み込む
				fread(boneWeight, sizeof(float), 1, fp);
				boneWeight[1] = 1.0f - boneWeight[0];
				break;

			case 2:	//“BDEF4”形式

				for (size_t boneNoIndex = 0; boneNoIndex < 4U; boneNoIndex++)
				{
					// ボーンインデックスを読み込む
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

				// ボーンウェイトを読み込む
				fread(boneWeight, sizeof(float[4]), 1, fp);
				break;

			case 3:	//“SDEF”形式

				for (size_t boneNoIndex = 0; boneNoIndex < 2U; boneNoIndex++)
				{
					// ボーンインデックスを読み込む
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

				// ボーンウェイトを読み込む
				fread(boneWeight, sizeof(float), 1, fp);
				boneWeight[1] = 1.0f - boneWeight[0];

				// SDEF値を読み込む
				fread(&sdefParam, sizeof(tktkMath::Matrix3), 1, fp);
				break;
			}

			// エッジ倍率
			float edge{};
			fread(&edge, sizeof(float), 1, fp);

			tktkMath::Vector3 tangent;
			tktkMath::Vector3 binormal;
			tktkMath::Vector3::orthoNormalize(&normal, &tangent, &binormal);

			// 読み込んだ頂点を構造体に詰めて保存する
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

		// インデックス数を読み込む
		int indexNum;
		fread(&indexNum, sizeof(int), 1, fp);

		// 読み込み結果構造体のインデックス情報の配列のメモリを確保する
		result.indexData.reserve(indexNum);

		for (size_t vertIndexIndex = 0; vertIndexIndex < static_cast<size_t>(indexNum); vertIndexIndex++)
		{
			int index{};

			// 小さいサイズの頂点インデックス読み込み用バッファ（4バイトで保存されている場合、この変数は使わない）
			char	sizeOneVertIndex{};
			short	sizeTwoVertIndex{};

			// 頂点インデックスを読み込む
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

			// 読み込んだインデックスを保存する
			result.indexData.push_back(static_cast<unsigned short>(index));
		}

		// テクスチャーの数を読み込む
		int textureNum;
		fread(&textureNum, sizeof(int), 1, fp);

		// 読み込み結果構造体のテクスチャー情報の配列のメモリを確保する
		result.textureFilePaths.reserve(textureNum);

		for (size_t textureIndex = 0; textureIndex < static_cast<size_t>(textureNum); textureIndex++)
		{
			// テクスチャパスを読み込んで保存する
			result.textureFilePaths.push_back(loadString(fp));
		}

		// マテリアル数を読み込む
		int materialNum;
		fread(&materialNum, sizeof(int), 1, fp);

		// 読み込み結果構造体のマテリアル情報の配列のメモリを確保する
		result.materialData.reserve(materialNum);

		for (size_t materialIndex = 0; materialIndex < static_cast<size_t>(materialNum); materialIndex++)
		{
			// 小さいサイズのテクスチャインデックス読み込み用バッファ（4バイトで保存されている場合、この変数は使わない）
			char	sizeOneTextureIndex{};
			short	sizeTwoTextureIndex{};

			// マテリアル名を読み込む
			std::string materialName = loadString(fp);

			// マテリアル名（英語）を読み込む
			std::string engMaterialName = loadString(fp);

			// 拡散反射色を読み込む
			tktkMath::Color diffuse{};
			fread(&diffuse, sizeof(tktkMath::Color), 1, fp);

			// 鏡面反射色を読み込む
			float specular[3]{};
			fread(specular, sizeof(float[3]), 1, fp);

			// 鏡面反射係数を読み込む
			float specularrity{};
			fread(&specularrity, sizeof(float), 1, fp);

			// 環境色を読み込む
			float ambient[3]{};
			fread(ambient, sizeof(float[3]), 1, fp);

			// 描画フラグを読み込む
			char drawFlag{};
			fread(&drawFlag, sizeof(char), 1, fp);

			// エッジカラーを読み込む
			tktkMath::Color edgeColor{};
			fread(&edgeColor, sizeof(tktkMath::Color), 1, fp);

			// エッジサイズを読み込む
			float edgeSize{};
			fread(&edgeSize, sizeof(float), 1, fp);

			// アルベドマップのテクスチャ番号
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

			// スフィアマップのテクスチャ番号
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

			// スフィアモードの種類を読み込む
			char sphereModeType{};
			fread(&sphereModeType, sizeof(char), 1, fp);

			// 共用トゥーンフラグを読み込む
			char toonFlag{};
			fread(&toonFlag, sizeof(char), 1, fp);

			// トゥーンテクスチャインデックスを読み込む
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

			// メモ欄を読み込む
			std::string text = loadString(fp);

			// 対応する頂点数を読み込む
			int indicesNum{};
			fread(&indicesNum, sizeof(int), 1, fp);

			// 読み込んだマテリアルを構造体に詰めて保存する
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

		// ボーン数を読み込む
		int boneNum;
		fread(&boneNum, sizeof(int), 1, fp);

		// 読み込み結果構造体のボーン情報の配列のメモリを確保する
		result.boneData.reserve(boneNum);
		
		for (size_t boneIndex = 0; boneIndex < static_cast<size_t>(boneNum); boneIndex++)
		{
			// 小さいサイズのボーンインデックス読み込み用バッファ（4バイトで保存されている場合、この変数は使わない）
			char	sizeOneBoneIndex{};
			short	sizeTwoBoneIndex{};

			// ボーン名を読み込む
			std::string boneName = loadString(fp);

			// ボーン名（英語）を読み込む
			std::string engBoneName = loadString(fp);

			// 座標を読み込む
			tktkMath::Vector3	pos{ };
			fread(&pos, sizeof(tktkMath::Vector3), 1, fp);

			// 親ボーンインデックスを読み込む
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

			// 変形階層を読み込む
			int transformHierarchy{};
			fread(&transformHierarchy, sizeof(int), 1, fp);

			// ボーンフラグを読み込む
			unsigned short boneFlag{};
			fread(&boneFlag, sizeof(unsigned short), 1, fp);


			// 子ボーン、接続先情報（ボーンフラグによって使用する変数が変わる）
			int nextNo{};
			tktkMath::Vector3	posOfset{};

			// ボーンで指定するフラグが立っていたら
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

			// 付与親ボーン
			int grantParentNo{};

			// 付与率
			float grantRate{};

			// 回転付与、移動付与フラグが立っていたら
			if ((boneFlag & 0x0100) != 0U || (boneFlag & 0x0200) != 0U)
			{
				fread(&grantParentNo, sizeof(int), 1, fp);
				fread(&grantRate, sizeof(float), 1, fp);
			}

			// 軸の方向
			tktkMath::Vector3	axisVec{};

			// 軸固定フラグが立っていたら
			if ((boneFlag & 0x0400) != 0U)
			{
				fread(&axisVec, sizeof(tktkMath::Vector3), 1, fp);
			}

			// それぞれの軸の方向
			tktkMath::Vector3	axisXVec{};
			tktkMath::Vector3	axisZVec{};

			// ローカル軸フラグが立っていたら
			if ((boneFlag & 0x0800) != 0U)
			{
				fread(&axisXVec, sizeof(tktkMath::Vector3), 1, fp);
				fread(&axisZVec, sizeof(tktkMath::Vector3), 1, fp);
			}

			// キー値
			int keyValue{};

			// 外部親変形フラグが立っていたら
			if ((boneFlag & 0x2000) != 0U)
			{
				fread(&keyValue, sizeof(int), 1, fp);
			}

			// IKターゲットボーン
			int ikTargetNo{};

			// Ikループ回数
			int ikLoopCount{};

			// Ik回転角度制限（ラジアン角）
			float ikLimitRotateAngleRad{};

			// Ikリンク回数
			int ikLinkNum{};

			// Ikフラグが立っていたら
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
					// IKリンクボーン
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

					// 回転制限フラグ
					char ikRoateLimitFlag{};
					fread(&ikRoateLimitFlag, sizeof(char), 1, fp);

					// 回転制限
					tktkMath::Vector3	ikRoateLimit{};
					fread(&ikRoateLimit, sizeof(tktkMath::Vector3), 1, fp);
				}
			}

			// 読み込んだボーンを構造体に詰めて保存する
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