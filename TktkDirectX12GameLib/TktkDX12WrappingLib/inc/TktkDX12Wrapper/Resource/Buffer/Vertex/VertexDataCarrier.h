#ifndef VERTEX_DATA_CARRIER_H_
#define VERTEX_DATA_CARRIER_H_

#include <vector>

namespace tktk
{
	// 頂点データを格納する構造体
	struct VertexDataCarrier
	{
	public:

		template <class VertexDataType>
		VertexDataCarrier(const std::vector<VertexDataType>& vertexDataArray)
			: typeSize(sizeof(VertexDataType))
			, dataCount(vertexDataArray.size())
			, dataTopPos(vertexDataArray.data()) {}

	public:

		size_t		typeSize{ 0U };

		size_t		dataCount{ 0U };

		const void* dataTopPos{ nullptr };
	};
}
#endif // !VERTEX_DATA_CARRIER_H_
