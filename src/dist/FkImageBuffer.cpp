#include"FkImageBuffer.h"
#include<iostream>
using namespace std;
FkImageBuffer::FkImageBuffer(){
	imageProduce = key.newCondition();
	imageConsume = key.newCondition();
} 
void FkImageBuffer::inFrame(IplImage* frame){
	key.lock();
	if(queue.size() == BUF_SIZE)
		imageConsume->await();
	queue.push_back(frame);
	cout<<queue.size()<<endl;
	imageProduce->signal();
	key.unlock();
} 
IplImage* FkImageBuffer::outFrame(){
	key.lock();
	if(queue.empty())
		imageProduce->await();
	iterator = queue.begin();
	IplImage* image = *iterator;
	iterator = queue.erase(iterator);
	imageConsume->signal();
	key.unlock();
	return image;
}
FkImageBuffer::~FkImageBuffer(){
	delete imageProduce;
	delete imageConsume;

}