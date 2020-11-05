#ifndef COPY_SOURCE_DATA_CARRIER_H_
#define COPY_SOURCE_DATA_CARRIER_H_

namespace tktk
{
	// 「memcpy」などでコピーするデータの情報を格納する構造体
	struct CopySourceDataCarrier
	{
	public:

		template <class SourceType>
		CopySourceDataCarrier(const SourceType& sourceData)
			: dataSize(sizeof(SourceType))
			, dataTopPos(&sourceData) {}

		// 応急的 ※「11/06中に消す」
		CopySourceDataCarrier(size_t dataSize, const void* dataTopPos)
			: dataSize(dataSize)
			, dataTopPos(dataTopPos) {}

	public:

		size_t		dataSize	{ 0U };

		const void*	dataTopPos	{ nullptr };
	};
}
#endif // !COPY_SOURCE_DATA_CARRIER_H_