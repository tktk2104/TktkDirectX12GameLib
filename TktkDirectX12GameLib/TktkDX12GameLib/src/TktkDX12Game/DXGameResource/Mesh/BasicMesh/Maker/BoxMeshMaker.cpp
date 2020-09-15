#include "TktkDX12Game/DXGameResource/Mesh/BasicMesh/Maker/BoxMeshMaker.h"

#include <vector>
#include <TktkMath/MathHelper.h>
#include <TktkMath/Structs/Vector2.h>
#include <TktkMath/Structs/Vector3.h>
#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/Mesh/BasicMesh/Structs/BasicMonoColorMeshCbuffer.h"

namespace tktk
{
	struct VertexData
	{
		tktkMath::Vector3	point;
		tktkMath::Vector3	normal;
		tktkMath::Vector2	texcoord;
		unsigned char		bones[4]{ 0, 0, 0, 0 };
		float				weight[4]{ 1.0f, 0.0f , 0.0f, 0.0f };
		tktkMath::Vector3	tangent;
		tktkMath::Vector3	binormal;
	};

	void BoxMeshMaker::make()
	{
		std::vector<VertexData> vertices{
			{ { -1.0f, -1.0f, -1.0f }, { -1.0f, -1.0f, -1.0f }, { 0.5f, 0.5f }, { 0, 0, 0, 0 }, { 1.0f, 0.0f , 0.0f, 0.0f }, { 0.0f, -1.0f , 0.0f }, { 1.0f, 0.0f , 0.0f } },
			{ {  1.0f, -1.0f, -1.0f }, {  1.0f, -1.0f, -1.0f }, { 0.5f, 0.5f }, { 0, 0, 0, 0 }, { 1.0f, 0.0f , 0.0f, 0.0f }, { 0.0f, -1.0f , 0.0f }, { 1.0f, 0.0f , 0.0f } },
			{ { -1.0f, -1.0f,  1.0f }, { -1.0f, -1.0f,  1.0f }, { 0.5f, 0.5f }, { 0, 0, 0, 0 }, { 1.0f, 0.0f , 0.0f, 0.0f }, { 0.0f, -1.0f , 0.0f }, { 1.0f, 0.0f , 0.0f } },
			{ {  1.0f, -1.0f,  1.0f }, {  1.0f, -1.0f,  1.0f }, { 0.5f, 0.5f }, { 0, 0, 0, 0 }, { 1.0f, 0.0f , 0.0f, 0.0f }, { 0.0f, -1.0f , 0.0f }, { 1.0f, 0.0f , 0.0f } },

			{ { -1.0f,  1.0f, -1.0f }, { -1.0f,  1.0f, -1.0f }, { 0.5f, 0.5f }, { 0, 0, 0, 0 }, { 1.0f, 0.0f , 0.0f, 0.0f }, { 0.0f, -1.0f , 0.0f }, { 1.0f, 0.0f , 0.0f } },
			{ {  1.0f,  1.0f, -1.0f }, {  1.0f,  1.0f, -1.0f }, { 0.5f, 0.5f }, { 0, 0, 0, 0 }, { 1.0f, 0.0f , 0.0f, 0.0f }, { 0.0f, -1.0f , 0.0f }, { 1.0f, 0.0f , 0.0f } },
			{ { -1.0f,  1.0f,  1.0f }, { -1.0f,  1.0f,  1.0f }, { 0.5f, 0.5f }, { 0, 0, 0, 0 }, { 1.0f, 0.0f , 0.0f, 0.0f }, { 0.0f, -1.0f , 0.0f }, { 1.0f, 0.0f , 0.0f } },
			{ {  1.0f,  1.0f,  1.0f }, {  1.0f,  1.0f,  1.0f }, { 0.5f, 0.5f }, { 0, 0, 0, 0 }, { 1.0f, 0.0f , 0.0f, 0.0f }, { 0.0f, -1.0f , 0.0f }, { 1.0f, 0.0f , 0.0f } }
		};

		for (auto& node : vertices)
		{
			tktkMath::Vector3::orthoNormalize(&node.normal, &node.tangent, &node.binormal);
		}

		// ���_�o�b�t�@�����
		DX12GameManager::setSystemHandle(SystemVertexBufferType::Box, DX12GameManager::createVertexBuffer(vertices));

		std::vector<unsigned short> indices{
			0, 1, 3,
			0, 3, 2,
			0, 5, 1,
			0, 4, 5,
			1, 5, 3,
			3, 5, 7,
			2, 3, 7,
			2, 7, 6,
			0, 2, 6,
			0, 6, 4,
			4, 7, 5,
			4, 6, 7
		};

		// �C���f�b�N�X�o�b�t�@�����
		DX12GameManager::setSystemHandle(SystemIndexBufferType::Box, DX12GameManager::createIndexBuffer(indices));

		// �����̃��b�V���̍쐬�ɕK�v�ȏ��
		BasicMeshInitParam meshInitParam{};
		meshInitParam.useVertexBufferHandle	= DX12GameManager::getSystemHandle(SystemVertexBufferType::Box);
		meshInitParam.useIndexBufferHandle	= DX12GameManager::getSystemHandle(SystemIndexBufferType::Box);

#ifdef _M_AMD64 /* x64�r���h�Ȃ� */
		meshInitParam.indexNum = static_cast<unsigned int>(indices.size());
#else
		meshInitParam.indexNum = indices.size();
#endif // _M_AMD64
		
		meshInitParam.primitiveTopology		= MeshPrimitiveTopology::TriangleList;

		{
			// �}�e���A���̍쐬�ɕK�v�ȏ��
			BasicMeshMaterialInitParam materialParam{};

			// �P�F�̃p�C�v���C���X�e�[�g���g��
			materialParam.usePipeLineStateHandle = DX12GameManager::getSystemHandle(SystemPipeLineStateType::BasicMonoColorMesh);

			materialParam.materialAmbient	= { 0.3f, 1.0f }; // ���}�e���A���̊����̒l�͒萔�l��ݒ肷��
			materialParam.materialDiffuse	= tktkMath::Color_v::white;
			materialParam.materialSpecular	= tktkMath::Color_v::white;
			materialParam.materialEmissive	= tktkMath::Color_v::white;
			materialParam.materialShiniess	= 10.0f;

			// �f�B�X�N���v�^�q�[�v�����
			{
				BasicDescriptorHeapInitParam descriptorHeapInitParam{};
				descriptorHeapInitParam.shaderVisible = true;
				descriptorHeapInitParam.descriptorTableParamArray.resize(3U);

				{ /* �V�F�[�_�[���\�[�X�r���[�̃f�B�X�N���v�^�̏�� */
					auto& srvDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(0U);
					srvDescriptorParam.type = BasicDescriptorType::textureBuffer;

					// �V���h�E�}�b�v�̂P���
					srvDescriptorParam.descriptorParamArray = {
						{ BufferType::depthStencil, DX12GameManager::getSystemHandle(SystemDsBufferType::ShadowMap)	}
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
						{ BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::BasicMeshMaterial)	},
						{ BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::BasicMonoColorMeshCbuffer)	}
					};
				}

				materialParam.useDescriptorHeapHandle = DX12GameManager::createBasicDescriptorHeap(descriptorHeapInitParam);

				// TODO : �uSystemBasicDescriptorHeapType::Box�v���̒l���{���ɕK�v�����ׂ�
				DX12GameManager::setSystemHandle(SystemBasicDescriptorHeapType::Box, materialParam.useDescriptorHeapHandle);
			}

			// �����̃��b�V���̃}�e���A�������
			DX12GameManager::setSystemHandle(SystemBasicMeshMaterialType::Box, DX12GameManager::createBasicMeshMaterial(materialParam));

			// �P�F���C���[�t���[���p�̃p�C�v���C���X�e�[�g���擾����
			materialParam.usePipeLineStateHandle = DX12GameManager::getSystemHandle(SystemPipeLineStateType::BasicMonoColorMeshWireFrame);

			// �����̃��b�V�����C���[�t���[���̃}�e���A�������
			DX12GameManager::setSystemHandle(SystemBasicMeshMaterialType::BoxWireFrame, DX12GameManager::createBasicMeshMaterial(materialParam));
		}

#ifdef _M_AMD64 /* x64�r���h�Ȃ� */

		// �����̃��b�V�������
		meshInitParam.materialSlots = { { DX12GameManager::getSystemHandle(SystemBasicMeshMaterialType::Box), 0, static_cast<unsigned int>(indices.size()) } };
		DX12GameManager::setSystemHandle(SystemBasicMeshType::Box, DX12GameManager::createBasicMesh(meshInitParam));

		// �����̃��b�V�����C���[�t���[�������
		meshInitParam.materialSlots = { { DX12GameManager::getSystemHandle(SystemBasicMeshMaterialType::BoxWireFrame), 0, static_cast<unsigned int>(indices.size()) } };
		DX12GameManager::setSystemHandle(SystemBasicMeshType::BoxWireFrame, DX12GameManager::createBasicMesh(meshInitParam));
#else
		// �����̃��b�V�������
		meshInitParam.materialSlots = { { DX12GameManager::getSystemHandle(SystemBasicMeshMaterialType::Box), 0, indices.size() } };
		DX12GameManager::setSystemHandle(SystemBasicMeshType::Box, DX12GameManager::createBasicMesh(meshInitParam));

		// �����̃��b�V�����C���[�t���[�������
		meshInitParam.materialSlots = { { DX12GameManager::getSystemHandle(SystemBasicMeshMaterialType::BoxWireFrame), 0, indices.size() } };
		DX12GameManager::setSystemHandle(SystemBasicMeshType::BoxWireFrame, DX12GameManager::createBasicMesh(meshInitParam));
#endif // _M_AMD64
	}
}