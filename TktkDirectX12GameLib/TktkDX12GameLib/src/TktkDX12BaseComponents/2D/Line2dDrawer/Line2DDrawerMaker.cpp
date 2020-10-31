#include "TktkDX12BaseComponents/2D/Line2dDrawer/Line2DDrawerMaker.h"

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
		// 自身を追加する階層情報が空だったら普通に作成する
		if (m_targetState.empty())
		{
			// コンポーネントを作成してそのポインタを返す
			return m_user->createComponent<Line2DDrawer>(
				m_drawPriority,
				m_lineVertexArray,
				m_lineColor,
				m_blendRate,
				m_useRtvDescriptorHeapHandle
				);
		}

		// コンポーネントを作成する
		auto createComponent = m_user->createComponent<Line2DDrawer>(
			m_drawPriority,
			m_lineVertexArray,
			m_lineColor,
			m_blendRate,
			m_useRtvDescriptorHeapHandle
			);

		// 作成したコンポーネントを特定のステートに追加する
		m_user->setComponentToStateMachine(m_targetState, createComponent);

		// 作成したコンポーネントのポインタを返す
		return createComponent;
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

	Line2DDrawerMaker& Line2DDrawerMaker::useRtvDescriptorHeapHandle(unsigned int value)
	{
		// 値を設定して自身の参照を返す
		m_useRtvDescriptorHeapHandle = value;
		return *this;
	}
}