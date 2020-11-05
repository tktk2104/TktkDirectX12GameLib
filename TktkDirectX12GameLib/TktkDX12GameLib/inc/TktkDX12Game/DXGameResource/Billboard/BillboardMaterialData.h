#ifndef BILLBOARD_MATERIAL_DATA_H_
#define BILLBOARD_MATERIAL_DATA_H_

#include "BillboardMaterialInitParam.h"
#include "BillboardDrawFuncBaseArgs.h"
#include "BillboardClippingParam.h"
#include "BillboardCbufferUpdateFuncArgs.h"

namespace tktk
{
	class BillboardMaterialData
	{
	public:

		explicit BillboardMaterialData(const BillboardMaterialInitParam& initParam);
		~BillboardMaterialData();

		// ���[�u�R���X�g���N�^
		BillboardMaterialData(BillboardMaterialData&& other) noexcept;

	public:

		// �r���{�[�h��`�悷��
		void drawBillboard(const BillboardDrawFuncBaseArgs& drawFuncArgs) const;

		// �������\���R�s�[�o�b�t�@���g���č��W�ϊ������Ǘ�����萔�o�b�t�@���X�V����
		void updateTransformCbuffer(size_t copyBufferHandle, const BillboardCbufferUpdateFuncArgs& updateArgs) const;

		// �������\���R�s�[�o�b�t�@���g���č��W�ϊ������Ǘ�����萔�o�b�t�@���X�V����i�؂蔲���͈͎w��Łj
		void updateTransformCbufferUseClippingParam(size_t copyBufferHandle, const BillboardCbufferUpdateFuncArgs& updateArgs, const BillboardClippingParam& clippingParam) const;

	private:

		size_t				m_createDescriptorHeapHandle{ 0U };
		tktkMath::Vector2	m_textureUvOffset;
		tktkMath::Vector2	m_textureUvMulRate;
		tktkMath::Vector2	m_textureSize;
	};
}
#endif // !BILLBOARD_MATERIAL_DATA_H_