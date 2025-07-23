#ifndef VARIABLES_H
#define VARIABLES_H



	// vw & vh
	int vh = 5;
	int vw = 10;




	// Images
	int landing_page_background_image;
	int button_image;
	int ball_image;
	int play_screen_background_image;
	char ball_images[3][100] = {
		"ball_image_8.png",
		"ball_image_10.png",
		"ball_image_2.png",
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
	double SPIKE_X = 90;


	//Movement Flags
	bool isDPressed = false;
	bool isAPressed = false;
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
	const double JUMP_SPEED = 12.0;         // initial jump velocity
	//const double MOVE_SPEED = 2.0;          // horizontal speed
	double GROUND_Y = 27 * vh;      // your floor level [GROUND_Y cannot be const]




#endif