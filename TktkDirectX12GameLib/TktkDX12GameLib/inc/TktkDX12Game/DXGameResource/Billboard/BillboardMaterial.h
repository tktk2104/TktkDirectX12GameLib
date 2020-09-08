#ifndef BILLBOARD_MATERIAL_H_
#define BILLBOARD_MATERIAL_H_

#include <TktkContainer/ResourceContainer/ResourceContainer.h>
#include <TktkDX12Wrapper/Resource/GraphicsPipeLine/PipeLineState/PipeLineStateInitParam.h>
#include "BillboardMaterialData.h"

namespace tktk
{
	// �uBillboardMaterialData�v���Ǘ�����N���X
	class BillboardMaterial
	{
	public:

		BillboardMaterial(const ShaderFilePaths& shaderFilePaths, const tktkContainer::ResourceContainerInitParam& initParam);
		~BillboardMaterial() = default;

	public:

		// �uBillboardMaterialData�v�̃C���X�^���X�����A���̃��\�[�X�̃n���h����Ԃ�
		unsigned int create(const BillboardMaterialInitParam& initParam);

		// �w�肵���r���{�[�h��`�悷��
		void drawBillboard(unsigned int handle, const BillboardDrawFuncBaseArgs& drawFuncArgs) const;

		// �������\���R�s�[�o�b�t�@���g���č��W�ϊ������Ǘ�����萔�o�b�t�@���X�V����
		void updateTransformCbuffer(unsigned int handle, unsigned int copyBufferHandle, const BillboardCbufferUpdateFuncArgs& updateArgs) const;

		// �������\���R�s�[�o�b�t�@���g���č��W�ϊ������Ǘ�����萔�o�b�t�@���X�V����i�؂蔲���͈͎w��Łj
		void updateTransformCbufferUseClippingParam(unsigned int handle, unsigned int copyBufferHandle, const BillboardCbufferUpdateFuncArgs& updateArgs, const BillboardClippingParam& clippingParam) const;

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