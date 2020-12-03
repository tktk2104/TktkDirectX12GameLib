#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/MeshResource.h"

#include <TktkDX12Game/_MainManager/DX12GameManager.h>
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Skeleton/SkeletonManager.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Motion/MotionManager.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Motion/MotionBoneParam.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Mesh/MeshManager.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/MeshMaterial/MeshMaterialManager.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Mesh/Loader/MeshPmdLoader.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Mesh/Loader/MeshPmxLoader.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Structs/MeshResourceInitParam.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Mesh/Maker/BoxMeshMaker.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Mesh/Maker/SphereMeshMaker.h"

#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Mesh/Structs/CameraCbuffer.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/Mesh/Structs/MeshShadowMapCBuffer.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/MeshMaterial/Structs/MeshMaterialCbuffer.h"
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/MeshResouse/MeshMaterial/Structs/MonoColorMeshCbuffer.h"

namespace tktk
{
    inline void createMeshRootSignature();
    inline void createMeshPipeLineState(const std::string& simpleMeshVS, const std::string& skinningMeshVS, const std::string& basicMeshPS);
    
	inline void createMonoColorMeshRootSignature();
	inline void createMonoColorMeshPipeLineState(const std::string& simpleMeshVS, const std::string& skinningMeshVS, const std::string& pS);
	
	inline void createWriteShadowMapRootSignature();
    inline void createWriteShadowMapPipeLineState(const std::string& simpleMeshShadowMapVsFilePath, const std::string& skinningMeshShadowMapVsFilePath);
    inline void createWriteShadowMapDescriptorHeap();

    MeshResource::MeshResource(const MeshResourceInitParam& initParam)
    {
		DX12GameManager::setSystemHandle(SystemCBufferType::Camera,			DX12GameManager::createCBuffer(CameraCbuffer()));
		DX12GameManager::setSystemHandle(SystemCBufferType::ShadowMap,	DX12GameManager::createCBuffer(MeshShadowMapCBuffer()));

		// ���b�V���`��ɕK�v�Ȓ萔�o�b�t�@�����
		DX12GameManager::setSystemHandle(SystemCBufferType::MeshMaterial,	DX12GameManager::createCBuffer(MeshMaterialCbuffer()));
		DX12GameManager::setSystemHandle(SystemCBufferType::MonoColorMesh,	DX12GameManager::createCBuffer(MonoColorMeshCbuffer()));

		// ���b�V���`��ɕK�v�ȃe�N�X�`���o�b�t�@�����
		TexBufFormatParam formatParam{};
		formatParam.resourceDimension	= D3D12_RESOURCE_DIMENSION_TEXTURE2D;
		formatParam.format				= DXGI_FORMAT_R32G32B32A32_FLOAT;
		formatParam.arraySize			= 1U;
		formatParam.mipLevels			= 1U;
		formatParam.sampleDescCount		= 1U;
		formatParam.sampleDescQuality	= 0U;
		TexBuffData buffdata{};
		buffdata.textureData	= std::vector<unsigned char>(sizeof(tktkMath::Matrix4) * 128U * 128U);
		buffdata.width			= (sizeof(tktkMath::Matrix4) * 128U) / 16U;
		buffdata.height			= 128U;
		DX12GameManager::setSystemHandle(SystemTextureBufferType::MeshBoneMatrix, DX12GameManager::gpuPriorityCreateTextureBuffer(formatParam, buffdata));

        // �e�탊�\�[�X�N���X�����
        m_skeleton              = std::make_unique<SkeletonManager>(initParam.skeletonMgrParam);
        m_motion                = std::make_unique<MotionManager>(initParam.motionMgrParam);
        m_meshManager           = std::make_unique<MeshManager>(initParam.meshMgrParam);
        m_meshMaterialManager   = std::make_unique<MeshMaterialManager>(initParam.meshMatMgrParam);

		// ���b�V���`��̃p�C�v���C���X�e�[�g�������
		createMeshRootSignature();
		createMeshPipeLineState(initParam.shaderFilePaths.simpleMeshVS, initParam.shaderFilePaths.skinningMeshVS, initParam.shaderFilePaths.basicMeshPS);

		// �P�F���b�V���`��̃p�C�v���C���X�e�[�g�������
		createMonoColorMeshRootSignature();
		createMonoColorMeshPipeLineState(initParam.shaderFilePaths.monoColorSimpleMeshVS, initParam.shaderFilePaths.monoColorSkinningMeshVS, initParam.shaderFilePaths.monoColorMeshPS);

		// �V���h�E�}�b�v�̃p�C�v���C���X�e�[�g�������
		createWriteShadowMapRootSignature();
		createWriteShadowMapPipeLineState(initParam.shaderFilePaths.simpleMeshShadowMapVs, initParam.shaderFilePaths.skinningMeshShadowMapVs);
		createWriteShadowMapDescriptorHeap();

		// �e�탁�b�V���쐬�N���X�����
		m_boxMeshMaker		= std::make_unique<BoxMeshMaker>();
		m_sphereMeshMaker	= std::make_unique<SphereMeshMaker>();
    }

    // �f�X�g���N�^���C�����C��������
    MeshResource::~MeshResource() = default;

    size_t MeshResource::createSkeleton(const SkeletonInitParam& initParam)
    {
        return m_skeleton->create(initParam);
    }

    size_t MeshResource::copySkeleton(size_t originalHandle)
    {
        return m_skeleton->copy(originalHandle);
    }

    size_t MeshResource::loadMotion(const std::string& motionFileName)
    {
        return m_motion->load(motionFileName);
    }

    size_t MeshResource::getMotionEndFrameNo(size_t handle) const
    {
        return m_motion->getEndFrameNo(handle);
    }

    void MeshResource::updateMotion(size_t skeletonHandle, size_t curMotionHandle, size_t preMotionHandle, float curFrame, float preFrame, float amount)
    {
        m_skeleton->transform(skeletonHandle, m_motion->calculateBoneTransformMatrices(curMotionHandle, preMotionHandle, curFrame, preFrame, amount));
    }

	void MeshResource::createSystemMesh()
	{
		// �`��R���|�[�l���g�̏������ϐ�
		MeshDrawFuncRunnerInitParam drawFuncRunnerInitParam = MeshDrawFuncRunnerInitParam::create();

		// �����̃��C���[�t���[�����b�V�������
		DX12GameManager::setSystemHandle(SystemMeshType::BoxWireFrame, m_boxMeshMaker->makeBoxMeshWireFrame(drawFuncRunnerInitParam));

		// �P�F�����̃��b�V�������
		DX12GameManager::setSystemHandle(SystemMeshType::Box, m_boxMeshMaker->makeMonoColorBoxMesh(drawFuncRunnerInitParam));

		// ���̃��C���[�t���[�����b�V�������
		DX12GameManager::setSystemHandle(SystemMeshType::SphereWireFrame, m_sphereMeshMaker->makeSphereMeshWireFrame(drawFuncRunnerInitParam));

		// �P�F���̃��b�V�������
		DX12GameManager::setSystemHandle(SystemMeshType::Sphere, m_sphereMeshMaker->makeMonoColorSphereMesh(drawFuncRunnerInitParam));
	}

	size_t MeshResource::createMesh(const MeshInitParam& initParam)
    {
        return m_meshManager->craete(initParam);
    }

    size_t MeshResource::copyMesh(size_t originalHandle)
    {
        return m_meshManager->copy(originalHandle);
    }

    size_t MeshResource::createMeshMaterial(const MeshMaterialInitParam& initParam)
    {
        return m_meshMaterialManager->create(initParam);
    }

    size_t MeshResource::copyMeshMaterial(size_t originalHandle)
    {
        return m_meshMaterialManager->copy(originalHandle);
    }

	size_t MeshResource::makeBoxMesh(size_t albedoMapTextureHandle, const MeshDrawFuncRunnerInitParam& funcRunnerInitParam)
	{
		return m_boxMeshMaker->makeBoxMesh(albedoMapTextureHandle, funcRunnerInitParam);
	}

	size_t MeshResource::makeSkyBoxMesh(size_t skyBoxTextureHandle, const MeshDrawFuncRunnerInitParam& funcRunnerInitParam)
	{
		return m_boxMeshMaker->makeSkyBoxMesh(skyBoxTextureHandle, funcRunnerInitParam);
	}

	MeshLoadPmdReturnValue MeshResource::loadPmd(const MeshLoadPmdArgs& args, const MeshDrawFuncRunnerInitParam& funcRunnerInitParam)
	{
		return MeshPmdLoader::loadPmd(args, funcRunnerInitParam);
	}

	MeshLoadPmxReturnValue MeshResource::loadPmx(const MeshLoadPmxArgs& args, const MeshDrawFuncRunnerInitParam& funcRunnerInitParam)
	{
		return MeshPmxLoader::loadPmx(args, funcRunnerInitParam);
	}

    void MeshResource::setMaterialHandle(size_t meshHandle, size_t materialSlot, size_t materialHandle)
    {
        m_meshManager->setMaterialHandle(meshHandle, materialSlot, materialHandle);
    }

    void MeshResource::setMaterialData(size_t handle) const
    {
        m_meshMaterialManager->setMaterialData(handle);
    }

    void MeshResource::addMaterialAppendParam(size_t handle, const MeshMaterialAppendParamInitParam& initParam)
    {
        m_meshMaterialManager->addAppendParam(handle, initParam);
    }

    void MeshResource::updateMaterialAppendParam(size_t handle, const MeshMaterialAppendParamUpdateFuncArgs& updateFuncArgs)
    {
        m_meshMaterialManager->updateAppendParam(handle, updateFuncArgs);
    }

	void MeshResource::clearInstanceParam(size_t handle)
	{
		m_meshManager->clearInstanceParam(handle);
	}

	void MeshResource::addInstanceVertParam(size_t handle, const CopySourceDataCarrier& instanceParam)
	{
		m_meshManager->addInstanceVertParam(handle, instanceParam);
	}

	void MeshResource::addInstanceBoneMatrix(size_t meshHandle, size_t skeletonHandle)
	{
		m_meshManager->addInstanceBoneMatrix(meshHandle, m_skeleton->getBoneMatrixArray(skeletonHandle));
	}

	void MeshResource::writeShadowMap(size_t handle) const
	{
		m_meshManager->writeShadowMap(handle);
	}

	void MeshResource::writeShadowMapUseBone(size_t handle) const
	{
		m_meshManager->writeShadowMapUseBone(handle);
	}

	void MeshResource::draw(size_t handle, const MeshDrawFuncBaseArgs& baseArgs) const
	{
		m_meshManager->draw(handle, baseArgs);
	}

	void MeshResource::drawUseBone(size_t handle, const MeshDrawFuncBaseArgs& baseArgs) const
	{
		m_meshManager->drawUseBone(handle, baseArgs);
	}

	void createMeshRootSignature()
	{
		// ���ʂ̏������ϐ�
		RootSignatureInitParam initParam{};
		initParam.flag = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
		initParam.rootParamArray.resize(3U);
		initParam.rootParamArray.at(0U).shaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
		initParam.rootParamArray.at(0U).descriptorTable = { { 3U, D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 0U } };	// PS�e�N�X�`���p
		initParam.rootParamArray.at(1U).shaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
		initParam.rootParamArray.at(1U).descriptorTable = { { 3U, D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 0U } };	// VS�萔�o�b�t�@�p
		initParam.rootParamArray.at(2U).shaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
		initParam.rootParamArray.at(2U).descriptorTable = { { 2U, D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 0U } };	// PS�萔�o�b�t�@�p

		//****************************************************************************************************
		// �V���v�����b�V���̃��[�g�V�O�l�`�������
		initParam.samplerDescArray.resize(3U);
		{/* �T���v���[�̐ݒ� */
			initParam.samplerDescArray.at(0U).addressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
			initParam.samplerDescArray.at(0U).addressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
			initParam.samplerDescArray.at(0U).addressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
			initParam.samplerDescArray.at(0U).bordercolor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;
			initParam.samplerDescArray.at(0U).filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
			initParam.samplerDescArray.at(0U).maxLod = D3D12_FLOAT32_MAX;
			initParam.samplerDescArray.at(0U).minLod = 0.0f;
			initParam.samplerDescArray.at(0U).shaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
			initParam.samplerDescArray.at(0U).comparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
			initParam.samplerDescArray.at(0U).shaderRegister = 0U;
		}
		{
			initParam.samplerDescArray.at(1U).addressU = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
			initParam.samplerDescArray.at(1U).addressV = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
			initParam.samplerDescArray.at(1U).addressW = D3D12_TEXTURE_ADDRESS_MODE_BORDER;
			initParam.samplerDescArray.at(1U).bordercolor = D3D12_STATIC_BORDER_COLOR_OPAQUE_WHITE;
			initParam.samplerDescArray.at(1U).filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
			initParam.samplerDescArray.at(1U).maxLod = D3D12_FLOAT32_MAX;
			initParam.samplerDescArray.at(1U).minLod = 0.0f;
			initParam.samplerDescArray.at(1U).shaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
			initParam.samplerDescArray.at(1U).comparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
			initParam.samplerDescArray.at(1U).shaderRegister = 1U;
		}
		{/* �T���v���[�̐ݒ� */
			initParam.samplerDescArray.at(2U).addressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
			initParam.samplerDescArray.at(2U).addressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
			initParam.samplerDescArray.at(2U).addressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
			initParam.samplerDescArray.at(2U).bordercolor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;
			initParam.samplerDescArray.at(2U).filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
			initParam.samplerDescArray.at(2U).maxLod = D3D12_FLOAT32_MAX;
			initParam.samplerDescArray.at(2U).minLod = 0.0f;
			initParam.samplerDescArray.at(2U).shaderVisibility = D3D12_SHADER_VISIBILITY_PIXEL;
			initParam.samplerDescArray.at(2U).comparisonFunc = D3D12_COMPARISON_FUNC_NEVER;
			initParam.samplerDescArray.at(2U).shaderRegister = 2U;
		}
		DX12GameManager::setSystemHandle(SystemRootSignatureType::SimpleMesh, DX12GameManager::createRootSignature(initParam));

		//****************************************************************************************************
		// �X�L�j���O���b�V���̃��[�g�V�O�l�`�������
		initParam.rootParamArray.resize(4U);
		initParam.rootParamArray.at(3U).shaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
		initParam.rootParamArray.at(3U).descriptorTable = { { 1U, D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 0U } };	// VS�e�N�X�`���p
		/* �T���v���[�̐ݒ�́g�V���v�����b�V���̃��[�g�V�O�l�`���h�Ɠ��� */
		DX12GameManager::setSystemHandle(SystemRootSignatureType::SkinningMesh, DX12GameManager::createRootSignature(initParam));
	}

	void createMeshPipeLineState(const std::string& simpleMeshVS, const std::string& skinningMeshVS, const std::string& basicMeshPS)
	{
		// ���ʂ̏������ϐ�
		D3D12_RENDER_TARGET_BLEND_DESC renderTargetBlendDesc{};
		renderTargetBlendDesc.BlendEnable			= false;
		renderTargetBlendDesc.LogicOpEnable			= false;
		renderTargetBlendDesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
		PipeLineStateInitParam initParam{};
		initParam.rasterizerDesc.MultisampleEnable	= false;
		initParam.rasterizerDesc.DepthClipEnable	= true;
		initParam.blendDesc.AlphaToCoverageEnable	= false;
		initParam.blendDesc.IndependentBlendEnable	= false;
		initParam.blendDesc.RenderTarget[0]			= renderTargetBlendDesc;
		initParam.inputLayoutArray = {
			{ "POSITION",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D12_APPEND_ALIGNED_ELEMENT,	D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,		0 },
			{ "NORMAL",			0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D12_APPEND_ALIGNED_ELEMENT,	D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,		0 },
			{ "TEXCOORD",		0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D12_APPEND_ALIGNED_ELEMENT,	D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,		0 },
			{ "BLENDINDICES",	0, DXGI_FORMAT_R8G8B8A8_SINT,		0, D3D12_APPEND_ALIGNED_ELEMENT,	D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,		0 },
			{ "BLENDWEIGHT",	0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, D3D12_APPEND_ALIGNED_ELEMENT,	D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,		0 },
			{ "TANGENT",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D12_APPEND_ALIGNED_ELEMENT,	D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,		0 },
			{ "BINORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D12_APPEND_ALIGNED_ELEMENT,	D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,		0 },
			{ "WORLDMATRIX",	0, DXGI_FORMAT_R32G32B32A32_FLOAT,	1, 0,								D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA,	1 },
			{ "WORLDMATRIX",	1, DXGI_FORMAT_R32G32B32A32_FLOAT,	1, 16,								D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA,	1 },
			{ "WORLDMATRIX",	2, DXGI_FORMAT_R32G32B32A32_FLOAT,	1, 32,								D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA,	1 },
			{ "WORLDMATRIX",	3, DXGI_FORMAT_R32G32B32A32_FLOAT,	1, 48,								D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA,	1 },
		};
		initParam.primitiveTopology			= D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
		initParam.renderTargetFormatArray	= { DXGI_FORMAT_R8G8B8A8_UNORM };
		initParam.useDepth					= true;
		initParam.writeDepth				= true;
		initParam.depthFunc					= D3D12_COMPARISON_FUNC_LESS;
		ShaderFilePaths shaderFilePaths{};

		//****************************************************************************************************
		// �V���v�����b�V���̃p�C�v���C���X�e�[�g�����
		initParam.rasterizerDesc.CullMode = D3D12_CULL_MODE_BACK;
		initParam.rasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;
		initParam.rootSignatureHandle = DX12GameManager::getSystemHandle(SystemRootSignatureType::SimpleMesh);
		shaderFilePaths.vsFilePath = simpleMeshVS;
		shaderFilePaths.psFilePath = basicMeshPS;
		DX12GameManager::setSystemHandle(SystemPipeLineStateType::SimpleMesh, DX12GameManager::createPipeLineState(initParam, shaderFilePaths));

		//****************************************************************************************************
		// �X�L�j���O���b�V���̃p�C�v���C���X�e�[�g�����
		initParam.rasterizerDesc.CullMode = D3D12_CULL_MODE_BACK;
		initParam.rasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;
		initParam.rootSignatureHandle = DX12GameManager::getSystemHandle(SystemRootSignatureType::SkinningMesh);
		shaderFilePaths.vsFilePath = skinningMeshVS;
		shaderFilePaths.psFilePath = basicMeshPS;
		DX12GameManager::setSystemHandle(SystemPipeLineStateType::SkinningMesh, DX12GameManager::createPipeLineState(initParam, shaderFilePaths));

		//****************************************************************************************************
		// ���]�����V���v�����b�V���̃p�C�v���C���X�e�[�g�����
		initParam.rasterizerDesc.CullMode = D3D12_CULL_MODE_FRONT;
		initParam.rasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;
		initParam.rootSignatureHandle = DX12GameManager::getSystemHandle(SystemRootSignatureType::SimpleMesh);
		shaderFilePaths.vsFilePath = simpleMeshVS;
		shaderFilePaths.psFilePath = basicMeshPS;
		DX12GameManager::setSystemHandle(SystemPipeLineStateType::InvertSimpleMesh, DX12GameManager::createPipeLineState(initParam, shaderFilePaths));

		//****************************************************************************************************
		// ���]�����X�L�j���O���b�V���̃p�C�v���C���X�e�[�g�����
		initParam.rasterizerDesc.CullMode = D3D12_CULL_MODE_FRONT;
		initParam.rasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;
		initParam.rootSignatureHandle = DX12GameManager::getSystemHandle(SystemRootSignatureType::SkinningMesh);
		shaderFilePaths.vsFilePath = skinningMeshVS;
		shaderFilePaths.psFilePath = basicMeshPS;
		DX12GameManager::setSystemHandle(SystemPipeLineStateType::InvertSkinningMesh, DX12GameManager::createPipeLineState(initParam, shaderFilePaths));
	}

	void createMonoColorMeshRootSignature()
	{
		// ���ʂ̏������ϐ�
		RootSignatureInitParam initParam{};
		initParam.flag = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
		initParam.rootParamArray.resize(1U);
		initParam.rootParamArray.at(0U).shaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
		initParam.rootParamArray.at(0U).descriptorTable = { { 1U, D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 0U } };	// VS�萔�o�b�t�@�p

		//****************************************************************************************************
		// �P�F�V���v�����b�V���̃��[�g�V�O�l�`�������
		initParam.samplerDescArray.resize(0U);
		DX12GameManager::setSystemHandle(SystemRootSignatureType::MonoColorSimpleMesh, DX12GameManager::createRootSignature(initParam));

		//****************************************************************************************************
		// �P�F�X�L�j���O���b�V���̃��[�g�V�O�l�`�������
		initParam.rootParamArray.resize(2U);
		initParam.rootParamArray.at(1U).shaderVisibility	= D3D12_SHADER_VISIBILITY_VERTEX;
		initParam.rootParamArray.at(1U).descriptorTable		= { { 1U, D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 0U } };	// VS�e�N�X�`���p
		/* �T���v���[�̐ݒ�́g�P�F�V���v�����b�V���̃��[�g�V�O�l�`���h�Ɠ��� */
		DX12GameManager::setSystemHandle(SystemRootSignatureType::MonoColorSkinningMesh, DX12GameManager::createRootSignature(initParam));
	}

	void createMonoColorMeshPipeLineState(const std::string& simpleMeshVS, const std::string& skinningMeshVS, const std::string& pS)
	{
		// ���ʂ̏������ϐ�
		D3D12_RENDER_TARGET_BLEND_DESC renderTargetBlendDesc{};
		renderTargetBlendDesc.BlendEnable			= false;
		renderTargetBlendDesc.LogicOpEnable			= false;
		renderTargetBlendDesc.RenderTargetWriteMask = D3D12_COLOR_WRITE_ENABLE_ALL;
		PipeLineStateInitParam initParam{};
		initParam.rasterizerDesc.MultisampleEnable	= false;
		initParam.rasterizerDesc.DepthClipEnable	= true;
		initParam.blendDesc.AlphaToCoverageEnable	= false;
		initParam.blendDesc.IndependentBlendEnable	= false;
		initParam.blendDesc.RenderTarget[0]			= renderTargetBlendDesc;
		initParam.inputLayoutArray = {
			{ "POSITION",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D12_APPEND_ALIGNED_ELEMENT,	D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,		0 },
			{ "NORMAL",			0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D12_APPEND_ALIGNED_ELEMENT,	D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,		0 },
			{ "TEXCOORD",		0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D12_APPEND_ALIGNED_ELEMENT,	D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,		0 },
			{ "BLENDINDICES",	0, DXGI_FORMAT_R8G8B8A8_SINT,		0, D3D12_APPEND_ALIGNED_ELEMENT,	D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,		0 },
			{ "BLENDWEIGHT",	0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, D3D12_APPEND_ALIGNED_ELEMENT,	D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,		0 },
			{ "TANGENT",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D12_APPEND_ALIGNED_ELEMENT,	D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,		0 },
			{ "BINORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D12_APPEND_ALIGNED_ELEMENT,	D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,		0 },
			{ "WORLDMATRIX",	0, DXGI_FORMAT_R32G32B32A32_FLOAT,	1, 0,								D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA,	1 },
			{ "WORLDMATRIX",	1, DXGI_FORMAT_R32G32B32A32_FLOAT,	1, 16,								D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA,	1 },
			{ "WORLDMATRIX",	2, DXGI_FORMAT_R32G32B32A32_FLOAT,	1, 32,								D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA,	1 },
			{ "WORLDMATRIX",	3, DXGI_FORMAT_R32G32B32A32_FLOAT,	1, 48,								D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA,	1 },
			{ "ALBEDOCOLOR",	0, DXGI_FORMAT_R32G32B32A32_FLOAT,	1, 64,								D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA,	1 },
		};
		initParam.primitiveTopology			= D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
		initParam.renderTargetFormatArray	= { DXGI_FORMAT_R8G8B8A8_UNORM };
		initParam.useDepth					= true;
		initParam.writeDepth				= true;
		initParam.depthFunc					= D3D12_COMPARISON_FUNC_LESS;
		ShaderFilePaths shaderFilePaths{};

		//****************************************************************************************************
		// �P�F�V���v�����b�V���̃p�C�v���C���X�e�[�g�����
		initParam.rasterizerDesc.CullMode = D3D12_CULL_MODE_BACK;
		initParam.rasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;
		initParam.rootSignatureHandle = DX12GameManager::getSystemHandle(SystemRootSignatureType::MonoColorSimpleMesh);
		shaderFilePaths.vsFilePath = simpleMeshVS;
		shaderFilePaths.psFilePath = pS;
		DX12GameManager::setSystemHandle(SystemPipeLineStateType::MonoColorSimpleMesh, DX12GameManager::createPipeLineState(initParam, shaderFilePaths));

		//****************************************************************************************************
		// �P�F�X�L�j���O���b�V���̃p�C�v���C���X�e�[�g�����
		initParam.rasterizerDesc.CullMode = D3D12_CULL_MODE_BACK;
		initParam.rasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;
		initParam.rootSignatureHandle = DX12GameManager::getSystemHandle(SystemRootSignatureType::MonoColorSkinningMesh);
		shaderFilePaths.vsFilePath = skinningMeshVS;
		shaderFilePaths.psFilePath = pS;
		DX12GameManager::setSystemHandle(SystemPipeLineStateType::MonoColorSkinningMesh, DX12GameManager::createPipeLineState(initParam, shaderFilePaths));

		//****************************************************************************************************
		// �P�F�V���v�����b�V�����C���[�t���[���̃p�C�v���C���X�e�[�g�����
		initParam.rasterizerDesc.CullMode = D3D12_CULL_MODE_BACK;
		initParam.rasterizerDesc.FillMode = D3D12_FILL_MODE_WIREFRAME;
		initParam.rootSignatureHandle = DX12GameManager::getSystemHandle(SystemRootSignatureType::MonoColorSimpleMesh);
		shaderFilePaths.vsFilePath = simpleMeshVS;
		shaderFilePaths.psFilePath = pS;
		DX12GameManager::setSystemHandle(SystemPipeLineStateType::MonoColorSimpleMeshWireFrame, DX12GameManager::createPipeLineState(initParam, shaderFilePaths));

		//****************************************************************************************************
		// �P�F�X�L�j���O���b�V�����C���[�t���[���̃p�C�v���C���X�e�[�g�����
		initParam.rasterizerDesc.CullMode = D3D12_CULL_MODE_BACK;
		initParam.rasterizerDesc.FillMode = D3D12_FILL_MODE_WIREFRAME;
		initParam.rootSignatureHandle = DX12GameManager::getSystemHandle(SystemRootSignatureType::MonoColorSkinningMesh);
		shaderFilePaths.vsFilePath = skinningMeshVS;
		shaderFilePaths.psFilePath = pS;
		DX12GameManager::setSystemHandle(SystemPipeLineStateType::MonoColorSkinningMeshWireFrame, DX12GameManager::createPipeLineState(initParam, shaderFilePaths));
	}

	void createWriteShadowMapRootSignature()
	{
		// ���ʂ̏������ϐ�
		RootSignatureInitParam initParam{};
		initParam.flag = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
		initParam.rootParamArray.resize(1U);
		initParam.rootParamArray.at(0U).shaderVisibility = D3D12_SHADER_VISIBILITY_VERTEX;
		initParam.rootParamArray.at(0U).descriptorTable = { { 1U, D3D12_DESCRIPTOR_RANGE_TYPE_CBV, 0U } };
		initParam.samplerDescArray.resize(0U);

		//****************************************************************************************************
		// �V���v�����b�V���̃V���h�E�}�b�v�p���[�g�V�O�l�`�������
		DX12GameManager::setSystemHandle(SystemRootSignatureType::SimpleMeshShadowMap, DX12GameManager::createRootSignature(initParam));

		//****************************************************************************************************
		// �X�L�j���O���b�V���̃V���h�E�}�b�v�p���[�g�V�O�l�`�������
		initParam.rootParamArray.resize(2U);
		initParam.rootParamArray.at(1U).shaderVisibility	= D3D12_SHADER_VISIBILITY_VERTEX;
		initParam.rootParamArray.at(1U).descriptorTable		= { { 1U, D3D12_DESCRIPTOR_RANGE_TYPE_SRV, 0U } };	// VS�e�N�X�`���p
		DX12GameManager::setSystemHandle(SystemRootSignatureType::SkinningMeshShadowMap, DX12GameManager::createRootSignature(initParam));
	}

	void createWriteShadowMapPipeLineState(const std::string& simpleMeshShadowMapVsFilePath, const std::string& skinningMeshShadowMapVsFilePath)
	{
		// ���ʂ̏������ϐ�
		PipeLineStateInitParam initParam{};
		initParam.rasterizerDesc.MultisampleEnable = false;
		initParam.rasterizerDesc.CullMode = D3D12_CULL_MODE_BACK;
		initParam.rasterizerDesc.FillMode = D3D12_FILL_MODE_SOLID;
		initParam.rasterizerDesc.DepthClipEnable = true;
		initParam.blendDesc.AlphaToCoverageEnable = false;
		initParam.blendDesc.IndependentBlendEnable = false;
		initParam.inputLayoutArray = {
			{ "POSITION",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D12_APPEND_ALIGNED_ELEMENT,	D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,		0 },
			{ "NORMAL",			0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D12_APPEND_ALIGNED_ELEMENT,	D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,		0 },
			{ "TEXCOORD",		0, DXGI_FORMAT_R32G32_FLOAT,		0, D3D12_APPEND_ALIGNED_ELEMENT,	D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,		0 },
			{ "BLENDINDICES",	0, DXGI_FORMAT_R8G8B8A8_SINT,		0, D3D12_APPEND_ALIGNED_ELEMENT,	D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,		0 },
			{ "BLENDWEIGHT",	0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, D3D12_APPEND_ALIGNED_ELEMENT,	D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,		0 },
			{ "TANGENT",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D12_APPEND_ALIGNED_ELEMENT,	D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,		0 },
			{ "BINORMAL",		0, DXGI_FORMAT_R32G32B32_FLOAT,		0, D3D12_APPEND_ALIGNED_ELEMENT,	D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA,		0 },
			{ "WORLDMATRIX",	0, DXGI_FORMAT_R32G32B32A32_FLOAT,	1, 0,								D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA,	1 },
			{ "WORLDMATRIX",	1, DXGI_FORMAT_R32G32B32A32_FLOAT,	1, 16,								D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA,	1 },
			{ "WORLDMATRIX",	2, DXGI_FORMAT_R32G32B32A32_FLOAT,	1, 32,								D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA,	1 },
			{ "WORLDMATRIX",	3, DXGI_FORMAT_R32G32B32A32_FLOAT,	1, 48,								D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA,	1 }
		};
		initParam.primitiveTopology = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
		initParam.useDepth = true;
		initParam.writeDepth = true;
		initParam.depthFunc = D3D12_COMPARISON_FUNC_LESS;
		ShaderFilePaths shaderFilePaths{};
		shaderFilePaths.psFilePath = "";

		//****************************************************************************************************
		// �V���v�����b�V���̃V���h�E�}�b�v�p�p�C�v���C���X�e�[�g�����
		initParam.rootSignatureHandle = DX12GameManager::getSystemHandle(SystemRootSignatureType::SimpleMeshShadowMap);
		shaderFilePaths.vsFilePath = simpleMeshShadowMapVsFilePath;
		DX12GameManager::setSystemHandle(SystemPipeLineStateType::SimpleMeshShadowMap, DX12GameManager::createPipeLineState(initParam, shaderFilePaths));

		//****************************************************************************************************
		// �X�L�j���O���b�V���̃V���h�E�}�b�v�p�p�C�v���C���X�e�[�g�����
		initParam.rootSignatureHandle = DX12GameManager::getSystemHandle(SystemRootSignatureType::SkinningMeshShadowMap);
		shaderFilePaths.vsFilePath = skinningMeshShadowMapVsFilePath;
		DX12GameManager::setSystemHandle(SystemPipeLineStateType::SkinningMeshShadowMap, DX12GameManager::createPipeLineState(initParam, shaderFilePaths));
	}

	void createWriteShadowMapDescriptorHeap()
	{
		// ���ʂ̏������ϐ�
		BasicDescriptorHeapInitParam initParam{};
		initParam.shaderVisible = true;
		initParam.descriptorTableParamArray.resize(1U);
		initParam.descriptorTableParamArray.at(0U).type					= BasicDescriptorType::constantBuffer;
		initParam.descriptorTableParamArray.at(0U).descriptorParamArray = { { BufferType::constant, DX12GameManager::getSystemHandle(SystemCBufferType::Camera) } };

		//****************************************************************************************************
		// �V���v�����b�V���̃V���h�E�}�b�v�p�̃f�B�X�N���v�^�q�[�v�����
		DX12GameManager::setSystemHandle(SystemBasicDescriptorHeapType::SimpleMeshShadowMap, DX12GameManager::createBasicDescriptorHeap(initParam));

		//****************************************************************************************************
		// �X�L�j���O���b�V���̃V���h�E�}�b�v�p�̃f�B�X�N���v�^�q�[�v�����
		initParam.descriptorTableParamArray.resize(2U);
		initParam.descriptorTableParamArray.at(1U).type = BasicDescriptorType::textureBuffer;
		initParam.descriptorTableParamArray.at(1U).descriptorParamArray = { { BufferType::texture,	DX12GameManager::getSystemHandle(SystemTextureBufferType::MeshBoneMatrix)} };
		DX12GameManager::setSystemHandle(SystemBasicDescriptorHeapType::SkinningMeshShadowMap, DX12GameManager::createBasicDescriptorHeap(initParam));
	}
}