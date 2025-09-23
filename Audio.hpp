#ifndef AUDIO_H
#define AUDIO_H
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")



void Audio_OpenAll(){

	mciSendString("open \"Audios//Landing_Page_Music.mp3\" alias landing", NULL, 0, NULL);
	mciSendString("open \"Audios//Play_Background_Music.mp3\" alias playbg", NULL, 0, NULL);
	mciSendString("open \"Audios//Coin_Music.mp3\" alias coin", NULL, 0, NULL);
	mciSendString("open \"Audios//Heart_Gain_Music.mp3\" alias heart_gain", NULL, 0, NULL);
	mciSendString("open \"Audios//Heart_Loss_Music.mp3\" alias heart_loss", NULL, 0, NULL);
	mciSendString("open \"Audios//Blast_Music.mp3\" alias blast", NULL, 0, NULL);

}

void Audio_CloseAll(){

	mciSendString("close landing", NULL, 0, NULL);
	mciSendString("close playbg", NULL, 0, NULL);
	mciSendString("close coin", NULL, 0, NULL);
	mciSendString("close heart_gain", NULL, 0, NULL);
	mciSendString("close heart_loss", NULL, 0, NULL);
	mciSendString("close blast", NULL, 0, NULL);

}


void RewindAndStop(const char* alias){

	char cmd[256];
	sprintf_s(cmd, "stop %s", alias);
	mciSendString(cmd, NULL, 0, NULL);
	sprintf_s(cmd, "seek %s to start", alias);
	mciSendString(cmd, NULL, 0, NULL);
}


void PlayLandingMusic(){

	RewindAndStop("landing");
	mciSendString("play landing repeat", NULL, 0, NULL);
}

void StopLandingMusic(){

	RewindAndStop("landing");
}


void PlayGameMusic(){

	RewindAndStop("playbg");
	mciSendString("play playbg repeat", NULL, 0, NULL);
}

void StopGameMusic(){

	RewindAndStop("playbg");
}


void PlayCoinSound(){

	RewindAndStop("coin");
	mciSendString("play coin", NULL, 0, NULL);
}


void PlayHeartGainSound(){

	RewindAndStop("heart_gain");
	mciSendString("play heart_gain", NULL, 0, NULL);
}

void PlayHeartLossSound(){

	RewindAndStop("heart_loss");
	mciSendString("play heart_loss", NULL, 0, NULL);
}


void PlayBlastSound(){
	
	StopGameMusic();
	StopLandingMusic();

	RewindAndStop("blast");
	mciSendString("play blast", NULL, 0, NULL);
}



































#endif