/*******************************************************************************************************************
@Copyright 2019 Inspur Co., Ltd
@Filename:  ImageConsumer.cpp
@Author:    Michael.Chen
@Version:   1.0
@Date:      15th/Jul/2018
*******************************************************************************************************************/
#include "ImageConsumer.hpp"
#include "RMVideoCapture.hpp"

#define VIDEO_WIDTH  640
#define VIDEO_HEIGHT 480
#define BUFFER_SIZE 3

// #define USE_CAMERA	// If wanna to use camera, uncommit this line plz!!!!!

volatile unsigned int prdIdx = 0;		// index of reading image
volatile unsigned int csmIdx = 0;		// index of processing image

struct ImageData {
	cv::Mat img;             // data come from camera
	unsigned int frame;  	// index of img
};

ImageData capturedata[BUFFER_SIZE];   // Buffer of capture

/************************************************* 
    Function:      	ImageReader
    Description:    Image read
    Input:          video file or camare image 
    Output:         one frame of reading iamge
    Return:         void
    Others:         none
    *************************************************/
void ImageConsumer::ImageReader() 
{ 									
	Settings & setting = *_settings;			// set config

	#ifndef USE_CAMERA
	// use video file
	// read video file
	std::string video_name = "../video/";
	video_name+=setting.video_name;

	cv::VideoCapture cap(video_name);			// try to open video file
	if (!cap.isOpened())
   	{
        std::cout<<"ERROR: Cannot find file \""<<video_name<<"\""<<std::endl;
        return;
	}
	else{
		std::cout<<"INFO: File \""<<video_name<<"\" load successfully..."<<std::endl;
	}

	#else
	// use camera
	RMVideoCapture cap("/dev/video0", 3); 					// watch out camera index!!!
	cap.setVideoFormat(VIDEO_WIDTH, VIDEO_HEIGHT, 1);		// video format configeration
	cap.startStream();
	cap.setVideoFPS(60);
	cap.info();
	cap.setExposureTime(true,0);							// set to auto exposure, setExposureTime(true/false,int)
															// true-auto exposure / false-manual exposure, int-exposure time
	#endif

	while (true) {
		#ifdef USE_CAMERA
		while (prdIdx - csmIdx >= BUFFER_SIZE);				// wait for image producing
		cap >> capturedata[prdIdx % BUFFER_SIZE].img;		// image reading
		capturedata[prdIdx % BUFFER_SIZE].frame = cap.getFrameCount();
		#else
		while(prdIdx - csmIdx >= BUFFER_SIZE);				// wait for image producing
		cap >> capturedata[prdIdx % BUFFER_SIZE].img;		// image reading
		capturedata[prdIdx % BUFFER_SIZE].frame++;
		#endif
		++prdIdx;											// procecc next frame
	}
}

/************************************************* 
    Function:       ImageProcesser 
    Description:    Image process
    Input:          one frame of reading iamge
    Output:         frame after processing display
    Return:         void
    Others:         none
    *************************************************/
void ImageConsumer::ImageProcesser() {
	Settings & setting = *_settings;			// set config
	cv::Mat frame,output;								// source image
	Detector detector;

	// for processing speed calculating
	struct timeb tb;
	char process_time[30];
	char timenow[20];
	long fps =0;
    while(true){
		if(setting.show_fps||setting.show_time){			// if fps display or time display
			ftime(&tb);										// get time 
			struct tm *t = localtime(&tb.time);				// get time with format
			fps = tb.time*1000+tb.millitm;

			sprintf(timenow, "%d-%02d-%02d-%02d:%02d:%02d",
				t->tm_year + 1900,
				t->tm_mon + 1,
				t->tm_mday,
				t->tm_hour,
				t->tm_min,
				t->tm_sec);
		}

		while (prdIdx - csmIdx == 0);						// wait for image producing
		capturedata[csmIdx % BUFFER_SIZE].img.copyTo(frame);
		++csmIdx;											// load next frame

		frame.copyTo(output);

		detector.GetResult(output);
		detector.DrawResult(output,detector.Class_names,detector.Boxes,detector.Confidences,detector.Centers);

		if(setting.show_time){								// display time on image
			cv::putText(output,timenow,cv::Point(output.cols-250,20),0 , 0.6, cv::Scalar(255, 0, 128), 1);
		}

		if(setting.show_fps){								// display fps on imagerows
			ftime(&tb);
			sprintf(process_time,"FPS: %.2f",double(1000/((tb.time*1000+tb.millitm)-fps)));
			cv::putText(output,process_time,cv::Point(15,20),0 , 0.8, cv::Scalar(0, 255, 100), 1);
		}

		try {
			cv::imshow("frame", output);	
			if(setting.debug_mode<1){						// debug mode, wait for keyboard to continu
				char key = cv::waitKey(30);
				if(key == 27)								// if 'esc' pressed, programe close 
					exit(10);
			}

			else{											// undebug mode, continu processing
				char key = cv::waitKey(0);
				if(key == 27)								// if 'esc' pressed, programe close 
					exit(0);
			}

		}
		catch (cv::Exception e) {
			std::cout<<"Capture Error"<<std::endl;
		}			
    }
}


