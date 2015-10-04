cmake_minimum_required(VERSION 2.8)

SET(COMPILE_DEFINITIONS -Werror)

include_directories(/opt/vc/include)
include_directories(/opt/vc/include/interface/vcos/pthreads)
include_directories(/opt/vc/include/interface/vmcs_host)
include_directories(/opt/vc/include/interface/vmcs_host/linux)

include_directories(/home/pi/src/FingerKeyboard/include/opencv2)

include_directories(/home/pi/src/FingerKeyboard/userland)
include_directories(/opt/vc/src/hello_pi/libs/vgfont)

link_directories(/opt/vc/lib)
link_directories(/opt/vc/src/hello_pi/libs/vgfont)



add_executable(mmal_dualCamera Main.cpp MmalDualCamera.cpp FkCamera.cpp FkFingerKeyboard.cpp FkPostprocessor.cpp FkFingertipDetector.cpp FkCurrentMode.cpp FkImageProcessor.cpp FkKeyButton.cpp FkKeyButtonEventListener.cpp FkMessage.cpp FkMouse.cpp FkMouseListener.cpp FkPaperKeyboard.cpp FkPaperKeyboard_TypeA.cpp FkPaperKeyboardRecognizer.cpp FkPreprocessor.cpp)

find_package( OpenCV REQUIRED )

target_link_libraries(mmal_dualCamera mmal_core mmal_util mmal_vc_client vcos bcm_host openmaxil EGL  pthread rt m freetype )
target_link_libraries(mmal_dualCamera vgfont)
target_link_libraries(mmal_dualCamera ${OpenCV_LIBS})