# 3D-Synthesis
## Requirements
- [OpenCV](https://www.learnopencv.com/install-opencv3-on-ubuntu/)
- C++ 11

## Segment Visualization
Code in [segmentVis](segmentVis) contains a JSON file parser and OpenCV visualization of segment polygons from the [Indian Driving Dataset (IDD)](https://idd.insaan.iiit.ac.in/). Visualization of bounding boxes is additionally supported. Download this repository and the datset and extract the data folders. The file structure should look as shown below.

```
root
|
└─ anue
|   └─ gtFine
|   └─ leftImg8bit
|   ...
|
└─ parser
    └─ segmentVis
    | Makefile
    | README
```
 To compile, within parser/, run
```
make segvis
```
