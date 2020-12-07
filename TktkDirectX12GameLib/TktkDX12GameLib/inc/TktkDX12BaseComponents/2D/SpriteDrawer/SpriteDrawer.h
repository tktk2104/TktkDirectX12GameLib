#ifndef SPRITE_DRAWER_H_
#define SPRITE_DRAWER_H_

/* class member */
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector2.h>
#include "../../../TktkDX12Game/DXGameResource/DXGameShaderResouse/Sprite/Structs/SpriteClippingParam.h"

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

		SpriteDrawer(
			float drawPriority,
			size_t spriteMaterialHandle,
			size_t useRtvDescriptorHeapHandle,
			const tktkMath::Vector2& centerRate,
			const tktkMath::Color& blendRate,
			const SpriteClippingParam& clippingParam
		);

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

		// �؂���͈͂̃e�N�X�`�����W�ł̍�����W��ݒ肷��i�e�N�Z���j
		void setClippingLeftTopPos(const tktkMath::Vector2& leftTopPos);

		// �؂���͈͂̑傫����ݒ肷��i�e�N�Z���j
		void setClippingSize(const tktkMath::Vector2& size);

		// �؂���͈͂̍�����W��ݒ肷��i�e�N�X�`���T�C�Y���i1, 1�j�Ƃ������̊����j
		void setClippingLeftTopPosRate(const tktkMath::Vector2& leftTopPosRate);

		// �؂���͈͂̑傫����ݒ肷��i�e�N�X�`���T�C�Y���i1, 1�j�Ƃ������̊����j
		void setClippingSizeRate(const tktkMath::Vector2& sizeRate);

	private:

		size_t						m_createUploadTransformCbufferHandle{ 0U };
		size_t						m_useRtvDescriptorHeapHandle;
		size_t						m_spriteMaterialHandle;
		tktkMath::Vector2			m_spriteCenterRate;
		tktkMath::Color				m_blendRate;
		SpriteClippingParam			m_clippingParam;
		ComponentPtr<Transform2D>	m_transform;
	};
}
#endif // !SPRITE_DRAWER_H_
