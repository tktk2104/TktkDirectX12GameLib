#include "ResourceHandleCarrier.h"

unsigned int ResourceHandleCarrier::m_postEffectRtvDescriptorHeapHandle;

unsigned int ResourceHandleCarrier::m_vertexColorPolygonCbufferHandle;
unsigned int ResourceHandleCarrier::m_vertexColorPolygonBasicDescriptorHeapHandle;
unsigned int ResourceHandleCarrier::m_vertexColorPolygonRootSignatureHandle;
unsigned int ResourceHandleCarrier::m_vertexColorPolygonPipeLineStateHandle;

unsigned int ResourceHandleCarrier::getPostEffectRtvDescriptorHeapHandle()
{
    return m_postEffectRtvDescriptorHeapHandle;
}

unsigned int ResourceHandleCarrier::getVertexColorPolygonCbufferHandle()
{
    return m_vertexColorPolygonCbufferHandle;
}

unsigned int ResourceHandleCarrier::getVertexColorPolygonBasicDescriptorHeapHandle()
{
    return m_vertexColorPolygonBasicDescriptorHeapHandle;
}

unsigned int ResourceHandleCarrier::getVertexColorPolygonRootSignatureHandle()
{
    return m_vertexColorPolygonRootSignatureHandle;
}

unsigned int ResourceHandleCarrier::getVertexColorPolygonPipeLineStateHandle()
{
    return m_vertexColorPolygonPipeLineStateHandle;
}

void ResourceHandleCarrier::setPostEffectRtvDescriptorHeapHandle(unsigned int handle)
{
    m_postEffectRtvDescriptorHeapHandle = handle;
}

void ResourceHandleCarrier::setVertexColorPolygonCbufferHandle(unsigned int handle)
{
    m_vertexColorPolygonCbufferHandle = handle;
}

void ResourceHandleCarrier::setVertexColorPolygonBasicDescriptorHeapHandle(unsigned int handle)
{
    m_vertexColorPolygonBasicDescriptorHeapHandle = handle;
}

void ResourceHandleCarrier::setVertexColorPolygonRootSignatureHandle(unsigned int handle)
{
    m_vertexColorPolygonRootSignatureHandle = handle;
}

void ResourceHandleCarrier::setVertexColorPolygonPipeLineStateHandle(unsigned int handle)
{
    m_vertexColorPolygonPipeLineStateHandle = handle;
}
