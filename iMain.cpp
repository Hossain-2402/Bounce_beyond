#include "iGraphics.h"
#include<string.h>

using namespace std;

// vw & vh
int vh = 5;
int vw = 10;

// Images
	int landing_page_background_image;
	int button_image;
	int ball_image;
	int play_screen_background_image;
	char ball_images[3][100] = { "ball_image_10.png", "ball_image_2.png", "ball_image_8.png",};

// Toggle buttons
	int play_button_enlarge = 0;
	int levels_button_enlarge = 0;
	int credits_button_enlarge = 0;
	int quit_button_enlarge = 0;
	int play_button_clicked = 0;
	int levels_button_clicked = 0;
	int credits_button_clicked = 0;
	int quit_button_clicked = 0;

// Positions
	double x_of_play_screen_background = 0;
	double ball_y = 23 * vh;
	double rotating_angle = 0;

// Variables
bool is_animating = false;
int frame_counter;
const double jumpHeight = 100; // Target jump height in pixels
double current_rotation_angle;
int ball_img_index = 0;

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

void show_play_screen() {
	levels_button_clicked = 0;
	quit_button_clicked = 0;

	for (int i = 0; i < 5; i++) {
		iShowImage((x_of_play_screen_background + i * 100) * vw, 0, 100 * vw, 100 * vh, play_screen_background_image);
	}

	Rotate((20 * vw + 12.5 * vh), 35.5 * vh, rotating_angle);
	iShowImage(20 * vw, ball_y, 25 * vh, 25 * vh, ball_image);
	iUnRotate();
}

void show_levels_screen() {
	play_button_clicked = 0;
	quit_button_clicked = 0;

	iSetColor(255, 255, 255);
	iFilledRectangle(0, 0, 100 * vw, 100 * vh);

	iSetColor(0, 0, 0);
	iText(0, 80 * vh, "Levels Screen");
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
	if (play_button_clicked == 1) show_play_screen();
	if (levels_button_clicked == 1) show_levels_screen();
	if (quit_button_clicked == 1) exit(0);
}

void iDraw() {
	iClear();
	create_landing_page();
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
	printf("%d, %d \n", mx/vw,my/vh);
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
	if (key == 'd') {
		if(!is_animating) rotating_angle -= 15;

		if (x_of_play_screen_background <= -400) x_of_play_screen_background = 0;
		else x_of_play_screen_background -= 1;
	}
	if (key == 'a') {
		if (!is_animating) rotating_angle += 15;


		if (x_of_play_screen_background >= 0) x_of_play_screen_background = -100;
		else x_of_play_screen_background += 1;

	}
	if (key == ' ' && !is_animating) {
		is_animating = true;
		frame_counter = 0;
	}
	if (key == 'c') {

		if (ball_img_index >= 2) ball_img_index = 0;
		else ball_img_index++;
		ball_image = iLoadImage(ball_images[ball_img_index]);

	}
}

void iTimer() {
	if (is_animating) {
		frame_counter++;
		rotating_angle = 0; 

		
		if (frame_counter <= 60) {
			ball_y += ((50 * vh) / 60);
		}
		
		else if (frame_counter > 60 && frame_counter <= 120) {
			if (ball_y <= 23 * vh) ball_y = 23 * vh;
			else ball_y -= ((50 * vh) / 60);

		}

		
		if (frame_counter >= 120) {
			ball_y = 23 * vh;
			is_animating = false;
			frame_counter = 0;
		}
	}
	iSetTimer(50000 / 60, iTimer);
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
	play_screen_background_image = iLoadImage("image (2).png");
	ball_image = iLoadImage(ball_images[0]);

	iSetTimer(1000 / 60, iTimer); // Initialize timer for 60 FPS
	iStart();
	return 0;
}

/*
	Questions:
		- how to generate "Heat box" ( "iTimer()" > "rotate_angle = 0" )
		- Code run korle "ERROR line" dekhay keno ?
		- "Space" press korle "d" bondho hoye jay keno?

*/
