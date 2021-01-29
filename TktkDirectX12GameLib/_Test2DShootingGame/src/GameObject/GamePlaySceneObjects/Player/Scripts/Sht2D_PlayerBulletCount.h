#ifndef SHT_2D_PLAYER_BULLET_COUNT_H_
#define SHT_2D_PLAYER_BULLET_COUNT_H_

#include <TktkDX12GameLib.h>

// プレイヤー弾数コンポーネント
class Sht2D_PlayerBulletCount
	: public tktk::ComponentBase
{
public:

	Sht2D_PlayerBulletCount() = default;

public:

	// 現在の残りミサイル数を変更する（ 0 < getMaxMissileCount() ）
	void changeMissileCount(int changeWidth);

	// 現在の残りミサイル数を取得する
	int getCurMissileCount() const;

	// 現在の残りミサイル数を変更する（ 0 < getMaxBombCount() ）
	void changeBombCount(int changeWidth);

	// 現在の残りミサイル数を取得する
	int getCurBombCount() const;

public:

	// 最大ミサイル数
	constexpr static int getMaxMissileCount()	{ return 20; }

	// 最大ボム数
	constexpr static int getMaxBombCount()		{ return 5; }

private:

	// 初期ミサイル数
	constexpr static int InitMissileCount		{ 20 };

	// 初期ボム数
	constexpr static int InitBombCount			{ 5 };

private:

	// 現在の残りミサイル数
	int m_curMissileCount	{ InitMissileCount };

	// 現在の残りボム数
	int m_curBombCount		{ InitBombCount };
};
#endif // !SHT_2D_PLAYER_BULLET_COUNT_H_
