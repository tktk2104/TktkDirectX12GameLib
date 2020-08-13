#ifndef CURSOR_SCRIPT_H_
#define CURSOR_SCRIPT_H_

#include <TktkDX12Game/Component/ComponentBase.h>
#include <TktkDX12BaseComponents/2D/Transform2D/Transform2D.h>

class CursorScript
	: public tktk::ComponentBase
{
public:

	void start();

	void update();

	void handleMessage(unsigned int messageId, const tktk::MessageAttachment& value);

private:

	tktk::ComponentPtr<tktk::Transform2D> m_transform;
};
#endif // !CURSOR_SCRIPT_H_