#ifndef COMPONENTS_H_
#define COMPONENTS_H_

#include "2D/Transform2D/Transform2DMaker.h"
#include "2D/InertialMovement2D/InertialMovement2DMaker.h"
#include "2D/InertialRotatement2D/InertialRotatement2DMaker.h"
#include "2D/CircleCollider/CircleColliderMaker.h"
#include "2D/Polygon2dCollider/Polygon2dColliderMaker.h"
#include "2D/RectCollider/RectColliderMaker.h"
#include "2D/ColliderWireFrameDrawer2D/ColliderWireFrameDrawer2DMaker.h"
#include "2D/Line2dDrawer/Line2DDrawerMaker.h"
#include "2D/SpriteDrawer/SpriteDrawerMaker.h"
#include "2D/SpriteDrawer/SpriteClippingDrawerMaker.h"
#include "2D/PostEffectDrawer/PostEffectDrawerMaker.h"

#include "3D/Transform3D/Transform3DMaker.h"
#include "3D/InertialMovement3D/InertialMovement3DMaker.h"
#include "3D/SphereCollider/SphereColliderMaker.h"
#include "3D/BoxCollider/BoxColliderMaker.h"
#include "3D/ColliderWireFrameDrawer3D/ColliderWireFrameDrawer3DMaker.h"
#include "3D/Light/PointLightControllerMaker.h"
#include "3D/Light/DirectionalLightControllerMaker.h"
#include "3D/Camera/BasicCameraControllerMaker.h"
#include "3D/Camera/OrthographicCameraControllerMaker.h"
#include "3D/Camera/ShadowMapCameraControllerMaker.h"
#include "3D/Camera/FirstPersonModuleMaker.h"
#include "3D/BillboardDrawer/BillboardDrawerMaker.h"
#include "3D/MeshDrawer/MeshDrawerMaker.h"
#include "3D/MeshDrawer/MonoColorMeshDrawerMaker.h"
#include "3D/MeshAnimator/MeshAnimatorMaker.h"
#include "3D/MeshAnimator/MotionChangerMaker.h"
#include "3D/Effects/BillboardShrinkEffect/BillboardShrinkEffectCreatorMaker.h"
#include "3D/Effects/BillboardSpreadEffect/BillboardSpreadEffectCreatorMaker.h"

#include "Other/ReceiveMessageToSelfDestroyer/ReceiveMessageToSelfDestroyerMaker.h"
#include "Other/Sound/SoundPlayerMaker.h"
#include "Other/Sound/SoundPlayTimerMaker.h"

class TktkManual;

// 下の行のコメントアウトを外すと“F12”で対応するクラスに飛べます
//#define SAMPLE

#ifdef SAMPLE
namespace tktk
{
	/* ２次元コンポーネント達 */
	//<
		// ２次元座標、スケール、回転コンポーネント
		using C01 = Transform2D;

		// 簡易慣性２次元移動コンポーネント
		using C02 = InertialMovement2D;

		// 簡易慣性２次元回転コンポーネント
		using C03 = InertialRotatement2D;

		// 円の当たり判定コンポーネント
		using C04 = CircleCollider;

		// ２次元ポリゴン当たり判定コンポーネント
		using C05 = Polygon2dCollider;

		// 四角形の当たり判定コンポーネント
		using C06 = RectCollider;

		// ２次元衝突判定の境界を線描画するコンポーネント
		using C08 = ColliderWireFrameDrawer2D;

		// ２次元で線描画するコンポーネント
		using C09 = Line2DDrawer;

		// スプライト描画コンポーネント
		using C10 = SpriteDrawer;

		// スプライト切り抜き描画コンポーネント
		using C11 = SpriteClippingDrawer;

		// ポストエフェクト描画コンポーネント
		using C12 = PostEffectDrawer;
	//>



	/* ３次元コンポーネント達 */
	//<
		// ３次元座標、スケール、回転コンポーネント
		using C30 = Transform3D;

		// 簡易慣性３次元移動コンポーネント
		using C31 = InertialMovement3D;

		// 球の当たり判定コンポーネント
		using C32 = SphereCollider;

		// AABBの当たり判定コンポーネント
		using C33 = BoxCollider;

		// ２次元衝突判定の境界を線描画するコンポーネント
		using C34 = ColliderWireFrameDrawer3D;

		// ポイントライトの制御コンポーネント
		using C35 = PointLightController;

		// ディレクショナルライトの制御コンポーネント
		using C36 = DirectionalLightController;

		// 通常カメラの制御コンポーネント
		using C37 = BasicCameraController;

		// 平行投影カメラの制御コンポーネント
		using C38 = OrthographicCameraController;

		// １人称移動コンポーネント
		using C39 = FirstPersonModule;

		// ビルボード描画コンポーネント
		using C40 = BillboardDrawer;

		// メッシュの描画コンポーネント
		using C41 = MeshDrawer;

		// 単色メッシュの描画コンポーネント
		using C42 = MonoColorMeshDrawer;

		// メッシュのアニメーションコンポーネント
		using C43 = MeshAnimator;

		// モーション変更コンポーネント
		using C44 = MotionChanger;

		// 収縮するビルボードエフェクトコンポーネント
		using C45 = BillboardShrinkEffectCreator;

		// 拡散するビルボードエフェクトコンポーネント
		using C46 = BillboardSpreadEffectCreator;
	//>



	/* その他のコンポーネント達 */
	//<
		// 特定のメッセージを受け取った時に自身を持つGameObjectを殺すコンポーネント
		using C60 = ReceiveMessageToSelfDestroyer;

		// サウンド再生コンポーネント
		using C61 = SoundPlayer;
	//>
}
#endif // !SAMPLE

#endif // !COMPONENTS_H_