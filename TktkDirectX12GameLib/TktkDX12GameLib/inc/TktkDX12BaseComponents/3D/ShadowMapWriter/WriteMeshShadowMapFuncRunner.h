#ifndef WRITE_MESH_SHADOW_MAP_FUNC_RUNNER_H_
#define WRITE_MESH_SHADOW_MAP_FUNC_RUNNER_H_

/* base class */
#include "../../../TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentBase.h"

namespace tktk
{
	class WriteMeshShadowMapFuncRunner
		: public ComponentBase
	{
	public:

		WriteMeshShadowMapFuncRunner(size_t meshHandle, bool useBone);

	public:

		void start();
		void onDestroy();
		void draw() const;

	private:

		// カメラ情報定数バッファの更新
		void updateCameraCbuffer() const;

	private:

		// 骨を使った描画か？
		bool m_useBone;

		// 使用するリソースハンドル
		size_t m_meshHandle;

		// アップロード用バッファハンドル
		size_t m_createUploadCameraCbufferHandle{ 0U };
		size_t m_createUploadShadowMapCbufferHandle{ 0U };
	};
}
#endif // !WRITE_MESH_SHADOW_MAP_FUNC_RUNNER_H_
