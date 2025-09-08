#ifndef DRONE_H
#define DRONE_H
#include "Variables.h"
#include "Functions.h"

double euclideanDistance(double x1, double y1, double x2, double y2){
	double distance = (x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2);
	return sqrt(distance);
}

int drone_image;
const int drone_width = 10;
const int drone_height = 12;
const double drone_speed = 0.5;
const int drone_max_number = 3;
int drone_X = OBSTACLE_X + 55;
double drone_Y = 24;
int drone_number;

struct Drone{
	//int drone_number = 0;
	int drone_x;
	double drone_y;
	int drone_direction;
};

Drone drones[3];

void spawn_drone(){

	drone_number = rand() % 3 + 1;

	for (int i = 0; i < drone_number; i++){
		drones[i].drone_x = 100 + i*(drone_width + 1);  // Be careful drone_x and drone_y are in vw and vh unit
		drones[i].drone_y = rand() % 75 + 24;
		drones[i].drone_direction = (rand() % 2) ? 1 : -1;
	}
}

void initiate_drone(){

	drone_number = rand() % 3 + 1;

	for (int i = 0; i < drone_number; i++){
		drones[i].drone_x = drone_X + i*(drone_width + 1);  // Be careful drone_x and drone_y are in vw and vh unit
		drones[i].drone_y = rand() % 75 + 24;
		drones[i].drone_direction = (rand() % 2) ? 1 : -1;
	}
}

void show_drone(){
	for (int i = 0; i < drone_number; i++){
		iShowImage(drones[i].drone_x*vw, drones[i].drone_y*vh, drone_width*vw, drone_height*vh, drone_image);
	}
}

/*void make_drone(){
iShowImage(drone_x*vw , drone_y*vh, drone_width*vw, drone_height*vh, drone_image);
}*/

void move_drone_x(int direction){
	for (int i = 0; i < drone_number; i++){
		drones[i].drone_x += direction;
	}
	if (drones[0].drone_x <= -30){
		//drones[i].drone_x = 120;
		spawn_drone();
	}
	else if (drones[0].drone_x >= 225){
		//drones[i].drone_x = -5;
		spawn_drone();
	}
}

void move_drone_y(){
	for (int i = 0; i < drone_number; i++){
		drones[i].drone_y += drones[i].drone_direction * drone_speed;

		if (drones[i].drone_y <= 24){
			drones[i].drone_direction = 1;;
		}
		if (drones[i].drone_y >= 90){
			drones[i].drone_direction = -1;
		}
	}
}



void drone_hit(){
	for (int i = 0; i < drone_number; i++){
		double distance = euclideanDistance((drones[i].drone_x + drone_width / 2)*vw, (drones[i].drone_y + drone_height / 2)*vh, ball_x, ball_y);
		if (distance <= 7 * vw){
			printf("Drone hit!\n");
			show_blast = true;
			blast_timer = 0;
		}
	}
}

/*void drone_hit() {
if ( ball_x == drone_x && ball_y == drone_y ) {
printf("Drone hit!\n");
show_blast = true;
blast_timer = 0;
}*/





#endif