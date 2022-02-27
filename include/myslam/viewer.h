#pragma once

#include <thread>
#include <pangolin/pangolin.h>

#include "myslam/common_include.h"

namespace myslam {

class Viewer {
public:
	Viewer();

private:
	std::thread mthreadViewer;
	bool mbViewerRunning = true;
};

} // namespace myslam