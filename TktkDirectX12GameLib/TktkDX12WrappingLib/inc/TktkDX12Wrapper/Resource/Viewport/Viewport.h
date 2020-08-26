#ifndef VIEWPORT_H_
#define VIEWPORT_H_

#include <TktkContainer/ResourceContainer/ResourceContainer.h>
#include "ViewportData.h"

namespace tktk
{
	// 「ViewportData」を管理するクラス
	class Viewport
	{
	public:

		explicit Viewport(const tktkContainer::ResourceContainerInitParam& initParam);
		~Viewport() = default;

	public:

		// 「ViewportData」のインスタンスを作り、そのリソースのハンドルを返す
		unsigned int create(const std::vector<ViewportInitParam>& initParamArray);

		// 指定のビューポートを削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		void erase(unsigned int handle);

		// 指定のビューポートをコマンドリストに登録する
		void set(unsigned int handle, ID3D12GraphicsCommandList* commandList) const;

	private:

		tktkContainer::ResourceContainer<ViewportData> m_viewportDataArray;
	};
}
#endif // !VIEWPORT_H_