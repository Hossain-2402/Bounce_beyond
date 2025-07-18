#include "iGraphics.h"
#include <cmath>
#include <cstring>
using namespace std;

// vw & vh
int vh = 5;
int vw = 10;

// Images
	int landing_page_background_image;
	int button_image;
	int ball_image;
	int play_screen_background_image;
	char ball_images[3][100] = { 
		"ball_image_10.png", 
		"ball_image_2.png", 
		"ball_image_8.png",
	};
	int obstacle_image_4;
	int spike_image;

// Toggle buttons
	int play_button_enlarge = 0;
	int levels_button_enlarge = 0;
	int credits_button_enlarge = 0;
	int quit_button_enlarge = 0;

	int play_button_clicked = 0;
	int levels_button_clicked = 0;
	int credits_button_clicked = 0;
	int quit_button_clicked = 0;

	int level_failed = 0;

// Positions
	double x_of_play_screen_background = 0;
	double	ball_x = 20 * vw;	//start X
	double ball_y = 23 * vh;	//start Y
	double rotating_angle = 0;
	double OBSTACLE_X = 100;
	double OBSTACLE_Y = 50;
	double SPIKE_X = 100;


//Movement Flags
	bool isDPressed = false ;
	bool isAPressed = false ;
	bool isJumping = false;

//Jump Animation
	bool is_animating = false;
	int frame_counter = 0;
	const double jumpHeight = 100; // Target jump height in pixels
	double current_rotation_angle;
	int ball_img_index = 0;

// --- New physics state ---
	double ball_vx = 0.0;
	double ball_vy = 0.0;

// --- Physics constants ---
	const double GRAVITY = -0.5;         // pixels/tick²
	const double JUMP_SPEED = 16.0;         // initial jump velocity
	//const double MOVE_SPEED = 2.0;          // horizontal speed
	double GROUND_Y = 23 * vh;      // your floor level [GROUND_Y cannot be const]


void enlarge_play()
{
	iShowImage(25 * vw, 60 * vh, 50 * vw, 50 * vh, button_image);
	iSetColor(0, 255, 0);
	iText(46.5 * vw, 85 * vh, "PLAY", GLUT_BITMAP_HELVETICA_18);
}
void enlarge_levels()
{
	iShowImage(25 * vw, 40 * vh, 50 * vw, 50 * vh, button_image);
	iSetColor(125, 0, 255);
	iText(45.5 * vw, 65 * vh, "LEVELS", GLUT_BITMAP_HELVETICA_18);
}
void enlarge_credits()
{
	iShowImage(25 * vw, 20 * vh, 50 * vw, 50 * vh, button_image);
	iSetColor(125, 0, 255);
	iText(45.5 * vw, 45 * vh, "CREDITS", GLUT_BITMAP_HELVETICA_18);
}
void enlarge_quit()
{
	iShowImage(25 * vw, 0 * vh, 50 * vw, 50 * vh, button_image);
	iSetColor(255, 0, 0);
	iText(47.5 * vw, 25 * vh, "QUIT", GLUT_BITMAP_HELVETICA_18);
}



void make_obstacles(){
	iShowImage(OBSTACLE_X*vw, OBSTACLE_Y * vh, 20 * vw, 20 * vh, obstacle_image_4);
	iShowImage(SPIKE_X*vw, 24 * vh, 20 * vw, 15 * vh, spike_image);
}
void change_y_of_obstacle(){
	OBSTACLE_Y = rand() % 21 + 40;
}
void move_obstacle(int moving_direction) { // moving_direction = 1 (moving RIGHT) moving_direction = -1 (moving LEFT)
	if (OBSTACLE_X <= -20) {
		OBSTACLE_X = 110; 
		change_y_of_obstacle();
	}
	else if (OBSTACLE_X >= 110) {
		OBSTACLE_X = -20; 
		change_y_of_obstacle();
	}
	OBSTACLE_X += (moving_direction)* 1;

 
}
void move_spikes(int moving_direction) { // moving_direction = 1 (moving RIGHT) moving_direction = -1 (moving LEFT)
	if (SPIKE_X <= -20) {
		SPIKE_X = 110;
	}
	else if (SPIKE_X >= 110) {
		SPIKE_X = -20;
	}
	SPIKE_X += (moving_direction)* 1;


}
void jump_on_obstacle(){
	if (OBSTACLE_X >= 5 && OBSTACLE_X <= 25) GROUND_Y = (OBSTACLE_Y+8) * vh;
	else GROUND_Y = 23 * vh;

}
void show_level_failed_screen(){
	iShowImage(0,0,100*vw,100*vh,play_screen_background_image);
	iSetColor(255, 0, 0);
	iText(42.5 * vw, 55 * vh, "LEVEL FAILED", GLUT_BITMAP_HELVETICA_18);

}
void ball_hit_spike(){
	if ((SPIKE_X >= 5 && SPIKE_X <= 25) && ball_y == 23 * vh) {
		level_failed = 1;
	}
}





void create_landing_page() {
	iShowImage(0, 0, 100 * vw, 100 * vh, play_screen_background_image);

	iShowImage(30 * vw, 65 * vh, 40 * vw, 40 * vh, button_image);
	iSetColor(0, 0, 0);
	iText(47 * vw, 85 * vh, "PLAY", GLUT_BITMAP_9_BY_15);


	iShowImage(30 * vw, 45 * vh, 40 * vw, 40 * vh, button_image);
	iSetColor(0, 0, 0);
	iText(46 * vw, 65 * vh, "LEVELS");

	iShowImage(30 * vw, 25 * vh, 40 * vw, 40 * vh, button_image);
	iSetColor(0, 0, 0);
	iText(46 * vw, 45 * vh, "CREDITS");

	iShowImage(30 * vw, 5 * vh, 40 * vw, 40 * vh, button_image);
	iSetColor(0, 0, 0);
	iText(47.5 * vw, 25 * vh, "QUIT");

	if (play_button_enlarge == 1) enlarge_play();
	if (levels_button_enlarge == 1) enlarge_levels();
	if (credits_button_enlarge == 1) enlarge_credits();
	if (quit_button_enlarge == 1) enlarge_quit();

	if (quit_button_clicked == 1) exit(0);
}

void show_play_screen() {
	levels_button_clicked = 0;
	credits_button_clicked = 0;
	quit_button_clicked = 0;

	//background tiles
	for (int i = 0; i < 5; i++) {
		iShowImage((int)(x_of_play_screen_background + i * 100) * vw, 0, 100 * vw, 100 * vh, play_screen_background_image);
	}

	// Eda obstacle
	make_obstacles();



	//	iShowImage(50*vw, 50 * vh, 20 * vw, 20 * vh, obstacle_image_4);

	//draw and rotate ball sprite
	iRotate((int)(ball_x + 12.5 * vh), (int)(ball_y + 12.5*vh), rotating_angle);
	iShowImage((int)ball_x, (int)ball_y, 25 * vh, 25 * vh, ball_image);
	iUnRotate();


	if (level_failed) show_level_failed_screen();
}

void show_levels_screen() {
	play_button_clicked = 0;
	quit_button_clicked = 0;

	iSetColor(255, 255, 255);
	iFilledRectangle(0, 0, 100 * vw, 100 * vh);

	iSetColor(0, 0, 0);
	iText(0, 80 * vh, "Levels Screen", GLUT_BITMAP_HELVETICA_18);
}















void iDraw() {
	iClear();

	if (play_button_clicked) {
		show_play_screen();        // <-- now draws & rotates your bouncing ball
	}
	else if (levels_button_clicked) {
		show_levels_screen();
	}
	else {
		create_landing_page();
	}
}

void iMouseMove(int mx, int my) {
	// Not used in this example
}

void iPassiveMouseMove(int mx, int my) {
	if ((mx >= 30 * vw && mx <= 70 * vw) && (my >= 80 * vh && my <= 90 * vh)) {
		play_button_enlarge = 1;
	}
	else{
		play_button_enlarge = 0;
	}


	if ((mx >= 30 * vw && mx <= 70 * vw) && (my >= 60 * vh && my <= 70 * vh)) {
		levels_button_enlarge = 1;
	}
	else{
		levels_button_enlarge = 0;
	}


	if ((mx >= 30 * vw && mx <= 70 * vw) && (my >= 40 * vh && my <= 50 * vh)) {
		credits_button_enlarge = 1;
	}
	else{
		credits_button_enlarge = 0;
	}


	if ((mx >= 30 * vw && mx <= 70 * vw) && (my >= 20 * vh && my <= 30 * vh)) {
		quit_button_enlarge = 1;
	}
	else{
		quit_button_enlarge = 0;
	}
}

void iMouse(int button, int state, int mx, int my) {

	//printf("%d, %d \n", mx/vw,my/vh);
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if ((mx >= 30 * vw && mx <= 70 * vw) && (my >= 80 * vh && my <= 90 * vh)) {
			play_button_clicked = 1;
		}
		if ((mx >= 30 * vw && mx <= 70 * vw) && (my >= 60 * vh && my <= 70 * vh)) {
			levels_button_clicked = 1;
		}

		if ((mx >= 30 * vw && mx <= 70 * vw) && (my >= 40 * vh && my <= 50 * vh)) {
			credits_button_clicked = 1;
		}
		if ((mx >= 30 * vw && mx <= 70 * vw) && (my >= 20 * vh && my <= 30 * vh)) {
			quit_button_clicked = 1;
		}
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		// Not used in this example
	}
}

void iKeyboard(unsigned char key) {
	if (key == 'd') isDPressed = true;
	else isDPressed = false;
	
	if (key == 'a') isAPressed = true;
	else isAPressed = false;
	
	if (key == ' ') {
        // only allow a new jump if you’re on (or very near) the ground
        if (!isJumping) {
			isJumping = true;
            ball_vy = JUMP_SPEED;
        }
    }
	if (key == 'c') {
		ball_img_index = (ball_img_index + 1) % 3;
		ball_image = iLoadImage(ball_images[ball_img_index]);
	}
}




void iTimer() {


	//Horizontal movement
	if (isDPressed) {
		rotating_angle -= 15;

		x_of_play_screen_background -= 1;
		if (x_of_play_screen_background <= -400) x_of_play_screen_background = 0;

		move_obstacle(-1); // -1 means moving LEFT
		move_spikes(-1); // -1 means moving LEFT
		ball_hit_spike();

	}

	if (isAPressed) {
		rotating_angle += 15;

		x_of_play_screen_background += 1;
		if (x_of_play_screen_background >= 0) x_of_play_screen_background = -100;
		
		move_obstacle(1); // 1 means moving RIGHT
		move_spikes(1); // 1 means moving RIGHT
		ball_hit_spike();
	}

	//Jump and gravity
	if (isJumping){

		ball_vy += GRAVITY;
		ball_y += ball_vy;
		if (ball_y < GROUND_Y) {
			ball_y = GROUND_Y;
			isJumping = false;
			ball_vy = 0;
		}

	}
	jump_on_obstacle();
	
}

void iSpecialKeyboard(unsigned char key) {
	if (key == GLUT_KEY_RIGHT) {
		// Not used in this example
	}
	if (key == GLUT_KEY_LEFT) {
		// Not used in this example
	}
	if (key == GLUT_KEY_HOME) {
		// Not used in this example
	}
}

int main() {
	iInitialize(100 * vw, 100 * vh, "Project Title");

	landing_page_background_image = iLoadImage("background_image.png");
	button_image = iLoadImage("button_image.png");
	play_screen_background_image = iLoadImage("image (1).png");
	ball_image = iLoadImage(ball_images[0]);
	obstacle_image_4 = iLoadImage("obstacle_image_4.png");
	spike_image = iLoadImage("spike_image_2.png");


	iSetTimer(1000 / 60, iTimer); // Initialize timer for 60 FPS
	iStart();
	return 0;
}
