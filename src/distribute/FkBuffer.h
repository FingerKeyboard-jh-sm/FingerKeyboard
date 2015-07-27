#include"FkCondition.h"
#include"FkKey.h"
#include<vector>
using namespace std;
#ifndef FK_BUFFER_
#define FK_BUFFER_
class FkBuffer{
	static const int bufferSize = 3;
	vector<int> queue;
	vector<int>::iterator it;
	FkKey key;
	FkCondition* freeSpace;
	FkCondition* moreProduct;
public:
	FkBuffer();
	void add(int value);
	int remove();
};
#endif