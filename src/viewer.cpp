#include "myslam/viewer.h"

namespace myslam {

Viewer::Viewer() {
	mthreadViewer = std::thread(std::bind(&Viewer::ThreadLoop, this));
}

void Viewer::Close() {
	mbViewerRunning = false;
	mthreadViewer.join();
}

} //namespace myslam