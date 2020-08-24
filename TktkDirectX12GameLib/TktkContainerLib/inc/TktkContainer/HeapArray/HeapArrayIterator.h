#ifndef HEAP_ARRAY_ITERATOR_H_
#define HEAP_ARRAY_ITERATOR_H_

#include <iterator>
#include <memory>

namespace tktkContainer
{
	template <class NodeType, class Allocator>
	class HeapArray;

	// イテレーター
	template <class NodeType, class Allocator = std::allocator<NodeType>>
	struct HeapArrayIterator
	{
		friend HeapArray;

		using iterator_category = std::forward_iterator_tag;
		using value_type = NodeType;
		using difference_type = std::ptrdiff_t;
		using pointer = NodeType*;
		using reference = NodeType&;

	private:

		// プライベートコンストラクタ達
		explicit HeapArrayIterator(NodeType* arrayTopPos);
		HeapArrayIterator(unsigned int index, unsigned int arrayMaxSize, NodeType* arrayTopPos, unsigned int* arrayNodeUseCheckBitFlagPtr);

	private:

		static HeapArrayIterator<NodeType, Allocator> getBegin(unsigned int arrayMaxSize, NodeType* arrayTopPos, unsigned int* arrayNodeUseCheckBitFlagPtr);
		static HeapArrayIterator<NodeType, Allocator> getEnd(NodeType* arrayTopPos);

	public:

		// コピーコンストラクタのみはパブリックに
		HeapArrayIterator(const HeapArrayIterator<NodeType, Allocator>& other);

	public:

		// イテレータに必要な実装
		const NodeType& operator*() const;

		NodeType& operator*();

		HeapArrayIterator<NodeType, Allocator>& operator++();

		HeapArrayIterator<NodeType, Allocator> operator++(int);

		bool operator==(const HeapArrayIterator<NodeType, Allocator>& other) const;

		bool operator!=(const HeapArrayIterator<NodeType, Allocator>& other) const;

	private:

		unsigned int	m_index;
		unsigned int	m_arrayMaxSize;
		NodeType*		m_arrayTopPos;
		unsigned int*	m_arrayNodeUseCheckBitFlagPtr;
	};
	//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
	//┃ここから下は関数の実装
	//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

	template<class NodeType, class Allocator>
	inline HeapArrayIterator<NodeType, Allocator>::HeapArrayIterator(NodeType* arrayTopPos)
	{
		m_index = SIZE_MAX;
		m_arrayMaxSize = 0U;
		m_arrayTopPos = arrayTopPos;
		m_arrayNodeUseCheckBitFlagPtr = nullptr;
	}

	template<class NodeType, class Allocator>
	inline HeapArrayIterator<NodeType, Allocator>::HeapArrayIterator(unsigned int index, unsigned int arrayMaxSize, NodeType* arrayTopPos, unsigned int* arrayNodeUseCheckBitFlagPtr)
	{
		m_index = (index == 0 ? index : SIZE_MAX);
		m_arrayMaxSize = arrayMaxSize;
		m_arrayTopPos = arrayTopPos;
		m_arrayNodeUseCheckBitFlagPtr = arrayNodeUseCheckBitFlagPtr;
	}

	template<class NodeType, class Allocator>
	inline HeapArrayIterator<NodeType, Allocator> HeapArrayIterator<NodeType, Allocator>::getBegin(unsigned int arrayMaxSize, NodeType* arrayTopPos, unsigned int* arrayNodeUseCheckBitFlagPtr)
	{
		static auto returnValue = HeapArrayIterator<NodeType, Allocator>(0U, arrayMaxSize, arrayTopPos, arrayNodeUseCheckBitFlagPtr);

		// サイズゼロだった場合、endと同じ要素を返す
		if (returnValue.m_arrayMaxSize == 0U) return getEnd(arrayTopPos);

		// もしも先頭のイテレーターが未使用状態ならインクリメントする
		if ((returnValue.m_arrayNodeUseCheckBitFlagPtr[returnValue.m_index / 32U] & (1U << (returnValue.m_index % 32U))) == 0U)
		{
			auto incrementReturnValue = ++returnValue;

			return incrementReturnValue;
		}
		return returnValue;
	}

	template<class NodeType, class Allocator>
	inline HeapArrayIterator<NodeType, Allocator> HeapArrayIterator<NodeType, Allocator>::getEnd(NodeType* arrayTopPos)
	{
		static auto returnValue = HeapArrayIterator<NodeType, Allocator>(arrayTopPos);

		return returnValue;
	}

	template<class NodeType, class Allocator>
	inline HeapArrayIterator<NodeType, Allocator>::HeapArrayIterator(const HeapArrayIterator<NodeType, Allocator>& other)
	{
		m_index			= other.m_index;
		m_arrayMaxSize	= other.m_arrayMaxSize;
		m_arrayTopPos	= other.m_arrayTopPos;
		m_arrayNodeUseCheckBitFlagPtr = other.m_arrayNodeUseCheckBitFlagPtr;
	}

	template<class NodeType, class Allocator>
	inline const NodeType& HeapArrayIterator<NodeType, Allocator>::operator*() const
	{
		// インデックスが範囲外を表しているか、インスタンス化に使用されていないメモリを指したイテレーターの場合
		if (m_index == SIZE_MAX || (m_arrayNodeUseCheckBitFlagPtr[m_index / 32U] & (1U << (m_index % 32U))) == 0U)
		{
			throw std::out_of_range("HeapArray iterator out of range");
		}

		return *(m_arrayTopPos + m_index);
	}

	template<class NodeType, class Allocator>
	inline NodeType& HeapArrayIterator<NodeType, Allocator>::operator*()
	{
		// インデックスが範囲外を表しているか、インスタンス化に使用されていないメモリを指したイテレーターの場合
		if (m_index == SIZE_MAX || (m_arrayNodeUseCheckBitFlagPtr[m_index / 32U] & (1U << (m_index % 32U))) == 0U)
		{
			throw std::out_of_range("HeapArray iterator out of range");
		}

		return *(m_arrayTopPos + m_index);
	}

	template<class NodeType, class Allocator>
	inline HeapArrayIterator<NodeType, Allocator>& HeapArrayIterator<NodeType, Allocator>::operator++()
	{
		if (m_index >= SIZE_MAX - 1U) return *this;

		++m_index;

		// インスタンスがあるイテレーターを見つけるまでインクリメントする
		while ((m_arrayNodeUseCheckBitFlagPtr[m_index / 32U] & (1U << (m_index % 32U))) == 0U)
		{
			++m_index;

			if (m_index > m_arrayMaxSize)
			{
				m_index			= SIZE_MAX;
				return *this;
			}
		}
		return *this;
	}

	template<class NodeType, class Allocator>
	inline HeapArrayIterator<NodeType, Allocator> HeapArrayIterator<NodeType, Allocator>::operator++(int)
	{
		HeapArrayIterator result = *this;

		if (m_index >= SIZE_MAX - 1U) return result;

		++m_index;

		// インスタンスがあるイテレーターを見つけるまでインクリメントする
		while ((m_arrayNodeUseCheckBitFlagPtr[m_index / 32U] & (1U << (m_index % 32U))) == 0U)
		{
			++m_index;

			if (m_index > m_arrayMaxSize)
			{
				m_index			= SIZE_MAX;
				return result;
			}
		}
		return result;
	}

	template<class NodeType, class Allocator>
	inline bool HeapArrayIterator<NodeType, Allocator>::operator==(const HeapArrayIterator<NodeType, Allocator>& other) const
	{
		return !(*this != other);
	}

	template<class NodeType, class Allocator>
	inline bool HeapArrayIterator<NodeType, Allocator>::operator!=(const HeapArrayIterator<NodeType, Allocator>& other) const
	{
		return m_index != other.m_index || m_arrayTopPos != other.m_arrayTopPos;
	}
}
#endif // !HEAP_ARRAY_ITERATOR_H_