#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "Variables.h"

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
			blast_timer += 0.01;
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
			//skip drawing if collected
			if (coins[i].collected){
				continue;
			}

			double x = x_of_coin + i * 15;
			int y;

			if (x >= (OBSTACLE_X - 10) && x <= OBSTACLE_X + 23) y = -50;
			else y = 30;

			//collision detection of coins
			double coin_x = x*vw;
			double coin_y = y*vh;

			if (abs(ball_x - coin_x) < 5 * vw && abs(ball_y - coin_y) < 5 * vh){
				coins[i].collected = true;
				score += 10;
				continue;
			}

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
		iShowImage(46.3 * vw, 35 * vh, 5 * vw, 10 * vh, restart_image);

		//Show score
		char score_text[50];
		sprintf_s(score_text, "Score: %d", score);
		iSetColor(255, 0, 0);
		iText(44 * vw, 50 * vh, score_text, GLUT_BITMAP_HELVETICA_18);

	}
	void show_level_2_failed_screen(){
		iShowImage(0, 0, 100 * vw, 100 * vh, ground_image);
		iSetColor(255, 0, 0);
		iText(42.5 * vw, 55 * vh, "LEVEL FAILED", GLUT_BITMAP_HELVETICA_18);
	}
	void ball_hit_spike(){
		if ((SPIKE_X >= -15 && SPIKE_X <= 20) && ball_y == 28 * vh) {

			show_blast = true;
			blast_timer = 0;
		}
	}


	void move_ball_backwards(){
		rotating_angle += 15;

		x_of_play_screen_background += 1;
		x_of_coin += 1;
		if (x_of_play_screen_background >= 0) x_of_play_screen_background = -100;

		camera_x += 1;

		move_obstacle(1); // 1 means moving RIGHT
		move_spikes(1); // 1 means moving RIGHT
		ball_hit_spike();
	}
	void move_ball_forwards(){
		rotating_angle -= 15;

		x_of_play_screen_background -= 1;
		x_of_coin -= 1;
		if (x_of_play_screen_background <= -400) x_of_play_screen_background = 0;

		camera_x -= 1;

		move_obstacle(-1); // -1 means moving LEFT
		move_spikes(-1); // -1 means moving LEFT
		ball_hit_spike();
	}



	void move_ball_backwards_in_level_2(){
		rotating_angle += 15;

		camera_x += 1;
	}
	void move_ball_forwards_in_level_2(){
		rotating_angle -= 15;

		camera_x -= 1;

	}



	void move_screen_backwards(){
		if (camera_x < 0) camera_x++;
		else camera_x = 0;
	}
	void move_screen_forwards(){
		if (camera_x >-1500) camera_x--;
		else camera_x = camera_x;
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
	void make_map(){


		iShowImage(camera_x*vw, camera_y*vh, 100 * vw, 70 * vh, platform_image);
		iShowImage((100 + camera_x)*vw, camera_y*vh, 100 * vw, 70 * vh, platform_image);

		left_of_first_small_ground = (250 + camera_x);
		if ((left_of_first_small_ground >= 24 && left_of_first_small_ground <= 74) && ball_y == 28 * vh) ball_y = -50 * vh;
		else ball_y = ball_y;

		iShowImage((250 + camera_x)*vw, camera_y*vh, 30 * vw, 70 * vh, platform_image);

		left_of_inclined_ramp = (401 + camera_x);
		iShowImage((401 + camera_x)*vw, (camera_y + 6) * vh, 20 * vw, 60 * vh, inclined_ramp);

		left_of_large_ground = (320 + camera_x);
		if ((left_of_large_ground >= 24 && left_of_large_ground <= 64) && ball_y == 28 * vh) ball_y = -50 * vh;
		else ball_y = ball_y;

		iShowImage((320 + camera_x)*vw, camera_y*vh, 100 * vw, 70 * vh, platform_image);

		iShowImage((419 + camera_x)*vw, (camera_y + 32.5)*vh, 50 * vw, 60 * vh, platform_image);

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
		make_background();

		//Score
		char score_text[50];
		iSetColor(255, 255, 255);
		sprintf_s(score_text, "Score: %d", score);
		iText(90 * vw, 95 * vh, score_text, GLUT_BITMAP_HELVETICA_18);

		// Eda obstacle
		make_coins();
		make_obstacles();

		make_ball();

		iShowImage(2.5*vh, 87.5*vh, 10 * vh, 10 * vh, back_image);

		if (projectileMode && isDragging) {
			iSetColor(255, 0, 0);
			iLine(drag_start_x, drag_start_y, mouseX, mouseY);
		}

		if (level_failed == 1) show_level_failed_screen();
	}
	void show_levels_screen() {


		for (int i = 0; i < 20; i++){

			double left = (i * 100) + camera_x;
			int current_i = i + 1; 
			double top = ((i + 1) * 100) + camera_y;

			iShowImage(left*vw, camera_y*vh, 100 * vw, 100 * vh, ground_image);

			
		}


		for (int i = 0; i < 20; i++){

			double left = (i * 100) + camera_x;
			int current_i = i + 1;
			double top = ((i + 1) * 100) + camera_y;

			iShowImage(left*vw, (100 + camera_y) * vh, 100 * vw, 100 * vh, ground_image);


		}

		for (int i = 0; i < 20; i++){

			double left = (i * 100) + camera_x;

			iShowImage(left*vw, (200 + camera_y) * vh, 100 * vw, 100 * vh, ground_image);


		}



		make_map();
		make_ball();


		iShowImage(2.5*vh, 87.5*vh, 10 * vh, 10 * vh, back_image);





		// pointer
		iSetColor(255, 255, 255);
		iFilledCircle(mouseX, mouseY, 2);


		if (projectileMode && isDragging) {
			//center of ball
			double ball_center_x = ball_x + 7.5 * vh;
			double ball_center_y = ball_y + 7.5 * vh;

			// drag line
			double dx = drag_start_x - mouseX;
			double dy = drag_start_y - mouseY;

			// visible guide multiplier(increase length)
			double scale = 2.0;
			double guide_x = ball_center_x + dx * scale;
			double guide_y = ball_center_y + dy * scale;

			// Main guide line
			iSetColor(255, 255, 255);
			iLine(ball_center_x, ball_center_y, guide_x, guide_y);

			// dot preview
			int steps = 6;
			for (int i = 1; i <= steps; i++) {
				double px = ball_center_x + ((dx * scale) / steps) * i;
				double py = ball_center_y + ((dy * scale) / steps) * i;
				iFilledCircle(px, py, 3);
			}
		}



		iShowImage(2.5*vh, 87.5*vh, 10 * vh, 10 * vh, back_image);

		if (ball_y == -50 * vh) show_level_2_failed_screen();


	}



	void reset_gamestate(){
		camera_x = 0;
		camera_y = 0;

		ball_x = 10 * vw;
		ball_y = GROUND_Y;

		//x_of_play_screen_background = 0;
		//x_of_coin = 5;
		//OBSTACLE_X = 100;
		//SPIKE_X = 90;

		//for (int i = 0; i < 50; i++){
		//coins[i].collected = false;
		//}
	}

	void adjustWorldDuringProjectile() {
		// ball screen lock
		double screen_center_x = ball_x;
		//static double last_ball_y = ball_y;
		//double dy = ball_y - last_ball_y;

		//camera_y += dy/vh;

		// world moves left as projectile moves right
		camera_x -= projectile_vx / vw;  // divide by vw to match world coordinates

		//last_ball_y = ball_y;


	}



	// additional buttons 

	void go_back_from_level_1(){
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

	void go_back_from_level_2(){
		levels_button_clicked = 0;
	}


#endif
