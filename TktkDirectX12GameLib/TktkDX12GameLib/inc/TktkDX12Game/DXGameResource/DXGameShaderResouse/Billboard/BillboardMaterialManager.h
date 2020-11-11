#ifndef BILLBOARD_MATERIAL_H_
#define BILLBOARD_MATERIAL_H_

/* tktkContainer::ResourceContainer */
#include <TktkContainer/ResourceContainer/ResourceContainer.h>

namespace tktk
{
	struct BillboardMaterialManagerInitParam;
	struct ShaderFilePaths;
	class BillboardMaterialData;
	struct BillboardMaterialInitParam;
	struct BillboardDrawFuncBaseArgs;
	struct BillboardCbufferUpdateFuncArgs;
	struct BillboardClippingParam;

	// �uBillboardMaterialData�v���Ǘ�����N���X
	class BillboardMaterialManager
	{
	public:

		BillboardMaterialManager(const BillboardMaterialManagerInitParam& initParam);
		~BillboardMaterialManager();

	public:

		// �uBillboardMaterialData�v�̃C���X�^���X�����A���̃��\�[�X�̃n���h����Ԃ�
		size_t create(const BillboardMaterialInitParam& initParam);

		// �w�肵���r���{�[�h��`�悷��
		void drawBillboard(size_t handle, const BillboardDrawFuncBaseArgs& drawFuncArgs) const;

		// �������\���R�s�[�o�b�t�@���g���č��W�ϊ������Ǘ�����萔�o�b�t�@���X�V����
		void updateTransformCbuffer(size_t handle, size_t copyBufferHandle, const BillboardCbufferUpdateFuncArgs& updateArgs) const;

		// �������\���R�s�[�o�b�t�@���g���č��W�ϊ������Ǘ�����萔�o�b�t�@���X�V����i�؂蔲���͈͎w��Łj
		void updateTransformCbufferUseClippingParam(size_t handle, size_t copyBufferHandle, const BillboardCbufferUpdateFuncArgs& updateArgs, const BillboardClippingParam& clippingParam) const;

	private:

		// �r���{�[�h�`��p�̃��[�g�V�O�l�`�������
		void createRootSignature() const;

		// �r���{�[�h�`��p�̃p�C�v���C���X�e�[�g�����
		void createGraphicsPipeLineState(const ShaderFilePaths & shaderFilePaths) const;

	private:

		tktkContainer::ResourceContainer<BillboardMaterialData> m_billboardMaterialArray;
	};
}
#endif // !BILLBOARD_MATERIAL_H_