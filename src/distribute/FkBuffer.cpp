#include"FkBuffer.h"
#include<iostream>
FkBuffer::FkBuffer(){
	freeSpace = key.newCondition();
	moreProduct = key.newCondition();
}
void FkBuffer::add(int value){
	key.lock();
	if(queue.size() == bufferSize){
		cout<<"Wait for consume"<<endl;
		freeSpace->await();
	}
	queue.push_back(value);
	moreProduct->signal();
	key.unlock();
}
int FkBuffer::remove(){
	int value = 0;
	key.lock();
	if(queue.empty()){
		cout<<"\t\twait for produce"<<endl;
		moreProduct->await();
	}
	value = queue.back();
	queue.pop_back();
	freeSpace->signal();

	key.unlock();
	return value;
}