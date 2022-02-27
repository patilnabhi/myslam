#include "myslam/initializer.h"

namespace myslam {

Initializer::Initializer(const Mat33& K, float sigma, int iterations) {
	mF = K(0,0);
	mPp = cv::Point2d(K(0,2), K(1,2));
	// mSigma = sigma;
	// mSigma2 = sigma*sigma;
	// mMaxIterations = iterations;
}

void Initializer::initialize(const std::vector<cv::Point2f>& vKeys1, const std::vector<cv::Point2f>& vKeys2, cv::Mat& R, cv::Mat& t) {

    LOG(INFO) << "no. of kps: " << vKeys1.size() << ", " << vKeys2.size();

    mE = cv::findEssentialMat(vKeys2, vKeys1, mF, mPp, cv::RANSAC, 0.999, 1.0, mMask);
    cv::recoverPose(mE, vKeys2, vKeys1, R, t, mF, mPp, mMask);
}

} // namespace myslam