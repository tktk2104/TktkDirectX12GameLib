#ifndef DRAW_3D_PARAMETERS_H_
#define DRAW_3D_PARAMETERS_H_

/* std::unique_ptr */
#include <memory>

/* funcUseType */
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Vector3.h>
#include <TktkMath/Structs/Matrix4.h>

namespace tktk
{
	class LightManager;
	class CameraManager;
	struct Draw3DParametersInitParam;

	// 3D描画に必要なパラメータを管理するクラス
	class Draw3DParameters
	{
	public:

		explicit Draw3DParameters(const Draw3DParametersInitParam& initParam);
		~Draw3DParameters();

	public: /* カメラ関係の処理 */

		// カメラを作り、そのリソースのハンドルを返す
		size_t createCamera();

		// 指定のカメラのビュー行列を取得する
		const tktkMath::Matrix4& getViewMatrix(size_t handle) const;

		// 指定のカメラのビュー行列を設定する
		void setViewMatrix(size_t handle, const tktkMath::Matrix4& view);

		// 指定のカメラのプロジェクション行列を取得する
		const tktkMath::Matrix4& getProjectionMatrix(size_t handle) const;

		// 指定のカメラのプロジェクション行列を設定する
		void setProjectionMatrix(size_t handle, const tktkMath::Matrix4& projection);

	public: /* ライト関係の処理 */

		// ライトを作り、そのリソースのハンドルを返す
		size_t createLight(
			const tktkMath::Color& ambient,
			const tktkMath::Color& diffuse,
			const tktkMath::Color& speqular,
			const tktkMath::Vector3& position
		);

		// ライト情報の定数バッファを更新する
		void updateLightCBuffer(size_t handle) const;

		// 指定のライトの環境光を設定する
		void setLightAmbient(size_t handle, const tktkMath::Color& ambient);

		// 指定のライトの拡散反射光を設定する
		void setLightDiffuse(size_t handle, const tktkMath::Color& diffuse);

		// 指定のライトの鏡面反射光を設定する
		void setLightSpeqular(size_t handle, const tktkMath::Color& speqular);

		// 指定のライトの座標を設定する
		void setLightPosition(size_t handle, const tktkMath::Vector3& position);

	private:

		std::unique_ptr<LightManager>	m_light;
		std::unique_ptr<CameraManager> m_camera;
	};
}
#endif // !DRAW_3D_PARAMETERS_H_