#ifndef TKTK_DX12_GAME_H_
#define TKTK_DX12_GAME_H_

/* std::string */
#include <string>

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

		// �Q�[���`��G���A�T�C�Y���擾����
		static const tktkMath::Vector2& getDrawGameAreaSize();

		// �X�N���[���T�C�Y���擾����
		static const tktkMath::Vector2& getScreenSize();

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
		static const tktkMath::Vector2& getMoveInput();

		// ���_�ړ��������擾
		static const tktkMath::Vector2& getLookInput();

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
	/* �|�X�g�G�t�F�N�g�֌W�̏��� */
	public:

		// ���m�N���`��̃|�X�g�G�t�F�N�g���J�n����i�����Ō��ʊ�����ݒ肷��F0.0f�`1.0f�j
		static void startMonochromePostEffect(float effectRate);
		// ���m�N���`��̃|�X�g�G�t�F�N�g�̌��ʊ�����ݒ肷��F0.0f�`1.0f
		static void setMonochromePostEffectRate(float effectRate);

		// �F���]�`��̃|�X�g�G�t�F�N�g���J�n����i�����Ō��ʊ�����ݒ肷��F0.0f�`1.0f�j
		static void startNegativePostEffect(float effectRate);
		// �F���]�`��̃|�X�g�G�t�F�N�g�̌��ʊ�����ݒ肷��F0.0f�`1.0f
		static void setNegativePostEffectRate(float effectRate);

		// ���ςڂ����`��̃|�X�g�G�t�F�N�g���J�n����i�����Ō��ʊ�����ݒ肷��F0.0f�`1.0f�j
		static void startAveragingBlurPostEffect(float effectRate);
		// ���ςڂ����`��̃|�X�g�G�t�F�N�g�̌��ʊ�����ݒ肷��F0.0f�`1.0f
		static void setAveragingBlurPostEffectRate(float effectRate);

		// �G���{�X�`��̃|�X�g�G�t�F�N�g���J�n����i�����Ō��ʊ�����ݒ肷��F0.0f�`1.0f�j
		static void startEmbossingPostEffect(float effectRate);
		// �G���{�X�`��̃|�X�g�G�t�F�N�g�̌��ʊ�����ݒ肷��F0.0f�`1.0f
		static void setEmbossingPostEffectRate(float effectRate);

		// �V���[�v�l�X�`��̃|�X�g�G�t�F�N�g���J�n����i�����Ō��ʊ�����ݒ肷��F0.0f�`1.0f�j
		static void startSharpnessPostEffect(float effectRate);
		// �V���[�v�l�X�`��̃|�X�g�G�t�F�N�g�̌��ʊ�����ݒ肷��F0.0f�`1.0f
		static void setSharpnessPostEffectRate(float effectRate);

		// �|�X�g�G�t�F�N�g���~����
		static void stopPostEffect();

	//************************************************************
	/* ���\�[�X��ǂݍ��ނ��߂̏��� */
	public:

		// �����f�[�^��ǂݍ��ށi�Ή����Ă��鉹���f�[�^�`����wav�j
		static void loadSound(ResourceIdCarrier soundId, const std::string& filePath);

		// �V�X�e���t�H���g���g������������
		static void createFont(ResourceIdCarrier fontId, const std::string& systemFontName, int fontSize = 64, float fontThicknessRate = 1.0f);

		// �t�H���g�t�@�C����ǂݍ��݁A���̃t�H���g���g������������
		static void createFont(ResourceIdCarrier fontId, const std::string& fontFilePath, const std::string& fontName, int fontSize = 64, float fontThicknessRate = 1.0f);

		// �e�N�X�`����ǂݍ��݃X�v���C�g�}�e���A�������i�Ή����Ă���摜�f�[�^�`����png�j
		static void loadSprite(ResourceIdCarrier spriteId, const std::string& filePath);

		// �e�N�X�`����ǂݍ��݃r���{�[�h�}�e���A�������i�Ή����Ă���摜�f�[�^�`����png�j
		static void loadBillboard(ResourceIdCarrier billBoardId, bool isEffect, const std::string& filePath);

		// ���b�V����ǂݍ��ށi�Ή����Ă��郁�b�V���`����pmd��pmx�j
		static void loadMesh(ResourceIdCarrier meshId, ResourceIdCarrier skeletonId, bool writeShadow, const std::string& filePath);

		// ���[�V������ǂݍ��ށi�Ή����Ă��郂�[�V�����`����vmd�j
		static void loadMotion(ResourceIdCarrier motionId, const std::string& filePath);

		// �e�N�X�`����ǂݍ��݃X�J�C�{�b�N�X���b�V�������i�Ή����Ă���摜�f�[�^�`����png�j
		static void loadSkyBox(ResourceIdCarrier meshId, const std::string& filePath);

		// �e�N�X�`����ǂݍ��݃{�b�N�X���b�V�������i�Ή����Ă���摜�f�[�^�`����png�j
		static void loadBoxMesh(ResourceIdCarrier meshId, bool writeShadow, const std::string& filePath);
	};
}
#endif // !TKTK_DX12_GAME_H_