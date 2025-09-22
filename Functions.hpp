#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "Variables.h"
#include "Drone.h"

void saveScore(const char *playerName, int points, const char *file = "scores.txt");

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
	for (int i = 0; i < 200; i++){
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
void place_coins(){
	coins[0].x = 100;  coins[0].y = 30;
	coins[1].x = 115;  coins[1].y = 30;
	coins[2].x = 130;  coins[2].y = 40;
	coins[3].x = 145;  coins[3].y = 50;
	coins[4].x = 160;  coins[4].y = 30;
	coins[5].x = 190;  coins[5].y = 30;
	coins[6].x = 210;  coins[6].y = 50;
	coins[7].x = 230;  coins[7].y = 70;
	coins[8].x = 250;  coins[8].y = 50;
	coins[9].x = 270;  coins[9].y = 30;
	coins[10].x = 370;  coins[10].y = 50;
	coins[11].x = 380;  coins[11].y = 55;
	coins[12].x = 360;  coins[12].y = 55;
	coins[13].x = 390;  coins[13].y = 60;
	coins[14].x = 350;  coins[14].y = 60;
	coins[15].x = 380;  coins[15].y = 65;
	coins[16].x = 360;  coins[16].y = 65;
	coins[17].x = 370;  coins[17].y = 70;
	coins[18].x = 500;  coins[18].y = 90;
	coins[19].x = 475;  coins[19].y = 90;
	coins[20].x = 487;  coins[20].y = 110;
	coins[21].x = 590;  coins[21].y = 70;
	coins[22].x = 590;  coins[22].y = 100;
	coins[23].x = 590;  coins[23].y = 90;
	coins[24].x = 590;  coins[24].y = 80;
	coins[25].x = 595;  coins[25].y = 80;
	coins[26].x = 585;  coins[26].y = 80;
	coins[27].x = 600;  coins[27].y = 90;
	coins[28].x = 580;  coins[28].y = 90;
	coins[29].x = 590;  coins[29].y = 110;

	for (int i = 0; i < 50; i++) {
		coins[i].collected = false;
	}
}
void make_coins2(){
	for (int i = 0; i < 50; i++) {
		if (coins[i].collected) continue; // Skip collected 

		double coin_x = (coins[i].x + camera_x)* vw;
		double coin_y = (coins[i].y + camera_y)* vh;

		if (abs(ball_x - coin_x) < 5 * vw && abs(ball_y - coin_y) < 5 * vh) {
			coins[i].collected = true;
			score += 10;
			continue;
		}

		iShowImage(coin_x, coin_y, coins[i].width * vh, coins[i].height * vh, coins[i].coin_image);
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

	if (!scoreSaved) {   // <-- only save once
		saveScore(playerName, score);
		scoreSaved = true; // mark as saved
	}
}
void show_level_2_failed_screen(){
	iShowImage(0, 0, 100 * vw, 100 * vh, ground_image);
	iSetColor(255, 0, 0);
	iText(42.5 * vw, 55 * vh, "LEVEL FAILED", GLUT_BITMAP_HELVETICA_18);
}



void ball_hit_spike(){

	if (collision_handled) return;
	if (collision_cooldown > 0) return;

	if ((SPIKE_X >= -15 && SPIKE_X <= 20) && ball_y == 28 * vh) {
		printf("Spike Hit!\n");

		if (heart_count <= 0){
			show_blast = true;
			blast_timer = 0;
		}
		else{
			heart_count -= 1;
		}
		collision_handled = true;
		collision_cooldown = COLLISION_COOLDOWN_FRAMES;
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
	move_drone_x(1);
	move_heart_x(1);
	//ball_hit_spike();
	//drone_hit();
	//heart_hit();
}
void move_ball_forwards(){
	rotating_angle -= 15;

	x_of_play_screen_background -= 1;
	x_of_coin -= 1;
	if (x_of_play_screen_background <= -400) x_of_play_screen_background = 0;

	camera_x -= 1;

	move_obstacle(-1); // -1 means moving LEFT
	move_spikes(-1); // -1 means moving LEFT
	move_drone_x(-1);
	move_heart_x(-1);
	//ball_hit_spike();
	//drone_hit();
	//heart_hit();
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
void jump_up() {
	
	if (jump_count < 2) {
		ball_vy = JUMP_SPEED;
		jump_count += 1;
		isJumping = true;
	}
}

void jump_down(){
	//ball_hit_spike();
	//drone_hit();
	//heart_hit();
	/*jump_on_obstacle();
	//isJumping = true;
	ball_vy += GRAVITY;
	ball_y += ball_vy;
	if (ball_y < GROUND_Y) {
		ball_y = GROUND_Y;
		jump_count = 0;
		isJumping = false;
		ball_vy = 0;
	}*/
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

	left_of_spike = (469 + camera_x);
	iShowImage((469 + camera_x)*vw, (camera_y + 32.5)*vh, 50 * vw, 60 * vh, platform_image);
	iShowImage((469 + camera_x)*vw, (camera_y + 52.5)*vh, 50 * vw, 15 * vh, spike_image);
	/*if ((left_of_spike >= -25 && left_of_spike <= 24) && ball_y == 28 * vh){
		if (heart_count <= 0) {
			show_blast = true;
			blast_timer = 0;
		}
		else {
			heart_count -= 1;
		}

	}
	else ball_y = ball_y;
	*/

	iShowImage((519 + camera_x)*vw, (camera_y + 32.5)*vh, 50 * vw, 60 * vh, platform_image);



	left_of_middle_platform = (569 + camera_x);
	iShowImage((569 + camera_x)*vw, (camera_y + y_of_floating_platform)*vh, 50 * vw, 60 * vh, platform_image);

	if ((left_of_middle_platform >= -25 && left_of_middle_platform <= 4)){
		is_floating_animation = 1;
	}

	iShowImage((619 + camera_x)*vw, (camera_y - 10.5)*vh, 50 * vw, 60 * vh, platform_image);

}

void askPlayerName() {
	printf("Enter your name: ");
	fgets(playerName, 50, stdin); // read input from console
	// remove trailing newline
	int len = strlen(playerName);
	if (len > 0 && playerName[len - 1] == '\n') {
		playerName[len - 1] = '\0';
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

	// Leaderboard button
	iShowImage(30 * vw, 10 * vh, 40 * vw, 40 * vh, button_image);
	iSetColor(0, 0, 0);
	iText(44 * vw, 15 * vh, "LEADERBOARD", GLUT_BITMAP_9_BY_15);

	if (leaderboard_button_enlarge == 1) {
		iShowImage(25 * vw, 10 * vh, 50 * vw, 50 * vh, button_image);
		iSetColor(255, 255, 0);
		iText(42 * vw, 15 * vh, "LEADERBOARD", GLUT_BITMAP_HELVETICA_18);
	}

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
	make_transparentHeart();
	make_coins();
	make_obstacles();
	show_drone();
	show_heart();
	show_filledHeart();

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

	for (int i = 0; i < 20; i++){

		double left = (i * 100) + camera_x;

		iShowImage(left*vw, (-100 + camera_y) * vh, 100 * vw, 100 * vh, ground_image);


	}

	//Score
	char score_text[50];
	iSetColor(255, 255, 255);
	sprintf_s(score_text, "Score: %d", score);
	iText(90 * vw, 95 * vh, score_text, GLUT_BITMAP_HELVETICA_18);

	make_map();
	make_ball();
	make_coins2(); //custom coins


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

	if (level_failed == 1 || ball_y == -50 * vh) show_level_failed_screen();



}



void reset_gamestate(){
	camera_x = 0;
	camera_y = 0;

	ball_x = 10 * vw;
	ball_y = GROUND_Y;

	initiate_drone();
	initiate_heart();

	//x_of_play_screen_background = 0;
	//x_of_coin = 5;
	//OBSTACLE_X = 100;
	//SPIKE_X = 90;

	//for (int i = 0; i < 50; i++){
	//coins[i].collected = false;
	//}

	//saveScore(playerName, score);
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

	initiate_heart();

	scoreSaved = false;

}

void go_back_from_level_2(){
	levels_button_clicked = 0;
}

void change_y_of_floating_platform(){
	//OBSTACLE_Y = rand() % 21 + 40;
	if ((left_of_middle_platform >= -25 && left_of_middle_platform <= 4) && is_floating_animation == 1){
		another_counter++;
		if (another_counter <= 43) {
			y_of_floating_platform--;
			camera_y++;

		}
		else{
			y_of_floating_platform = y_of_floating_platform;
			camera_y = camera_y;
			//is_floating_animation = 0;
			is_floating_animation = 0;
			left_of_middle_platform = -30;
			return;
		}
	}

}




#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Variables.h"  // make sure your other game variables are included

// -------------------- Score Structure --------------------
struct Score {
	char name[50];
	int points;
};

// -------------------- Save Score --------------------
void saveScore(const char* playerName, int points, const char* file) {
	FILE* fp;
	if (fopen_s(&fp, file, "a") == 0) {  // append mode
		fprintf(fp, "%s %d\n", playerName, points);
		fclose(fp);
	}
}

// -------------------- Load Scores --------------------
int loadScores(struct Score scores[], int maxCount, const char* file) {
	FILE* fp;
	if (fopen_s(&fp, file, "r") != 0) return 0;

	int count = 0;
	while (count < maxCount && fscanf_s(fp, "%s %d", scores[count].name, (unsigned)_countof(scores[count].name), &scores[count].points) == 2) {
		count++;
	}

	fclose(fp);
	return count;
}

// -------------------- Sort Scores (High to Low) --------------------
void sortScores(struct Score scores[], int count) {
	for (int i = 0; i < count - 1; i++) {
		for (int j = i + 1; j < count; j++) {
			if (scores[j].points > scores[i].points) {
				struct Score temp = scores[i];
				scores[i] = scores[j];
				scores[j] = temp;
			}
		}
	}
}

// -------------------- Show Top Scores --------------------
void showScoreboard() {
	struct Score scores[100];
	int count = loadScores(scores, 100, "scores.txt");  // always specify file

	if (count == 0) {
		iSetColor(255, 255, 255);
		iText(10*vw, 90*vh, "No scores yet!", GLUT_BITMAP_HELVETICA_18);
		return;
	}

	sortScores(scores, count);

	iSetColor(255, 255, 255);
	iText(10 * vw, 95 * vh, "=== SCOREBOARD ===", GLUT_BITMAP_HELVETICA_18);

	int y = 90;
	for (int i = 0; i < count && i < 10; i++) {  // top 10
		char line[100];
		sprintf_s(line, sizeof(line), "%d. %s - %d", i + 1, scores[i].name, scores[i].points);
		iText(10*vw, y*vh, line, GLUT_BITMAP_HELVETICA_18);
		y -= 5;
	}
}

// -------------------- Example Usage --------------------
// Call saveScore("Player1", 50, "scores.txt") when level ends
// Call showScoreboard() inside your landing page or a scoreboard screen

#endif

