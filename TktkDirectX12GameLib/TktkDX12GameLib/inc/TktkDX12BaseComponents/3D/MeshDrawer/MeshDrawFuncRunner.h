#ifndef MESH_DRAW_FUNC_RUNNER_H_
#define MESH_DRAW_FUNC_RUNNER_H_

/* base class */
#include "../../../TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentBase.h"

namespace tktk
{
	struct MeshDrawFuncRunnerInitParam;

	class MeshDrawFuncRunner
		: public ComponentBase
	{
	public:

		MeshDrawFuncRunner(size_t meshHandle, const MeshDrawFuncRunnerInitParam& initParam);

	public:

		void start();
		void onDestroy();
		void update();
		void draw() const;

	private:

		// カメラ情報定数バッファの更新
		void updateCameraCbuffer() const;

		// シャドウマップ用の定数バッファの更新
		void updateShadowMapCbuffer() const;

	private:

		// 骨を使った描画か？
		bool m_useBone;

		// 使用するリソースハンドル
		size_t m_meshHandle;
		size_t m_rtvDescriptorHeapHandle;
		size_t m_lightHandle;
		size_t m_cameraHandle;
		size_t m_shadowMapCameraHandle;

		size_t m_skeletonHandle{ 0U };
		size_t m_createUploadBoneMatrixCbufferHandle{ 0U };

		// アップロード用バッファハンドル
		size_t m_createUploadCameraCbufferHandle	{ 0U };
		size_t m_createUploadShadowMapCbufferHandle	{ 0U };
	};
}
#endif // !MESH_DRAW_FUNC_RUNNER_H_