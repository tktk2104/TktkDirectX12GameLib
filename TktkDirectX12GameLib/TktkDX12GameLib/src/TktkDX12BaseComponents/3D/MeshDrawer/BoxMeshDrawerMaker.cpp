#include "TktkDX12BaseComponents/3D/MeshDrawer/BoxMeshDrawerMaker.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"

namespace tktk
{
    BoxMeshDrawerMaker BoxMeshDrawerMaker::m_self;

    BoxMeshDrawerMaker& BoxMeshDrawerMaker::makeStart(GameObjectPtr user)
    {
        // 変数を初期化する
        m_self = BoxMeshDrawerMaker();

        // 引数のユーザーを設定
        m_self.m_user = user;

        // 使用するカメラハンドルのデフォルト値はデフォルト通常カメラ
        m_self.m_useResourceHandles.cameraHandle = DX12GameManager::getSystemHandle(SystemCameraType::DefaultCamera);

        // 使用するシャドウマップカメラハンドルのデフォルト値はデフォルトシャドウマップカメラ
        m_self.m_useResourceHandles.shadowMapCameraHandle = DX12GameManager::getSystemHandle(SystemCameraType::DefaultShadowMapCamera);

        // 使用するライトハンドルのデフォルト値はデフォルトライト
        m_self.m_useResourceHandles.lightHandle = DX12GameManager::getSystemHandle(SystemLightType::DefaultLight);

        // 使用するレンダーターゲットのディスクリプタヒープハンドルのデフォルト値はバックバッファ
        m_self.m_useResourceHandles.rtvDescriptorHeapHandle = DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::BackBuffer);

        // 自身の参照を返す
        return m_self;
    }

    ComponentPtr<BoxMeshDrawer> BoxMeshDrawerMaker::create()
    {
        // コンポーネントを作成する
        return m_user->createComponent<BoxMeshDrawer>(
            m_drawPriority,
            m_boxSize,
            m_localPosition,
            m_albedoColor,
            m_useResourceHandles
            );
    }

    BoxMeshDrawerMaker& BoxMeshDrawerMaker::drawPriority(float value)
    {
        // 値を設定して自身の参照を返す
        m_drawPriority = value;
        return *this;
    }

    BoxMeshDrawerMaker& BoxMeshDrawerMaker::boxSize(const tktkMath::Vector3& value)
    {
        // 値を設定して自身の参照を返す
        m_boxSize = value;
        return *this;
    }

    BoxMeshDrawerMaker& BoxMeshDrawerMaker::localPosition(const tktkMath::Vector3& value)
    {
        // 値を設定して自身の参照を返す
        m_localPosition = value;
        return *this;
    }

    BoxMeshDrawerMaker& BoxMeshDrawerMaker::albedoColor(const tktkMath::Color& value)
    {
        // 値を設定して自身の参照を返す
        m_albedoColor = value;
        return *this;
    }

    BoxMeshDrawerMaker& BoxMeshDrawerMaker::useRtvDescriptorHeapHandle(size_t value)
    {
        // 値を設定して自身の参照を返す
        m_useResourceHandles.rtvDescriptorHeapHandle = value;
        return *this;
    }

    BoxMeshDrawerMaker& BoxMeshDrawerMaker::cameraHandle(size_t value)
    {
        // 値を設定して自身の参照を返す
        m_useResourceHandles.cameraHandle = value;
        return *this;
    }

    BoxMeshDrawerMaker& BoxMeshDrawerMaker::cameraId(ResourceIdCarrier value)
    {
        // 値を設定して自身の参照を返す
        m_useResourceHandles.cameraHandle = DX12GameManager::getCameraHandle(value);
        return *this;
    }

    BoxMeshDrawerMaker& BoxMeshDrawerMaker::shadowMapCameraHandle(size_t value)
    {
        // 値を設定して自身の参照を返す
        m_useResourceHandles.shadowMapCameraHandle = value;
        return *this;
    }

    BoxMeshDrawerMaker& BoxMeshDrawerMaker::shadowMapCameraId(ResourceIdCarrier value)
    {
        // 値を設定して自身の参照を返す
        m_useResourceHandles.shadowMapCameraHandle = DX12GameManager::getCameraHandle(value);
        return *this;
    }

    BoxMeshDrawerMaker& BoxMeshDrawerMaker::lightHandle(size_t value)
    {
        // 値を設定して自身の参照を返す
        m_useResourceHandles.lightHandle = value;
        return *this;
    }

    BoxMeshDrawerMaker& BoxMeshDrawerMaker::lightId(ResourceIdCarrier value)
    {
        // 値を設定して自身の参照を返す
        m_useResourceHandles.lightHandle = DX12GameManager::getLightHandle(value);
        return *this;
    }
}