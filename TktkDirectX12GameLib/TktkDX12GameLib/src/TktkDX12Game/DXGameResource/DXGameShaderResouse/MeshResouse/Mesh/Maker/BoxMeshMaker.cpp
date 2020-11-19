#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Mesh/Maker/BoxMeshMaker.h"

#include <vector>
#include <TktkMath/MathHelper.h>
#include <TktkMath/Structs/Vector2.h>
#include <TktkMath/Structs/Vector3.h>
#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Mesh/Structs/Subset.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Mesh/Structs/MonoColorInstanceVertData.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/MeshMaterial/Structs/MonoColorMeshCbuffer.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/MeshMaterial/Structs/MeshMaterialCbuffer.h"

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

	BoxMeshMaker::BoxMeshMaker()
	{
		// ���_���
		std::vector<VertexData> vertices{
			/* ��̖� */
			{ { -0.5f,  0.5f, -0.5f }, {  0.0f,  1.0f,  0.0f }, { 0.0f,			0.5f }, { 0, 0, 0, 0 }, { 1.0f, 0.0f , 0.0f, 0.0f }, { 0.0f, -1.0f , 0.0f }, { 1.0f, 0.0f , 0.0f } },
			{ {  0.5f,  0.5f, -0.5f }, {  0.0f,  1.0f,  0.0f }, { 1.0f / 3.0f,	0.5f }, { 0, 0, 0, 0 }, { 1.0f, 0.0f , 0.0f, 0.0f }, { 0.0f, -1.0f , 0.0f }, { 1.0f, 0.0f , 0.0f } },
			{ {  0.5f,  0.5f,  0.5f }, {  0.0f,  1.0f,  0.0f }, { 1.0f / 3.0f,	0.0f }, { 0, 0, 0, 0 }, { 1.0f, 0.0f , 0.0f, 0.0f }, { 0.0f, -1.0f , 0.0f }, { 1.0f, 0.0f , 0.0f } },
			{ { -0.5f,  0.5f,  0.5f }, {  0.0f,  1.0f,  0.0f }, { 0.0f,			0.0f }, { 0, 0, 0, 0 }, { 1.0f, 0.0f , 0.0f, 0.0f }, { 0.0f, -1.0f , 0.0f }, { 1.0f, 0.0f , 0.0f } },

			/* ���̖� */
			{ { -0.5f, -0.5f, -0.5f }, {  0.0f, -1.0f,  0.0f }, { 1.0f,			1.0f }, { 0, 0, 0, 0 }, { 1.0f, 0.0f , 0.0f, 0.0f }, { 0.0f, -1.0f , 0.0f }, { 1.0f, 0.0f , 0.0f } },
			{ {  0.5f, -0.5f, -0.5f }, {  0.0f, -1.0f,  0.0f }, { 2.0f / 3.0f,	1.0f }, { 0, 0, 0, 0 }, { 1.0f, 0.0f , 0.0f, 0.0f }, { 0.0f, -1.0f , 0.0f }, { 1.0f, 0.0f , 0.0f } },
			{ {  0.5f, -0.5f,  0.5f }, {  0.0f, -1.0f,  0.0f }, { 2.0f / 3.0f,	0.5f }, { 0, 0, 0, 0 }, { 1.0f, 0.0f , 0.0f, 0.0f }, { 0.0f, -1.0f , 0.0f }, { 1.0f, 0.0f , 0.0f } },
			{ { -0.5f, -0.5f,  0.5f }, {  0.0f, -1.0f,  0.0f }, { 1.0f,			0.5f }, { 0, 0, 0, 0 }, { 1.0f, 0.0f , 0.0f, 0.0f }, { 0.0f, -1.0f , 0.0f }, { 1.0f, 0.0f , 0.0f } },
	
			/* ���̖� */
			{ { -0.5f, -0.5f,  0.5f }, { -1.0f,  0.0f,  0.0f }, { 2.0f / 3.0f,	0.5f }, { 0, 0, 0, 0 }, { 1.0f, 0.0f , 0.0f, 0.0f }, { 0.0f, -1.0f , 0.0f }, { 1.0f, 0.0f , 0.0f } },
			{ { -0.5f, -0.5f, -0.5f }, { -1.0f,  0.0f,  0.0f }, { 1.0f,			0.5f }, { 0, 0, 0, 0 }, { 1.0f, 0.0f , 0.0f, 0.0f }, { 0.0f, -1.0f , 0.0f }, { 1.0f, 0.0f , 0.0f } },
			{ { -0.5f,  0.5f, -0.5f }, { -1.0f,  0.0f,  0.0f }, { 1.0f,			0.0f }, { 0, 0, 0, 0 }, { 1.0f, 0.0f , 0.0f, 0.0f }, { 0.0f, -1.0f , 0.0f }, { 1.0f, 0.0f , 0.0f } },
			{ { -0.5f,  0.5f,  0.5f }, { -1.0f,  0.0f,  0.0f }, { 2.0f / 3.0f,	0.0f }, { 0, 0, 0, 0 }, { 1.0f, 0.0f , 0.0f, 0.0f }, { 0.0f, -1.0f , 0.0f }, { 1.0f, 0.0f , 0.0f } },

			/* �E�̖� */
			{ {  0.5f, -0.5f,  0.5f }, {  1.0f,  0.0f,  0.0f }, { 1.0f / 3.0f,	1.0f }, { 0, 0, 0, 0 }, { 1.0f, 0.0f , 0.0f, 0.0f }, { 0.0f, -1.0f , 0.0f }, { 1.0f, 0.0f , 0.0f } },
			{ {  0.5f, -0.5f, -0.5f }, {  1.0f,  0.0f,  0.0f }, { 0.0f,			1.0f }, { 0, 0, 0, 0 }, { 1.0f, 0.0f , 0.0f, 0.0f }, { 0.0f, -1.0f , 0.0f }, { 1.0f, 0.0f , 0.0f } },
			{ {  0.5f,  0.5f, -0.5f }, {  1.0f,  0.0f,  0.0f }, { 0.0f,			0.5f }, { 0, 0, 0, 0 }, { 1.0f, 0.0f , 0.0f, 0.0f }, { 0.0f, -1.0f , 0.0f }, { 1.0f, 0.0f , 0.0f } },
			{ {  0.5f,  0.5f,  0.5f }, {  1.0f,  0.0f,  0.0f }, { 1.0f / 3.0f,	0.5f }, { 0, 0, 0, 0 }, { 1.0f, 0.0f , 0.0f, 0.0f }, { 0.0f, -1.0f , 0.0f }, { 1.0f, 0.0f , 0.0f } },

			/* ��O�̖�*/
			{ { -0.5f, -0.5f, -0.5f }, {  0.0f,  0.0f, -1.0f }, { 1.0f / 3.0f,	0.5f }, { 0, 0, 0, 0 }, { 1.0f, 0.0f , 0.0f, 0.0f }, { 0.0f, -1.0f , 0.0f }, { 1.0f, 0.0f , 0.0f } },
			{ {  0.5f, -0.5f, -0.5f }, {  0.0f,  0.0f, -1.0f }, { 2.0f / 3.0f,	0.5f }, { 0, 0, 0, 0 }, { 1.0f, 0.0f , 0.0f, 0.0f }, { 0.0f, -1.0f , 0.0f }, { 1.0f, 0.0f , 0.0f } },
			{ {  0.5f,  0.5f, -0.5f }, {  0.0f,  0.0f, -1.0f }, { 2.0f / 3.0f,	0.0f }, { 0, 0, 0, 0 }, { 1.0f, 0.0f , 0.0f, 0.0f }, { 0.0f, -1.0f , 0.0f }, { 1.0f, 0.0f , 0.0f } },
			{ { -0.5f,  0.5f, -0.5f }, {  0.0f,  0.0f, -1.0f }, { 1.0f / 3.0f,	0.0f }, { 0, 0, 0, 0 }, { 1.0f, 0.0f , 0.0f, 0.0f }, { 0.0f, -1.0f , 0.0f }, { 1.0f, 0.0f , 0.0f } },

			/* ���̖� */
			{ { -0.5f, -0.5f,  0.5f }, {  0.0f,  0.0f,  1.0f }, { 2.0f / 3.0f,	1.0f }, { 0, 0, 0, 0 }, { 1.0f, 0.0f , 0.0f, 0.0f }, { 0.0f, -1.0f , 0.0f }, { 1.0f, 0.0f , 0.0f } },
			{ {  0.5f, -0.5f,  0.5f }, {  0.0f,  0.0f,  1.0f }, { 1.0f / 3.0f,	1.0f }, { 0, 0, 0, 0 }, { 1.0f, 0.0f , 0.0f, 0.0f }, { 0.0f, -1.0f , 0.0f }, { 1.0f, 0.0f , 0.0f } },
			{ {  0.5f,  0.5f,  0.5f }, {  0.0f,  0.0f,  1.0f }, { 1.0f / 3.0f,	0.5f }, { 0, 0, 0, 0 }, { 1.0f, 0.0f , 0.0f, 0.0f }, { 0.0f, -1.0f , 0.0f }, { 1.0f, 0.0f , 0.0f } },
			{ { -0.5f,  0.5f,  0.5f }, {  0.0f,  0.0f,  1.0f }, { 2.0f / 3.0f,	0.5f }, { 0, 0, 0, 0 }, { 1.0f, 0.0f , 0.0f, 0.0f }, { 0.0f, -1.0f , 0.0f }, { 1.0f, 0.0f , 0.0f } }
		};

		for (auto& node : vertices) tktkMath::Vector3::orthoNormalize(&node.normal, &node.tangent, &node.binormal);

		// ���_�o�b�t�@�����
		DX12GameManager::setSystemHandle(SystemVertexBufferType::Box, DX12GameManager::createVertexBuffer(vertices));

		// �C���f�b�N�X���
		std::vector<unsigned short> indices{
			3,1,0,
			2,1,3,

			6,4,5,
			7,4,6,

			11,9,8,
			10,9,11,

			14,12,13,
			15,12,14,

			19,17,16,
			18,17,19,

			22,20,21,
			23,20,22
		};

		// �C���f�b�N�X�o�b�t�@�����
		DX12GameManager::setSystemHandle(SystemIndexBufferType::Box, DX12GameManager::createIndexBuffer(indices));
	}

	// �f�X�g���N�^���C�����C��������
	BoxMeshMaker::~BoxMeshMaker() = default;

	size_t BoxMeshMaker::makeBoxMeshWireFrame(const MeshDrawFuncRunnerInitParam& funcRunnerInitParam)
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

			// ������f�B�X�N���v�^�q�[�v�̃n���h�����}�e���A���쐬�����ɑ������
			materialParam.useDescriptorHeapHandle = DX12GameManager::createBasicDescriptorHeap(descriptorHeapInitParam);
		}
		// �P�F�̃V���v�������̃��b�V�����C���[�t���[���̃}�e���A�������
		size_t boxMeshMaterialhandle = DX12GameManager::createMeshMaterial(materialParam);

		// �V�X�e���n���h���ƌ��т���
		DX12GameManager::setSystemHandle(SystemMeshMaterialType::BoxWireFrame, boxMeshMaterialhandle);

		// ��U���[�J���ϐ��ɔz����i�[
		auto tempInstanceVertParam = std::vector<MonoColorInstanceVertData>(128U);

		// �P�F�̃V���v�������̃��b�V�����C���[�t���[���̍쐬�ɕK�v�ȏ��
		MeshInitParam meshInitParam{};
		meshInitParam.useVertexBufferHandle	= DX12GameManager::getSystemHandle(SystemVertexBufferType::Box);
		meshInitParam.useIndexBufferHandle	= DX12GameManager::getSystemHandle(SystemIndexBufferType::Box);
		meshInitParam.indexNum				= IndicesSize;
		meshInitParam.primitiveTopology		= PrimitiveTopology::TriangleList;
		meshInitParam.instanceVertParam		= tempInstanceVertParam;
		meshInitParam.materialSlots =		{ { boxMeshMaterialhandle, 0, IndicesSize } };

		// �P�F�̃V���v�������̃��b�V�����C���[�t���[�������A���̃n���h����Ԃ�
		return DX12GameManager::createMesh(meshInitParam, funcRunnerInitParam);
	}

	size_t BoxMeshMaker::makeMonoColorBoxMesh(const MeshDrawFuncRunnerInitParam& funcRunnerInitParam)
	{
		// �}�e���A���̍쐬�ɕK�v�ȏ��
		MeshMaterialInitParam materialParam{};

		// �P�F�̃V���v�����b�V���p�C�v���C���X�e�[�g���g��
		materialParam.usePipeLineStateHandle = DX12GameManager::getSystemHandle(SystemPipeLineStateType::MonoColorSimpleMesh);

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

			// ������f�B�X�N���v�^�q�[�v�̃n���h�����}�e���A���쐬�����ɑ������
			materialParam.useDescriptorHeapHandle = DX12GameManager::createBasicDescriptorHeap(descriptorHeapInitParam);
		}
		// �P�F�̃V���v�������̃��b�V���̃}�e���A�������
		size_t boxMeshMaterialhandle = DX12GameManager::createMeshMaterial(materialParam);

		// �V�X�e���n���h���ƌ��т���
		DX12GameManager::setSystemHandle(SystemMeshMaterialType::Box, boxMeshMaterialhandle);

		// ��U���[�J���ϐ��ɔz����i�[
		auto tempInstanceVertParam = std::vector<MonoColorInstanceVertData>(128U);

		// �����̃��b�V���̍쐬�ɕK�v�ȏ��
		MeshInitParam meshInitParam{};
		meshInitParam.useVertexBufferHandle = DX12GameManager::getSystemHandle(SystemVertexBufferType::Box);
		meshInitParam.useIndexBufferHandle	= DX12GameManager::getSystemHandle(SystemIndexBufferType::Box);
		meshInitParam.indexNum				= IndicesSize;
		meshInitParam.primitiveTopology		= PrimitiveTopology::TriangleList;
		meshInitParam.instanceVertParam		= tempInstanceVertParam;
		meshInitParam.materialSlots			= { { boxMeshMaterialhandle, 0, IndicesSize } };

		// �P�F�̃V���v�������̃��b�V�������A���̃n���h����Ԃ�
		return DX12GameManager::createMesh(meshInitParam, funcRunnerInitParam);
	}

	size_t BoxMeshMaker::makeBoxMesh(size_t albedoMapTextureHandle, const MeshDrawFuncRunnerInitParam& funcRunnerInitParam)
	{
		// �}�e���A���̍쐬�ɕK�v�ȏ��
		MeshMaterialInitParam materialParam{};

		// �V���v�����b�V���p�C�v���C���X�e�[�g���g��
		materialParam.usePipeLineStateHandle = DX12GameManager::getSystemHandle(SystemPipeLineStateType::SimpleMesh);

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
					{ BufferType::texture, albedoMapTextureHandle },
					{ BufferType::depthStencil, DX12GameManager::getSystemHandle(SystemDsBufferType::ShadowMap)	}
				};
			}

			{ /* ���_�V�F�[�_�[�p�̃R���X�^���g�o�b�t�@�[�r���[�̃f�B�X�N���v�^�̏�� */
				auto& cbufferViewDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(1U);
				cbufferViewDescriptorParam.type = BasicDescriptorType::constantBuffer;

				// �J�����A���C�g�A�V���h�E�}�b�v�̂R���
				cbufferViewDescriptorParam.descriptorParamArray = {
					{ BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::Camera)		},
					{ BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::Light)		},
					{ BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::ShadowMap)	}
				};
			}

			{ /* �s�N�Z���V�F�[�_�[�p�̃R���X�^���g�o�b�t�@�[�r���[�̃f�B�X�N���v�^�̏�� */
				auto& cbufferViewDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(2U);
				cbufferViewDescriptorParam.type = BasicDescriptorType::constantBuffer;

				// ���C�g�A���b�V���}�e���A���̂Q���
				cbufferViewDescriptorParam.descriptorParamArray = {
					{ BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::Light)			},
					{ BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::MeshMaterial)	}
				};
			}

			// ������f�B�X�N���v�^�q�[�v�̃n���h�����}�e���A���쐬�����ɑ������
			materialParam.useDescriptorHeapHandle = DX12GameManager::createBasicDescriptorHeap(descriptorHeapInitParam);
		}
		// �V���v�������̃��b�V���̃}�e���A�������
		size_t boxMeshMaterialhandle = DX12GameManager::createMeshMaterial(materialParam);

		// ���b�V���}�e���A���萔�o�b�t�@
		auto boxMeshMaterialCbufferPtr = std::make_shared<MeshMaterialCbuffer>();

		// �g���b�V���}�e���A���萔�o�b�t�@�h�̒l������������
		boxMeshMaterialCbufferPtr->materialAmbient	= { 0.3f, 1.0f };
		boxMeshMaterialCbufferPtr->materialDiffuse	= tktkMath::Color_v::white;
		boxMeshMaterialCbufferPtr->materialSpecular = tktkMath::Color_v::white;
		boxMeshMaterialCbufferPtr->materialEmissive = { 0.1f, 1.0f };
		boxMeshMaterialCbufferPtr->materialShiniess = 1.0f;

		// ������g���b�V���}�e���A���萔�o�b�t�@�h���}�e���A���ɒǉ�����
		DX12GameManager::addMeshMaterialAppendParam(
			boxMeshMaterialhandle,
			MeshMaterialAppendParamInitParam(DX12GameManager::getSystemHandle(SystemCBufferType::MeshMaterial), boxMeshMaterialCbufferPtr)
		);

		// ��U���[�J���ϐ��ɔz����i�[
		auto tempInstanceVertParam = std::vector<tktkMath::Matrix4>(2048U);

		// �����̃��b�V���̍쐬�ɕK�v�ȏ��
		MeshInitParam meshInitParam{};
		meshInitParam.useVertexBufferHandle	= DX12GameManager::getSystemHandle(SystemVertexBufferType::Box);
		meshInitParam.useIndexBufferHandle	= DX12GameManager::getSystemHandle(SystemIndexBufferType::Box);
		meshInitParam.indexNum				= IndicesSize;
		meshInitParam.primitiveTopology		= PrimitiveTopology::TriangleList;
		meshInitParam.instanceVertParam		= tempInstanceVertParam;
		meshInitParam.materialSlots			= { { boxMeshMaterialhandle, 0, IndicesSize } };

		// �V���v�������̃��b�V�������A���̃n���h����Ԃ�
		return DX12GameManager::createMesh(meshInitParam, funcRunnerInitParam);
	}

	size_t BoxMeshMaker::makeSkyBoxMesh(size_t skyBoxTextureHandle, const MeshDrawFuncRunnerInitParam& funcRunnerInitParam)
	{
		// �}�e���A���̍쐬�ɕK�v�ȏ��
		MeshMaterialInitParam materialParam{};

		// ���]�����V���v�����b�V���p�C�v���C���X�e�[�g���g��
		materialParam.usePipeLineStateHandle = DX12GameManager::getSystemHandle(SystemPipeLineStateType::InvertSimpleMesh);

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
					{ BufferType::texture, skyBoxTextureHandle },
					{ BufferType::texture, DX12GameManager::getSystemHandle(SystemTextureBufferType::White)	}
				};
			}

			{ /* ���_�V�F�[�_�[�p�̃R���X�^���g�o�b�t�@�[�r���[�̃f�B�X�N���v�^�̏�� */
				auto& cbufferViewDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(1U);
				cbufferViewDescriptorParam.type = BasicDescriptorType::constantBuffer;

				// �J�����A���C�g�A�V���h�E�}�b�v�̂R���
				cbufferViewDescriptorParam.descriptorParamArray = {
					{ BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::Camera)		},
					{ BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::Light)		},
					{ BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::ShadowMap)	}
				};
			}

			{ /* �s�N�Z���V�F�[�_�[�p�̃R���X�^���g�o�b�t�@�[�r���[�̃f�B�X�N���v�^�̏�� */
				auto& cbufferViewDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(2U);
				cbufferViewDescriptorParam.type = BasicDescriptorType::constantBuffer;

				// ���C�g�A���b�V���}�e���A���̂Q���
				cbufferViewDescriptorParam.descriptorParamArray = {
					{ BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::Light)			},
					{ BufferType::constant,		DX12GameManager::getSystemHandle(SystemCBufferType::MeshMaterial)	}
				};
			}

			// ������f�B�X�N���v�^�q�[�v�̃n���h�����}�e���A���쐬�����ɑ������
			materialParam.useDescriptorHeapHandle = DX12GameManager::createBasicDescriptorHeap(descriptorHeapInitParam);
		}
		// ���]�����V���v�������̃��b�V���̃}�e���A�������
		size_t boxMeshMaterialhandle = DX12GameManager::createMeshMaterial(materialParam);

		// ���b�V���}�e���A���萔�o�b�t�@
		auto boxMeshMaterialCbufferPtr = std::make_shared<MeshMaterialCbuffer>();

		// �g���b�V���}�e���A���萔�o�b�t�@�h�̒l������������
		boxMeshMaterialCbufferPtr->materialAmbient	= tktkMath::Color_v::white;
		boxMeshMaterialCbufferPtr->materialDiffuse	= tktkMath::Color_v::white;
		boxMeshMaterialCbufferPtr->materialSpecular = tktkMath::Color_v::white;
		boxMeshMaterialCbufferPtr->materialEmissive = tktkMath::Color_v::white;
		boxMeshMaterialCbufferPtr->materialShiniess = 1.0f;

		// ������g���b�V���}�e���A���萔�o�b�t�@�h���}�e���A���ɒǉ�����
		DX12GameManager::addMeshMaterialAppendParam(
			boxMeshMaterialhandle,
			MeshMaterialAppendParamInitParam(DX12GameManager::getSystemHandle(SystemCBufferType::MeshMaterial), boxMeshMaterialCbufferPtr)
		);

		// ��U���[�J���ϐ��ɔz����i�[
		auto tempInstanceVertParam = std::vector<tktkMath::Matrix4>(128U);

		// �����̃��b�V���̍쐬�ɕK�v�ȏ��
		MeshInitParam meshInitParam{};
		meshInitParam.useVertexBufferHandle	= DX12GameManager::getSystemHandle(SystemVertexBufferType::Box);
		meshInitParam.useIndexBufferHandle	= DX12GameManager::getSystemHandle(SystemIndexBufferType::Box);
		meshInitParam.indexNum				= IndicesSize;
		meshInitParam.primitiveTopology		= PrimitiveTopology::TriangleList;
		meshInitParam.instanceVertParam		= tempInstanceVertParam;
		meshInitParam.materialSlots			= { { boxMeshMaterialhandle, 0, IndicesSize } };

		// ���]�����V���v�������̃��b�V�������A���̃n���h����Ԃ�
		return DX12GameManager::createMesh(meshInitParam, funcRunnerInitParam);
	}
}