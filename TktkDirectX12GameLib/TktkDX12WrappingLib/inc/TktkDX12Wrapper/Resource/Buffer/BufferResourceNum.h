#ifndef BUFFER_RESOURCE_INIT_PARAM_H_
#define BUFFER_RESOURCE_INIT_PARAM_H_

#include <TktkContainer/ResourceContainer/ResourceContainerInitParam.h>

namespace tktk
{
	// ���ꂼ��̃o�b�t�@�[���\�[�X�̐���ݒ肷�邽�߂̍\����
	struct BufferResourceNum
	{
		tktkContainer::ResourceContainerInitParam copyBufferContainerInitParam;		// �R�s�[�o�b�t�@���Ǘ�����R���e�i�����������鎞�̒l
		tktkContainer::ResourceContainerInitParam vertexBufferContainerInitParam;	// ���_�o�b�t�@���Ǘ�����R���e�i�����������鎞�̒l
		tktkContainer::ResourceContainerInitParam indexBufferContainerInitParam;	// �C���f�b�N�X�o�b�t�@���Ǘ�����R���e�i�����������鎞�̒l
		tktkContainer::ResourceContainerInitParam cbufferContainerInitParam;		// �萔�o�b�t�@���Ǘ�����R���e�i�����������鎞�̒l
		tktkContainer::ResourceContainerInitParam textureBufferStaticNodeNum;		// �e�N�X�`���o�b�t�@���Ǘ�����R���e�i�����������鎞�̒l
		tktkContainer::ResourceContainerInitParam dsbufferStaticNodeNum;			// �[�x�X�e���V���o�b�t�@���Ǘ�����R���e�i�����������鎞�̒l
		tktkContainer::ResourceContainerInitParam rtbufferStaticNodeNum;			// �����_�[�^�[�Q�b�g�o�b�t�@���Ǘ�����R���e�i�����������鎞�̒l
	};
}
#endif // !BUFFER_RESOURCE_INIT_PARAM_H_