#ifndef SUBSET_H_
#define SUBSET_H_

namespace tktk
{
	// �T�u�Z�b�g�i�g�p����}�e���A�����j
	struct Subset
	{
	public:

		// �g�p����}�e���A����ID
		size_t useMaterialHandle;

		// �C���f�b�N�X�o�b�t�@�̎g�p�J�n�ʒu
		size_t indexBufferStartPos;

		// �C���f�b�N�X�o�b�t�@�̎g�p��
		size_t indexBufferUseCount;
	};
}
#endif // !SUBSET_H_