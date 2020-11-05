#include "TktkDX12Game/DXGameResource/Mesh/BasicMesh/Maker/SphereMeshMaker.h"

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
		unsigned char		bones[4]	{ 0, 0, 0, 0 };
		float				weight[4]	{ 1.0f, 1.0f , 1.0f, 1.0f };
		tktkMath::Vector3	tangent;
		tktkMath::Vector3	binormal;
	};

	void SphereMeshMaker::make()
	{
		size_t uMax = 24;
		size_t vMax = 12;

		std::vector<VertexData> vertices;

		vertices.resize(uMax * (vMax + 1));
		
		for (size_t v = 0U; v <= vMax; v++)
		{
			for (size_t u = 0U; u < uMax; u++)
			{
				VertexData tempVertexData;

				float x = tktkMath::MathHelper::sin(180.0f * v / vMax) * tktkMath::MathHelper::cos(360.0f * u / uMax);
				float y = tktkMath::MathHelper::cos(180.0f * v / vMax);
				float z = tktkMath::MathHelper::sin(180.0f * v / vMax) * tktkMath::MathHelper::sin(360.0f * u / uMax);

				tempVertexData.point = tktkMath::Vector3(x, y, z);
				tempVertexData.normal = tktkMath::Vector3::normalize(tempVertexData.point);

				// TODO : �g�p�\��UV�ɂȂ��Ă��邩�`�F�b�N����
				tempVertexData.texcoord = tktkMath::Vector2(static_cast<float>(u) / uMax, static_cast<float>(v) / vMax);

				tktkMath::Vector3::orthoNormalize(
					&tempVertexData.normal,
					&tempVertexData.tangent,
					&tempVertexData.binormal
				);

				tempVertexData.bones[0] = 0;
				tempVertexData.bones[1] = 0;
				tempVertexData.bones[2] = 0;
				tempVertexData.bones[3] = 0;

				tempVertexData.weight[0] = 1.0f;
				tempVertexData.weight[1] = 0.0f;
				tempVertexData.weight[2] = 0.0f;
				tempVertexData.weight[3] = 0.0f;

				vertices.at(uMax * v + u) = (tempVertexData);
			}
		}

		size_t i = 0U;

		std::vector<unsigned short> indices;
		indices.resize(2 * vMax * (uMax + 1));

		for (size_t v = 0; v < vMax; v++)
		{
			for (size_t u = 0; u <= uMax; u++)
			{
				if (u == uMax)
				{
					indices.at(i) = static_cast<unsigned short>(v * uMax);
					i++;
					indices.at(i) = static_cast<unsigned short>((v + 1) * uMax);
					i++;
				}
				else
				{
					indices.at(i) = static_cast<unsigned short>((v * uMax) + u);
					i++;
					indices.at(i) = static_cast<unsigned short>(indices.at(i - 1U) + uMax);
					i++;
				}
			}
		}

		// ���_�o�b�t�@�����
		DX12GameManager::setSystemHandle(SystemVertexBufferType::Sphere, DX12GameManager::createVertexBuffer(vertices));

		// �C���f�b�N�X�o�b�t�@�����
		DX12GameManager::setSystemHandle(SystemIndexBufferType::Sphere, DX12GameManager::createIndexBuffer(indices));

		// ���̃��b�V���̍쐬�ɕK�v�ȏ��
		BasicMeshInitParam meshInitParam{};
		meshInitParam.useVertexBufferHandle = DX12GameManager::getSystemHandle(SystemVertexBufferType::Sphere);
		meshInitParam.useIndexBufferHandle	= DX12GameManager::getSystemHandle(SystemIndexBufferType::Sphere);
		meshInitParam.indexNum				= indices.size();
		meshInitParam.primitiveTopology		= MeshPrimitiveTopology::TriangleStrip;

		{
			// �}�e���A���̍쐬�ɕK�v�ȏ��
			BasicMeshMaterialInitParam materialParam{};

			// �P�F�̃p�C�v���C���X�e�[�g���g��
			materialParam.usePipeLineStateHandle = DX12GameManager::getSystemHandle(SystemPipeLineStateType::BasicMonoColorMesh);

			materialParam.materialAmbient	= { 0.3f, 1.0f }; // ���}�e���A���̊����̒l�͒萔�l��ݒ肷��
			materialParam.materialDiffuse	= tktkMath::Color_v::white;
			materialParam.materialSpecular	= tktkMath::Color_v::white;
			materialParam.materialEmissive	= { 0.1f, 1.0f };
			materialParam.materialShiniess	= 1.0f;

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

				// TODO : �uSystemBasicDescriptorHeapType::Sphere�v���̒l���{���ɕK�v�����ׂ�
				DX12GameManager::setSystemHandle(SystemBasicDescriptorHeapType::Sphere, materialParam.useDescriptorHeapHandle);
			}

			// ���̃��b�V���̃}�e���A�������
			DX12GameManager::setSystemHandle(SystemBasicMeshMaterialType::Sphere, DX12GameManager::createBasicMeshMaterial(materialParam));

			// �P�F���C���[�t���[���p�̃p�C�v���C���X�e�[�g���擾����
			materialParam.usePipeLineStateHandle = DX12GameManager::getSystemHandle(SystemPipeLineStateType::BasicMonoColorMeshWireFrame);

			// ���̃��b�V�����C���[�t���[���̃}�e���A�������
			DX12GameManager::setSystemHandle(SystemBasicMeshMaterialType::SphereWireFrame, DX12GameManager::createBasicMeshMaterial(materialParam));
		}

		// ���̃��b�V�������
		meshInitParam.materialSlots = { { DX12GameManager::getSystemHandle(SystemBasicMeshMaterialType::Sphere), 0, indices.size() } };
		DX12GameManager::setSystemHandle(SystemBasicMeshType::Sphere, DX12GameManager::createBasicMesh(meshInitParam));

		// ���̃��b�V�����C���[�t���[�������
		meshInitParam.materialSlots = { { DX12GameManager::getSystemHandle(SystemBasicMeshMaterialType::SphereWireFrame), 0, indices.size() } };
		DX12GameManager::setSystemHandle(SystemBasicMeshType::SphereWireFrame, DX12GameManager::createBasicMesh(meshInitParam));
	}
}