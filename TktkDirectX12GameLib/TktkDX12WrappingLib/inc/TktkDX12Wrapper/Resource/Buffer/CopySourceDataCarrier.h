#ifndef COPY_SOURCE_DATA_CARRIER_H_
#define COPY_SOURCE_DATA_CARRIER_H_

namespace tktk
{
	// �umemcpy�v�ȂǂŃR�s�[����f�[�^�̏����i�[����\����
	struct CopySourceDataCarrier
	{
	public:

		template <class SourceType>
		CopySourceDataCarrier(const SourceType& sourceData)
			: dataSize(sizeof(SourceType))
			, dataTopPos(&sourceData) {}

		// ���}�I ���u11/06���ɏ����v
		CopySourceDataCarrier(size_t dataSize, const void* dataTopPos)
			: dataSize(dataSize)
			, dataTopPos(dataTopPos) {}

	public:

		size_t		dataSize	{ 0U };

		const void*	dataTopPos	{ nullptr };
	};
}
#endif // !COPY_SOURCE_DATA_CARRIER_H_