#include<opencv\cv.h>
#include<opencv\highgui.h>
#ifndef FK_DISPLAYER_
#define FK_DISPLAYER_
#include"FkThread.h"
#include"FkImageBuffer.h"
class FkImageDisplayer : public FkThread{
	FkImageBuffer* imageBuffer;
public:
	void setBuffer(FkImageBuffer* imageBuffer);
	FkImageDisplayer();
	void run();
};
#endif