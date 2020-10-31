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
		unsigned int createSkeleton(const SkeletonInitParam& initParam);

		// スケルトンのコピーを作り、そのリソースのハンドルを返す
		unsigned int copySkeleton(unsigned int originalHandle);

		// 指定のスケルトンの骨情報の定数バッファの値にコピーするためのバッファを作り、そのハンドルを返す
		// ※この関数で取得したハンドルは使用後に「DX12GameManager::eraseCopyBuffer(handle)」を必ず読んでバッファを削除してください
		unsigned int createSkeletonCopyBufferHandle(unsigned int handle) const;

		// 指定のスケルトンを使って引数が表すコピーバッファを使い骨情報を管理する定数バッファを更新する
		void updateBoneMatrixCbuffer(unsigned int handle, unsigned int copyBufferHandle) const;

		// 骨情報を管理する定数バッファに単位行列を設定する
		void resetBoneMatrixCbuffer() const;

	public: /* モーション関係の処理 */

		// vmdファイルを読み込んで「MotionData」のインスタンスを作り、そのリソースのハンドルを返す
		unsigned int loadMotion(const std::string& motionFileName);

		// 指定のモーションの終了キーの番号を取得する
		unsigned int getMotionEndFrameNo(unsigned int handle) const;

		// 2種類のモーション情報を線形補完してスケルトンを更新する
		// ※補完割合の値は「0.0fでpreFrame100%」、「1.0fでcurFrame100%」となる
		void updateMotion(
			unsigned int skeletonHandle,
			unsigned int curMotionHandle,
			unsigned int preMotionHandle,
			unsigned int curFrame,
			unsigned int preFrame,
			float amount
		);

	public: /* メッシュ関係の処理 */

		// 通常メッシュを作り、そのリソースのハンドルを返す
		unsigned int createBasicMesh(const BasicMeshInitParam& initParam);

		// 通常メッシュのコピーを作り、そのリソースのハンドルを返す
		unsigned int copyBasicMesh(unsigned int originalHandle);

		// 通常メッシュマテリアルを作り、そのリソースのハンドルを返す
		unsigned int createBasicMeshMaterial(const BasicMeshMaterialInitParam& initParam);

		// 通常メッシュマテリアルのコピーを作り、そのリソースのハンドルを返す
		unsigned int copyBasicMeshMaterial(unsigned int originalHandle);

		// 通常メッシュが使用しているマテリアルを更新する
		void setMaterialHandle(unsigned int meshHandle , unsigned int materialSlot, unsigned int materialHandle);

		// 指定の通常メッシュでシャドウマップを書き込む
		void writeBasicMeshShadowMap(unsigned int handle) const;

		// 指定の通常メッシュのマテリアル情報をグラフィックパイプラインに設定する
		void setMaterialData(unsigned int handle) const;

		// 指定の通常メッシュのマテリアルで追加で管理する定数バッファのIDと値を設定する
		void addMaterialAppendParam(unsigned int handle, unsigned int cbufferHandle, unsigned int dataSize, void* dataTopPos);

		// 指定の通常メッシュのマテリアルで追加で管理する定数バッファのIDと値を更新する
		void updateMaterialAppendParam(unsigned int handle, unsigned int cbufferHandle, unsigned int dataSize, const void* dataTopPos);

		// 指定の通常メッシュを描画する
		void drawBasicMesh(unsigned int handle, const MeshDrawFuncBaseArgs& baseArgs) const;

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