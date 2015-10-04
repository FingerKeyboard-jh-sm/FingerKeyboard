class FkFinger{
	bool downOrientMotion;
	bool validMotion;
	double motionVector;
	double motionVectorAccumulation;
public:
	FkFinger* prevFinger;
	CvPoint fingerTip;
	void setPrevFinger();
	void fingerCopy(FkFinger* finger);
	void setValidMotion();
	void setMotionVector();
	void initAttribute();
	bool isMotion();
	bool isDownMotion();
	bool isFingerInButton(FkKeyButton button);
	double getmotionVectorAccumulation();
	FkFinger();
	~FkFinger();
};