#include<opencv\cv.h>
#include<opencv\highgui.h>
#include<vector>
#ifndef FK_IMAGE_BUFFER_
#define FK_IMAGE_BUFFER_
#include"FkKey.h"
#include"FkCondition.h"
#define BUF_SIZE 100
using namespace std;
class FkImageBuffer{
	vector<IplImage*> queue;
	vector<IplImage*>::iterator iterator;
	FkKey key;
	FkCondition* imageProduce;
	FkCondition* imageConsume;
public:
	FkImageBuffer();
	void inFrame(IplImage* frame);
	IplImage* outFrame();
	~FkImageBuffer();
};
#endif