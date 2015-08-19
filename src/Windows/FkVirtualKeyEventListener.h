#ifndef FK_KEY_EVENT
#define FK_KEY_EVENT
#include"FkThread.h"
#include"FkKey.h"
#include"FkCondition.h"
#include"FkEventMessage.h"
#include"FkMessageQueue.h"
#include"FkKeyButtonProperty.h"

#ifdef WIN32
#include<Windows.h>
#else 
#include<signal.h>
#endif

//FkVirtual Key Event Listener thread consume a Key event Message
//Message Processing was differance to defined each OS(e.g Windows, Unix..)
class FkVirtualKeyEventListener : public FkThread{
	FkMessageQueue* messageQueue;
#ifndef WIN32
	int fileDescriptor[2];
	char buffer[40];
	int procHandle;
	__sighandler_t kill_proc();
	~FkVirtualKeyEventListener();
#endif
public:
	FkVirtualKeyEventListener(FkMessageQueue* messageQueue);
	
	void run();
};
#endif