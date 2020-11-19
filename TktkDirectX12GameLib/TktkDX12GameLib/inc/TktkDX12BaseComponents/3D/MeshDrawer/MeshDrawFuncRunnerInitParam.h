#ifndef MESH_DRAW_FUNC_RUNNER_INIT_PARAM_H_
#define MESH_DRAW_FUNC_RUNNER_INIT_PARAM_H_

#include "TktkDX12Game/UtilityProcessManager/ResourceHandleGetter/ResourceIdConverter/ResourceIdCarrier.h"

namespace tktk
{
	struct MeshDrawFuncRunnerInitParam
	{
	public:

		static MeshDrawFuncRunnerInitParam& create();

	public:

		// シャドウマップを描画するか？
		MeshDrawFuncRunnerInitParam& writeShadowMap(bool value);

		// 描画優先度を設定する
		MeshDrawFuncRunnerInitParam& drawPriority(float value);

		// ボーンを使用して描画するか？
		MeshDrawFuncRunnerInitParam& useBone(bool value);

		// 使用するレンダーターゲットのディスクリプタヒープハンドルを設定する
		// ※初期パラメータはバックバッファー
		MeshDrawFuncRunnerInitParam& useRtvDescriptorHeapHandle(size_t value);

		// 使用するライトハンドルを設定する
		// ※初期パラメータはデフォルトライト
		MeshDrawFuncRunnerInitParam& lightHandle(size_t value);

		// 使用するライトIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可で、関数内で対応するリソースハンドルに変換される）
		// ※初期パラメータはデフォルトライト
		MeshDrawFuncRunnerInitParam& lightId(ResourceIdCarrier value);

		// 使用するカメラハンドルを設定する
		// ※初期パラメータはデフォルト通常カメラ
		MeshDrawFuncRunnerInitParam& cameraHandle(size_t value);

		// 使用するカメラIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可で、関数内で対応するリソースハンドルに変換される）
		// ※初期パラメータはデフォルト通常カメラ
		MeshDrawFuncRunnerInitParam& cameraId(ResourceIdCarrier value);

		// 使用するシャドウマップカメラハンドルを設定する
		// ※初期パラメータはデフォルトシャドウマップカメラ
		MeshDrawFuncRunnerInitParam& shadowMapCameraHandle(size_t value);

		// 使用するシャドウマップカメラIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可で、関数内で対応するリソースハンドルに変換される）
		// ※初期パラメータはデフォルトシャドウマップカメラ
		MeshDrawFuncRunnerInitParam& shadowMapCameraId(ResourceIdCarrier value);


		MeshDrawFuncRunnerInitParam& skeletonHandle(size_t value);
		MeshDrawFuncRunnerInitParam& skeletonId(ResourceIdCarrier value);

	private:

		static MeshDrawFuncRunnerInitParam m_self;

	private:

		MeshDrawFuncRunnerInitParam() = default;

	public:

		bool	m_writeShadowMap			{ false };
		float	m_drawPriority				{ 0.0f };
		bool	m_useBone					{ false };
		size_t	m_rtvDescriptorHeapHandle	{ 0U };
		size_t	m_lightHandle				{ 0U };
		size_t	m_cameraHandle				{ 0U };
		size_t	m_shadowMapCameraHandle		{ 0U };

		size_t m_skeletonHandle{ 0U };
	};
}
#endif // !MESH_DRAW_FUNC_RUNNER_INIT_PARAM_H_