#ifndef MESH_DRAWER_MAKER_H_
#define MESH_DRAWER_MAKER_H_

#include "TktkDX12Game/UtilityProcessManager/ResourceHandleGetter/ResourceIdConverter/ResourceIdCarrier.h"
#include "MeshDrawer.h"

namespace tktk
{
	class MeshDrawerMaker
	{
	private:

		MeshDrawerMaker() = default;
		MeshDrawerMaker(const MeshDrawerMaker& other) = default;
		MeshDrawerMaker& operator = (const MeshDrawerMaker& other) = default;

	public:

		// 作成開始
		static MeshDrawerMaker& makeStart(GameObjectPtr user);

	public:

		// 作成完了
		ComponentPtr<MeshDrawer> create();

	public:  /* パラメータ設定関数 */

		// 使用するメッシュハンドルを設定する
		MeshDrawerMaker& meshHandle(size_t value);

		// 使用するメッシュIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可で、関数内で対応するリソースハンドルに変換される）
		MeshDrawerMaker& meshId(ResourceIdCarrier value);

		// 使用するスケルトンハンドルを設定する
		MeshDrawerMaker& skeletonHandle(size_t value);

		// 使用するスケルトンIDを設定する（列挙型を含む整数型のidが渡された場合のみビルド可で、関数内で対応するリソースハンドルに変換される）
		MeshDrawerMaker& skeletonId(ResourceIdCarrier value);

		// 基本の座標を設定する
		MeshDrawerMaker& basePosition(const tktkMath::Vector3 & value);

		// 基本のスケールを設定する
		MeshDrawerMaker& baseScale(const tktkMath::Vector3 & value);

		// 基本の回転を設定する
		MeshDrawerMaker& baseRotation(const tktkMath::Quaternion & value);

	private: /* 自身のインスタンスは静的な存在として扱う */

		static MeshDrawerMaker m_self;

	private: /* 変数達 */

		GameObjectPtr			m_user			{  };
		size_t					m_meshHandle	{  };
		size_t					m_skeletonHandle{  };
		tktkMath::Vector3		m_basePosition	{ tktkMath::Vector3_v::zero };
		tktkMath::Vector3		m_baseScale		{ tktkMath::Vector3_v::one };
		tktkMath::Quaternion	m_baseRotation	{ tktkMath::Quaternion_v::identity };
	};
}
#endif // !MESH_DRAWER_MAKER_H_