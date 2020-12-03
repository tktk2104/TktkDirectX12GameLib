#ifndef BILLBOARD_DRAWER_H_
#define BILLBOARD_DRAWER_H_

/* base class */
#include "../../../TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentBase.h"

/* funcUseType */
#include "TktkDX12Game/UtilityProcessManager/ResourceHandleGetter/ResourceIdConverter/ResourceIdCarrier.h"

/* class member */
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector2.h>


namespace tktk
{
	/* class member */
	class Transform3D;

	// �r���{�[�h�`��R���|�[�l���g
	// �y�K�{�R���|�[�l���g�FTransform3D�i��]�͂����A�X�P�[���͂������̂ݎQ�Ƃ��܂��j�z
	class BillboardDrawer
		: public ComponentBase
	{
	public:

		BillboardDrawer(
			size_t billboardMaterialHandle,
			const tktkMath::Vector2& centerRate,
			const tktkMath::Color& blendRate,
			const tktkMath::Vector2& clippingLeftTopPos,
			const tktkMath::Vector2& clippingSize
		);

	public:

		void start();
		void afterCollide();

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

		size_t						m_billboardMaterialHandle;
		tktkMath::Vector2			m_centerRate;
		tktkMath::Color				m_blendRate;
		tktkMath::Vector2			m_clippingLeftTopPos;
		tktkMath::Vector2			m_clippingSize;
		ComponentPtr<Transform3D>	m_transform;
	};
}
#endif // !BILLBOARD_DRAWER_H_