#include "Image.h"

using namespace std;
using namespace cv;

#define cout(a) cout<<a<<endl

int main(int argc, char** argv) 
{
    ifstream file("segmentVis/imageList.txt");
    if(file.is_open())
    {
        while(!file.eof())
        {
            string fName;
            file >> fName;
            Image image;
            image.ReadJson(fName);
            //image.PrintSegments();
            image.ComputeBoundingBox();
            image.DrawSegments(fName);    
        }
    }
    else
    { 
        cout << "Unable to open file\n";
    }
	return 0;
}

