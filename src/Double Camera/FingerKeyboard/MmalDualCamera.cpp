#ifndef _WINDOWS

#include "MmalDualCamera.h"

CAMERA_SET_DATA camera0Set;	// 카메라의 설정 정보를 담고 있는 구조체
CAMERA_SET_DATA camera1Set;

RETURN_STATE cameraSetDataInit(int cameraNum) {

	/* bcm_host_init */
	bcm_host_init();

	/* gx_graphics_init */
	gx_graphics_init("/opt/vc/src/hello_pi/hello_font");

	MMAL_RECT_T viewRect = {0, 0, CAMERA_VIEW_WIDTH, CAMERA_VIEW_HEIGHT};

	/* Camera Set */
	switch(cameraNum){
	case 2: {	// Camera Num == 2
		camera0Set.video_width = CAMERA_VIEW_WIDTH;
		camera0Set.video_height = CAMERA_VIEW_HEIGHT;

		camera0Set.image = cvCreateImage(cvSize(camera0Set.video_width,camera0Set.video_height),IPL_DEPTH_8U, 3);

		camera0Set.status = mmal_component_create(MMAL_COMPONENT_DEFAULT_CAMERA, &camera0Set.camera);
		if (camera0Set.status != STATE_SUCCESS) {
			printf("Error: create camera %x\n", camera0Set.status);
			return STATE_WRONG_PARAM;
		}

		MMAL_PARAMETER_INT32_T camera_num = 
		{{MMAL_PARAMETER_CAMERA_NUM, sizeof(camera_num)}, 1};	// CAM0 포트에 해당하는 카메라 번호는 1번
		// Raspberry pi에서 카메라 2대를 사용할 때 2번째 카메라 번호는 1번이며 CAM0 포트에 추가로 연결되어 있다.
		camera0Set.status = mmal_port_parameter_set(camera0Set.camera->control, &camera_num.hdr);

		if (camera0Set.status != MMAL_SUCCESS) {
			printf("Could not select camera : error %d", camera0Set.status);
			return STATE_CANNOT_SELECT_CAMERA;
		}

		if (!((camera0Set.camera)->output_num))
		{
			camera0Set.status = MMAL_ENOSYS;
			printf("Camera1 doesn't have output ports");
			return STATE_NOT_EXIST_OUTPUTPORT;
		}

		camera0Set.camera_video_port = camera0Set.camera->output[MMAL_CAMERA_VIDEO_PORT];

		{
			MMAL_PARAMETER_CAMERA_CONFIG_T cam_config = {
				{ MMAL_PARAMETER_CAMERA_CONFIG, sizeof (cam_config)},
				CAMERA_VIEW_WIDTH,
				CAMERA_VIEW_HEIGHT,
				0,
				0,
				CAMERA_VIEW_WIDTH,
				CAMERA_VIEW_HEIGHT,
				2,
				0,
				1,
				MMAL_PARAM_TIMESTAMP_MODE_RESET_STC
			};

			mmal_port_parameter_set(camera0Set.camera->control, &cam_config.hdr);
		}

		camera0Set.format = camera0Set.camera_video_port->format;

		camera0Set.format->encoding = MMAL_ENCODING_RGB24;
		camera0Set.format->encoding_variant = MMAL_ENCODING_RGB24;

		camera0Set.format->es->video.width = camera0Set.video_width;
		camera0Set.format->es->video.height = camera0Set.video_width;
		camera0Set.format->es->video.crop.x = 0;
		camera0Set.format->es->video.crop.y = 0;
		camera0Set.format->es->video.crop.width = camera0Set.video_width;
		camera0Set.format->es->video.crop.height = camera0Set.video_height;
		camera0Set.format->es->video.frame_rate.num = 30;
		camera0Set.format->es->video.frame_rate.den = 1;

		camera0Set.camera_video_port->buffer_size = camera0Set.video_width * camera0Set.video_height * 12 / 8 * 3;
		camera0Set.camera_video_port->buffer_num = 1;
		printf("  Camera video buffer_size = %d\n", camera0Set.camera_video_port->buffer_size);

		camera0Set.status = mmal_port_format_commit(camera0Set.camera_video_port);

		if (camera0Set.status != MMAL_SUCCESS) {
			printf("Error: unable to commit camera video port format (%u)\n", camera0Set.status);
			return STATE_PORT_FORMAT_FAIL;
		}

		camera0Set.camera_video_port_pool = (MMAL_POOL_T *) mmal_port_pool_create(camera0Set.camera_video_port, camera0Set.camera_video_port->buffer_num, camera0Set.camera_video_port->buffer_size);
		camera0Set.camera_video_port->userdata = (struct MMAL_PORT_USERDATA_T *) &camera0Set;

		camera0Set.status = mmal_port_enable(camera0Set.camera_video_port, video_buffer_callback);
		if (camera0Set.status != MMAL_SUCCESS) {
			printf("Error: unable to enable camera video port (%u)\n", camera0Set.status);
			return STATE_PORT_ENABLE_FAIL;
		}

		camera0Set.status = mmal_component_enable(camera0Set.camera);

		// Send all the buffers to the camera video port
		int num = mmal_queue_length(camera0Set.camera_video_port_pool->queue);
		int q;

		for (q = 0; q < num; q++) {
			MMAL_BUFFER_HEADER_T *buffer = mmal_queue_get(camera0Set.camera_video_port_pool->queue);

			if (!buffer) {
				printf("Unable to get a required buffer %d from pool queue\n", q);
			}

			if (mmal_port_send_buffer(camera0Set.camera_video_port, buffer) != MMAL_SUCCESS) {
				printf("Unable to send a buffer to encoder output port (%d)\n", q);
			}
		}

		if (mmal_port_parameter_set_boolean(camera0Set.camera_video_port, MMAL_PARAMETER_CAPTURE, 1) != MMAL_SUCCESS) {
			printf("%s: Failed to start capture\n", __func__);
		}

		vcos_semaphore_create(&camera0Set.complete_semaphore, "mmal_opencv_demo-sem", 0);
			}
	case 1: {	// Camera Num == 1 
		camera1Set.video_width = CAMERA_VIEW_WIDTH;
		camera1Set.video_height = CAMERA_VIEW_HEIGHT;

		camera1Set.image = cvCreateImage(cvSize(camera1Set.video_width,camera1Set.video_height),IPL_DEPTH_8U, 3);

		camera1Set.status = mmal_component_create(MMAL_COMPONENT_DEFAULT_CAMERA, &camera1Set.camera);
		if (camera1Set.status != STATE_SUCCESS) {
			printf("Error: create camera %x\n", camera1Set.status);
			return STATE_WRONG_PARAM;
		}

		MMAL_PARAMETER_INT32_T camera_num2 = 
		{{MMAL_PARAMETER_CAMERA_NUM, sizeof(camera_num2)}, 0};	// CAM1 포트에 해당하는 카메라 번호는 0번
		// Raspberry pi 에서 첫번째 카메라는 0번 카메라이며 포트는 CAM1에 연결되어 있다.
		camera1Set.status = mmal_port_parameter_set(camera1Set.camera->control, &camera_num2.hdr);

		if (camera1Set.status != MMAL_SUCCESS) {
			printf("Could not select camera : error %d", camera1Set.status);
			return STATE_CANNOT_SELECT_CAMERA;
		}

		if (!((camera1Set.camera)->output_num))
		{
			camera1Set.status = MMAL_ENOSYS;
			printf("Camera1 doesn't have output ports");
			return STATE_NOT_EXIST_OUTPUTPORT;
		}

		camera1Set.camera_video_port = camera1Set.camera->output[MMAL_CAMERA_VIDEO_PORT];

		{
			MMAL_PARAMETER_CAMERA_CONFIG_T cam_config = {
				{ MMAL_PARAMETER_CAMERA_CONFIG, sizeof (cam_config)},
				CAMERA_VIEW_WIDTH,
				CAMERA_VIEW_HEIGHT,
				0,
				0,
				CAMERA_VIEW_WIDTH,
				CAMERA_VIEW_HEIGHT,
				2,
				0,
				1,
				MMAL_PARAM_TIMESTAMP_MODE_RESET_STC
			};

			mmal_port_parameter_set(camera1Set.camera->control, &cam_config.hdr);
		}

		camera1Set.format = camera1Set.camera_video_port->format;

		camera1Set.format->encoding = MMAL_ENCODING_RGB24;
		camera1Set.format->encoding_variant = MMAL_ENCODING_RGB24;

		camera1Set.format->es->video.width = camera1Set.video_width;
		camera1Set.format->es->video.height = camera1Set.video_width;
		camera1Set.format->es->video.crop.x = 0;
		camera1Set.format->es->video.crop.y = 0;
		camera1Set.format->es->video.crop.width = camera1Set.video_width;
		camera1Set.format->es->video.crop.height = camera1Set.video_height;
		camera1Set.format->es->video.frame_rate.num = 30;
		camera1Set.format->es->video.frame_rate.den = 1;

		camera1Set.camera_video_port->buffer_size = camera1Set.video_width * camera1Set.video_height * 12 / 8 * 3;
		camera1Set.camera_video_port->buffer_num = 1;
		printf("  Camera video buffer_size = %d\n", camera1Set.camera_video_port->buffer_size);

		camera1Set.status = mmal_port_format_commit(camera1Set.camera_video_port);

		if (camera1Set.status != MMAL_SUCCESS) {
			printf("Error: unable to commit camera video port format (%u)\n", camera1Set.status);
			return STATE_PORT_FORMAT_FAIL;
		}

		camera1Set.camera_video_port_pool = (MMAL_POOL_T *) mmal_port_pool_create(camera1Set.camera_video_port, camera1Set.camera_video_port->buffer_num, camera1Set.camera_video_port->buffer_size);
		camera1Set.camera_video_port->userdata = (struct MMAL_PORT_USERDATA_T *) &camera1Set;

		camera1Set.status = mmal_port_enable(camera1Set.camera_video_port, video_buffer_callback);
		if (camera1Set.status != MMAL_SUCCESS) {
			printf("Error: unable to enable camera video port (%u)\n", camera1Set.status);
			return STATE_PORT_ENABLE_FAIL;
		}

		camera1Set.status = mmal_component_enable(camera1Set.camera);

		// Send all the buffers to the camera video port
		int num2 = mmal_queue_length(camera1Set.camera_video_port_pool->queue);
		int q2;

		for (q2 = 0; q2 < num2; q2++) {
			MMAL_BUFFER_HEADER_T *buffer = mmal_queue_get(camera1Set.camera_video_port_pool->queue);

			if (!buffer) {
				printf("Unable to get a required buffer %d from pool queue\n", q2);
			}
			if (mmal_port_send_buffer(camera1Set.camera_video_port, buffer) != MMAL_SUCCESS) {
				printf("Unable to send a buffer to encoder output port (%d)\n", q2);
			}
		}
		if (mmal_port_parameter_set_boolean(camera1Set.camera_video_port, MMAL_PARAMETER_CAPTURE, 1) != MMAL_SUCCESS) {
			printf("%s: Failed to start capture\n", __func__);
		}

		vcos_semaphore_create(&camera1Set.complete_semaphore, "mmal_opencv_demo-sem", 0);

		break;
			}
	default://Wrong Parameter
		return STATE_WRONG_PARAM;
	}

}

static void video_buffer_callback(MMAL_PORT_T *port, MMAL_BUFFER_HEADER_T *buffer) {
	MMAL_BUFFER_HEADER_T *new_buffer;
	CAMERA_SET_DATA * userdata = (CAMERA_SET_DATA *) port->userdata;
	MMAL_POOL_T *pool = userdata->camera_video_port_pool;
	mmal_buffer_header_mem_lock(buffer);
	memcpy(userdata->image->imageData, buffer->data, userdata->video_width * userdata->video_height * 3); //Img Copy
	mmal_buffer_header_mem_unlock(buffer);

	if (vcos_semaphore_trywait(&(userdata->complete_semaphore)) != VCOS_SUCCESS)
		vcos_semaphore_post(&(userdata->complete_semaphore));

	mmal_buffer_header_release(buffer);
	// and send one back to the port (if still open)
	if (port->is_enabled) {
		MMAL_STATUS_T status;

		new_buffer = mmal_queue_get(pool->queue);

		if (new_buffer)
			status = mmal_port_send_buffer(port, new_buffer);

		if (!new_buffer || status != MMAL_SUCCESS)
			printf("Unable to return a buffer to the video port\n");
	}
}

#endif