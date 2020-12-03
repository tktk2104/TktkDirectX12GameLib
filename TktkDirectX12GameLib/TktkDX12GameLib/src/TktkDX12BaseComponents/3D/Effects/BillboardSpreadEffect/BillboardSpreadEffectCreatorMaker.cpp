#include "TktkDX12BaseComponents/3D/Effects/BillboardSpreadEffect/BillboardSpreadEffectCreatorMaker.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"

namespace tktk
{
    BillboardSpreadEffectCreatorMaker BillboardSpreadEffectCreatorMaker::m_self;

    BillboardSpreadEffectCreatorMaker& BillboardSpreadEffectCreatorMaker::makeStart(GameObjectPtr user)
    {
        // �ϐ�������������
        m_self = BillboardSpreadEffectCreatorMaker();

        // �����̃��[�U�[��ݒ�
        m_self.m_user = user;

        // ���g�̎Q�Ƃ�Ԃ�
        return m_self;
    }

    ComponentPtr<BillboardSpreadEffectCreator> BillboardSpreadEffectCreatorMaker::create()
    {
        return m_user->createComponent<BillboardSpreadEffectCreator>(m_param);
    }

    BillboardSpreadEffectCreatorMaker& BillboardSpreadEffectCreatorMaker::generateLocalPos(const tktkMath::Vector3& value)
    {
        // �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
        m_param.generateLocalPos = value;
        return *this;
    }

    BillboardSpreadEffectCreatorMaker& BillboardSpreadEffectCreatorMaker::generateLocalPosRandomRange(const tktkMath::Vector3& value)
    {
        // �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
        m_param.generateLocalPosRandomRange = value;
        return *this;
    }

    BillboardSpreadEffectCreatorMaker& BillboardSpreadEffectCreatorMaker::firstGenerateTimeSec(float value)
    {
        // �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
        m_param.firstGenerateTimeSec = value;
        return *this;
    }

    BillboardSpreadEffectCreatorMaker& BillboardSpreadEffectCreatorMaker::generateIntervalTimeSec(float value)
    {
        // �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
        m_param.generateIntervalTimeSec = value;
        return *this;
    }

    BillboardSpreadEffectCreatorMaker& BillboardSpreadEffectCreatorMaker::generateIntervalTimeRandomRange(float value)
    {
        // �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
        m_param.generateIntervalTimeRandomRange = value;
        return *this;
    }

    BillboardSpreadEffectCreatorMaker& BillboardSpreadEffectCreatorMaker::generateNumPerOnce(int value)
    {
        // �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
        m_param.generateNumPerOnce = value;
        return *this;
    }

    BillboardSpreadEffectCreatorMaker& BillboardSpreadEffectCreatorMaker::generateNumPerOnceRandomRange(int value)
    {
        // �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
        m_param.generateNumPerOnceRandomRange = value;
        return *this;
    }

    BillboardSpreadEffectCreatorMaker& BillboardSpreadEffectCreatorMaker::totalGenerateNum(int value)
    {
        // �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
        m_param.totalGenerateNum = value;
        return *this;
    }

    BillboardSpreadEffectCreatorMaker& BillboardSpreadEffectCreatorMaker::changeAvtiveToReset(bool value)
    {
        // �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
        m_param.changeAvtiveToReset = value;
        return *this;
    }

    BillboardSpreadEffectCreatorMaker& BillboardSpreadEffectCreatorMaker::billboardMaterialHandle(size_t value)
    {
        // �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
        m_param.useBillboardHandle = value;
        return *this;
    }

    BillboardSpreadEffectCreatorMaker& BillboardSpreadEffectCreatorMaker::billboardMaterialId(ResourceIdCarrier value)
    {
        // �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
        m_param.useBillboardHandle = DX12GameManager::getBillboardMaterialHandle(value);
        return *this;
    }

    BillboardSpreadEffectCreatorMaker& BillboardSpreadEffectCreatorMaker::billboardScale(const tktkMath::Vector2& value)
    {
        // �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
        m_param.billboardScale = value;
        return *this;
    }

    BillboardSpreadEffectCreatorMaker& BillboardSpreadEffectCreatorMaker::billboardScaleRandomRange(const tktkMath::Vector2& value)
    {
        // �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
        m_param.billboardScaleRandomRange = value;
        return *this;
    }

    BillboardSpreadEffectCreatorMaker& BillboardSpreadEffectCreatorMaker::billboardBlendRate(const tktkMath::Color& value)
    {
        // �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
        m_param.billboardBlendRate = value;
        return *this;
    }

    BillboardSpreadEffectCreatorMaker& BillboardSpreadEffectCreatorMaker::setChild(bool value)
    {
        // �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
        m_param.setChild = value;
        return *this;
    }

    BillboardSpreadEffectCreatorMaker& BillboardSpreadEffectCreatorMaker::lifeTimeSec(float value)
    {
        // �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
        m_param.lifeTimeSec = value;
        return *this;
    }

    BillboardSpreadEffectCreatorMaker& BillboardSpreadEffectCreatorMaker::lifeTimeSecRandomRange(float value)
    {
        // �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
        m_param.lifeTimeSecRandomRange = value;
        return *this;
    }

    BillboardSpreadEffectCreatorMaker& BillboardSpreadEffectCreatorMaker::moveSpeedPerSec(float value)
    {
        // �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
        m_param.moveSpeedPerSec = value;
        return *this;
    }

    BillboardSpreadEffectCreatorMaker& BillboardSpreadEffectCreatorMaker::moveSpeedPerSecRandomRange(float value)
    {
        // �l��ݒ肵�Ď��g�̎Q�Ƃ�Ԃ�
        m_param.moveSpeedPerSecRandomRange = value;
        return *this;
    }
}