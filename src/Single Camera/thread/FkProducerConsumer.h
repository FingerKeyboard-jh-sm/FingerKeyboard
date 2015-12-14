#include"FkBuffer.h"
#include"FkThread.h"
class FkProducer : public FkThread{
private:
	FkBuffer* buffer;
public:
	FkProducer(FkBuffer* buffer);
	void run();
	void cleanUp();
};
class FkConsumer : public FkThread{
private:
	FkBuffer* buffer;
public:
	FkConsumer(FkBuffer* buffer);
	void run();
	void cleanUp();
};