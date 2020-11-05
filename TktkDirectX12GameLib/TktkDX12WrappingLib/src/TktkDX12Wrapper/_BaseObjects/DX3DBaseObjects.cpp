#include "TktkDX12Wrapper/_BaseObjects/DX3DBaseObjects.h"

#include <TktkMath/Structs/Vector2.h>
#include <TktkMath/Structs/Matrix4.h>
#include "TktkDX12Wrapper/SwapChain/SwapChain.h"
#include "TktkDX12Wrapper/Fence/Fence.h"
#include "TktkDX12Wrapper/Resource/DX3DResource.h"

namespace tktk
{
	DX3DBaseObjects::DX3DBaseObjects(const DX3DBaseObjectsInitParam& initParam)
		: m_backGroundColor(initParam.backGroundColor)
	{
		// DX12�̃��\�[�X�̊Ǘ��N���X�����
		m_dX3DResource	= std::make_unique<DX3DResource>(initParam.resourceNum);

#ifdef _DEBUG
		if (initParam.craeteDebugLayer)
		{
			ID3D12Debug* debugLayer{ nullptr };
			D3D12GetDebugInterface(IID_PPV_ARGS(&debugLayer));
			debugLayer->EnableDebugLayer();

			ID3D12Debug1* debugLayer1{ nullptr };
			debugLayer->QueryInterface(IID_PPV_ARGS(&debugLayer1));
			debugLayer1->SetEnableGPUBasedValidation(true);

			debugLayer1->Release();
			debugLayer->Release();
		}
#endif // _DEBUG

		// �f�o�C�X�����
		D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_12_1, IID_PPV_ARGS(&m_device));

		// �t�@�N�g�������
#ifdef _DEBUG
		if (initParam.craeteDebugLayer) CreateDXGIFactory2(DXGI_CREATE_FACTORY_DEBUG, IID_PPV_ARGS(&m_factory));
		else CreateDXGIFactory1(IID_PPV_ARGS(&m_factory));
#else
		CreateDXGIFactory1(IID_PPV_ARGS(&m_factory));
#endif

		// �R�}���h�A���P�[�^�����
		m_device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&m_commandAllocator));

		// �R�}���h���X�g�����
		m_device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, m_commandAllocator, nullptr, IID_PPV_ARGS(&m_commandList));

		// �R�}���h�L���[�����
		D3D12_COMMAND_QUEUE_DESC commandQueueDesc{};
		commandQueueDesc.Flags		= D3D12_COMMAND_QUEUE_FLAG_NONE;
		commandQueueDesc.NodeMask	= 0;
		commandQueueDesc.Priority	= D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
		commandQueueDesc.Type		= D3D12_COMMAND_LIST_TYPE_DIRECT;
		m_device->CreateCommandQueue(&commandQueueDesc, IID_PPV_ARGS(&m_commandQueue));
		
		// �X���b�v�`�F�[�������
		m_swapChain = std::make_unique<SwapChain>(initParam.hwnd, m_factory, m_commandQueue, initParam.windowSize);

		// �t�F���X�����
		m_fence		= std::make_unique<Fence>(m_device);

		// ���񃊃Z�b�g
		m_commandList->Close();
		m_commandAllocator->Reset();
		m_commandList->Reset(m_commandAllocator, nullptr);

		// �r���[�|�[�g�����
		setSystemHandle(
			SystemViewportType::Basic,
			m_dX3DResource->createViewport({ { initParam.windowSize, tktkMath::Vector2_v::zero, 1.0f, 0.0f } })
		);

		// �V�U�[��`�����
		setSystemHandle(
			SystemScissorRectType::Basic,
			m_dX3DResource->createScissorRect({ { tktkMath::Vector2_v::zero, initParam.windowSize } })
		);

		// �X���b�v�`�F�[���̃o�b�N�o�b�t�@�[���f�B�X�N���v�^�q�[�v�Ŏg�����߂̏���
		setSystemHandle(SystemRtBufferType::BackBuffer_1, m_dX3DResource->createRtBuffer(m_swapChain->getPtr(), 0U));
		setSystemHandle(SystemRtBufferType::BackBuffer_2, m_dX3DResource->createRtBuffer(m_swapChain->getPtr(), 1U));

		// �o�b�N�o�b�t�@�[�p�̃f�B�X�N���v�^�q�[�v�����
		{
			RtvDescriptorHeapInitParam rtvDescriptorHeapInitParam{};
			rtvDescriptorHeapInitParam.shaderVisible = false;
			rtvDescriptorHeapInitParam.descriptorParamArray.resize(2U);
			rtvDescriptorHeapInitParam.descriptorParamArray.at(0U).type		= RtvDescriptorType::normal;
			rtvDescriptorHeapInitParam.descriptorParamArray.at(0U).handle	= getSystemHandle(SystemRtBufferType::BackBuffer_1);
			rtvDescriptorHeapInitParam.descriptorParamArray.at(1U).type		= RtvDescriptorType::normal;
			rtvDescriptorHeapInitParam.descriptorParamArray.at(1U).handle	= getSystemHandle(SystemRtBufferType::BackBuffer_2);

			setSystemHandle(SystemRtvDescriptorHeapType::BackBuffer, m_dX3DResource->createRtvDescriptorHeap(m_device, rtvDescriptorHeapInitParam));
		}

		// �f�t�H���g�̐[�x�o�b�t�@�[�����
		{
			DepthStencilBufferInitParam dsbInitParam{};
			dsbInitParam.depthStencilSize = initParam.windowSize;
			dsbInitParam.useAsShaderResource = false;

			setSystemHandle(SystemDsBufferType::Basic, m_dX3DResource->createDsBuffer(m_device, dsbInitParam));
		}

		// �f�t�H���g�̐[�x�f�B�X�N���v�^�q�[�v�����
		{
			DsvDescriptorHeapInitParam dsvDescriptorHeapInitParam{};
			dsvDescriptorHeapInitParam.shaderVisible = false;
			dsvDescriptorHeapInitParam.descriptorParamArray.push_back({ DsvDescriptorType::normal, getSystemHandle(SystemDsBufferType::Basic) });

			setSystemHandle(SystemDsvDescriptorHeapType::Basic, m_dX3DResource->createDsvDescriptorHeap(m_device, dsvDescriptorHeapInitParam));
		}

		// ���e�N�X�`�������
		{
			TexBufFormatParam formatParam{};
			formatParam.resourceDimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
			formatParam.format = DXGI_FORMAT_R8G8B8A8_UNORM;
			formatParam.arraySize = 1U;
			formatParam.mipLevels = 1U;
			formatParam.sampleDescCount = 1U;
			formatParam.sampleDescQuality = 0U;

			TexBuffData dataParam{};
			dataParam.textureData = {
				255, 255, 255, 255, /**/ 255, 255, 255, 255, /**/ 255, 255, 255, 255, /**/ 255, 255, 255, 255,
				255, 255, 255, 255, /**/ 255, 255, 255, 255, /**/ 255, 255, 255, 255, /**/ 255, 255, 255, 255,
				255, 255, 255, 255, /**/ 255, 255, 255, 255, /**/ 255, 255, 255, 255, /**/ 255, 255, 255, 255,
				255, 255, 255, 255, /**/ 255, 255, 255, 255, /**/ 255, 255, 255, 255, /**/ 255, 255, 255, 255
			};
			dataParam.width = 4U;
			dataParam.height = 4U;

			setSystemHandle(SystemTextureBufferType::White, m_dX3DResource->cpuPriorityCreateTextureBuffer(m_device, formatParam, dataParam));
		}
	}

	DX3DBaseObjects::~DX3DBaseObjects()
	{
		if (m_device != nullptr)
		{
			m_device->Release();
		}

		if (m_factory != nullptr)
		{
			m_factory->Release();
		}

		if (m_commandAllocator != nullptr)
		{
			m_commandAllocator->Release();
		}

		if (m_commandList != nullptr)
		{
			m_commandList->Release();
		}

		if (m_commandQueue != nullptr)
		{
			m_commandQueue->Release();
		}
	}

	void DX3DBaseObjects::beginDraw()
	{
		// ���݂̃o�b�N�o�b�t�@�[�����ʂ���C���f�b�N�X���X�V����
		m_swapChain->updateBackBufferIndex();
		
		// ���݂̃o�b�N�o�b�t�@�[�̎�ނ��um_curBackBufferIndex�v���狁�߂�
		auto curBackBufferType = (m_swapChain->getCurBackBufferIndex() == 0) ? SystemRtBufferType::BackBuffer_1 : SystemRtBufferType::BackBuffer_2;
		
		// �o�b�N�o�b�t�@�������_�[�^�[�Q�b�g��Ԃɂ���
		m_dX3DResource->beginWriteBackBuffer(getSystemHandle(curBackBufferType), m_commandList);

		// ���݂̃o�b�N�o�b�t�@�[����`���ɐݒ肷��
		m_dX3DResource->setBackBufferView(m_device, m_commandList, m_swapChain->getCurBackBufferIndex());

		// ���݂̃o�b�N�o�b�t�@�[���w�肵���P�F�œh��Ԃ�
		m_dX3DResource->clearRtv(getSystemHandle(SystemRtvDescriptorHeapType::BackBuffer), m_device, m_commandList, m_swapChain->getCurBackBufferIndex(), m_backGroundColor);
		
		// �S�Ẵf�v�X�X�e���V���r���[���N���A����
		m_dX3DResource->clearDsvAll(m_device, m_commandList);

		// �r���[�|�[�g��ݒ肷��
		m_dX3DResource->setViewport(getSystemHandle(SystemViewportType::Basic), m_commandList);
		
		// �V�U�[��`��ݒ肷��
		m_dX3DResource->setScissorRect(getSystemHandle(SystemScissorRectType::Basic), m_commandList);
	}

	void DX3DBaseObjects::endDraw()
	{
		// ���݂̃o�b�N�o�b�t�@�[�̎�ނ��um_curBackBufferIndex�v���狁�߂�
		auto curBackBufferType = (m_swapChain->getCurBackBufferIndex() == 0) ? SystemRtBufferType::BackBuffer_1 : SystemRtBufferType::BackBuffer_2;
		
		// �o�b�N�o�b�t�@���v���Z�b�g��Ԃɂ���
		m_dX3DResource->endWriteBackBuffer(getSystemHandle(curBackBufferType), m_commandList);

		// �R�}���h���X�g�����s����
		executeCommandList();

		// ��ʂ��t���b�v����
		m_swapChain->flipScreen();
	}

	size_t DX3DBaseObjects::createRootSignature(const RootSignatureInitParam& initParam)
	{
		return m_dX3DResource->createRootSignature(m_device, initParam);
	}

	size_t DX3DBaseObjects::createPipeLineState(const PipeLineStateInitParam& initParam, const ShaderFilePaths& shaderFilePath)
	{
		size_t handle = m_dX3DResource->createPipeLineState(m_device, initParam, shaderFilePath);

		// ����Z�b�g�i���ŏ��ɃZ�b�g�������̂ݏd���������ƂȂ�̂ŁA�쐬����ɐ�s�ŃZ�b�g����j
		m_dX3DResource->setPipeLineState(handle, m_commandList);

		return handle;
	}

	size_t DX3DBaseObjects::createUploadBuffer(const UploadBufferInitParam& initParam)
	{
		return m_dX3DResource->createUploadBuffer(m_device, initParam);
	}

	size_t DX3DBaseObjects::duplicateUploadBuffer(size_t originalHandle)
	{
		return m_dX3DResource->duplicateUploadBuffer(m_device, originalHandle);
	}

	size_t DX3DBaseObjects::createVertexBuffer(const VertexDataCarrier& vertexData)
	{
		return m_dX3DResource->createVertexBuffer(m_device, vertexData);
	}

	size_t DX3DBaseObjects::createIndexBuffer(const std::vector<unsigned short>& indices)
	{
		return m_dX3DResource->createIndexBuffer(m_device, indices);
	}

	size_t DX3DBaseObjects::createCBuffer(const CopySourceDataCarrier& constantBufferData)
	{
		return m_dX3DResource->createCBuffer(m_device, constantBufferData);
	}

	size_t DX3DBaseObjects::createRtBuffer(const tktkMath::Vector2& renderTargetSize, const tktkMath::Color& clearColor)
	{
		return m_dX3DResource->createRtBuffer(m_device, renderTargetSize, clearColor);
	}

	size_t DX3DBaseObjects::createDsBuffer(const DepthStencilBufferInitParam& initParam)
	{
		return m_dX3DResource->createDsBuffer(m_device, initParam);
	}

	size_t DX3DBaseObjects::createBasicDescriptorHeap(const BasicDescriptorHeapInitParam& initParam)
	{
		return m_dX3DResource->createBasicDescriptorHeap(m_device, initParam);
	}

	size_t DX3DBaseObjects::createRtvDescriptorHeap(const RtvDescriptorHeapInitParam& initParam)
	{
		return m_dX3DResource->createRtvDescriptorHeap(m_device, initParam);
	}

	size_t DX3DBaseObjects::createDsvDescriptorHeap(const DsvDescriptorHeapInitParam& initParam)
	{
		return m_dX3DResource->createDsvDescriptorHeap(m_device, initParam);
	}

	size_t DX3DBaseObjects::cpuPriorityCreateTextureBuffer(const TexBufFormatParam& formatParam, const TexBuffData& dataParam)
	{
		return m_dX3DResource->cpuPriorityCreateTextureBuffer(m_device, formatParam, dataParam);
	}

	size_t DX3DBaseObjects::gpuPriorityCreateTextureBuffer(const TexBufFormatParam& formatParam, const TexBuffData& dataParam)
	{
		return m_dX3DResource->gpuPriorityCreateTextureBuffer(m_device, m_commandList, formatParam, dataParam);
	}

	size_t DX3DBaseObjects::cpuPriorityLoadTextureBuffer(const std::string& texDataPath)
	{
		return m_dX3DResource->cpuPriorityLoadTextureBuffer(m_device, texDataPath);
	}

	size_t DX3DBaseObjects::gpuPriorityLoadTextureBuffer(const std::string& texDataPath)
	{
		return m_dX3DResource->gpuPriorityLoadTextureBuffer(m_device, m_commandList, texDataPath);
	}

	void DX3DBaseObjects::eraseViewport(size_t handle)
	{
		m_dX3DResource->eraseViewport(handle);
	}

	void DX3DBaseObjects::eraseScissorRect(size_t handle)
	{
		m_dX3DResource->eraseScissorRect(handle);
	}

	void DX3DBaseObjects::eraseRootSignature(size_t handle)
	{
		m_dX3DResource->eraseRootSignature(handle);
	}

	void DX3DBaseObjects::erasePipeLineState(size_t handle)
	{
		m_dX3DResource->erasePipeLineState(handle);
	}

	void DX3DBaseObjects::eraseUploadBuffer(size_t handle)
	{
		m_dX3DResource->eraseUploadBuffer(handle);
	}

	void DX3DBaseObjects::eraseVertexBuffer(size_t handle)
	{
		m_dX3DResource->eraseVertexBuffer(handle);
	}

	void DX3DBaseObjects::eraseIndexBuffer(size_t handle)
	{
		m_dX3DResource->eraseIndexBuffer(handle);
	}

	void DX3DBaseObjects::eraseCBuffer(size_t handle)
	{
		m_dX3DResource->eraseCBuffer(handle);
	}

	void DX3DBaseObjects::eraseTextureBuffer(size_t handle)
	{
		m_dX3DResource->eraseTextureBuffer(handle);
	}

	void DX3DBaseObjects::eraseDsBuffer(size_t handle)
	{
		m_dX3DResource->eraseDsBuffer(handle);
	}

	void DX3DBaseObjects::eraseRtBuffer(size_t handle)
	{
		m_dX3DResource->eraseRtBuffer(handle);
	}

	void DX3DBaseObjects::eraseBasicDescriptorHeap(size_t handle)
	{
		m_dX3DResource->eraseBasicDescriptorHeap(handle);
	}

	void DX3DBaseObjects::eraseRtvDescriptorHeap(size_t handle)
	{
		m_dX3DResource->eraseRtvDescriptorHeap(handle);
	}

	void DX3DBaseObjects::eraseDsvDescriptorHeap(size_t handle)
	{
		m_dX3DResource->eraseDsvDescriptorHeap(handle);
	}

	void DX3DBaseObjects::setBackGroundColor(const tktkMath::Color& backGroundColor)
	{
		m_backGroundColor = backGroundColor;
	}

	void DX3DBaseObjects::updateUploadBuffer(size_t handle, const CopySourceDataCarrier& bufferData)
	{
		m_dX3DResource->updateUploadBuffer(handle, bufferData);
	}

	void DX3DBaseObjects::copyBuffer(size_t handle) const
	{
		m_dX3DResource->copyBuffer(handle, m_commandList);
	}

	void DX3DBaseObjects::clearRtv(size_t handle, size_t rtvLocationIndex, const tktkMath::Color& color) const
	{
		m_dX3DResource->clearRtv(handle, m_device, m_commandList, rtvLocationIndex, color);
	}

	const tktkMath::Vector3& DX3DBaseObjects::getTextureBufferSizePx(size_t handle) const
	{
		return m_dX3DResource->getTextureBufferSizePx(handle);
	}

	const tktkMath::Vector2& DX3DBaseObjects::getDsBufferSizePx(size_t handle) const
	{
		return m_dX3DResource->getDsBufferSizePx(handle);
	}

	const tktkMath::Vector2& DX3DBaseObjects::getRtBufferSizePx(size_t handle) const
	{
		return m_dX3DResource->getRtBufferSizePx(handle);
	}

	void DX3DBaseObjects::setRtv(size_t rtvDescriptorHeapHandle, size_t startRtvLocationIndex, size_t rtvCount) const
	{
		m_dX3DResource->setRtv(rtvDescriptorHeapHandle, m_device, m_commandList, startRtvLocationIndex, rtvCount);
	}

	void DX3DBaseObjects::setRtvAndDsv(size_t rtvDescriptorHeapHandle, size_t dsvDescriptorHeapHandle, size_t startRtvLocationIndex, size_t rtvCount) const
	{
		m_dX3DResource->setRtvAndDsv(rtvDescriptorHeapHandle, dsvDescriptorHeapHandle, m_device, m_commandList, startRtvLocationIndex, rtvCount);
	}

	void DX3DBaseObjects::setOnlyDsv(size_t handle) const
	{
		m_dX3DResource->setOnlyDsv(handle, m_device, m_commandList);
	}

	void DX3DBaseObjects::setBackBufferView() const
	{
		m_dX3DResource->setBackBufferView(m_device, m_commandList, m_swapChain->getCurBackBufferIndex());
	}

	void DX3DBaseObjects::setBackBufferViewAndDsv(size_t dsvDescriptorHeapHandle) const
	{
		m_dX3DResource->setBackBufferViewAndDsv(dsvDescriptorHeapHandle, m_device, m_commandList, m_swapChain->getCurBackBufferIndex());
	}

	void DX3DBaseObjects::unSetRtv(size_t rtvDescriptorHeapHandle, size_t startRtvLocationIndex, size_t rtvCount) const
	{
		m_dX3DResource->unSetRtv(rtvDescriptorHeapHandle, m_commandList, startRtvLocationIndex, rtvCount);
	}

	void DX3DBaseObjects::unSetDsv(size_t dsvDescriptorHeapHandle) const
	{
		m_dX3DResource->unSetDsv(dsvDescriptorHeapHandle, m_commandList);
	}

	void DX3DBaseObjects::setViewport(size_t handle) const
	{
		m_dX3DResource->setViewport(handle, m_commandList);
	}

	void DX3DBaseObjects::setScissorRect(size_t handle) const
	{
		m_dX3DResource->setScissorRect(handle, m_commandList);
	}

	void DX3DBaseObjects::setPipeLineState(size_t handle) const
	{
		m_dX3DResource->setPipeLineState(handle, m_commandList);
	}

	void DX3DBaseObjects::setVertexBuffer(size_t handle) const
	{
		m_dX3DResource->setVertexBuffer(handle, m_commandList);
	}

	void DX3DBaseObjects::setIndexBuffer(size_t handle) const
	{
		m_dX3DResource->setIndexBuffer(handle, m_commandList);
	}

	void DX3DBaseObjects::setDescriptorHeap(const std::vector<DescriptorHeapParam>& heapParamArray) const
	{
		m_dX3DResource->setDescriptorHeap(m_device, m_commandList, heapParamArray);
	}

	void DX3DBaseObjects::setBlendFactor(const std::array<float, 4>& blendFactor) const
	{
		m_commandList->OMSetBlendFactor(blendFactor.data());
	}

	void DX3DBaseObjects::setPrimitiveTopology(D3D12_PRIMITIVE_TOPOLOGY topology) const
	{
		m_commandList->IASetPrimitiveTopology(topology);
	}

	void DX3DBaseObjects::drawInstanced(size_t vertexCountPerInstance, size_t instanceCount, size_t baseVertexLocation, size_t startInstanceLocation) const
	{
		m_commandList->DrawInstanced(
			static_cast<unsigned int>(vertexCountPerInstance),
			static_cast<unsigned int>(instanceCount),
			static_cast<unsigned int>(baseVertexLocation),
			static_cast<unsigned int>(startInstanceLocation)
		);
	}

	void DX3DBaseObjects::drawIndexedInstanced(size_t indexCountPerInstance, size_t instanceCount, size_t startIndexLocation, size_t baseVertexLocation, size_t startInstanceLocation) const
	{
		m_commandList->DrawIndexedInstanced(
			static_cast<unsigned int>(indexCountPerInstance),
			static_cast<unsigned int>(instanceCount),
			static_cast<unsigned int>(startIndexLocation),
			static_cast<unsigned int>(baseVertexLocation),
			static_cast<unsigned int>(startInstanceLocation)
		);
	}

	void DX3DBaseObjects::executeCommandList()
	{
		// �R�}���h���X�g�����
		m_commandList->Close();

		// �R�}���h���X�g�����s����
		ID3D12CommandList* commandLists[] = { m_commandList };
		m_commandQueue->ExecuteCommandLists(1, commandLists);

		// GPU�������I���܂ő҂�
		m_fence->waitGpuProcess(m_commandQueue);

		// �R�}���h�A���P�[�^�����Z�b�g����
		m_commandAllocator->Reset();

		// �R�}���h���X�g�����Z�b�g����
		m_commandList->Reset(m_commandAllocator, nullptr);
	}

	size_t DX3DBaseObjects::getSystemHandle(SystemViewportType type) const
	{
		return m_dX3DResource->getSystemHandle(type);
	}

	size_t DX3DBaseObjects::getSystemHandle(SystemScissorRectType type) const
	{
		return m_dX3DResource->getSystemHandle(type);
	}

	size_t DX3DBaseObjects::getSystemHandle(SystemVertexBufferType type) const
	{
		return m_dX3DResource->getSystemHandle(type);
	}

	size_t DX3DBaseObjects::getSystemHandle(SystemIndexBufferType type) const
	{
		return m_dX3DResource->getSystemHandle(type);
	}

	size_t DX3DBaseObjects::getSystemHandle(SystemCBufferType type) const
	{
		return m_dX3DResource->getSystemHandle(type);
	}

	size_t DX3DBaseObjects::getSystemHandle(SystemTextureBufferType type) const
	{
		return m_dX3DResource->getSystemHandle(type);
	}

	size_t DX3DBaseObjects::getSystemHandle(SystemRtBufferType type) const
	{
		return m_dX3DResource->getSystemHandle(type);
	}

	size_t DX3DBaseObjects::getSystemHandle(SystemDsBufferType type) const
	{
		return m_dX3DResource->getSystemHandle(type);
	}

	size_t DX3DBaseObjects::getSystemHandle(SystemBasicDescriptorHeapType type) const
	{
		return m_dX3DResource->getSystemHandle(type);
	}

	size_t DX3DBaseObjects::getSystemHandle(SystemRtvDescriptorHeapType type) const
	{
		return m_dX3DResource->getSystemHandle(type);
	}

	size_t DX3DBaseObjects::getSystemHandle(SystemDsvDescriptorHeapType type) const
	{
		return m_dX3DResource->getSystemHandle(type);
	}

	size_t DX3DBaseObjects::getSystemHandle(SystemRootSignatureType type) const
	{
		return m_dX3DResource->getSystemHandle(type);
	}

	size_t DX3DBaseObjects::getSystemHandle(SystemPipeLineStateType type) const
	{
		return m_dX3DResource->getSystemHandle(type);
	}

	void DX3DBaseObjects::setSystemHandle(SystemViewportType type, size_t handle)
	{
		m_dX3DResource->setSystemHandle(type, handle);
	}

	void DX3DBaseObjects::setSystemHandle(SystemScissorRectType type, size_t handle)
	{
		m_dX3DResource->setSystemHandle(type, handle);
	}

	void DX3DBaseObjects::setSystemHandle(SystemVertexBufferType type, size_t handle)
	{
		m_dX3DResource->setSystemHandle(type, handle);
	}

	void DX3DBaseObjects::setSystemHandle(SystemIndexBufferType type, size_t handle)
	{
		m_dX3DResource->setSystemHandle(type, handle);
	}

	void DX3DBaseObjects::setSystemHandle(SystemCBufferType type, size_t handle)
	{
		m_dX3DResource->setSystemHandle(type, handle);
	}

	void DX3DBaseObjects::setSystemHandle(SystemTextureBufferType type, size_t handle)
	{
		m_dX3DResource->setSystemHandle(type, handle);
	}

	void DX3DBaseObjects::setSystemHandle(SystemRtBufferType type, size_t handle)
	{
		m_dX3DResource->setSystemHandle(type, handle);
	}

	void DX3DBaseObjects::setSystemHandle(SystemDsBufferType type, size_t handle)
	{
		m_dX3DResource->setSystemHandle(type, handle);
	}

	void DX3DBaseObjects::setSystemHandle(SystemBasicDescriptorHeapType type, size_t handle)
	{
		m_dX3DResource->setSystemHandle(type, handle);
	}

	void DX3DBaseObjects::setSystemHandle(SystemRtvDescriptorHeapType type, size_t handle)
	{
		m_dX3DResource->setSystemHandle(type, handle);
	}

	void DX3DBaseObjects::setSystemHandle(SystemDsvDescriptorHeapType type, size_t handle)
	{
		m_dX3DResource->setSystemHandle(type, handle);
	}

	void DX3DBaseObjects::setSystemHandle(SystemRootSignatureType type, size_t handle)
	{
		m_dX3DResource->setSystemHandle(type, handle);
	}

	void DX3DBaseObjects::setSystemHandle(SystemPipeLineStateType type, size_t handle)
	{
		m_dX3DResource->setSystemHandle(type, handle);
	}
}