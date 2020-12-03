#ifndef RESOURCE_HANDLE_MANAGER_H_
#define RESOURCE_HANDLE_MANAGER_H_

#include <limits>
#include <queue>

namespace tktkContainer
{
	class ResourceHandleManager
	{
	public:

		ResourceHandleManager() = default;
		~ResourceHandleManager() = default;

	public:

		// �V���ȃn���h�����擾����
		// ���ȑO�g���Ă��č��g���Ă��Ȃ��ԍ����������炻����擾����
		size_t createHandle();

		// �����̃n���h�����g�p�ς݂Ƃ���
		void endUseHandle(size_t deleteHandle);

		// �n���h���̍쐬�󋵂�����������
		void reset();

	private:

		// �g�p�ς݂̃n���h����ۑ�����L���[
		std::queue<size_t>	m_endUseHandles;

		// ���Ɏg�p����n���h��
		size_t				m_nextUseHandle	{ std::numeric_limits<size_t>::max() };
	};
}
#endif // !RESOURCE_HANDLE_MANAGER_H_