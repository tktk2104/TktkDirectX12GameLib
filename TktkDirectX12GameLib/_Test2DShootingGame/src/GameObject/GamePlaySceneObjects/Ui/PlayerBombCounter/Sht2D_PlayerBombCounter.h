#ifndef SHT_2D_PLAYER_BOMB_COUNTER_H_
#define SHT_2D_PLAYER_BOMB_COUNTER_H_

#include <TktkDX12GameLib.h>

// �v���C���[�̃{���c���J�E���^UI
struct Sht2D_PlayerBombCounter
{
  /*����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������
	�����́ucreate()�v���V���O���N���b�N��F12�L�[����͂��ă\�[�X�t�@�C���ɔ��ŉ������B
	����������������������������������������������������������������������������������������������������������������������������������������������������������������������������������*/

	static tktk::GameObjectPtr create(const tktkMath::Vector2& position);
};
#endif // !SHT_2D_PLAYER_BOMB_COUNTER_H_