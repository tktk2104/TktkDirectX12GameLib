#ifndef BOX_MESH_MAKER_H_
#define BOX_MESH_MAKER_H_

#include <TktkMath/Structs/Color.h>

namespace tktk
{
	struct MeshDrawFuncRunnerInitParam;

	class BoxMeshMaker
	{
	public:

		BoxMeshMaker();
		~BoxMeshMaker();

	public:

		// 単色の立方体メッシュワイヤーフレームを作り、そのハンドルを返す
		size_t makeBoxMeshWireFrame(const MeshDrawFuncRunnerInitParam& funcRunnerInitParam);

		// 単色の立方体メッシュを作り、そのハンドルを返す
		size_t makeMonoColorBoxMesh(const MeshDrawFuncRunnerInitParam& funcRunnerInitParam);

	public:

		// テクスチャを貼った立方体メッシュを作り、そのハンドルを返す
		size_t makeBoxMesh(size_t albedoMapTextureHandle, const MeshDrawFuncRunnerInitParam& funcRunnerInitParam);

		// スカイボックスメッシュを作り、そのハンドルを返す
		size_t makeSkyBoxMesh(size_t skyBoxTextureHandle, const MeshDrawFuncRunnerInitParam& funcRunnerInitParam);

	private:

		// 立方体のインデックスサイズ
		constexpr static size_t IndicesSize{ 36U };
	};
}
#endif // !BOX_MESH_MAKER_H_