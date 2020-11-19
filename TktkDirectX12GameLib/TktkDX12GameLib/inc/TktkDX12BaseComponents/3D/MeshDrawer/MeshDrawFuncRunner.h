#ifndef MESH_DRAW_FUNC_RUNNER_H_
#define MESH_DRAW_FUNC_RUNNER_H_

/* base class */
#include "../../../TktkDX12Game/DXGameResource/GameObjectResouse/Component/ComponentBase.h"

namespace tktk
{
	struct MeshDrawFuncRunnerInitParam;

	class MeshDrawFuncRunner
		: public ComponentBase
	{
	public:

		MeshDrawFuncRunner(size_t meshHandle, const MeshDrawFuncRunnerInitParam& initParam);

	public:

		void start();
		void onDestroy();
		void update();
		void draw() const;

	private:

		// �J�������萔�o�b�t�@�̍X�V
		void updateCameraCbuffer() const;

		// �V���h�E�}�b�v�p�̒萔�o�b�t�@�̍X�V
		void updateShadowMapCbuffer() const;

	private:

		// �����g�����`�悩�H
		bool m_useBone;

		// �g�p���郊�\�[�X�n���h��
		size_t m_meshHandle;
		size_t m_rtvDescriptorHeapHandle;
		size_t m_lightHandle;
		size_t m_cameraHandle;
		size_t m_shadowMapCameraHandle;

		size_t m_skeletonHandle{ 0U };
		size_t m_createUploadBoneMatrixCbufferHandle{ 0U };

		// �A�b�v���[�h�p�o�b�t�@�n���h��
		size_t m_createUploadCameraCbufferHandle	{ 0U };
		size_t m_createUploadShadowMapCbufferHandle	{ 0U };
	};
}
#endif // !MESH_DRAW_FUNC_RUNNER_H_