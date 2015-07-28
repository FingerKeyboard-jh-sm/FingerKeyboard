#include"FkKey.h"
FkKey::FkKey(){
	pthread_mutex_init(&mutex, NULL);
}
void FkKey::lock(){
	pthread_mutex_lock(&mutex);
}

void FkKey::unlock(){
	pthread_mutex_unlock(&mutex);
}
FkCondition* FkKey::newCondition(){
	return new FkCondition(&mutex);
}
