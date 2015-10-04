#include "FkFingerKeyboard.h"
#include <opencv2/core/core_c.h>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
int sm_fd[2];
char sm_buf[40];
int _proc_handle;

__sighandler_t kill_proc(){
	if(_proc_handle == 0)
	kill(_proc_handle, SIGKILL);
}

int main(int argc, char* argv[]) {
	int cameraDeviceIndexTop = 0;
	int cameraDeviceIndexBottom = 1;
	int keyboardType = 0;

	if (pipe(sm_fd) != 0 )
	 {
	    perror("pipe");
	    return 1;
    	}
	if ((_proc_handle=fork()) == 0)
	{
        printf("Starting up Python interface...\n");
        dup2(sm_fd[0], STDIN_FILENO);
 
        close(sm_fd[1]);
        execlp("python","python","mybluetooth.py", (char*)NULL);
        perror("execlp");
        printf("Error executing Python.\n");
        exit(1);
	}
	close(sm_fd[0]);

	signal(SIGKILL,(__sighandler_t)kill_proc);

	if(argc == 4) {
		cameraDeviceIndexTop = atoi(argv[1]);
		cameraDeviceIndexBottom = atoi(argv[2]);
		keyboardType = atoi(argv[3]);
	}
	FkFingerKeyboard fk(cameraDeviceIndexTop, cameraDeviceIndexBottom, keyboardType);
	fk.programRun();
/*
	IplImage* srcImage;
	if((srcImage=cvLoadImage("test.jpg",CV_LOAD_IMAGE_GRAYSCALE)) ==NULL)
		return -1;
	cvNamedWindow("test", CV_WINDOW_AUTOSIZE);
	cvShowImage("test", srcImage);
	cvWaitKey(0);
	cvDestroyAllWindows();
	cvReleaseImage(&srcImage);
*/
}
