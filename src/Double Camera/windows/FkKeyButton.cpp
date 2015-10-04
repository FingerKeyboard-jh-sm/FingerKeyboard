#include"FkPaperKeyboard.h"
#include<Windows.h>
void FkKeyButton::setKeyLocation(int x, int y, int width, int height){
	this->keyLocation = cvRect(x, y, width, height);
}
CvRect FkKeyButton::getKeyLocation(){
	return keyLocation;
}
FkKeyButton::FkKeyButton(){
	this->keyState = KEY_STATE_NONE;
}
void FkKeyButton::setKeyId(KeyId keyId){
	this->keyId = keyId;
}
KeyId FkKeyButton::getKeyId(){
	return this->keyId;
}
KeyState FkKeyButton::getKeyState(){
	return this->keyState;
}
void FkKeyButton::setPress(){
	this->keyState = KEY_STATE_PRESS;
}
void FkKeyButton::setHold(){
	this->keyState = KEY_STATE_PRESS_HOLD;

}
void FkKeyButton::setRelease(){
	this->keyState = KEY_STATE_RELEASE;
}
void FkKeyButton::setNone(){
	this->keyState = KEY_STATE_NONE;
}
void FkKeyButton::keyAction(){
	switch(this->keyId){
	case KEY_ID_ESC:
		if(this->keyState == KEY_STATE_PRESS)
			keybd_event(VK_ESCAPE, 0, 0, 0);
		break;
	case KEY_ID_F1:
		if(this->keyState == KEY_STATE_PRESS)
			keybd_event(VK_F1, 0, 0, 0);
		break;
	case KEY_ID_F2:
		if(this->keyState == KEY_STATE_PRESS)
			keybd_event(VK_F2, 0, 0, 0);
		break;
	case KEY_ID_F3:
		if(this->keyState == KEY_STATE_PRESS)
			keybd_event(VK_F3, 0, 0, 0);
		break;
	case KEY_ID_F4:
		if(this->keyState == KEY_STATE_PRESS)
			keybd_event(VK_F4, 0, 0, 0);
		break;
	case KEY_ID_F5:
		if(this->keyState == KEY_STATE_PRESS)
			keybd_event(VK_F5, 0, 0, 0);
		break;
	case KEY_ID_F6:
		if(this->keyState == KEY_STATE_PRESS)
			keybd_event(VK_F6, 0, 0, 0);
		break;
	case KEY_ID_F7:
		if(this->keyState == KEY_STATE_PRESS)
			keybd_event(VK_F7, 0, 0, 0);
		break;
	case KEY_ID_F8:
		if(this->keyState == KEY_STATE_PRESS)
			keybd_event(VK_F8, 0, 0, 0);
		break;
	case KEY_ID_F9:
		if(this->keyState == KEY_STATE_PRESS)
			keybd_event(VK_F9, 0, 0, 0);
		break;
	case KEY_ID_F10:
		if(this->keyState == KEY_STATE_PRESS)
			keybd_event(VK_F10, 0, 0, 0);
		break;
	case KEY_ID_F11:
		if(this->keyState == KEY_STATE_PRESS)
			keybd_event(VK_F11, 0, 0, 0);
		break;
	case KEY_ID_F12:
		if(this->keyState == KEY_STATE_PRESS)
			keybd_event(VK_F12, 0, 0, 0);
		break;
	case KEY_ID_PRTSC:
		if(this->keyState == KEY_STATE_PRESS)
			keybd_event(VK_SNAPSHOT, 0, 0, 0);
		break;
	case KEY_ID_DELETE:
		if(this->keyState == KEY_STATE_PRESS || this->keyState == KEY_STATE_PRESS_HOLD)
			keybd_event(VK_DELETE, 0, 0, 0);
		break;
	case KEY_ID_TILDE:
		if(this->keyState == KEY_STATE_PRESS || this->keyState == KEY_STATE_PRESS_HOLD)
			keybd_event(VK_OEM_3, 0, 0, 0);
		break;
	case KEY_ID_NUM_1:
		if(this->keyState == KEY_STATE_PRESS || this->keyState == KEY_STATE_PRESS_HOLD)
			keybd_event('1', 0, 0, 0);
		break;
	case KEY_ID_NUM_2:
		if(this->keyState == KEY_STATE_PRESS || this->keyState == KEY_STATE_PRESS_HOLD)
			keybd_event('2', 0, 0, 0);
		break;
	case KEY_ID_NUM_3:
		if(this->keyState == KEY_STATE_PRESS || this->keyState == KEY_STATE_PRESS_HOLD)
			keybd_event('3', 0, 0, 0);
		break;
	case KEY_ID_NUM_4:
		if(this->keyState == KEY_STATE_PRESS || this->keyState == KEY_STATE_PRESS_HOLD)
			keybd_event('4', 0, 0, 0);
		break;
	case KEY_ID_NUM_5:
		if(this->keyState == KEY_STATE_PRESS || this->keyState == KEY_STATE_PRESS_HOLD)
			keybd_event('5', 0, 0, 0);
		break;
	case KEY_ID_NUM_6:
		if(this->keyState == KEY_STATE_PRESS || this->keyState == KEY_STATE_PRESS_HOLD)
			keybd_event('6', 0, 0, 0);
		break;
	case KEY_ID_NUM_7:
		if(this->keyState == KEY_STATE_PRESS || this->keyState == KEY_STATE_PRESS_HOLD)
			keybd_event('7', 0, 0, 0);
		break;
	case KEY_ID_NUM_8:
		if(this->keyState == KEY_STATE_PRESS || this->keyState == KEY_STATE_PRESS_HOLD)
			keybd_event('8', 0, 0, 0);
		break;
	case KEY_ID_NUM_9:
		if(this->keyState == KEY_STATE_PRESS || this->keyState == KEY_STATE_PRESS_HOLD)
			keybd_event('9', 0, 0, 0);
		break;
	case KEY_ID_NUM_0:
		if(this->keyState == KEY_STATE_PRESS || this->keyState == KEY_STATE_PRESS_HOLD)
			keybd_event('0', 0, 0, 0);
		break;
	case KEY_ID_NUM_MINUS:
		if(this->keyState == KEY_STATE_PRESS || this->keyState == KEY_STATE_PRESS_HOLD)
			keybd_event(VK_SUBTRACT, 0, 0, 0);
		break;
	case KEY_ID_NUM_EQ:
		if(this->keyState == KEY_STATE_PRESS || this->keyState == KEY_STATE_PRESS_HOLD)
			keybd_event(VK_OEM_PLUS, 0, 0, 0);
		break;

	case KEY_ID_NUM_BACKSP:
		if(this->keyState == KEY_STATE_PRESS || this->keyState == KEY_STATE_PRESS_HOLD)
			keybd_event(VK_BACK,0,0,0);
		break;
	case KEY_ID_TAP:
		if(this->keyState == KEY_STATE_PRESS || this->keyState == KEY_STATE_PRESS_HOLD)
			keybd_event(VK_TAB, 0, 0, 0);
		break;
	case KEY_ID_Q:
		if(this->keyState == KEY_STATE_PRESS || this->keyState == KEY_STATE_PRESS_HOLD)
			keybd_event('Q',0,0,0);
		break;
	case KEY_ID_W:
		if(this->keyState == KEY_STATE_PRESS || this->keyState == KEY_STATE_PRESS_HOLD)
			keybd_event('W',0,0,0);
		break;
	case KEY_ID_E:
		if(this->keyState == KEY_STATE_PRESS || this->keyState == KEY_STATE_PRESS_HOLD)
			keybd_event('E',0,0,0);
		break;
	case KEY_ID_R:
		if(this->keyState == KEY_STATE_PRESS || this->keyState == KEY_STATE_PRESS_HOLD)
			keybd_event('R',0,0,0);
		break;
	case KEY_ID_T:
		if(this->keyState == KEY_STATE_PRESS || this->keyState == KEY_STATE_PRESS_HOLD)
			keybd_event('T',0,0,0);
		break;
	case KEY_ID_Y:
		if(this->keyState == KEY_STATE_PRESS || this->keyState == KEY_STATE_PRESS_HOLD)
			keybd_event('Y',0,0,0);
		break;
	case KEY_ID_U:
		if(this->keyState == KEY_STATE_PRESS || this->keyState == KEY_STATE_PRESS_HOLD)
			keybd_event('U',0,0,0);
		break;
	case KEY_ID_I:
		if(this->keyState == KEY_STATE_PRESS || this->keyState == KEY_STATE_PRESS_HOLD)
			keybd_event('I',0,0,0);
		break;
	case KEY_ID_O:
		if(this->keyState == KEY_STATE_PRESS || this->keyState == KEY_STATE_PRESS_HOLD)
			keybd_event('O',0,0,0);
		break;
	case KEY_ID_P:
		if(this->keyState == KEY_STATE_PRESS || this->keyState == KEY_STATE_PRESS_HOLD)
			keybd_event('P',0,0,0);
		break;
	case KEY_ID_OBRACKET:
		if(this->keyState == KEY_STATE_PRESS || this->keyState == KEY_STATE_PRESS_HOLD)
			keybd_event(VK_OEM_4,0,0,0);
		break;
	case KEY_ID_CBRACKET:
		if(this->keyState == KEY_STATE_PRESS || this->keyState == KEY_STATE_PRESS_HOLD)
			keybd_event(VK_OEM_6,0,0,0);
		break;
	case KEY_ID_BACKSLASH:
		if(this->keyState == KEY_STATE_PRESS || this->keyState == KEY_STATE_PRESS_HOLD)
			keybd_event(VK_OEM_5,0,0,0);
		break;
	case KEY_ID_CAPS:
		if(this->keyState == KEY_STATE_PRESS || this->keyState == KEY_STATE_PRESS_HOLD) {
			keybd_event(VK_CAPITAL ,0,0,0);
			keybd_event(VK_CAPITAL, 0, KEYEVENTF_KEYUP, 0);
		}
		break;
	case KEY_ID_A:
		if(this->keyState == KEY_STATE_PRESS || this->keyState == KEY_STATE_PRESS_HOLD)
			keybd_event('A',0,0,0);
		break;
	case KEY_ID_S:
		if(this->keyState == KEY_STATE_PRESS || this->keyState == KEY_STATE_PRESS_HOLD)
			keybd_event('S',0,0,0);
		break;
	case KEY_ID_D:
		if(this->keyState == KEY_STATE_PRESS || this->keyState == KEY_STATE_PRESS_HOLD)
			keybd_event('D',0,0,0);
		break;
	case KEY_ID_F:
		if(this->keyState == KEY_STATE_PRESS || this->keyState == KEY_STATE_PRESS_HOLD)
			keybd_event('F',0,0,0);
		break;
	case KEY_ID_G:
		if(this->keyState == KEY_STATE_PRESS || this->keyState == KEY_STATE_PRESS_HOLD)
			keybd_event('G',0,0,0);
		break;
	case KEY_ID_H:
		if(this->keyState == KEY_STATE_PRESS || this->keyState == KEY_STATE_PRESS_HOLD)
			keybd_event('H',0,0,0);
		break;
	case KEY_ID_J:
		if(this->keyState == KEY_STATE_PRESS || this->keyState == KEY_STATE_PRESS_HOLD)
			keybd_event('J',0,0,0);
		break;
	case KEY_ID_K:
		if(this->keyState == KEY_STATE_PRESS || this->keyState == KEY_STATE_PRESS_HOLD)
			keybd_event('K',0,0,0);
		break;
	case KEY_ID_L:
		if(this->keyState == KEY_STATE_PRESS || this->keyState == KEY_STATE_PRESS_HOLD)
			keybd_event('L',0,0,0);
		break;
	case KEY_ID_SEMI:
		if(this->keyState == KEY_STATE_PRESS || this->keyState == KEY_STATE_PRESS_HOLD)
			keybd_event(VK_OEM_1,0,0,0);
		break;
	case KEY_ID_QUOTE:
		if(this->keyState == KEY_STATE_PRESS || this->keyState == KEY_STATE_PRESS_HOLD)
			keybd_event(VK_OEM_7,0,0,0);
		break;
	case KEY_ID_ENTER:
		if(this->keyState == KEY_STATE_PRESS || this->keyState == KEY_STATE_PRESS_HOLD)
			keybd_event(VK_RETURN, 0, 0, 0);
		break;
	case KEY_ID_LSHIFT:
		if(keyState == KEY_STATE_PRESS)
			keybd_event(VK_LSHIFT, 0, KEYEVENTF_EXTENDEDKEY, 0);
		else if(keyState == KEY_STATE_RELEASE || keyState == KEY_STATE_NONE)
			keybd_event(VK_LSHIFT, 0, KEYEVENTF_KEYUP, 0);
		break;
	case KEY_ID_Z:
		if(this->keyState == KEY_STATE_PRESS || this->keyState == KEY_STATE_PRESS_HOLD)
			keybd_event('Z',0,0,0);
		break;
	case KEY_ID_X:
		if(this->keyState == KEY_STATE_PRESS || this->keyState == KEY_STATE_PRESS_HOLD)
			keybd_event('X',0,0,0);
		break;
	case KEY_ID_C:
		if(this->keyState == KEY_STATE_PRESS || this->keyState == KEY_STATE_PRESS_HOLD)
			keybd_event('C',0,0,0);
		break;
	case KEY_ID_V:
		if(this->keyState == KEY_STATE_PRESS || this->keyState == KEY_STATE_PRESS_HOLD)
			keybd_event('V',0,0,0);
		break;
	case KEY_ID_B:
		if(this->keyState == KEY_STATE_PRESS || this->keyState == KEY_STATE_PRESS_HOLD)
			keybd_event('B',0,0,0);
		break;
	case KEY_ID_N:
		if(this->keyState == KEY_STATE_PRESS || this->keyState == KEY_STATE_PRESS_HOLD)
			keybd_event('N',0,0,0);
		break;
	case KEY_ID_M:
		if(this->keyState == KEY_STATE_PRESS || this->keyState == KEY_STATE_PRESS_HOLD)
			keybd_event('M',0,0,0);
		break;
	case KEY_ID_COMMA:
		if(this->keyState == KEY_STATE_PRESS || this->keyState == KEY_STATE_PRESS_HOLD)
			keybd_event(VK_OEM_COMMA,0,0,0);
		break;
	case KEY_ID_DOT:
		if(this->keyState == KEY_STATE_PRESS || this->keyState == KEY_STATE_PRESS_HOLD)
			keybd_event(VK_OEM_PERIOD,0,0,0);
		break;
	case KEY_ID_SLASH:
		if(this->keyState == KEY_STATE_PRESS || this->keyState == KEY_STATE_PRESS_HOLD)
			keybd_event(VK_OEM_2,0,0,0);
		break;
	case KEY_ID_RSHIFT:
		if(keyState == KEY_STATE_PRESS)
			keybd_event(VK_RSHIFT, 0, 0, 0);
		else if(keyState == KEY_STATE_RELEASE || keyState == KEY_STATE_NONE)
			keybd_event(VK_RSHIFT, 0, KEYEVENTF_KEYUP, 0);
		break;
	case KEY_ID_CTRL:
		if(keyState == KEY_STATE_PRESS)
			keybd_event(VK_CONTROL, 0, 0, 0);
		else if(keyState == KEY_STATE_RELEASE || keyState == KEY_STATE_NONE)
			keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
		break;
	case KEY_ID_ALT:
		if(keyState == KEY_STATE_PRESS)
			keybd_event(VK_MENU, 0, 0, 0);
		else if(keyState == KEY_STATE_RELEASE || keyState == KEY_STATE_NONE)
			keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0);
		break;
	case KEY_ID_SPACE:
		if(this->keyState == KEY_STATE_PRESS || this->keyState == KEY_STATE_PRESS_HOLD)
			keybd_event(VK_SPACE,0,0,0);
		break;
	case KEY_ID_KOEN:
		if(this->keyState == KEY_STATE_PRESS)
			keybd_event(VK_HANGUL,0,0,0);
		break;
	case KEY_ID_DIREC_LEFT:
		if(this->keyState == KEY_STATE_PRESS || KEY_STATE_PRESS_HOLD)
			keybd_event(VK_LEFT,0,0,0);
		break;
	case KEY_ID_DIREC_RIGHT:
		if(this->keyState == KEY_STATE_PRESS || KEY_STATE_PRESS_HOLD)
			keybd_event(VK_RIGHT,0,0,0);
		break;
	case KEY_ID_DIREC_UP:
		if(this->keyState == KEY_STATE_PRESS || KEY_STATE_PRESS_HOLD)
			keybd_event(VK_UP,0,0,0);
		break;
	case KEY_ID_DIREC_DOWN:
		if(this->keyState == KEY_STATE_PRESS || KEY_STATE_PRESS_HOLD)
			keybd_event(VK_DOWN,0,0,0);
		break;
	}
	if( this->keyState == KEY_STATE_PRESS ) Beep(700,22);
}


void FkKeyButton::initSpecailKey() {
	keybd_event(VK_LSHIFT,0,KEYEVENTF_KEYUP,0);
	keybd_event(VK_RSHIFT,0,KEYEVENTF_KEYUP,0);
	keybd_event(VK_CONTROL,0,KEYEVENTF_KEYUP,0);
	keybd_event(VK_MENU,0,KEYEVENTF_KEYUP,0);
}