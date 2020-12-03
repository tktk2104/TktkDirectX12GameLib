#ifndef BILLBOARD_SPREAD_EFFECT_CREATOR_MAKER_H_
#define BILLBOARD_SPREAD_EFFECT_CREATOR_MAKER_H_

#include "TktkDX12Game/UtilityProcessManager/ResourceHandleGetter/ResourceIdConverter/ResourceIdCarrier.h"
#include "BillboardSpreadEffectCreator.h"

namespace tktk
{
	class BillboardSpreadEffectCreatorMaker
	{
	private: /* �v���C�x�[�g�R���X�g���N�^�B */

		BillboardSpreadEffectCreatorMaker() = default;
		BillboardSpreadEffectCreatorMaker(const BillboardSpreadEffectCreatorMaker& other) = default;
		BillboardSpreadEffectCreatorMaker& operator = (const BillboardSpreadEffectCreatorMaker& other) = default;

	public:

		// �쐬�J�n
		static BillboardSpreadEffectCreatorMaker& makeStart(GameObjectPtr user);

	public:

		// �쐬����
		ComponentPtr<BillboardSpreadEffectCreator> create();

	public:  /* �p�����[�^�ݒ�֐� */

		// �������[�J�����W��ݒ肷��
		BillboardSpreadEffectCreatorMaker& generateLocalPos(const tktkMath::Vector3& value);

		// �������[�J�����W�̂Ԃ��ݒ肷��
		BillboardSpreadEffectCreatorMaker& generateLocalPosRandomRange(const tktkMath::Vector3& value);

		// �ŏ��̐������ԁi�b�j
		BillboardSpreadEffectCreatorMaker& firstGenerateTimeSec(float value);

		// �����p�x��ݒ肷��i�b�j
		BillboardSpreadEffectCreatorMaker& generateIntervalTimeSec(float value);

		// �����p�x�̂Ԃ��ݒ肷��
		BillboardSpreadEffectCreatorMaker& generateIntervalTimeRandomRange(float value);

		// �P�x�ɉ��������邩��ݒ肷��i�b�j
		BillboardSpreadEffectCreatorMaker& generateNumPerOnce(int value);

		// �P�x�ɐ���������̂Ԃ��ݒ肷��
		BillboardSpreadEffectCreatorMaker& generateNumPerOnceRandomRange(int value);

		// �ő剽�������邩��ݒ肷��
		BillboardSpreadEffectCreatorMaker& totalGenerateNum(int value);

		// �A�N�e�B�u�t���O�ύX���ɏ�Ԃ����Z�b�g���邩��ݒ肷��
		BillboardSpreadEffectCreatorMaker& changeAvtiveToReset(bool value);

		// �g�p����r���{�[�h�}�e���A���n���h����ݒ肷��
		BillboardSpreadEffectCreatorMaker& billboardMaterialHandle(size_t value);

		// �g�p����r���{�[�h�}�e���A��ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������j
		BillboardSpreadEffectCreatorMaker& billboardMaterialId(ResourceIdCarrier value);

		// �r���{�[�h�̃X�P�[����ݒ肷��
		BillboardSpreadEffectCreatorMaker& billboardScale(const tktkMath::Vector2& value);

		// �r���{�[�h�̃X�P�[���̂Ԃ��ݒ肷��
		BillboardSpreadEffectCreatorMaker& billboardScaleRandomRange(const tktkMath::Vector2& value);

		// �r���{�[�h�̃u�����h���[�g��ݒ肷��
		BillboardSpreadEffectCreatorMaker& billboardBlendRate(const tktkMath::Color& value);

		// �q�v�f�Ƃ��Ĉ�������ݒ肷��
		BillboardSpreadEffectCreatorMaker& setChild(bool value);

		// �������Ԃ�ݒ肷��i�b�j
		BillboardSpreadEffectCreatorMaker& lifeTimeSec(float value);

		// �������Ԃ̂Ԃ��ݒ肷��
		BillboardSpreadEffectCreatorMaker& lifeTimeSecRandomRange(float value);

		// �ړ����x��ݒ肷��i�b�j
		BillboardSpreadEffectCreatorMaker& moveSpeedPerSec(float value);

		// �ړ����x�̂Ԃ��ݒ肷��
		BillboardSpreadEffectCreatorMaker& moveSpeedPerSecRandomRange(float value);

	private: /* ���g�̃C���X�^���X�͐ÓI�ȑ��݂Ƃ��Ĉ��� */

		static BillboardSpreadEffectCreatorMaker m_self;

	private: /* �ϐ��B */

		GameObjectPtr				m_user{  };
		BillboardSpreadEffectParam	m_param{ };
	};
}
#endif // !BILLBOARD_SPREAD_EFFECT_CREATOR_MAKER_H_