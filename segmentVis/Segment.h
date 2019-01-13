#pragma once

#include <bits/stdc++.h>

#include "SegPoint.h"

class Segment
{
public:
	std::vector<SegPoint> polygon;
	std::string label;
	int pointCount;

	Segment()
	{
		label = "";
		pointCount = 0;
	}
};