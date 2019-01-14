#include <bits/stdc++.h>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "Segment.h"
#include "Label.h"

using namespace std;
using namespace cv;

typedef long long ll;

#define cout(a) cout<<a<<endl

void drawSegments(vector<Segment> segments, int imgHeight, int imgWidth)
{
    Mat image = Mat::zeros(imgHeight, imgWidth, CV_8UC3 );

    for(size_t i = 0; i < segments.size(); i++)
    {
        Point poly[1][(int)segments[i].pointCount / 2];
        for(size_t j = 0; j < segments[i].pointCount / 2; j++)
        {
            poly[0][j] = Point(segments[i].polygon[j].x, segments[i].polygon[j].y);
        }
        
        const Point* ppt[1] = { poly[0] };
        int npt[] = { (int)segments[i].pointCount / 2 };
     
        Colour col = labels[segments[i].label];
        fillPoly(image, ppt, npt, 1, Scalar(col.r, col.g, col.b), 8 );
        rectangle(image, Point(segments[i].box.x1, segments[i].box.y1), Point(segments[i].box.x2, segments[i].box.y2), Scalar(255, 255, 255));
    }
    imshow("Image", image);
    waitKey(0);
}

void printSegments(vector<Segment> segments, int imgHeight, int imgWidth)
{
    cout(imgHeight);
    cout(imgWidth);
    for(size_t i = 0; i < segments.size(); i++)
    {
        cout << segments[i].label << " " << segments[i].pointCount << endl;
        for(size_t j = 0; j < segments[i].polygon.size(); j++)
        {
            cout << segments[i].polygon[j].x << " " << segments[i].polygon[j].y << endl;
        }
        cout << endl;
    }
    cout << endl;
}

void computeBoundingBox(vector<Segment> &segments)
{
    for(size_t i = 0; i < segments.size(); i++)
    {
        segments[i].ComputeBoundingBox();
    }
}

void readJson(vector<Segment> &segments, int &imgHeight, int &imgWidth)
{
    string line;
    ifstream file ("005506_gtFine_polygons.json");
    if (file.is_open())
    {
        while (!file.eof())
        {
            getline (file, line);
            string word = "imgHeight\": ";
            size_t found = line.find(word);
            if (found != string::npos) 
            {
                int pos = found + word.length();
                imgHeight =stoi(line.substr(pos, line.length() - pos - 1)); 
                break;
            }
        }

        while (!file.eof())
        {
            getline (file, line);
            string word = "imgWidth\": ";
            size_t found = line.find(word);
            if (found != string::npos) 
            {
                int pos = found + word.length();
                imgWidth = stoi(line.substr(pos, line.length() - pos - 1)); 
                break;
            }
        }
        while (!file.eof())
        {
            Segment newSegment;
            getline (file, line);
            string word = "label\": \"";
            size_t found = line.find(word);
            if (found != string::npos) 
            {
                int pos = found + word.length();
                newSegment.label = line.substr(pos, line.length() - pos - 2);    
                while (!file.eof())
                {
                    string start="    [";
                    word = "verified";

                    getline (file, line);

                    if(line.find(start) != string::npos)
                    {
                        SegPoint point;

                        getline (file, line);
                        line.erase (std::remove (line.begin(), line.end(), ' '), line.end());
                        point.x = atof(line.substr(0, line.length() - 1).c_str());   

                        getline (file, line);
                        line.erase (std::remove (line.begin(), line.end(), ' '), line.end());
                        point.y = atof(line.substr(0, line.length()).c_str());     

                        newSegment.polygon.push_back(point);

                        newSegment.pointCount += 2;
                    }

                    if (line.find(word) != string::npos) 
                    {
                        break;
                    }
                }
                segments.push_back(newSegment);
            }
        }
    }
    else
    { 
        cout << "Unable to open file\n";
    }

    file.close();
}

int main(int argc, char** argv) 
{
    vector<Segment> segments;
    int imgHeight, imgWidth;
    readJson(segments, imgHeight, imgWidth);
    //printSegments(segments, imgHeight, imgWidth);
    computeBoundingBox(segments);
    drawSegments(segments, imgHeight, imgWidth);
	return 0;
}

