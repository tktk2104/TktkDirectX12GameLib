#ifndef BILLBOARD_MATERIAL_INIT_PARAM_H_
#define BILLBOARD_MATERIAL_INIT_PARAM_H_

/* class member */
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector2.h>
#include <TktkDX12Wrapper/Resource/Buffer/BufferType.h>

namespace tktk
{
	// �r���{�[�h�}�e���A���̍쐬�ɕK�v�ȕϐ�
	struct BillboardMaterialInitParam
	{
		// �`�悷��o�b�t�@�[�̎��
		BufferType			srvBufferType;

		// �`�悷��o�b�t�@�[��ID
		size_t				useBufferHandle;

		// �`��ł���ő�C���X�^���X��
		size_t				maxInstanceCount;

		// ���Z�u�����h���s�����H
		bool				isEffect;
	};
}
#endif // !BILLBOARD_MATERIAL_INIT_PARAM_H_
