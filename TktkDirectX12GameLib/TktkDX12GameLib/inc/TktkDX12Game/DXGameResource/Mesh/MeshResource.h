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

		// スケルトンを作成する
		void createSkeleton(unsigned int id, const SkeletonInitParam& initParam);

		// 指定のスケルトンを使って骨情報を管理する定数バッファを更新する
		void updateBoneMatrixCbuffer(unsigned int id) const;

		// 骨情報を管理する定数バッファに単位行列を設定する
		void resetBoneMatrixCbuffer() const;

	public: /* モーション関係の処理 */

		// vmdファイルを読み込んで「MotionData」のインスタンスを作る
		void loadMotion(unsigned int id, const std::string& motionFileName);

		// 指定のモーションの終了キーの番号を取得する
		unsigned int getMotionEndFrameNo(unsigned int id) const;

		// 2種類のモーション情報を線形補完してスケルトンを更新する
		// ※補完割合の値は「0.0fでpreFrame100%」、「1.0fでcurFrame100%」となる
		void updateMotion(
			unsigned int skeletonId,
			unsigned int curMotionId,
			unsigned int preMotionId,
			unsigned int curFrame,
			unsigned int preFrame,
			float amount
		);

	public: /* メッシュ関係の処理 */

		// 通常メッシュを作る
		void createBasicMesh(unsigned int id, const BasicMeshInitParam& initParam);

		// 通常メッシュのコピーを作る
		void copyBasicMesh(unsigned int id, unsigned int originalId);

		// 通常メッシュマテリアルを作る
		void createBasicMeshMaterial(unsigned int id, const BasicMeshMaterialInitParam& initParam);

		// 通常メッシュマテリアルのコピーを作る
		void copyBasicMeshMaterial(unsigned int id, unsigned int originalId);

		// 通常メッシュが使用しているマテリアルを更新する
		void setMaterialId(unsigned int id, unsigned int materialSlot, unsigned int materialId);

		// 指定の通常メッシュでシャドウマップを書き込む
		void writeBasicMeshShadowMap(unsigned int id, const MeshTransformCbuffer& transformBufferData) const;

		// 指定の通常メッシュのマテリアル情報をグラフィックパイプラインに設定する
		void setMaterialData(unsigned int id) const;

		// 指定の通常メッシュのマテリアルで追加で管理する定数バッファのIDと値を設定する
		void addMaterialAppendParam(unsigned int id, unsigned int cbufferId, unsigned int dataSize, void* dataTopPos);

		// 指定の通常メッシュのマテリアルで追加で管理する定数バッファのIDと値を更新する
		void updateMaterialAppendParam(unsigned int id, unsigned int cbufferId, unsigned int dataSize, const void* dataTopPos);

		// 指定の通常メッシュを描画する
		void drawBasicMesh(unsigned int id, const MeshDrawFuncBaseArgs& baseArgs) const;

		// pmdファイルをロードしてゲームの各種リソースクラスを作る
		BasicMeshLoadPmdReturnValue loadPmd(const BasicMeshLoadPmdArgs& args);

	private:

		std::unique_ptr<Skeleton>			m_skeleton;
		std::unique_ptr<Motion>				m_motion;
		std::unique_ptr<BasicMesh>			m_basicMesh;
		std::unique_ptr<BasicMeshMaterial>	m_basicMeshMaterial;
	};
}
#endif // !MESH_RESOURCE_H_