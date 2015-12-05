#include<opencv\cv.h>
#include<opencv\highgui.h>
#include<stdio.h>
int g_slider_posi = 0;
CvCapture* cap = NULL;

void onTrackbarSlide(int pos){
	cvSetCaptureProperty(cap, CV_CAP_PROP_POS_FRAMES, pos);
}
int main(){
	cvNamedWindow("Anal");
	bool run = true;
	cap = cvCreateFileCapture("Test.avi");
	int frames = (int)cvGetCaptureProperty(cap, CV_CAP_PROP_FRAME_COUNT);
	if(frames != 0)
		cvCreateTrackbar("frame", "Anal", &g_slider_posi, frames, onTrackbarSlide);
	IplImage* frame;
	while(1){
		if(run){
			frame = cvQueryFrame(cap);
			if(!frame)
				break;
			cvSetTrackbarPos("frame", "Anal", ++g_slider_posi);
			cvShowImage("Anal", frame);
			int key = cvWaitKey(50);
			if(key == 27)
				break;
			else if(key == 32)
				run = false;
		}
		else{
			cvSetCaptureProperty(cap, CV_CAP_PROP_POS_FRAMES, g_slider_posi);
			frame = cvQueryFrame(cap);
			cvSetTrackbarPos("frame", "Anal", g_slider_posi);
			cvShowImage("Anal", frame);
			char key = cvWaitKey(0);
			if(key == 27)
				break;
			else if(key == 32)
				run = true;
		else if(key =='d')
				g_slider_posi++;
			else if(key =='a')
				g_slider_posi--;
		}
	}
	cvReleaseCapture(&cap);
	cvDestroyAllWindows();

	return 0;
}





