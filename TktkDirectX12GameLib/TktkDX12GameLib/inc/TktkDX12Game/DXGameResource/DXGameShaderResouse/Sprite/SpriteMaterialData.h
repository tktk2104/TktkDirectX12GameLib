#ifndef SPRITE_MATERIAL_DATA_H_
#define SPRITE_MATERIAL_DATA_H_

/* class member */
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector2.h>

namespace tktk
{
	struct SpriteMaterialInitParam;
	struct SpriteMaterialDrawFuncArgs;
	struct SpriteCbufferUpdateFuncArgs;
	struct SpriteClippingParam;

	// �X�v���C�g�̃}�e���A�����Ǘ�����N���X
	class SpriteMaterialData
	{
	public:

		explicit SpriteMaterialData(const SpriteMaterialInitParam& initParam);
		~SpriteMaterialData();

		// ���[�u�R���X�g���N�^
		SpriteMaterialData(SpriteMaterialData&& other) noexcept;

	public:

		// �X�v���C�g��`�悷��
		void drawSprite(const SpriteMaterialDrawFuncArgs& drawFuncArgs) const;

		// �������\���R�s�[�o�b�t�@���g���č��W�ϊ������Ǘ�����萔�o�b�t�@���X�V����
		void updateTransformCbuffer(size_t copyBufferHandle, const SpriteCbufferUpdateFuncArgs& cbufferUpdateArgs) const;

		// �������\���R�s�[�o�b�t�@���g���č��W�ϊ������Ǘ�����萔�o�b�t�@���X�V����i�؂蔲���͈͎w��Łj
		void updateTransformCbufferUseClippingParam(size_t copyBufferHandle, const SpriteCbufferUpdateFuncArgs& cbufferUpdateArgs, const SpriteClippingParam& clippingParam) const;

	private:

		// �萔�o�b�t�@�̃R�s�[�p�o�b�t�@���X�V����
		void updateCopyBuffer() const;

	private:

		size_t				m_createDescriptorHeapHandle { 0U };
		size_t				m_createUploadBufferHandle{ 0U };
		tktkMath::Color		m_blendRate;
		tktkMath::Vector2	m_textureUvOffset;
		tktkMath::Vector2	m_textureUvMulRate;
		tktkMath::Vector2	m_textureSize;
	};
}
#endif // !SPRITE_MATERIAL_DATA_H_