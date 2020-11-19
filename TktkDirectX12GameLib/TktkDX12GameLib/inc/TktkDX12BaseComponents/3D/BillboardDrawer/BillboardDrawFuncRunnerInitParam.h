#ifndef BILLBOARD_DRAW_FUNC_RUNNER_INIT_PARAM_H_
#define BILLBOARD_DRAW_FUNC_RUNNER_INIT_PARAM_H_

#include "TktkDX12Game/UtilityProcessManager/ResourceHandleGetter/ResourceIdConverter/ResourceIdCarrier.h"

namespace tktk
{
	struct BillboardDrawFuncRunnerInitParam
	{
	public:

		static BillboardDrawFuncRunnerInitParam& create();

	public:

		// 描画優先度を設定する
		BillboardDrawFuncRunnerInitParam& drawPriority(float value);

		// 使用するレンダーターゲットのディスクリプタヒープハンドルを設定する
		// ※初期パラメータはバックバッファー
		BillboardDrawFuncRunnerInitParam& useRtvDescriptorHeapHandle(size_t value);

		// 使用するカメラハンドルを設定する
		// ※初期パラメータはデフォルト通常カメラ
		BillboardDrawFuncRunnerInitParam& cameraHandle(size_t value);

		// 使用するカメラIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可で、関数内で対応するリソースハンドルに変換される）
		// ※初期パラメータはデフォルト通常カメラ
		BillboardDrawFuncRunnerInitParam& cameraId(ResourceIdCarrier value);

	private:

		static BillboardDrawFuncRunnerInitParam m_self;

	public:

		float	m_drawPriority				{ 0.0f };
		size_t	m_rtvDescriptorHeapHandle	{ 0U };
		size_t	m_cameraHandle				{ 0U };
	};
}
#endif // !BILLBOARD_DRAW_FUNC_RUNNER_INIT_PARAM_H_