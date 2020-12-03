#ifndef HEAP_ARRAY_ITERATOR_H_
#define HEAP_ARRAY_ITERATOR_H_

#include <limits>
#include <iterator>
#include <memory>
#include <vector>
#include "UseNodeCheckBitFlagArrayPtr.h"

namespace tktkContainer
{
	template <class NodeType, class Allocator>
	class PreAllocContainer;

	// �C�e���[�^�[
	template <class NodeType>
	struct PreAllocContainerIterator
	{
		friend PreAllocContainer;

		using iterator_category = std::forward_iterator_tag;
		using value_type		= NodeType;
		using difference_type	= std::ptrdiff_t;
		using pointer			= NodeType*;
		using reference			= NodeType&;

	private:

		// �v���C�x�[�g�R���X�g���N�^�B
		explicit PreAllocContainerIterator(NodeType* arrayTopPos);
		PreAllocContainerIterator(size_t index, size_t arrayMaxSize, NodeType* arrayTopPos, const UseNodeCheckBitFlagArrayWeakPtr& arrayNodeUseCheckBitFlagPtr);

	private:

		static PreAllocContainerIterator<NodeType> getBegin(size_t arrayMaxSize, NodeType* arrayTopPos, const UseNodeCheckBitFlagArrayWeakPtr& arrayNodeUseCheckBitFlagPtr);
		static PreAllocContainerIterator<NodeType> getEnd(NodeType* arrayTopPos);

	public:

		// �R�s�[�R���X�g���N�^�݂̂̓p�u���b�N��
		PreAllocContainerIterator(const PreAllocContainerIterator<NodeType>& other);

	public:

		// �C�e���[�^�ɕK�v�Ȏ���
		const NodeType& operator*() const;
		NodeType& operator*();

		PreAllocContainerIterator<NodeType>& operator++();
		PreAllocContainerIterator<NodeType> operator++(int);

		bool operator==(const PreAllocContainerIterator<NodeType>& other) const;
		bool operator!=(const PreAllocContainerIterator<NodeType>& other) const;

	private:

		size_t			m_index;
		size_t			m_arrayMaxSize;
		NodeType*		m_arrayTopPos;
		UseNodeCheckBitFlagArrayWeakPtr	m_arrayNodeUseCheckBitFlagPtr{};
	};
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�͊֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	template<class NodeType>
	inline PreAllocContainerIterator<NodeType>::PreAllocContainerIterator(NodeType* arrayTopPos)
		: m_index(std::numeric_limits<size_t>::max())
		, m_arrayMaxSize(0U)
		, m_arrayTopPos(arrayTopPos)
	{
	}

	template<class NodeType>
	inline PreAllocContainerIterator<NodeType>::PreAllocContainerIterator(size_t index, size_t arrayMaxSize, NodeType* arrayTopPos, const UseNodeCheckBitFlagArrayWeakPtr& arrayNodeUseCheckBitFlagPtr)
		: m_index((index == 0) ? index : std::numeric_limits<size_t>::max())
		, m_arrayMaxSize(arrayMaxSize)
		, m_arrayTopPos(arrayTopPos)
		, m_arrayNodeUseCheckBitFlagPtr(arrayNodeUseCheckBitFlagPtr)
	{
	}

	template<class NodeType>
	inline PreAllocContainerIterator<NodeType> PreAllocContainerIterator<NodeType>::getBegin(size_t arrayMaxSize, NodeType* arrayTopPos, const UseNodeCheckBitFlagArrayWeakPtr& arrayNodeUseCheckBitFlagPtr)
	{
		static auto returnValue = PreAllocContainerIterator<NodeType>(0U, arrayMaxSize, arrayTopPos, arrayNodeUseCheckBitFlagPtr);

		// �T�C�Y�[���������ꍇ�Aend�Ɠ����v�f��Ԃ�
		if (returnValue.m_arrayMaxSize == 0U) return getEnd(arrayTopPos);

		// �������擪�̃C�e���[�^�[�����g�p��ԂȂ�C���N�������g����
		if ((returnValue.m_arrayNodeUseCheckBitFlagPtr->at(returnValue.m_index / 32U) & (1U << (returnValue.m_index % 32U))) == 0U)
		{
			auto incrementReturnValue = returnValue;

			return ++incrementReturnValue;
		}
		return returnValue;
	}

	template<class NodeType>
	inline PreAllocContainerIterator<NodeType> PreAllocContainerIterator<NodeType>::getEnd(NodeType* arrayTopPos)
	{
		static auto returnValue = PreAllocContainerIterator<NodeType>(arrayTopPos);

		return returnValue;
	}

	template<class NodeType>
	inline PreAllocContainerIterator<NodeType>::PreAllocContainerIterator(const PreAllocContainerIterator<NodeType>& other)
		: m_index(other.m_index)
		, m_arrayMaxSize(other.m_arrayMaxSize)
		, m_arrayTopPos(other.m_arrayTopPos)
		, m_arrayNodeUseCheckBitFlagPtr(other.m_arrayNodeUseCheckBitFlagPtr)
	{
	}

	template<class NodeType>
	inline const NodeType& PreAllocContainerIterator<NodeType>::operator*() const
	{
		// �C���f�b�N�X���͈͊O��\���Ă��邩�A�C���X�^���X���Ɏg�p����Ă��Ȃ����������w�����C�e���[�^�[�̏ꍇ
		if (m_index == std::numeric_limits<size_t>::max() || (m_arrayNodeUseCheckBitFlagPtr->at(m_index / 32U) & (1U << (m_index % 32U))) == 0U)
		{
			throw std::out_of_range("HeapArray iterator out of range");
		}

		return *(m_arrayTopPos + m_index);
	}

	template<class NodeType>
	inline NodeType& PreAllocContainerIterator<NodeType>::operator*()
	{
		// �C���f�b�N�X���͈͊O��\���Ă��邩�A�C���X�^���X���Ɏg�p����Ă��Ȃ����������w�����C�e���[�^�[�̏ꍇ
		if (m_index == std::numeric_limits<size_t>::max() || (m_arrayNodeUseCheckBitFlagPtr->at(m_index / 32U) & (1U << (m_index % 32U))) == 0U)
		{
			throw std::out_of_range("HeapArray iterator out of range");
		}

		return *(m_arrayTopPos + m_index);
	}

	template<class NodeType>
	inline PreAllocContainerIterator<NodeType>& PreAllocContainerIterator<NodeType>::operator++()
	{
		if (m_index >= std::numeric_limits<size_t>::max() - 1U) return *this;

		++m_index;

		// �C���X�^���X������C�e���[�^�[��������܂ŃC���N�������g����
		while ((m_arrayNodeUseCheckBitFlagPtr->at(m_index / 32U) & (1U << (m_index % 32U))) == 0U)
		{
			++m_index;

			if (m_index > m_arrayMaxSize)
			{
				m_index			= std::numeric_limits<size_t>::max();
				return *this;
			}
		}
		return *this;
	}

	template<class NodeType>
	inline PreAllocContainerIterator<NodeType> PreAllocContainerIterator<NodeType>::operator++(int)
	{
		PreAllocContainerIterator result = *this;

		if (m_index >= std::numeric_limits<size_t>::max() - 1U) return result;

		++m_index;

		// �C���X�^���X������C�e���[�^�[��������܂ŃC���N�������g����
		while ((m_arrayNodeUseCheckBitFlagPtr.lock()->at(m_index / 32U) & (1U << (m_index % 32U))) == 0U)
		{
			++m_index;

			if (m_index > m_arrayMaxSize)
			{
				m_index			= std::numeric_limits<size_t>::max();
				return result;
			}
		}
		return result;
	}

	template<class NodeType>
	inline bool PreAllocContainerIterator<NodeType>::operator==(const PreAllocContainerIterator<NodeType>& other) const
	{
		return !(*this != other);
	}

	template<class NodeType>
	inline bool PreAllocContainerIterator<NodeType>::operator!=(const PreAllocContainerIterator<NodeType>& other) const
	{
		return m_index != other.m_index || m_arrayTopPos != other.m_arrayTopPos;
	}
}
#endif // !HEAP_ARRAY_ITERATOR_H_