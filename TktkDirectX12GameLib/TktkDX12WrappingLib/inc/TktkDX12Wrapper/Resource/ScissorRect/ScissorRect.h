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
		unsigned int create(const std::vector<ScissorRectInitParam>& initParamArray);

		// 指定のシザー矩形をコマンドリストに登録する
		void set(unsigned int handle, ID3D12GraphicsCommandList* commandList) const;

	private:

		tktkContainer::ResourceContainer<ScissorRectData> m_scissorRectDataArray;
	};
}
#endif // !SCISSOR_RECT_H_