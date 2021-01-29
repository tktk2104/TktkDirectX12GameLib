#ifndef SHT_2D_PLAYER_BULLET_COUNT_H_
#define SHT_2D_PLAYER_BULLET_COUNT_H_

#include <TktkDX12GameLib.h>

// �v���C���[�e���R���|�[�l���g
class Sht2D_PlayerBulletCount
	: public tktk::ComponentBase
{
public:

	Sht2D_PlayerBulletCount() = default;

public:

	// ���݂̎c��~�T�C������ύX����i 0 < getMaxMissileCount() �j
	void changeMissileCount(int changeWidth);

	// ���݂̎c��~�T�C�������擾����
	int getCurMissileCount() const;

	// ���݂̎c��~�T�C������ύX����i 0 < getMaxBombCount() �j
	void changeBombCount(int changeWidth);

	// ���݂̎c��~�T�C�������擾����
	int getCurBombCount() const;

public:

	// �ő�~�T�C����
	constexpr static int getMaxMissileCount()	{ return 20; }

	// �ő�{����
	constexpr static int getMaxBombCount()		{ return 5; }

private:

	// �����~�T�C����
	constexpr static int InitMissileCount		{ 20 };

	// �����{����
	constexpr static int InitBombCount			{ 5 };

private:

	// ���݂̎c��~�T�C����
	int m_curMissileCount	{ InitMissileCount };

	// ���݂̎c��{����
	int m_curBombCount		{ InitBombCount };
};
#endif // !SHT_2D_PLAYER_BULLET_COUNT_H_
