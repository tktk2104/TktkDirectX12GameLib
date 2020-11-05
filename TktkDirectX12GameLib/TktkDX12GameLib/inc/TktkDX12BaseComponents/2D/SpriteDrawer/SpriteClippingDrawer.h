#ifndef SPRITE_CLIPPING_DRAWER_H_
#define SPRITE_CLIPPING_DRAWER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector2.h>
#include "../../../TktkDX12Game/Component/ComponentBase.h"
#include "../Transform2D/Transform2D.h"
#include "../../../TktkDX12Game/DXGameResource/Sprite/SpriteClippingParam.h"

namespace tktk
{
	// �X�v���C�g�؂蔲���`��R���|�[�l���g
	// �y�K�{�R���|�[�l���g�FTransform2D�z
	class SpriteClippingDrawer
		: public ComponentBase
	{
	public:

		SpriteClippingDrawer(float drawPriority, size_t spriteMaterialHandle, size_t useRtvDescriptorHeapHandle, const tktkMath::Vector2& centerRate, const SpriteClippingParam& clippingParam);

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

		// �؂���͈͂̃e�N�X�`�����W�ł̍�����W��ݒ肷��i�e�N�Z���j
		void setClippingLeftTopPos(const tktkMath::Vector2& leftTopPos);

		// �؂���͈͂̑傫����ݒ肷��i�e�N�Z���j
		void setClippingSize(const tktkMath::Vector2& size);

	private:

		size_t						m_createUploadTransformCbufferHandle{ 0U };
		size_t						m_useRtvDescriptorHeapHandle;
		size_t						m_spriteMaterialHandle;
		tktkMath::Vector2			m_spriteCenterRate;
		SpriteClippingParam			m_clippingParam;
		ComponentPtr<Transform2D>	m_transform;
	};
}
#endif // !SPRITE_CLIPPING_DRAWER_H_