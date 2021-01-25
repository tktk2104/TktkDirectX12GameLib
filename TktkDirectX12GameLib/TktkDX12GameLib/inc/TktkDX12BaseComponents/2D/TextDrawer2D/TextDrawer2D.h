#ifndef TEXT_DRAWER_2D_H_
#define TEXT_DRAWER_2D_H_

/* class member */
#include <string>
#include <vector>
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

	// �e�L�X�g�`��R���|�[�l���g
	class TextDrawer2D
		: public ComponentBase
	{
	public:

		TextDrawer2D(
			float drawPriority,
			size_t fontHandle,
			const std::string& initText,
			const tktkMath::Vector2& localPosition,
			const tktkMath::Vector2& localScale,
			const tktkMath::Vector2& centerRate,
			const tktkMath::Color& blendRate
		);

	public:

		void start();
		void afterCollide();

	public:

		// �g�p����t�H���gID���Đݒ肷��
		void setFontId(ResourceIdCarrier fontId);

		// �`�悷��e�L�X�g���X�V����
		void updateText(const std::string& text);

		// �e�L�X�g�̃��[�J�����W���Đݒ肷��
		void setLocalPosition(const tktkMath::Vector2& localPosition);

		// �e�L�X�g�̃��[�J���X�P�[�����Đݒ肷��
		void setLocalScale(const tktkMath::Vector2& localScale);

		// �e�L�X�g�̒��S�ʒu�̊������Đݒ肷��
		void setCenterRate(const tktkMath::Vector2& centerRate);

		// �u�����h���[�g���Đݒ肷��
		void setBlendRate(const tktkMath::Color& blendRate);

	private:

		float						m_drawPriority;
		size_t						m_fontHandle;
		std::string					m_tempText;
		std::vector<unsigned char>	m_textureData;
		float						m_useTextureDataWidth{ 0.0f };
		tktkMath::Vector2			m_localPosition;
		tktkMath::Vector2			m_localScale;
		tktkMath::Vector2			m_centerRate;
		tktkMath::Color				m_blendRate;
		ComponentPtr<Transform2D>	m_transform;
	};
}
#endif // !TEXT_DRAWER_2D_H_