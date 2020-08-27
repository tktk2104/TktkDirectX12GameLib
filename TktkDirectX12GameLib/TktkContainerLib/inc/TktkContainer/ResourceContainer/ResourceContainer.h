#ifndef RESOURCE_CONTAINER_H_
#define RESOURCE_CONTAINER_H_

#include <limits>
#include <list>
#include <forward_list>
#include <unordered_map>
#include "../HeapArray/HeapArray.h"
#include "../ResourceHandleManager/ResourceHandleManager.h"
#include "ResourceContainerIterator.h"
#include "ResourceContainerConstIterator.h"
#include "ResourceContainerInitParam.h"

namespace tktkContainer
{
	template <class NodeType, class Allocator = std::allocator<NodeType>>
	class ResourceContainer
	{
	public:

		using iterator			= ResourceContainerIterator<NodeType>;
		using const_iterator	= ResourceContainerConstIterator<NodeType>;

	public:

		explicit ResourceContainer(const ResourceContainerInitParam& initParam);
		~ResourceContainer() = default;

	private:

		struct ResourceNode
		{
			NodeType*		ptr			{ nullptr };
			bool			isStatic	{ false };
		};

	public:

		// 初期化時に確保したメモリに空きがあった場合、最も寿命が長い動的に確保したメモリを使用したインスタンスを初期化時確保メモリに移動する
		void memoryCompaction();

	public:

		// コンストラクタ引数を渡してインスタンスを作り、そのハンドルを返す
		template <class... ConstructorArgs>
		unsigned int create(ConstructorArgs&&... args);

		// ハンドルを引数に対応するポインタを取得する
		// ※ハンドルに対応したリソースが無かった場合、nullptrを返す
		NodeType* getMatchHandlePtr(unsigned int handle) const;

		// 引数のハンドルのインスタンスを削除（メモリ解放）する
		void erase(unsigned int handle);

		// 全てのインスタンスを削除（メモリ解放）する
		void clear();

	public:

		ResourceContainer<NodeType, Allocator>::iterator		begin();
		ResourceContainer<NodeType, Allocator>::const_iterator	begin() const;

		ResourceContainer<NodeType, Allocator>::iterator		end();
		ResourceContainer<NodeType, Allocator>::const_iterator	end() const;

	private:

		// １フレームで初期化時確保メモリに移動できる要素数
		unsigned int m_moveNodeMaxNumPerFrame;

		// リソースを管理するためのハンドルを作るクラス
		ResourceHandleManager m_resourceHandleManager;

		// ハンドルから要素のポインタにアクセスするためのコンテナ
		std::unordered_map<unsigned int, ResourceNode> m_connectNodeMap;

		// 初期化時に確保したメモリにインスタンスを作るコンテナ
		HeapArray<NodeType, Allocator> m_staticNode;

		// 動的にメモリを確保してインスタンスを作るコンテナ
		std::list<NodeType, Allocator> m_dynamicNode;
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	template<class NodeType, class Allocator>
	inline ResourceContainer<NodeType, Allocator>::ResourceContainer(const ResourceContainerInitParam& initParam)
		: m_moveNodeMaxNumPerFrame(initParam.moveNodeMaxNumPerFrame)
		, m_staticNode(initParam.staticNodeNum)
	{
	}

	// 初期化時に確保したメモリに空きがあった場合、最も寿命が長い動的に確保したメモリを使用したインスタンスを初期化時確保メモリに移動する
	template<class NodeType, class Allocator>
	inline void ResourceContainer<NodeType, Allocator>::memoryCompaction()
	{
		// 移動した要素のポインタを持つリスト
		std::forward_list<std::pair<NodeType*, NodeType*>> movingNodeList;

		// 1フレームでの初期化時確保メモリに移動できる要素数分ループする
		for (unsigned int i = 0; i < m_moveNodeMaxNumPerFrame; ++i)
		{
			// 自作のコンテナにメモリの空きが無かったら関数を抜ける
			if (!m_staticNode.canCreateNode()) return;

			// 移動前（std::listの最後尾）でのポインタを取得
			NodeType* beforePtr = &(*--std::end(m_dynamicNode));

			// std::listの最後尾から要素を自作コンテナにムーブする
			HeapArrayIndexPtrPair<NodeType> createResult = m_staticNode.create(std::move(*beforePtr));

			// 移動前、移送先のポインタのペアをリストに追加
			movingNodeList.push_front(std::make_pair(beforePtr, createResult.ptr));

			// std::listの最後尾から要素を削除する
			m_dynamicNode.pop_back();
		}

		// リソースのインスタンスにアクセスするためのコンテナの要素が指すポインタを更新する
		for (auto& pair : m_connectNodeMap)
		{
			for (const auto& movingNode : movingNodeList)
			{
				if (pair.ptr == movingNode.first)
				{
					pair.ptr		= movingNode.second;
					pair.isStatic	= true;
				}
			}
		}
	}

	// コンストラクタ引数を渡してインスタンスを作り、そのハンドルを返す
	template<class NodeType, class Allocator>
	template<class ...ConstructorArgs>
	inline unsigned int ResourceContainer<NodeType, Allocator>::create(ConstructorArgs && ...args)
	{
		// 未使用のハンドルを取得する
		unsigned int handle = m_resourceHandleManager.createHandle();

		// 自作のコンテナにメモリの空きがあったら
		if (m_staticNode.canCreateNode())
		{
			// 自作のコンテナに要素を作成し、作成した要素の情報を取得する
			HeapArrayIndexPtrPair<NodeType> createdNode = m_staticNode.emplace(std::forward<ConstructorArgs>(args)...);

			// ハンドルから要素にアクセスするためのコンテナの要素を作る
			ResourceNode tempNode{ createdNode.ptr, true };
			m_connectNodeMap.emplace(handle, tempNode);
		}
		else
		{
			// std::listに要素を作成し、作成した要素の情報を取得する
			NodeType& createdNode = m_dynamicNode.emplace_front(std::forward<ConstructorArgs>(args)...);

			// ハンドルから要素にアクセスするためのコンテナの要素を作る
			ResourceNode tempNode{ &createdNode, false };
			m_connectNodeMap.emplace(handle, tempNode);
		}

		// 取得したハンドルを返す
		return handle;
	}

	// ハンドルを引数に対応するポインタを取得する
	// ※ハンドルに対応したリソースが無かった場合、nullptrを返す
	template<class NodeType, class Allocator>
	inline NodeType* ResourceContainer<NodeType, Allocator>::getMatchHandlePtr(unsigned int handle) const
	{
		if (m_connectNodeMap.count(handle) == 0U) return nullptr;

		return m_connectNodeMap.at(handle).ptr;
	}

	// 引数のハンドルのインスタンスを削除（メモリ解放）する
	template<class NodeType, class Allocator>
	inline void ResourceContainer<NodeType, Allocator>::erase(unsigned int handle)
	{
		// 引数のハンドルに対応したリソースが無かったら何もしない
		if (m_connectNodeMap.count(handle) == 0) return;

		// 引数のハンドルに対応したリソースを取得する
		ResourceContainer<NodeType, Allocator>::ResourceNode eraseNode = m_connectNodeMap.at(handle);

		// 自作のコンテナを使って管理されていたら
		if (eraseNode.isStatic)
		{
			// 自作のコンテナから削除する
			m_staticNode.erase(&eraseNode.ptr);
		}
		// std::listで管理されていたら
		else
		{
			// std::listから削除する
			m_dynamicNode.remove_if([&eraseNode](const auto& node) { return &node == eraseNode.ptr; });
		}

		// 削除したポインタとハンドルを結びつけているコンテナの要素を削除する
		m_connectNodeMap.erase(handle);

		// 引数のハンドルを未使用状態に変更する
		m_resourceHandleManager.endUseHandle(handle);
	}

	// 全てのインスタンスを削除（メモリ解放）する
	template<class NodeType, class Allocator>
	inline void ResourceContainer<NodeType, Allocator>::clear()
	{
		// 自作のコンテナの要素を全て開放する
		m_staticNode.clear();

		// std::listの要素を全て開放する
		m_dynamicNode.clear();

		// リソースを管理するためのハンドルを作るクラスを初期化する
		m_resourceHandleManager.reset();
	}

	template<class NodeType, class Allocator>
	inline typename ResourceContainer<NodeType, Allocator>::iterator ResourceContainer<NodeType, Allocator>::begin()
	{
		return ResourceContainer<NodeType, Allocator>::iterator(
			(std::begin(m_staticNode) != std::end(m_staticNode)),
			std::begin(m_staticNode),
			std::end(m_staticNode),
			std::begin(m_dynamicNode),
			std::end(m_dynamicNode)
		);
	}

	template<class NodeType, class Allocator>
	inline typename ResourceContainer<NodeType, Allocator>::const_iterator ResourceContainer<NodeType, Allocator>::begin() const
	{
		return ResourceContainer<NodeType, Allocator>::const_iterator(
			(std::begin(m_staticNode) != std::end(m_staticNode)),
			std::begin(m_staticNode),
			std::end(m_staticNode),
			std::begin(m_dynamicNode),
			std::end(m_dynamicNode)
		);
	}

	template<class NodeType, class Allocator>
	inline typename ResourceContainer<NodeType, Allocator>::iterator ResourceContainer<NodeType, Allocator>::end()
	{
		static auto returnValue = ResourceContainer<NodeType, Allocator>::iterator(
			false,
			std::end(m_staticNode),
			std::end(m_staticNode),
			std::end(m_dynamicNode),
			std::end(m_dynamicNode)
		);

		return returnValue;
	}

	template<class NodeType, class Allocator>
	inline typename ResourceContainer<NodeType, Allocator>::const_iterator ResourceContainer<NodeType, Allocator>::end() const
	{
		static auto returnValue = ResourceContainer<NodeType, Allocator>::const_iterator(
			false,
			std::end(m_staticNode),
			std::end(m_staticNode),
			std::end(m_dynamicNode),
			std::end(m_dynamicNode)
		);

		return returnValue;
	}
}
#endif // !RESOURCE_CONTAINER_H_