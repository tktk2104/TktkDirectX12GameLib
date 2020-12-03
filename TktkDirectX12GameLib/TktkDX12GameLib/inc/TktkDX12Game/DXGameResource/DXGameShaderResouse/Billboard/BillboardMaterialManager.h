#ifndef BILLBOARD_MATERIAL_H_
#define BILLBOARD_MATERIAL_H_

/* tktkContainer::ResourceContainer */
#include <TktkMath/Structs/Vector2.h>
#include <TktkContainer/ResourceContainer/ResourceContainer.h>

namespace tktk
{
	class BillboardMaterialData;

	struct BillboardMaterialManagerInitParam;
	struct BillboardMaterialInitParam;
	struct BillboardDrawFuncBaseArgs;
	struct BillboardMaterialInstanceVertData;

	// 「BillboardMaterialData」を管理するクラス
	class BillboardMaterialManager
	{
	public:

		BillboardMaterialManager(const BillboardMaterialManagerInitParam& initParam);
		~BillboardMaterialManager();

	public:

		// 「BillboardMaterialData」のインスタンスを作り、そのリソースのハンドルを返す
		size_t create(const BillboardMaterialInitParam& initParam);

		// 指定したビルボードが使用するテクスチャのサイズを取得する
		const tktkMath::Vector2& getBillboardTextureSize(size_t handle) const;

		// 指定したビルボードをインスタンス描画する時に使用する値を削除する
		void clearInstanceParam(size_t handle);

		// 指定したビルボードをインスタンス描画する時に使用する値を追加する
		void addInstanceVertParam(size_t handle, const BillboardMaterialInstanceVertData& instanceParam);

		// 指定したビルボードを描画する
		void draw(size_t handle, const BillboardDrawFuncBaseArgs& drawFuncArgs) const;

	private:

		tktkContainer::ResourceContainer<BillboardMaterialData> m_billboardMaterialArray;
	};
}
#endif // !BILLBOARD_MATERIAL_H_