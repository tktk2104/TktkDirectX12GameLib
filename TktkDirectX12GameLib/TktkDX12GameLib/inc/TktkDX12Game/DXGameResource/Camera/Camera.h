#ifndef CAMERA_H_
#define CAMERA_H_

#include <TktkContainer/HeapArray/HeapArray.h>
#include "CameraData.h"

namespace tktk
{
	// 「CameraData」を管理するクラス
	class Camera
	{
	public:

		Camera(unsigned int cameraNum);
		~Camera() = default;

	public:

		// 「CameraData」のインスタンスを作る
		void create(unsigned int id);

		// 指定のカメラのビュー行列を取得する
		const tktkMath::Matrix4& getViewMatrix(unsigned int id) const;

		// 指定のカメラのビュー行列を設定する
		void setViewMatrix(unsigned int id, const tktkMath::Matrix4& view);

		// 指定のカメラのプロジェクション行列を取得する
		const tktkMath::Matrix4& getProjectionMatrix(unsigned int id) const;

		// プ指定のカメラのロジェクション行列を設定する
		void setProjectionMatrix(unsigned int id, const tktkMath::Matrix4& projection);

	private:

		HeapArray<CameraData> m_cameraArray;
	};
}
#endif // !CAMERA_H_