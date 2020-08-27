#ifndef SPRITE_MATERIAL_DATA_H_
#define SPRITE_MATERIAL_DATA_H_

#include <TktkMath/Structs/Matrix3.h>
#include "SpriteMaterialInitParam.h"
#include "SpriteMaterialDrawFuncArgs.h"

namespace tktk
{
	// �X�v���C�g�̃}�e���A�����Ǘ�����N���X
	class SpriteMaterialData
	{
	public:

		explicit SpriteMaterialData(const SpriteMaterialInitParam& initParam);
		~SpriteMaterialData() = default;

		// ���[�u�R���X�g���N�^
		SpriteMaterialData(SpriteMaterialData&& other) noexcept;

	public:

		// �X�v���C�g��`�悷��
		void drawSprite(const SpriteMaterialDrawFuncArgs& drawFuncArgs) const;

	private:

		// �X�v���C�g�p�̒萔�o�b�t�@���X�V����
		void updateSpriteConstantBuffer(const tktkMath::Matrix3& worldMatrix) const;

	private:

		unsigned int		m_createDescriptorHeapHandle { 0U };
		tktkMath::Color		m_blendRate;
		tktkMath::Vector2	m_textureUvOffset;
		tktkMath::Vector2	m_textureUvMulRate;
		tktkMath::Vector2	m_textureSize;
		tktkMath::Vector2	m_spriteCenterRate;
	};
}
#endif // !SPRITE_MATERIAL_DATA_H_