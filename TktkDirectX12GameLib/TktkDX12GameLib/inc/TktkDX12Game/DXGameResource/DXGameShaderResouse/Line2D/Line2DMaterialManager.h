#ifndef LINE_2D_MATERIAL_MANAGER_H_
#define LINE_2D_MATERIAL_MANAGER_H_

/* tktkContainer::ResourceContainer */
#include <TktkContainer/ResourceContainer/ResourceContainer.h>

namespace tktk
{
	class Line2DMaterialData;
	struct Line2DMaterialManagerInitParam;
	struct ShaderFilePaths;
	struct Line2DMaterialDrawFuncArgs;

	// 「Line2DMaterialData」を管理するクラス
	class Line2DMaterialManager
	{
	public:

		Line2DMaterialManager(const Line2DMaterialManagerInitParam& initParam);
		~Line2DMaterialManager();

	public:

		// ２Ｄラインを作り、そのリソースのハンドルを返す
		size_t create();

		// ２Ｄラインを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		void erase(size_t handle);

		// 指定の２Ｄラインを描画する
		// ※前フレームで作った頂点バッファを削除し、内部でライン描画用の頂点バッファを作り、そのリソースハンドルを保持する処理の為、非const関数
		void drawLine(size_t handle, const Line2DMaterialDrawFuncArgs& drawFuncArgs);

	private:

		// ２Ｄライン描画用のルートシグネチャを作る
		void createBasicDescriptorHeap() const;

		// ２Ｄライン描画用のルートシグネチャを作る
		void createRootSignature() const;

		// ２Ｄライン描画用のパイプラインステートを作る
		void createGraphicsPipeLineState(const ShaderFilePaths& shaderFilePaths) const;

	private:

		tktkContainer::ResourceContainer<Line2DMaterialData> m_line2DMaterialArray;
	};
}
#endif // !LINE_2D_MATERIAL_MANAGER_H_