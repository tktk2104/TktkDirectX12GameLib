#ifndef SPRITE_MATERIAL_H_
#define SPRITE_MATERIAL_H_

/* class member */
#include <TktkMath/Structs/Vector2.h>

/* tktkContainer::ResourceContainer */
#include <TktkContainer/ResourceContainer/ResourceContainer.h>

namespace tktk
{
	struct SpriteMaterialManagerInitParam;
	struct ShaderFilePaths;
	class SpriteMaterialData;
	struct SpriteMaterialInitParam;
	struct SpriteMaterialDrawFuncArgs;
	struct SpriteCBufferUpdateFuncArgs;
	struct SpriteClippingParam;

	// �uSpriteMaterialData�v���Ǘ�����N���X
	class SpriteMaterialManager
	{
	public:

		SpriteMaterialManager(const SpriteMaterialManagerInitParam& initParam);
		~SpriteMaterialManager();

	public:

		// �uSpriteMaterialData�v�̃C���X�^���X�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t create(const SpriteMaterialInitParam& initParam);

		// �w�肵���X�v���C�g���g�p����e�N�X�`���̃T�C�Y���擾����
		const tktkMath::Vector2& getSpriteTextureSize(size_t handle) const;

		// �w�肵���X�v���C�g��`�悷��
		void drawSprite(size_t handle, const SpriteMaterialDrawFuncArgs& drawFuncArgs) const;

		// �������\���R�s�[�o�b�t�@���g���č��W�ϊ������Ǘ�����萔�o�b�t�@���X�V����
		void updateTransformCbuffer(size_t handle, size_t copyBufferHandle, const SpriteCBufferUpdateFuncArgs& cbufferUpdateArgs) const;

		// �������\���R�s�[�o�b�t�@���g���č��W�ϊ������Ǘ�����萔�o�b�t�@���X�V����i�؂蔲���͈͎w��Łj
		void updateTransformCbufferUseClippingParam(size_t handle, size_t copyBufferHandle, const SpriteCBufferUpdateFuncArgs& cbufferUpdateArgs, const SpriteClippingParam& clippingParam) const;

	private:

		// �X�v���C�g�`��p�̃��[�g�V�O�l�`�������
		void createRootSignature() const;

		// �X�v���C�g�`��p�̃p�C�v���C���X�e�[�g�����
		void createGraphicsPipeLineState(const ShaderFilePaths& shaderFilePaths) const;

	private:

		tktkContainer::ResourceContainer<SpriteMaterialData> m_spriteMaterialArray;
	};
}
#endif // !SPRITE_MATERIAL_H_