#ifndef COMPONENT_BASE_H_
#define COMPONENT_BASE_H_

/* std::forward_list */
#include <forward_list>

/* funcUseType */
#include "ComponentBasePtr.h"
#include "ComponentPtr.h"

/* class member */
#include "ComponentCollisionFunc/CollisionGroupTypeCarrier.h"
#include "../GameObject/GameObjectPtr.h"

namespace tktk
{
	/*
	�R���|�[�l���g�̊��N���X
	<PolymorphismFunc>

	void awake();				// ��������i�R���X�g���N�^���Ă΂ꂽ��j�ɌĂ΂��
	void start();				// �����������̃t���[���̍ŏ��ɌĂ΂��
	void onEnable();			// ��A�N�e�B�u����A�N�e�B�u��ԂɈڍs�������ɌĂ΂��
	void onDisable();			// �A�N�e�B�u�����A�N�e�B�u��ԂɈڍs�������ɌĂ΂��
	void onDestroy();			// �폜�t���O���������u�ԁi�f�X�g���N�^���Ă΂��O�j�ɌĂ΂��
	void update();				// ���t���[���Ă΂��
	void beforeCollide();		// �Փ˔��肪�s���钼�O�ɌĂ΂��
	void afterCollide();		// �Փ˔��肪�s��ꂽ��ɌĂ΂��

	void afterChangeParent	(const tktk::GameObjectPtr& beforParent);	// �q�v�f���ύX���ꂽ��ɌĂ΂��
	void onCollisionEnter	(const tktk::GameObjectPtr& other);			// �ՓˊJ�n���ɌĂ΂��
	void onCollisionStay	(const tktk::GameObjectPtr& other);			// �Փ˒��ɌĂ΂��
	void onCollisionExit	(const tktk::GameObjectPtr& other);			// �ՓˏI�����ɌĂ΂��

	void handleMessage		(tktk::MessageTypeCarrier type, const tktk::MessageAttachment& attachment);	// ���b�Z�[�W���󂯎�������ɌĂ΂��
	*/
	class ComponentBase
	{
	public:

		ComponentBase(float drawPriority = 0.0f, CollisionGroupTypeCarrier collisionGroup = 0);
		virtual ~ComponentBase();

	public:

		// �`��D��x���擾����i�l���������قǐ�ɌĂ΂��j
		float getDrawPriority() const;

		// �Փ˔���O���[�v���擾����
		CollisionGroupTypeCarrier getCollisionGroup() const;

		// �A�N�e�B�u�t���O��ݒ肷��
		void setActive(bool activeFlag);

		// ���g���E��
		void destroy();

		// �A�N�e�B�u�t���O���擾����
		bool isActive() const;

		// ���S�t���O���擾����
		bool isDead() const;

		// �A�N�e�B�u�t���O�̕ύX����
		bool activeChangeCheck();

	public:

		// ���g�̏����I�u�W�F�N�g���擾����
		const GameObjectPtr& getGameObject() const;

		// ���g�̏����I�u�W�F�N�g�������Ă���e���v���[�g�����̌^�̃R���|�[�l���g���擾����
		// ���擾�ł��Ȃ������ꍇ��nullptr��Ԃ�
		// �������Y���R���|�[�l���g���������ꍇ�A�ŏ��Ɍ������P���擾����
		template <class ComponentType>
		ComponentPtr<ComponentType> getComponent() const
		{
			return getComponent(typeid(ComponentType)).castPtr<ComponentType>();
		}
		
		// �����̌^�̃R���|�[�l���g���擾����
		// ���擾�ł��Ȃ�������nullptr��Ԃ�
		// �������Y������R���|�[�l���g����������ŏ��Ɍ������P��Ԃ�
		ComponentBasePtr getComponent(std::type_index type) const;

		// ���g�̏����I�u�W�F�N�g�������Ă���e���v���[�g�����̌^�̃R���|�[�l���g��S�Ď擾����
		template <class ComponentType>
		std::forward_list<ComponentPtr<ComponentType>> getComponents() const
		{
			std::forward_list<ComponentPtr<ComponentType>> castPtrList;

			for (const auto& basePtr : getComponents(typeid(ComponentType)))
			{
				castPtrList.push_front(basePtr.castPtr<ComponentType>());
			}
			return castPtrList;
		}

		// �����̌^�̃R���|�[�l���g��S�Ď擾����
		std::forward_list<ComponentBasePtr> getComponents(std::type_index type) const;

	public:

		// ���g����������I�u�W�F�N�g��ݒ肷��
		void setUser(const GameObjectPtr& user);

	private:

		const float							m_drawPriority;
		const CollisionGroupTypeCarrier		m_collisionGroup;
		bool								m_isActive			{ true };
		bool								m_nextFrameActive	{ true };
		bool								m_isDead			{ false };
		GameObjectPtr						m_user				{ };
	};
}
#endif // !COMPONENT_BASE_H_