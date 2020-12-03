#ifndef BILLBOARD_DRAW_FUNC_RUNNER_INIT_PARAM_H_
#define BILLBOARD_DRAW_FUNC_RUNNER_INIT_PARAM_H_

#include "TktkDX12Game/UtilityProcessManager/ResourceHandleGetter/ResourceIdConverter/ResourceIdCarrier.h"

namespace tktk
{
	struct BillboardDrawFuncRunnerInitParam
	{
	public:

		static BillboardDrawFuncRunnerInitParam& create();

	public:

		// �`��D��x��ݒ肷��
		BillboardDrawFuncRunnerInitParam& drawPriority(float value);

		// �g�p���郌���_�[�^�[�Q�b�g�̃f�B�X�N���v�^�q�[�v�n���h����ݒ肷��
		// �������p�����[�^�̓o�b�N�o�b�t�@�[
		BillboardDrawFuncRunnerInitParam& useRtvDescriptorHeapHandle(size_t value);

		// �g�p����J�����n���h����ݒ肷��
		// �������p�����[�^�̓f�t�H���g�ʏ�J����
		BillboardDrawFuncRunnerInitParam& cameraHandle(size_t value);

		// �g�p����J����ID��ݒ肷��i�񋓌^���܂ސ����^��id���n���ꂽ�ꍇ�̂݃r���h�ŁA�֐����őΉ����郊�\�[�X�n���h���ɕϊ������j
		// �������p�����[�^�̓f�t�H���g�ʏ�J����
		BillboardDrawFuncRunnerInitParam& cameraId(ResourceIdCarrier value);

	private:

		static BillboardDrawFuncRunnerInitParam m_self;

	public:

		float	m_drawPriority				{ 0.0f };
		size_t	m_rtvDescriptorHeapHandle	{ 0U };
		size_t	m_cameraHandle				{ 0U };
	};
}
#endif // !BILLBOARD_DRAW_FUNC_RUNNER_INIT_PARAM_H_