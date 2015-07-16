#include"FkFingerKeyboard.h"
int main(int argc, char* argv[]){
	if(argc == 3){
		FkFingerKeyboard fk(atoi(argv[0]), atoi(argv[1]));
		if(fk.isCameraSet())
			fk.programRun();
	}
}