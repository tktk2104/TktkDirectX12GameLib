#ifndef SCISSOR_RECT_DATA_H_
#define SCISSOR_RECT_DATA_H_

#include <vector>
#include "../../Includer/D3d12Includer.h"
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