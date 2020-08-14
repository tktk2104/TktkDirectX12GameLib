#ifndef COMPONENT_SATRT_LIST_H_
#define COMPONENT_SATRT_LIST_H_

#include <forward_list>
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasStartChecker.h>
#include "ComponentStartFuncRunner.h"

namespace tktk
{
	// �w��̃N���X���ϐ���start�֐��������Ă��邩���肷��e���v���[�g���^�̃G�C���A�X�e���v���[�g
	template <class ComponentType>
	using has_start = std::enable_if_t<has_start_checker<ComponentType*, void>::value>*;
	template <class ComponentType>
	using not_has_start = std::enable_if_t<!has_start_checker<ComponentType*, void>::value>*;

	// �R���|�[�l���g�́ustart�v�֐������s���郊�X�g
	class ComponentStartList
	{
	public:

		ComponentStartList() = default;

	public:

		// �����̃R���|�[�l���g�̌^���ustart�v�֐��������Ă����玩�g�̃R���e�i�ɒǉ�����
		template <class ComponentType, has_start<ComponentType> = nullptr>
		void add(const std::weak_ptr<ComponentType>& componentPtr);
		template <class ComponentType, not_has_start<ComponentType> = nullptr>
		void add(const std::weak_ptr<ComponentType>& componentPtr);

		// �ustart()�v�֐����Ă�
		void runStartFunc();

		// �O�t���[���ɒǉ����ꂽ�R���|�[�l���g�����C�����X�g�ɒǉ�����
		void movePreFrameAddedNode();

		// ���Ɂustart�v�֐����Ă΂ꂽ���A���S�t���O�������Ă���R���|�[�l���g���폜����
		void removeDeadComponent();

	private:

		std::forward_list<ComponentStartFuncRunner> m_startList;
		std::forward_list<ComponentStartFuncRunner> m_nextFrameAddNodeList;
	};
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�͊֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	// �����̃R���|�[�l���g�̌^���ustart()�v�֐��������Ă����玩�g�̃R���e�i�ɒǉ�����
	template<class ComponentType, has_start<ComponentType>>
	inline void ComponentStartList::add(const std::weak_ptr<ComponentType>& componentPtr)
	{
		m_nextFrameAddNodeList.emplace_front(componentPtr);
	}
	template<class ComponentType, not_has_start<ComponentType>>
	inline void ComponentStartList::add(const std::weak_ptr<ComponentType>& componentPtr) {}
}
#endif // !COMPONENT_SATRT_LIST_H_