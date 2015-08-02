#ifndef FK_EVENT_MSG_
#define FK_EVENT_MSG_
#include"FkKeyButtonProperty.h"
class FkEventMessage{
	KeyState state;
	KeyId id;
public:
	KeyState getState();
	KeyId getId();
};
#endif