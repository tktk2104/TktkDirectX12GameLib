#ifndef DX_12_GAME_MANAGER_INIT_PARAM_H_
#define DX_12_GAME_MANAGER_INIT_PARAM_H_

#include <string>
#include <TktkDX12Wrapper/Resource/DX3DResourceNum.h>
#include "../GraphicManager/Window/WindowInitParam.h"

namespace tktk
{
	struct DX12GameManagerInitParam
	{
		// DirectX12�̃��b�p�[�N���X�̏������ɕK�v�ȕϐ�
		DX3DResourceNum				dx3dResNum			{};

		// �E�B���h�E�̏������ɕK�v�ȕϐ�
		WindowInitParam				windowParam			{};

		// ���̃t���[�����[�N�̊�{���\�[�X�̃t�H���_�K�w
		std::string					tktkLibResFolderPath{""};

		// DirectX12�̃f�o�b�N���C���[����邩�ǂ����H
		bool						craeteDebugLayer	{ true };

		// ���̃t���[�����[�N�̃��\�[�X�Ǘ��R���e�i�̃������m�ۊ֌W�̐ݒ�ϐ�
		tktkContainer::ResourceContainerInitParam lightContainerParam;
		tktkContainer::ResourceContainerInitParam cameraContainerParam;
		tktkContainer::ResourceContainerInitParam postEffectMatContainerParam;
		tktkContainer::ResourceContainerInitParam line2DMatContainerParam;
		tktkContainer::ResourceContainerInitParam spriteMatContainerParam;
		tktkContainer::ResourceContainerInitParam billboardMatContainerParam;
		tktkContainer::ResourceContainerInitParam meshContainerParam;
		tktkContainer::ResourceContainerInitParam meshMatContainerParam;
		tktkContainer::ResourceContainerInitParam skeletonContainerParam;
		tktkContainer::ResourceContainerInitParam motionContainerParam;
		tktkContainer::ResourceContainerInitParam sceneContainerParam;
		tktkContainer::ResourceContainerInitParam soundContainerParam;
	};
}
#endif // !DX_12_GAME_MANAGER_INIT_PARAM_H_