/*******************************************************************************************************************
@Copyright 2019 Inspur Co., Ltd
@Filename:  ImageConsumer.hpp
@Author:    Michael.Chen
@Version:   1.0
@Date:      15th/Jul/2018
*******************************************************************************************************************/
#pragma once
#include "opencv2/opencv.hpp"
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "setting.hpp"
#include "detection.hpp"
#include <time.h>
#include <sys/timeb.h>

class ImageConsumer{
public:
    ImageConsumer(Settings *settings)
    {
        _settings = settings;
    }
    ImageConsumer(){ }
    void ImageReader();
    void ImageProcesser();
    public:
        Settings * _settings;
};