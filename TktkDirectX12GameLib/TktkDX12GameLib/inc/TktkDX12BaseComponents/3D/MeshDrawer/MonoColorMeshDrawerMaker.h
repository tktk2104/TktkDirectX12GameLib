#ifndef MONO_COLOR_MESH_DRAWER_MAKER_H_
#define MONO_COLOR_MESH_DRAWER_MAKER_H_

#include "TktkDX12Game/UtilityProcessManager/ResourceHandleGetter/ResourceIdConverter/ResourceIdCarrier.h"
#include "MonoColorMeshDrawer.h"

namespace tktk
{
	class MonoColorMeshDrawerMaker
	{
	private:

		MonoColorMeshDrawerMaker() = default;
		MonoColorMeshDrawerMaker(const MonoColorMeshDrawerMaker& other) = default;
		MonoColorMeshDrawerMaker& operator = (const MonoColorMeshDrawerMaker& other) = default;

	public:

		// 作成開始
		static MonoColorMeshDrawerMaker& makeStart(GameObjectPtr user);

	public:

		// 作成完了
		ComponentPtr<MonoColorMeshDrawer> create();

	public:  /* パラメータ設定関数 */

		// 立方体メッシュハンドルを設定する
		MonoColorMeshDrawerMaker& setBoxMesh();

		// 立方体メッシュワイヤーフレームハンドルを設定する
		MonoColorMeshDrawerMaker& setBoxMeshWireFrame();

		// 球体メッシュハンドルを設定する
		MonoColorMeshDrawerMaker& setSphereMesh();

		// 球体メッシュワイヤーフレームハンドルを設定する
		MonoColorMeshDrawerMaker& setSphereMeshWireFrame();

		// 使用するメッシュハンドルを設定する
		MonoColorMeshDrawerMaker& meshHandle(size_t value);

		// 使用するメッシュIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可で、関数内で対応するリソースハンドルに変換される）
		MonoColorMeshDrawerMaker& meshId(ResourceIdCarrier value);

		// 使用するスケルトンハンドルを設定する
		MonoColorMeshDrawerMaker& skeletonHandle(size_t value);

		// 使用するスケルトンIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可で、関数内で対応するリソースハンドルに変換される）
		MonoColorMeshDrawerMaker& skeletonId(ResourceIdCarrier value);

		// アルベドカラーを設定する
		MonoColorMeshDrawerMaker& albedoColor(const tktkMath::Color& value);

		// 基本の座標を設定する
		MonoColorMeshDrawerMaker& basePosition(const tktkMath::Vector3 & value);

		// 基本のスケールを設定する
		MonoColorMeshDrawerMaker& baseScale(const tktkMath::Vector3 & value);

		// 基本の回転を設定する
		MonoColorMeshDrawerMaker& baseRotation(const tktkMath::Quaternion & value);

	private: /* 自身のインスタンスは静的な存在として扱う */

		static MonoColorMeshDrawerMaker m_self;

	private: /* 変数達 */

		GameObjectPtr			m_user				{  };
		size_t					m_meshHandle		{  };
		size_t					m_skeletonHandle	{  };
		tktkMath::Color			m_albedoColor		{ tktkMath::Color_v::white };
		tktkMath::Vector3		m_basePosition		{ tktkMath::Vector3_v::zero };
		tktkMath::Vector3		m_baseScale			{ tktkMath::Vector3_v::one };
		tktkMath::Quaternion	m_baseRotation		{ tktkMath::Quaternion_v::identity };
	};
}
#endif // !MONO_COLOR_MESH_DRAWER_MAKER_H_