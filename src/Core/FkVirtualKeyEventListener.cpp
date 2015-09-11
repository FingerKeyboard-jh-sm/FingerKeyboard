#include"FkVirtualKeyEventListener.h"
#include"FkMessage.h"
#ifndef WIN32
int FkVirtualKeyEventListener::procHandle;
#endif
FkVirtualKeyEventListener::FkVirtualKeyEventListener(FkMessageQueue* messageQueue){
	this->messageQueue = messageQueue;
#ifndef WIN32
	if (pipe(fileDescriptor) != 0 ){
        perror("pipe");
    	return;
    }

    if ((procHandle=fork()) == 0){
        printf("Starting up Python interface...\n");
        dup2(fileDescriptor[0], STDIN_FILENO);
 
        close(fileDescriptor[1]);
        execlp("python","python","mybluetooth.py", (char*)NULL);
        perror("execlp");
        printf("Error executing Python.\n");
        exit(1);
    }
	close(fileDescriptor[0]);
	//signal(SIGKILL,FkVirtualKeyEventListener::(__sighandler_t)kill_proc);
#endif
}
void FkVirtualKeyEventListener::cleanUp(){

}
FkVirtualKeyEventListener::~FkVirtualKeyEventListener(){
#ifndef WIN32
	kill(procHandle, SIGKILL);
#endif
}
#ifndef WIN32
__sighandler_t FkVirtualKeyEventListener::kill_proc(){
	if(procHandle == 0)
	kill(procHandle, SIGKILL);
}

#endif
#ifdef WIN32
void FkVirtualKeyEventListener::run(){
	FkEventMessage message;
	while(1){
		message = messageQueue->dequeue();
		switch(message.getId()){
		case KEY_ID_ESC:
			if(message.getState() == KEY_STATE_PRESS)
				keybd_event(VK_ESCAPE, 0, 0, 0);
			break;
		case KEY_ID_F1:
			if(message.getState() == KEY_STATE_PRESS)
				keybd_event(VK_F1, 0, 0, 0);
			break;
		case KEY_ID_F2:
			if(message.getState() == KEY_STATE_PRESS)
				keybd_event(VK_F2, 0, 0, 0);
			break;
		case KEY_ID_F3:
			if(message.getState() == KEY_STATE_PRESS)
				keybd_event(VK_F3, 0, 0, 0);
			break;
		case KEY_ID_F4:
			if(message.getState() == KEY_STATE_PRESS)
				keybd_event(VK_F4, 0, 0, 0);
			break;
		case KEY_ID_F5:
			if(message.getState() == KEY_STATE_PRESS)
				keybd_event(VK_F5, 0, 0, 0);
			break;
		case KEY_ID_F6:
			if(message.getState() == KEY_STATE_PRESS)
				keybd_event(VK_F6, 0, 0, 0);
			break;
		case KEY_ID_F7:
			if(message.getState() == KEY_STATE_PRESS)
				keybd_event(VK_F7, 0, 0, 0);
			break;
		case KEY_ID_F8:
			if(message.getState() == KEY_STATE_PRESS)
				keybd_event(VK_F8, 0, 0, 0);
			break;
		case KEY_ID_F9:
			if(message.getState() == KEY_STATE_PRESS)
				keybd_event(VK_F9, 0, 0, 0);
			break;
		case KEY_ID_F10:
			if(message.getState() == KEY_STATE_PRESS)
				keybd_event(VK_F10, 0, 0, 0);
			break;
		case KEY_ID_F11:
			if(message.getState() == KEY_STATE_PRESS)
				keybd_event(VK_F11, 0, 0, 0);
			break;
		case KEY_ID_F12:
			if(message.getState() == KEY_STATE_PRESS)
				keybd_event(VK_F12, 0, 0, 0);
			break;
		case KEY_ID_PRTSC:
			//
			break;
		case KEY_ID_DELETE:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				keybd_event(VK_DELETE, 0, 0, 0);
			break;
		case KEY_ID_TILDE:
			//
			break;
		case KEY_ID_NUM_1:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				keybd_event(VK_NUMPAD1, 0, 0, 0);
			//
			break;
		case KEY_ID_NUM_2:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				keybd_event(VK_NUMPAD2, 0, 0, 0);
			//
			break;
		case KEY_ID_NUM_3:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				keybd_event(VK_NUMPAD3, 0, 0, 0);
			break;
		case KEY_ID_NUM_4:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				keybd_event(VK_NUMPAD4, 0, 0, 0);
			break;
		case KEY_ID_NUM_5:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				keybd_event(VK_NUMPAD5, 0, 0, 0);
			break;
		case KEY_ID_NUM_6:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				keybd_event(VK_NUMPAD6, 0, 0, 0);
			break;
		case KEY_ID_NUM_7:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				keybd_event(VK_NUMPAD7, 0, 0, 0);
			break;
		case KEY_ID_NUM_8:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				keybd_event(VK_NUMPAD8, 0, 0, 0);
			break;
		case KEY_ID_NUM_9:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				keybd_event(VK_NUMPAD9, 0, 0, 0);
			break;
		case KEY_ID_NUM_0:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				keybd_event(VK_NUMPAD0, 0, 0, 0);
			break;
		case KEY_ID_NUM_MINUS:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				keybd_event(VK_SUBTRACT, 0, 0, 0);
			break;
		case KEY_ID_NUM_EQ:
			//
			break;

		case KEY_ID_NUM_BACKSP:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				keybd_event(VK_BACK,0,0,0);
			break;
		case KEY_ID_TAP:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				keybd_event(VK_TAB, 0, 0, 0);
			break;
		case KEY_ID_Q:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				keybd_event('Q',0,0,0);
			break;
		case KEY_ID_W:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				keybd_event('W',0,0,0);
			break;
		case KEY_ID_E:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				keybd_event('E',0,0,0);
			break;
		case KEY_ID_R:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				keybd_event('R',0,0,0);
			break;
		case KEY_ID_T:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				keybd_event('T',0,0,0);
			break;
		case KEY_ID_Y:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				keybd_event('Y',0,0,0);
			break;
		case KEY_ID_U:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				keybd_event('U',0,0,0);
			break;
		case KEY_ID_I:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				keybd_event('I',0,0,0);
			break;
		case KEY_ID_O:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				keybd_event('O',0,0,0);
			break;
		case KEY_ID_P:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				keybd_event('P',0,0,0);
			break;
		case KEY_ID_OBRACKET:
			//keybd_event(VK_b
			break;
		case KEY_ID_CBRACKET:
			//keybd_event(VK_b
			break;
		case KEY_ID_BACKSLASH:
			//keybd_event(VK_b
			break;
		case KEY_ID_CAPS:
			//keybd_event(VK_C
			break;
		case KEY_ID_A:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				keybd_event('A',0,0,0);
			break;
		case KEY_ID_S:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				keybd_event('S',0,0,0);
			break;
		case KEY_ID_D:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				keybd_event('D',0,0,0);
			break;
		case KEY_ID_F:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				keybd_event('F',0,0,0);
			break;
		case KEY_ID_G:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				keybd_event('G',0,0,0);
			break;
		case KEY_ID_H:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				keybd_event('H',0,0,0);
			break;
		case KEY_ID_J:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				keybd_event('J',0,0,0);
			break;
		case KEY_ID_K:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				keybd_event('K',0,0,0);
			break;
		case KEY_ID_L:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				keybd_event('L',0,0,0);
			break;
		case KEY_ID_SEMI:
			//keybd_event(';',0, 0, 0);
			break;
		case KEY_ID_QUOTE:
			//keybd_event(
			break;
		case KEY_ID_ENTER:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				keybd_event(VK_RETURN, 0, 0, 0);
			break;
		case KEY_ID_LSHIFT:
			if(message.getState() == KEY_STATE_PRESS)
				keybd_event(VK_LSHIFT, 0, 0, 0);
			else if(message.getState() == KEY_STATE_RELEASE || message.getState() == KEY_STATE_NONE)
				keybd_event(VK_LSHIFT, 0, KEYEVENTF_KEYUP, 0);
			break;
		case KEY_ID_Z:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				keybd_event('Z',0,0,0);
			break;
		case KEY_ID_X:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				keybd_event('X',0,0,0);
			break;
		case KEY_ID_C:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				keybd_event('C',0,0,0);
			break;
		case KEY_ID_V:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				keybd_event('V',0,0,0);
			break;
		case KEY_ID_B:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				keybd_event('B',0,0,0);
			break;
		case KEY_ID_N:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				keybd_event('N',0,0,0);
			break;
		case KEY_ID_M:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				keybd_event('M',0,0,0);
			break;
		case KEY_ID_COMMA:
			//keybd_event(',', 0, 0, 0);
			break;
		case KEY_ID_DOT:
			//keybd_event('.', 0, 0, 0);
			break;
		case KEY_ID_SLASH:
			//keybd_event('/', 0, 0, 0);
			break;
		case KEY_ID_RSHIFT:
			if(message.getState() == KEY_STATE_PRESS)
				keybd_event(VK_RSHIFT, 0, 0, 0);
			else if(message.getState() == KEY_STATE_RELEASE || message.getState() == KEY_STATE_NONE)
				keybd_event(VK_RSHIFT, 0, KEYEVENTF_KEYUP, 0);
			break;
		case KEY_ID_CTRL:
			if(message.getState() == KEY_STATE_PRESS)
				keybd_event(VK_CONTROL, 0, 0, 0);
			else if(message.getState() == KEY_STATE_RELEASE || message.getState() == KEY_STATE_NONE)
				keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
			break;
		case KEY_ID_ALT:
			if(message.getState() == KEY_STATE_PRESS)
				keybd_event(VK_MENU, 0, 0, 0);
			else if(message.getState() == KEY_STATE_RELEASE || message.getState() == KEY_STATE_NONE)
				keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0);
			break;
		case KEY_ID_SPACE:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				keybd_event(VK_SPACE,0,0,0);
			break;
		case KEY_ID_KOEN:
			if(message.getState() == KEY_STATE_PRESS)
				keybd_event(VK_HANGUL,0,0,0);
			break;
		case KEY_ID_DIREC_LEFT:
			if(message.getState() == KEY_STATE_PRESS || KEY_STATE_PRESS_HOLD)
				keybd_event(VK_LEFT,0,0,0);
			break;
		case KEY_ID_DIREC_RIGHT:
			if(message.getState() == KEY_STATE_PRESS || KEY_STATE_PRESS_HOLD)
				keybd_event(VK_RIGHT,0,0,0);
			break;
		case KEY_ID_DIREC_UPDOWN:
			if(message.getState() == KEY_STATE_PRESS || KEY_STATE_PRESS_HOLD)
				keybd_event(VK_UP,0,0,0);
			break;
		}

	}
}
#else 
void FkVirtualKeyEventListener::run(){
	FkEventMessage message;
	while(1){
		message = messageQueue->dequeue();
		switch(message.getId()){
		case KEY_ID_ESC:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD){
				buffer[0]=')';
				buffer[1]='\0';
				write(fileDescriptor[1], buffer, strlen(buffer));
				write(fileDescriptor[1], "\n", 1);
			}
			break;
		case KEY_ID_TILDE:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
			{
				buffer[0]='`';
				buffer[1]='\0';
				write(fileDescriptor[1], buffer, strlen(buffer));
				write(fileDescriptor[1], "\n", 1);
			}
			//
			break;
		case KEY_ID_NUM_1:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
			{				
				buffer[0]='1';
				buffer[1]='\0';
				write(fileDescriptor[1], buffer, strlen(buffer));
				write(fileDescriptor[1], "\n", 1);
			}
			//
			break;
		case KEY_ID_NUM_2:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
			{	
				buffer[0]='2';
				buffer[1]='\0';
				write(fileDescriptor[1], buffer, strlen(buffer));
				write(fileDescriptor[1], "\n", 1);
			}
			break;
		case KEY_ID_NUM_3:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				//				keybd_event(VK_NUMPAD3, 0, 0, 0);
			{
				buffer[0]='3';
				buffer[1]='\0';
				write(fileDescriptor[1], buffer, strlen(buffer));
				write(fileDescriptor[1], "\n", 1);
			}
			break;
		case KEY_ID_NUM_4:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				//				keybd_event(VK_NUMPAD4, 0, 0, 0);
			{
				buffer[0]='4';
				buffer[1]='\0';
				write(fileDescriptor[1], buffer, strlen(buffer));
				write(fileDescriptor[1], "\n", 1);
			}			
			break;
		case KEY_ID_NUM_5:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				//				keybd_event(VK_NUMPAD5, 0, 0, 0);
			{
				buffer[0]='5';
				buffer[1]='\0';
				write(fileDescriptor[1], buffer, strlen(buffer));
				write(fileDescriptor[1], "\n", 1);
			}			
			break;
		case KEY_ID_NUM_6:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				//				keybd_event(VK_NUMPAD6, 0, 0, 0);
			{			
				buffer[0]='6';
				buffer[1]='\0';
				write(fileDescriptor[1], buffer, strlen(buffer));
				write(fileDescriptor[1], "\n", 1);
			}			
			break;
		case KEY_ID_NUM_7:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				//				keybd_event(VK_NUMPAD7, 0, 0, 0);
			{			
				buffer[0]='7';
				buffer[1]='\0';
				write(fileDescriptor[1], buffer, strlen(buffer));
				write(fileDescriptor[1], "\n", 1);
			}			
			break;
		case KEY_ID_NUM_8:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				//				keybd_event(VK_NUMPAD8, 0, 0, 0);
			{			
				buffer[0]='8';
				buffer[1]='\0';
				write(fileDescriptor[1], buffer, strlen(buffer));
				write(fileDescriptor[1], "\n", 1);
			}
			break;
		case KEY_ID_NUM_9:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				//				keybd_event(VK_NUMPAD9, 0, 0, 0);
			{			
				buffer[0]='9';
				buffer[1]='\0';
				write(fileDescriptor[1], buffer, strlen(buffer));
				write(fileDescriptor[1], "\n", 1);
			}			
			break;
		case KEY_ID_NUM_0:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				//				keybd_event(VK_NUMPAD0, 0, 0, 0);
			{			
				buffer[0]='0';
				buffer[1]='\0';
				write(fileDescriptor[1], buffer, strlen(buffer));
				write(fileDescriptor[1], "\n", 1);
			}			
			break;
		case KEY_ID_NUM_MINUS:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				//				keybd_event(VK_SUBTRACT, 0, 0, 0);

					break;
		case KEY_ID_NUM_EQ:
			{
				buffer[0]='=';
				buffer[1]='\0';
				write(fileDescriptor[1], buffer, strlen(buffer));
				write(fileDescriptor[1], "\n", 1);
			}		

			break;

		case KEY_ID_NUM_BACKSP:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				//				keybd_event(VK_BACK,0,0,0);
			{
				buffer[0]='!';
				buffer[1]='\0';
				write(fileDescriptor[1], buffer, strlen(buffer));
				write(fileDescriptor[1], "\n", 1);
			}		
			break;
			//		case KEY_ID_TAP:
			//			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
			//				keybd_event(VK_TAB, 0, 0, 0);
			//			break;
		case KEY_ID_Q:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				//				keybd_event('Q',0,0,0);
			{
				buffer[0]='q';
				buffer[1]='\0';
				write(fileDescriptor[1], buffer, strlen(buffer));
				write(fileDescriptor[1], "\n", 1);
			}			
			break;
		case KEY_ID_W:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				//				keybd_event('W',0,0,0);
			{
				buffer[0]='w';
				buffer[1]='\0';
				write(fileDescriptor[1], buffer, strlen(buffer));
				write(fileDescriptor[1], "\n", 1);
			}			
			break;
		case KEY_ID_E:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				//				keybd_event('E',0,0,0);
			{			
				buffer[0]='e';
				buffer[1]='\0';
				write(fileDescriptor[1], buffer, strlen(buffer));
				write(fileDescriptor[1], "\n", 1);
			}			
			break;
		case KEY_ID_R:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				//				keybd_event('R',0,0,0);
			{			
				buffer[0]='r';
				buffer[1]='\0';
				write(fileDescriptor[1], buffer, strlen(buffer));
				write(fileDescriptor[1], "\n", 1);
			}			
			break;
		case KEY_ID_T:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				//				keybd_event('T',0,0,0);
			{			
				buffer[0]='t';
				buffer[1]='\0';
				write(fileDescriptor[1], buffer, strlen(buffer));
				write(fileDescriptor[1], "\n", 1);
			}			
			break;
		case KEY_ID_Y:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				//				keybd_event('Y',0,0,0);
			{			
				buffer[0]='y';
				buffer[1]='\0';
				write(fileDescriptor[1], buffer, strlen(buffer));
				write(fileDescriptor[1], "\n", 1);
			}			
			break;
		case KEY_ID_U:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				//				keybd_event('U',0,0,0);
			{	
				buffer[0]='u';
				buffer[1]='\0';
				write(fileDescriptor[1], buffer, strlen(buffer));
				write(fileDescriptor[1], "\n", 1);
			}			
			break;
		case KEY_ID_I:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				//				keybd_event('I',0,0,0);
			{			
				buffer[0]='i';
				buffer[1]='\0';
				write(fileDescriptor[1], buffer, strlen(buffer));
				write(fileDescriptor[1], "\n", 1);
			}			
			break;
		case KEY_ID_O:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				//				keybd_event('O',0,0,0);
			{			
				buffer[0]='o';
				buffer[1]='\0';
				write(fileDescriptor[1], buffer, strlen(buffer));
				write(fileDescriptor[1], "\n", 1);
			}			
			break;
		case KEY_ID_P:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				//				keybd_event('P',0,0,0);
			{			
				buffer[0]='p';
				buffer[1]='\0';
				write(fileDescriptor[1], buffer, strlen(buffer));
				write(fileDescriptor[1], "\n", 1);
			}			
			break;
		case KEY_ID_OBRACKET:
			//keybd_event(VK_b
			{
				buffer[0]='[';
				buffer[1]='\0';
				write(fileDescriptor[1], buffer, strlen(buffer));
				write(fileDescriptor[1], "\n", 1);
			}		
			break;
		case KEY_ID_CBRACKET:
			//keybd_event(VK_b
			{
				buffer[0]=']';
				buffer[1]='\0';
				write(fileDescriptor[1], buffer, strlen(buffer));
				write(fileDescriptor[1], "\n", 1);
			}		
			break;
		case KEY_ID_BACKSLASH:
			//keybd_event(VK_b
			{
				buffer[0]='!';
				buffer[1]='\0';
				write(fileDescriptor[1], buffer, strlen(buffer));
				write(fileDescriptor[1], "\n", 1);
			}		
			break;
			//		case KEY_ID_CAPS:
			//keybd_event(VK_C
			//			break;
		case KEY_ID_A:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				//				keybd_event('A',0,0,0);
			{			
				buffer[0]='a';
				buffer[1]='\0';
				write(fileDescriptor[1], buffer, strlen(buffer));
				write(fileDescriptor[1], "\n", 1);
			}			
			break;
		case KEY_ID_S:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				//				keybd_event('S',0,0,0);
			{			
				buffer[0]='s';
				buffer[1]='\0';
				write(fileDescriptor[1], buffer, strlen(buffer));
				write(fileDescriptor[1], "\n", 1);
			}			
			break;
		case KEY_ID_D:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				//				keybd_event('D',0,0,0);
			{			
				buffer[0]='d';
				buffer[1]='\0';
				write(fileDescriptor[1], buffer, strlen(buffer));
				write(fileDescriptor[1], "\n", 1);
			}			
			break;
		case KEY_ID_F:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				//				keybd_event('F',0,0,0);
			{			
				buffer[0]='f';
				buffer[1]='\0';
				write(fileDescriptor[1], buffer, strlen(buffer));
				write(fileDescriptor[1], "\n", 1);
			}			
			break;
		case KEY_ID_G:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				//				keybd_event('G',0,0,0);
			{			
				buffer[0]='g';
				buffer[1]='\0';
				write(fileDescriptor[1], buffer, strlen(buffer));
				write(fileDescriptor[1], "\n", 1);
			}			
			break;
		case KEY_ID_H:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				//				keybd_event('H',0,0,0);
			{			
				buffer[0]='h';
				buffer[1]='\0';
				write(fileDescriptor[1], buffer, strlen(buffer));
				write(fileDescriptor[1], "\n", 1);
			}			
			break;
		case KEY_ID_J:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				//				keybd_event('J',0,0,0);
			{			
				buffer[0]='j';
				buffer[1]='\0';
				write(fileDescriptor[1], buffer, strlen(buffer));
				write(fileDescriptor[1], "\n", 1);
			}			
			break;
		case KEY_ID_K:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				//				keybd_event('K',0,0,0);
			{			
				buffer[0]='k';
				buffer[1]='\0';
				write(fileDescriptor[1], buffer, strlen(buffer));
				write(fileDescriptor[1], "\n", 1);
			}			
			break;
		case KEY_ID_L:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				//				keybd_event('L',0,0,0);
			{			
				buffer[0]='l';
				buffer[1]='\0';
				write(fileDescriptor[1], buffer, strlen(buffer));
				write(fileDescriptor[1], "\n", 1);
			}			
			break;
		case KEY_ID_SEMI:
			//keybd_event(';',0, 0, 0);
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
			{
				buffer[0]=';';
				buffer[1]='\0';
				write(fileDescriptor[1], buffer, strlen(buffer));
				write(fileDescriptor[1], "\n", 1);
			}		
			break;
		case KEY_ID_QUOTE:
			//keybd_event(
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
			{
				buffer[0]='~';
				buffer[1]='\0';
				write(fileDescriptor[1], buffer, strlen(buffer));
				write(fileDescriptor[1], "\n", 1);
			}		
			break;
		case KEY_ID_ENTER:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				//				keybd_event(VK_RETURN, 0, 0, 0);
			{
				buffer[0]='$';
				buffer[1]='\0';
				write(fileDescriptor[1], buffer, strlen(buffer));
				write(fileDescriptor[1], "\n", 1);
			}		

			break;
			//		case KEY_ID_LSHIFT:
			//			if(keyState == KEY_STATE_PRESS)
			//				keybd_event(VK_LSHIFT, 0, 0, 0);
			//			else if(keyState == KEY_STATE_RELEASE)
			//				keybd_event(VK_LSHIFT, 0, KEYEVENTF_KEYUP, 0);
			break;
		case KEY_ID_Z:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				//				keybd_event('Z',0,0,0);
			{			
				buffer[0]='z';
				buffer[1]='\0';
				write(fileDescriptor[1], buffer, strlen(buffer));
				write(fileDescriptor[1], "\n", 1);
			}			
			break;
		case KEY_ID_X:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				//				keybd_event('X',0,0,0);
			{			
				buffer[0]='x';
				buffer[1]='\0';
				write(fileDescriptor[1], buffer, strlen(buffer));
				write(fileDescriptor[1], "\n", 1);
			}			
			break;
		case KEY_ID_C:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				//				keybd_event('C',0,0,0);
			{			
				buffer[0]='c';
				buffer[1]='\0';
				write(fileDescriptor[1], buffer, strlen(buffer));
				write(fileDescriptor[1], "\n", 1);
			}			
			break;
		case KEY_ID_V:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				//				keybd_event('V',0,0,0);
			{			
				buffer[0]='v';
				buffer[1]='\0';
				write(fileDescriptor[1], buffer, strlen(buffer));
				write(fileDescriptor[1], "\n", 1);
			}
			break;
		case KEY_ID_B:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				//				keybd_event('B',0,0,0);
			{			
				buffer[0]='b';
				buffer[1]='\0';
				write(fileDescriptor[1], buffer, strlen(buffer));
				write(fileDescriptor[1], "\n", 1);
			}
			break;
		case KEY_ID_N:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				//				keybd_event('N',0,0,0);
			{			
				buffer[0]='n';
				buffer[1]='\0';
				write(fileDescriptor[1], buffer, strlen(buffer));
				write(fileDescriptor[1], "\n", 1);
			}
			break;
		case KEY_ID_M:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				//				keybd_event('M',0,0,0);
			{			
				buffer[0]='m';
				buffer[1]='\0';
				write(fileDescriptor[1], buffer, strlen(buffer));
				write(fileDescriptor[1], "\n", 1);
			}
			break;
		case KEY_ID_COMMA:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				//keybd_event(',', 0, 0, 0);
			{			
				buffer[0]=',';
				buffer[1]='\0';
				write(fileDescriptor[1], buffer, strlen(buffer));
				write(fileDescriptor[1], "\n", 1);
			}
			break;
		case KEY_ID_DOT:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				//keybd_event('.', 0, 0, 0);
			{			
				buffer[0]='.';
				buffer[1]='\0';
				write(fileDescriptor[1], buffer, strlen(buffer));
				write(fileDescriptor[1], "\n", 1);
			}			
			break;
		case KEY_ID_SLASH:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				//keybd_event('/', 0, 0, 0);
			{			
				buffer[0]='/';
				buffer[1]='\0';
				write(fileDescriptor[1], buffer, strlen(buffer));
				write(fileDescriptor[1], "\n", 1);
			}
			break;
			//		case KEY_ID_RSHIFT:
			//			if(keyState == KEY_STATE_PRESS)
			//				keybd_event(VK_RSHIFT, 0, 0, 0);
			//			else if(keyState == KEY_STATE_RELEASE)
			//				keybd_event(VK_RSHIFT, 0, KEYEVENTF_KEYUP, 0);
			//			break;
			//		case KEY_ID_CTRL:
			//			if(keyState == KEY_STATE_PRESS)
			//				keybd_event(VK_CONTROL, 0, 0, 0);
			//			else if(keyState == KEY_STATE_RELEASE)
			//				keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
			//			break;
			//		case KEY_ID_ALT:
			//			if(keyState == KEY_STATE_PRESS){
			//				keybd_event(VK_MENU, 0, 0, 0);
			//			}
			//			else if(keyState == KEY_STATE_RELEASE)
			//				keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0);
			//			break;
		case KEY_ID_SPACE:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				//keybd_event(VK_SPACE,0,0,0);
			{			
				buffer[0]=' ';
				buffer[1]='\0';
				write(fileDescriptor[1], buffer, strlen(buffer));
				write(fileDescriptor[1], "\n", 1);
			}
			break;
		case KEY_ID_KOEN:
			if(message.getState() == KEY_STATE_PRESS)
				//				keybd_event(VK_HANGUL,0,0,0);
			{			
				buffer[0]='@';
				buffer[1]='\0';
				write(fileDescriptor[1], buffer, strlen(buffer));
				write(fileDescriptor[1], "\n", 1);
			}
			break;
		case KEY_ID_DIREC_LEFT:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				//				keybd_event(VK_LEFT,0,0,0);
			{			
				buffer[0]='&';
				buffer[1]='\0';
				write(fileDescriptor[1], buffer, strlen(buffer));
				write(fileDescriptor[1], "\n", 1);
			}
			break;
		case KEY_ID_DIREC_RIGHT:
			if(message.getState() == KEY_STATE_PRESS || message.getState() == KEY_STATE_PRESS_HOLD)
				//				keybd_event(VK_RIGHT,0,0,0);
			{			
				buffer[0]='*';
				buffer[1]='\0';
				write(fileDescriptor[1], buffer, strlen(buffer));
				write(fileDescriptor[1], "\n", 1);
			}
			break;
		}
	}
}
#endif
