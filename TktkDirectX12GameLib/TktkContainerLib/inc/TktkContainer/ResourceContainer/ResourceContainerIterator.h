#ifndef RESOURCE_CONTAINER_ITERATOR_H_
#define RESOURCE_CONTAINER_ITERATOR_H_

#include <type_traits>
#include <iterator>
#include <memory>
#include <list>
#include "../HeapArray/HeapArrayIterator.h"

namespace tktkContainer
{
	template <class NodeType, class Allocator>
	class ResourceContainer;

	template <class NodeType>
	class ResourceContainerIterator
	{
		friend ResourceContainer;

		using iterator_category = std::forward_iterator_tag;
		using value_type		= NodeType;
		using difference_type	= std::ptrdiff_t;
		using pointer			= NodeType*;
		using reference			= NodeType&;

	private:

		// プライベートコンストラクタ達
		ResourceContainerIterator(
			bool isStatic,
			const HeapArrayIterator<NodeType>& curHeapArrayItr,
			const HeapArrayIterator<NodeType>& endHeapArrayItr,
			const typename std::list<NodeType>::iterator& curListItr,
			const typename std::list<NodeType>::iterator& endListItr
		);

	public:

		// コピーコンストラクタのみはパブリックに
		ResourceContainerIterator(const ResourceContainerIterator<NodeType>& other);

	public:

		// イテレータに必要な実装
		NodeType& operator*();

		ResourceContainerIterator<NodeType>& operator++();
		ResourceContainerIterator<NodeType> operator++(int);

		bool operator==(const ResourceContainerIterator<NodeType>& other) const;
		bool operator!=(const ResourceContainerIterator<NodeType>& other) const;

	private:

		bool							m_isStatic;

		HeapArrayIterator<NodeType>		m_curHeapArrayItr;
		HeapArrayIterator<NodeType>		m_endHeapArrayItr;

		typename std::list<NodeType>::iterator	m_curListItr;
		typename std::list<NodeType>::iterator	m_endListItr;
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━


	template<class NodeType>
	inline ResourceContainerIterator<NodeType>::ResourceContainerIterator(
		bool isStatic,
		const HeapArrayIterator<NodeType>& curHeapArrayItr,
		const HeapArrayIterator<NodeType>& endHeapArrayItr,
		const typename std::list<NodeType>::iterator& curListItr,
		const typename std::list<NodeType>::iterator& endListItr
	)
		: m_isStatic(isStatic)
		, m_curHeapArrayItr(curHeapArrayItr)
		, m_endHeapArrayItr(endHeapArrayItr)
		, m_curListItr(curListItr)
		, m_endListItr(endListItr)
	{
	}

	template<class NodeType>
	inline ResourceContainerIterator<NodeType>::ResourceContainerIterator(const ResourceContainerIterator<NodeType>& other)
		: m_isStatic(other.m_isStatic)
		, m_curHeapArrayItr(other.m_curHeapArrayItr)
		, m_endHeapArrayItr(other.m_endHeapArrayItr)
		, m_curListItr(other.m_curListItr)
		, m_endListItr(other.m_endListItr)
	{
	}

	template<class NodeType>
	inline NodeType& ResourceContainerIterator<NodeType>::operator*()
	{
		if (m_isStatic) return *m_curHeapArrayItr;

		return *m_curListItr;
	}

	template<class NodeType>
	inline ResourceContainerIterator<NodeType>& ResourceContainerIterator<NodeType>::operator++()
	{
		if (m_isStatic)
		{
			if (++m_curHeapArrayItr == m_endHeapArrayItr)
			{
				m_isStatic = false;
			}
		}
		else if (m_curListItr != m_endListItr)
		{
			++m_curListItr;
		}
		return *this;
	}

	template<class NodeType>
	inline ResourceContainerIterator<NodeType> ResourceContainerIterator<NodeType>::operator++(int)
	{
		HeapArrayIterator result = *this;

		if (m_isStatic)
		{
			if (++m_curHeapArrayItr == m_endHeapArrayItr)
			{
				m_isStatic = false;
			}
		}
		else if (m_curListItr != m_endListItr)
		{
			++m_curListItr;
		}
		return result;
	}

	template<class NodeType>
	inline bool ResourceContainerIterator<NodeType>::operator==(const ResourceContainerIterator<NodeType>& other) const
	{
		return !(*this != other);
	}

	template<class NodeType>
	inline bool ResourceContainerIterator<NodeType>::operator!=(const ResourceContainerIterator<NodeType>& other) const
	{
		return m_isStatic != other.m_isStatic || m_curHeapArrayItr != other.m_curHeapArrayItr || m_curListItr != other.m_curListItr;
	}
}
#endif // !RESOURCE_CONTAINER_ITERATOR_H_
