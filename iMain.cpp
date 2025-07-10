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

// Toggle buttons
int play_button_clicked = 0;
int levels_button_clicked = 0;
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
char image[100] = "ball_image_1.png";

void show_play_screen() {
	levels_button_clicked = 0;
	quit_button_clicked = 0;

	for (int i = 0; i < 5; i++) {
		iShowImage((x_of_play_screen_background + i * 100) * vw, 0, 100 * vw, 100 * vh, play_screen_background_image);
	}

	iSetColor(255, 255, 255);
	iText(0, 80 * vh, "Play Screen");

	iRotate((20 * vw + 12.5 * vh), 35.5 * vh, rotating_angle);
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
	iShowImage(0, 0, 100 * vw, 100 * vh, landing_page_background_image);

	iShowImage(30 * vw, 50 * vh, 40 * vw, 40 * vh, button_image);
	iSetColor(0, 0, 0);
	iText(47.5 * vw, 70 * vh, "Play", GLUT_BITMAP_8_BY_13);

	iShowImage(30 * vw, 30 * vh, 40 * vw, 40 * vh, button_image);
	iSetColor(0, 0, 0);
	iText(46 * vw, 50 * vh, "Levels");

	iShowImage(30 * vw, 10 * vh, 40 * vw, 40 * vh, button_image);
	iSetColor(0, 0, 0);
	iText(47.5 * vw, 30 * vh, "Quit");

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
	// Not used in this example
}

void iMouse(int button, int state, int mx, int my) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if ((mx >= 30 * vw && mx <= 70 * vw) && (my >= 65 * vh && my <= 76 * vh)) {
			play_button_clicked = 1;
		}
		if ((mx >= 30 * vw && mx <= 70 * vw) && (my >= 45 * vh && my <= 55 * vh)) {
			levels_button_clicked = 1;
		}
		if ((mx >= 30 * vw && mx <= 70 * vw) && (my >= 25 * vh && my <= 35 * vh)) {
			quit_button_clicked = 1;
		}
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		// Not used in this example
	}
}

void iKeyboard(unsigned char key) {
	if (key == 'd') {
		rotating_angle -= 15;
		current_rotation_angle = rotating_angle;

		if (x_of_play_screen_background <= -400) x_of_play_screen_background = 0;
		else x_of_play_screen_background -= 1;
	}
	if (key == 'a') {
		rotating_angle += 15;
		current_rotation_angle = rotating_angle;


		if (x_of_play_screen_background >= 0) x_of_play_screen_background = -100;
		else x_of_play_screen_background += 1;

	}
	if (key == ' ' && !is_animating) {
		is_animating = true;
		frame_counter = 0;
	}
	if (key == 'c') {
		strcpy_s(image,"ball_image_1.png");
	}
}

void iTimer() {
	if (is_animating) {
		frame_counter++;
		rotating_angle = 0;

		// Move up for the first 60 frames (1 second)
		if (frame_counter <= 60) {
			ball_y += (jumpHeight / 60); // Move up by approximately 1.67 pixels per frame
		}
		// Move down for the next 60 frames (1 second)
		else if (frame_counter > 60 && frame_counter <= 120) {
			ball_y -= (jumpHeight / 60); // Move down by approximately 1.67 pixels per frame
		}

		// Reset when animation completes (2 seconds = 120 frames)
		if (frame_counter >= 120) {
			ball_y = 23 * vh; // Reset to starting position
			is_animating = false;
			frame_counter = 0;
			rotating_angle = current_rotation_angle;
		}
	}
	iSetTimer(1000 / 60, iTimer); // 60 FPS
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
	ball_image = iLoadImage(image);

	iSetTimer(1000 / 60, iTimer); // Initialize timer for 60 FPS
	iStart();
	return 0;
}