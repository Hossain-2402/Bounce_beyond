
#ifndef VARIABLES_H
#define VARIABLES_H



// vw & vh
int vh = 5;
int vw = 10;




// Images
int landing_page_background_image;
int blast_image;
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
int back_image;
int restart_image;
int ground_image;
int platform_image;
int drop_ground_image;
int inclined_ramp;

struct Coins{
	int coin_image; // coin top-bottom-left-right padding : 2*vh
	int height = 8;
	int width = 8;
	bool collected = false;
}coins[50];

int score = 0;


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
double x_of_coin = 5;
double ball_x = 20 * vw;	//start X
double ball_y = 23 * vh;	//start Y
double rotating_angle = 0;
double OBSTACLE_X = 100;
double OBSTACLE_Y = 50;
double SPIKE_X = 90;
double GROUND_Y = 28 * vh;      // your floor level [GROUND_Y cannot be const]

double camera_x = 0;
double camera_y = 0;
double left_of_first_small_ground;
double left_of_large_ground;
double left_of_inclined_ramp;


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

//physics state
double ball_vx = 0.0;
double ball_vy = 0.0;

//Physics constants
const double GRAVITY = -0.5;         // pixels/frame
const double JUMP_SPEED = 12.0;         // initial jump velocity
//const double MOVE_SPEED = 2.0;          // horizontal speed

//blast
bool show_blast = false;
int blast_timer = 0;
const int blast_duration = 10;

int counter = 0;


//projectile
bool projectileMode = false;
bool isDragging = false;
int drag_start_x;
int drag_end_x;
int drag_start_y;
int drag_end_y;

bool launched = false;
double projectile_vx = 0;
double projectile_vy = 0;

//mouse tracker
int mouseX, mouseY;




#endif
