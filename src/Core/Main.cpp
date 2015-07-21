#include"FkFingerKeyboard.h"
#include<pthread.h>
int main(int argc, char* argv[]){
	pthread_t p_thread;
	if(argc == 3){
		FkFingerKeyboard fk(atoi(argv[1]), atoi(argv[2]));
		if(fk.isCameraSet())
			int a = pthread_create(&p_thread, NULL, fk.programRun, NULL);
	}
	printf("Main function return\n");
}