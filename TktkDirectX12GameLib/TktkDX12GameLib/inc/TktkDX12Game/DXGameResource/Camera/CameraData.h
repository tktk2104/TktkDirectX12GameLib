#ifndef CAMERA_DATA_H_
#define CAMERA_DATA_H_

#include <TktkMath/Structs/Matrix4.h>

namespace tktk
{
	// カメラ情報を管理するクラス
	class CameraData
	{
	public:

		CameraData() = default;
		~CameraData() = default;

	public:

		// ビュー行列を取得する
		const tktkMath::Matrix4& getViewMatrix() const;

		// ビュー行列を設定する
		void setViewMatrix(const tktkMath::Matrix4& view);

		// プロジェクション行列を取得する
		const tktkMath::Matrix4& getProjectionMatrix() const;

		// プロジェクション行列を設定する
		void setProjectionMatrix(const tktkMath::Matrix4& projection);

	private:

		tktkMath::Matrix4 m_viewMatrix			{ tktkMath::Matrix4_v::identity };
		tktkMath::Matrix4 m_projectionMatrix	{ tktkMath::Matrix4_v::identity };
	};
}
#endif // !CAMERA_DATA_H_
