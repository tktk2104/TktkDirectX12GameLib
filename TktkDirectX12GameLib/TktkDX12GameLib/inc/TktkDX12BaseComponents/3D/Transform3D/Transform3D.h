#ifndef TRANSFORM_3D_H_
#define TRANSFORM_3D_H_

/* base class */
#include "../../../TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentBase.h"

/* funcUseType */
#include <TktkMath/Structs/Matrix4.h>

/* class member */
#include <TktkMath/Structs/Quaternion.h>
#include <TktkMath/Structs/Vector3.h>
#include "../../2D/Transform2D/TraceParentType.h"

namespace tktk
{
	// ３次元の自身の座標、回転、スケールを管理するコンポーネント
	class Transform3D
		: public ComponentBase
	{
	public:

		Transform3D(
			const tktkMath::Vector3& initPosition,	// 初期座標
			const tktkMath::Vector3& initScaleRate,	// 初期スケール
			const tktkMath::Quaternion& initRotation,	// 初期回転
			TraceParentType traceType		// 親のTransform2Dとの関係性の種類
		);

	public:

		// <PolymorphismFunc>
		void start();
		void afterChangeParent(const GameObjectPtr& beforParent);

	public:

		// ワールド座標を取得
		const tktkMath::Vector3& getWorldPosition() const;
		// ワールドスケールを取得
		const tktkMath::Vector3& getWorldScaleRate() const;
		// ワールド回転を取得
		const tktkMath::Quaternion& getWorldRotation() const;
		// ワールド回転（オイラー角）を計算
		tktkMath::Vector3 calculateWorldEulerAngles() const;

		// ローカル座標を取得
		const tktkMath::Vector3& getLocalPosition() const;
		// ローカルスケールを取得
		const tktkMath::Vector3& getLocalScaleRate() const;
		// ローカル回転を取得
		const tktkMath::Quaternion& getLocalRotation() const;
		// ローカル回転（オイラー角）を計算
		tktkMath::Vector3 calculateLocalEulerAngles() const;

		// ワールドの行列を計算
		tktkMath::Matrix4 calculateWorldMatrix() const;
		// ローカルの行列を計算
		tktkMath::Matrix4 calculateLocalMatrix() const;

		// ワールド座標を指定分だけ増加
		void addWorldPosition(const tktkMath::Vector3& position);
		// ワールド回転を指定分だけ増加
		void addWorldRotation(const tktkMath::Quaternion& rotation);
		// ワールド回転（オイラー角）を指定分だけ増加
		void addWorldEulerAngles(const tktkMath::Vector3& eulerAngles);

		// ローカル座標を指定分だけ増加
		void addLocalPosition(const tktkMath::Vector3& position);
		// ローカルスケールを指定分だけ増加
		void addLocalScaleRate(const tktkMath::Vector3& scaleRate);
		// ローカル回転を指定分だけ増加
		void addLocalRotation(const tktkMath::Quaternion& rotation);
		// ローカル回転（オイラー角）を指定分だけ増加
		void addLocalEulerAngles(const tktkMath::Vector3& eulerAngles);

		// ワールド座標を設定
		void setWorldPosition(const tktkMath::Vector3& position);
		// ワールド回転を設定
		void setWorldRotation(const tktkMath::Quaternion& rotation);
		// ワールド回転（オイラー角）を設定
		void setWorldEulerAngles(const tktkMath::Vector3& eulerAngles);
		// 「axis」を軸として「degree」度だけ回転したワールド回転を設定
		void setWorldAxisAngle(const tktkMath::Vector3& axis, float degree);

		// ローカル座標を設定
		void setLocalPosition(const tktkMath::Vector3& position);
		// ローカルスケールを設定
		void setLocalScaleRate(const tktkMath::Vector3& scaleRate);
		// ローカル回転を設定
		void setLocalRotation(const tktkMath::Quaternion& rotation);
		// ローカル回転（オイラー角）を設定
		void setLocalEulerAngles(const tktkMath::Vector3& eulerAngles);
		// 「axis」を軸として「degree」度だけ回転したローカル回転を設定
		void setLocalAxisAngle(const tktkMath::Vector3& axis, float degree);

	public:

		// ワールド空間の左手座標系の前方ベクトルを計算（DirectX等）
		tktkMath::Vector3 calculateWorldForwardLH() const;
		// ワールド空間の右手座標系の前方ベクトルを計算（OpenGL等）
		tktkMath::Vector3 calculateWorldForwardRH() const;
		// ワールド空間の右方ベクトルを計算
		tktkMath::Vector3 calculateWorldRight() const;
		// ワールド空間の上方ベクトルを計算
		tktkMath::Vector3 calculateWorldUp() const;

		// ワールド空間の左手座標系の前方ベクトルを計算（DirectX等）
		tktkMath::Vector3 calculateLocalForwardLH() const;
		// ワールド空間の右手座標系の前方ベクトルを計算（OpenGL等）
		tktkMath::Vector3 calculateLocalForwardRH() const;
		// ワールド空間の右方ベクトルを計算
		tktkMath::Vector3 calculateLocalRight() const;
		// ワールド空間の上方ベクトルを計算
		tktkMath::Vector3 calculateLocalUp() const;

		// ワールド空間の左手座標系の前方ベクトルを設定（DirectX等）
		void setWorldForwardLH(const tktkMath::Vector3& forward);
		// ワールド空間の右手座標系の前方ベクトルを設定（OpenGL等）
		void setWorldForwardRH(const tktkMath::Vector3& forward);
		// ワールド空間の右方ベクトルを設定
		void setWorldRight(const tktkMath::Vector3& right);
		// ワールド空間の上方ベクトルを設定
		void setWorldUp(const tktkMath::Vector3& up);

		// ローカル空間の左手座標系の前方ベクトルを設定（DirectX等）
		void setLocalForwardLH(const tktkMath::Vector3& forward);
		// ローカル空間の右手座標系の前方ベクトルを設定（OpenGL等）
		void setLocalForwardRH(const tktkMath::Vector3& forward);
		// ローカル空間の右方ベクトルを設定
		void setLocalRight(const tktkMath::Vector3& right);
		// ローカル空間の上方ベクトルを設定
		void setLocalUp(const tktkMath::Vector3& up);

		// 指定のTransform3Dの方を向くように自身のワールド行列を変換する
		void lookAt(const ComponentPtr<Transform3D>& target);
		// 指定の座標の方を向くように自身のワールド行列を変換する
		void lookAt(const tktkMath::Vector3& target);

		// 指定の座標を中心とした軸で指定した角度だけ回転させる。
		void rotateAround(const tktkMath::Vector3& worldPoint, const tktkMath::Vector3& axis, float angle);

		//// ローカル座標からワールド座標へと変換した行列を取得する
		//Matrix4 calculateLocalToWorldMatrix() const;
		//// ワールド座標からローカル座標へと変換した行列を取得する
		//Matrix4 calculateWorldToLocalMatrix() const;

	private:

		// 引数のTransform3Dを追従するのに使用するワールド行列を計算
		static tktkMath::Matrix4 calculateTraceUseMat(const ComponentPtr<Transform3D>& target, TraceParentType traceType);

		// 引数のTransform3Dを追従するのに使用するスケール値を計算
		static tktkMath::Vector3 calculateTraceUseScale(const ComponentPtr<Transform3D>& target, TraceParentType traceType);

		// 引数のTransform3Dを追従するのに使用する逆スケール値を計算
		static tktkMath::Vector3 calculateTraceUseInvScale(const ComponentPtr<Transform3D>& target, TraceParentType traceType);

	private:

		// 新しいローカル行列を指定して自身のローカルのトランスフォームを更新する
		void updateLocalTransform(const tktkMath::Matrix4& newLocalMat, const tktkMath::Vector3 newLocalScale);

		// 新しいワールド行列を指定して自身のワールドのトランスフォームを更新する
		void updateWorldTransform(const tktkMath::Matrix4& newWorldMat, const tktkMath::Vector3 newWorldScale);

		// 親のTransform3Dを探す
		ComponentPtr<Transform3D> findParentTransform3D() const;

		// 全ての子供のTransform3Dを更新する
		void updateAllChildTransform();

		// 指定した子供のTransform3Dを更新する
		void updateChildTransform(const GameObjectPtr& child);

		// 親のTransform3Dの追従を開始
		void enableParentTransform(const GameObjectPtr& curParent);

		// 親のTransform3Dの追従を終了
		void disableParentTransform(const GameObjectPtr& beforParent);

		// 大元のTransformから全ての子供を更新する（生ポインタ版）
		void findAndUpdateRootTransform(Transform3D* curTransform);

		// 大元のTransformから全ての子供を更新する（CfpPtr版）
		void findAndUpdateRootTransform(const ComponentPtr<Transform3D>& curTransform);

	private:

		// ローカルの座標
		tktkMath::Vector3 m_localPosition{ tktkMath::Vector3_v::zero };
		// ローカルのスケール
		tktkMath::Vector3 m_localScaleRate{ tktkMath::Vector3_v::one };
		// ローカルの回転
		tktkMath::Quaternion m_localRotation{ tktkMath::Quaternion_v::identity };

		// ワールドの座標
		tktkMath::Vector3 m_worldPosition{ tktkMath::Vector3_v::zero };
		// ワールドのスケール
		tktkMath::Vector3 m_worldScaleRate{ tktkMath::Vector3_v::one };
		// ローカルの回転
		tktkMath::Quaternion m_worldRotation{ tktkMath::Quaternion_v::identity };

		// 親のTransform3Dとの関係性
		TraceParentType m_traceType;
	};
}
#endif // !TRANSFORM_3D_H_