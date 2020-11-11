#ifndef BILLBOARD_CLIPPING_DRAWER_H_
#define BILLBOARD_CLIPPING_DRAWER_H_

/* base class */
#include "../../../TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentBase.h"

/* funcUseType */
#include "TktkDX12Game/UtilityProcessManager/ResourceHandleGetter/ResourceIdConverter/ResourceIdCarrier.h"

/* class member */
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector2.h>
#include "TktkDX12Game/DXGameResource/DXGameShaderResouse/Billboard/BillboardClippingParam.h"

namespace tktk
{
	/* class member */
	class Transform3D;

	// �r���{�[�h�؂蔲���`��R���|�[�l���g
	// �y�K�{�R���|�[�l���g�FTransform3D�i��]�͂����A�X�P�[���͂������̂ݎQ�Ƃ��܂��j�z
	class BillboardClippingDrawer
		: public ComponentBase
	{
	public:

		BillboardClippingDrawer(float drawPriority, size_t billboardMaterialHandle, size_t useRtvDescriptorHeapHandle, size_t cameraHandle, const tktkMath::Vector2& centerRate, const tktkMath::Color& blendRate, const BillboardClippingParam& clippingParam);

	public:

		void start();
		void onDestroy();
		void draw() const;

	public:

		// �r���{�[�h�}�e���A���n���h�����Đݒ肷��
		void setBillboardMaterialHandle(size_t handle);

		// �r���{�[�h�}�e���A��ID���Đݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		// �������őΉ����郊�\�[�X�n���h���ɕϊ������
		void setBillboardMaterialId(ResourceIdCarrier id);

		// �r���{�[�h�̒��S�ʒu�̊�����ݒ肷��
		void setCenterRate(const tktkMath::Vector2& centerRate);

		// �؂���͈͂̃e�N�X�`�����W�ł̍�����W��ݒ肷��i�e�N�Z���j
		void setClippingLeftTopPos(const tktkMath::Vector2& leftTopPos);

		// �؂���͈͂̑傫����ݒ肷��i�e�N�Z���j
		void setClippingSize(const tktkMath::Vector2& size);

	private:

		size_t						m_createUploadTransformCbufferHandle{ 0U };
		size_t						m_useRtvDescriptorHeapHandle;
		size_t						m_cameraHandle;
		size_t						m_billboardMaterialHandle;
		tktkMath::Vector2			m_centerRate;
		tktkMath::Color				m_blendRate;
		BillboardClippingParam		m_clippingParam;
		ComponentPtr<Transform3D>	m_transform;
	};
}
#endif // !BILLBOARD_CLIPPING_DRAWER_H_
