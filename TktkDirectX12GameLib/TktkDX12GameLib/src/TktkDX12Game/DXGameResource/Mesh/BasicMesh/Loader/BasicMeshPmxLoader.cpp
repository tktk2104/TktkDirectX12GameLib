#include "TktkDX12Game/DXGameResource/Mesh/BasicMesh/Loader/BasicMeshPmxLoader.h"

#include <TktkFileIo/lodepmx.h>
#include "TktkDX12Game/_MainManager/DX12GameManager.h"

namespace tktk
{
	// �X�P���g�������
	inline void craeteSkeleton(unsigned int createSkeletonId, const std::vector<tktkFileIo::lodepmx::loadData::OutBone>& boneData);

	BasicMeshLoadPmxReturnValue BasicMeshPmxLoader::loadPmx(const BasicMeshLoadPmxArgs& args)
	{
		// ���[�h���s��
		auto outData = tktkFileIo::lodepmx::load(args.filePath);

		// ���_�o�b�t�@�����
		unsigned int createdVertexBufferHandle = DX12GameManager::createVertexBuffer(outData.vertexData);

		// �C���f�b�N�X�o�b�t�@�����
		unsigned int createdIndexBufferHandle = DX12GameManager::createIndexBuffer(outData.indexData);

		// �ʏ탁�b�V���̍쐬�ɕK�v�ȏ��
		BasicMeshInitParam meshInitParam{};
		meshInitParam.useVertexBufferHandle = createdVertexBufferHandle;
		meshInitParam.useIndexBufferHandle = createdIndexBufferHandle;

#ifdef _M_AMD64 /* x64�r���h�Ȃ� */
		meshInitParam.indexNum = static_cast<unsigned int>(outData.indexData.size());
#else
		meshInitParam.indexNum = outData.indexData.size();
#endif // _M_AMD64

		meshInitParam.primitiveTopology = MeshPrimitiveTopology::TriangleList;
		meshInitParam.materialSlots.reserve(outData.materialData.size());

		// �ǂݍ��񂾃e�N�X�`���n���h���̔z��
		std::vector<unsigned int> loadTextureBufferHandle{};
		loadTextureBufferHandle.reserve(outData.textureFilePaths.size());

		// �ǂݍ��񂾃e�N�X�`���t�@�C���p�X������
		for (const auto& textureFilePath : outData.textureFilePaths)
		{
			loadTextureBufferHandle.push_back(DX12GameManager::cpuPriorityLoadTextureBuffer(textureFilePath));
		}

		// ���݂̃C���f�b�N�X�i�C���f�b�N�X�o�b�t�@�̈ʒu�j
		unsigned int curIndex = 0U;

		// �}�e���A���̐��������[�v
		for (unsigned int i = 0; i < outData.materialData.size(); i++)
		{
			// �}�e���A���̍쐬�ɕK�v�ȏ��
			BasicMeshMaterialInitParam materialParam{};

			// �f�t�H���g�̃p�C�v���C���X�e�[�g���g��
			materialParam.usePipeLineStateHandle = DX12GameManager::getSystemHandle(SystemPipeLineStateType::BasicMesh);



			materialParam.materialAmbient = { 0.3f, 1.0f }; // ���}�e���A���̊����̒l�͒萔�l��ݒ肷��
			materialParam.materialDiffuse = outData.materialData.at(i).diffuse;
			materialParam.materialSpecular = outData.materialData.at(i).speqular;
			materialParam.materialEmissive = outData.materialData.at(i).emissive;
			materialParam.materialShiniess = outData.materialData.at(i).shiniess;

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
						{ BufferType::texture,		loadTextureBufferHandle.at(outData.materialData.at(i).textureId)	},
						{ BufferType::depthStencil, DX12GameManager::getSystemHandle(SystemDsBufferType::ShadowMap)		}
					};
				}

				{ /* ���_�V�F�[�_�[�p�̃R���X�^���g�o�b�t�@�[�r���[�̃f�B�X�N���v�^�̏�� */
					auto& cbufferViewDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(1U);
					cbufferViewDescriptorParam.type = BasicDescriptorType::constantBuffer;

					// 
					cbufferViewDescriptorParam.descriptorParamArray = {
						{ BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::MeshTransform)		},
						{ BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::BoneMatCbuffer)		},
						{ BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::Light)				},
						{ BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::BasicMeshMaterial)	},
						{ BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::MeshShadowMap)		}
					};
				}

				{ /* �s�N�Z���V�F�[�_�[�p�̃R���X�^���g�o�b�t�@�[�r���[�̃f�B�X�N���v�^�̏�� */
					auto& cbufferViewDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(2U);
					cbufferViewDescriptorParam.type = BasicDescriptorType::constantBuffer;

					// 
					cbufferViewDescriptorParam.descriptorParamArray = {
						{ BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::Light)		},
						{ BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::BasicMeshMaterial)	}
					};
				}
				materialParam.useDescriptorHeapHandle = DX12GameManager::createBasicDescriptorHeap(descriptorHeapInitParam);
			}

			// �ʏ탁�b�V���̃}�e���A�������
			unsigned int meshMaterialHandle = DX12GameManager::createBasicMeshMaterial(materialParam);

			// �ʏ탁�b�V���̃T�u�Z�b�g�����X�V
			meshInitParam.materialSlots.push_back({ meshMaterialHandle, curIndex, outData.materialData.at(i).indexCount });

			// ���݂̃C���f�b�N�X�����Z
			curIndex += outData.materialData.at(i).indexCount;
		}
		DX12GameManager::createBasicMeshAndAttachId(args.createBasicMeshId, meshInitParam);

		// �X�P���g�������
		craeteSkeleton(args.createSkeletonId, outData.boneData);

		// TODO : �쐬�������b�V���̏���Ԃ��\��
		return { };
	}

	// �X�P���g�������
	void craeteSkeleton(unsigned int createSkeletonId, const std::vector<tktkFileIo::lodepmx::loadData::OutBone>& boneData)
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