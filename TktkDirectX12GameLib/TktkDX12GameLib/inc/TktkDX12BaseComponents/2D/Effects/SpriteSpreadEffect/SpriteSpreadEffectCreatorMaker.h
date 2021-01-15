#ifndef SPRITE_SPREAD_EFFECT_CREATOR_MAKER_H_
#define SPRITE_SPREAD_EFFECT_CREATOR_MAKER_H_

#include "TktkDX12Game/UtilityProcessManager/ResourceHandleGetter/ResourceIdConverter/ResourceIdCarrier.h"
#include "SpriteSpreadEffectCreator.h"

namespace tktk
{
	class SpriteSpreadEffectCreatorMaker
	{
	private: /* �v���C�x�[�g�R���X�g���N�^�B */

		SpriteSpreadEffectCreatorMaker() = default;
		SpriteSpreadEffectCreatorMaker(const SpriteSpreadEffectCreatorMaker& other) = default;
		SpriteSpreadEffectCreatorMaker& operator = (const SpriteSpreadEffectCreatorMaker& other) = default;

	public:

		// �쐬�J�n
		static SpriteSpreadEffectCreatorMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<SpriteSpreadEffectCreator> create();

	public:  /* �p�����[�^�ݒ�֐� */

		// �������[�J�����W��ݒ肷��
		SpriteSpreadEffectCreatorMaker& generateLocalPos(const tktkMath::Vector2 & value);

		// �������[�J�����W�̂Ԃ��ݒ肷��
		SpriteSpreadEffectCreatorMaker& generateLocalPosRandomRange(const tktkMath::Vector2 & value);

		// �ŏ��̐����p�x�i�x���@�j
		SpriteSpreadEffectCreatorMaker& minGenerateAngleDeg(float value);

		// �ő�̐����p�x�i�x���@�j
		SpriteSpreadEffectCreatorMaker& maxGenerateAngleDeg(float value);

		// �ŏ��̐������ԁi�b�j
		SpriteSpreadEffectCreatorMaker& firstGenerateTimeSec(float value);

		// �����p�x��ݒ肷��i�b�j
		SpriteSpreadEffectCreatorMaker& generateIntervalTimeSec(float value);

		// �����p�x�̂Ԃ��ݒ肷��
		SpriteSpreadEffectCreatorMaker& generateIntervalTimeRandomRange(float value);

		// �P�x�ɉ��������邩��ݒ肷��i�b�j
		SpriteSpreadEffectCreatorMaker& generateNumPerOnce(int value);

		// �P�x�ɐ���������̂Ԃ��ݒ肷��
		SpriteSpreadEffectCreatorMaker& generateNumPerOnceRandomRange(int value);

		// �ő剽�������邩��ݒ肷��
		SpriteSpreadEffectCreatorMaker& totalGenerateNum(int value);

		// �A�N�e�B�u�t���O�ύX���ɏ�Ԃ����Z�b�g���邩��ݒ肷��
		SpriteSpreadEffectCreatorMaker& changeAvtiveToReset(bool value);

		// �g�p����X�v���C�g�}�e���A���n���h����ݒ肷��
		SpriteSpreadEffectCreatorMaker& spriteMaterialHandle(size_t value);

		// �g�p����X�v���C�g�}�e���A��ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������j
		SpriteSpreadEffectCreatorMaker& spriteMaterialId(ResourceIdCarrier value);

		// �X�v���C�g�̃X�P�[����ݒ肷��
		SpriteSpreadEffectCreatorMaker& spriteScale(const tktkMath::Vector2 & value);

		// �X�v���C�g�̃X�P�[���̂Ԃ��ݒ肷��
		SpriteSpreadEffectCreatorMaker& spriteScaleRandomRange(const tktkMath::Vector2 & value);

		// �X�v���C�g�̃u�����h���[�g��ݒ肷��
		SpriteSpreadEffectCreatorMaker& spriteBlendRate(const tktkMath::Color & value);

		// �q�v�f�Ƃ��Ĉ�������ݒ肷��
		SpriteSpreadEffectCreatorMaker& setChild(bool value);

		// �������Ԃ�ݒ肷��i�b�j
		SpriteSpreadEffectCreatorMaker& lifeTimeSec(float value);

		// �������Ԃ̂Ԃ��ݒ肷��
		SpriteSpreadEffectCreatorMaker& lifeTimeSecRandomRange(float value);

		// �ړ����x��ݒ肷��i�b�j
		SpriteSpreadEffectCreatorMaker& moveSpeedPerSec(float value);

		// �ړ����x�̂Ԃ��ݒ肷��
		SpriteSpreadEffectCreatorMaker& moveSpeedPerSecRandomRange(float value);

	private: /* ���g�̃C���X�^���X�͐ÓI�ȑ��݂Ƃ��Ĉ��� */

		static SpriteSpreadEffectCreatorMaker m_self;

	private: /* �ϐ��B */

		GameObjectPtr			m_user{  };
		SpriteSpreadEffectParam	m_param{ };
	};
}
#endif // !SPRITE_SPREAD_EFFECT_CREATOR_MAKER_H_