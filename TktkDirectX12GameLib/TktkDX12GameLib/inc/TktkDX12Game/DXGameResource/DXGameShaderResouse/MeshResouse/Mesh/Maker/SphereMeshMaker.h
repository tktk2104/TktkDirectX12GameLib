#ifndef SPHERE_MESH_MAKER_H_
#define SPHERE_MESH_MAKER_H_

#include <TktkMath/Structs/Color.h>

namespace tktk
{
	struct MeshDrawFuncRunnerInitParam;

	class SphereMeshMaker
	{
	public:

		SphereMeshMaker();
		~SphereMeshMaker();

	public:

		// 球体ワイヤーフレームメッシュを作る
		size_t makeSphereMeshWireFrame(const MeshDrawFuncRunnerInitParam& funcRunnerInitParam);

		// 球体単色メッシュを作る
		size_t makeMonoColorSphereMesh(const MeshDrawFuncRunnerInitParam& funcRunnerInitParam);

	private:

		// 球体のインデックスサイズ
		constexpr static size_t IndicesSize{ 600U };
	};
}
#endif // !SPHERE_MESH_MAKER_H_