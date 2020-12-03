#ifndef SCENE_V_TABLE_H_
#define SCENE_V_TABLE_H_

/* std::weak_ptr */
#include <memory>

/* start_runner<> */
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasStartChecker.h>

/* update_runner<> */
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasUpdateChecker.h>

/* end_runner<> */
#include <TktkTemplateMetaLib/HasFuncCheck/CreatedStruct/HasEndChecker.h>

namespace tktk
{
	class SceneBase;

	// �V�[���N���X�̊֐����s�N���X
	struct SceneVTable
	{
		void (*start)	(const std::weak_ptr<SceneBase>&);
		void (*update)	(const std::weak_ptr<SceneBase>&);
		void (*end)		(const std::weak_ptr<SceneBase>&);
	};

	// �uSceneVTable�v����邽�߂ɕK�v�ȐÓI�֐��|�C���^
	template <class SceneType>
	struct SceneVTableInitializer
	{
		// �e���v���[�g�N���X�́ustart, update, end�v�֐��������Ă�������s����֐��̃|�C���^��ێ�����\����
		static SceneVTable m_vtable;

		// �����̃|�C���^�̎w�����Ԃ��ustart�v�֐��������Ă�������s����
		static void start(const std::weak_ptr<SceneBase>& self)
		{
			if (self.expired()) return;
			start_runner<void>::checkAndRun(std::dynamic_pointer_cast<SceneType>(self.lock()));
		}

		// �����̃|�C���^�̎w�����Ԃ��uupdate�v�֐��������Ă�������s����
		static void update(const std::weak_ptr<SceneBase>& self)
		{
			if (self.expired()) return;
			update_runner<void>::checkAndRun(std::dynamic_pointer_cast<SceneType>(self.lock()));
		}

		// �����̃|�C���^�̎w�����Ԃ��uend�v�֐��������Ă�������s����
		static void end(const std::weak_ptr<SceneBase>& self)
		{
			if (self.expired()) return;
			end_runner<void>::checkAndRun(std::dynamic_pointer_cast<SceneType>(self.lock()));
		}
	};

	// �e���v���[�g�N���X�́ustart, update, end�v�֐��������Ă�������s����֐��̃|�C���^��ێ�����\����
	template <class SceneType>
	SceneVTable SceneVTableInitializer<SceneType>::m_vtable =
	{
		&SceneVTableInitializer<SceneType>::start,
		&SceneVTableInitializer<SceneType>::update,
		&SceneVTableInitializer<SceneType>::end
	};
}
#endif // !SCENE_V_TABLE_H_