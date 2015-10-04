#include"FkImageDisplayer.h"
FkImageDisplayer::FkImageDisplayer(){
	
}
void FkImageDisplayer::setBuffer(FkImageBuffer* imageBuffer){
	this->imageBuffer = imageBuffer;
}
void FkImageDisplayer::run(){
	int sum = 0;
	IplImage* frame;
	while(1){
		frame = imageBuffer->outFrame();
		cvShowImage("Test", frame);
		if(cvWaitKey(1) == 27)
			break;
	}
}
