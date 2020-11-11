#ifndef MESH_RESOURCE_H_
#define MESH_RESOURCE_H_

/* std::unique_ptr */
#include <memory>

/* std::string */
#include <string>

/* funcUseType */
#include "Mesh/Loader/MeshLoadPmdReturnValue.h"
#include "Mesh/Loader/MeshLoadPmxReturnValue.h"

namespace tktk
{
	// 前方宣言達
	class SkeletonManager;
	class MotionManager;
	class MeshManager;
	class MeshMaterialManager;

	struct MeshResourceInitParam;
	struct SkeletonInitParam;
	struct MeshInitParam;
	struct MeshMaterialInitParam;
	struct MeshMaterialAppendParamInitParam;
	struct MeshMaterialAppendParamUpdateFuncArgs;
	struct MeshDrawFuncBaseArgs;
	struct MeshLoadPmdArgs;
	struct MeshLoadPmxArgs;

	// メッシュ関係のリソースを管理するクラス
	class MeshResource
	{
	public:

		MeshResource(const MeshResourceInitParam& initParam);
		~MeshResource();

	public: /* スケルトン関係の処理 */

		// スケルトンを作り、そのリソースのハンドルを返す
		size_t createSkeleton(const SkeletonInitParam& initParam);

		// スケルトンのコピーを作り、そのリソースのハンドルを返す
		size_t copySkeleton(size_t originalHandle);

		// 指定のスケルトンの骨情報の定数バッファの値にアップロードするためのバッファを作り、そのハンドルを返す
		// ※この関数で取得したハンドルは使用後に「DX12GameManager::eraseUploadBuffer(handle)」を必ず読んでバッファを削除してください
		size_t createSkeletonUploadBufferHandle(size_t handle) const;

		// 指定のスケルトンを使って引数が表すコピーバッファを使い骨情報を管理する定数バッファを更新する
		void updateBoneMatrixCbuffer(size_t handle, size_t copyBufferHandle) const;

		// 骨情報を管理する定数バッファに単位行列を設定する
		void resetBoneMatrixCbuffer() const;

	public: /* モーション関係の処理 */

		// vmdファイルを読み込んで「MotionData」のインスタンスを作り、そのリソースのハンドルを返す
		size_t loadMotion(const std::string& motionFileName);

		// 指定のモーションの終了キーの番号を取得する
		size_t getMotionEndFrameNo(size_t handle) const;

		// 2種類のモーション情報を線形補完してスケルトンを更新する
		// ※補完割合の値は「0.0fでpreFrame100%」、「1.0fでcurFrame100%」となる
		void updateMotion(
			size_t skeletonHandle,
			size_t curMotionHandle,
			size_t preMotionHandle,
			size_t curFrame,
			size_t preFrame,
			float amount
		);

	public: /* メッシュ関係の処理 */

		// メッシュを作り、そのリソースのハンドルを返す
		size_t createBasicMesh(const MeshInitParam& initParam);

		// メッシュのコピーを作り、そのリソースのハンドルを返す
		size_t copyBasicMesh(size_t originalHandle);

		// メッシュマテリアルを作り、そのリソースのハンドルを返す
		size_t createBasicMeshMaterial(const MeshMaterialInitParam& initParam);

		// メッシュマテリアルのコピーを作り、そのリソースのハンドルを返す
		size_t copyBasicMeshMaterial(size_t originalHandle);

		// メッシュが使用しているマテリアルを更新する
		void setMaterialHandle(size_t meshHandle , size_t materialSlot, size_t materialHandle);

		// 指定のメッシュでシャドウマップを書き込む
		void writeBasicMeshShadowMap(size_t handle) const;

		// 指定のメッシュのマテリアル情報をグラフィックパイプラインに設定する
		void setMaterialData(size_t handle) const;

		// 指定のメッシュのマテリアルで追加で管理する定数バッファのIDと値を設定する
		void addMaterialAppendParam(size_t handle, const MeshMaterialAppendParamInitParam& initParam);

		// 指定のメッシュのマテリアルで追加で管理する定数バッファのIDと値を更新する
		void updateMaterialAppendParam(size_t handle, const MeshMaterialAppendParamUpdateFuncArgs& updateFuncArgs);

		// 指定のメッシュを描画する
		void drawBasicMesh(size_t handle, const MeshDrawFuncBaseArgs& baseArgs) const;

		// pmdファイルをロードしてゲームの各種リソースクラスを作る
		MeshLoadPmdReturnValue loadPmd(const MeshLoadPmdArgs& args);

		// pmxファイルをロードしてゲームの各種リソースクラスを作る
		MeshLoadPmxReturnValue loadPmx(const MeshLoadPmxArgs& args);

	private:

		std::unique_ptr<SkeletonManager>				m_skeleton;
		std::unique_ptr<MotionManager>					m_motion;
		std::unique_ptr<MeshManager>			m_meshManager;
		std::unique_ptr<MeshMaterialManager>	m_meshMaterialManager;
	};
}
#endif // !MESH_RESOURCE_H_