#ifndef RESOURCE_HANDLE_CARRIER_H_
#define RESOURCE_HANDLE_CARRIER_H_

class ResourceHandleCarrier
{
public:

	static unsigned int getPostEffectRtvDescriptorHeapHandle();

	static unsigned int getVertexColorPolygonCbufferHandle();
	static unsigned int getVertexColorPolygonBasicDescriptorHeapHandle();
	static unsigned int getVertexColorPolygonRootSignatureHandle();
	static unsigned int getVertexColorPolygonPipeLineStateHandle();

public:

	static void setPostEffectRtvDescriptorHeapHandle(unsigned int handle);

	static void setVertexColorPolygonCbufferHandle(unsigned int handle);
	static void setVertexColorPolygonBasicDescriptorHeapHandle(unsigned int handle);
	static void setVertexColorPolygonRootSignatureHandle(unsigned int handle);
	static void setVertexColorPolygonPipeLineStateHandle(unsigned int handle);

private:

	static unsigned int m_postEffectRtvDescriptorHeapHandle;

	static unsigned int m_vertexColorPolygonCbufferHandle;
	static unsigned int m_vertexColorPolygonBasicDescriptorHeapHandle;
	static unsigned int m_vertexColorPolygonRootSignatureHandle;
	static unsigned int m_vertexColorPolygonPipeLineStateHandle;
};

#endif // !RESOURCE_HANDLE_CARRIER_H_
