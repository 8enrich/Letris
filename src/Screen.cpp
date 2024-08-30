#include "../include/Screen.hpp"
#include <cstdio>
#include <raylib.h>
Screen::Screen() : Screen(""){};

Screen::Screen(std::string musicPath) : musicPath(musicPath){
  if(IsAudioDeviceReady()){
    if(musicPath != ""){
      music = LoadMusicStream(musicPath.c_str());
      if (IsMusicReady(music)){
        PlayMusicStream(music);
        SetMusicVolume(music, (float)settings::db["VOLUME"]/100);
      }
    }
  }
};

Screen::~Screen() {
  if(IsMusicReady(music) && IsMusicStreamPlaying(music)){StopMusicStream(music);}
  if(IsMusicReady(music)){UnloadMusicStream(music);}
};
void Screen::OpenClose() {
  shouldClose = !shouldClose;
}

bool Screen::ShouldClose(){
  return shouldClose;
}

void Screen::Draw(){}

void Screen::Tick(){}

Music Screen::GetMusic(){
  return music;
}

Screens Screen::GetScreen(){ return nextScreen;}

void Screen::SetNextScreen(Screens newNextScreen){
  nextScreen = newNextScreen;
}
