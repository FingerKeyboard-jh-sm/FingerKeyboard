#include"FkPaperKeyboard.h"
FkPaperKeyboard_TypeA::FkPaperKeyboard_TypeA(){
	this->keyButton = new FkKeyButton[80];	// 각 키 버튼
	this->keyButtonCorner = new CvPoint2D32f[316];	// 각 키의 꼭짓점 정보
	this->keyButtonCount = 80;	// 키의 개수
	this->divisionNum = -1;
	for(int i = 0 ; i < keyButtonCount ; i++)
		this->keyButton[i].setKeyId(KeyId(i));
	this->pressedKey = -1;
	this->holdKey = -1;
}
void FkPaperKeyboard_TypeA::initKeyButtonCorner(){
	// 각 키패드의 좌표값들을 정렬한다.
	cornerSortingY(0,316);

	cornerSortingX(0,32);	cornerSortingX( 32,32);
	cornerSortingX(64,28);	cornerSortingX( 92,28);
	cornerSortingX(120,28);	cornerSortingX( 148,28);
	cornerSortingX(176, 26);cornerSortingX( 202, 26);
	cornerSortingX(228,24);	cornerSortingX( 252,24);
	cornerSortingX(276,40);	
	
	cornerSortingY(276, 28);			
	
	cornerSortingX(276,14); cornerSortingX(290, 14);

	cornerSortingY(304, 12);

	cornerSortingX(304, 2);
	cornerSortingX(306, 4);
	cornerSortingX(310, 6);

}

void FkPaperKeyboard_TypeA::setKeyboardCorner(CvPoint2D32f* corner){
	for(int i = 0 ; i < 4 ; i++)
		keyboardCorner[i] = corner[i];
}
void FkPaperKeyboard_TypeA::detectKeyButtonCorner(IplImage* srcImage){
	//500,250
	CvSize transSize = cvSize(640,480);
	IplImage* eigImage = cvCreateImage(transSize, IPL_DEPTH_8U,1);
	IplImage* tempImage = cvCreateImage(transSize, IPL_DEPTH_8U, 1);
	IplImage* grayImage = cvCreateImage(transSize, IPL_DEPTH_8U, 1);
	IplImage* dstImage = cvCreateImage(transSize, IPL_DEPTH_8U, 1);
	int keyButtonCornerCount = 316;
	cvCopy(srcImage, grayImage);
	//cvShowImage("ssssssssssssssss",srcImage);
	//cvShowImage("gggggggggggggggg",grayImage);
	

	cvGoodFeaturesToTrack(grayImage, eigImage, tempImage, keyButtonCorner, &keyButtonCornerCount, 0.03, 7, NULL, 10, 0);
	cvFindCornerSubPix (grayImage, keyButtonCorner, keyButtonCornerCount,cvSize (3, 3), cvSize (-1, -1), cvTermCriteria (CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, 0.03));
	initKeyButtonCorner();
	cvReleaseImage(&eigImage);
	cvReleaseImage(&tempImage);
	cvReleaseImage(&grayImage);
	cvReleaseImage(&dstImage);
}
//추후 수정
void FkPaperKeyboard_TypeA::cornerVerification(IplImage* srcImage){
	CvSize size = cvGetSize(srcImage);
	IplImage* eigImage = cvCreateImage(size, IPL_DEPTH_8U,1);
	IplImage* tempImage = cvCreateImage(size, IPL_DEPTH_8U, 1);
	IplImage* grayImage = cvCreateImage(size, IPL_DEPTH_8U, 1);
	IplImage* veriImage = cvCreateImage(size, IPL_DEPTH_8U, 1);
	IplImage* dstImage = cvCreateImage(size, IPL_DEPTH_8U, 1);
	IplImage* mask = cvCreateImage(size, IPL_DEPTH_8U, 1);
	IplImage* mask2 = cvCreateImage(size, IPL_DEPTH_8U, 1);
	CvRect rect = cvRect(10, 10, 640 - 20, 480 - 20);

	CvPoint2D32f srcQuad[4], dstQuad[4];
	CvMat* warp_matrix = cvCreateMat(3,3, CV_32FC1);
	CvMat* warp_matrix_invert = cvCreateMat(3,3, CV_32FC1);
	CvMat* result = cvCreateMat(3, 1, CV_32FC1);
	CvMat* dst = cvCreateMat(3, 1,CV_32FC1);

	int keyButtonCornerCount = 316;
	
	cvCvtColor(srcImage, grayImage, CV_BGR2GRAY);
	cvSetImageROI(grayImage, rect);
	cvSetImageROI(mask, rect);
	cvSetImageROI(dstImage, rect);
	cvSetImageROI(mask2, rect);

	// 150~255사이의 값만 추출해서 마스크에 저장
	cvInRangeS(grayImage, cvScalar(100, 100, 100), cvScalar(255, 255, 255), mask);
	cvCopy(mask, mask2);

	//cvShowImage("mask", mask);
	//cvShowImage("mask2", mask2);

	// 20,20? 150 미만의 값을 제외하기 위해 0인 값(mask)과 추출한 값(mask2)을 XOR 연산 한다.
	cvFloodFill(mask, cvPoint(10, 10), cvScalar(0, 0, 0));
	cvXor(mask2, mask, dstImage);
	
	//cvShowImage("mask3", mask);
	//cvShowImage("mask4", mask2);
	//cvShowImage("dstImage", dstImage);

	// 최종 연산된 이미지에서 코너 추출(각 키패드의 코너)
	cvGoodFeaturesToTrack(dstImage, eigImage, tempImage, keyButtonCorner, &keyButtonCornerCount, 0.01, 7, NULL, 7, 0);
	cvFindCornerSubPix (dstImage, keyButtonCorner, keyButtonCornerCount,cvSize (3, 3), cvSize (-1, -1), cvTermCriteria (CV_TERMCRIT_ITER | CV_TERMCRIT_EPS, 20, 0.03));
	
	cvResetImageROI(dstImage);
	for(int i =0 ; i < 316 ; i++){
		keyButtonCorner[i].x += rect.x;
		keyButtonCorner[i].y += rect.y;
	}
	
	initKeyButtonCorner();
	
	srcQuad[CLOCKWISE_1].x = keyButtonCorner[315].x+10;
	srcQuad[CLOCKWISE_1].y = keyButtonCorner[315].y-10;
	srcQuad[CLOCKWISE_5].x = keyButtonCorner[31].x + 10;
	srcQuad[CLOCKWISE_5].y = keyButtonCorner[31].y + 10;
	srcQuad[CLOCKWISE_7].x = keyButtonCorner[0].x - 10;
	srcQuad[CLOCKWISE_7].y = keyButtonCorner[0].y + 10;
	srcQuad[CLOCKWISE_11].x = keyButtonCorner[290].x - 10;
	srcQuad[CLOCKWISE_11].y = keyButtonCorner[290].y - 10;
	dstQuad[CLOCKWISE_1].x = 640;
	dstQuad[CLOCKWISE_1].y = 0;
	dstQuad[CLOCKWISE_5].x = 640;
	dstQuad[CLOCKWISE_5].y = 480;
	dstQuad[CLOCKWISE_7].x = 0;
	dstQuad[CLOCKWISE_7].y = 480;
	dstQuad[CLOCKWISE_11].x = 0;
	dstQuad[CLOCKWISE_11].y = 0;
	cvGetPerspectiveTransform(srcQuad, dstQuad, warp_matrix);
	
	cvWarpPerspective(dstImage, veriImage, warp_matrix);
	detectKeyButtonCorner(veriImage);
	cvInvert(warp_matrix, warp_matrix_invert);
	for(int i = 0 ; i < 316 ; i++){	
		cvmSet(dst, 0, 0, keyButtonCorner[i].x);  
		cvmSet(dst, 1, 0, keyButtonCorner[i].y);
		cvmSet(dst, 2, 0, 1);

		cvMatMul(warp_matrix_invert, dst, result);
		float t = cvmGet(result, 2,0);
		keyButtonCorner[i].x = cvmGet(result, 0,0)/t ;
		keyButtonCorner[i].y = cvmGet(result, 1,0)/t ;
	}
	cvResetImageROI(srcImage);
	cvResetImageROI(mask);
	cvReleaseImage(&eigImage);
	cvReleaseImage(&tempImage);
	cvReleaseImage(&grayImage);
	cvReleaseImage(&veriImage);
	cvReleaseImage(&dstImage);
	cvReleaseImage(&mask);
	cvReleaseImage(&mask2);
	cvReleaseMat(&warp_matrix);
	cvReleaseMat(&warp_matrix_invert);
	cvReleaseMat(&result);
	cvReleaseMat(&dst);	
}
void FkPaperKeyboard_TypeA::setDirectionKeyButtonArea(CvPoint2D32f* corners, int startIndex, int next, int index){
	int cornerCount = next*2;
	int keyWidth, keyHeight, keyX, keyY;
	float width1, width2, height1, height2;
	width1 = corners[startIndex + 1].x - corners[startIndex].x;
	width2 = corners[startIndex +cornerCount+1 ].x - corners[startIndex + cornerCount].x;
	width1 > width2 ? keyWidth = width1 : keyWidth =  width2;

	height1 = corners[startIndex ].y - corners[startIndex+ cornerCount].y;
	height2 = corners[startIndex +1].y - corners[startIndex +cornerCount + 1].y;
	height1 > height2 ? keyHeight = height1 : keyHeight = height2;
	
	keyX = (corners[startIndex + cornerCount].x + corners[startIndex].x)/2;
	keyY = (corners[startIndex + cornerCount].y + corners[startIndex + cornerCount + 1].y)/2;

	// Key Box 크기 수정
	int diff = 0;
	if(index == 76) {
		keyButton[76].setKeyLocation(keyX-diff, keyY-diff+(keyHeight+2*diff)/2, keyWidth+2*diff, (keyHeight+2*diff)/2);
		keyButton[79].setKeyLocation(keyX-diff, keyY-diff, keyWidth+2*diff, (keyHeight+2*diff)/2);
	}
	else
		keyButton[index].setKeyLocation(keyX-diff, keyY-diff, keyWidth+2*diff, keyHeight+2*diff);
}
void FkPaperKeyboard_TypeA::setKeyButtonArea(CvPoint2D32f* corners, int startIndex, int keyCount){
	int cornerCount = keyCount*2;
	int keyWidth, keyHeight, keyX, keyY;
	float width1, width2, height1, height2;
	int index = 0;
	static int line = 0;

	for(int i =startIndex  ; i < cornerCount + startIndex ; i +=2){
		width1 = corners[i+1].x - corners[i].x;
		width2 = corners[i+cornerCount + 1].x - corners[i + cornerCount].x;
		width1 > width2 ? keyWidth = width1 : keyWidth =  width2;
		height1 = corners[i].y - corners[i + cornerCount].y;
		height2 = corners[i+1].y - corners[i + cornerCount+1].y;
		height1 > height2 ? keyHeight = height1 : keyHeight = height2;

		keyX = (corners[i + cornerCount].x + corners[i].x)/2;
		keyY = (corners[i + cornerCount].y + corners[i + cornerCount + 1].y)/2;

		int diff = 0;
		// Key Box 크기 수정
		keyButton[(startIndex/4) + index++].setKeyLocation(keyX-diff, keyY-diff, keyWidth+2*diff, keyHeight+2*diff);
	}
	line++;
}
void FkPaperKeyboard_TypeA::setKeyButton(IplImage* srcImage){
	//꼭지점
	CvPoint2D32f srcQuad[4], dstQuad[4];

	IplImage* perspectiveTransImage = cvCreateImage(cvSize(640,480), IPL_DEPTH_8U, 3);

	CvMat* warp_matrix = cvCreateMat(3,3, CV_32FC1);
	CvMat* warp_matrix_invert = cvCreateMat(3,3, CV_32FC1);
	CvMat* result = cvCreateMat(3, 1, CV_32FC1);
	CvMat* dst = cvCreateMat(3, 1,CV_32FC1);

	sortPaperKeyboardCorner();
	
	srcQuad[CLOCKWISE_1] = keyboardCorner[1];
	srcQuad[CLOCKWISE_5] = keyboardCorner[2];
	srcQuad[CLOCKWISE_7] = keyboardCorner[3];
	srcQuad[CLOCKWISE_11] = keyboardCorner[0];

	dstQuad[CLOCKWISE_1].x = 640;
	dstQuad[CLOCKWISE_1].y = 0;
	dstQuad[CLOCKWISE_5].x = 640;
	dstQuad[CLOCKWISE_5].y = 480;
	dstQuad[CLOCKWISE_7].x = 0;
	dstQuad[CLOCKWISE_7].y = 480;
	dstQuad[CLOCKWISE_11].x = 0;
	dstQuad[CLOCKWISE_11].y = 0;	

	// 원근변환 후 검사한다.
	cvGetPerspectiveTransform(srcQuad, dstQuad, warp_matrix); // 변환 값 계산
	cvWarpPerspective(srcImage, perspectiveTransImage, warp_matrix);	// 투영 변환 행렬을 구한다
	cornerVerification(perspectiveTransImage);	// 추출된 행렬의 유효성을 검사한다
	cvInvert(warp_matrix, warp_matrix_invert);	// 
	
	//cvShowImage("srcImage",srcImage);
	//cvShowImage("perspectiveTransImage", perspectiveTransImage);

	for(int i = 0 ; i < 316 ; i++){
		cvmSet(dst, 0, 0, keyButtonCorner[i].x);  
		cvmSet(dst, 1, 0, keyButtonCorner[i].y);
		cvmSet(dst, 2, 0, 1);

		cvMatMul(warp_matrix_invert, dst, result);
		float t = cvmGet(result, 2,0);
		keyButtonCorner[i].x = cvmGet(result, 0,0)/t;
		keyButtonCorner[i].y = cvmGet(result, 1,0)/t;
	}
	
	setKeyButtonArea(keyButtonCorner, 0, 16);
	setKeyButtonArea(keyButtonCorner, 64, 14);
	setKeyButtonArea(keyButtonCorner, 120, 14);
	setKeyButtonArea(keyButtonCorner, 176, 13);
	setKeyButtonArea(keyButtonCorner, 228, 12);
	setKeyButtonArea(keyButtonCorner, 276, 7);
	setDirectionKeyButtonArea(keyButtonCorner, 306, 2, 77);
	setDirectionKeyButtonArea(keyButtonCorner, 304, 4, 76);
	setDirectionKeyButtonArea(keyButtonCorner, 308, 3, 78);
	
	cvReleaseImage(&perspectiveTransImage);

	cvReleaseMat(&warp_matrix);
	cvReleaseMat(&warp_matrix_invert);
	cvReleaseMat(&result);
	cvReleaseMat(&dst);
}
void FkPaperKeyboard_TypeA::setKeyButtonImage(IplImage* srcImage, IplImage* dstImage){
	cvCopy(srcImage, dstImage);
	for(int i =0 ; i < 16 ; i++)
		cvRectangleR(dstImage, keyButton[i].getKeyLocation(), CV_RGB(255,0,0), 1);
	for(int i =16 ; i < 30 ; i++)
		cvRectangleR(dstImage, keyButton[i].getKeyLocation(), CV_RGB(255,255,0), 1);
	for(int i =30 ; i < 44 ; i++)
		cvRectangleR(dstImage, keyButton[i].getKeyLocation(), CV_RGB(0, 255, 255), 1);
	for(int i =44 ; i < 57 ; i++)
		cvRectangleR(dstImage, keyButton[i].getKeyLocation(), CV_RGB(0,0,0), 1);
	for(int i =57 ; i < 69 ; i++)
		cvRectangleR(dstImage, keyButton[i].getKeyLocation(), CV_RGB(170,10,120), 1);
	for(int i =69 ; i < 76 ; i++)
		cvRectangleR(dstImage, keyButton[i].getKeyLocation(), CV_RGB(255,0,255), 1);
	for(int i =76 ; i < 80 ; i++)
		cvRectangleR(dstImage, keyButton[i].getKeyLocation(), CV_RGB(255,255,255), 1);
}

FkKeyButton* FkPaperKeyboard_TypeA::getKeyButton() {
	return this->keyButton;
}

FkPaperKeyboard_TypeA::~FkPaperKeyboard_TypeA(){
	delete []this->keyButton;
}