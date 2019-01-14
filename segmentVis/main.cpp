#include "Image.h"

using namespace std;
using namespace cv;

#define cout(a) cout<<a<<endl

int main(int argc, char** argv) 
{
    Image image;
    image.ReadJson("005506_gtFine_polygons.json");
    //image.PrintSegments();
    image.ComputeBoundingBox();
    image.DrawSegments("005506_gtFine_polygons.json");
	return 0;
}

