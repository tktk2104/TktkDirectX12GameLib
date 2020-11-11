#include "TktkDX12BaseComponents/2D/Line2dDrawer/Line2DDrawerMaker.h"

#include "TktkDX12Game/_MainManager/DX12GameManager.h"
#include "TktkDX12Game/DXGameResource/GameObjectResouse/GameObject/GameObject.h"

namespace tktk
{
	Line2DDrawerMaker Line2DDrawerMaker::m_self;

	Line2DDrawerMaker & Line2DDrawerMaker::makeStart(GameObjectPtr user)
	{
		// 変数を初期化する
		m_self = Line2DDrawerMaker();

		// 引数のユーザーを設定
		m_self.m_user = user;

		// 使用するレンダーターゲットのディスクリプタヒープハンドルのデフォルト値はバックバッファ
		m_self.m_useRtvDescriptorHeapHandle = DX12GameManager::getSystemHandle(SystemRtvDescriptorHeapType::BackBuffer);

		// 自身の参照を返す
		return m_self;
	}

	ComponentPtr<Line2DDrawer> Line2DDrawerMaker::create()
	{
		// コンポーネントを作成する
		return m_user->createComponent<Line2DDrawer>(
			m_drawPriority,
			m_lineVertexArray,
			m_lineColor,
			m_blendRate,
			m_useRtvDescriptorHeapHandle
			);
	}

	Line2DDrawerMaker & Line2DDrawerMaker::drawPriority(float value)
	{
		m_drawPriority = value;
		return *this;
	}

	Line2DDrawerMaker & Line2DDrawerMaker::lineVertexArray(const std::vector<tktkMath::Vector2>& value)
	{
		// 値を設定して自身の参照を返す
		m_lineVertexArray = value;
		return *this;
	}

	Line2DDrawerMaker & Line2DDrawerMaker::lineColor(const tktkMath::Color & value)
	{
		// 値を設定して自身の参照を返す
		m_lineColor = value;
		return *this;
	}

	Line2DDrawerMaker & Line2DDrawerMaker::blendRate(const tktkMath::Color & value)
	{
		// 値を設定して自身の参照を返す
		m_blendRate = value;
		return *this;
	}

	Line2DDrawerMaker& Line2DDrawerMaker::useRtvDescriptorHeapHandle(size_t value)
	{
		// 値を設定して自身の参照を返す
		m_useRtvDescriptorHeapHandle = value;
		return *this;
	}
}