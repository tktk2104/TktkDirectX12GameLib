#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Mesh/Loader/MeshPmxLoader.h"

#include <TktkFileIo/lodepmx.h>
#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Mesh/Structs/Subset.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/MeshMaterial/Structs/MeshMaterialCBufferData.h"

#include "TktkDX12BaseComponents/3D/MeshDrawer/MeshDrawFuncRunnerInitParam.h"

namespace tktk
{
	// �X�P���g�������
	inline size_t craeteSkeleton(int createSkeletonId, const std::vector<tktkFileIo::lodepmx::loadData::OutBone>& boneData);

	MeshLoadPmxReturnValue MeshPmxLoader::loadPmx(const MeshLoadPmxArgs& args, const MeshDrawFuncRunnerInitParam& funcRunnerInitParam)
	{
		// ���[�h���s��
		auto outData = tktkFileIo::lodepmx::load(args.filePath);

		// ���_�o�b�t�@�����
		size_t createdVertexBufferHandle = DX12GameManager::createVertexBuffer(outData.vertexData);

		// �C���f�b�N�X�o�b�t�@�����
		size_t createdIndexBufferHandle = DX12GameManager::createIndexBuffer(outData.indexData);

		// ��U���[�J���ϐ��ɔz����i�[
		auto tempInstanceVertParam = std::vector<tktkMath::Matrix4>(128U);

		// �ʏ탁�b�V���̍쐬�ɕK�v�ȏ��
		MeshInitParam meshInitParam{};
		meshInitParam.useVertexBufferHandle = createdVertexBufferHandle;
		meshInitParam.useIndexBufferHandle	= createdIndexBufferHandle;
		meshInitParam.indexNum				= outData.indexData.size();
		meshInitParam.primitiveTopology		= PrimitiveTopology::TriangleList;
		meshInitParam.instanceVertParam		= tempInstanceVertParam;
		meshInitParam.materialSlots.reserve(outData.materialData.size());

		// �ǂݍ��񂾃e�N�X�`���n���h���̔z��
		std::vector<size_t> loadTextureBufferHandle{};
		loadTextureBufferHandle.reserve(outData.textureFilePaths.size());

		// �ǂݍ��񂾃e�N�X�`���t�@�C���p�X������
		for (const auto& textureFilePath : outData.textureFilePaths)
		{
			loadTextureBufferHandle.push_back(DX12GameManager::cpuPriorityLoadTextureBuffer(textureFilePath));
		}

		// ���݂̃C���f�b�N�X�i�C���f�b�N�X�o�b�t�@�̈ʒu�j
		size_t curIndex = 0U;

		// �}�e���A���̐��������[�v
		for (size_t i = 0; i < outData.materialData.size(); i++)
		{
			// �}�e���A���̍쐬�ɕK�v�ȏ��
			MeshMaterialInitParam materialParam{};

			// �f�t�H���g�̃p�C�v���C���X�e�[�g���g��
			materialParam.usePipeLineStateHandle = DX12GameManager::getSystemHandle(SystemPipeLineStateType::SkinningMesh);

			// �f�B�X�N���v�^�q�[�v�����
			{
				BasicDescriptorHeapInitParam descriptorHeapInitParam{};
				descriptorHeapInitParam.shaderVisible = true;
				descriptorHeapInitParam.descriptorTableParamArray.resize(4U);

				{ /* �V�F�[�_�[���\�[�X�r���[�̃f�B�X�N���v�^�̏�� */
					auto& srvDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(0U);
					srvDescriptorParam.type = BasicDescriptorType::textureBuffer;

					// �A���x�h�}�b�v�ƃV���h�E�}�b�v�ƃm�[�}���}�b�v�̂R���
					srvDescriptorParam.descriptorParamArray = {
						{ BufferType::texture,		loadTextureBufferHandle.at(outData.materialData.at(i).textureId)		},
						{ BufferType::depthStencil, DX12GameManager::getSystemHandle(SystemDsBufferType::ShadowMap)			},
						{ BufferType::texture,		DX12GameManager::getSystemHandle(SystemTextureBufferType::FlatNormal4x4)}
					};
				}

				{ /* ���_�V�F�[�_�[�p�̃R���X�^���g�o�b�t�@�[�r���[�̃f�B�X�N���v�^�̏�� */
					auto& cbufferViewDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(1U);
					cbufferViewDescriptorParam.type = BasicDescriptorType::constantBuffer;

					// �J�����A���C�g�A�V���h�E�}�b�v�A�{�[���s��̂S��
					cbufferViewDescriptorParam.descriptorParamArray = {
						{ BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::Camera)			},
						{ BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::Light)			},
						{ BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::ShadowMap)		}
					};
				}

				{ /* �s�N�Z���V�F�[�_�[�p�̃R���X�^���g�o�b�t�@�[�r���[�̃f�B�X�N���v�^�̏�� */
					auto& cbufferViewDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(2U);
					cbufferViewDescriptorParam.type = BasicDescriptorType::constantBuffer;

					// ���C�g�A���b�V���}�e���A���̂Q��
					cbufferViewDescriptorParam.descriptorParamArray = {
						{ BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::Light)		},
						{ BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::MeshMaterial)	}
					};
				}

				{ /* �V�F�[�_�[���\�[�X�r���[�̃f�B�X�N���v�^�̏�� */
					auto& srvDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(3U);
					srvDescriptorParam.type = BasicDescriptorType::textureBuffer;

					// ���s��e�N�X�`���̂P���
					srvDescriptorParam.descriptorParamArray = {
						{ BufferType::texture,		DX12GameManager::getSystemHandle(SystemTextureBufferType::MeshBoneMatrix) }
					};
				}

				materialParam.useDescriptorHeapHandle = DX12GameManager::createBasicDescriptorHeap(descriptorHeapInitParam);
			}

			// �ʏ탁�b�V���̃}�e���A�������
			size_t meshMaterialHandle = DX12GameManager::createMeshMaterial(materialParam);

			// ���b�V���}�e���A���萔�o�b�t�@
			auto meshMaterialCbufferPtr = std::make_shared<MeshMaterialCBufferData>();

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

		// �X�P���g�������
		size_t skeletonHandle = craeteSkeleton(args.createSkeletonId.value, outData.boneData);

		DX12GameManager::createMeshAndAttachId(args.createBasicMeshId.value, meshInitParam, funcRunnerInitParam);

		// TODO : �쐬�������b�V���̏���Ԃ��\��
		return { skeletonHandle };
	}

	// �X�P���g�������
	size_t craeteSkeleton(int createSkeletonId, const std::vector<tktkFileIo::lodepmx::loadData::OutBone>& boneData)
	{
		// �����̍쐬�ɕK�v�ȏ��
		SkeletonInitParam skeletonInitParam{};
		skeletonInitParam.boneDataArray.reserve(boneData.size());

		for (const auto& node : boneData)
		{
			skeletonInitParam.boneDataArray.push_back({ node.name, node.parentNo, node.pos });
		}

		// �X�P���g�����쐬����
		return DX12GameManager::createSkeletonAndAttachId(createSkeletonId, skeletonInitParam);
	}
}