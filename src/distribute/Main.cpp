#include"FkProducerConsumer.h"
int main(){
	FkBuffer buffer;
	FkConsumer consumer(&buffer);
	FkProducer producer(&buffer);

	consumer.start();
	producer.start();
	consumer.join();
	producer.join();
}
