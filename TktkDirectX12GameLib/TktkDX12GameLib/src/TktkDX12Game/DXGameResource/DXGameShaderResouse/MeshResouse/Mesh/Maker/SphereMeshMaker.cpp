#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Mesh/Maker/SphereMeshMaker.h"

#include <vector>
#include <TktkMath/MathHelper.h>
#include <TktkMath/Structs/Vector2.h>
#include <TktkMath/Structs/Vector3.h>
#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Mesh/Structs/Subset.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Mesh/Structs/MonoColorInstanceVertData.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/MeshMaterial/Structs/MonoColorMeshCBufferData.h"

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

	SphereMeshMaker::SphereMeshMaker()
	{
		size_t uMax = 24;
		size_t vMax = 12;

		// ���_���
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

				tempVertexData.point = tktkMath::Vector3(x, y, z) / 2.0f;
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

		// �C���f�b�N�X���
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
	}

	// �f�X�g���N�^���C�����C��������
	SphereMeshMaker::~SphereMeshMaker() = default;

	size_t SphereMeshMaker::makeSphereMeshWireFrame(const MeshDrawFuncRunnerInitParam& funcRunnerInitParam)
	{
		// �}�e���A���̍쐬�ɕK�v�ȏ��
		MeshMaterialInitParam materialParam{};

		// �P�F�V���v�����b�V�����C���[�t���[���p�C�v���C���X�e�[�g���擾����
		materialParam.usePipeLineStateHandle = DX12GameManager::getSystemHandle(SystemPipeLineStateType::MonoColorSimpleMeshWireFrame);

		// �f�B�X�N���v�^�q�[�v�����
		{
			BasicDescriptorHeapInitParam descriptorHeapInitParam{};
			descriptorHeapInitParam.shaderVisible = true;
			descriptorHeapInitParam.descriptorTableParamArray.resize(1U);

			{ /* ���_�V�F�[�_�[�p�̃R���X�^���g�o�b�t�@�[�r���[�̃f�B�X�N���v�^�̏�� */
				auto& cbufferViewDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(0U);
				cbufferViewDescriptorParam.type = BasicDescriptorType::constantBuffer;

				// �J�����̂P���
				cbufferViewDescriptorParam.descriptorParamArray = {
					{ BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::Camera)		}
				};
			}
			materialParam.useDescriptorHeapHandle = DX12GameManager::createBasicDescriptorHeap(descriptorHeapInitParam);
		}

		// �P�F�̃V���v�����̃��b�V�����C���[�t���[���̃}�e���A�������
		size_t sphereMeshMaterialhandle = DX12GameManager::createMeshMaterial(materialParam);

		// �V�X�e���n���h���ƌ��т���
		DX12GameManager::setSystemHandle(SystemMeshMaterialType::SphereWireFrame, sphereMeshMaterialhandle);

		// ��U���[�J���ϐ��ɔz����i�[
		auto tempInstanceVertParam = std::vector<MonoColorInstanceVertData>(128U);

		// ���̃��b�V���̍쐬�ɕK�v�ȏ��
		MeshInitParam meshInitParam{};
		meshInitParam.useVertexBufferHandle	= DX12GameManager::getSystemHandle(SystemVertexBufferType::Sphere);
		meshInitParam.useIndexBufferHandle	= DX12GameManager::getSystemHandle(SystemIndexBufferType::Sphere);
		meshInitParam.indexNum				= IndicesSize;
		meshInitParam.primitiveTopology		= PrimitiveTopology::TriangleStrip;
		meshInitParam.instanceVertParam		= tempInstanceVertParam;
		meshInitParam.materialSlots			= { { sphereMeshMaterialhandle, 0, IndicesSize } };

		// �P�F�̃V���v�����̃��b�V�����C���[�t���[�������A���̃n���h����Ԃ�
		return DX12GameManager::createMesh(meshInitParam, funcRunnerInitParam);
	}

	size_t SphereMeshMaker::makeMonoColorSphereMesh(const MeshDrawFuncRunnerInitParam& funcRunnerInitParam)
	{
		// �}�e���A���̍쐬�ɕK�v�ȏ��
		MeshMaterialInitParam materialParam{};

		// �P�F�̃p�C�v���C���X�e�[�g���g��
		materialParam.usePipeLineStateHandle = DX12GameManager::getSystemHandle(SystemPipeLineStateType::MonoColorSkinningMesh);

		// �f�B�X�N���v�^�q�[�v�����
		{
			BasicDescriptorHeapInitParam descriptorHeapInitParam{};
			descriptorHeapInitParam.shaderVisible = true;
			descriptorHeapInitParam.descriptorTableParamArray.resize(1U);

			{ /* ���_�V�F�[�_�[�p�̃R���X�^���g�o�b�t�@�[�r���[�̃f�B�X�N���v�^�̏�� */
				auto& cbufferViewDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(0U);
				cbufferViewDescriptorParam.type = BasicDescriptorType::constantBuffer;

				// �J�����̂P���
				cbufferViewDescriptorParam.descriptorParamArray = {
					{ BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::Camera)		}
				};
			}

			materialParam.useDescriptorHeapHandle = DX12GameManager::createBasicDescriptorHeap(descriptorHeapInitParam);
		}

		// �P�F�̃V���v�����̃��b�V���̃}�e���A�������
		size_t sphereMeshMaterialhandle = DX12GameManager::createMeshMaterial(materialParam);

		// �V�X�e���n���h���ƌ��т���
		DX12GameManager::setSystemHandle(SystemMeshMaterialType::Sphere, sphereMeshMaterialhandle);

		// ��U���[�J���ϐ��ɔz����i�[
		auto tempInstanceVertParam = std::vector<MonoColorInstanceVertData>(128U);

		// ���̃��b�V���̍쐬�ɕK�v�ȏ��
		MeshInitParam meshInitParam{};
		meshInitParam.useVertexBufferHandle = DX12GameManager::getSystemHandle(SystemVertexBufferType::Sphere);
		meshInitParam.useIndexBufferHandle	= DX12GameManager::getSystemHandle(SystemIndexBufferType::Sphere);
		meshInitParam.indexNum				= IndicesSize;
		meshInitParam.primitiveTopology		= PrimitiveTopology::TriangleStrip;
		meshInitParam.instanceVertParam		= tempInstanceVertParam;
		meshInitParam.materialSlots			= { { sphereMeshMaterialhandle, 0, IndicesSize } };

		// �P�F�̃V���v�����̃��b�V�������A���̃n���h����Ԃ�
		return DX12GameManager::createMesh(meshInitParam, funcRunnerInitParam);
	}
}