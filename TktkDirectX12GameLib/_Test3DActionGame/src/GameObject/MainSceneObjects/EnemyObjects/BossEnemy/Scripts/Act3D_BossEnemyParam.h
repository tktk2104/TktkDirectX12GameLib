#ifndef ACT_3D_BOSS_ENEMY_PARAM_H_
#define ACT_3D_BOSS_ENEMY_PARAM_H_

#include <TktkDX12GameLib.h>

// �{�X�G�l�~�[�̔\�͒l�̃R���|�[�l���g
class Act3D_BossEnemyParam
	: public tktk::ComponentBase
{
public:

	Act3D_BossEnemyParam() = default;

public:

	void update();

public:

	// �����̒l����Hp�����炷
	void damage(int damage);
	// Hp���[�������ʂ���
	bool outOfHp() const;

	// �ʏ�U���̃C���^�[�o�����I����Ă��邩�擾����
	bool canNormalAttack() const;
	// �ʏ�U���̃C���^�[�o����ݒ肷��
	void resetNormalAttackIntervelTimer(float time);

	// ��]�U���̃C���^�[�o�����I����Ă��邩���擾����
	bool canRollAttack() const;
	// ��]�U���̃C���^�[�o����ݒ肷��
	void resetRollAttackIntervelTimer(float time);

	// �W�����v�U���̃C���^�[�o�����I����Ă��邩���擾����
	bool canJumpAttack() const;
	// �W�����v�U���̃C���^�[�o����ݒ肷��
	void resetJumpAttackIntervelTimer(float time);

public:

	// �ő�HP
	constexpr int getMaxHp() const { return 15; }

private:

	// ���݂�Hp
	int		m_curHp							{ getMaxHp() };

	// �ʏ�U���̃C���^�[�o���^�C�}�[
	float	m_normalAttackIntervalSecTimer	{ 0.0f };
	// ��]�U���̃C���^�[�o���^�C�}�[
	float	m_rollAttackIntervalSecTimer	{ 0.0f };
	// �W�����v�U���̃C���^�[�o���^�C�}�[
	float	m_jumpAttackIntervalSecTimer	{ 0.0f };
};
#endif // !ACT_3D_BOSS_ENEMY_PARAM_H_