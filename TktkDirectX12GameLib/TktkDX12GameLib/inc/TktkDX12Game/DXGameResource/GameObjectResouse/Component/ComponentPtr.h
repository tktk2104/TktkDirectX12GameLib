#ifndef COMPONENT_PTR_H_
#define COMPONENT_PTR_H_

/* std::weak_ptr */
#include <memory>

namespace tktk
{
	// �R���|�[�l���g�̌^����ێ������|�C���^�N���X
	template <class ComponentType>
	class ComponentPtr
	{
		// ComponentBasePtr�̓t�����h�N���X
		friend class ComponentBasePtr;

	public:

		ComponentPtr() = default;

		explicit ComponentPtr(const std::weak_ptr<ComponentType>& weakPtr)
			: m_componentPtr(weakPtr) {}

	public:

		// �|�C���^�������؂ꂩ���肷��
		bool expired() const { return m_componentPtr.expired(); }

		// �����̃|�C���^�Ǝ��g�������|�C���^���w���Ă��邩���肷��
		bool isSame(const ComponentPtr<ComponentType>& other) const { return !m_componentPtr.expired() && !other.m_componentPtr.expired() && m_componentPtr.lock() == other.m_componentPtr.lock(); }

		// �|�C���^�̎g�p
		std::shared_ptr<ComponentType> operator ->() const
		{
			if (m_componentPtr.expired()) return nullptr;
			return m_componentPtr.lock();
		}

	private:

		std::weak_ptr<ComponentType> m_componentPtr;
	};
}
#endif // !COMPONENT_PTR_H_