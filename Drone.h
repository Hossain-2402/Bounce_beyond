#ifndef DRONE_H
#define DRONE_H
#include "Variables.hpp"
#include "Audio.hpp"


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

extern bool collision_handled ;
extern int heart_count;
int collision_cooldown = 0;
const int COLLISION_COOLDOWN_FRAMES = 20;


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

	if (collision_handled) return;
	if (collision_cooldown > 0) return;

	for (int i = 0; i < drone_number; i++){
		double distance = euclideanDistance((drones[i].drone_x + drone_width / 2)*vw, (drones[i].drone_y + drone_height / 2)*vh, ball_x, ball_y);
		
		/*double ball_radius = (15.0 * vh) / 2.0;           
		double drone_radius = (drone_width * vw) / 2.0;   
		double hit_range = ball_radius + drone_radius;
		*/

		if (distance <= 7 * vw){
			printf("Drone hit!\n");

			if (heart_count <= 0){
				show_blast = true;
				blast_timer = 0;
				PlayBlastSound();
			}
			else{
				heart_count -= 1;	
				PlayHeartLossSound();
			}
			collision_handled = true;
			collision_cooldown = COLLISION_COOLDOWN_FRAMES;
			break;
		}
		
	}
}

/*void drone_hit() {
if ( ball_x == drone_x && ball_y == drone_y ) {
printf("Drone hit!\n");
show_blast = true;
blast_timer = 0;
}*/

//Heart(Lifeline) 

int heart_image;
int heart_filled_image;
int heart_transparent_image;
const int heart_width = 4;
const int heart_height = 8;
//int heart_x = 320;
const int heart_y = 76 ;
const int heart_transparent_y = 87 ;
int heart_transparent_x = 90 ;
const int heart_filled_y = 87 ;
int heart_filled_x = 90 ;
//int heart_count = 0;

struct Heart{
	int heart_x;
	bool heart_miss;
};

struct TransparentHeart{
	
};

Heart hearts[3];
TransparentHeart transparentHearts[3];

void initiate_heart(){
	heart_count = 0;
	for (int i = 0; i < 3; i++){
		hearts[i].heart_x = (290 + i * 299);
		hearts[i].heart_miss = true;
	}
}

void show_heart(){
	for (int i = 0; i < 3; i++){
		if (hearts[i].heart_miss == true){
			iShowImage((hearts[i].heart_x)*vw, heart_y*vh, heart_width * vw, heart_height * vh, heart_image);
		}	
	}
}

void move_heart_x(int direction){
	for (int i = 0; i < 3; i++){
		hearts[i].heart_x += direction;
	}
}

void heart_hit(){
	for (int i = 0; i < 3; i++){
		double distance = euclideanDistance((hearts[i].heart_x + heart_width / 2)*vw, (heart_y + heart_height / 2)*vh, ball_x, ball_y);

		double ball_radius = (15.0 * vh) / 2.0;            
		double heart_radius = (heart_width * vw) / 2.0;    

		double hit_range = ball_radius + heart_radius;

		if (distance <= hit_range){
			printf("Heart hit");
			if (hearts[i].heart_miss == true){
				hearts[i].heart_miss = false;
				heart_count += 1;
				PlayHeartGainSound();
			}
		}
	}
}

void make_transparentHeart(){
	for (int i = 0; i < 3; i++){
		iShowImage((heart_transparent_x + i * 3)*vw, heart_transparent_y*vh, 3 * vw, 6 * vh, heart_transparent_image);
	}
}

void show_filledHeart(){
	if (heart_count>0){
		for (int i = 0; i < heart_count; i++){
			iShowImage((heart_filled_x + i * 3)*vw, heart_filled_y*vh, 3 * vw, 6 * vh, heart_filled_image);
		}
	}
}






#endif
