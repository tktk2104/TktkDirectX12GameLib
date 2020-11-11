#include "TktkDX12BaseComponents/2D/PostEffectDrawer/PostEffectDrawerMaker.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"

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

	ComponentPtr<PostEffectDrawer> PostEffectDrawerMaker::create()
	{
		// コンポーネントを作成する
		return m_user->createComponent<PostEffectDrawer>(
			m_drawPriority,
			m_postEffectMaterialHandle,
			m_useRtvDescriptorHeapHandle
			);
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