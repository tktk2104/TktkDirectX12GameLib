#ifndef BILLBOARD_MATERIAL_INIT_PARAM_H_
#define BILLBOARD_MATERIAL_INIT_PARAM_H_

#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector2.h>
#include <TktkDX12Wrapper/Resource/Buffer/BufferType.h>

namespace tktk
{
	struct BillboardMaterialInitParam
	{
		// �`�悷��o�b�t�@�[�̎��
		BufferType			srvBufferType;

		// �`�悷��o�b�t�@�[��ID
		unsigned int		useBufferHandle;

		// �e�N�X�`��UV�̃I�t�Z�b�g
		tktkMath::Vector2	textureUvOffset{ 0.0f, 0.0f };

		// �e�N�X�`��UV�ɏ�Z����l
		tktkMath::Vector2	textureUvMulRate{ 1.0f, 1.0f };
	};
}
#endif // !BILLBOARD_MATERIAL_INIT_PARAM_H_
