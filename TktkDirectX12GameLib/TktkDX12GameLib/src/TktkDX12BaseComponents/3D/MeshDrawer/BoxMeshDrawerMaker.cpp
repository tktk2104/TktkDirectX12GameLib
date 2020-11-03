#include "TktkDX12BaseComponents/3D/MeshDrawer/BoxMeshDrawerMaker.h"

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

    BoxMeshDrawerMaker& BoxMeshDrawerMaker::makeStart(const StateTypeHierarchy& targetState, GameObjectPtr user)
    {
        // 変数を初期化する
        m_self = BoxMeshDrawerMaker();

        // 引数のユーザーを設定
        m_self.m_user = user;

        // 引数の追加階層を設定
        m_self.m_targetState = targetState;

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
        // 自身を追加する階層情報が空だったら普通に作成する
        if (m_targetState.hierarchy.empty())
        {
            // コンポーネントを作成してそのポインタを返す
            return m_user->createComponent<BoxMeshDrawer>(
                m_drawPriority,
                m_boxSize,
                m_localPosition,
                m_albedoColor,
                m_useResourceHandles
                );
        }

        // コンポーネントを作成する
        auto createComponent = m_user->createComponent<BoxMeshDrawer>(
            m_drawPriority,
            m_boxSize,
            m_localPosition,
            m_albedoColor,
            m_useResourceHandles
            );

        // 作成したコンポーネントを特定のステートに追加する
        m_user->setComponentToStateMachine(m_targetState, createComponent);

        // 作成したコンポーネントのポインタを返す
        return createComponent;
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

    BoxMeshDrawerMaker& BoxMeshDrawerMaker::useRtvDescriptorHeapHandle(unsigned int value)
    {
        // 値を設定して自身の参照を返す
        m_useResourceHandles.rtvDescriptorHeapHandle = value;
        return *this;
    }

    BoxMeshDrawerMaker& BoxMeshDrawerMaker::cameraHandle(unsigned int value)
    {
        // 値を設定して自身の参照を返す
        m_useResourceHandles.cameraHandle = value;
        return *this;
    }

    BoxMeshDrawerMaker& BoxMeshDrawerMaker::shadowMapCameraHandle(unsigned int value)
    {
        // 値を設定して自身の参照を返す
        m_useResourceHandles.shadowMapCameraHandle = value;
        return *this;
    }

    BoxMeshDrawerMaker& BoxMeshDrawerMaker::lightHandle(unsigned int value)
    {
        // 値を設定して自身の参照を返す
        m_useResourceHandles.lightHandle = value;
        return *this;
    }

    BoxMeshDrawerMaker& BoxMeshDrawerMaker::cameraIdImpl(int value)
    {
        // 値を設定して自身の参照を返す
        m_useResourceHandles.cameraHandle = DX12GameManager::getCameraHandle(value);
        return *this;
    }

    BoxMeshDrawerMaker& BoxMeshDrawerMaker::shadowMapCameraIdImpl(int value)
    {
        // 値を設定して自身の参照を返す
        m_useResourceHandles.shadowMapCameraHandle = DX12GameManager::getCameraHandle(value);
        return *this;
    }

    BoxMeshDrawerMaker& BoxMeshDrawerMaker::lightIdImpl(int value)
    {
        // 値を設定して自身の参照を返す
        m_useResourceHandles.lightHandle = DX12GameManager::getLightHandle(value);
        return *this;
    }
}