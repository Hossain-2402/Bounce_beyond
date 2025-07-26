#include "iGraphics.h"
#include <cmath>
#include <cstring>


#include "Variables.hpp"
#include "Functions.hpp"

using namespace std;


void iDraw()
{
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

void iMouseMove(int mx, int my)
{

}

void iPassiveMouseMove(int mx, int my)
{
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

void iMouse(int button, int state, int mx, int my)
{
		//printf("%d -> %d\n", mx / vh, my / vh);
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

// Special Keys:
// GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6, GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12, 
// GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP, GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT

void fixedUpdate()
{
	if (show_blast) return; //stop everything if level failed


	if (isKeyPressed('a') || isSpecialKeyPressed(GLUT_KEY_LEFT))
	{
	
		move_ball_backwards();
	
	}

	if (isKeyPressed('d') || isSpecialKeyPressed(GLUT_KEY_RIGHT))
	{

		move_ball_forwards();
	
	}

	if (isKeyPressed(' ')) {

		jump_up();

	}

	if (!isKeyPressed(' ')) {

		jump_down();

	}
}


void iTimer(){

	if (show_blast){
		blast_timer++;
	}


	/*
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
	*/

}




int main()
{
	// Opening/Loading the audio files
	//mciSendString("open \"Audios//background.mp3\" alias bgsong", NULL, 0, NULL);
	//mciSendString("open \"Audios//gameover.mp3\" alias ggsong", NULL, 0, NULL);

	// Playing the background audio on repeat
	//mciSendString("play bgsong repeat", NULL, 0, NULL);

	// If the use of an audio is finished, close it to free memory
	// mciSendString("close bgsong", NULL, 0, NULL);
	// mciSendString("close ggsong", NULL, 0, NULL);




	iInitialize(100 * vw, 100 * vh, "Project Title");

	// Generating Images
	landing_page_background_image = iLoadImage("background_image.png");
	button_image = iLoadImage("button_image.png");
	play_screen_background_image = iLoadImage("image (1).png");
	ball_image = iLoadImage(ball_images[0]);
	obstacle_image_4 = iLoadImage("obstacle_image_4.png");
	spike_image = iLoadImage("spike_image_2.png");
	blast_image = iLoadImage("blast_image(1).png");
	for (int i = 0; i < 50; i++){
		coins[i].coin_image = iLoadImage("coin_image_1.png");
	}


	iSetTimer(1000 / 60, iTimer); // Initialize timer for 60 FPS
	// Keep oscillating the spike 
	iSetTimer(150, change_y_of_obstacle);
	iStart();
	return 0;
}
