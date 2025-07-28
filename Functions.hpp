#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "Variables.hpp"

	// hover effects
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

	// the game screen
	void make_background(){
		for (int i = 0; i < 5; i++) {
			iShowImage((x_of_play_screen_background + i * 100) * vw, 0, 100 * vw, 100 * vh, play_screen_background_image);
		}
	}
	void make_ball(){
		//blast before level failed
		if (show_blast && (blast_timer < blast_duration)) {
			iShowImage(ball_x, ball_y, 25 * vh, 25 * vh, blast_image);
		}
		else if (show_blast && blast_timer >= blast_duration) {
			level_failed = 1;
			show_blast = false; // prevent looping
		}
		else{
			//draw and rotate ball sprite
			iRotate((ball_x + 7.5 * vh), (ball_y + 7.5 * vh), rotating_angle);
			iShowImage(ball_x, ball_y, 15 * vh, 15 * vh, ball_image);
			iUnRotate();
		}
	}
	void make_obstacles(){
		iShowImage(OBSTACLE_X*vw, OBSTACLE_Y * vh, 20 * vw, 20 * vh, obstacle_image_4);
		iShowImage(SPIKE_X*vw, 24 * vh, 37.5 * vw, 12.5 * vh, spike_image);
	}
	void make_coins(){
		for (int i = 0; i < 50; i++){
			double x = x_of_coin + i * 15;
			int y;

			if (x >= (OBSTACLE_X-10) && x <= OBSTACLE_X + 23) y = -50;
			else y = 30;

			iShowImage(x*vw, y*vh, coins[i].width * vh, coins[i].height * vh, coins[i].coin_image);
		}
	}

	// moving things
	void move_obstacle(int moving_direction) { // moving_direction = 1 (moving RIGHT) moving_direction = -1 (moving LEFT)
		if (OBSTACLE_X <= -20) {
			OBSTACLE_X = 110;
		}
		else if (OBSTACLE_X >= 110) {
			OBSTACLE_X = -20;
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

	// moving actions
	void change_y_of_obstacle(){
		//OBSTACLE_Y = rand() % 21 + 40;
		counter++;
		if (counter <= 15) OBSTACLE_Y++;
		else if (counter >= 15 && counter <= 30) OBSTACLE_Y--;
		else{
			counter = 0;
		}

	}
	void jump_on_obstacle(){
		if ((OBSTACLE_X >= 4 && OBSTACLE_X <= 25) && ball_y > OBSTACLE_Y * vh) GROUND_Y = (OBSTACLE_Y + 12) * vh;
		else GROUND_Y = 28 * vh;

	}
	void show_level_failed_screen(){
		iShowImage(0, 0, 100 * vw, 100 * vh, play_screen_background_image);
		iSetColor(255, 0, 0);
		iText(42.5 * vw, 55 * vh, "LEVEL FAILED", GLUT_BITMAP_HELVETICA_18);
		iShowImage(46.5 * vw, 40 * vh, 5 * vw, 10 * vh, restart_image);

	}
	void ball_hit_spike(){
		if ((SPIKE_X >= -15 && SPIKE_X <= 20) && ball_y == 28 * vh) {

			show_blast = true;
			blast_timer = 0;
		}
	}


	// moving the ball forwards/backwards 
	void move_ball_backwards(){
		rotating_angle += 15;

		x_of_play_screen_background += 1;
		x_of_coin += 1;
		if (x_of_play_screen_background >= 0) x_of_play_screen_background = -100;

		move_obstacle(1); // 1 means moving RIGHT
		move_spikes(1); // 1 means moving RIGHT
		ball_hit_spike();
	}
	void move_ball_forwards(){
		rotating_angle -= 15;

		x_of_play_screen_background -= 1;
		x_of_coin -= 1;
		if (x_of_play_screen_background <= -400) x_of_play_screen_background = 0;

		move_obstacle(-1); // -1 means moving LEFT
		move_spikes(-1); // -1 means moving LEFT
		ball_hit_spike();
	}

	// ball jump up/down
	void jump_up(){
		isJumping = true;
		jump_on_obstacle();


		ball_vy = JUMP_SPEED;
		ball_vy += GRAVITY;
		ball_y += ball_vy;
	}
	void jump_down(){
		ball_hit_spike();
		jump_on_obstacle();
		//isJumping = true;
		ball_vy += GRAVITY;
		ball_y += ball_vy;
		if (ball_y < GROUND_Y) {
			ball_y = GROUND_Y;
			//isJumping = false;
			ball_vy = 0;
		}
	}


	// making pages 
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
		make_background();

		// Eda obstacle
		make_coins();
		make_obstacles();

		make_ball();

		iShowImage(2.5*vh, 87.5*vh, 10 * vh, 10 * vh, back_image);

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










#endif
