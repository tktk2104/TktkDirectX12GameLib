#ifndef BILLBOARD_DRAW_FUNC_RUNNER_H_
#define BILLBOARD_DRAW_FUNC_RUNNER_H_

/* base class */
#include "../../../TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentBase.h"

namespace tktk
{
	struct BillboardDrawFuncRunnerInitParam;

	class BillboardDrawFuncRunner
		: public ComponentBase
	{
	public:

		BillboardDrawFuncRunner(size_t billboardHandle, const BillboardDrawFuncRunnerInitParam& initParam);

	public:

		void start();
		void onDestroy();
		void update();
		void draw() const;

	private:

		// カメラ情報定数バッファの更新
		void updateCameraCbuffer() const;

	private:

		// 使用するリソースハンドル
		size_t m_billboardHandle;
		size_t m_rtvDescriptorHeapHandle;
		size_t m_cameraHandle;

		// アップロード用バッファハンドル
		size_t m_createUploadCameraCbufferHandle{ 0U };
	};
}
#endif // !BILLBOARD_DRAW_FUNC_RUNNER_H_