#ifndef SCISSOR_RECT_H_
#define SCISSOR_RECT_H_

#include <TktkContainer/HeapArray/HeapArray.h>
#include "ScissorRectData.h"

namespace tktk
{
	// 「ScissorRectData」を管理するクラス
	class ScissorRect
	{
	public:

		ScissorRect(unsigned int scissorRectNum);
		~ScissorRect() = default;

	public:

		// 「ScissorRectData」のインスタンスを作る
		void create(unsigned int id, const std::vector<ScissorRectInitParam>& initParamArray);

		// 指定のシザー矩形をコマンドリストに登録する
		void set(unsigned int id, ID3D12GraphicsCommandList* commandList) const;

	private:

		HeapArray<ScissorRectData> m_scissorRectDataArray;
	};
}
#endif // !SCISSOR_RECT_H_