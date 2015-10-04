#include"FkProducerConsumer.h"
#include<cstdlib>
#include<ctime>
#include<iostream>
#include<Windows.h>
using namespace std;
void FkProducer::run(){
	int ran;
	srand((unsigned int)time(NULL));
	for(int i = 0 ; i < 21 ; i++){
		ran = (rand() % 100)+1 ;
		cout<<"Producer : "<<ran<<endl;
		buffer->add(ran);
		Sleep(ran);
	}

}
FkProducer::FkProducer(FkBuffer* buffer){
	this->buffer = buffer;
}
FkConsumer::FkConsumer(FkBuffer* buffer){
	this->buffer = buffer;
}
void FkConsumer::run(){
	for(int i = 0 ; i < 21 ; i++){
		cout<<"\t\tConsumer : "<<buffer->remove()<<endl;
		Sleep((rand() % 100) + 1);
	}
}