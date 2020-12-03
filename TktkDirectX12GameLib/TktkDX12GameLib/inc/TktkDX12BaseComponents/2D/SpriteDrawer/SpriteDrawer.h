#ifndef SPRITE_DRAWER_H_
#define SPRITE_DRAWER_H_

/* class member */
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector2.h>

/* funcUseType */
#include "../../../TktkDX12Game/UtilityProcessManager/ResourceHandleGetter/ResourceIdConverter/ResourceIdCarrier.h"

/* base class */
#include "../../../TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentBase.h"

namespace tktk
{
	/* class member */
	class Transform2D;

	// �X�v���C�g�`��R���|�[�l���g
	// �y�K�{�R���|�[�l���g�FTransform2D�z
	class SpriteDrawer
		: public ComponentBase
	{
	public:

		SpriteDrawer(float drawPriority, size_t spriteMaterialHandle, size_t useRtvDescriptorHeapHandle, const tktkMath::Vector2& centerRate, const tktkMath::Color& blendRate);

	public:

		void start();
		void onDestroy();
		void draw() const;

	public:

		// �X�v���C�g�}�e���A���n���h�����Đݒ肷��
		void setSpriteMaterialHandle(size_t handle);

		// �X�v���C�g�}�e���A��ID���Đݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		// �������őΉ����郊�\�[�X�n���h���ɕϊ������
		void setSpriteMaterialId(ResourceIdCarrier id);
		
		// �X�v���C�g�̒��S�ʒu�̊�����ݒ肷��
		void setCenterRate(const tktkMath::Vector2& centerRate);

		// �u�����h���[�g���擾����
		const tktkMath::Color& getBlendRate() const;

		// �u�����h���[�g��ݒ肷��
		void setBlendRate(const tktkMath::Color& blendRate);

	private:

		size_t						m_createUploadTransformCbufferHandle{ 0U };
		size_t						m_useRtvDescriptorHeapHandle;
		size_t						m_spriteMaterialHandle;
		tktkMath::Vector2			m_spriteCenterRate;
		tktkMath::Color				m_blendRate;
		ComponentPtr<Transform2D>	m_transform;
	};
}
#endif // !SPRITE_DRAWER_H_
