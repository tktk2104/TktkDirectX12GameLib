#include "TktkDX12BaseComponents/2D/Effects/SpriteSpreadEffect/SpriteSpreadEffectCreatorMaker.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"

namespace tktk
{
	SpriteSpreadEffectCreatorMaker SpriteSpreadEffectCreatorMaker::m_self;

	SpriteSpreadEffectCreatorMaker& SpriteSpreadEffectCreatorMaker::makeStart(GameObjectPtr user)
	{
		// �ϐ�������������
		m_self = SpriteSpreadEffectCreatorMaker();

		// �����̃��[�U�[��ݒ�
		m_self.m_user = user;

		// ���g�̎Q�Ƃ�Ԃ�
		return m_self;
	}

	ComponentPtr<SpriteSpreadEffectCreator> SpriteSpreadEffectCreatorMaker::create()
	{
		return m_user->createComponent<SpriteSpreadEffectCreator>(m_param);
	}

	SpriteSpreadEffectCreatorMaker& SpriteSpreadEffectCreatorMaker::generateLocalPos(const tktkMath::Vector2& value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_param.generateLocalPos = value;
		return *this;
	}

	SpriteSpreadEffectCreatorMaker& SpriteSpreadEffectCreatorMaker::generateLocalPosRandomRange(const tktkMath::Vector2& value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_param.generateLocalPosRandomRange = value;
		return *this;
	}

	SpriteSpreadEffectCreatorMaker& SpriteSpreadEffectCreatorMaker::minGenerateAngleDeg(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_param.minGenerateAngleDeg = value;
		return *this;
	}

	SpriteSpreadEffectCreatorMaker& SpriteSpreadEffectCreatorMaker::maxGenerateAngleDeg(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_param.maxGenerateAngleDeg = value;
		return *this;
	}

	SpriteSpreadEffectCreatorMaker& SpriteSpreadEffectCreatorMaker::firstGenerateTimeSec(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_param.firstGenerateTimeSec = value;
		return *this;
	}

	SpriteSpreadEffectCreatorMaker& SpriteSpreadEffectCreatorMaker::generateIntervalTimeSec(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_param.generateIntervalTimeSec = value;
		return *this;
	}

	SpriteSpreadEffectCreatorMaker& SpriteSpreadEffectCreatorMaker::generateIntervalTimeRandomRange(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_param.generateIntervalTimeRandomRange = value;
		return *this;
	}

	SpriteSpreadEffectCreatorMaker& SpriteSpreadEffectCreatorMaker::generateNumPerOnce(int value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_param.generateNumPerOnce = value;
		return *this;
	}

	SpriteSpreadEffectCreatorMaker& SpriteSpreadEffectCreatorMaker::generateNumPerOnceRandomRange(int value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_param.generateNumPerOnceRandomRange = value;
		return *this;
	}

	SpriteSpreadEffectCreatorMaker& SpriteSpreadEffectCreatorMaker::totalGenerateNum(int value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_param.totalGenerateNum = value;
		return *this;
	}

	SpriteSpreadEffectCreatorMaker& SpriteSpreadEffectCreatorMaker::changeAvtiveToReset(bool value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_param.changeAvtiveToReset = value;
		return *this;
	}

	SpriteSpreadEffectCreatorMaker& SpriteSpreadEffectCreatorMaker::spriteMaterialHandle(size_t value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_param.useSpriteHandle = value;
		return *this;
	}

	SpriteSpreadEffectCreatorMaker& SpriteSpreadEffectCreatorMaker::spriteMaterialId(ResourceIdCarrier value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_param.useSpriteHandle = DX12GameManager::getSpriteMaterialHandle(value);
		return *this;
	}

	SpriteSpreadEffectCreatorMaker& SpriteSpreadEffectCreatorMaker::spriteScale(const tktkMath::Vector2& value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_param.spriteScale = value;
		return *this;
	}

	SpriteSpreadEffectCreatorMaker& SpriteSpreadEffectCreatorMaker::spriteScaleRandomRange(const tktkMath::Vector2& value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_param.spriteScaleRandomRange = value;
		return *this;
	}

	SpriteSpreadEffectCreatorMaker& SpriteSpreadEffectCreatorMaker::spriteBlendRate(const tktkMath::Color& value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_param.spriteBlendRate = value;
		return *this;
	}

	SpriteSpreadEffectCreatorMaker& SpriteSpreadEffectCreatorMaker::setChild(bool value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_param.setChild = value;
		return *this;
	}

	SpriteSpreadEffectCreatorMaker& SpriteSpreadEffectCreatorMaker::lifeTimeSec(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_param.lifeTimeSec = value;
		return *this;
	}

	SpriteSpreadEffectCreatorMaker& SpriteSpreadEffectCreatorMaker::lifeTimeSecRandomRange(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_param.lifeTimeSecRandomRange = value;
		return *this;
	}

	SpriteSpreadEffectCreatorMaker& SpriteSpreadEffectCreatorMaker::moveSpeedPerSec(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_param.moveSpeedPerSec = value;
		return *this;
	}

	SpriteSpreadEffectCreatorMaker& SpriteSpreadEffectCreatorMaker::moveSpeedPerSecRandomRange(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_param.moveSpeedPerSecRandomRange = value;
		return *this;
	}

	SpriteSpreadEffectCreatorMaker& SpriteSpreadEffectCreatorMaker::useAnimation(bool value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_param.useAnimation = value;
		return *this;
	}

	SpriteSpreadEffectCreatorMaker& SpriteSpreadEffectCreatorMaker::isLoop(bool value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_param.isLoop = value;
		return *this;
	}

	SpriteSpreadEffectCreatorMaker& SpriteSpreadEffectCreatorMaker::initFrame(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_param.initFrame = value;
		return *this;
	}

	SpriteSpreadEffectCreatorMaker& SpriteSpreadEffectCreatorMaker::animSpeedRate(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_param.animSpeedRate = value;
		return *this;
	}

	SpriteSpreadEffectCreatorMaker& SpriteSpreadEffectCreatorMaker::animFramePerSec(float value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_param.animFramePerSec = value;
		return *this;
	}

	SpriteSpreadEffectCreatorMaker& SpriteSpreadEffectCreatorMaker::totalAnimFrameSize(unsigned int value)
	{
		// �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
		m_param.totalAnimFrameSize = value;
		return *this;
	}
}