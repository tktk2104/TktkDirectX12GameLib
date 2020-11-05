#ifndef CAMERA_H_
#define CAMERA_H_

#include <TktkContainer/ResourceContainer/ResourceContainer.h>
#include "CameraData.h"

namespace tktk
{
	// 「CameraData」を管理するクラス
	class Camera
	{
	public:

		explicit Camera(const tktkContainer::ResourceContainerInitParam& initParam);
		~Camera() = default;

	public:

		// 「CameraData」のインスタンスを作り、そのリソースのハンドルを返す
		size_t create();

		// 指定のカメラのビュー行列を取得する
		const tktkMath::Matrix4& getViewMatrix(size_t handle) const;

		// 指定のカメラのビュー行列を設定する
		void setViewMatrix(size_t handle, const tktkMath::Matrix4& view);

		// 指定のカメラのプロジェクション行列を取得する
		const tktkMath::Matrix4& getProjectionMatrix(size_t handle) const;

		// プ指定のカメラのロジェクション行列を設定する
		void setProjectionMatrix(size_t handle, const tktkMath::Matrix4& projection);

	private:

		tktkContainer::ResourceContainer<CameraData> m_cameraArray;
	};
}
#endif // !CAMERA_H_