#ifndef FK_EVENT_MSG_
#define FK_EVENT_MSG_
#include"FkKeyButtonProperty.h"
class FkEventMessage{
	KeyState state;
	KeyId id;
public:
	FkEventMessage(KeyId id, KeyState state);
	FkEventMessage();
	KeyState getState();
	KeyId getId();
};
#endif