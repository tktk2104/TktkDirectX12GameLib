#ifndef SPRITE_MATERIAL_H_
#define SPRITE_MATERIAL_H_

/* use func type */
#include <TktkMath/Structs/Vector2.h>

/* tktkContainer::ResourceContainer */
#include <TktkContainer/ResourceContainer/ResourceContainer.h>

namespace tktk
{
	class SpriteMaterialData;

	struct SpriteMaterialManagerInitParam;
	struct SpriteMaterialInitParam;
	struct SpriteMaterialDrawFuncArgs;
	struct TempSpriteMaterialInstanceData;

	// �uSpriteMaterialData�v���Ǘ�����N���X
	class SpriteMaterialManager
	{
	public:

		explicit SpriteMaterialManager(const SpriteMaterialManagerInitParam& initParam);
		~SpriteMaterialManager();

	public:

		// �uSpriteMaterialData�v�̃C���X�^���X�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t create(const SpriteMaterialInitParam& initParam);

		// �w�肵���X�v���C�g���g�p����e�N�X�`���̃T�C�Y���擾����
		const tktkMath::Vector2& getSpriteTextureSize(size_t handle) const;

		// �w�肵���X�v���C�g�̍ő�̃C���X�^���X�����擾����
		size_t getMaxInstanceCount(size_t handle) const;

		// �w�肵���X�v���C�g�̌��݂̃C���X�^���X�����擾����
		size_t getCurInstanceCount(size_t handle) const;

		// �w�肵���X�v���C�g���C���X�^���X�`�悷�鎞�Ɏg�p����l���폜����
		void clearInstanceParam(size_t handle);

		// �w�肵���X�v���C�g���C���X�^���X�`�悷�鎞�Ɏg�p����l��ǉ�����
		void addInstanceParam(size_t handle, float drawPriority, const TempSpriteMaterialInstanceData& instanceParam);

		// �w�肵�X�v���C�g���C���X�^���X�`�悷�鎞�Ɏg�p����l�𒸓_�o�b�t�@�ɏ�������
		void updateInstanceParam(size_t handle);

		// �w�肵���X�v���C�g��`�悷��
		void draw(size_t handle, const SpriteMaterialDrawFuncArgs& drawFuncArgs) const;

	private:

		tktkContainer::ResourceContainer<SpriteMaterialData> m_spriteMaterialArray;
	};
}
#endif // !SPRITE_MATERIAL_H_