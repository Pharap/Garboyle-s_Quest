/*  
  ****  Garboyle's Quest ****
  
    Made by Cédric Martin 2020 - 2021    
    inspired by CAPCOM "Gargoyle's Quest"    
    Physics, camera, level generator and more are taken from Mystic Ballon (see under)

    I hope you'll enjoy ! 


  ** Controls **
  
  Left/Right  : Move 
  Up          : look up / go through a door
  Down        : look down
  Up + Down   : Pause Game -> can save and return to main menu
  A           : Shoot
  B           : Jump / Fly / Stop Flying
  ????        : Secret Level Up

  When you jump against a wall, you will hang on to it. There you can:
  - Shoot with A
  - Drop with Down + B
  - Jump with B or with B + the direction oppposite to the wall

  When you enter a "Boss Room", you can't get out until you are the last survivor...


  *** Team ARG Mystic Ballon ***
  
  Mystic Balloon: http://www.team-arg.org/mybl-manual.html
  Arduboy version 1.7.2:  http://www.team-arg.org/mybl-downloads.html
  MADE by TEAM a.r.g. : http://www.team-arg.org/more-about.html
  2016-2018 - GAVENO - CastPixel - JO3RI - Martian220
  Game License: MIT : https://opensource.org/licenses/MIT
  
  Garboyle's Quest License is also MIT

*/

//determine the game
#define GAME_ID 206

#include "globals.h"
#include "menu.h"
#include "game.h"
#include "inputs.h"
#include "player.h"
#include "enemies.h"
#include "elements.h"
#include "levels.h"


typedef void (*FunctionPointer) ();

const FunctionPointer PROGMEM  mainGameLoop[] = {
  stateMenuIntro,
  stateMenuMain,
  stateMenuDifficulty, //stateMenuHelp,
  stateMenuPlaySelect,
  stateMenuInfo,
  stateMenuGameOver,
  stateGameNextLevel,
  stateGamePlaying,
  stateGamePause,
  stateGameLvlUp,
  stateGameOver,
  stateMenuPlayLoad,
  stateMenuPlayNew,
};

void setup()
{
  arduboy.boot();                                           // begin with the boot logo en setting up the device to work
  //arduboy.audio.begin();
  arduboy.bootLogoSpritesSelfMasked();
  arduboy.setFrameRate(60);                                 // set the frame rate of the game at 60 fps
  arduboy.initRandomSeed();
  loadSetEEPROM();
}

void loop() {
  if (!(arduboy.nextFrame())) return;
  //if (gameState < STATE_GAME_NEXT_LEVEL && arduboy.everyXFrames(10))sparkleFrames = (++sparkleFrames) % 5;
  arduboy.pollButtons();
  arduboy.clear();
  ((FunctionPointer) pgm_read_word (&mainGameLoop[gameState]))();
  arduboy.display();
}
