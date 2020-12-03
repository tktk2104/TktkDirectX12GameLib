#ifndef BILLBOARD_SHRINK_EFFECT_CREATOR_MAKER_H_
#define BILLBOARD_SHRINK_EFFECT_CREATOR_MAKER_H_

#include "TktkDX12Game/UtilityProcessManager/ResourceHandleGetter/ResourceIdConverter/ResourceIdCarrier.h"
#include "BillboardShrinkEffectCreator.h"

namespace tktk
{
	class BillboardShrinkEffectCreatorMaker
	{
	private: /* �v���C�x�[�g�R���X�g���N�^�B */

		BillboardShrinkEffectCreatorMaker() = default;
		BillboardShrinkEffectCreatorMaker(const BillboardShrinkEffectCreatorMaker& other) = default;
		BillboardShrinkEffectCreatorMaker& operator = (const BillboardShrinkEffectCreatorMaker& other) = default;

	public:

		// �쐬�J�n
		static BillboardShrinkEffectCreatorMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<BillboardShrinkEffectCreator> create();

	public:  /* �p�����[�^�ݒ�֐� */

		// ���k�_���W��ݒ肷��
		BillboardShrinkEffectCreatorMaker& shrinkTargetPos(const tktkMath::Vector3 & value);

		// ���k�_���W�̂Ԃ��ݒ肷��
		BillboardShrinkEffectCreatorMaker& shrinkTargetPosRandomRange(const tktkMath::Vector3 & value);

		// �ŏ��̐������ԁi�b�j
		BillboardShrinkEffectCreatorMaker& firstGenerateTimeSec(float value);

		// �����p�x��ݒ肷��i�b�j
		BillboardShrinkEffectCreatorMaker& generateIntervalTimeSec(float value);

		// �����p�x�̂Ԃ��ݒ肷��
		BillboardShrinkEffectCreatorMaker& generateIntervalTimeRandomRange(float value);

		// �P�x�ɉ��������邩��ݒ肷��i�b�j
		BillboardShrinkEffectCreatorMaker& generateNumPerOnce(int value);

		// �P�x�ɐ���������̂Ԃ��ݒ肷��
		BillboardShrinkEffectCreatorMaker& generateNumPerOnceRandomRange(int value);

		// �ő剽�������邩��ݒ肷��
		BillboardShrinkEffectCreatorMaker& totalGenerateNum(int value);

		// �A�N�e�B�u�t���O�ύX���ɏ�Ԃ����Z�b�g���邩��ݒ肷��
		BillboardShrinkEffectCreatorMaker& changeAvtiveToReset(bool value);

		// �g�p����r���{�[�h�}�e���A���n���h����ݒ肷��
		BillboardShrinkEffectCreatorMaker& billboardMaterialHandle(size_t value);

		// �g�p����r���{�[�h�}�e���A��ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������j
		BillboardShrinkEffectCreatorMaker& billboardMaterialId(ResourceIdCarrier value);

		// �r���{�[�h�̃X�P�[����ݒ肷��
		BillboardShrinkEffectCreatorMaker& billboardScale(const tktkMath::Vector2 & value);

		// �r���{�[�h�̃X�P�[���̂Ԃ��ݒ肷��
		BillboardShrinkEffectCreatorMaker& billboardScaleRandomRange(const tktkMath::Vector2 & value);

		// �r���{�[�h�̃u�����h���[�g��ݒ肷��
		BillboardShrinkEffectCreatorMaker& billboardBlendRate(const tktkMath::Color & value);

		// �q�v�f�Ƃ��Ĉ�������ݒ肷��
		BillboardShrinkEffectCreatorMaker& setChild(bool value);

		// �������Ԃ�ݒ肷��i�b�j
		BillboardShrinkEffectCreatorMaker& lifeTimeSec(float value);

		// �������Ԃ̂Ԃ��ݒ肷��
		BillboardShrinkEffectCreatorMaker& lifeTimeSecRandomRange(float value);

		// �ړ����x��ݒ肷��i�b�j
		BillboardShrinkEffectCreatorMaker& moveSpeedPerSec(float value);

		// �ړ����x�̂Ԃ��ݒ肷��
		BillboardShrinkEffectCreatorMaker& moveSpeedPerSecRandomRange(float value);

	private: /* ���g�̃C���X�^���X�͐ÓI�ȑ��݂Ƃ��Ĉ��� */

		static BillboardShrinkEffectCreatorMaker m_self;

	private: /* �ϐ��B */

		GameObjectPtr				m_user{  };
		BillboardShrinkEffectParam	m_param{ };
	};
}
#endif // !BILLBOARD_SHRINK_EFFECT_CREATOR_MAKER_H_