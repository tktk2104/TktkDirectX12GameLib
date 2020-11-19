#ifndef SCISSOR_RECT_DATA_H_
#define SCISSOR_RECT_DATA_H_

/* std::vector */
#include <vector>

/* ID3D12GraphicsCommandList, D3D12_RECT */
#include <d3d12.h>
#undef min
#undef max

#include "ScissorRectInitParam.h"

namespace tktk
{
	// シザー矩形を管理するクラス
	class ScissorRectData
	{
	public:

		explicit ScissorRectData(const std::vector<ScissorRectInitParam>& initParamArray);
		~ScissorRectData() = default;

		// ムーブコンストラクタ
		ScissorRectData(ScissorRectData&& other) noexcept;

	public:

		// 自身をコマンドリストに登録する
		void set(ID3D12GraphicsCommandList* commandList) const;

	private:

		std::vector<D3D12_RECT> m_scissorRectArray{};
	};
}
#endif // !SCISSOR_RECT_DATA_H_