#include"FkFingerKeyboard.h"
#include<pthread.h>
int main(int argc, char* argv[]){
	if(argc == 3){
		FkFingerKeyboard fk(atoi(argv[1]), atoi(argv[2]));
		if(fk.isCameraSet())
			fk.programRun();
	}
}