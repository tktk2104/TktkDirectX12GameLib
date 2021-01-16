#ifndef SPRITE_SHRINK_EFFECT_CREATOR_MAKER_H_
#define SPRITE_SHRINK_EFFECT_CREATOR_MAKER_H_

#include "TktkDX12Game/UtilityProcessManager/ResourceHandleGetter/ResourceIdConverter/ResourceIdCarrier.h"
#include "SpriteShrinkEffectCreator.h"

namespace tktk
{
	class SpriteShrinkEffectCreatorMaker
	{
	private: /* �v���C�x�[�g�R���X�g���N�^�B */

		SpriteShrinkEffectCreatorMaker() = default;
		SpriteShrinkEffectCreatorMaker(const SpriteShrinkEffectCreatorMaker& other) = default;
		SpriteShrinkEffectCreatorMaker& operator = (const SpriteShrinkEffectCreatorMaker& other) = default;

	public:

		// �쐬�J�n
		static SpriteShrinkEffectCreatorMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<SpriteShrinkEffectCreator> create();

	public:  /* �p�����[�^�ݒ�֐� */

		//************************************************************
		/* ������� */

		// ���k�_���W��ݒ肷��
		SpriteShrinkEffectCreatorMaker& shrinkTargetPos(const tktkMath::Vector2 & value);

		// ���k�_���W�̂Ԃ��ݒ肷��
		SpriteShrinkEffectCreatorMaker& shrinkTargetPosRandomRange(const tktkMath::Vector2 & value);

		// �ŏ��̐������ԁi�b�j
		SpriteShrinkEffectCreatorMaker& firstGenerateTimeSec(float value);

		// �����p�x��ݒ肷��i�b�j
		SpriteShrinkEffectCreatorMaker& generateIntervalTimeSec(float value);

		// �����p�x�̂Ԃ��ݒ肷��
		SpriteShrinkEffectCreatorMaker& generateIntervalTimeRandomRange(float value);

		// �P�x�ɉ��������邩��ݒ肷��i�b�j
		SpriteShrinkEffectCreatorMaker& generateNumPerOnce(int value);

		// �P�x�ɐ���������̂Ԃ��ݒ肷��
		SpriteShrinkEffectCreatorMaker& generateNumPerOnceRandomRange(int value);

		// �ő剽�������邩��ݒ肷��
		SpriteShrinkEffectCreatorMaker& totalGenerateNum(int value);

		// �A�N�e�B�u�t���O�ύX���ɏ�Ԃ����Z�b�g���邩��ݒ肷��
		SpriteShrinkEffectCreatorMaker& changeAvtiveToReset(bool value);

		//************************************************************
		/* �p�[�e�B�N����� */

		// �g�p����X�v���C�g�}�e���A���n���h����ݒ肷��
		SpriteShrinkEffectCreatorMaker& spriteMaterialHandle(size_t value);

		// �g�p����X�v���C�g�}�e���A��ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������j
		SpriteShrinkEffectCreatorMaker& spriteMaterialId(ResourceIdCarrier value);

		// �X�v���C�g�̃X�P�[����ݒ肷��
		SpriteShrinkEffectCreatorMaker& spriteScale(const tktkMath::Vector2 & value);

		// �X�v���C�g�̃X�P�[���̂Ԃ��ݒ肷��
		SpriteShrinkEffectCreatorMaker& spriteScaleRandomRange(const tktkMath::Vector2 & value);

		// �X�v���C�g�̃u�����h���[�g��ݒ肷��
		SpriteShrinkEffectCreatorMaker& spriteBlendRate(const tktkMath::Color & value);

		// �q�v�f�Ƃ��Ĉ�������ݒ肷��
		SpriteShrinkEffectCreatorMaker& setChild(bool value);

		// �������Ԃ�ݒ肷��i�b�j
		SpriteShrinkEffectCreatorMaker& lifeTimeSec(float value);

		// �������Ԃ̂Ԃ��ݒ肷��
		SpriteShrinkEffectCreatorMaker& lifeTimeSecRandomRange(float value);

		// �ړ����x��ݒ肷��i�b�j
		SpriteShrinkEffectCreatorMaker& moveSpeedPerSec(float value);

		// �ړ����x�̂Ԃ��ݒ肷��
		SpriteShrinkEffectCreatorMaker& moveSpeedPerSecRandomRange(float value);

		//************************************************************
		/* �p�[�e�B�N���A�j���[�V������� */

		// �A�j���[�V�������g�p���邩��ݒ肷��
		SpriteShrinkEffectCreatorMaker& useAnimation(bool value);

		// �A�j���[�V���������[�v���邩��ݒ肷��
		SpriteShrinkEffectCreatorMaker& isLoop(bool value);

		// �A�j���[�V�����̏����t���[����ݒ肷��
		SpriteShrinkEffectCreatorMaker& initFrame(float value);

		// �A�j���[�V�����̍Đ����x������ݒ肷��
		SpriteShrinkEffectCreatorMaker& animSpeedRate(float value);

		// �A�j���[�V�����P�t���[��������ɂ����鎞�Ԃ�ݒ肷��
		SpriteShrinkEffectCreatorMaker& animFramePerSec(float value);

		// �A�j���[�V�����̑��t���[������ݒ肷��
		SpriteShrinkEffectCreatorMaker& totalAnimFrameSize(unsigned int value);

	private: /* ���g�̃C���X�^���X�͐ÓI�ȑ��݂Ƃ��Ĉ��� */

		static SpriteShrinkEffectCreatorMaker m_self;

	private: /* �ϐ��B */

		GameObjectPtr			m_user{  };
		SpriteShrinkEffectParam	m_param{ };
	};
}
#endif // !SPRITE_SHRINK_EFFECT_CREATOR_MAKER_H_