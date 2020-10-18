#include "LoadingScene.h"

#include <TktkDX12Game/_MainManager/DX12GameManager.h>
#include "../GameObject/Cursor/CursorScript.h"
#include "../Enum/_ResourceIds/ResourceIds.h"
#include "../TutorialCode/GameObject/ElementShape/VertexColor2DPolygonConstantBufferData.h"

#include "../ResourceHandleCarrier/ResourceHandleCarrier.h"

void LoadingScene::start()
{
	// �e�N�X�`����ǂݍ��݁A�X�v���C�g�̃}�e���A�������
	{
		unsigned int spriteTextureHandle = tktk::DX12GameManager::cpuPriorityLoadTextureBuffer("res/test.png");
		//tktk::DX12GameManager::executeCommandList();

		tktk::SpriteMaterialInitParam initParam{};
		/*initParam.srvBufferType				= tktk::BufferType::texture;
		initParam.useBufferHandle			= spriteTextureHandle;*/
		initParam.srvBufferType				= tktk::BufferType::depthStencil;
		initParam.useBufferHandle			= tktk::DX12GameManager::getSystemHandle(tktk::SystemDsBufferType::ShadowMap);

		tktk::DX12GameManager::createSpriteMaterialAndAttachId(SpriteMaterialId::Test, initParam);

		tktk::BillboardMaterialInitParam billInitParam{};
		billInitParam.srvBufferType			= tktk::BufferType::texture;
		billInitParam.useBufferHandle = spriteTextureHandle;

		tktk::DX12GameManager::createBillboardMaterialAndAttachId(BillboardId::test, billInitParam);
	}

	// ���b�V�������[�h����
	{
		tktk::BasicMeshLoadPmdArgs loadArgs{};
		loadArgs.filePath = "res/Model/�����~�N.pmd";
		loadArgs.createBasicMeshId					= static_cast<int>(BasicMeshId::Miku);
		loadArgs.createSkeletonId					= static_cast<int>(SkeletonId::Miku);

		tktk::DX12GameManager::loadPmd(loadArgs);
	}

	// ���[�V���������[�h����
	{
		tktk::DX12GameManager::loadMotionAndAttachId(MotionId::motion1, "res/Motion/pose.vmd");
		tktk::DX12GameManager::loadMotionAndAttachId(MotionId::motion2, "res/Motion/motion.vmd");
	}

	// �|�X�g�G�t�F�N�g�ɕK�v�ȃ��\�[�X�����
	{
		// �����_�[�^�[�Q�b�g�����
		unsigned int postEffectRtBufferHandle = tktk::DX12GameManager::createRtBuffer(tktk::DX12GameManager::getWindowSize(), tktkMath::Color_v::red);

		// �����_�[�^�[�Q�b�g�r���[�����
		tktk::RtvDescriptorHeapInitParam rtvDescriptorHeapInitParam{};
		rtvDescriptorHeapInitParam.shaderVisible = false;
		rtvDescriptorHeapInitParam.descriptorParamArray.resize(1U);
		rtvDescriptorHeapInitParam.descriptorParamArray.at(0U).type		= tktk::RtvDescriptorType::normal;
		rtvDescriptorHeapInitParam.descriptorParamArray.at(0U).handle	= postEffectRtBufferHandle;
		unsigned int postEffectRtvDescriptorHeapHandle = tktk::DX12GameManager::createRtvDescriptorHeap(rtvDescriptorHeapInitParam);

		ResourceHandleCarrier::setPostEffectRtvDescriptorHeapHandle(postEffectRtvDescriptorHeapHandle);

		// �f�B�X�N���v�^�q�[�v�����
		tktk::BasicDescriptorHeapInitParam basicDescriptorHeapInitParam{};
		basicDescriptorHeapInitParam.shaderVisible = true;
		basicDescriptorHeapInitParam.descriptorTableParamArray.resize(1U);
		{ /* �V�F�[�_�[���\�[�X�r���[�̃f�B�X�N���v�^�̏�� */
			auto& srvDescriptorParam = basicDescriptorHeapInitParam.descriptorTableParamArray.at(0U);
			srvDescriptorParam.type = tktk::BasicDescriptorType::textureBuffer;

			// �����_�[�^�[�Q�b�g�e�N�X�`���̂P���
			srvDescriptorParam.descriptorParamArray = {
				{ tktk::BufferType::renderTarget,		postEffectRtBufferHandle }
			};
		}
		unsigned int postEffectBasicDescriptorHeapHandle = tktk::DX12GameManager::createBasicDescriptorHeap(basicDescriptorHeapInitParam);

		// �|�X�g�G�t�F�N�g�����
		tktk::PostEffectMaterialInitParam postEffectInitParam{};
		postEffectInitParam.usePipeLineStateHandle	= tktk::DX12GameManager::getSystemHandle(tktk::SystemPipeLineStateType::PostEffectMonochrome);
		postEffectInitParam.useDescriptorHeapHandle = postEffectBasicDescriptorHeapHandle;
		postEffectInitParam.autoClearRtvDescriptorHeapHandleArray = { postEffectRtvDescriptorHeapHandle };
		tktk::DX12GameManager::createPostEffectMaterialAndAttachId(PostEffectMaterialId::PostEffectTest, postEffectInitParam);
	}

	// �T�E���h�����[�h����
	{
		tktk::DX12GameManager::loadSoundAndAttachId(SoundId::TestSe, "res/Sound/PlayerShot.wav");//Fier damage PlayerShot
		tktk::DX12GameManager::loadSoundAndAttachId(SoundId::TestBgm, "res/Sound/kendo.wav");
	}

	// ���_�J���[�QD�|���S���`��ɕK�v�ȃ��\�[�X�����
	{
		//// �萔�o�b�t�@�����
		//unsigned int vertexColorPolygonCbufferHandle = tktk::DX12GameManager::createCBuffer(VertexColor2DPolygonConstantBufferData());

		//// �f�B�X�N���v�^�q�[�v�����
		//tktk::BasicDescriptorHeapInitParam descriptorHeapInitParam{};
		//descriptorHeapInitParam.shaderVisible = true;
		//descriptorHeapInitParam.descriptorTableParamArray.resize(1U);
		//{ /* �R���X�^���g�o�b�t�@�[�r���[�̃f�B�X�N���v�^�̏�� */
		//	auto& cbufferViewDescriptorParam = descriptorHeapInitParam.descriptorTableParamArray.at(0U);
		//	cbufferViewDescriptorParam.type = tktk::BasicDescriptorType::constantBuffer;

		//	// ���_�J���[�萔�o�b�t�@�̂P���
		//	cbufferViewDescriptorParam.descriptorParamArray = {
		//		{ tktk::BufferType::constant,		vertexColorPolygonCbufferHandle }
		//	};
		//}
		//unsigned int vertexColorPolygonBasicDescriptorHeapHandle = tktk::DX12GameManager::createBasicDescriptorHeap(descriptorHeapInitParam);

		//// ���[�g�V�O�l�`�������
		//tktk::RootSignatureInitParam rootSignatureInitParam{};
		//rootSignatureInitParam.flag = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
		//rootSignatureInitParam.rootParamArray.resize(1U);
		//{/* �萔�o�b�t�@�p�̃��[�g�p�����[�^ */
		//	rootSignatureInitParam.rootParamArray.at(0).shaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
		//	rootSignatureInitParam.rootParamArray.at(0).descriptorTable.resize(1U);
		//	{
		//		rootSignatureInitParam.rootParamArray.at(0).descriptorTable.at(0).numDescriptors = 1U;
		//		rootSignatureInitParam.rootParamArray.at(0).descriptorTable.at(0).type = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
		//	}
		//}
		//rootSignatureInitParam.samplerDescArray.resize(0U);
		//unsigned int vertexColorPolygonRootSignatureHandle = tktk::DX12GameManager::createRootSignature(rootSignatureInitParam);

		//// �p�C�v���C���X�e�[�g�����
		//D3D12_RENDER_TARGET_BLEND_DESC renderTargetBlendDesc{};
		//renderTargetBlendDesc.BlendEnable = true;
		//renderTargetBlendDesc.SrcBlend = D3D12_BLEND_SRC_ALPHA;
		//renderTargetBlendDesc.DestBlend = D3D12_BLEND_INV_SRC_ALPHA;
		//renderTargetBlendDesc.BlendOp = D3D12_BLEND_OP_ADD;
		//renderTargetBlendDesc.SrcBlendAlpha = D3D12_BLEND_ONE;
		//renderTargetBlendDesc.DestBlendAlpha = D3D12_BLEND_ZERO;
		//renderTargetBlendDesc.BlendOpAlpha = D3D12_BLEND_OP_ADD;
		//renderTargetBlendDesc.LogicOpEnable = false;
		//renderTargetBlendDesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;

		//tktk::PipeLineStateInitParam pipeLineStateInitParam{};
		//pipeLineStateInitParam.rasterizerDesc.MultisampleEnable = false;
		//pipeLineStateInitParam.rasterizerDesc.CullMode = D3D12_CULL_MODE_NONE;
		//pipeLineStateInitParam.rasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;
		//pipeLineStateInitParam.rasterizerDesc.DepthClipEnable = false;
		//pipeLineStateInitParam.sampleMask = 0xffffffff;
		//pipeLineStateInitParam.blendDesc.AlphaToCoverageEnable = false;
		//pipeLineStateInitParam.blendDesc.IndependentBlendEnable = true;
		//pipeLineStateInitParam.blendDesc.RenderTarget[0] = renderTargetBlendDesc;
		//pipeLineStateInitParam.inputLayoutArray = {
		//	{ "POSITION",	0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
		//	{ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, D3D12_APPEND_ALIGNED_ELEMENT, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 }
		//};
		//pipeLineStateInitParam.primitiveTopology = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
		//pipeLineStateInitParam.renderTargetFormatArray = { DXGI_FORMAT_R8G8B8A8_UNORM };
		//pipeLineStateInitParam.rootSignatureHandle = vertexColorPolygonRootSignatureHandle;

		//tktk::ShaderFilePaths shaderFilePaths{};
		//shaderFilePaths.vsFilePath = "res/Shader/VertexColor2DPolygonVertexShader.cso";
		//shaderFilePaths.psFilePath = "res/Shader/VertexColor2DPolygonPixelShader.cso";

		//unsigned int vertexColorPolygonPipeLineStateHandle = tktk::DX12GameManager::createPipeLineState(pipeLineStateInitParam, shaderFilePaths);
	}

	// 2D���C���}�e���A�������
	{
		tktk::DX12GameManager::createLine2DMaterialAndAttachId(Line2DMaterialId::ElementShapeGuide);
	}

	tktk::DX12GameManager::addUpdatePriority<CursorScript>(-10.0f);

	// �ǂݍ��݃V�[���𖳌��ɂ���
	tktk::DX12GameManager::disableScene(tktk::DX12GameManager::getSceneHandle(SceneId::Loading));

	// ���C���V�[����L���ɂ���
	tktk::DX12GameManager::enableScene(tktk::DX12GameManager::getSceneHandle(SceneId::Main));
}

void LoadingScene::end()
{
}
