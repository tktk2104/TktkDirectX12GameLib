#ifndef BILLBOARD_MATERIAL_H_
#define BILLBOARD_MATERIAL_H_

/* tktkContainer::ResourceContainer */
#include <TktkMath/Structs/Vector2.h>
#include <TktkContainer/ResourceContainer/ResourceContainer.h>

namespace tktk
{
	class BillboardMaterialData;

	struct BillboardMaterialManagerInitParam;
	struct BillboardMaterialInitParam;
	struct BillboardDrawFuncBaseArgs;
	struct BillboardMaterialInstanceVertData;

	// �uBillboardMaterialData�v���Ǘ�����N���X
	class BillboardMaterialManager
	{
	public:

		BillboardMaterialManager(const BillboardMaterialManagerInitParam& initParam);
		~BillboardMaterialManager();

	public:

		// �uBillboardMaterialData�v�̃C���X�^���X�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t create(const BillboardMaterialInitParam& initParam);

		// �w�肵���r���{�[�h���g�p����e�N�X�`���̃T�C�Y���擾����
		const tktkMath::Vector2& getBillboardTextureSize(size_t handle) const;

		// �w�肵���r���{�[�h���C���X�^���X�`�悷�鎞�Ɏg�p����l���폜����
		void clearInstanceParam(size_t handle);

		// �w�肵���r���{�[�h���C���X�^���X�`�悷�鎞�Ɏg�p����l��ǉ�����
		void addInstanceVertParam(size_t handle, const BillboardMaterialInstanceVertData& instanceParam);

		// �w�肵���r���{�[�h��`�悷��
		void draw(size_t handle, const BillboardDrawFuncBaseArgs& drawFuncArgs) const;

	private:

		tktkContainer::ResourceContainer<BillboardMaterialData> m_billboardMaterialArray;
	};
}
#endif // !BILLBOARD_MATERIAL_H_