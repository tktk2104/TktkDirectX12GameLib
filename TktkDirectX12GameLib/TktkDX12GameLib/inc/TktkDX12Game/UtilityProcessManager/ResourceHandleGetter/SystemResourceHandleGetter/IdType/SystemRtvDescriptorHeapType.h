#ifndef SYSTEM_RTV_DESCRIPTOR_HEAP_TYPE_H_
#define SYSTEM_RTV_DESCRIPTOR_HEAP_TYPE_H_

namespace tktk
{
	// システムで使用しているレンダーターゲット用のディスクリプタヒープの種類
	enum class SystemRtvDescriptorHeapType
	{
		BackBuffer,			// バックバッファー
		DrawGameArea,		// ゲームの描画エリア
		PostEffectTarget,	// ポストエフェクト出力
	};
}
#endif // !SYSTEM_RTV_DESCRIPTOR_HEAP_TYPE_H_