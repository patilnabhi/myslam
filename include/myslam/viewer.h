#pragma once

#include <thread>
#include <pangolin/pangolin.h>

#include "myslam/common_include.h"
#include "myslam/map.h"
#include "myslam/frame.h"

namespace myslam {

class Viewer {
public:
	typedef std::shared_ptr<Viewer> Ptr;

	Viewer();

	void Close();

	void UpdateMap();

	void AddCurrentFrame(Frame::Ptr current_frame);

	void SetMap(Map::Ptr map) { mpMap = map; }

private:
	void ThreadLoop();

	void DrawFrame(Frame::Ptr frame, const float* color);

    void DrawMapPoints();

    void FollowCurrentFrame(pangolin::OpenGlRenderState& vis_camera);

    /// plot the features in current frame into an image
    cv::Mat PlotFrameImage();

private:
	Frame::Ptr mpCurrentFrame = nullptr;
    Map::Ptr mpMap = nullptr;

    std::unordered_map<unsigned long, Frame::Ptr> mvActiveKeyframes;
    std::unordered_map<unsigned long, MapPoint::Ptr> mvActiveLandmarks;
    bool mbMapUpdated = false;

	std::thread mthreadViewer;
	bool mbViewerRunning = true;
	std::mutex mMutexViewerData;
};

} // namespace myslam