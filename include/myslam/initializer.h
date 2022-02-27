#pragma once

#include "myslam/common_include.h"
#include "myslam/feature.h"
#include "myslam/frame.h"

namespace myslam {

class Initializer {
public:
	Initializer(const Mat33& K, float sigma, int iterations);
	void initialize(const std::vector<cv::Point2f>& vKeys1, const std::vector<cv::Point2f>& vKeys2, cv::Mat& R, cv::Mat& t);

private:
	double mF;
	cv::Point2d mPp;

	cv::Mat mE, mMask;
	// int mMaxIterations;
	// float mSigma;
	// float mSigma2;
	

};

} //namespace myslam