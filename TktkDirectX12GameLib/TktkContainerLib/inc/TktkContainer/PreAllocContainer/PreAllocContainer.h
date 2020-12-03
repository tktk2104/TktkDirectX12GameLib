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
	// ���O�Ƀ��������m�ۂ���R���e�i
	template <class NodeType, class Allocator = std::allocator<NodeType>>
	class PreAllocContainer
	{
	public:

		// �C�e���[�^�[�̒�`
		using iterator			=  PreAllocContainerIterator<NodeType>;
		using const_iterator	=  PreAllocContainerIterator<const NodeType>;

	public:

		explicit PreAllocContainer(size_t maxInstanceCount);
		~PreAllocContainer();

	public:

		// �R���e�i�̍ő�C���X�^���X��
		size_t maxInstanceCount() const;

		// �V���ȃC���X�^���X����邾���̋󂫂����邩�H
		bool canCreateInstance() const;

	public:

		// ���̃R���e�i�ł̃C���X�^���X�C���f�b�N�X�ƃC���X�^���X�̃|�C���^�̃y�A
		struct IndexPtrPair
		{
			size_t		index;
			NodeType*	ptr;
		};

	public:

		// �m�ۂ����������̐擪����g�p�\�ȃ����������݂��邩�T���A������������̎Q�Ƃ����[�u����
		IndexPtrPair create(NodeType&& node);

		// �m�ۂ����������̓���ʒu�i�擪�A�h���X + (index * sizeof(NodeType))�j�̃����������g�p�Ȃ�Ό�����������̎Q�Ƃ����[�u����
		NodeType* createAt(size_t index, NodeType&& node);

		// �m�ۂ����������̐擪����g�p�\�ȃ����������݂��邩�T���A��������������g���ăC���X�^���X���������ł��̃A�h���X�̃|�C���^�ƃC���f�b�N�X��Ԃ��A������Ȃ�������nullptr�ƂO��Ԃ�
		template <class... ConstructorArgs>
		IndexPtrPair emplace(ConstructorArgs&&... args);

		// �m�ۂ����������̓���ʒu�i�擪�A�h���X + (index * sizeof(NodeType))�j�̃����������g�p�Ȃ�Έ������g���ăC���X�^���X���������ł��̃A�h���X�̃|�C���^��Ԃ��A�g�p�ς݂�������nullptr��Ԃ�
		template <class... ConstructorArgs>
		NodeType* emplaceAt(size_t index, ConstructorArgs&&... args);

		// �w�肵���|�C���^���g�p�ς݂ł���΂��̃|�C���^���w���C���X�^���X���f�X�g���N�g����
		void erase(NodeType** eraseNode);

		// �m�ۂ����������̓���ʒu�i�擪�A�h���X + (index * sizeof(NodeType))�j�̃��������g�p���Ȃ�΁A���̃������ɑ��݂���C���X�^���X���f�X�g���N�g����
		void eraseAt(size_t index);

		// �g�p���̃������ɑ��݂���C���X�^���X��S�ăf�X�g���N�g����
		void clear();

	public:

		// �w�肵���C���f�b�N�X�̃|�C���^���擾����i�C���f�b�N�X���w�����������������g�p�Ȃ�nullPtr��Ԃ��j
		NodeType* at(size_t index);

		// �w�肵���C���f�b�N�X�̃|�C���^���擾����iconst�Łj�i�C���f�b�N�X���w�����������������g�p�Ȃ�nullPtr��Ԃ��j
		const NodeType* at(size_t index) const;

		// �R���e�i�̍ŏ��̗v�f��\���C�e���[�^�[���擾����
		PreAllocContainer<NodeType, Allocator>::iterator		begin();
		// �R���e�i�̍ŏ��̗v�f��\���C�e���[�^�[���擾����iconst�Łj
		PreAllocContainer<NodeType, Allocator>::const_iterator	begin() const;

		// �R���e�i�̍Ō�́g���́h�v�f��\���C�e���[�^�[���擾����
		PreAllocContainer<NodeType, Allocator>::iterator		end();
		// �R���e�i�̍Ō�́g���́h�v�f��\���C�e���[�^�[���擾����iconst�Łj
		PreAllocContainer<NodeType, Allocator>::const_iterator	end() const;

	public:

		// �r�b�g�t���O�ϐ��P�ɂ��A���̃C���X�^���X���Ή����Ă��邩�H
		constexpr static size_t BitFlagCapacity{ sizeof(unsigned int) * 8U };

	private:

		// �A���P�[�^
		Allocator	m_allocator;

		// �R���e�i�̍ő�C���X�^���X���i�um_maxInstanceCount * sizeof(NodeType)�v�̑傫���̃q�[�v�����������g�̔z��̂��߂Ɋm�ۂ����j
		size_t		m_maxInstanceCount;

		// ���݂̃C���X�^���X��
		size_t		m_curInstanceCount{ 0U };

		// �m�ۂ����������̐擪�A�h���X
		NodeType*	m_allocateTopPos;
		
		// �z��̗v�f���g�p���Ă��邩���Ǘ�����r�b�g�f�[�^�iuint�z��Ƃ��č쐬�j
		UseNodeCheckBitFlagArraySharedPtr m_bitFlagArray;
	};

//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�͊֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	template<class NodeType, class Allocator>
	inline PreAllocContainer<NodeType, Allocator>::PreAllocContainer(size_t maxInstanceCount)
		: m_maxInstanceCount(maxInstanceCount)
		, m_allocateTopPos(std::allocator_traits<Allocator>::allocate(m_allocator, m_maxInstanceCount))	// ���������m��
	{
		// ��uint�P��32�̗v�f���Ǘ��\
		m_bitFlagArray = std::make_shared<std::vector<unsigned int>>((1U + m_maxInstanceCount / BitFlagCapacity), 0U);
	}

	template<class NodeType, class Allocator>
	inline PreAllocContainer<NodeType, Allocator>::~PreAllocContainer()
	{
		// �g�p���������݂̂��f�X�g���N�g����
		for (size_t i = 0; i < m_maxInstanceCount; i++)
		{
			if ((m_bitFlagArray->at(i / BitFlagCapacity) & (1U << (i % BitFlagCapacity))) != 0U)
			{
				std::allocator_traits<Allocator>::destroy(m_allocator, m_allocateTopPos + i);
			}
		}

		// �m�ۂ������������J������
		std::allocator_traits<Allocator>::deallocate(m_allocator, m_allocateTopPos, m_maxInstanceCount);
	}

	template<class NodeType, class Allocator>
	inline size_t PreAllocContainer<NodeType, Allocator>::maxInstanceCount() const
	{
		return m_maxInstanceCount;
	}

	// �V���ȃC���X�^���X����邾���̋󂫂����邩�H
	template<class NodeType, class Allocator>
	inline bool PreAllocContainer<NodeType, Allocator>::canCreateInstance() const
	{
		return m_curInstanceCount < m_maxInstanceCount;
	}

	// �m�ۂ����������̐擪����g�p�\�ȃ����������݂��邩�T���A������������̎Q�Ƃ����[�u����
	template<class NodeType, class Allocator>
	inline typename PreAllocContainer<NodeType, Allocator>::IndexPtrPair PreAllocContainer<NodeType, Allocator>::create(NodeType&& node)
	{
		return emplace(std::move(node));
	}

	// �m�ۂ����������̓���ʒu�i�擪�A�h���X + (index * sizeof(NodeType))�j�̃����������g�p�Ȃ�Ό�����������̎Q�Ƃ����[�u����
	template<class NodeType, class Allocator>
	inline NodeType* PreAllocContainer<NodeType, Allocator>::createAt(size_t index, NodeType&& node)
	{
		return emplaceAt(index, std::move(node));
	}

	// �m�ۂ����������̐擪����g�p�\�ȃ����������݂��邩�T���A��������������g���ăC���X�^���X���������ł��̃A�h���X�̃|�C���^��Ԃ��A������Ȃ�������uintMax��Ԃ�
	template<class NodeType, class Allocator>
	template<class ...ConstructorArgs>
	inline typename PreAllocContainer<NodeType, Allocator>::IndexPtrPair PreAllocContainer<NodeType, Allocator>::emplace(ConstructorArgs&& ...args)
	{
		// ���݂̃C���X�^���X�����쐬�\�ő吔��������
		if (!canCreateInstance())
		{
			return { std::numeric_limits<unsigned int>::max(), nullptr };
		}

		for (size_t i = 0U; i < m_maxInstanceCount; i++)
		{
			// ���g�p����������������
			if ((m_bitFlagArray->at(i / BitFlagCapacity) & (1U << (i % BitFlagCapacity))) == 0U)
			{
				// �R���X�g���N�g����
				std::allocator_traits<Allocator>::construct(m_allocator, m_allocateTopPos + i, std::forward<ConstructorArgs>(args)...);

				// �쐬�����C���X�^���X�̑��݂��郁�������g�p���ɂ���
				m_bitFlagArray->at(i / BitFlagCapacity) |= (1U << (i % BitFlagCapacity));

				// ���݂̃C���X�^���X�����P���₷
				m_curInstanceCount++;

				// �쐬�����C���X�^���X�̃|�C���^��Ԃ�
				return { i, (m_allocateTopPos + i) };
			}
		}
		return { std::numeric_limits<unsigned int>::max(), nullptr };
	}

	// �m�ۂ����������̓���ʒu�i�擪�A�h���X + (index * sizeof(NodeType))�j�̃����������g�p�Ȃ�Έ������g���ăC���X�^���X���������ł��̃A�h���X�̃|�C���^��Ԃ��A�g�p�ς݂�������nullptr��Ԃ�
	template<class NodeType, class Allocator>
	template<class ...ConstructorArgs>
	inline NodeType* PreAllocContainer<NodeType, Allocator>::emplaceAt(size_t index, ConstructorArgs&& ...args)
	{
		// ���݂̃C���X�^���X�����쐬�\�ő吔���A�C���f�b�N�X���͈͊O���w���Ă�����
		if (!canCreateInstance() || index >= m_maxInstanceCount)
		{
			return nullptr;
		}

		// �����̃C���f�b�N�X�����g�p���������w���Ă�����
		if ((m_bitFlagArray->at(index / BitFlagCapacity) & (1U << (index % BitFlagCapacity))) == 0U)
		{
			// �R���X�g���N�g����
			std::allocator_traits<Allocator>::construct(m_allocator, m_allocateTopPos + index, std::forward<ConstructorArgs>(args)...);

			// �쐬�����C���X�^���X�̑��݂��郁�������g�p���ɂ���
			m_bitFlagArray->at(index / BitFlagCapacity) |= (1U << (index % BitFlagCapacity));

			// ���݂̃C���X�^���X�����P���₷
			m_curInstanceCount++;

			// �쐬�����C���X�^���X�̃|�C���^��Ԃ�
			return (m_allocateTopPos + index);
		}
		return nullptr;
	}

	// �w�肵���|�C���^���g�p�ς݂ł���΂��̃|�C���^���w���C���X�^���X���f�X�g���N�g����
	template<class NodeType, class Allocator>
	inline void PreAllocContainer<NodeType, Allocator>::erase(NodeType** eraseNode)
	{
		// �|�C���^���s���������牽�����Ȃ�
		if ((*eraseNode) < m_allocateTopPos || reinterpret_cast<size_t>(*eraseNode) > (reinterpret_cast<size_t>(m_allocateTopPos) + sizeof(NodeType) * (m_maxInstanceCount - 1U)))
		{
			return;
		}

		size_t index = (reinterpret_cast<size_t>((*eraseNode)) - reinterpret_cast<size_t>(m_allocateTopPos)) / sizeof(NodeType);

		// �����̃C���f�b�N�X���g�p�����������w���Ă�����
		if ((m_bitFlagArray->at(index / BitFlagCapacity) & (1U << (index % BitFlagCapacity))) != 0U)
		{
			// �����̃C���f�b�N�X�̃C���X�^���X���f�X�g���N�g����
			std::allocator_traits<Allocator>::destroy(m_allocator, m_allocateTopPos + index);

			// �폜�����C���X�^���X�̃������𖢎g�p�ɂ���
			m_bitFlagArray->at(index / BitFlagCapacity) ^= (1U << (index % BitFlagCapacity));

			// ���݂̃C���X�^���X�����P���炷
			m_curInstanceCount--;

			(*eraseNode) = nullptr;
		}
	}

	// �m�ۂ����������̓���ʒu�i�擪�A�h���X + (index * sizeof(NodeType))�j�̃��������g�p���Ȃ�΁A���̃������ɑ��݂���C���X�^���X���f�X�g���N�g����
	template<class NodeType, class Allocator>
	inline void PreAllocContainer<NodeType, Allocator>::eraseAt(size_t index)
	{
		// �����̃C���f�b�N�X���g�p�����������w���Ă�����
		if ((m_bitFlagArray->at(index / BitFlagCapacity) & (1U << (index % BitFlagCapacity))) != 0U)
		{
			// �����̃C���f�b�N�X�̃C���X�^���X���f�X�g���N�g����
			std::allocator_traits<Allocator>::destroy(m_allocator, m_allocateTopPos + index);

			// �폜�����C���X�^���X�̃������𖢎g�p�ɂ���
			m_bitFlagArray->at(index / BitFlagCapacity) ^= (1U << (index % BitFlagCapacity));

			// ���݂̃C���X�^���X�����P���炷
			m_curInstanceCount--;
		}
	}

	// �g�p���̃������ɑ��݂���C���X�^���X��S�ăf�X�g���N�g����
	template<class NodeType, class Allocator>
	inline void PreAllocContainer<NodeType, Allocator>::clear()
	{
		// �g�p���������݂̂��f�X�g���N�g����
		for (size_t i = 0; i < m_maxInstanceCount; i++)
		{
			if ((m_bitFlagArray->at(i / BitFlagCapacity) & (1U << (i % BitFlagCapacity))) != 0U)
			{
				std::allocator_traits<Allocator>::destroy(m_allocator, m_allocateTopPos + i);

				// �폜�����C���X�^���X�̃������𖢎g�p�ɂ���
				m_bitFlagArray->at(i / BitFlagCapacity) ^= (1U << (i % BitFlagCapacity));
			}
		}

		// ���݂̃C���X�^���X�����O�ɂ���
		m_curInstanceCount = 0U;
	}

	// �w�肵���C���f�b�N�X�̃|�C���^���擾����i�C���f�b�N�X���w�����������������g�p�Ȃ�nullPtr��Ԃ��j
	template<class NodeType, class Allocator>
	inline NodeType* PreAllocContainer<NodeType, Allocator>::at(size_t index) 
	{
		// �����̃C���f�b�N�X�����g�p���������w���Ă�����nullptr��Ԃ�
		if ((m_bitFlagArray->at(index / BitFlagCapacity) & (1U << (index % BitFlagCapacity))) == 0U) return nullptr;

		return (m_allocateTopPos + index);
	}

	// �w�肵���C���f�b�N�X�̃|�C���^���擾����iconst�Łj�i�C���f�b�N�X���w�����������������g�p�Ȃ�nullPtr��Ԃ��j
	template<class NodeType, class Allocator>
	inline const NodeType* PreAllocContainer<NodeType, Allocator>::at(size_t index) const
	{
		// �����̃C���f�b�N�X�����g�p���������w���Ă�����nullptr��Ԃ�
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

// �v�R�[�h
//// �z��̎g�p���r�b�g�t���O��32�r�b�g������
//for (unsigned int i = 0; i < m_arrayNodeUseCheckBitFlagsArraySize; i++)
//{
//	// �S���̃t���O�������Ă����牽�����Ȃ�
//	if (m_arrayNodeUseCheckBitFlagsArray[i] == 0xffffffff) continue;
//
//	// �e�r�b�g���ɔ��肷��
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