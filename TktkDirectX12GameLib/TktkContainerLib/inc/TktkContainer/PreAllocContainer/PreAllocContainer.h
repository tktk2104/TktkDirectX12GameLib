#ifndef PRE_ALLOC_STATIC_CONTAINER_H_
#define PRE_ALLOC_STATIC_CONTAINER_H_

#include <limits>
#include <stdexcept>
#include <memory>
#include <vector>
#include "PreAllocContainerIterator.h"
#include "UseNodeCheckBitFlagArrayPtr.h"

namespace tktkContainer
{
	// 事前にメモリを確保するコンテナ
	template <class NodeType, class Allocator = std::allocator<NodeType>>
	class PreAllocContainer
	{
	public:

		// イテレーターの定義
		using iterator			=  PreAllocContainerIterator<NodeType>;
		using const_iterator	=  PreAllocContainerIterator<const NodeType>;

	public:

		explicit PreAllocContainer(size_t maxInstanceCount);
		~PreAllocContainer();

	public:

		// コンテナの最大インスタンス数
		size_t maxInstanceCount() const;

		// 新たなインスタンスを作るだけの空きがあるか？
		bool canCreateInstance() const;

	public:

		// このコンテナでのインスタンスインデックスとインスタンスのポインタのペア
		struct IndexPtrPair
		{
			size_t		index;
			NodeType*	ptr;
		};

	public:

		// 確保したメモリの先頭から使用可能なメモリが存在するか探し、見つけたら引数の参照をムーブする
		IndexPtrPair create(NodeType&& node);

		// 確保したメモリの特定位置（先頭アドレス + (index * sizeof(NodeType))）のメモリが未使用ならば見つけたら引数の参照をムーブする
		NodeType* createAt(size_t index, NodeType&& node);

		// 確保したメモリの先頭から使用可能なメモリが存在するか探し、見つけたら引数を使ってインスタンスを作った上でそのアドレスのポインタとインデックスを返し、見つからなかったらnullptrと０を返す
		template <class... ConstructorArgs>
		IndexPtrPair emplace(ConstructorArgs&&... args);

		// 確保したメモリの特定位置（先頭アドレス + (index * sizeof(NodeType))）のメモリが未使用ならば引数を使ってインスタンスを作った上でそのアドレスのポインタを返し、使用済みだったらnullptrを返す
		template <class... ConstructorArgs>
		NodeType* emplaceAt(size_t index, ConstructorArgs&&... args);

		// 指定したポインタが使用済みであればそのポインタが指すインスタンスをデストラクトする
		void erase(NodeType** eraseNode);

		// 確保したメモリの特定位置（先頭アドレス + (index * sizeof(NodeType))）のメモリが使用中ならば、そのメモリに存在するインスタンスをデストラクトする
		void eraseAt(size_t index);

		// 使用中のメモリに存在するインスタンスを全てデストラクトする
		void clear();

	public:

		// 指定したインデックスのポインタを取得する（インデックスが指し示すメモリが未使用ならnullPtrを返す）
		NodeType* at(size_t index);

		// 指定したインデックスのポインタを取得する（const版）（インデックスが指し示すメモリが未使用ならnullPtrを返す）
		const NodeType* at(size_t index) const;

		// コンテナの最初の要素を表すイテレーターを取得する
		PreAllocContainer<NodeType, Allocator>::iterator		begin();
		// コンテナの最初の要素を表すイテレーターを取得する（const版）
		PreAllocContainer<NodeType, Allocator>::const_iterator	begin() const;

		// コンテナの最後の“次の”要素を表すイテレーターを取得する
		PreAllocContainer<NodeType, Allocator>::iterator		end();
		// コンテナの最後の“次の”要素を表すイテレーターを取得する（const版）
		PreAllocContainer<NodeType, Allocator>::const_iterator	end() const;

	public:

		// ビットフラグ変数１つにつき、何個のインスタンスが対応しているか？
		constexpr static size_t BitFlagCapacity{ sizeof(unsigned int) * 8U };

	private:

		// アロケータ
		Allocator	m_allocator;

		// コンテナの最大インスタンス数（「m_maxInstanceCount * sizeof(NodeType)」の大きさのヒープメモリが自身の配列のために確保される）
		size_t		m_maxInstanceCount;

		// 現在のインスタンス数
		size_t		m_curInstanceCount{ 0U };

		// 確保したメモリの先頭アドレス
		NodeType*	m_allocateTopPos;
		
		// 配列の要素を使用しているかを管理するビットデータ（uint配列として作成）
		UseNodeCheckBitFlagArraySharedPtr m_bitFlagArray;
	};

//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	template<class NodeType, class Allocator>
	inline PreAllocContainer<NodeType, Allocator>::PreAllocContainer(size_t maxInstanceCount)
		: m_maxInstanceCount(maxInstanceCount)
		, m_allocateTopPos(std::allocator_traits<Allocator>::allocate(m_allocator, m_maxInstanceCount))	// メモリを確保
	{
		// ※uint１つで32個の要素を管理可能
		m_bitFlagArray = std::make_shared<std::vector<unsigned int>>((1U + m_maxInstanceCount / BitFlagCapacity), 0U);
	}

	template<class NodeType, class Allocator>
	inline PreAllocContainer<NodeType, Allocator>::~PreAllocContainer()
	{
		// 使用中メモリのみをデストラクトする
		for (size_t i = 0; i < m_maxInstanceCount; i++)
		{
			if ((m_bitFlagArray->at(i / BitFlagCapacity) & (1U << (i % BitFlagCapacity))) != 0U)
			{
				std::allocator_traits<Allocator>::destroy(m_allocator, m_allocateTopPos + i);
			}
		}

		// 確保したメモリを開放する
		std::allocator_traits<Allocator>::deallocate(m_allocator, m_allocateTopPos, m_maxInstanceCount);
	}

	template<class NodeType, class Allocator>
	inline size_t PreAllocContainer<NodeType, Allocator>::maxInstanceCount() const
	{
		return m_maxInstanceCount;
	}

	// 新たなインスタンスを作るだけの空きがあるか？
	template<class NodeType, class Allocator>
	inline bool PreAllocContainer<NodeType, Allocator>::canCreateInstance() const
	{
		return m_curInstanceCount < m_maxInstanceCount;
	}

	// 確保したメモリの先頭から使用可能なメモリが存在するか探し、見つけたら引数の参照をムーブする
	template<class NodeType, class Allocator>
	inline typename PreAllocContainer<NodeType, Allocator>::IndexPtrPair PreAllocContainer<NodeType, Allocator>::create(NodeType&& node)
	{
		return emplace(std::move(node));
	}

	// 確保したメモリの特定位置（先頭アドレス + (index * sizeof(NodeType))）のメモリが未使用ならば見つけたら引数の参照をムーブする
	template<class NodeType, class Allocator>
	inline NodeType* PreAllocContainer<NodeType, Allocator>::createAt(size_t index, NodeType&& node)
	{
		return emplaceAt(index, std::move(node));
	}

	// 確保したメモリの先頭から使用可能なメモリが存在するか探し、見つけたら引数を使ってインスタンスを作った上でそのアドレスのポインタを返し、見つからなかったらuintMaxを返す
	template<class NodeType, class Allocator>
	template<class ...ConstructorArgs>
	inline typename PreAllocContainer<NodeType, Allocator>::IndexPtrPair PreAllocContainer<NodeType, Allocator>::emplace(ConstructorArgs&& ...args)
	{
		// 現在のインスタンス数が作成可能最大数だったら
		if (!canCreateInstance())
		{
			return { std::numeric_limits<unsigned int>::max(), nullptr };
		}

		for (size_t i = 0U; i < m_maxInstanceCount; i++)
		{
			// 未使用メモリを見つけたら
			if ((m_bitFlagArray->at(i / BitFlagCapacity) & (1U << (i % BitFlagCapacity))) == 0U)
			{
				// コンストラクトする
				std::allocator_traits<Allocator>::construct(m_allocator, m_allocateTopPos + i, std::forward<ConstructorArgs>(args)...);

				// 作成したインスタンスの存在するメモリを使用中にする
				m_bitFlagArray->at(i / BitFlagCapacity) |= (1U << (i % BitFlagCapacity));

				// 現在のインスタンス数を１増やす
				m_curInstanceCount++;

				// 作成したインスタンスのポインタを返す
				return { i, (m_allocateTopPos + i) };
			}
		}
		return { std::numeric_limits<unsigned int>::max(), nullptr };
	}

	// 確保したメモリの特定位置（先頭アドレス + (index * sizeof(NodeType))）のメモリが未使用ならば引数を使ってインスタンスを作った上でそのアドレスのポインタを返し、使用済みだったらnullptrを返す
	template<class NodeType, class Allocator>
	template<class ...ConstructorArgs>
	inline NodeType* PreAllocContainer<NodeType, Allocator>::emplaceAt(size_t index, ConstructorArgs&& ...args)
	{
		// 現在のインスタンス数が作成可能最大数か、インデックスが範囲外を指していたら
		if (!canCreateInstance() || index >= m_maxInstanceCount)
		{
			return nullptr;
		}

		// 引数のインデックスが未使用メモリを指していたら
		if ((m_bitFlagArray->at(index / BitFlagCapacity) & (1U << (index % BitFlagCapacity))) == 0U)
		{
			// コンストラクトする
			std::allocator_traits<Allocator>::construct(m_allocator, m_allocateTopPos + index, std::forward<ConstructorArgs>(args)...);

			// 作成したインスタンスの存在するメモリを使用中にする
			m_bitFlagArray->at(index / BitFlagCapacity) |= (1U << (index % BitFlagCapacity));

			// 現在のインスタンス数を１増やす
			m_curInstanceCount++;

			// 作成したインスタンスのポインタを返す
			return (m_allocateTopPos + index);
		}
		return nullptr;
	}

	// 指定したポインタが使用済みであればそのポインタが指すインスタンスをデストラクトする
	template<class NodeType, class Allocator>
	inline void PreAllocContainer<NodeType, Allocator>::erase(NodeType** eraseNode)
	{
		// ポインタが不正だったら何もしない
		if ((*eraseNode) < m_allocateTopPos || reinterpret_cast<size_t>(*eraseNode) > (reinterpret_cast<size_t>(m_allocateTopPos) + sizeof(NodeType) * (m_maxInstanceCount - 1U)))
		{
			return;
		}

		size_t index = (reinterpret_cast<size_t>((*eraseNode)) - reinterpret_cast<size_t>(m_allocateTopPos)) / sizeof(NodeType);

		// 引数のインデックスが使用中メモリを指していたら
		if ((m_bitFlagArray->at(index / BitFlagCapacity) & (1U << (index % BitFlagCapacity))) != 0U)
		{
			// 引数のインデックスのインスタンスをデストラクトする
			std::allocator_traits<Allocator>::destroy(m_allocator, m_allocateTopPos + index);

			// 削除したインスタンスのメモリを未使用にする
			m_bitFlagArray->at(index / BitFlagCapacity) ^= (1U << (index % BitFlagCapacity));

			// 現在のインスタンス数を１減らす
			m_curInstanceCount--;

			(*eraseNode) = nullptr;
		}
	}

	// 確保したメモリの特定位置（先頭アドレス + (index * sizeof(NodeType))）のメモリが使用中ならば、そのメモリに存在するインスタンスをデストラクトする
	template<class NodeType, class Allocator>
	inline void PreAllocContainer<NodeType, Allocator>::eraseAt(size_t index)
	{
		// 引数のインデックスが使用中メモリを指していたら
		if ((m_bitFlagArray->at(index / BitFlagCapacity) & (1U << (index % BitFlagCapacity))) != 0U)
		{
			// 引数のインデックスのインスタンスをデストラクトする
			std::allocator_traits<Allocator>::destroy(m_allocator, m_allocateTopPos + index);

			// 削除したインスタンスのメモリを未使用にする
			m_bitFlagArray->at(index / BitFlagCapacity) ^= (1U << (index % BitFlagCapacity));

			// 現在のインスタンス数を１減らす
			m_curInstanceCount--;
		}
	}

	// 使用中のメモリに存在するインスタンスを全てデストラクトする
	template<class NodeType, class Allocator>
	inline void PreAllocContainer<NodeType, Allocator>::clear()
	{
		// 使用中メモリのみをデストラクトする
		for (size_t i = 0; i < m_maxInstanceCount; i++)
		{
			if ((m_bitFlagArray->at(i / BitFlagCapacity) & (1U << (i % BitFlagCapacity))) != 0U)
			{
				std::allocator_traits<Allocator>::destroy(m_allocator, m_allocateTopPos + i);

				// 削除したインスタンスのメモリを未使用にする
				m_bitFlagArray->at(i / BitFlagCapacity) ^= (1U << (i % BitFlagCapacity));
			}
		}

		// 現在のインスタンス数を０にする
		m_curInstanceCount = 0U;
	}

	// 指定したインデックスのポインタを取得する（インデックスが指し示すメモリが未使用ならnullPtrを返す）
	template<class NodeType, class Allocator>
	inline NodeType* PreAllocContainer<NodeType, Allocator>::at(size_t index) 
	{
		// 引数のインデックスが未使用メモリを指していたらnullptrを返す
		if ((m_bitFlagArray->at(index / BitFlagCapacity) & (1U << (index % BitFlagCapacity))) == 0U) return nullptr;

		return (m_allocateTopPos + index);
	}

	// 指定したインデックスのポインタを取得する（const版）（インデックスが指し示すメモリが未使用ならnullPtrを返す）
	template<class NodeType, class Allocator>
	inline const NodeType* PreAllocContainer<NodeType, Allocator>::at(size_t index) const
	{
		// 引数のインデックスが未使用メモリを指していたらnullptrを返す
		if ((m_bitFlagArray->at(index / BitFlagCapacity) & (1U << (index % BitFlagCapacity))) == 0U) return nullptr;

		return (m_allocateTopPos + index);
	}

	template<class NodeType, class Allocator>
	inline typename PreAllocContainer<NodeType, Allocator>::iterator PreAllocContainer<NodeType, Allocator>::begin()
	{
		return PreAllocContainer<NodeType, Allocator>::iterator::getBegin(m_maxInstanceCount, m_allocateTopPos, m_bitFlagArray);
	}

	template<class NodeType, class Allocator>
	inline typename PreAllocContainer<NodeType, Allocator>::iterator PreAllocContainer<NodeType, Allocator>::end()
	{
		return PreAllocContainer<NodeType, Allocator>::iterator::getEnd(m_allocateTopPos);
	}

	template<class NodeType, class Allocator>
	inline typename PreAllocContainer<NodeType, Allocator>::const_iterator PreAllocContainer<NodeType, Allocator>::begin() const
	{
		return PreAllocContainer<NodeType, Allocator>::const_iterator::getBegin(m_maxInstanceCount, m_allocateTopPos, m_bitFlagArray);
	}

	template<class NodeType, class Allocator>
	inline typename PreAllocContainer<NodeType, Allocator>::const_iterator PreAllocContainer<NodeType, Allocator>::end() const
	{
		return PreAllocContainer<NodeType, Allocator>::const_iterator::getEnd(m_allocateTopPos);
	}
}
#endif // !PRE_ALLOC_STATIC_CONTAINER_H_

// 没コード
//// 配列の使用中ビットフラグを32ビットずつ巡回
//for (unsigned int i = 0; i < m_arrayNodeUseCheckBitFlagsArraySize; i++)
//{
//	// 全部のフラグが立っていたら何もしない
//	if (m_arrayNodeUseCheckBitFlagsArray[i] == 0xffffffff) continue;
//
//	// 各ビット毎に判定する
//	for (unsigned int j = 0; j < 32U; j++)
//	{
//		if ((m_arrayNodeUseCheckBitFlagsArray[i] & (1U << j)) != 0U)
//		{
//			emplacePoint = (i * 32U) + j;
//			break;
//		}
//	}
//	break;
//}