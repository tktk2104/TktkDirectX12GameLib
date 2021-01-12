#ifndef COPY_SOURCE_DATA_CARRIER_H_
#define COPY_SOURCE_DATA_CARRIER_H_

namespace tktk
{
	// �umemcpy�v�ȂǂŃR�s�[����f�[�^�̏����i�[����\����
	struct CopySourceDataCarrier
	{
	public:

		template <class SourceType>
		CopySourceDataCarrier(const SourceType& sourceData, size_t dataOffset)
			: dataSize(sizeof(SourceType))
			, dataTopPos(&sourceData)
			, dataOffset(dataOffset){}

		// �e���v���[�g���g�p��
		CopySourceDataCarrier(size_t dataSize, const void* dataTopPos, size_t dataOffset)
			: dataSize(dataSize)
			, dataTopPos(dataTopPos)
			, dataOffset(dataOffset) {}

	public:

		size_t		dataSize	{ 0U };

		const void*	dataTopPos	{ nullptr };

		size_t		dataOffset	{ 0U };
	};
}
#endif // !COPY_SOURCE_DATA_CARRIER_H_