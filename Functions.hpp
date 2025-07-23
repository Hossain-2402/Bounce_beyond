#ifndef FUNCTIONS_H
#define FUNCTIONS_H


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
		iShowImage(SPIKE_X*vw, 24 * vh, 37.5 * vw, 12.5 * vh, spike_image);
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
		if ((OBSTACLE_X >= 4 && OBSTACLE_X <= 25) && ball_y > 27*vh) GROUND_Y = (OBSTACLE_Y + 12) * vh;
		else GROUND_Y = 27 * vh;

	}
	void show_level_failed_screen(){
		iShowImage(0, 0, 100 * vw, 100 * vh, play_screen_background_image);
		iSetColor(255, 0, 0);
		iText(42.5 * vw, 55 * vh, "LEVEL FAILED", GLUT_BITMAP_HELVETICA_18);

	}
	void ball_hit_spike(){
		if ((SPIKE_X >= -15 && SPIKE_X <= 25) && ball_y == 27 * vh) {

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










#endif
