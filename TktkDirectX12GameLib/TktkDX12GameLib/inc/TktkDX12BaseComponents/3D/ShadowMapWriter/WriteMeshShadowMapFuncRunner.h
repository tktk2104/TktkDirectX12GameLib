#ifndef WRITE_MESH_SHADOW_MAP_FUNC_RUNNER_H_
#define WRITE_MESH_SHADOW_MAP_FUNC_RUNNER_H_

/* base class */
#include "../../../TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentBase.h"

namespace tktk
{
	class WriteMeshShadowMapFuncRunner
		: public ComponentBase
	{
	public:

		WriteMeshShadowMapFuncRunner(size_t meshHandle, bool useBone);

	public:

		void start();
		void onDestroy();
		void draw() const;

	private:

		// �J�������萔�o�b�t�@�̍X�V
		void updateCameraCbuffer() const;

	private:

		// �����g�����`�悩�H
		bool m_useBone;

		// �g�p���郊�\�[�X�n���h��
		size_t m_meshHandle;

		// �A�b�v���[�h�p�o�b�t�@�n���h��
		size_t m_createUploadCameraCbufferHandle{ 0U };
		size_t m_createUploadShadowMapCbufferHandle{ 0U };
	};
}
#endif // !WRITE_MESH_SHADOW_MAP_FUNC_RUNNER_H_
