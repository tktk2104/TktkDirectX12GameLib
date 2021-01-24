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

		SpriteDrawer(
			float drawPriority,
			size_t spriteMaterialHandle,
			const tktkMath::Vector2& localPosition,
			const tktkMath::Vector2& localScale,
			float localRotationDeg,
			const tktkMath::Vector2& centerRate,
			const tktkMath::Color& blendRate,
			const tktkMath::Vector2& clippingLeftTopPos,
			const tktkMath::Vector2& clippingSize
		);

	public:

		void start();
		void afterCollide();

	public:

		// �X�v���C�g�}�e���A���n���h�����Đݒ肷��
		void setSpriteMaterialHandle(size_t handle);

		// �X�v���C�g�}�e���A��ID���Đݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�j
		// �������őΉ����郊�\�[�X�n���h���ɕϊ������
		void setSpriteMaterialId(ResourceIdCarrier id);
		
		// �X�v���C�g�̃��[�J���擾��ݒ肷��
		const tktkMath::Vector2& getLocalPosition() const;
		// �X�v���C�g�̃��[�J���X�P�[�����擾����
		const tktkMath::Vector2& getLocalScaleRate() const;
		// �X�v���C�g�̃��[�J����]���擾����i�x���@�j
		float getLocalRotationDeg() const;

		// �X�v���C�g�̃��[�J�����W��ݒ肷��
		void setLocalPosition(const tktkMath::Vector2& localPosition);
		// �X�v���C�g�̃��[�J���X�P�[����ݒ肷��
		void setLocalScaleRate(const tktkMath::Vector2& localScaleRate);
		// �X�v���C�g�̃��[�J����]��ݒ肷��i�x���@�j
		void setLocalRotationDeg(float localRotationDeg);

		// �X�v���C�g�̃��[�J�����W�𑝉�����
		void addLocalPosition(const tktkMath::Vector2& position);
		// �X�v���C�g�̃��[�J���X�P�[���𑝉�����
		void addLocalScaleRate(const tktkMath::Vector2& scaleRate);
		// �X�v���C�g�̃��[�J����]�𑝉�����i�x���@�j
		void addLocalRotationDeg(float rotationDeg);

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

		size_t						m_spriteMaterialHandle;
		float						m_drawPriority;
		tktkMath::Vector2			m_localPosition;
		tktkMath::Vector2			m_localScaleRate;
		float						m_localRotationDeg;
		tktkMath::Vector2			m_centerRate;
		tktkMath::Color				m_blendRate;
		tktkMath::Vector2			m_clippingLeftTopPos;
		tktkMath::Vector2			m_clippingSize;
		ComponentPtr<Transform2D>	m_transform;
	};
}
#endif // !SPRITE_DRAWER_H_