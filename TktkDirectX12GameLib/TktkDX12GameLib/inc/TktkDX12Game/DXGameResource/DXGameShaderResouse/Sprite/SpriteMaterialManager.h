#ifndef SPRITE_MATERIAL_H_
#define SPRITE_MATERIAL_H_

/* use func type */
#include <TktkMath/Structs/Vector2.h>

/* tktkContainer::ResourceContainer */
#include <TktkContainer/ResourceContainer/ResourceContainer.h>

namespace tktk
{
	class SpriteMaterialData;

	struct SpriteMaterialManagerInitParam;
	struct SpriteMaterialInitParam;
	struct SpriteMaterialDrawFuncArgs;
	struct TempSpriteMaterialInstanceData;

	// 「SpriteMaterialData」を管理するクラス
	class SpriteMaterialManager
	{
	public:

		explicit SpriteMaterialManager(const SpriteMaterialManagerInitParam& initParam);
		~SpriteMaterialManager();

	public:

		// 「SpriteMaterialData」のインスタンスを作り、そのリソースのハンドルを返す
		size_t create(const SpriteMaterialInitParam& initParam);

		// 指定したスプライトが使用するテクスチャのサイズを取得する
		const tktkMath::Vector2& getSpriteTextureSize(size_t handle) const;

		// 指定したスプライトの最大のインスタンス数を取得する
		size_t getMaxInstanceCount(size_t handle) const;

		// 指定したスプライトの現在のインスタンス数を取得する
		size_t getCurInstanceCount(size_t handle) const;

		// 指定したスプライトをインスタンス描画する時に使用する値を削除する
		void clearInstanceParam(size_t handle);

		// 指定したスプライトをインスタンス描画する時に使用する値を追加する
		void addInstanceParam(size_t handle, float drawPriority, const TempSpriteMaterialInstanceData& instanceParam);

		// 指定しスプライトをインスタンス描画する時に使用する値を頂点バッファに書き込む
		void updateInstanceParam(size_t handle);

		// 指定したスプライトを描画する
		void draw(size_t handle, const SpriteMaterialDrawFuncArgs& drawFuncArgs) const;

	private:

		tktkContainer::ResourceContainer<SpriteMaterialData> m_spriteMaterialArray;
	};
}
#endif // !SPRITE_MATERIAL_H_