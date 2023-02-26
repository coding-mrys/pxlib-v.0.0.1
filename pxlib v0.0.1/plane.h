#include<vector>
#include"tools.h"
Line line;

class plane {

private:
	double position[3] = { 0,0,0 };
	double rotation[3] = { 0,0,0 };

	double rotatedX[3] = { 0,0,0 };
	double rotatedY[3] = { 0,0,0 };
	double rotatedZ[3] = { 0,0,0 };

	double p = 1;
	double pMatrix[3][3];


	double pi = 3.1415926535;

	double nodes[4][3] = {
		{-1,-1,1},
		{1,-1,1},
		{1,1,1},
		{-1,1,1}
	};

	double thick = 1;

public:

	void build(double x, double y, double z, double width, double height, u32 color) {

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

		for (int i = 0; i < 4; i++) {

			for (int j = 0; j < 3; j++) {
				rotatedX[j] = nodes[i][0] * xrot[j][0] + nodes[i][1] * xrot[j][1] + nodes[i][2] * xrot[j][2];
			}

			for (int j = 0; j < 3; j++) {
				rotatedY[j] = rotatedX[0] * yrot[j][0] + rotatedX[1] * yrot[j][1] + rotatedX[2] * yrot[j][2];
			}

			for (int j = 0; j < 3; j++) {
				rotatedZ[j] = rotatedY[0] * zrot[j][0] + rotatedY[1] * zrot[j][1] + rotatedY[2] * zrot[j][2];
			}

			p = 2 / (2.5 - rotatedZ[2]);

			float pMatrix[3][3] = {
				{p,0,0},
				{0,p,0},
				{0,0,0}  
			};

			for (int j = 0; j <= 3; j++) {
				rotatedZ[j] = rotatedZ[0] *pMatrix[j][0] + rotatedZ[1] * pMatrix[j][1] + rotatedZ[2] * pMatrix[j][2];
			}

			position[0] = x + rotatedZ[0] * width;
			position[1] = y + rotatedZ[1] * height;
			position[2] = z + rotatedZ[2];
			
			//to screen
			screen.xvalues.push_back(position[0]);
			screen.yvalues.push_back(position[1]);
			screen.zvalues.push_back(position[2]);


		}

	}

	void rotate(double x, double y, double z) {
		rotation[0] = x; rotation[1] = y; rotation[2] = z;
	}
};

