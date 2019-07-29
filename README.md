# Inspur_camera

[![](https://img.shields.io/badge/TGeek-project-blue.svg)](47.93.7.151)

 ![](https://img.shields.io/badge/%E6%B5%AA%E6%BD%AE%E9%9B%86%E5%9B%A2-%E8%87%AA%E5%8A%A8%E9%A9%BE%E9%A9%B6%E4%BA%8C%E7%BB%84-yellowgreen.svg)

[English](./README.en.md)

## 1.介绍

基于大疆RMCapture的摄像头 以及基于OpenCV的视频调用 API

**Author:** 陈明聪 Michael.Chen

**Website:** www.tgeek.tech

## 2.开发环境

**系统环境:** Ubuntu16.04

**软件环境:** Cmake2.8以上, C++11, OpenCV3.4.0 

## 3.文件结构

**src:** 源文件 

**include:** 头文件 

**lib:** 库文件 

**build:** 编译目录 

**video:** 测试视频 

**parm:** 配置文件

**CMakeLists.txt:** Cmake 配置文件

## 4.安装教程

### i.确保开发环境依赖安装完成 

### ii.配置编译

配置```CMakeLists.txt ```

```bash
gedit CMakeLists.txt
```

如果装有多版本OpenCV,修改文件第9行，指定想要使用的OpenCV路径

```cmake
#if u have OpenCV version more than one, set the build path which one u want to use
set(OpenCV_DIR "YOUR_PATH")
```

举例如下:

```cmake
#if u have OpenCV version more than one, set the build path which one u want to use
set(OpenCV_DIR "/home/test/app/opencv-3.4.0/build/")
```

### iii.编译

进入```build```文件夹进行编译

```bash
cd build
cmake ..
make
```

### iv.运行程序

```bash
./inspur_camera
```

## 5.使用说明

#### i.代码修改 

修改完代码**需重新在```build```文件夹下执行```make```编译**

#### ii.代码文件变更 

如有源代码文件移动(新增,删除文件，重命名)**需在```build/```文件夹下重新执行```cmake ..```配置并```make```编译**,即4.iii

#### iii. 摄像头使用 

```ImageConsumer.cpp``` 源文件第15行，取消注释```#define USE_CAMERA```，即可使用摄像头(默认video1，于57行```RMVideoCapture cap("/dev/video1", 3);```更改摄像头编号), 修改完成**需要重新```make```编译**

#### iv.视频文件使用 

```ImageConsProd.cpp``` 源文件第15行，注释```#define USE_CAMERA```，即可使用视频, 修改完成**需要重新```make```编译**

选定视频文件，需要将视频放入```video/```文件夹,然后在```param/```文件夹下的```param_config.xml```内第5行修改使用的视频文件名. **注:不需要编译，只需保存修改**

#### v.Debug 模式 

**Debug模式下，读入视频或者摄像头图像，检测键盘，每敲击一下键盘读入一帧图像**

Debug 模式打开与关闭

修改```param/```文件夹下的```param_config.xml```第4行，1代表打开，0代表关闭

```xml
<?xml version="1.0"?>
<opencv_storage>
                                            <!--0-disable     1-enable-->
<debug_mode>0</debug_mode>                  <!--wait for keyboard to process next frame-->
<video_name>project_video.mp4</video_name>  <!--video file name in {ProjectFolder}/video-->
<show_fps>0</show_fps>                      <!--display fps on output image-->
<show_time>1</show_time>                    <!--display time on output image-->
</opencv_storage>
```

#### vi.FPS或者系统时间输出

修改```param/```文件夹下的```param_config.xml```第6,7行，1代表打开，0代表关闭

```xml
<?xml version="1.0"?>
<opencv_storage>
                                            <!--0-disable     1-enable-->
<debug_mode>0</debug_mode>                  <!--wait for keyboard to process next frame-->
<video_name>project_video.mp4</video_name>  <!--video file name in {ProjectFolder}/video-->
<show_fps>0</show_fps>                      <!--display fps on output image-->
<show_time>1</show_time>                    <!--display time on output image-->
</opencv_storage>
```