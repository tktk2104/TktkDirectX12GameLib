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

		SpriteClippingDrawer(float drawPriority, unsigned int spriteMaterialHandle, unsigned int useRtvDescriptorHeapHandle, const tktkMath::Vector2& centerRate, const SpriteClippingParam& clippingParam);

	public:

		void start();
		void onDestroy();
		void draw() const;

	public:

		// �X�v���C�g�}�e���A���n���h�����Đݒ肷��
		void setSpriteMaterialHandle(unsigned int handle);

		// �X�v���C�g�}�e���A��ID���Đݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		// �������őΉ����郊�\�[�X�n���h���ɕϊ������
		template <class IdType, is_idType<IdType> = nullptr>
		void setSpriteMaterialId(IdType id) { setSpriteMaterialIdImpl(static_cast<unsigned int>(id)); }
		
		// �X�v���C�g�̒��S�ʒu�̊�����ݒ肷��
		void setCenterRate(const tktkMath::Vector2& centerRate);

		// �؂���͈͂̃e�N�X�`�����W�ł̍�����W��ݒ肷��i�e�N�Z���j
		void setClippingLeftTopPos(const tktkMath::Vector2& leftTopPos);

		// �؂���͈͂̑傫����ݒ肷��i�e�N�Z���j
		void setClippingSize(const tktkMath::Vector2& size);

	private:

		// �e��id�w��n�̊֐��̎���
		void setSpriteMaterialIdImpl(int id);

	private:

		unsigned int				m_createCopyTransformCbufferHandle{ 0U };
		unsigned int				m_useRtvDescriptorHeapHandle;
		unsigned int				m_spriteMaterialHandle;
		tktkMath::Vector2			m_spriteCenterRate;
		SpriteClippingParam			m_clippingParam;
		ComponentPtr<Transform2D>	m_transform;

	public:

		template <class IdType, is_not_idType<IdType> = nullptr>
		void setSpriteMaterialId(IdType id) { static_assert(false, "SpriteMaterialId Fraud Type"); }
	};
}
#endif // !SPRITE_CLIPPING_DRAWER_H_