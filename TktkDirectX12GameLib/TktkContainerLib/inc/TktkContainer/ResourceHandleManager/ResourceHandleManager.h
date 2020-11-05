#ifndef RESOURCE_HANDLE_MANAGER_H_
#define RESOURCE_HANDLE_MANAGER_H_

#include <limits>
#include <queue>

namespace tktkContainer
{
	class ResourceHandleManager
	{
	public:

		ResourceHandleManager() = default;
		~ResourceHandleManager() = default;

	public:

		// 新たなハンドルを取得する
		// ※以前使っていて今使っていない番号があったらそれを取得する
		size_t createHandle();

		// 引数のハンドルを使用済みとして
		void endUseHandle(size_t deleteHandle);

		// ハンドルの作成状況を初期化する
		void reset();

	private:

		// 使用済みのハンドルを保存するキュー
		std::queue<size_t>	m_endUseHandles;

		// 次に使用するハンドル
		size_t				m_nextUseHandle	{ std::numeric_limits<size_t>::max() };
	};
}
#endif // !RESOURCE_HANDLE_MANAGER_H_