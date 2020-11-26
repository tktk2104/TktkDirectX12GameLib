#include "TktkDX12BaseComponents/3D/Effects/BillboardSpreadEffect/BillboardSpreadEffectCreatorMaker.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"

namespace tktk
{
    BillboardSpreadEffectCreatorMaker BillboardSpreadEffectCreatorMaker::m_self;

    BillboardSpreadEffectCreatorMaker& BillboardSpreadEffectCreatorMaker::makeStart(GameObjectPtr user)
    {
        // 変数を初期化する
        m_self = BillboardSpreadEffectCreatorMaker();

        // 引数のユーザーを設定
        m_self.m_user = user;

        // 自身の参照を返す
        return m_self;
    }

    ComponentPtr<BillboardSpreadEffectCreator> BillboardSpreadEffectCreatorMaker::create()
    {
        return m_user->createComponent<BillboardSpreadEffectCreator>(m_param);
    }

    BillboardSpreadEffectCreatorMaker& BillboardSpreadEffectCreatorMaker::generateLocalPos(const tktkMath::Vector3& value)
    {
        // 値を設定して自身の参照を返す
        m_param.generateLocalPos = value;
        return *this;
    }

    BillboardSpreadEffectCreatorMaker& BillboardSpreadEffectCreatorMaker::generateLocalPosRandomRange(const tktkMath::Vector3& value)
    {
        // 値を設定して自身の参照を返す
        m_param.generateLocalPosRandomRange = value;
        return *this;
    }

    BillboardSpreadEffectCreatorMaker& BillboardSpreadEffectCreatorMaker::firstGenerateTimeSec(float value)
    {
        // 値を設定して自身の参照を返す
        m_param.firstGenerateTimeSec = value;
        return *this;
    }

    BillboardSpreadEffectCreatorMaker& BillboardSpreadEffectCreatorMaker::generateIntervalTimeSec(float value)
    {
        // 値を設定して自身の参照を返す
        m_param.generateIntervalTimeSec = value;
        return *this;
    }

    BillboardSpreadEffectCreatorMaker& BillboardSpreadEffectCreatorMaker::generateIntervalTimeRandomRange(float value)
    {
        // 値を設定して自身の参照を返す
        m_param.generateIntervalTimeRandomRange = value;
        return *this;
    }

    BillboardSpreadEffectCreatorMaker& BillboardSpreadEffectCreatorMaker::generateNumPerOnce(int value)
    {
        // 値を設定して自身の参照を返す
        m_param.generateNumPerOnce = value;
        return *this;
    }

    BillboardSpreadEffectCreatorMaker& BillboardSpreadEffectCreatorMaker::generateNumPerOnceRandomRange(int value)
    {
        // 値を設定して自身の参照を返す
        m_param.generateNumPerOnceRandomRange = value;
        return *this;
    }

    BillboardSpreadEffectCreatorMaker& BillboardSpreadEffectCreatorMaker::totalGenerateNum(int value)
    {
        // 値を設定して自身の参照を返す
        m_param.totalGenerateNum = value;
        return *this;
    }

    BillboardSpreadEffectCreatorMaker& BillboardSpreadEffectCreatorMaker::changeAvtiveToReset(bool value)
    {
        // 値を設定して自身の参照を返す
        m_param.changeAvtiveToReset = value;
        return *this;
    }

    BillboardSpreadEffectCreatorMaker& BillboardSpreadEffectCreatorMaker::billboardMaterialHandle(size_t value)
    {
        // 値を設定して自身の参照を返す
        m_param.useBillboardHandle = value;
        return *this;
    }

    BillboardSpreadEffectCreatorMaker& BillboardSpreadEffectCreatorMaker::billboardMaterialId(ResourceIdCarrier value)
    {
        // 値を設定して自身の参照を返す
        m_param.useBillboardHandle = DX12GameManager::getBillboardMaterialHandle(value);
        return *this;
    }

    BillboardSpreadEffectCreatorMaker& BillboardSpreadEffectCreatorMaker::billboardScale(const tktkMath::Vector2& value)
    {
        // 値を設定して自身の参照を返す
        m_param.billboardScale = value;
        return *this;
    }

    BillboardSpreadEffectCreatorMaker& BillboardSpreadEffectCreatorMaker::billboardScaleRandomRange(const tktkMath::Vector2& value)
    {
        // 値を設定して自身の参照を返す
        m_param.billboardScaleRandomRange = value;
        return *this;
    }

    BillboardSpreadEffectCreatorMaker& BillboardSpreadEffectCreatorMaker::billboardBlendRate(const tktkMath::Color& value)
    {
        // 値を設定して自身の参照を返す
        m_param.billboardBlendRate = value;
        return *this;
    }

    BillboardSpreadEffectCreatorMaker& BillboardSpreadEffectCreatorMaker::setChild(bool value)
    {
        // 値を設定して自身の参照を返す
        m_param.setChild = value;
        return *this;
    }

    BillboardSpreadEffectCreatorMaker& BillboardSpreadEffectCreatorMaker::lifeTimeSec(float value)
    {
        // 値を設定して自身の参照を返す
        m_param.lifeTimeSec = value;
        return *this;
    }

    BillboardSpreadEffectCreatorMaker& BillboardSpreadEffectCreatorMaker::lifeTimeSecRandomRange(float value)
    {
        // 値を設定して自身の参照を返す
        m_param.lifeTimeSecRandomRange = value;
        return *this;
    }

    BillboardSpreadEffectCreatorMaker& BillboardSpreadEffectCreatorMaker::moveSpeedPerSec(float value)
    {
        // 値を設定して自身の参照を返す
        m_param.moveSpeedPerSec = value;
        return *this;
    }

    BillboardSpreadEffectCreatorMaker& BillboardSpreadEffectCreatorMaker::moveSpeedPerSecRandomRange(float value)
    {
        // 値を設定して自身の参照を返す
        m_param.moveSpeedPerSecRandomRange = value;
        return *this;
    }
}