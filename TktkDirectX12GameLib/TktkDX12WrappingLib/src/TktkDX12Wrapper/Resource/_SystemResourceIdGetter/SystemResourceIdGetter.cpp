#include "TktkDX12Wrapper/Resource/_SystemResourceIdGetter/SystemResourceIdGetter.h"

namespace tktk
{
	SystemResourceIdGetter::SystemResourceIdGetter(DX3DResourceInitParam* initParam)
		: m_basicResourceNum(*initParam)
	{
		initParam->viewPortNum										+= SystemViewportNum;
		initParam->scissorRectNum									+= SystemScissorRectNum;
		initParam->bufferResourceNum.vertexBufferNum			+= SystemVertexBufferNum;
		initParam->bufferResourceNum.indexBufferNum			+= SystemIndexBufferNum;
		initParam->bufferResourceNum.constantBufferNum		+= SystemCBufferNum;
		initParam->bufferResourceNum.textureBufferNum			+= SystemTextureBufferNum;
		initParam->bufferResourceNum.renderTargetBufferNum	+= SystemRtBufferNum;
		initParam->bufferResourceNum.depthStencilBufferNum	+= SystemDsBufferNum;
		initParam->descriptorHeapNum.basicDescriptorHeapNum	+= SystemBasicDescriptorHeapNum;
		initParam->descriptorHeapNum.rtvDescriptorHeapNum		+= SystemRtvDescriptorHeapNum;
		initParam->descriptorHeapNum.dsvDescriptorHeapNum		+= SystemDsvDescriptorHeapNum;
		initParam->rootSignatureNum									+= SystemRootSignatureNum;
		initParam->pipeLineStateNum									+= SystemPipeLineStateNum;
	}

	unsigned int SystemResourceIdGetter::getSystemId(SystemViewportType type) const
	{
		return m_basicResourceNum.viewPortNum + static_cast<unsigned int>(type);
	}

	unsigned int SystemResourceIdGetter::getSystemId(SystemScissorRectType type) const
	{
		return  m_basicResourceNum.scissorRectNum + static_cast<unsigned int>(type);
	}

	unsigned int SystemResourceIdGetter::getSystemId(SystemVertexBufferType type) const
	{
		return  m_basicResourceNum.bufferResourceNum.vertexBufferNum + static_cast<unsigned int>(type);
	}

	unsigned int SystemResourceIdGetter::getSystemId(SystemIndexBufferType type) const
	{
		return  m_basicResourceNum.bufferResourceNum.indexBufferNum + static_cast<unsigned int>(type);
	}

	unsigned int SystemResourceIdGetter::getSystemId(SystemCBufferType type) const
	{
		return m_basicResourceNum.bufferResourceNum.constantBufferNum + static_cast<unsigned int>(type);
	}

	unsigned int SystemResourceIdGetter::getSystemId(SystemTextureBufferType type) const
	{
		return m_basicResourceNum.bufferResourceNum.textureBufferNum + static_cast<unsigned int>(type);
	}

	unsigned int SystemResourceIdGetter::getSystemId(SystemRtBufferType type) const
	{
		return m_basicResourceNum.bufferResourceNum.renderTargetBufferNum + static_cast<unsigned int>(type);
	}

	unsigned int SystemResourceIdGetter::getSystemId(SystemDsBufferType type) const
	{
		return  m_basicResourceNum.bufferResourceNum.depthStencilBufferNum + static_cast<unsigned int>(type);
	}

	unsigned int SystemResourceIdGetter::getSystemId(SystemBasicDescriptorHeapType type) const
	{
		return m_basicResourceNum.descriptorHeapNum.basicDescriptorHeapNum + static_cast<unsigned int>(type);
	}

	unsigned int SystemResourceIdGetter::getSystemId(SystemRtvDescriptorHeapType type) const
	{
		return m_basicResourceNum.descriptorHeapNum.rtvDescriptorHeapNum + static_cast<unsigned int>(type);
	}

	unsigned int SystemResourceIdGetter::getSystemId(SystemDsvDescriptorHeapType type) const
	{
		return m_basicResourceNum.descriptorHeapNum.dsvDescriptorHeapNum + static_cast<unsigned int>(type);
	}

	unsigned int SystemResourceIdGetter::getSystemId(SystemRootSignatureType type) const
	{
		return  m_basicResourceNum.rootSignatureNum + static_cast<unsigned int>(type);
	}

	unsigned int SystemResourceIdGetter::getSystemId(SystemPipeLineStateType type) const
	{
		return  m_basicResourceNum.pipeLineStateNum + static_cast<unsigned int>(type);
	}
}