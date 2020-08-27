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

		// ���������Ɋm�ۂ����������ɋ󂫂��������ꍇ�A�ł��������������I�Ɋm�ۂ������������g�p�����C���X�^���X�����������m�ۃ������Ɉړ�����
		void memoryCompaction();

	public:

		// �R���X�g���N�^������n���ăC���X�^���X�����A���̃n���h����Ԃ�
		template <class... ConstructorArgs>
		unsigned int create(ConstructorArgs&&... args);

		// �n���h���������ɑΉ�����|�C���^���擾����
		// ���n���h���ɑΉ��������\�[�X�����������ꍇ�Anullptr��Ԃ�
		NodeType* getMatchHandlePtr(unsigned int handle) const;

		// �����̃n���h���̃C���X�^���X���폜�i����������j����
		void erase(unsigned int handle);

		// �S�ẴC���X�^���X���폜�i����������j����
		void clear();

	public:

		ResourceContainer<NodeType, Allocator>::iterator		begin();
		ResourceContainer<NodeType, Allocator>::const_iterator	begin() const;

		ResourceContainer<NodeType, Allocator>::iterator		end();
		ResourceContainer<NodeType, Allocator>::const_iterator	end() const;

	private:

		// �P�t���[���ŏ��������m�ۃ������Ɉړ��ł���v�f��
		unsigned int m_moveNodeMaxNumPerFrame;

		// ���\�[�X���Ǘ����邽�߂̃n���h�������N���X
		ResourceHandleManager m_resourceHandleManager;

		// �n���h������v�f�̃|�C���^�ɃA�N�Z�X���邽�߂̃R���e�i
		std::unordered_map<unsigned int, ResourceNode> m_connectNodeMap;

		// ���������Ɋm�ۂ����������ɃC���X�^���X�����R���e�i
		HeapArray<NodeType, Allocator> m_staticNode;

		// ���I�Ƀ��������m�ۂ��ăC���X�^���X�����R���e�i
		std::list<NodeType, Allocator> m_dynamicNode;
	};
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�͊֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	template<class NodeType, class Allocator>
	inline ResourceContainer<NodeType, Allocator>::ResourceContainer(const ResourceContainerInitParam& initParam)
		: m_moveNodeMaxNumPerFrame(initParam.moveNodeMaxNumPerFrame)
		, m_staticNode(initParam.staticNodeNum)
	{
	}

	// ���������Ɋm�ۂ����������ɋ󂫂��������ꍇ�A�ł��������������I�Ɋm�ۂ������������g�p�����C���X�^���X�����������m�ۃ������Ɉړ�����
	template<class NodeType, class Allocator>
	inline void ResourceContainer<NodeType, Allocator>::memoryCompaction()
	{
		// �ړ������v�f�̃|�C���^�������X�g
		std::forward_list<std::pair<NodeType*, NodeType*>> movingNodeList;

		// 1�t���[���ł̏��������m�ۃ������Ɉړ��ł���v�f�������[�v����
		for (unsigned int i = 0; i < m_moveNodeMaxNumPerFrame; ++i)
		{
			// ����̃R���e�i�Ƀ������̋󂫂�����������֐��𔲂���
			if (!m_staticNode.canCreateNode()) return;

			// �ړ��O�istd::list�̍Ō���j�ł̃|�C���^���擾
			NodeType* beforePtr = &(*--std::end(m_dynamicNode));

			// std::list�̍Ō������v�f������R���e�i�Ƀ��[�u����
			HeapArrayIndexPtrPair<NodeType> createResult = m_staticNode.create(std::move(*beforePtr));

			// �ړ��O�A�ڑ���̃|�C���^�̃y�A�����X�g�ɒǉ�
			movingNodeList.push_front(std::make_pair(beforePtr, createResult.ptr));

			// std::list�̍Ō������v�f���폜����
			m_dynamicNode.pop_back();
		}

		// ���\�[�X�̃C���X�^���X�ɃA�N�Z�X���邽�߂̃R���e�i�̗v�f���w���|�C���^���X�V����
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

	// �R���X�g���N�^������n���ăC���X�^���X�����A���̃n���h����Ԃ�
	template<class NodeType, class Allocator>
	template<class ...ConstructorArgs>
	inline unsigned int ResourceContainer<NodeType, Allocator>::create(ConstructorArgs && ...args)
	{
		// ���g�p�̃n���h�����擾����
		unsigned int handle = m_resourceHandleManager.createHandle();

		// ����̃R���e�i�Ƀ������̋󂫂���������
		if (m_staticNode.canCreateNode())
		{
			// ����̃R���e�i�ɗv�f���쐬���A�쐬�����v�f�̏����擾����
			HeapArrayIndexPtrPair<NodeType> createdNode = m_staticNode.emplace(std::forward<ConstructorArgs>(args)...);

			// �n���h������v�f�ɃA�N�Z�X���邽�߂̃R���e�i�̗v�f�����
			ResourceNode tempNode{ createdNode.ptr, true };
			m_connectNodeMap.emplace(handle, tempNode);
		}
		else
		{
			// std::list�ɗv�f���쐬���A�쐬�����v�f�̏����擾����
			NodeType& createdNode = m_dynamicNode.emplace_front(std::forward<ConstructorArgs>(args)...);

			// �n���h������v�f�ɃA�N�Z�X���邽�߂̃R���e�i�̗v�f�����
			ResourceNode tempNode{ &createdNode, false };
			m_connectNodeMap.emplace(handle, tempNode);
		}

		// �擾�����n���h����Ԃ�
		return handle;
	}

	// �n���h���������ɑΉ�����|�C���^���擾����
	// ���n���h���ɑΉ��������\�[�X�����������ꍇ�Anullptr��Ԃ�
	template<class NodeType, class Allocator>
	inline NodeType* ResourceContainer<NodeType, Allocator>::getMatchHandlePtr(unsigned int handle) const
	{
		if (m_connectNodeMap.count(handle) == 0U) return nullptr;

		return m_connectNodeMap.at(handle).ptr;
	}

	// �����̃n���h���̃C���X�^���X���폜�i����������j����
	template<class NodeType, class Allocator>
	inline void ResourceContainer<NodeType, Allocator>::erase(unsigned int handle)
	{
		// �����̃n���h���ɑΉ��������\�[�X�����������牽�����Ȃ�
		if (m_connectNodeMap.count(handle) == 0) return;

		// �����̃n���h���ɑΉ��������\�[�X���擾����
		ResourceContainer<NodeType, Allocator>::ResourceNode eraseNode = m_connectNodeMap.at(handle);

		// ����̃R���e�i���g���ĊǗ�����Ă�����
		if (eraseNode.isStatic)
		{
			// ����̃R���e�i����폜����
			m_staticNode.erase(&eraseNode.ptr);
		}
		// std::list�ŊǗ�����Ă�����
		else
		{
			// std::list����폜����
			m_dynamicNode.remove_if([&eraseNode](const auto& node) { return &node == eraseNode.ptr; });
		}

		// �폜�����|�C���^�ƃn���h�������т��Ă���R���e�i�̗v�f���폜����
		m_connectNodeMap.erase(handle);

		// �����̃n���h���𖢎g�p��ԂɕύX����
		m_resourceHandleManager.endUseHandle(handle);
	}

	// �S�ẴC���X�^���X���폜�i����������j����
	template<class NodeType, class Allocator>
	inline void ResourceContainer<NodeType, Allocator>::clear()
	{
		// ����̃R���e�i�̗v�f��S�ĊJ������
		m_staticNode.clear();

		// std::list�̗v�f��S�ĊJ������
		m_dynamicNode.clear();

		// ���\�[�X���Ǘ����邽�߂̃n���h�������N���X������������
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