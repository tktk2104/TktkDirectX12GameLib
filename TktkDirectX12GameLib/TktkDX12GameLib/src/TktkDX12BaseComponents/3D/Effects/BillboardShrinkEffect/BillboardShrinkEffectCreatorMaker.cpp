#include "TktkDX12BaseComponents/3D/Effects/BillboardShrinkEffect/BillboardShrinkEffectCreatorMaker.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"

namespace tktk
{
    BillboardShrinkEffectCreatorMaker BillboardShrinkEffectCreatorMaker::m_self;

    BillboardShrinkEffectCreatorMaker& BillboardShrinkEffectCreatorMaker::makeStart(GameObjectPtr user)
    {
        // 変数を初期化する
        m_self = BillboardShrinkEffectCreatorMaker();

        // 引数のユーザーを設定
        m_self.m_user = user;

        // 自身の参照を返す
        return m_self;
    }

    ComponentPtr<BillboardShrinkEffectCreator> BillboardShrinkEffectCreatorMaker::create()
    {
        return m_user->createComponent<BillboardShrinkEffectCreator>(m_param);
    }

    BillboardShrinkEffectCreatorMaker& BillboardShrinkEffectCreatorMaker::shrinkTargetPos(const tktkMath::Vector3& value)
    {
        // 値を設定して自身の参照を返す
        m_param.shrinkTargetPos = value;
        return *this;
    }

    BillboardShrinkEffectCreatorMaker& BillboardShrinkEffectCreatorMaker::shrinkTargetPosRandomRange(const tktkMath::Vector3& value)
    {
        // 値を設定して自身の参照を返す
        m_param.shrinkTargetPosRandomRange = value;
        return *this;
    }

    BillboardShrinkEffectCreatorMaker& BillboardShrinkEffectCreatorMaker::generateIntervalTimeSec(float value)
    {
        // 値を設定して自身の参照を返す
        m_param.generateIntervalTimeSec = value;
        return *this;
    }

    BillboardShrinkEffectCreatorMaker& BillboardShrinkEffectCreatorMaker::generateIntervalTimeRandomRange(float value)
    {
        // 値を設定して自身の参照を返す
        m_param.generateIntervalTimeRandomRange = value;
        return *this;
    }

    BillboardShrinkEffectCreatorMaker& BillboardShrinkEffectCreatorMaker::generateNumPerOnce(int value)
    {
        // 値を設定して自身の参照を返す
        m_param.generateNumPerOnce = value;
        return *this;
    }

    BillboardShrinkEffectCreatorMaker& BillboardShrinkEffectCreatorMaker::generateNumPerOnceRandomRange(int value)
    {
        // 値を設定して自身の参照を返す
        m_param.generateNumPerOnceRandomRange = value;
        return *this;
    }

    BillboardShrinkEffectCreatorMaker& BillboardShrinkEffectCreatorMaker::totalGenerateNum(int value)
    {
        // 値を設定して自身の参照を返す
        m_param.totalGenerateNum = value;
        return *this;
    }

    BillboardShrinkEffectCreatorMaker& BillboardShrinkEffectCreatorMaker::changeAvtiveToReset(bool value)
    {
        // 値を設定して自身の参照を返す
        m_param.changeAvtiveToReset = value;
        return *this;
    }

    BillboardShrinkEffectCreatorMaker& BillboardShrinkEffectCreatorMaker::billboardMaterialHandle(size_t value)
    {
        // 値を設定して自身の参照を返す
        m_param.useBillboardHandle = value;
        return *this;
    }

    BillboardShrinkEffectCreatorMaker& BillboardShrinkEffectCreatorMaker::billboardMaterialId(ResourceIdCarrier value)
    {
        // 値を設定して自身の参照を返す
        m_param.useBillboardHandle = DX12GameManager::getBillboardMaterialHandle(value);
        return *this;
    }

    BillboardShrinkEffectCreatorMaker& BillboardShrinkEffectCreatorMaker::billboardScale(const tktkMath::Vector2& value)
    {
        // 値を設定して自身の参照を返す
        m_param.billboardScale = value;
        return *this;
    }

    BillboardShrinkEffectCreatorMaker& BillboardShrinkEffectCreatorMaker::billboardScaleRandomRange(const tktkMath::Vector2& value)
    {
        // 値を設定して自身の参照を返す
        m_param.billboardScaleRandomRange = value;
        return *this;
    }

    BillboardShrinkEffectCreatorMaker& BillboardShrinkEffectCreatorMaker::billboardBlendRate(const tktkMath::Color& value)
    {
        // 値を設定して自身の参照を返す
        m_param.billboardBlendRate = value;
        return *this;
    }

    BillboardShrinkEffectCreatorMaker& BillboardShrinkEffectCreatorMaker::setChild(bool value)
    {
        // 値を設定して自身の参照を返す
        m_param.setChild = value;
        return *this;
    }

    BillboardShrinkEffectCreatorMaker& BillboardShrinkEffectCreatorMaker::lifeTimeSec(float value)
    {
        // 値を設定して自身の参照を返す
        m_param.lifeTimeSec = value;
        return *this;
    }

    BillboardShrinkEffectCreatorMaker& BillboardShrinkEffectCreatorMaker::lifeTimeSecRandomRange(float value)
    {
        // 値を設定して自身の参照を返す
        m_param.lifeTimeSecRandomRange = value;
        return *this;
    }

    BillboardShrinkEffectCreatorMaker& BillboardShrinkEffectCreatorMaker::moveSpeedPerSec(float value)
    {
        // 値を設定して自身の参照を返す
        m_param.moveSpeedPerSec = value;
        return *this;
    }

    BillboardShrinkEffectCreatorMaker& BillboardShrinkEffectCreatorMaker::moveSpeedPerSecRandomRange(float value)
    {
        // 値を設定して自身の参照を返す
        m_param.moveSpeedPerSecRandomRange = value;
        return *this;
    }
}