#include "VPDetection.h"

using namespace std;
using namespace cv;



void drawClusters( cv::Mat &img, std::vector<std::vector<double> > &lines, std::vector<std::vector<int> > &clusters )
{
	int cols = img.cols;
	int rows = img.rows;

	//draw lines
	std::vector<cv::Scalar> lineColors( 3 );
	lineColors[0] = cv::Scalar( 0, 0, 255 );
	lineColors[1] = cv::Scalar( 0, 255, 0 );
	lineColors[2] = cv::Scalar( 255, 0, 0 );

	for ( int i=0; i<lines.size(); ++i )
	{
		int idx = i;
		cv::Point pt_s = cv::Point( lines[idx][0], lines[idx][1]);
		cv::Point pt_e = cv::Point( lines[idx][2], lines[idx][3]);
		cv::Point pt_m = ( pt_s + pt_e ) * 0.5;

		cv::line( img, pt_s, pt_e, cv::Scalar(0,0,0), 2, CV_AA );
	}

	for ( int i = 0; i < clusters.size(); ++i )
	{
		for ( int j = 0; j < clusters[i].size(); ++j )
		{
			int idx = clusters[i][j];

			cv::Point pt_s = cv::Point( lines[idx][0], lines[idx][1] );
			cv::Point pt_e = cv::Point( lines[idx][2], lines[idx][3] );
			cv::Point pt_m = ( pt_s + pt_e ) * 0.5;

			cv::line( img, pt_s, pt_e, lineColors[i], 2, CV_AA );
		}
	}
}

void main()
{	
	std::vector<std::vector<double> > lines;  // set your line segments here

	// Camera internal parameters
	cv::Point2d pp( 307, 251 );        // Principle point (in pixel)
	double f = 6.053 / 0.009;          // Focal length (in pixel)

	// Vanishing point detection
	std::vector<cv::Point3d> vps;              // Detected vanishing points (in pixel)
	std::vector<std::vector<int> > clusters;   // Line segment clustering results of each vanishing point
	VPDetection detector;
	detector.run( lines, pp, f, vps, clusters );
}
