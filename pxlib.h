#include "plane.h"
#include<string>

class renderer {
private:
	float rotation[3] = { 0,0,0 };
	float position[3] = { 0,0,0 };

	float objPos[3] = {0,0,0};

	float rotatedX[3] = { 0,0,0 };
	float rotatedY[3] = { 0,0,0 };
	float rotatedZ[3] = { 0,0,0 };

	int ac = 10;
	float vLen;

public:

	void init(float x, float y, float z, float width, float height, float depth) {
		
		double xrot[3][3] = {
			{1,0,0},
			{0,cos(rotation[0] * pi / 180),-sin(rotation[0] * pi / 180)},
			{0,sin(rotation[0] * pi / 180),cos(rotation[0] * pi / 180)}
		};
		double yrot[3][3] = {
			{cos(rotation[1] * pi / 180),0,sin(rotation[1] * pi / 180)},
			{0,1,0},
			{-sin(rotation[1] * pi / 180),0,cos(rotation[1] * pi / 180)}
		};
		double zrot[3][3] = {
			{cos(rotation[2] * pi / 180),-sin(rotation[2] * pi / 180),0},
			{sin(rotation[2] * pi / 180),cos(rotation[2] * pi / 180),0},
			{0,0,1}
		};

		for (int j = 0; j <= 3; j++) {
			rotatedX[j] = 1 * xrot[j][0] + 1 * xrot[j][1] + 1 * xrot[j][2];
		}

		for (int j = 0; j <= 3; j++) {
			rotatedY[j] = rotatedX[0] * yrot[j][0] + rotatedX[1] * yrot[j][1] + rotatedX[2] * yrot[j][2];
		}

		for (int j = 0; j <= 3; j++) {
			rotatedZ[j] = rotatedY[0] * zrot[j][0] + rotatedY[1] * zrot[j][1] + rotatedY[2] * zrot[j][2];
		}

		position[0] = x + rotatedZ[0] * width;
		position[1] = y + rotatedZ[1] * height;
		position[2] = z + rotatedZ[2] * depth;

		for (int i = 0; i < screen.xvalues.size(); i++) {
			if (screen.xvalues[i] > x && screen.xvalues[i] < x+width && screen.yvalues[i] > y && screen.yvalues[i] < y+height) {

				//draw lines
				if (i < screen.xvalues.size()-1) {
					line.build(screen.xvalues[i], screen.yvalues[i], screen.xvalues[i + 1], screen.yvalues[i + 1], 2, 0xff0ff);
				}
				line.build(screen.xvalues[3], screen.yvalues[3], screen.xvalues[0], screen.yvalues[0], 2, 0xff0ff);
				
				circle.build(screen.xvalues[i], screen.yvalues[i], 5, 1, 0xff3333); //draw nodes
				circle.fill();
			}
		}
		screen.xvalues.erase(screen.xvalues.begin(), screen.xvalues.end());
		screen.yvalues.erase(screen.yvalues.begin(), screen.yvalues.end());
		screen.zvalues.erase(screen.zvalues.begin(), screen.zvalues.end());
	}
	void rotate(float x, float y, float z){
		rotation[0] = x; rotation[1] = y; rotation[2] = z;
	}
};
renderer cam;


/*
____________  ____      ____   ___           ___     ___ 
|###########| \###\    /###/  |###|         |###|   |###|
|###|   |###|  \###\  /###/   |###|         |###|   |###|
|###|___|###|   \###\/###/    |###|         |###|   |###|
|##########/     \######/     |###|         |###|   |###|_______
|###|            /######\     |###|         |###|   |###########|
|###|           /###/\###\    |###|_____    |###|   |###|   |###|
|###|          /###/  \###\   |#########\   |###|   |###|___|###|
|###|         /###/    \###\   \#########|  |###|   |###########/

v 0.1 - mrys.exe

*/


