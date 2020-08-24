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
		unsigned int createHandle();

		// �����̃n���h�����g�p�ς݂Ƃ���
		void endUseHandle(unsigned int deleteHandle);

		// �n���h���̍쐬�󋵂�����������
		void reset();

	private:

		// �g�p�ς݂̃n���h����ۑ�����L���[
		std::queue<unsigned int>	m_endUseHandles;

		// ���Ɏg�p����n���h��
		unsigned int				m_nextUseHandle	{ std::numeric_limits<unsigned int>::max() };
	};
}
#endif // !RESOURCE_HANDLE_MANAGER_H_