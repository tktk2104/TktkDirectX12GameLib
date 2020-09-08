#ifndef BILLBOARD_DRAWER_H_
#define BILLBOARD_DRAWER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector2.h>
#include "../../../TktkDX12Game/Component/ComponentBase.h"
#include "../Transform3D/Transform3D.h"

namespace tktk
{
	// �r���{�[�h�`��R���|�[�l���g
	// �y�K�{�R���|�[�l���g�FTransform3D�i��]�͂����A�X�P�[���͂������̂ݎQ�Ƃ��܂��j�z
	class BillboardDrawer
		: public ComponentBase
	{
	public:

		BillboardDrawer(float drawPriority, unsigned int billboardMaterialHandle, unsigned int useRtvDescriptorHeapHandle, unsigned int cameraHandle, const tktkMath::Vector2& centerRate, const tktkMath::Color& blendRate);

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
		ComponentPtr<Transform3D>	m_transform;

	public:

		template <class IdType, is_not_idType<IdType> = nullptr>
		void setBillboardMaterialId(IdType id) { static_assert(false, "BillboardMaterialId Fraud Type"); }
	};
}
#endif // !BILLBOARD_DRAWER_H_