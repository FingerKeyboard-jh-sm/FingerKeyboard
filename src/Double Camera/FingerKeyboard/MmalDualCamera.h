#ifndef _WINDOWS
#ifndef MMALDUALCAMERA_H
#define MMALDUALCAMERA_H

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include <opencv2/core/core_c.h>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "bcm_host.h"
#include "interface/vcos/vcos.h"

#include "/home/pi/src/FingerKeyboard/userland/interface/mmal//util/mmal_util.h"
#include "/home/pi/src/FingerKeyboard/userland/interface/mmal//util/mmal_util_params.h"
#include "interface/mmal/mmal.h"
#include "interface/mmal/util/mmal_default_components.h"
#include "interface/mmal/util/mmal_connection.h"

#include "vgfont.h"


#define MMAL_CAMERA_VIDEO_PORT 1

#define CAMERA_VIEW_WIDTH 640
#define CAMERA_VIEW_HEIGHT 480

typedef enum RETURN_STATE {
	STATE_SUCCESS,
	STATE_WRONG_PARAM,
	STATE_CANNOT_SELECT_CAMERA,
	STATE_NOT_EXIST_OUTPUTPORT,
	STATE_PORT_FORMAT_FAIL,
	STATE_PORT_ENABLE_FAIL,
	STATE_COMPONENT_CREATE_FAIL,
	STATE_PARAM_SET_FAIL,
	STATE_CONNECTION_CREATE_FAIL,
	STATE_CONNECTION_ENABLE_FAIL
	
}RETURN_STATE;

typedef struct CAMERA_SET_DATA{

	/* PORT_USERDATA */
	int video_width;
    int video_height;
    MMAL_POOL_T *camera_video_port_pool;

	IplImage* image;	//

    VCOS_SEMAPHORE_T complete_semaphore;

	/* ? */
	MMAL_COMPONENT_T *camera;
	
	MMAL_ES_FORMAT_T *format;
	
	MMAL_STATUS_T status;
	
	MMAL_PORT_T *camera_video_port;


} CAMERA_SET_DATA;

extern CAMERA_SET_DATA camera0Set;	//
extern CAMERA_SET_DATA camera1Set;	//


/* 
	Name	  : Video Buffer CallBack
	Parameter : MMAL_PORT_T , MMAL_BUFFER_HEADER_T
	Function  : ?
*/
static void video_buffer_callback(MMAL_PORT_T *port, MMAL_BUFFER_HEADER_T *buffer);

/* 
	Name	  : CAMERA_SET_DATA INIT
	Parameter : int cameraNum ( Count ) 
	Function  : Initialized Variables
*/
RETURN_STATE cameraSetDataInit(int cameraNum);

#endif
#endif