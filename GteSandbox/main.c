#include <loader.h>
#include <locator.h>
#include <memory.h>
#include <misctool.h>
#include <types.h>

#include "demo_data.h"
#include "gte.h"

#define TOOLFAIL(string) \
  if (toolerror()) SysFailMgr(toolerror(), "\p" string "\n\r    Error Code -> $");

#define LEFT_ARROW      0x0008
#define RIGHT_ARROW     0x0015
#define UP_ARROW        0x000B
#define DOWN_ARROW      0x000A

#define SPRITE_START_TILE 2
#define SPRITE_SLOT 0
#define SPRITE_VBUFF (GTE_VBUFF_SPRITE_START+0*GTE_VBUFF_SPRITE_STEP)


int main (void) {
  Word controlMask;
  Word keyPress;
  Word userId;
  Handle dpHndl;
  Word dpWord;
  Word playerX = 10;
  Word playerY = 20;

  TLStartUp();
  TOOLFAIL("Unable to start tool locator");

  userId = MMStartUp();
  TOOLFAIL("Unable to start memory manager");

  MTStartUp();
  TOOLFAIL("Unable to start misc tools");

  LoadGTEToolSet(userId);

  dpHndl = NewHandle(0x0200, userId, 0x4015, 0);
  if (dpHndl == NULL) {
    TOOLFAIL("Unable to allocate bank 0 memory");
  }
  dpWord = (Word)(*dpHndl);
  if ((dpWord & 0x00FF) != 0x0000) {
    TOOLFAIL("Allocated bank 0 memory is not aligned");
  }

  GTEStartUp(dpWord, 0x0000, userId);
  TOOLFAIL("Unable to start GTE");

  GTESetScreenMode(160, 200);
  GTELoadTileSet(tiles);
  GTESetPalette(0, (Pointer)palette);
  GTEFillTileStore(1);
  GTESetBG0Origin(0, 0);

  GTECreateSpriteStamp(GTE_SPRITE_8X8 | SPRITE_START_TILE, SPRITE_VBUFF);
  GTEAddSprite(SPRITE_SLOT, 0x0000, SPRITE_VBUFF, playerX, playerY);

  do {
    controlMask = GTEReadControl();
    keyPress = controlMask & 0x007F;

    switch (keyPress) {
      case LEFT_ARROW: if (playerX > 0) { playerX--; }
        break;
  
      case RIGHT_ARROW: if (playerX < 156) { playerX++; }
        break;

      case UP_ARROW: if (playerY > 0) { playerY--; }
        break;

      case DOWN_ARROW: if (playerY < 192) { playerY++; }
        break;
    }
 
    GTEMoveSprite(SPRITE_SLOT, playerX, playerY);
    GTERender(0);

  } while (keyPress != 'q' && keyPress != 'Q');

  GTEShutDown();

  DisposeHandle(dpHndl);

  MTShutDown();
  TOOLFAIL("Unable to shutdown misc tool");

  MMShutDown(userId);
  TOOLFAIL("Unable to shutdown memory manager");

  TLShutDown();
  TOOLFAIL("Unable to shutdown tool locator");
}
