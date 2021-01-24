#ifndef SPRITE_MATERIAL_DATA_H_
#define SPRITE_MATERIAL_DATA_H_

/* class member */
#include <map>
#include <TktkMath/Structs/Vector2.h>
#include "Structs/TempSpriteMaterialInstanceData.h"
#include "Structs/SpriteMaterialInstanceData.h"

namespace tktk
{
	struct SpriteMaterialInitParam;
	struct SpriteMaterialDrawFuncArgs;

	// �X�v���C�g�̃}�e���A�����Ǘ�����N���X
	class SpriteMaterialData
	{
	public:

		explicit SpriteMaterialData(const SpriteMaterialInitParam& initParam);
		~SpriteMaterialData();

		// ���[�u�R���X�g���N�^
		SpriteMaterialData(SpriteMaterialData&& other) noexcept;

	public:

		// �X�v���C�g���g�p����e�N�X�`���̃T�C�Y���擾����
		const tktkMath::Vector2& getSpriteTextureSize() const;

		// �ő�̃C���X�^���X�����擾����
		size_t getMaxInstanceCount() const;

		// ���݂̃C���X�^���X�����擾����
		size_t getCurInstanceCount() const;

		// �X�v���C�g���C���X�^���X�`�悷�鎞�Ɏg�p����l���폜����
		void clearInstanceParam();

		// �X�v���C�g���C���X�^���X�`�悷�鎞�Ɏg�p����l��ǉ�����
		void addInstanceParam(float drawPriority, const TempSpriteMaterialInstanceData& instanceParam);

		// �X�v���C�g���C���X�^���X�`�悷�鎞�Ɏg�p����l�𒸓_�o�b�t�@�ɏ�������
		void updateInstanceParam();

		// �X�v���C�g��`�悷��
		void draw(const SpriteMaterialDrawFuncArgs& drawFuncArgs) const;

	private:

		// ������X�v���C�g�̃f�B�X�N���v�^�q�[�v�̃n���h��
		size_t m_createDescriptorHeapHandle			{ 0U };

		// �C���X�^���X�����������_�o�b�t�@�̃n���h��
		size_t m_instanceParamVertexBufferHandle	{ 0U };

		// �C���X�^���X�����������_�o�b�t�@���X�V����o�b�t�@�̃n���h��
		size_t m_instanceParamUplaodBufferHandle	{ 0U };

		// �e�N�X�`���T�C�Y
		tktkMath::Vector2 m_textureSize;

		// �C���X�^���X�`�悷�鎞�̍ő�C���X�^���X��
		size_t m_maxInstanceCount;

		// ��x�ɕ`�悷��C���X�^���X��
		size_t m_instanceCount{ 0U };

		// �C���X�^���X���̘A�z�z��
		std::multimap<float, SpriteMaterialInstanceData>	m_instanceParamList;
	};
}
#endif // !SPRITE_MATERIAL_DATA_H_