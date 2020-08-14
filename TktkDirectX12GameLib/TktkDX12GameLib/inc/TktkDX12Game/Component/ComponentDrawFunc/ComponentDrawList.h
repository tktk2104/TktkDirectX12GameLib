#ifndef COMPONENT_DRAW_LIST_H_
#define COMPONENT_DRAW_LIST_H_

#include <forward_list>
#include <map>
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasDrawChecker.h>
#include "ComponentDrawFuncRunner.h"

namespace tktk
{
	// �w��̃N���X���ϐ���draw�֐��������Ă��邩���肷��e���v���[�g���^�̃G�C���A�X�e���v���[�g
	template <class ComponentType>
	using has_draw = std::enable_if_t<has_draw_checker<ComponentType*, void>::value>*;
	template <class ComponentType>
	using not_has_draw = std::enable_if_t<!has_draw_checker<ComponentType*, void>::value>*;

	// �R���|�[�l���g�̕`�揈�����s�����X�g
	class ComponentDrawList
	{
	public:

		ComponentDrawList() = default;

	public:

		// �`��D��x���Łudraw�v�֐����Ă�
		void runDrawFunc();

		// �O�t���[���ɒǉ����ꂽ�R���|�[�l���g�����C�����X�g�ɒǉ�����
		void movePreFrameAddedNode();

		// ���S�t���O�������Ă���R���|�[�l���g���폜����
		void removeDeadComponent();

	public:

		// �����̃R���|�[�l���g�̌^���udraw()�v�֐��������Ă����玩�g�̃R���e�i�ɒǉ�����
		template <class ComponentType, has_draw<ComponentType> = nullptr>
		void addComponent(const std::weak_ptr<ComponentType>& componentPtr);
		template <class ComponentType, not_has_draw<ComponentType> = nullptr>
		void addComponent(const std::weak_ptr<ComponentType>& componentPtr);

	private:

		std::multimap<float, ComponentDrawFuncRunner>					m_drawList;
		std::forward_list<std::pair<float, ComponentDrawFuncRunner>>	m_nextFrameAddNodeList;
	};
//������������������������������������������������������������������������������������������������������������������������������������������������������������������
//���������牺�͊֐��̎���
//������������������������������������������������������������������������������������������������������������������������������������������������������������������

	// �����̃R���|�[�l���g�̌^���udraw()�v�֐��������Ă����玩�g�̃R���e�i�ɒǉ�����
	template<class ComponentType, has_draw<ComponentType>>
	inline void ComponentDrawList::addComponent(const std::weak_ptr<ComponentType>& componentPtr)
	{
		m_nextFrameAddNodeList.emplace_front(componentPtr.lock()->getDrawPriority(), componentPtr);
	}
	template<class ComponentType, not_has_draw<ComponentType>>
	inline void ComponentDrawList::addComponent(const std::weak_ptr<ComponentType>& componentPtr) {}
}
#endif // !COMPONENT_DRAW_LIST_H_