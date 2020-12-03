#ifndef VERTEX_DATA_CARRIER_H_
#define VERTEX_DATA_CARRIER_H_

#include <vector>

namespace tktk
{
	// ���_�f�[�^���i�[����\����
	struct VertexDataCarrier
	{
	public:

		template <class VertexDataType>
		VertexDataCarrier(const std::vector<VertexDataType>& vertexDataArray)
			: typeSize(sizeof(VertexDataType))
			, dataCount(vertexDataArray.size())
			, dataTopPos(vertexDataArray.data()) {}

		// �e���v���[�g���g�p��
		VertexDataCarrier(size_t typeSize, size_t dataCount, const void* dataTopPos)
			: typeSize(typeSize)
			, dataCount(dataCount)
			, dataTopPos(dataTopPos) {}

	public:

		size_t		typeSize{ 0U };

		size_t		dataCount{ 0U };

		const void* dataTopPos{ nullptr };
	};
}
#endif // !VERTEX_DATA_CARRIER_H_