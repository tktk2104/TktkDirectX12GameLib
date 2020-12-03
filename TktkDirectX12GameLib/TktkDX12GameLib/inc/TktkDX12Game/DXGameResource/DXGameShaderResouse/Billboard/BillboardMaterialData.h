#ifndef BILLBOARD_MATERIAL_DATA_H_
#define BILLBOARD_MATERIAL_DATA_H_

/* class member */
#include <forward_list>
#include <TktkMath/Structs/Vector2.h>
#include "BillboardMaterialInstanceVertData.h"

namespace tktk
{
	/* funcUseType */
	struct BillboardMaterialInitParam;
	struct BillboardDrawFuncBaseArgs;

	// �r���{�[�h�}�e���A���̏��������N���X
	class BillboardMaterialData
	{
	public:

		explicit BillboardMaterialData(const BillboardMaterialInitParam& initParam);
		~BillboardMaterialData();

		// ���[�u�R���X�g���N�^
		BillboardMaterialData(BillboardMaterialData&& other) noexcept;

	public:

		// �r���{�[�h�e�N�X�`���̃T�C�Y���擾����
		const tktkMath::Vector2& getBillboardTextureSize() const;

		// �r���{�[�h���C���X�^���X�`�悷�鎞�Ɏg�p����l���폜����
		void clearInstanceParam();

		// �r���{�[�h���C���X�^���X�`�悷�鎞�Ɏg�p����l��ǉ�����
		void addInstanceVertParam(const BillboardMaterialInstanceVertData& instanceParam);

		// �C���X�^���X�`������������_�o�b�t�@���X�V����
		void updateInstanceParamVertBuffer() const;

		// �r���{�[�h��`�悷��
		void draw(const BillboardDrawFuncBaseArgs& drawFuncArgs) const;

	private:

		// ������r���{�[�h�̃f�B�X�N���v�^�q�[�v�̃n���h��
		size_t m_createDescriptorHeapHandle	{ 0U };
		
		// �C���X�^���X�����������_�o�b�t�@�̃n���h��
		size_t m_instanceParamVertexBufferHandle{ 0U };

		// �e�N�X�`���T�C�Y
		tktkMath::Vector2 m_textureSize;

		// �C���X�^���X�`�悷�鎞�̍ő�C���X�^���X��
		size_t m_maxInstanceCount;

		// ��x�ɕ`�悷��C���X�^���X��
		size_t m_instanceCount				{ 0U };

		// ���Z�u�����h���s�����H
		bool m_isEffect;

		// �C���X�^���X���̔z��
		std::forward_list<BillboardMaterialInstanceVertData>	m_instanceVertParamList;
	};
}
#endif // !BILLBOARD_MATERIAL_DATA_H_