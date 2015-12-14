#ifndef FK_LOG
#define FK_LOG
#include<fstream>
#include<FkPostProcessor.h>
using namespace std;
class FkMotionLogger{
	FkHand* userHand[2];
	ofstream fout;
	int frameCount;
public:
	FkMotionLogger(FkHand* userHand);
	void writeMotion();
	~FkMotionLogger();
};
#endif