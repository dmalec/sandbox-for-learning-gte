#include <locator.h>
#include <memory.h>
#include <misctool.h>
#include <types.h>

#include "main.h"
#include "gte.h"
#include "demo_data.h"


#define TOOLFAIL(string) \
    if (toolerror()) SysFailMgr(toolerror(), "\p" string "\n\r    Error Code -> $");

#define LEFT_ARROW      0x0008
#define RIGHT_ARROW     0x0015
#define UP_ARROW        0x000B
#define DOWN_ARROW      0x000A

int main (void) {
  Ref toolStartupRef;
  Word controlMask;
  Word keyPress;
  unsigned int userId;
  Word playerSpriteDecriptor = GTE_SPRITE_8X8 + 2;
  Word playerSpriteVbuff = GTE_VBUFF_SPRITE_START + 0 * GTE_VBUFF_SPRITE_STEP;
  Word playerSpriteSlot = 0;
  Word playerX = 10;
  Word playerY = 20;
  Word yDiff = 1;
  Word xDiff = 1;
  Word page;

  userId = MMStartUp();
  TOOLFAIL("Unable to start memory manager");

  TLStartUp();
  TOOLFAIL("Unable to start tool locator");

  toolStartupRef = StartUpTools(userId, refIsResource, rez_tools);
  TOOLFAIL("Unable to start tools");

  // NOTE: The first zero (for dPageAddr) seems incorrect based on looking at the
  // demos which call thusly (adding 0x0100 to the direct page register value):
  //
  //   clc
  //   tdc
  //   adc   #$0100
  //   pha
  //   pea   #0
  //   lda   MyUserId
  //   pha
  //   _GTEStartUp
  //
  // I am unsure how to do the equivalent in C. The value 0 does not cause
  // immediate issues; but, I'm worried it's causing the stability issues over time.
  
  GTEStartUp(0x0000, 0x0000, userId);
  TOOLFAIL("Unable to start GTE");

  GTESetScreenMode(320, 200);
  
  GTELoadTileSet(tiles);

  GTESetPalette(0, (Ptr)palette);

  GTEFillTileStore(1);
  GTESetBG0Origin(0, 0);

  GTECreateSpriteStamp(playerSpriteDecriptor, playerSpriteVbuff);
  GTEAddSprite(playerSpriteDecriptor, playerX, playerY, playerSpriteSlot);
  GTEUpdateSprite(playerSpriteSlot, 0x0000, playerSpriteVbuff);

  do {
    controlMask = GTEReadControl();
    keyPress = controlMask & 0x007F;
    
    if (keyPress == LEFT_ARROW && playerX > 0) {
      playerX = playerX - 1;
    }
    
    // NOTE: This is another interesting point. I would expect this value to
    // be 320 (width of screen) - 8 (width of sprite). I'm not sure what I'm
    // doing wrong setting up widths to result in this being the boundary for
    // the sprite lining up with the right side of the screen.
    if (keyPress == RIGHT_ARROW && playerX < 156) {
      playerX = playerX + 1;
    }

    if (keyPress == UP_ARROW && playerY > 0) {
      playerY--;
    }
    
    if (keyPress == DOWN_ARROW && playerY < 192) {
      playerY++;
    }

    GTEMoveSprite(playerSpriteSlot, playerX, playerY);
    GTERender(0);

  } while (keyPress != 'q' && keyPress != 'Q');

  GTEShutDown();

  ShutDownTools(refIsHandle, toolStartupRef);
  TOOLFAIL("Unable to shutdown tools");

  TLShutDown();
  TOOLFAIL("Unable to shutdown tool locator");

  MMShutDown(userId);
  TOOLFAIL("Unable to shutdown memory manager");
}
