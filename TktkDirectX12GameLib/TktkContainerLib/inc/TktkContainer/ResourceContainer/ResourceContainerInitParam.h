#ifndef RESOURCE_CONTAINER_INIT_PARAM_H_
#define RESOURCE_CONTAINER_INIT_PARAM_H_

namespace tktkContainer
{
	// 「ResourceContainer」のインスタンスを作る時に必要な変数
	struct ResourceContainerInitParam
	{
		size_t	staticNodeNum			{ 10U };	// 初期化時にインスタンス何個分のメモリを事前確保するか？
		size_t	moveNodeMaxNumPerFrame	{ 1U };		// １フレームで初期化時確保メモリに移動できる要素数
	};
}
#endif // !RESOURCE_CONTAINER_INIT_PARAM_H_