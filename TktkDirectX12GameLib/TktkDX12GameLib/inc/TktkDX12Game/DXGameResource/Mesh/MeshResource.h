#ifndef MESH_RESOURCE_H_
#define MESH_RESOURCE_H_

#include <memory>
#include "MeshResourceNum.h"
#include "MeshResourceShaderFilePaths.h"
#include "MeshResourceInitParamIncluder.h"
#include "MeshResourceFuncArgsIncluder.h"

namespace tktk
{
	// 前方宣言達
	class Skeleton;
	class Motion;
	class BasicMesh;
	class BasicMeshMaterial;

	// メッシュ関係のリソースを管理するクラス
	class MeshResource
	{
	public:

		MeshResource(const MeshResourceNum& resourceNum, const MeshResourceShaderFilePaths& shaderFilePaths);
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

		// 通常メッシュを作り、そのリソースのハンドルを返す
		size_t createBasicMesh(const BasicMeshInitParam& initParam);

		// 通常メッシュのコピーを作り、そのリソースのハンドルを返す
		size_t copyBasicMesh(size_t originalHandle);

		// 通常メッシュマテリアルを作り、そのリソースのハンドルを返す
		size_t createBasicMeshMaterial(const BasicMeshMaterialInitParam& initParam);

		// 通常メッシュマテリアルのコピーを作り、そのリソースのハンドルを返す
		size_t copyBasicMeshMaterial(size_t originalHandle);

		// 通常メッシュが使用しているマテリアルを更新する
		void setMaterialHandle(size_t meshHandle , size_t materialSlot, size_t materialHandle);

		// 指定の通常メッシュでシャドウマップを書き込む
		void writeBasicMeshShadowMap(size_t handle) const;

		// 指定の通常メッシュのマテリアル情報をグラフィックパイプラインに設定する
		void setMaterialData(size_t handle) const;

		// 指定の通常メッシュのマテリアルで追加で管理する定数バッファのIDと値を設定する
		void addMaterialAppendParam(size_t handle, size_t cbufferHandle, size_t dataSize, void* dataTopPos);

		// 指定の通常メッシュのマテリアルで追加で管理する定数バッファのIDと値を更新する
		void updateMaterialAppendParam(size_t handle, size_t cbufferHandle, size_t dataSize, const void* dataTopPos);

		// 指定の通常メッシュを描画する
		void drawBasicMesh(size_t handle, const MeshDrawFuncBaseArgs& baseArgs) const;

		// pmdファイルをロードしてゲームの各種リソースクラスを作る
		BasicMeshLoadPmdReturnValue loadPmd(const BasicMeshLoadPmdArgs& args);

		// pmxファイルをロードしてゲームの各種リソースクラスを作る
		BasicMeshLoadPmxReturnValue loadPmx(const BasicMeshLoadPmxArgs& args);

	private:

		std::unique_ptr<Skeleton>			m_skeleton;
		std::unique_ptr<Motion>				m_motion;
		std::unique_ptr<BasicMesh>			m_basicMesh;
		std::unique_ptr<BasicMeshMaterial>	m_basicMeshMaterial;
	};
}
#endif // !MESH_RESOURCE_H_