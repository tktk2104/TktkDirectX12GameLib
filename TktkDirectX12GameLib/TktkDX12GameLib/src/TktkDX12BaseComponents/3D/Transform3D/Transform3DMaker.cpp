#include "TktkDX12BaseComponents/3D/Transform3D/Transform3DMaker.h"

namespace tktk
{
	Transform3DMaker Transform3DMaker::m_self;

	Transform3DMaker& Transform3DMaker::makeStart(GameObjectPtr user)
	{
		// 変数を初期化する
		m_self = Transform3DMaker();

		// 引数のユーザーを設定
		m_self.m_user = user;

		// 自身の参照を返す
		return m_self;
	}

	ComponentPtr<Transform3D> Transform3DMaker::create()
	{
		// 自身を追加する階層情報が空だったら普通に作成する
		if (m_targetState.empty())
		{
			// コンポーネントを作成してそのポインタを返す
			return m_user->createComponent<Transform3D>(
				m_initPosition,
				m_initScaleRate,
				m_initRotation,
				m_traceType
				);
		}

		// コンポーネントを作成する
		auto createComponent = m_user->createComponent<Transform3D>(
			m_initPosition,
			m_initScaleRate,
			m_initRotation,
			m_traceType
			);

		// 作成したコンポーネントを特定のステートに追加する
		m_user->setComponentToStateMachine(m_targetState, createComponent);

		// 作成したコンポーネントのポインタを返す
		return createComponent;
	}

	Transform3DMaker& Transform3DMaker::initPosition(const tktkMath::Vector3& value)
	{
		// 値を設定して自身の参照を返す
		m_initPosition = value;
		return *this;
	}

	Transform3DMaker& Transform3DMaker::initScaleRate(const tktkMath::Vector3& value)
	{
		// 値を設定して自身の参照を返す
		m_initScaleRate = value;
		return *this;
	}

	Transform3DMaker& Transform3DMaker::initRotation(const tktkMath::Quaternion& value)
	{
		// 値を設定して自身の参照を返す
		m_initRotation = value;
		return *this;
	}

	Transform3DMaker& Transform3DMaker::initRotation(const tktkMath::Vector3& value)
	{
		// クオータニオンに変換した値を設定して自身の参照を返す
		m_initRotation = tktkMath::Quaternion::createFromEulerAngle(value);
		return *this;
	}

	Transform3DMaker& Transform3DMaker::setInitTransformFromMatrix(const tktkMath::Matrix4& value)
	{
		// 値を設定して自身の参照を返す
		m_initPosition = value.calculateTranslation();
		m_initScaleRate = value.calculateScale();
		m_initRotation = value.calculateRotation();
		return *this;
	}

	Transform3DMaker& Transform3DMaker::traceType(TraceParentType value)
	{
		// 値を設定して自身の参照を返す
		m_traceType = value;
		return *this;
	}
}