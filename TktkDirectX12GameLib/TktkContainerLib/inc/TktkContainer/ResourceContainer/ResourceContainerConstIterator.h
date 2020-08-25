#ifndef RESOURCE_CONTAINER_CONST_ITERATOR_H_
#define RESOURCE_CONTAINER_CONST_ITERATOR_H_

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
	class ResourceContainerConstIterator
	{
		friend ResourceContainer;

		using iterator_category	= std::forward_iterator_tag;
		using value_type		= const NodeType;
		using difference_type	= std::ptrdiff_t;
		using pointer			= const NodeType*;
		using reference			= const NodeType&;

	private:

		// プライベートコンストラクタ達
		ResourceContainerConstIterator(
			bool isStatic,
			const HeapArrayIterator<const NodeType>& curHeapArrayItr,
			const HeapArrayIterator<const NodeType>& endHeapArrayItr,
			const typename std::list<NodeType>::const_iterator& curListItr,
			const typename std::list<NodeType>::const_iterator& endListItr
		);

	public:

		// コピーコンストラクタのみはパブリックに
		ResourceContainerConstIterator(const ResourceContainerConstIterator<NodeType>& other);

	public:

		// イテレータに必要な実装
		const NodeType& operator*() const;

		ResourceContainerConstIterator<NodeType>& operator++();
		ResourceContainerConstIterator<NodeType> operator++(int);

		bool operator==(const ResourceContainerConstIterator<NodeType>& other) const;
		bool operator!=(const ResourceContainerConstIterator<NodeType>& other) const;

	private:

		bool							m_isStatic;

		HeapArrayIterator<const NodeType>		m_curHeapArrayItr;
		HeapArrayIterator<const NodeType>		m_endHeapArrayItr;

		typename std::list<NodeType>::const_iterator	m_curListItr;
		typename std::list<NodeType>::const_iterator	m_endListItr;
	};
//┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//┃ここから下は関数の実装
//┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━


	template<class NodeType>
	inline ResourceContainerConstIterator<NodeType>::ResourceContainerConstIterator(
		bool isStatic,
		const HeapArrayIterator<const NodeType>& curHeapArrayItr,
		const HeapArrayIterator<const NodeType>& endHeapArrayItr,
		const typename std::list<NodeType>::const_iterator& curListItr,
		const typename std::list<NodeType>::const_iterator& endListItr
	)
		: m_isStatic(isStatic)
		, m_curHeapArrayItr(curHeapArrayItr)
		, m_endHeapArrayItr(endHeapArrayItr)
		, m_curListItr(curListItr)
		, m_endListItr(endListItr)
	{
	}

	template<class NodeType>
	inline ResourceContainerConstIterator<NodeType>::ResourceContainerConstIterator(const ResourceContainerConstIterator<NodeType>& other)
		: m_isStatic(other.m_isStatic)
		, m_curHeapArrayItr(other.m_curHeapArrayItr)
		, m_endHeapArrayItr(other.m_endHeapArrayItr)
		, m_curListItr(other.m_curListItr)
		, m_endListItr(other.m_endListItr)
	{
	}

	template<class NodeType>
	inline const NodeType& ResourceContainerConstIterator<NodeType>::operator*() const
	{
		if (m_isStatic) return *m_curHeapArrayItr;

		return *m_curListItr;
	}

	template<class NodeType>
	inline ResourceContainerConstIterator<NodeType>& ResourceContainerConstIterator<NodeType>::operator++()
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
	inline ResourceContainerConstIterator<NodeType> ResourceContainerConstIterator<NodeType>::operator++(int)
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
	inline bool ResourceContainerConstIterator<NodeType>::operator==(const ResourceContainerConstIterator<NodeType>& other) const
	{
		return !(*this != other);
	}

	template<class NodeType>
	inline bool ResourceContainerConstIterator<NodeType>::operator!=(const ResourceContainerConstIterator<NodeType>& other) const
	{
		return m_isStatic != other.m_isStatic || m_curHeapArrayItr != other.m_curHeapArrayItr || m_curListItr != other.m_curListItr;
	}
}

#endif // !RESOURCE_CONTAINER_CONST_ITERATOR_H_
