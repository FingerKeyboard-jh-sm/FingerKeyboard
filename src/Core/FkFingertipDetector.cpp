#include"FkPostProcessor.h"
FkFingerTipDetector::FkFingerTipDetector(){
	size = cvSize(640, 480);
	transImage = cvCreateImage(size, IPL_DEPTH_8U, 3);
	splitImage = cvCreateImage(size, IPL_DEPTH_8U, 1);
	bgSplitImage = cvCreateImage(size, IPL_DEPTH_8U, 1);
	handMasking = cvCreateImage(size, IPL_DEPTH_8U, 1);
	backProImage = cvCreateImage(size, IPL_DEPTH_8U, 1);
	handBinaryImage = cvCreateImage(size, IPL_DEPTH_8U, 1);
	storage = cvCreateMemStorage(0);
	contour = NULL;
}
void FkFingerTipDetector::getHandBinaryImage(IplImage* srcImage, IplImage* bgImage,CvHistogram* skinColorHistogram ){
	cvCvtColor(srcImage, transImage, CV_BGR2YCrCb);
	cvSplit(transImage, 0, splitImage, 0, 0);
	cvCalcBackProject(&splitImage, backProImage, skinColorHistogram);
	cvInRangeS(transImage, cvScalar(0, 133, 77), cvScalar(255, 173, 127), handMasking);
	cvSplit(bgImage, 0, bgSplitImage, 0, 0);
	cvAbsDiff(bgSplitImage, splitImage, splitImage);
	cvThreshold(splitImage, splitImage, 7, 255, CV_THRESH_BINARY);
	cvAnd(splitImage, handMasking, splitImage);
	cvAnd(backProImage, splitImage, backProImage);
	cvDilate(backProImage, backProImage, 0, 2);
	cvErode(backProImage, handBinaryImage, 0,6);
}
void FkFingerTipDetector::resetData(){
	userHand[0].setPrevDetectFingerCount();
	userHand[1].setPrevDetectFingerCount();

	userHand[0].resetFingerAttribute();
	userHand[1].resetFingerAttribute();
	
}
void FkFingerTipDetector::detectHandContour(CvRect selectedArea){
	double handArea[2] = {0,};
	double tempArea;
	CvSeq* tempContour;
	this->selectedArea = selectedArea;
	cvSetImageROI(handBinaryImage, this->selectedArea);
	if(cvFindContours(handBinaryImage, storage, &contour, sizeof(CvContour), CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, cvPoint(0, 0)) > 0){
		for(tempContour = contour ; tempContour != NULL ; tempContour = tempContour->h_next){
			tempArea = cvContourArea(tempContour, CV_WHOLE_SEQ);
			if(tempArea > handArea[0]){
				handArea[0] = tempArea;
				userHand[0].setHandContour(tempContour);
			}
		}
		
		userHand[0].setHandArea(handArea[0]);
		for(tempContour = contour ; tempContour != NULL ; tempContour = tempContour->h_next){
			tempArea = cvContourArea(tempContour, CV_WHOLE_SEQ);
			if(tempArea < handArea[0] && tempArea > handArea[1]){
				handArea[1] = tempArea;
				userHand[1].setHandContour(tempContour);
			}
		}
		userHand[1].setHandArea(handArea[1]);
	}
	cvResetImageROI(handBinaryImage);
}
void FkFingerTipDetector::setHandCenterPoint(){
	userHand[0].getHandDefect();
	userHand[0].convertArray();
	userHand[0].setHandCenter(this->selectedArea);
}

void FkFingerTipDetector::detectFingerTip(IplImage* srcImage){
	
	if(userHand[0].handArea > OVERLAP_HAND_AREA){
		detectHandCount = 0;
		std::cout<<"don't overlap hand"<<std::endl;
	} 
	else if(userHand[0].handArea < MAX_HAND_AREA && userHand[0].handArea > MIN_HAND_AREA && userHand[1].handArea < MIN_HAND_AREA){
		userHand[0].getHandDefect();	
		for(;userHand[0].defect; userHand[0].defect = userHand[0].defect->h_next){
			if(userHand[0].getDefectTotal() == 0)
				continue;
			userHand[0].convertArray();
			determineSingleHandFingerTip();
			detectHandCount = 1;
		}
	}
	if(userHand[1].handArea> MIN_HAND_AREA && userHand[1].handArea < MAX_HAND_AREA){
		userHand[0].getHandDefect();
		userHand[1].getHandDefect();
		for(;userHand[0].defect || userHand[1].defect ; userHand[0].defect = userHand[0].defect->h_next, userHand[1].defect = userHand[1].defect->h_next){
			if(userHand[0].getDefectTotal() == 0 || userHand[1].getDefectTotal() == 0)
				continue;
			userHand[0].convertArray();
			userHand[1].convertArray();
			determineDoubleHandFingerTip();
			detectHandCount = 2;
		}
	}
	userHand[0].correctPrevFingerTipIndex();
	userHand[1].correctPrevFingerTipIndex();
}
void FkFingerTipDetector::calcMotionProperty(){
	userHand[0].setValidMotionVector();
	userHand[1].setValidMotionVector();

	userHand[0].setFingerMotionVector();
	userHand[1].setFingerMotionVector();
}
void FkFingerTipDetector::determineSingleHandFingerTip(){
	CvConvexityDefect descendingOrder[100];
	int k = 0;
	int total = userHand[0].getDefectTotal();
	userHand[0].detectFingerCount = 0;
	for(int j = 0 ; j < total ; j++)
		if(userHand[0].defectArray[j].depth > MIN_FINGER_DEPTH)
			descendingOrder[userHand[0].detectFingerCount++] = userHand[0].defectArray[j];
	if(userHand[0].detectFingerCount == 0)
		return ;
	
	CvConvexityDefect tmp;
	for(int i = 0 ; i < userHand[0].detectFingerCount ; i++){
		for(int j = 0 ; j < (userHand[0].detectFingerCount -1) -i ; j++){
			if(descendingOrder[j].start->y < descendingOrder[j+1].start->y){
				tmp = descendingOrder[j];
				descendingOrder[j] = descendingOrder[j+1];
				descendingOrder[j+1] = tmp;
			}	
		}
	}
	k = 0;
	if(userHand[0].detectFingerCount >= 4){
		userHand[0].detectFingerCount = 5;
		for(int i = 0 ; i <total &&  k != 4 ; i++){
			for(int j = 0 ; j < userHand[0].detectFingerCount; j++){
				if(userHand[0].defectArray[i].start == descendingOrder[j].start){
					userHand[0].finger[k].fingerTip.x = (userHand[0].defectArray[i].start)->x + selectedArea.x;
					userHand[0].finger[k++].fingerTip.y = (userHand[0].defectArray[i].start)->y + selectedArea.y;
					if(k == 4){
						userHand[0].finger[k].fingerTip.x = (userHand[0].defectArray[i].end)->x + selectedArea.x;
						userHand[0].finger[k].fingerTip.y = (userHand[0].defectArray[i].end)->y + selectedArea.y;
						break;
					}
					break;
				}
			}
		}
	}
	else{
		for(int i = 0 ; i <total && k != userHand[0].detectFingerCount;i++)
			for(int j = 0 ; j < userHand[0].detectFingerCount ; j++)
				if(userHand[0].defectArray[i].start == descendingOrder[j].start){
					userHand[0].finger[k].fingerTip.x = (userHand[0].defectArray[i].start)->x + selectedArea.x;
					userHand[0].finger[k++].fingerTip.y = (userHand[0].defectArray[i].start)->y + selectedArea.y;
					if(k == userHand[0].detectFingerCount){
						userHand[0].finger[k].fingerTip.x = (userHand[0].defectArray[i].end)->x + selectedArea.x;
						userHand[0].finger[k].fingerTip.y = (userHand[0].defectArray[i].end)->y + selectedArea.y;
						break;
					}
					break;
				}
				userHand[0].detectFingerCount++;		
	}
	memset(descendingOrder, 0, 100);
}
void FkFingerTipDetector::determineDoubleHandFingerTip(){
	int k = 0;
	CvConvexityDefect descendingOrder[2][100];
	CvConvexityDefect tmp;
	int total[2];
	total[0] = userHand[0].getDefectTotal();
	total[1] = userHand[1].getDefectTotal();
	userHand[0].detectFingerCount = 0;
	userHand[1].detectFingerCount = 0;

	for(int i = 0 ; i < 2 ; i++){
		for(int j = 0 ; j < total[i] ; j++){
			if(userHand[i].defectArray[j].depth > 30)
				descendingOrder[i][userHand[i].detectFingerCount++] = userHand[i].defectArray[j];
		}
	}

	for(int k = 0 ; k < 2 ; k++){
		for(int i = 0 ; i < userHand[k].detectFingerCount ; i++){
			for(int j = 0 ; j < (userHand[k].detectFingerCount -1) -i ; j++){
				if(descendingOrder[k][j].start->y < descendingOrder[k][j+1].start->y){
					tmp = descendingOrder[k][j];
					descendingOrder[k][j] = descendingOrder[k][j+1];
					descendingOrder[k][j+1] = tmp;
				}	
			}
		}
	}
	//0¿Ã øﬁ¬ 		0¿∫ øﬁº” ¿˙¿Â.
	if(userHand[0].detectFingerCount > 0 && userHand[1].detectFingerCount > 0){
		if(descendingOrder[0][0].start->x < descendingOrder[1][0].start->x){
			for(int handSide = 0 ; handSide < 2 ; handSide++){
				k = 0;
				if(userHand[handSide].detectFingerCount >= 4){
					userHand[handSide].detectFingerCount= 5;
					for(int i = 0 ; i <total[handSide]&& k != 4; i++){

						for(int j = 0 ; j < userHand[handSide].detectFingerCount ; j++){
							if(userHand[handSide].defectArray[i].start == descendingOrder[handSide][j].start){
								userHand[handSide].finger[k].fingerTip.x = (userHand[handSide].defectArray[i].start)->x + selectedArea.x;
								userHand[handSide].finger[k++].fingerTip.y = (userHand[handSide].defectArray[i].start)->y + selectedArea.y;
								if(k == 4){
									userHand[handSide].finger[k].fingerTip.x = (userHand[handSide].defectArray[i].end)->x + selectedArea.x;
									userHand[handSide].finger[k].fingerTip.y = (userHand[handSide].defectArray[i].end)->y + selectedArea.y;
									break;
								}
								break;
							}
						}
					}

				}
				else{
					for(int i = 0 ; i <total[handSide]&& k != userHand[handSide].detectFingerCount; i++){
						for(int j = 0 ; j < userHand[handSide].detectFingerCount ; j++){
							if(userHand[handSide].defectArray[i].start == descendingOrder[handSide][j].start){
								userHand[handSide].finger[k].fingerTip.x = (userHand[handSide].defectArray[i].start)->x + selectedArea.x;
								userHand[handSide].finger[k++].fingerTip.y = (userHand[handSide].defectArray[i].start)->y + selectedArea.y;
								if(k == userHand[handSide].detectFingerCount){
									userHand[handSide].finger[k].fingerTip.x = (userHand[handSide].defectArray[i].end)->x + selectedArea.x;
									userHand[handSide].finger[k].fingerTip.y = (userHand[handSide].defectArray[i].end)->y + selectedArea.y;
									break;
								}
								break;
							}
						}
					}
					userHand[handSide].detectFingerCount++;
				}
			}
		}
		//1¿Ã øﬁº’
		else{
			for(int handSide = 0 ; handSide < 2 ; handSide++){
				k = 0;
				if(userHand[(handSide+1)%2].detectFingerCount >= 4){
					userHand[(handSide+1)%2].detectFingerCount= 5;
					for(int i = 0 ; i <total[(handSide+1)%2]&& k != 4; i++){
						for(int j = 0 ; j < userHand[(handSide+1)%2].detectFingerCount ; j++){
							if(userHand[(handSide+1)%2].defectArray[i].start == descendingOrder[(handSide+1)%2][j].start){
								userHand[handSide].finger[k].fingerTip.x = (userHand[(handSide+1)%2].defectArray[i].start)->x + selectedArea.x;
								userHand[handSide].finger[k++].fingerTip.y = (userHand[(handSide+1)%2].defectArray[i].start)->y + selectedArea.y;

								if(k == 4){
									userHand[handSide].finger[k].fingerTip.x = (userHand[(handSide+1)%2].defectArray[i].end)->x + selectedArea.x;
									userHand[handSide].finger[k].fingerTip.y = (userHand[(handSide+1)%2].defectArray[i].end)->y + selectedArea.y;
									break;
								}
								break;
							}
						}
					}

				}
				else{
					for(int i = 0 ; i <total[(handSide+1)%2]&&k != userHand[handSide].detectFingerCount; i++){
						for(int j = 0 ; j < userHand[(handSide+1)%2].detectFingerCount ; j++){
							if(userHand[(handSide+1)%2].defectArray[i].start == descendingOrder[(handSide+1)%2][j].start){
								userHand[handSide].finger[k].fingerTip.x = (userHand[(handSide+1)%2].defectArray[i].start)->x + selectedArea.x;
								userHand[handSide].finger[k++].fingerTip.y = (userHand[(handSide+1)%2].defectArray[i].start)->y + selectedArea.y;

								if(k == userHand[(handSide+1)%2].detectFingerCount){
									userHand[handSide].finger[k].fingerTip.x = (userHand[(handSide+1)%2].defectArray[i].end)->x + selectedArea.x;
									userHand[handSide].finger[k].fingerTip.y = (userHand[(handSide+1)%2].defectArray[i].end)->y + selectedArea.y;
									break;
								}
								break;
							}
						}
					}
					userHand[(handSide+1)%2].detectFingerCount++;
				}

			}
			int temp;
			temp = userHand[0].detectFingerCount;
			userHand[0].detectFingerCount = userHand[1].detectFingerCount;
			userHand[1].detectFingerCount = temp;
		}
	}
	memset(descendingOrder[0], 0 , 100);
	memset(descendingOrder[1], 0, 100);
}
FkFingerTipDetector::~FkFingerTipDetector(){
	cvReleaseImage(&transImage);
	cvReleaseImage(&splitImage);
	cvReleaseImage(&bgSplitImage);
	cvReleaseImage(&handMasking);
	cvReleaseImage(&backProImage);
	cvReleaseImage(&handBinaryImage);
}