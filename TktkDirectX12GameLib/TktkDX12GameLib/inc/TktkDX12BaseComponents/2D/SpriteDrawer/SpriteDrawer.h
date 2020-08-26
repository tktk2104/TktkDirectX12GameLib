#ifndef SPRITE_DRAWER_H_
#define SPRITE_DRAWER_H_

#include <TktkTemplateMetaLib/TypeCheck/isIdType.h>
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector2.h>
#include "../../../TktkDX12Game/Component/ComponentBase.h"
#include "../Transform2D/Transform2D.h"

namespace tktk
{
	// �X�v���C�g�`��R���|�[�l���g
	// �y�K�{�R���|�[�l���g�FTransform2D�z
	class SpriteDrawer
		: public ComponentBase
	{
	public:

		SpriteDrawer(float drawPriority, unsigned int spriteMaterialId, unsigned int useRtvDescriptorHeapHandle);

	public:

		void start();
		void draw() const;

	public:

		// �e�N�X�`���}�e���A��ID���Đݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		template <class IdType, is_idType<IdType> = nullptr>
		void setSpriteMaterialId(IdType id)
		{
			setSpriteMaterialIdImpl(static_cast<unsigned int>(id));
		}
		template <class IdType, is_not_idType<IdType> = nullptr>
		void setSpriteMaterialId(IdType id) { static_assert(false, "SpriteMaterialId Fraud Type"); }

	private:

		// �e��id�w��n�̊֐��̎���
		void setSpriteMaterialIdImpl(unsigned int id);

	private:

		unsigned int				m_useRtvDescriptorHeapHandle;
		unsigned int				m_spriteMaterialId;
		ComponentPtr<Transform2D>	m_transform			{ };
	};
}
#endif // !SPRITE_DRAWER_H_
