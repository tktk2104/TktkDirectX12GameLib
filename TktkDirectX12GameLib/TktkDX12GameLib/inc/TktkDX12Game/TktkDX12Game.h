#ifndef TKTK_DX12_GAME_H_
#define TKTK_DX12_GAME_H_

/* std::forward_list */
#include <forward_list>

/* funcUseType */
#include <TktkMath/Structs/Vector2.h>
#include "EventMessage/MessageTypeCarrier.h"
#include "EventMessage/MessageAttachment.h"
#include "DXGameResource/GameObjectResouse/GameObject/GameObject.h"
#include "DXGameResource/GameObjectResouse/GameObject/GameObjectPtr.h"
#include "DXGameResource/GameObjectResouse/GameObject/GameObjectTagCarrier.h"
#include "DXGameResource/GameObjectResouse/Component/ComponentCollisionFunc/CollisionGroupTypeCarrier.h"
#include "UtilityProcessManager/InputManager/InputGetter/MouseInputGetter/MouseBtnType.h"
#include "UtilityProcessManager/InputManager/InputGetter/DirectInputWrapper/KeyboardInputGetter/KeybordKeyType.h"
#include "UtilityProcessManager/InputManager/InputGetter/DirectInputWrapper/GamePadInputGetter/GamePadBtnType.h"
#include "UtilityProcessManager/InputManager/CommandTypeManager/CommandIdCarrier.h"
#include "UtilityProcessManager/InputManager/CommandTypeManager/DirectionCommandId.h"
#include "UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemViewportType.h"
#include "UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemScissorRectType.h"
#include "UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemVertexBufferType.h"
#include "UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemIndexBufferType.h"
#include "UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemConstantBufferType.h"
#include "UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemTextureBufferType.h"
#include "UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemRenderTargetBufferType.h"
#include "UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemDepthStencilBufferType.h"
#include "UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemBasicDescriptorHeapType.h"
#include "UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemRtvDescriptorHeapType.h"
#include "UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemDsvDescriptorHeapType.h"
#include "UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemRootSignatureType.h"
#include "UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemPipeLineStateType.h"
#include "UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemCameraType.h"
#include "UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemLightType.h"
#include "UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemBasicMeshType.h"
#include "UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemBasicMeshMaterialType.h"
#include "UtilityProcessManager/ResourceHandleGetter/SystemResourceHandleGetter/IdType/SystemPostEffectMaterialType.h"
#include "UtilityProcessManager/ResourceHandleGetter/ResourceIdConverter/ResourceIdCarrier.h"

namespace tktk
{
	// �Q�[���̊e�폈�����Ă�
	// ���ׂ����������Ăт����ꍇ�́uDX12GameManager�v���g���Ă�������
	class DX12Game
	{
	//************************************************************
	/* �E�B���h�E�̏��� */
	public:

		// �E�B���h�E�T�C�Y���擾����
		static const tktkMath::Vector2& getWindowSize();

	//************************************************************
	/* �V�[���̏��� */
	public:

		// �V�[����L���ɂ���
		// �������őΉ����郊�\�[�X�n���h���ɕϊ������
		static void enableScene(ResourceIdCarrier id);

		// �V�[���𖳌��ɂ���
		// �������őΉ����郊�\�[�X�n���h���ɕϊ������
		static void disableScene(ResourceIdCarrier id);

	//************************************************************
	/* �Q�[���I�u�W�F�N�g�̏��� */
	public:

		// �S�Ă�GameObject�Ƀ��b�Z�[�W�𑗐M����
		static void sendMessageAll(MessageTypeCarrier type, const MessageAttachment& attachment = {});

		// �Q�[���I�u�W�F�N�g���쐬���A���̃|�C���^��Ԃ�
		static GameObjectPtr createGameObject();

		// �����̃^�O���������Q�[���I�u�W�F�N�g���擾����
		// ���Y���I�u�W�F�N�g�����������ꍇ�A���GameObjectPtr���擾����
		// �������Y���I�u�W�F�N�g���������ꍇ�A�ŏ��Ɍ������P���擾����
		static GameObjectPtr findGameObjectWithTag(GameObjectTagCarrier tag);

		// �����̃^�O���������Q�[���I�u�W�F�N�g��S�Ď擾����
		static std::forward_list<GameObjectPtr> findGameObjectsWithTag(GameObjectTagCarrier tag);

		// �����̃^�O���������Q�[���I�u�W�F�N�g��S�č폜����
		static void destroyGameObjectsWithTag(GameObjectTagCarrier tag);

	//************************************************************
	/* ���͊֌W�̏��� */
	public:

		// ID�ɑΉ��������͂�������Ă��邩�𔻒�
		static bool isPush(CommandIdCarrier commandId);
		// ID�ɑΉ��������͂�������n�߂����𔻒�
		static bool isTrigger(CommandIdCarrier commandId);

		// �w��̃{�^����������Ă��邩
		static bool isPush(MouseBtnType btnType);
		// �w��̃{�^����������n�߂����𔻒�
		static bool isTrigger(MouseBtnType btnType);
		
		// �w��̃L�[��������Ă��邩�𔻒�
		static bool isPush(KeybordKeyType keyType);
		// �w��̃L�[��������n�߂����𔻒�
		static bool isTrigger(KeybordKeyType keyType);

		// �w��̃{�^����������Ă��邩�𔻒�
		static bool isPush(GamePadBtnType btnType);
		// �w��̃{�^����������n�߂����𔻒�
		static bool isTrigger(GamePadBtnType btnType);

		// �ړ��������擾
		static const tktkMath::Vector2& moveVec();

		// ���_�ړ��������擾
		static const tktkMath::Vector2& lookVec();

		// �}�E�X�J�[�\���̍��W���擾����
		static tktkMath::Vector2 mousePos();

	//************************************************************
	/* �^�C���֌W�̏��� */
	public:

		// �o�ߎ��Ԃ�����������
		static void resetElapsedTime();

		// �O�t���[���Ƃ̎��Ԃ̍������߂�
		static float deltaTime();

		// �O�t���[���Ƃ̎��Ԃ̍������߂�iTimeScale�𖳎��j
		static float noScaleDeltaTime();

		// �v���O�������N�����Ă���̎��ԁi�b�j��Ԃ�
		static float getCurTimeSec();

		// �ő��deltaTime�̒l��ݒ�i���̐��j
		static void setMaximumDeltaTime(float maximumDeltaTime);

		// ���Ԃ̌o�ߑ��x�������擾����
		static float getTimeScale();

		// ���Ԃ̌o�ߑ��x������ݒ肷��i0.0�`float_max�j
		static void setTimeScale(float timeScaleRate);

		// ��ƂȂ�FPS��ݒ肷��
		static void setBaseFps(unsigned int baseFps = 60U);

		// ��ƂȂ�FPS���擾����
		static unsigned int getBaseFps();

		// �u�ԓI��FPS���擾����
		static float fps();

	//************************************************************
	/* �V�X�e���̃��\�[�X���g�����߂̃n���h�����擾���� */
	public:

		static size_t getSystemHandle(SystemViewportType type);
		static size_t getSystemHandle(SystemScissorRectType type);
		static size_t getSystemHandle(SystemVertexBufferType type);
		static size_t getSystemHandle(SystemIndexBufferType type);
		static size_t getSystemHandle(SystemCBufferType type);
		static size_t getSystemHandle(SystemTextureBufferType type);
		static size_t getSystemHandle(SystemRtBufferType type);
		static size_t getSystemHandle(SystemDsBufferType type);
		static size_t getSystemHandle(SystemBasicDescriptorHeapType type);
		static size_t getSystemHandle(SystemRtvDescriptorHeapType type);
		static size_t getSystemHandle(SystemDsvDescriptorHeapType type);
		static size_t getSystemHandle(SystemRootSignatureType type);
		static size_t getSystemHandle(SystemPipeLineStateType type);
		static size_t getSystemHandle(SystemCameraType type);
		static size_t getSystemHandle(SystemLightType type);
		static size_t getSystemHandle(SystemMeshType type);
		static size_t getSystemHandle(SystemMeshMaterialType type);
		static size_t getSystemHandle(SystemPostEffectMaterialType type);
	};
}
#endif // !TKTK_DX12_GAME_H_