/*******************************************************************************************************************
@Copyright 2019 Inspur Co., Ltd
@Filename:  main.cpp
@Author:    Michael.Chen
@Version:   1.0
@Date:      15th/Jul/2018
*******************************************************************************************************************/
#include <thread> 
#include <unistd.h>
#include <iostream>
#include "ImageConsumer.hpp" 
#include "setting.hpp"

/************************************************* 
    Function:       main
    Description:    function entrance
    Calls:          
                    DetectProcess::ImageProducer()
                    DetectProcess::ImageConsumer() 
    Input:          None 
    Output:         None 
    Return:         return 0
    *************************************************/
int main(int argc, char * argv[])
{
	char *config_file_name = "../param/param_config.xml";           // load config file
    cv::FileStorage fs(config_file_name, cv::FileStorage::READ);    // initialization config
    if (!fs.isOpened())     //open xml config file
    {
        std::cout << "Could not open the configuration file: param_config.xml " << std::endl;
        return -1;
    }
    Settings setting(config_file_name);

    ImageConsumer image_consumer(&setting);
    
	std::thread task0(&ImageConsumer::ImageReader, image_consumer);  	// add image reading thread
	std::thread task1(&ImageConsumer::ImageProcesser, image_consumer);  // add image processing thread

	// thread joined
	task0.join();
    task1.join();
    
	return EXIT_SUCCESS;
}