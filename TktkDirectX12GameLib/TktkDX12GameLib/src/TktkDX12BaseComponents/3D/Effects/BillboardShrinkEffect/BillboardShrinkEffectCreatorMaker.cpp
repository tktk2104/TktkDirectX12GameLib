#include "TktkDX12BaseComponents/3D/Effects/BillboardShrinkEffect/BillboardShrinkEffectCreatorMaker.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"

namespace tktk
{
    BillboardShrinkEffectCreatorMaker BillboardShrinkEffectCreatorMaker::m_self;

    BillboardShrinkEffectCreatorMaker& BillboardShrinkEffectCreatorMaker::makeStart(GameObjectPtr user)
    {
        // �ϐ�������������
        m_self = BillboardShrinkEffectCreatorMaker();

        // �����̃��[�U�[��ݒ�
        m_self.m_user = user;

        // ���g�̎Q�Ƃ�Ԃ�
        return m_self;
    }

    ComponentPtr<BillboardShrinkEffectCreator> BillboardShrinkEffectCreatorMaker::create()
    {
        return m_user->createComponent<BillboardShrinkEffectCreator>(m_param);
    }

    BillboardShrinkEffectCreatorMaker& BillboardShrinkEffectCreatorMaker::shrinkTargetPos(const tktkMath::Vector3& value)
    {
        // �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
        m_param.shrinkTargetPos = value;
        return *this;
    }

    BillboardShrinkEffectCreatorMaker& BillboardShrinkEffectCreatorMaker::shrinkTargetPosRandomRange(const tktkMath::Vector3& value)
    {
        // �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
        m_param.shrinkTargetPosRandomRange = value;
        return *this;
    }

    BillboardShrinkEffectCreatorMaker& BillboardShrinkEffectCreatorMaker::generateIntervalTimeSec(float value)
    {
        // �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
        m_param.generateIntervalTimeSec = value;
        return *this;
    }

    BillboardShrinkEffectCreatorMaker& BillboardShrinkEffectCreatorMaker::generateIntervalTimeRandomRange(float value)
    {
        // �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
        m_param.generateIntervalTimeRandomRange = value;
        return *this;
    }

    BillboardShrinkEffectCreatorMaker& BillboardShrinkEffectCreatorMaker::generateNumPerOnce(int value)
    {
        // �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
        m_param.generateNumPerOnce = value;
        return *this;
    }

    BillboardShrinkEffectCreatorMaker& BillboardShrinkEffectCreatorMaker::generateNumPerOnceRandomRange(int value)
    {
        // �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
        m_param.generateNumPerOnceRandomRange = value;
        return *this;
    }

    BillboardShrinkEffectCreatorMaker& BillboardShrinkEffectCreatorMaker::totalGenerateNum(int value)
    {
        // �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
        m_param.totalGenerateNum = value;
        return *this;
    }

    BillboardShrinkEffectCreatorMaker& BillboardShrinkEffectCreatorMaker::changeAvtiveToReset(bool value)
    {
        // �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
        m_param.changeAvtiveToReset = value;
        return *this;
    }

    BillboardShrinkEffectCreatorMaker& BillboardShrinkEffectCreatorMaker::billboardMaterialHandle(size_t value)
    {
        // �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
        m_param.useBillboardHandle = value;
        return *this;
    }

    BillboardShrinkEffectCreatorMaker& BillboardShrinkEffectCreatorMaker::billboardMaterialId(ResourceIdCarrier value)
    {
        // �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
        m_param.useBillboardHandle = DX12GameManager::getBillboardMaterialHandle(value);
        return *this;
    }

    BillboardShrinkEffectCreatorMaker& BillboardShrinkEffectCreatorMaker::billboardScale(const tktkMath::Vector2& value)
    {
        // �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
        m_param.billboardScale = value;
        return *this;
    }

    BillboardShrinkEffectCreatorMaker& BillboardShrinkEffectCreatorMaker::billboardScaleRandomRange(const tktkMath::Vector2& value)
    {
        // �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
        m_param.billboardScaleRandomRange = value;
        return *this;
    }

    BillboardShrinkEffectCreatorMaker& BillboardShrinkEffectCreatorMaker::billboardBlendRate(const tktkMath::Color& value)
    {
        // �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
        m_param.billboardBlendRate = value;
        return *this;
    }

    BillboardShrinkEffectCreatorMaker& BillboardShrinkEffectCreatorMaker::setChild(bool value)
    {
        // �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
        m_param.setChild = value;
        return *this;
    }

    BillboardShrinkEffectCreatorMaker& BillboardShrinkEffectCreatorMaker::lifeTimeSec(float value)
    {
        // �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
        m_param.lifeTimeSec = value;
        return *this;
    }

    BillboardShrinkEffectCreatorMaker& BillboardShrinkEffectCreatorMaker::lifeTimeSecRandomRange(float value)
    {
        // �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
        m_param.lifeTimeSecRandomRange = value;
        return *this;
    }

    BillboardShrinkEffectCreatorMaker& BillboardShrinkEffectCreatorMaker::moveSpeedPerSec(float value)
    {
        // �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
        m_param.moveSpeedPerSec = value;
        return *this;
    }

    BillboardShrinkEffectCreatorMaker& BillboardShrinkEffectCreatorMaker::moveSpeedPerSecRandomRange(float value)
    {
        // �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
        m_param.moveSpeedPerSecRandomRange = value;
        return *this;
    }
}