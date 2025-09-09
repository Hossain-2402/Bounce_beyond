##include "iGraphics.h"
#include <cmath>
#include <cstring>


#include "Variables.h"
#include "Functions.h"
#include "Drone.h"

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
	mouseX = mx;
	mouseY = my;
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

	mouseX = mx;
	mouseY = my;
}

void iMouse(int button, int state, int mx, int my)
{
	printf("%d -> %d\n", mx / vh, my / vh);
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		if ((mx >= 30 * vw && mx <= 70 * vw) && (my >= 80 * vh && my <= 90 * vh)) {
			play_button_clicked = 1;
			levels_button_clicked = 0;
			credits_button_clicked = 0;
			quit_button_clicked = 0;
		}
		if ((mx >= 2.5 * vh && mx <= 12.5 * vh) && (my >= 87.5 * vh && my <= 97.5 * vh)) { // back button

			if (play_button_clicked) go_back_from_level_1();
			else if (levels_button_clicked) go_back_from_level_2();
			else{}

		}
		if ((mx >= 46.3 * vw && mx <= 51.3 * vw) && (my >= 35 * vh && my <= 45 * vh)){
			play_button_clicked = 0;
			reset_gamestate();

			//reset variables
			score = 0;
			level_failed = 0;
			show_blast = false;
			blast_timer = 0;

			//reset ball position
			ball_x = 20 * vw;
			ball_y = 23 * vh;

			//reset movement and physics
			ball_vx = 0;
			ball_vy = 0;
			rotating_angle = 0;
			GROUND_Y = 28 * vh;

			//reset background scroll
			x_of_play_screen_background = 0;
			x_of_coin = 5;

			//reset obstacle & spike positions
			OBSTACLE_X = 100;
			OBSTACLE_Y = 50;
			SPIKE_X = 90;

			for (int i = 0; i < 50; i++){
				coins[i].collected = false;
			}
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

	if (projectileMode && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		isDragging = true;
		drag_start_x = mx;
		drag_start_y = my;
	}
	if (projectileMode && button == GLUT_LEFT_BUTTON && state == GLUT_UP && isDragging){
		isDragging = false;
		launched = true;

		drag_end_x = mx;
		drag_end_y = my;

		//velocity calculator
		double dx = drag_end_x - drag_start_x;
		double dy = drag_end_y - drag_start_y;

		double power = 0.2;
		projectile_vx = -dx * power;
		projectile_vy = -dy * power;


		projectileMode = false;
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

	if (ball_y == -50 * vh) return;
	if (launched) return;
	//if (is_floating_animation) return;

	ball_hit_spike();
	drone_hit();

	if (show_blast) { return; } //stop everything if level failed

	if (isKeyPressed('a') || isSpecialKeyPressed(GLUT_KEY_LEFT))
	{

		if (play_button_clicked) move_ball_backwards();
		if (levels_button_clicked) {
			move_screen_backwards();
			move_ball_backwards_in_level_2();


			if (left_of_inclined_ramp >= 4 && left_of_inclined_ramp <= 23) camera_y += 3;
			else camera_y = camera_y;
		}

	}

	if (isKeyPressed('d') || isSpecialKeyPressed(GLUT_KEY_RIGHT))
	{

		if (play_button_clicked) move_ball_forwards();
		if (levels_button_clicked){
			move_screen_forwards();
			move_ball_forwards_in_level_2();
			if (left_of_inclined_ramp >= 7 && left_of_inclined_ramp <= 25) camera_y -= 3;
			else camera_y = camera_y;
		}
	}

	if (isKeyPressed(' ')) {

		jump_up();

	}

	if (!isKeyPressed(' ')) {

		jump_down();

	}

	if (isKeyPressed('p')){
		isDragging = false;
		launched = false;

		projectileMode = true;

		//stop where you are
		ball_vx = 0;
		ball_vy = 0;
	}


}

void iTimer(){

	if (launched) {
		// Gravity effect
		projectile_vy += GRAVITY;
		ball_y += projectile_vy;

		// Adjust world to keep ball locked
		adjustWorldDuringProjectile();

		// Stop on ground
		if (ball_y <= GROUND_Y) {
			ball_y = GROUND_Y;
			launched = false;
			projectile_vx = 0;
			projectile_vy = 0;

		}
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



	srand((unsigned)time(NULL));
	iInitialize(100 * vw, 100 * vh, "Project Title");

	// Generating Images
	landing_page_background_image = iLoadImage("background_image.png");
	button_image = iLoadImage("button_image.png");
	back_image = iLoadImage("back_button_2.png");
	play_screen_background_image = iLoadImage("image (1).png");
	ball_image = iLoadImage(ball_images[0]);
	obstacle_image_4 = iLoadImage("obstacle_image_4.png");
	spike_image = iLoadImage("spike_image_2.png");
	blast_image = iLoadImage("blast_image(1).png");
	for (int i = 0; i < 50; i++){
		coins[i].coin_image = iLoadImage("coin_image_1.png");
	}
	place_coins();
	restart_image = iLoadImage("restart_button.png");

	ground_image = iLoadImage("map.jpg");
	platform_image = iLoadImage("Ground.png");
	drop_ground_image = iLoadImage("drop.png");

	inclined_ramp = iLoadImage("inclined_ramp.png");

	drone_image = iLoadImage("drone.png");
	initiate_drone();


	iSetTimer(1000 / 60, iTimer); // Initialize timer for 60 FPS

	// Keep oscillating the spike 
	iSetTimer(150, change_y_of_obstacle);
	iSetTimer(1000 / 60, move_drone_y);
	iSetTimer(150, change_y_of_floating_platform);
	iStart();
	return 0;
}

