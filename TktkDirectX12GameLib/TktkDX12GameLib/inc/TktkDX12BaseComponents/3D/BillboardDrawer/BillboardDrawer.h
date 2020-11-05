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

		BillboardDrawer(float drawPriority, size_t billboardMaterialHandle, size_t useRtvDescriptorHeapHandle, size_t cameraHandle, const tktkMath::Vector2& centerRate, const tktkMath::Color& blendRate);

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

	private:

		size_t						m_createUploadTransformCbufferHandle{ 0U };
		size_t						m_useRtvDescriptorHeapHandle;
		size_t						m_cameraHandle;
		size_t						m_billboardMaterialHandle;
		tktkMath::Vector2			m_centerRate;
		tktkMath::Color				m_blendRate;
		ComponentPtr<Transform3D>	m_transform;
	};
}
#endif // !BILLBOARD_DRAWER_H_