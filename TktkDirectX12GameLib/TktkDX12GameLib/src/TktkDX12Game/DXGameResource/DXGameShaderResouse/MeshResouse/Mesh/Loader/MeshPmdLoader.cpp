#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Mesh/Loader/MeshPmdLoader.h"

#include <TktkFileIo/lodepmd.h>
#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Mesh/Structs/Subset.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/MeshMaterial/Structs/MeshMaterialCbuffer.h"

namespace tktk
{
	// �X�P���g�������
	inline void craeteSkeleton(int createSkeletonId, const std::vector<tktkFileIo::lodepmd::loadData::OutBone>& boneData);

	// �ǂݍ��݊֐�
	MeshLoadPmdReturnValue MeshPmdLoader::loadPmd(const MeshLoadPmdArgs& args, const MeshDrawFuncRunnerInitParam& funcRunnerInitParam)
	{
		// pmd�t�@�C���̃��[�h�����̏o�͕ϐ�
		tktkFileIo::lodepmd::loadData outData{};

		// ���[�h���s��
		tktkFileIo::lodepmd::load(&outData, args.filePath);

		// ���_�o�b�t�@�����
		size_t createdVertexBufferHandle = DX12GameManager::createVertexBuffer(outData.vertexData);

		// �C���f�b�N�X�o�b�t�@�����
		size_t createdIndexBufferHandle = DX12GameManager::createIndexBuffer(outData.indexData);

		// �ʏ탁�b�V���̍쐬�ɕK�v�ȏ��
		MeshInitParam meshInitParam{};
		meshInitParam.useVertexBufferHandle	= createdVertexBufferHandle;
		meshInitParam.useIndexBufferHandle	= createdIndexBufferHandle;
		meshInitParam.indexNum				= outData.indexData.size();
		meshInitParam.primitiveTopology		= PrimitiveTopology::TriangleList;
		meshInitParam.instanceVertParam		= std::vector<tktkMath::Matrix4>(128U);
		meshInitParam.materialSlots.reserve(outData.materialData.size());

		// ���݂̃C���f�b�N�X�i�C���f�b�N�X�o�b�t�@�̈ʒu�j
		size_t curIndex				= 0U;

		// �}�e���A���̐��������[�v
		for (size_t i = 0; i < outData.materialData.size(); i++)
		{
			// �}�e���A���̍쐬�ɕK�v�ȏ��
			MeshMaterialInitParam materialParam{};

			// �f�t�H���g�̃p�C�v���C���X�e�[�g���g��
			materialParam.usePipeLineStateHandle = DX12GameManager::getSystemHandle(SystemPipeLineStateType::SkinningMesh);

			size_t createdTextureBufferHandle = 0U;

			// �}�e���A���Ƀe�N�X�`�����ݒ肳��Ă�����
			if (outData.materialData.at(i).textureFilePath != "")
			{
				// �e�N�X�`����ǂݍ���
				createdTextureBufferHandle = DX12GameManager::cpuPriorityLoadTextureBuffer(outData.materialData.at(i).textureFilePath);
			}
			// �e�N�X�`�����ݒ肳��Ă��Ȃ�������
			else
			{
				// �ŏ��̑傫���̊����̐F�̃e�N�X�`�����쐬����

				TexBufFormatParam formatParam{};
				formatParam.resourceDimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
				formatParam.format = DXGI_FORMAT_R8G8B8A8_UNORM;
				formatParam.arraySize = 1U;
				formatParam.mipLevels = 1U;
				formatParam.sampleDescCount = 1U;
				formatParam.sampleDescQuality = 0U;

				TexBuffData dataParam{};

				for (size_t j = 0; j < 16; j++)
				{
					dataParam.textureData.push_back(static_cast<unsigned char>(255U * outData.materialData.at(i).ambient.r));
					dataParam.textureData.push_back(static_cast<unsigned char>(255U * outData.materialData.at(i).ambient.g));
					dataParam.textureData.push_back(static_cast<unsigned char>(255U * outData.materialData.at(i).ambient.b));
					dataParam.textureData.push_back(static_cast<unsigned char>(255U * outData.materialData.at(i).ambient.a));
				}

				dataParam.width = 4U;
				dataParam.height = 4U;

				// �e�N�X�`��������������̂ŃR�}���h���X�g
				createdTextureBufferHandle = DX12GameManager::cpuPriorityCreateTextureBuffer(formatParam, dataParam);
			}

			// �f�B�X�N���v�^�q�[�v�����
			{
				BasicDescriptorHeapInitParam descriptorHeapInitParam{};
				descriptorHeapInitParam.shaderVisible = true;
				descriptorHeapInitParam.descriptorTableParamArray.resize(3U);

				{ /* �V�F�[�_�[���\�[�X�r���[�̃f�B�X�N���v�^�̏�� */
					auto& srvDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(0U);
					srvDescriptorParam.type = BasicDescriptorType::textureBuffer;

					// �A���x�h�}�b�v�ƃV���h�E�}�b�v�̂Q���
					srvDescriptorParam.descriptorParamArray = {
						{ BufferType::texture,		createdTextureBufferHandle									},
						{ BufferType::depthStencil, DX12GameManager::getSystemHandle(SystemDsBufferType::ShadowMap)	}
					};
				}

				{ /* ���_�V�F�[�_�[�p�̃R���X�^���g�o�b�t�@�[�r���[�̃f�B�X�N���v�^�̏�� */
					auto& cbufferViewDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(1U);
					cbufferViewDescriptorParam.type = BasicDescriptorType::constantBuffer;

					// �J�����A���C�g�A�V���h�E�}�b�v�A�{�[���s��̂S��
					cbufferViewDescriptorParam.descriptorParamArray = {
						{ BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::Camera)			},
						{ BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::Light)			},
						{ BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::ShadowMap)		},
						{ BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::BoneMatCbuffer)	}
					};
				}

				{ /* �s�N�Z���V�F�[�_�[�p�̃R���X�^���g�o�b�t�@�[�r���[�̃f�B�X�N���v�^�̏�� */
					auto& cbufferViewDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(2U);
					cbufferViewDescriptorParam.type = BasicDescriptorType::constantBuffer;

					// 
					cbufferViewDescriptorParam.descriptorParamArray = {
						{ BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::Light)		},
						{ BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::MeshMaterial)	}
					};
				}
				materialParam.useDescriptorHeapHandle = DX12GameManager::createBasicDescriptorHeap(descriptorHeapInitParam);
			}

			// �ʏ탁�b�V���̃}�e���A�������
			size_t meshMaterialHandle = DX12GameManager::createMeshMaterial(materialParam);

			// ���b�V���}�e���A���萔�o�b�t�@
			auto meshMaterialCbufferPtr = std::make_shared<MeshMaterialCbuffer>();

			// �g���b�V���}�e���A���萔�o�b�t�@�h�̒l������������
			meshMaterialCbufferPtr->materialAmbient		= { 0.3f, 1.0f }; // ���}�e���A���̊����̒l�͒萔�l��ݒ肷��
			meshMaterialCbufferPtr->materialDiffuse		= outData.materialData.at(i).diffuse;
			meshMaterialCbufferPtr->materialSpecular	= outData.materialData.at(i).speqular;
			meshMaterialCbufferPtr->materialEmissive	= outData.materialData.at(i).emissive;
			meshMaterialCbufferPtr->materialShiniess	= outData.materialData.at(i).shiniess;

			// ������g���b�V���}�e���A���萔�o�b�t�@�h���}�e���A���ɒǉ�����
			DX12GameManager::addMeshMaterialAppendParam(
				meshMaterialHandle,
				MeshMaterialAppendParamInitParam(DX12GameManager::getSystemHandle(SystemCBufferType::MeshMaterial), meshMaterialCbufferPtr)
			);

			// �ʏ탁�b�V���̃T�u�Z�b�g�����X�V
			meshInitParam.materialSlots.push_back({ meshMaterialHandle, curIndex, outData.materialData.at(i).indexCount });

			// ���݂̃C���f�b�N�X�����Z
			curIndex += outData.materialData.at(i).indexCount;
		}
		DX12GameManager::createMeshAndAttachId(args.createBasicMeshId, meshInitParam, funcRunnerInitParam);

		// �X�P���g�������
		craeteSkeleton(args.createSkeletonId, outData.boneData);

		// TODO : �쐬�������b�V���̏���Ԃ��\��
		return { };
	}

	// �X�P���g�������
	void craeteSkeleton(int createSkeletonId, const std::vector<tktkFileIo::lodepmd::loadData::OutBone>& boneData)
	{
		// �����̍쐬�ɕK�v�ȏ��
		SkeletonInitParam skeletonInitParam{};
		skeletonInitParam.boneDataArray.reserve(boneData.size());

		for (const auto& node : boneData)
		{
			skeletonInitParam.boneDataArray.push_back({ node.name, node.parentNo, node.pos });
		}

		// �X�P���g�����쐬����
		DX12GameManager::createSkeletonAndAttachId(createSkeletonId, skeletonInitParam);
	}
}