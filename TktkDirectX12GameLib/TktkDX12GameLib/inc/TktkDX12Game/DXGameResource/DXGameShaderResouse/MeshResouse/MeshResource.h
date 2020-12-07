#ifndef MESH_RESOURCE_H_
#define MESH_RESOURCE_H_

/* std::unique_ptr */
#include <memory>

/* std::string */
#include <string>

/* funcUseType */
#include <TktkMath/Structs/Color.h>
#include <TktkMath/Structs/Matrix4.h>
#include "Mesh/Loader/Structs/MeshLoadPmdReturnValue.h"
#include "Mesh/Loader/Structs/MeshLoadPmxReturnValue.h"

namespace tktk
{
	// 前方宣言達
	class SkeletonManager;
	class MotionManager;
	class MeshManager;
	class MeshMaterialManager;
	class BoxMeshMaker;
	class SphereMeshMaker;

	struct MeshResourceInitParam;
	struct SkeletonInitParam;
	struct MeshInitParam;
	struct MeshMaterialInitParam;
	struct MeshMaterialAppendParamInitParam;
	struct MeshMaterialAppendParamUpdateFuncArgs;
	struct MeshDrawFuncBaseArgs;
	struct MeshLoadPmdArgs;
	struct MeshLoadPmxArgs;
	struct MeshDrawFuncRunnerInitParam;
	struct CopySourceDataCarrier;

	// メッシュ関係のリソースを管理するクラス
	class MeshResource
	{
	public:

		explicit MeshResource(const MeshResourceInitParam& initParam);
		~MeshResource();

	public: /* スケルトン関係の処理 */

		// スケルトンを作り、そのリソースのハンドルを返す
		size_t createSkeleton(const SkeletonInitParam& initParam);

		// スケルトンのコピーを作り、そのリソースのハンドルを返す
		size_t copySkeleton(size_t originalHandle);

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
			float curFrame,
			float preFrame,
			float amount
		);

	public: /* メッシュ関係の処理 */

		// 初期から存在するメッシュを作る
		void createSystemMesh();

		// メッシュを作り、そのリソースのハンドルを返す
		size_t createMesh(const MeshInitParam& initParam);

		// メッシュのコピーを作り、そのリソースのハンドルを返す
		size_t copyMesh(size_t originalHandle);

		// メッシュマテリアルを作り、そのリソースのハンドルを返す
		size_t createMeshMaterial(const MeshMaterialInitParam& initParam);

		// メッシュマテリアルのコピーを作り、そのリソースのハンドルを返す
		size_t copyMeshMaterial(size_t originalHandle);

		// テクスチャを貼った立方体メッシュを作り、そのハンドルを返す
		size_t makeBoxMesh(size_t albedoMapTextureHandle, const MeshDrawFuncRunnerInitParam& funcRunnerInitParam);

		// スカイボックスメッシュを作り、そのハンドルを返す
		size_t makeSkyBoxMesh(size_t skyBoxTextureHandle, const MeshDrawFuncRunnerInitParam& funcRunnerInitParam);

		// pmdファイルをロードしてゲームの各種リソースクラスを作る
		MeshLoadPmdReturnValue loadPmd(const MeshLoadPmdArgs& args, const MeshDrawFuncRunnerInitParam& funcRunnerInitParam);

		// pmxファイルをロードしてゲームの各種リソースクラスを作る
		MeshLoadPmxReturnValue loadPmx(const MeshLoadPmxArgs& args, const MeshDrawFuncRunnerInitParam& funcRunnerInitParam);

		// メッシュが使用しているマテリアルを更新する
		void setMaterialHandle(size_t meshHandle , size_t materialSlot, size_t materialHandle);

		// 指定のメッシュのマテリアル情報をグラフィックパイプラインに設定する
		void setMaterialData(size_t handle) const;

		// 指定のメッシュのマテリアルで追加で管理する定数バッファのIDと値を設定する
		void addMaterialAppendParam(size_t handle, const MeshMaterialAppendParamInitParam& initParam);

		// 指定のメッシュのマテリアルで追加で管理する定数バッファのIDと値を更新する
		void updateMaterialAppendParam(size_t handle, const MeshMaterialAppendParamUpdateFuncArgs& updateFuncArgs);

		// 指定のメッシュをインスタンス描画する時に使用する値を削除する
		void clearInstanceParam(size_t handle);

		// 指定のメッシュをインスタンス描画する時に使用する値を追加する
		void addInstanceVertParam(size_t handle, const CopySourceDataCarrier& instanceParam);

		// スキニングメッシュをインスタンス描画する時に使用する骨行列を追加する
		void addInstanceBoneMatrix(size_t meshHandle, size_t skeletonHandle);

		// 指定のメッシュでシャドウマップを書き込む
		void writeShadowMap(size_t handle) const;

		// 指定のスキニングメッシュでシャドウマップを書き込む
		void writeShadowMapUseBone(size_t handle) const;

		// 指定のメッシュをインスタンス描画する
		void draw(size_t handle, const MeshDrawFuncBaseArgs& baseArgs) const;

		// スキニングメッシュをインスタンス描画する
		void drawUseBone(size_t handle, const MeshDrawFuncBaseArgs& baseArgs) const;

	private:

		std::unique_ptr<SkeletonManager>		m_skeleton;
		std::unique_ptr<MotionManager>			m_motion;
		std::unique_ptr<MeshManager>			m_meshManager;
		std::unique_ptr<MeshMaterialManager>	m_meshMaterialManager;
		std::unique_ptr<BoxMeshMaker>			m_boxMeshMaker;
		std::unique_ptr<SphereMeshMaker>		m_sphereMeshMaker;
	};
}
#endif // !MESH_RESOURCE_H_