#ifndef COMPONENT_BASE_PTR_H_
#define COMPONENT_BASE_PTR_H_

/* std::weak_ptr */
#include <memory>

/* std::type_index */
#include <typeindex>

/* funcUseType */
#include "ComponentPtr.h"

namespace tktk
{
	/* class member */
	class ComponentBase;

	// �R���|�[�l���g�̌^�����B�������|�C���^�N���X
	class ComponentBasePtr
	{
	public:

		ComponentBasePtr() = default;

		ComponentBasePtr(std::type_index componentType, const std::weak_ptr<ComponentBase>& componentPtr);

		template <class ComponentType>
		ComponentBasePtr(const std::weak_ptr<ComponentType>& componentPtr)
			: m_componentType(typeid(ComponentType))
			, m_componentPtr(componentPtr) {}

		template <class ComponentType>
		ComponentBasePtr(const ComponentPtr<ComponentType>& componentPtr)
			: m_componentType(typeid(ComponentType))
			, m_componentPtr(componentPtr.m_componentPtr) {}

	public:

		// �|�C���^���擾
		std::shared_ptr<ComponentBase> operator ->() const;

		// �����̃|�C���^�Ǝ��g�������|�C���^���w���Ă��邩���肷��
		bool isSame(const ComponentBasePtr& other) const;

		// �����̃|�C���^�Ǝ��g�������|�C���^���w���Ă��邩���肷��
		template <class ComponentType>
		bool isSame(const ComponentPtr<ComponentType>& other) const { return other.isSame(castPtr<ComponentType>()); }

		// �e���v���[�g�����̌^�Ɏ��g�̃|�C���^���L���X�g�ł��邩���肷��
		template <class ComponentType>
		bool canCast() const { return canCast(typeid(ComponentType)); }

		// �����̌^�Ɏ��g�̃|�C���^���L���X�g�ł��邩���肷��
		bool canCast(std::type_index type) const;

		// �e���v���[�g�����̌^�ɃL���X�g�����uComponentPtr�v���擾����
		// �L���X�g�ł��Ȃ��������́uComponentPtr�v��Ԃ�
		template <class ComponentType>
		ComponentPtr<ComponentType> castPtr() const
		{
			if (canCast<ComponentType>())
			{
				return ComponentPtr<ComponentType>(std::dynamic_pointer_cast<ComponentType>(m_componentPtr.lock()));
			}
			return ComponentPtr<ComponentType>();
		}

		// �A�N�e�B�u�t���O��ύX����
		void setActive(bool isActive) const;

		// ���S�t���O���擾����
		bool isDead() const;

	private:

		std::type_index					m_componentType	{ typeid(void) };
		std::weak_ptr<ComponentBase>	m_componentPtr	{ };
	};
}
#endif // !COMPONENT_BASE_PTR_H_