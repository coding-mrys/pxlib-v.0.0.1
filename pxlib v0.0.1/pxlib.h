#include "plane.h"
#include<string>

class renderer {
private:
	float rotation[3] = { 0,0,0 };
	float tol = 1;

public:

	void init(double x, double y, double z,double render_distance) {

		for (int i = 0; i < 1200; i++) {
			for (int j = 0; j < 700; j++) {
				for (int k = 0; k < screen.xvalues.size(); k++) {
					if (screen.xvalues[k] >= i-tol && screen.xvalues[k] <= i+tol
						&& screen.yvalues[k] >= j-tol && screen.yvalues[k] <= j+tol) {
						rect.build(screen.xvalues[k],screen.yvalues[k],10,10,0xffffff);
					}
					
				}
			}
		}

		screen.xvalues.erase(screen.xvalues.begin(), screen.xvalues.end());
		screen.yvalues.erase(screen.yvalues.begin(), screen.yvalues.end());
		screen.zvalues.erase(screen.zvalues.begin(), screen.zvalues.end());

	}
	void rotate(double x, double y, double z){
		rotation[0] = x; rotation[1] = y; rotation[2] = z;
	}
};
renderer cam;

namespace physics {

	class object {
	private:
		float power[2] = { 1,1 };
		float dif = 1;
		float position[2] = { 0,0 };
		float radient = 1;
		bool collision = false;
		float len = 1;
		float gravity = 0;

	public:

		bool build(double x, double y, double width, double height, u32 color, string type, double energy) {

			//calculate radient
			radient = ((y + power[1]) - y) / ((x + power[0]) - x);

			len = sqrt(
				(((x + power[0]) - x) * ((x + power[0]) - x)) +
				(((y + power[1]) - y) * ((y + power[1]) - y))
			);

			if (position[0] < (x + power[0])) {
				dif += energy;
			}
			else if (position[0] > (x + power[0])) {
				dif -= energy;
			}
			position[0] = x + dif;
			position[1] = y + gravity + dif * radient;

			if (position[0] > 0 && position[0] < 1200 && position[1] > 0 && position[1] < 600) {
				if (type == "circle") {
					circle.build(position[0], position[1] - width + 7, width, 1, color);
					circle.fill();

					for (int i = 0; i < screen.obj_x.size(); i++) {
						if (position[0] + width*2.3 > screen.obj_x[i] && position[0] < screen.obj_x[i] + width &&
							position[1] + width*2.3 > screen.obj_y[i] && position[1] < screen.obj_y[i] + width)
						{
							collision = true;
						}
						else { collision = false; }
					}
				}
				else if (type == "rectangle") {
					rect.build(position[0], position[1], width, height, color);

					for (int i = 0; i < screen.obj_x.size(); i++) {
						if (position[0] + width > screen.obj_x[i] && position[0] < screen.obj_x[i] + width &&
							position[1] + height > screen.obj_y[i] && position[1] < screen.obj_y[i] + height)
						{
							collision = true;
						}
						else { collision = false; }
					}
				}
			}

			//erase ball values
			screen.obj_x.erase(screen.obj_x.begin(), screen.obj_x.end());
			screen.obj_y.erase(screen.obj_y.begin(), screen.obj_y.end());

			//add values
			screen.obj_x.push_back(position[0]);
			screen.obj_y.push_back(position[1]);
			
			return collision;

		}

		void push(double value_X, double value_Y){
			power[0] = value_X;
			power[1] = value_Y;
		}

		void set_gravity(double g){
			gravity += 0.5*g;
		}
		
	};
}



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


