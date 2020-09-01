#ifndef SYSTEM_INDEX_BUFFER_TYPE_H_
#define SYSTEM_INDEX_BUFFER_TYPE_H_

namespace tktk
{
	// �V�X�e���Ŏg�p���Ă���C���f�b�N�X�o�b�t�@�̐�
	constexpr unsigned int SystemIndexBufferNum = 2U;

	// �V�X�e���Ŏg�p���Ă���C���f�b�N�X�o�b�t�@�̎��
	enum class SystemIndexBufferType
	{
		Sprite = 0U,
		Sphere
	};
}
#endif // !SYSTEM_INDEX_BUFFER_TYPE_H_