/**
* @file FkCameraCalibrator.cpp
* @author 한성대학교 컴퓨터공학과 강진혁(jinhuk1313@gmail.com)	
* @brief 영상 좌표계, 세계 좌표계를 이용한 카메라 외부, 내부 파라미터를 산출 
*/
#include"FkPreProcessor.h"
#include<fstream>

#define TAG_CAMERA "cameraMat"
#define TAG_DISTOR "distortionCoeffs"
#define FILE_NAME "realworldcorner.txt"
#define XML_FILE_NAME "camcalib.xml"

using namespace std;
FkCameraCalibrator::FkCameraCalibrator(){
	this->cameraMat			= cvCreateMat(3, 3, CV_32F);
	this->distortionCoeffs	= cvCreateMat(1, 4, CV_64F);
	camCalibrateReader = NULL;
	camCalibrateWriter = NULL;
}
void FkCameraCalibrator::readFile(){
	camCalibrateReader	= cvOpenFileStorage(XML_FILE_NAME, 0, CV_STORAGE_READ);
	cameraMat			= (CvMat*)cvReadByName(camCalibrateReader, 0, TAG_CAMERA);
	distortionCoeffs	= (CvMat*)cvReadByName(camCalibrateReader, 0, TAG_DISTOR);
	if(!cameraMat || !distortionCoeffs)
		camCalibrate = false;
	else
		camCalibrate = true;

}
bool FkCameraCalibrator::isCamCalibrated(){
	return camCalibrate;
}
FkCameraCalibrator::~FkCameraCalibrator(){
	cvReleaseMat(&cameraMat);
	cvReleaseMat(&distortionCoeffs);
	cvReleaseFileStorage(&camCalibrateReader);
	if(camCalibrateWriter)
		cvReleaseFileStorage(&camCalibrateWriter);
}
void FkCameraCalibrator::cameraCalibration(IplImage* srcImage, FkPaperKeyboard* paperKeyboard){
	ifstream fin;
	double x, y;
	CvSize size			= cvGetSize(srcImage);
	int cornerCount		= paperKeyboard->getKeyButtonCornerCount() - 12;
	CvMat* mWorld		= cvCreateMat(2, cornerCount, CV_32F);
	CvMat* mScreen		= cvCreateMat(2, cornerCount, CV_32F);
	CvMat* worldPoint	= cvCreateMat(3, cornerCount, CV_32F);
	CvMat* screenPoint	= cvCreateMat(2, cornerCount, CV_32F);
	CvMat* mVerifyScreen= cvCreateMat(1, cornerCount, CV_64FC2);
	CvMat* mVerifyWorld = cvCreateMat(1, cornerCount, CV_64FC3);
	CvMat* pointCount	= cvCreateMat(1, 1, CV_32S);
	CvMat* rotationVector		= cvCreateMat(1, 3, CV_32F);
	CvMat* translationVector	= cvCreateMat(1, 3, CV_32F);
	CvMat* rotationMat			= cvCreateMat(3, 3, CV_64F);
	CvTermCriteria criteria		= cvTermCriteria(CV_TERMCRIT_ITER+ CV_TERMCRIT_EPS, 30, DBL_EPSILON);
	double reError =0;
	IplImage* co = cvCreateImage(size, IPL_DEPTH_8U, 3);
	IplImage* co1 = cvCreateImage(size, IPL_DEPTH_8U, 3);
	fin.open(FILE_NAME);
	if(!fin)
		return;
	for(int i = 0 ; i < cornerCount ; i++){
		fin>>x;
		fin>>y;

		cvmSet(mWorld, 0, i, x);
		cvmSet(mWorld, 1, i,  CV_IABS((y-11)));
		cvmSet(mScreen, 0, i, paperKeyboard->getKeyButtonCorner(i).x);
		cvmSet(mScreen, 1, i, paperKeyboard->getKeyButtonCorner(i).y);

		CV_MAT_ELEM(*worldPoint, float, 0, i) = CV_MAT_ELEM(*mWorld, float, 0, i);
		CV_MAT_ELEM(*worldPoint, float, 1, i) = CV_MAT_ELEM(*mWorld, float, 1, i);
		CV_MAT_ELEM(*worldPoint, float, 2, i) = 0.0;

		CV_MAT_ELEM(*screenPoint, float, 0, i) = CV_MAT_ELEM(*mScreen, float, 0, i);
		CV_MAT_ELEM(*screenPoint, float, 1, i) = CV_MAT_ELEM(*mScreen, float, 1, i);
	}

	cvSetReal1D(pointCount, 0, cornerCount);

	reError =  cvCalibrateCamera2(worldPoint, screenPoint, pointCount, size, cameraMat,  distortionCoeffs, NULL, NULL, 0,criteria);

	camCalibrateWriter = cvOpenFileStorage(XML_FILE_NAME, 0, CV_STORAGE_WRITE);
	cvConvertPointsHomogeneous(mWorld, mVerifyWorld);

	cvFindExtrinsicCameraParams2(mWorld, mScreen,  cameraMat,  distortionCoeffs,
		rotationVector, translationVector, 0);

	cvProjectPoints2(mVerifyWorld, rotationVector, translationVector,  cameraMat,  distortionCoeffs, mVerifyScreen);
	cvWrite(camCalibrateWriter, TAG_CAMERA,  cameraMat);
	cvWrite(camCalibrateWriter, TAG_DISTOR,  distortionCoeffs);

	camCalibrate = true;
	FkCurrentMode::state = SET_KB_REGION;
	cvReleaseFileStorage(&camCalibrateWriter);
	cvReleaseMat(&mScreen);
	cvReleaseMat(&mVerifyScreen);
	cvReleaseMat(&mWorld);
	cvReleaseMat(&mVerifyWorld);
	cvReleaseMat(&rotationMat);
	cvReleaseMat(&rotationVector);
	cvReleaseMat(&translationVector);
	cvReleaseMat(&pointCount);
	cvReleaseMat(&worldPoint);
	cvReleaseMat(&screenPoint);

}