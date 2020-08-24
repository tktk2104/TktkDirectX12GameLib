#ifndef HEAP_ARRAY_H_
#define HEAP_ARRAY_H_

#include <limits>
#include <stdexcept>
#include <memory>
#include "HeapArrayIterator.h"

namespace tktkContainer
{
	template <class NodeType>
	struct HeapArrayIndexPtrPair
	{
		unsigned int	index;
		NodeType* ptr;
	};

	template <class NodeType, class Allocator = std::allocator<NodeType>>
	class HeapArray
	{
	public:

		using iterator			=  HeapArrayIterator<NodeType>;
		using const_iterator	=  HeapArrayIterator<const NodeType>;

	public:

		explicit HeapArray(unsigned int arrayMaxSize);
		~HeapArray();

	public:

		unsigned int arrayMaxSize() const;

		// 新たなインスタンスを作るだけの空きがあるか？
		bool canCreateNode() const;

	public:

		// 確保したメモリの先頭から使用可能なメモリが存在するか探し、見つけたら引数の参照をムーブする
		HeapArrayIndexPtrPair<NodeType> create(NodeType&& node);

		// 確保したメモリの特定位置（先頭アドレス + (index * sizeof(NodeType))）のメモリが未使用ならば見つけたら引数の参照をムーブする
		NodeType* createAt(unsigned int index, NodeType&& node);

		// 確保したメモリの先頭から使用可能なメモリが存在するか探し、見つけたら引数を使ってインスタンスを作った上でそのアドレスのポインタとインデックスを返し、見つからなかったらnullptrと０を返す
		template <class... ConstructorArgs>
		HeapArrayIndexPtrPair<NodeType> emplace(ConstructorArgs&&... args);

		// 確保したメモリの特定位置（先頭アドレス + (index * sizeof(NodeType))）のメモリが未使用ならば引数を使ってインスタンスを作った上でそのアドレスのポインタを返し、使用済みだったらnullptrを返す
		template <class... ConstructorArgs>
		NodeType* emplaceAt(unsigned int index, ConstructorArgs&&... args);

		// 指定したポインタが使用済みであればそのポインタが指すインスタンスをデストラクトする
		void erase(NodeType** eraseNode);

		// 確保したメモリの特定位置（先頭アドレス + (index * sizeof(NodeType))）のメモリが使用中ならば、そのメモリに存在するインスタンスをデストラクトする
		void eraseAt(unsigned int index);

		// 使用中のメモリに存在するインスタンスを全てデストラクトする
		void clear();

	public:

		// 指定したインデックスのポインタを取得する（インデックスが指し示すメモリが未使用ならnullPtrを返す）
		NodeType* at(unsigned int index);

		// 指定したインデックスのポインタを取得する（const版）（インデックスが指し示すメモリが未使用ならnullPtrを返す）
		const NodeType* at(unsigned int index) const;

		HeapArray<NodeType, Allocator>::iterator		begin();
		HeapArray<NodeType, Allocator>::const_iterator	begin() const;

		HeapArray<NodeType, Allocator>::iterator		end();
		HeapArray<NodeType, Allocator>::const_iterator	end() const;

	private:

		// アロケータ
		Allocator		m_allocator;

		// 配列の最大数（「m_arrayMaxSize * sizeof(NodeType)」の大きさのヒープメモリが自身の配列のために確保される）
		unsigned int	m_arrayMaxSize;

		// 現在のインスタンス数
		unsigned int	m_curInstanceCount{ 0U };

		// 確保したメモリの先頭アドレス
		NodeType*		m_arrayTopPos;
		
		// 配列の要素を使用しているかを管理するビットデータ（uint配列として作成）
		unsigned int*	m_arrayNodeUseCheckBitFlag;
	};

//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	template<class NodeType, class Allocator>
	inline HeapArray<NodeType, Allocator>::HeapArray(unsigned int arrayMaxSize)
		: m_arrayMaxSize(arrayMaxSize)
		, m_arrayTopPos(std::allocator_traits<Allocator>::allocate(m_allocator, m_arrayMaxSize)) // メモリを確保
		, m_arrayNodeUseCheckBitFlag(new unsigned int[1U + (m_arrayMaxSize / 32U)])// ※uint１つで32個の要素を管理可能
	{
		// 配列要素使用管理ビットデータのフラグを全て切る。※memset()の第三引数はバイト数指定
		for (unsigned int i = 0; i < (1U + (m_arrayMaxSize / 32U)); i++)
		{
			m_arrayNodeUseCheckBitFlag[i] = 0U;
		}
	}

	template<class NodeType, class Allocator>
	inline HeapArray<NodeType, Allocator>::~HeapArray()
	{
		// 使用中メモリのみをデストラクトする
		for (unsigned int i = 0; i < m_arrayMaxSize; i++)
		{
			if ((m_arrayNodeUseCheckBitFlag[i / 32U] & (1U << (i % 32U))) != 0U)
			{
				std::allocator_traits<Allocator>::destroy(m_allocator, m_arrayTopPos + i);
			}
		}

		// 確保したメモリを開放する
		std::allocator_traits<Allocator>::deallocate(m_allocator, m_arrayTopPos, m_arrayMaxSize);

		// 配列要素使用管理ビットデータを開放する
		delete[] m_arrayNodeUseCheckBitFlag;
	}

	template<class NodeType, class Allocator>
	inline unsigned int HeapArray<NodeType, Allocator>::arrayMaxSize() const
	{
		return m_arrayMaxSize;
	}

	// 新たなインスタンスを作るだけの空きがあるか？
	template<class NodeType, class Allocator>
	inline bool HeapArray<NodeType, Allocator>::canCreateNode() const
	{
		return m_curInstanceCount < m_arrayMaxSize;
	}

	// 確保したメモリの先頭から使用可能なメモリが存在するか探し、見つけたら引数の参照をムーブする
	template<class NodeType, class Allocator>
	inline HeapArrayIndexPtrPair<NodeType> HeapArray<NodeType, Allocator>::create(NodeType&& node)
	{
		return emplace(std::move(node));
	}

	// 確保したメモリの特定位置（先頭アドレス + (index * sizeof(NodeType))）のメモリが未使用ならば見つけたら引数の参照をムーブする
	template<class NodeType, class Allocator>
	inline NodeType* HeapArray<NodeType, Allocator>::createAt(unsigned int index, NodeType&& node)
	{
		return emplaceAt(index, std::move(node));
	}

	// 確保したメモリの先頭から使用可能なメモリが存在するか探し、見つけたら引数を使ってインスタンスを作った上でそのアドレスのポインタを返し、見つからなかったらuintMaxを返す
	template<class NodeType, class Allocator>
	template<class ...ConstructorArgs>
	inline HeapArrayIndexPtrPair<NodeType> HeapArray<NodeType, Allocator>::emplace(ConstructorArgs&& ...args)
	{
		// 現在のインスタンス数が作成可能最大数だったら
		if (!canCreateNode())
		{
			return { std::numeric_limits<unsigned int>::max(), nullptr };
		}

		for (unsigned int i = 0U; i < m_arrayMaxSize; i++)
		{
			// 未使用メモリを見つけたら
			if ((m_arrayNodeUseCheckBitFlag[i / 32U] & (1U << (i % 32U))) == 0U)
			{
				// コンストラクトする
				std::allocator_traits<Allocator>::construct(m_allocator, m_arrayTopPos + i, std::forward<ConstructorArgs>(args)...);

				// 作成したインスタンスの存在するメモリを使用中にする
				m_arrayNodeUseCheckBitFlag[i / 32U] |= (1U << (i % 32U));

				// 現在のインスタンス数を１増やす
				m_curInstanceCount++;

				// 作成したインスタンスのポインタを返す
				return { i, (m_arrayTopPos + i) };
			}
		}
		return { std::numeric_limits<unsigned int>::max(), nullptr };
	}

	// 確保したメモリの特定位置（先頭アドレス + (index * sizeof(NodeType))）のメモリが未使用ならば引数を使ってインスタンスを作った上でそのアドレスのポインタを返し、使用済みだったらnullptrを返す
	template<class NodeType, class Allocator>
	template<class ...ConstructorArgs>
	inline NodeType* HeapArray<NodeType, Allocator>::emplaceAt(unsigned int index, ConstructorArgs&& ...args)
	{
		// 現在のインスタンス数が作成可能最大数か、インデックスが範囲外を指していたら
		if (!canCreateNode() || index >= m_arrayMaxSize)
		{
			return nullptr;
		}

		// 引数のインデックスが未使用メモリを指していたら
		if ((m_arrayNodeUseCheckBitFlag[index / 32U] & (1U << (index % 32U))) == 0U)
		{
			// コンストラクトする
			std::allocator_traits<Allocator>::construct(m_allocator, m_arrayTopPos + index, std::forward<ConstructorArgs>(args)...);

			// 作成したインスタンスの存在するメモリを使用中にする
			m_arrayNodeUseCheckBitFlag[index / 32U] |= (1U << (index % 32U));

			// 現在のインスタンス数を１増やす
			m_curInstanceCount++;

			// 作成したインスタンスのポインタを返す
			return (m_arrayTopPos + index);
		}
		return nullptr;
	}

	// 指定したポインタが使用済みであればそのポインタが指すインスタンスをデストラクトする
	template<class NodeType, class Allocator>
	inline void HeapArray<NodeType, Allocator>::erase(NodeType** eraseNode)
	{
		// ポインタが不正だったら何もしない
		if ((*eraseNode) < m_arrayTopPos || (*eraseNode) > (m_arrayTopPos * m_arrayMaxSize))
		{
			return;
		}

		// ポインタからインデックスを逆算する
		unsigned int index = (static_cast<unsigned int>((*eraseNode)) - static_cast<unsigned int>(m_arrayTopPos)) / sizeof(NodeType);

		// 引数のインデックスが使用中メモリを指していたら
		if ((m_arrayNodeUseCheckBitFlag[index / 32U] & (1U << (index % 32U))) != 0U)
		{
			// 引数のインデックスのインスタンスをデストラクトする
			std::allocator_traits<Allocator>::destroy(m_allocator, m_arrayTopPos + index);

			// 削除したインスタンスのメモリを未使用にする
			m_arrayNodeUseCheckBitFlag[index / 32U] ^= (1U << (index % 32U));

			// 現在のインスタンス数を１減らす
			m_curInstanceCount--;

			(*eraseNode) = nullptr;
		}
	}

	// 確保したメモリの特定位置（先頭アドレス + (index * sizeof(NodeType))）のメモリが使用中ならば、そのメモリに存在するインスタンスをデストラクトする
	template<class NodeType, class Allocator>
	inline void HeapArray<NodeType, Allocator>::eraseAt(unsigned int index)
	{
		// 引数のインデックスが使用中メモリを指していたら
		if ((m_arrayNodeUseCheckBitFlag[index / 32U] & (1U << (index % 32U))) != 0U)
		{
			// 引数のインデックスのインスタンスをデストラクトする
			std::allocator_traits<Allocator>::destroy(m_allocator, m_arrayTopPos + index);

			// 削除したインスタンスのメモリを未使用にする
			m_arrayNodeUseCheckBitFlag[index / 32U] ^= (1U << (index % 32U));

			// 現在のインスタンス数を１減らす
			m_curInstanceCount--;
		}
	}

	// 使用中のメモリに存在するインスタンスを全てデストラクトする
	template<class NodeType, class Allocator>
	inline void HeapArray<NodeType, Allocator>::clear()
	{
		// 使用中メモリのみをデストラクトする
		for (unsigned int i = 0; i < m_arrayMaxSize; i++)
		{
			if ((m_arrayNodeUseCheckBitFlag[i / 32U] & (1U << (i % 32U))) != 0U)
			{
				std::allocator_traits<Allocator>::destroy(m_allocator, m_arrayTopPos + i);

				// 削除したインスタンスのメモリを未使用にする
				m_arrayNodeUseCheckBitFlag[i / 32U] ^= (1U << (i % 32U));
			}
		}

		// 現在のインスタンス数を０にする
		m_curInstanceCount = 0U;
	}

	// 指定したインデックスのポインタを取得する（インデックスが指し示すメモリが未使用ならnullPtrを返す）
	template<class NodeType, class Allocator>
	inline NodeType* HeapArray<NodeType, Allocator>::at(unsigned int index) 
	{
		// 引数のインデックスが未使用メモリを指していたらnullptrを返す
		if ((m_arrayNodeUseCheckBitFlag[index / 32U] & (1U << (index % 32U))) == 0U) return nullptr;

		return (m_arrayTopPos + index);
	}

	// 指定したインデックスのポインタを取得する（const版）（インデックスが指し示すメモリが未使用ならnullPtrを返す）
	template<class NodeType, class Allocator>
	inline const NodeType* HeapArray<NodeType, Allocator>::at(unsigned int index) const
	{
		// 引数のインデックスが未使用メモリを指していたらnullptrを返す
		if ((m_arrayNodeUseCheckBitFlag[index / 32U] & (1U << (index % 32U))) == 0U) return nullptr;

		return (m_arrayTopPos + index);
	}

	template<class NodeType, class Allocator>
	inline typename HeapArray<NodeType, Allocator>::iterator HeapArray<NodeType, Allocator>::begin()
	{
		return HeapArray<NodeType, Allocator>::iterator::getBegin(m_arrayMaxSize, m_arrayTopPos, m_arrayNodeUseCheckBitFlag);
	}

	template<class NodeType, class Allocator>
	inline typename HeapArray<NodeType, Allocator>::iterator HeapArray<NodeType, Allocator>::end()
	{
		return HeapArray<NodeType, Allocator>::iterator::getEnd(m_arrayTopPos);
	}

	template<class NodeType, class Allocator>
	inline typename HeapArray<NodeType, Allocator>::const_iterator HeapArray<NodeType, Allocator>::begin() const
	{
		return HeapArray<NodeType, Allocator>::const_iterator::getBegin(m_arrayMaxSize, m_arrayTopPos, m_arrayNodeUseCheckBitFlag);
	}

	template<class NodeType, class Allocator>
	inline typename HeapArray<NodeType, Allocator>::const_iterator HeapArray<NodeType, Allocator>::end() const
	{
		return HeapArray<NodeType, Allocator>::const_iterator::getEnd(m_arrayTopPos);
	}
}
#endif // !HEAP_ARRAY_H_

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