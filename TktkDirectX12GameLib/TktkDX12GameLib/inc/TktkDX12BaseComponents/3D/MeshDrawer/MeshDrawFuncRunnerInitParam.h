#ifndef MESH_DRAW_FUNC_RUNNER_INIT_PARAM_H_
#define MESH_DRAW_FUNC_RUNNER_INIT_PARAM_H_

#include "TktkDX12Game/UtilityProcessManager/ResourceHandleGetter/ResourceIdConverter/ResourceIdCarrier.h"

namespace tktk
{
	struct MeshDrawFuncRunnerInitParam
	{
	public:

		static MeshDrawFuncRunnerInitParam& create();

	public:

		// �V���h�E�}�b�v��`�悷�邩�H
		MeshDrawFuncRunnerInitParam& writeShadowMap(bool value);

		// �`��D��x��ݒ肷��
		MeshDrawFuncRunnerInitParam& drawPriority(float value);

		// �{�[�����g�p���ĕ`�悷�邩�H
		MeshDrawFuncRunnerInitParam& useBone(bool value);

		// �g�p���郌���_�[�^�[�Q�b�g�̃f�B�X�N���v�^�q�[�v�n���h����ݒ肷��
		// �������p�����[�^�̓o�b�N�o�b�t�@�[
		MeshDrawFuncRunnerInitParam& useRtvDescriptorHeapHandle(size_t value);

		// �g�p���郉�C�g�n���h����ݒ肷��
		// �������p�����[�^�̓f�t�H���g���C�g
		MeshDrawFuncRunnerInitParam& lightHandle(size_t value);

		// �g�p���郉�C�gID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������j
		// �������p�����[�^�̓f�t�H���g���C�g
		MeshDrawFuncRunnerInitParam& lightId(ResourceIdCarrier value);

		// �g�p����J�����n���h����ݒ肷��
		// �������p�����[�^�̓f�t�H���g�ʏ�J����
		MeshDrawFuncRunnerInitParam& cameraHandle(size_t value);

		// �g�p����J����ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������j
		// �������p�����[�^�̓f�t�H���g�ʏ�J����
		MeshDrawFuncRunnerInitParam& cameraId(ResourceIdCarrier value);

		// �g�p����V���h�E�}�b�v�J�����n���h����ݒ肷��
		// �������p�����[�^�̓f�t�H���g�V���h�E�}�b�v�J����
		MeshDrawFuncRunnerInitParam& shadowMapCameraHandle(size_t value);

		// �g�p����V���h�E�}�b�v�J����ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������j
		// �������p�����[�^�̓f�t�H���g�V���h�E�}�b�v�J����
		MeshDrawFuncRunnerInitParam& shadowMapCameraId(ResourceIdCarrier value);


		MeshDrawFuncRunnerInitParam& skeletonHandle(size_t value);
		MeshDrawFuncRunnerInitParam& skeletonId(ResourceIdCarrier value);

	private:

		static MeshDrawFuncRunnerInitParam m_self;

	private:

		MeshDrawFuncRunnerInitParam() = default;

	public:

		bool	m_writeShadowMap			{ false };
		float	m_drawPriority				{ 0.0f };
		bool	m_useBone					{ false };
		size_t	m_rtvDescriptorHeapHandle	{ 0U };
		size_t	m_lightHandle				{ 0U };
		size_t	m_cameraHandle				{ 0U };
		size_t	m_shadowMapCameraHandle		{ 0U };

		size_t m_skeletonHandle{ 0U };
	};
}
#endif // !MESH_DRAW_FUNC_RUNNER_INIT_PARAM_H_