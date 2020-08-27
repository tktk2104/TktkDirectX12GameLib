#ifndef SPRITE_MATERIAL_H_
#define SPRITE_MATERIAL_H_

#include <TktkContainer/ResourceContainer/ResourceContainer.h>
#include <TktkDX12Wrapper/Resource/GraphicsPipeLine/PipeLineState/PipeLineStateInitParam.h>
#include "SpriteMaterialData.h"

namespace tktk
{
	// �uSpriteMaterialData�v���Ǘ�����N���X
	class SpriteMaterial
	{
	public:

		SpriteMaterial(const ShaderFilePaths& shaderFilePaths, const tktkContainer::ResourceContainerInitParam& initParam);
		~SpriteMaterial() = default;

	public:

		// �uSpriteMaterialData�v�̃C���X�^���X�����A���̃��\�[�X�̃n���h����Ԃ�
		unsigned int create(const SpriteMaterialInitParam& initParam);

		// �w�肵���X�v���C�g��`�悷��
		void drawSprite(unsigned int handle, const SpriteMaterialDrawFuncArgs& drawFuncArgs) const;

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