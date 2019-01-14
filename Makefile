segvis:
	g++ -std=c++11 segmentVis/main.cpp segmentVis/Segment.cpp segmentVis/Image.cpp `pkg-config --libs --cflags opencv` -o p