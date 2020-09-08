#ifndef BILLBOARD_CLIPPING_DRAWER_H_
#define BILLBOARD_CLIPPING_DRAWER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector2.h>
#include "../../../TktkDX12Game/Component/ComponentBase.h"
#include "../Transform3D/Transform3D.h"

namespace tktk
{
	// �r���{�[�h�؂蔲���`��R���|�[�l���g
	// �y�K�{�R���|�[�l���g�FTransform3D�i��]�͂����A�X�P�[���͂������̂ݎQ�Ƃ��܂��j�z
	class BillboardClippingDrawer
		: public ComponentBase
	{
	public:

		BillboardClippingDrawer(float drawPriority, unsigned int billboardMaterialHandle, unsigned int useRtvDescriptorHeapHandle, unsigned int cameraHandle, const tktkMath::Vector2& centerRate, const tktkMath::Color& blendRate, const BillboardClippingParam& clippingParam);

	public:

		void start();
		void onDestroy();
		void draw() const;

	public:

		// �r���{�[�h�}�e���A���n���h�����Đݒ肷��
		void setBillboardMaterialHandle(unsigned int handle);

		// �r���{�[�h�}�e���A��ID���Đݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		// �������őΉ����郊�\�[�X�n���h���ɕϊ������
		template <class IdType, is_idType<IdType> = nullptr>
		void setBillboardMaterialId(IdType id) { setBillboardMaterialIdImpl(static_cast<unsigned int>(id)); }

		// �r���{�[�h�̒��S�ʒu�̊�����ݒ肷��
		void setCenterRate(const tktkMath::Vector2& centerRate);

		// �؂���͈͂̃e�N�X�`�����W�ł̍�����W��ݒ肷��i�e�N�Z���j
		void setClippingLeftTopPos(const tktkMath::Vector2& leftTopPos);

		// �؂���͈͂̑傫����ݒ肷��i�e�N�Z���j
		void setClippingSize(const tktkMath::Vector2& size);

	private:

		// �e��id�w��n�̊֐��̎���
		void setBillboardMaterialIdImpl(int id);

	private:

		unsigned int				m_createCopyTransformCbufferHandle{ 0U };
		unsigned int				m_useRtvDescriptorHeapHandle;
		unsigned int				m_cameraHandle;
		unsigned int				m_billboardMaterialHandle;
		tktkMath::Vector2			m_centerRate;
		tktkMath::Color				m_blendRate;
		BillboardClippingParam		m_clippingParam;
		ComponentPtr<Transform3D>	m_transform;

	public:

		template <class IdType, is_not_idType<IdType> = nullptr>
		void setBillboardMaterialId(IdType id) { static_assert(false, "BillboardMaterialId Fraud Type"); }
	};
}
#endif // !BILLBOARD_CLIPPING_DRAWER_H_
