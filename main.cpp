#include<bits/stdc++.h>
#include <opencv2/opencv.hpp>

#include "Segment.h"

using namespace std;
using namespace cv;

typedef long long ll;

#define cout(a) cout<<a<<endl

void drawSegments(vector<Segment> segments, int imgHeight, int imgWidth)
{
    Mat image = Mat::zeros(imgWidth, imgHeight, CV_8UC3 );
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
            cout << segments[i].polygon[j].x << " " << segments[i].polygon[j].y << " ";
        }
        cout << endl;
    }
    cout << endl;
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
    printSegments(segments, imgHeight, imgWidth);
	return 0;
}

