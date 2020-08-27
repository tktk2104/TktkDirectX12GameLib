#ifndef DX_GAME_RESOURCE_NUM_H_
#define DX_GAME_RESOURCE_NUM_H_

#include "Mesh/MeshResourceNum.h"

namespace tktk
{
	// �Q�[���Ŏg�p����\�ʓI�ȃ��\�[�X���Ǘ�����R���e�i����邽�߂̕ϐ�
	struct DXGameResourceNum
	{
		// �V�[�����Ǘ�����R���e�i����邽�߂̕ϐ�
		tktkContainer::ResourceContainerInitParam sceneNum				{};

		// �T�E���h���Ǘ�����R���e�i����邽�߂̕ϐ�
		tktkContainer::ResourceContainerInitParam soundNum				{};

		// �X�v���C�g�}�e���A�����Ǘ�����R���e�i����邽�߂̕ϐ�
		tktkContainer::ResourceContainerInitParam spriteMaterialNum		{};

		// ���C���QD�}�e���A�����Ǘ�����R���e�i����邽�߂̕ϐ�
		tktkContainer::ResourceContainerInitParam line2DMaterialNum		{};

		// ���b�V���֘A���\�[�X���Ǘ�����R���e�i����邽�߂̕ϐ�
		MeshResourceNum meshResourceNum									{};

		// �|�X�g�G�t�F�N�g�}�e���A�����Ǘ�����R���e�i����邽�߂̕ϐ�
		tktkContainer::ResourceContainerInitParam postEffectMaterialNum	{};

		// �J�������Ǘ�����R���e�i����邽�߂̕ϐ�
		tktkContainer::ResourceContainerInitParam cameraNum				{};

		// ���C�g���Ǘ�����R���e�i����邽�߂̕ϐ�
		tktkContainer::ResourceContainerInitParam lightNum				{};
	};
}
#endif // !DX_GAME_RESOURCE_NUM_H_