/*******************************************************************************************************************
@Copyright 2019 Inspur Co., Ltd
@Filename:  setting.hpp
@Author:    Michael.Chen
@Version:   1.0
@Date:      15th/Jul/2018
*******************************************************************************************************************/
#pragma once
#include "opencv2/core/core.hpp"
#include <string>

class Settings{
public:
    Settings(const std::string & filename)
	{
        cv::FileStorage setting_fs(filename, cv::FileStorage::READ);
        read(setting_fs);
        setting_fs.release();
    }
    void read(const cv::FileStorage& fs) {
        fs["debug_mode"] >> debug_mode;
        fs["video_name"] >> video_name;
        fs["show_fps"] >> show_fps;
        fs["show_time"] >> show_time;
    }
public:
    int debug_mode;
    std::string video_name;
    int show_fps;
    int show_time;
};