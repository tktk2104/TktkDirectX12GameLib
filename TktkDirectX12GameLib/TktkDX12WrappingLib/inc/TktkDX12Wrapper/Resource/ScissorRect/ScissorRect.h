#ifndef SCISSOR_RECT_H_
#define SCISSOR_RECT_H_

#include <TktkContainer/ResourceContainer/ResourceContainer.h>
#include "ScissorRectData.h"

namespace tktk
{
	// 「ScissorRectData」を管理するクラス
	class ScissorRect
	{
	public:

		explicit ScissorRect(const tktkContainer::ResourceContainerInitParam& initParam);
		~ScissorRect() = default;

	public:

		// 「ScissorRectData」のインスタンスを作り、そのリソースのハンドルを返す
		size_t create(const std::vector<ScissorRectInitParam>& initParamArray);

		// 指定のシザー矩形を削除する
		// ※引数のハンドルに対応するリソースが無かったら何もしない
		void erase(size_t handle);

		// 指定のシザー矩形をコマンドリストに登録する
		void set(size_t handle, ID3D12GraphicsCommandList* commandList) const;

	private:

		tktkContainer::ResourceContainer<ScissorRectData> m_scissorRectDataArray;
	};
}
#endif // !SCISSOR_RECT_H_