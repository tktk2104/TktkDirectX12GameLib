#ifndef RESOURCE_CONTAINER_INIT_PARAM_H_
#define RESOURCE_CONTAINER_INIT_PARAM_H_

namespace tktkContainer
{
	// �uResourceContainer�v�̃C���X�^���X����鎞�ɕK�v�ȕϐ�
	struct ResourceContainerInitParam
	{
		unsigned int staticNodeNum			{ 10U };	// ���������ɃC���X�^���X�����̃����������O�m�ۂ��邩�H
		unsigned int moveNodeMaxNumPerFrame	{ 1U };		// �P�t���[���ŏ��������m�ۃ������Ɉړ��ł���v�f��
	};
}
#endif // !RESOURCE_CONTAINER_INIT_PARAM_H_