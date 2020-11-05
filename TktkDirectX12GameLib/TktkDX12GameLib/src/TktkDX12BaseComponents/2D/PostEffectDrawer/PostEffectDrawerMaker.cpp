#include "TktkDX12BaseComponents/2D/PostEffectDrawer/PostEffectDrawerMaker.h"

namespace tktk
{
	PostEffectDrawerMaker PostEffectDrawerMaker::m_self;

	PostEffectDrawerMaker& PostEffectDrawerMaker::makeStart(GameObjectPtr user)
	{
		// 変数を初期化する
		m_self = PostEffectDrawerMaker();
		
		// 引数のユーザーを設定
		m_self.m_user = user;

		// 使用するレンダーターゲットのディスクリプタヒープハンドルのデフォルト値はバックバッファ
		m_self.m_useRtvDescriptorHeapHandle = DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::BackBuffer);

		// 自身の参照を返す
		return m_self;
	}

	PostEffectDrawerMaker& PostEffectDrawerMaker::makeStart(const StateTypeHierarchy& targetState, GameObjectPtr user)
	{
		// 変数を初期化する
		m_self = PostEffectDrawerMaker();

		// 引数のユーザーを設定
		m_self.m_user = user;

		// 引数の追加階層を設定
		m_self.m_targetState = targetState;

		// 使用するレンダーターゲットのディスクリプタヒープハンドルのデフォルト値はバックバッファ
		m_self.m_useRtvDescriptorHeapHandle = DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::BackBuffer);

		// 自身の参照を返す
		return m_self;
	}

	ComponentPtr<PostEffectDrawer> PostEffectDrawerMaker::create()
	{
		// 自身を追加する階層情報が空だったら普通に作成する
		if (m_targetState.hierarchy.empty())
		{
			// コンポーネントを作成してそのポインタを返す
			return m_user->createComponent<PostEffectDrawer>(
				m_drawPriority,
				m_postEffectMaterialHandle,
				m_useRtvDescriptorHeapHandle
				);
		}

		// コンポーネントを作成する
		auto createComponent = m_user->createComponent<PostEffectDrawer>(
			m_drawPriority,
			m_postEffectMaterialHandle,
			m_useRtvDescriptorHeapHandle
			);

		// 作成したコンポーネントを特定のステートに追加する
		m_user->setComponentToStateMachine(m_targetState, createComponent);

		// 作成したコンポーネントのポインタを返す
		return createComponent;
	}

	PostEffectDrawerMaker& PostEffectDrawerMaker::drawPriority(float value)
	{
		// 値を設定して自身の参照を返す
		m_drawPriority = value;
		return *this;
	}

	PostEffectDrawerMaker& PostEffectDrawerMaker::useRtvDescriptorHeapId(unsigned int value)
	{
		// 値を設定して自身の参照を返す
		m_useRtvDescriptorHeapHandle = value;
		return *this;
	}

	PostEffectDrawerMaker& PostEffectDrawerMaker::postEffectMaterialHandle(unsigned int value)
	{
		// 値を設定して自身の参照を返す
		m_postEffectMaterialHandle = value;
		return *this;
	}

	PostEffectDrawerMaker& PostEffectDrawerMaker::postEffectMaterialId(ResourceIdCarrier value)
	{
		// 値を設定して自身の参照を返す
		m_postEffectMaterialHandle = DX12GameManager::getPostEffectMaterialHandle(value);
		return *this;
	}
}