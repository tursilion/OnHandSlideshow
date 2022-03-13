/* Slideshow - show MMP, GMP, and my own G2P images */
/* by M.Brent - for the OnHandPC */

/* MMP - Monochrome image format - handled by the Matsucom libs */
/* GMP - Greyscale image format - stored as MMP, flickers 8 images */
/* G2P - Greyscale image format - flickers 2 images at different rates */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <psdos.h>
#include <wbios.h>
#include <lcdbios.h>

#include "..\tunnelx\data\bytursi.inc"

/* The tags are to help find the configurable options in the binary ;) */
/* assumes that the compiler will at least leave them in order!! ;)    */
const char TAG[16]    = "---START DATA--";
const char DELAY[16]  = "Delay: (005) s";
const char PTAG[16]   = "Path to pics:";
const char PATH[50]   = "\\ACCESSOR\\GRAPHICS\\";
const char TAG2[16]   = "----END DATA---";

char buf[10000];
char prev[30][64];  /* Note: fixed size assumed below in code */

int delay;
int nFrame;
static volatile int tick=0;
int *timer;
char DTA[44];
char filename[64];
int nCur, nMax;

int showfile(char *filename);

void timefunc() { 
  tick=tick+1;                 
}

int main() {
  screen(1);
  timer=bi_tmset(0, 255, 1, timefunc);  /* 1hz timer */

  delay=atoi(&DELAY[8]);
  if (delay < 1) delay=5;
  delay=5;

  memset(prev,0,sizeof(prev));

  dos_setdta(DTA);
  strncpy(filename, PATH, 50);
  filename[50]='\0';
  strncat(filename, "*.?MP", 13);
  filename[63]='\0';
  if (dos_fnd_first(filename, 0x3f)) {
    return 1;
  }

  /* show logo 2 seconds - no logo, no files found */
  cls(1);
  gv_put(0, 2, TursLogo, 0);
  tick=0;
  while (tick<2) ;

  nCur=0; nMax=-1;

  /* start slideshow */
  for (;;) {
    if (nCur > nMax) {
      strncpy(filename, PATH, 50);
      filename[50]='\0';
      strncat(filename, &DTA[31], 13);
      filename[strlen(PATH)+13]='\0';
      strcpy(&prev[nCur][0], filename);
      nMax=nCur;
    }
      
    if (showfile(&prev[nCur][0])) {
      break;
    }

    if (nCur == 29) {
      // Oops - out of buffer. Lose the first 10 to make room
      memmove(&prev[0][0], &prev[10][0], 20*64);
      nCur-=10;
      nMax-=10;
    }
    
    nCur++;

    if (nCur > nMax) {
      if (dos_fnd_next()) {
          break;
      }
    }
  }

  bi_tmdel(timer);

  return 0;
}

void strupr(char *fn) {
  while (*fn) {
    *fn=toupper(*fn);
    fn++;
  }
}

/* GMP has 8 images. Each shows for one tick. This gives 256 grey levels */
/* Images use 9x the space of an MMP (and have 1 wasted frame)           */
void doGMP() {
  int x, y;

  nFrame++;
  if ((nFrame > 7) || (nFrame < 0)) nFrame=0;

  x=(nFrame%3)*102;
  y=(nFrame/3)*64;

  gv_place(x,y);
}

/* ZMP has 2 images. The first shows for 1 tick, the second for 2. This gives 4 grey levels */
/* Images use 2x the space of an MMP                                                        */
void doZMP() {
  int x;

  nFrame++;
  if ((nFrame > 2) || (nFrame < 0)) nFrame=0;

  x=(nFrame ? 102 : 0);
  gv_place(x, 0);
}

int showfile(char *filename) {
  /* load file, do delay, check keys (next and menu) */
  int key, ret;
  int type=-1;

  /* check file type (by extension) */
  strupr(filename);
  if (strstr(filename, ".MMP")) { type=1; }
  if (strstr(filename, ".GMP")) { type=2; }
  if (strstr(filename, ".ZMP")) { type=3; }
  if (-1 == type) return 0;

  lcdfreeze(1);
  ret=dos_fopen(filename, 0);
  if (ret<0) { return 0; }  /* try next on failure */
  dos_fread(ret,buf,9999);
  dos_fclose(ret);
  gv_put(0,0,buf,0);
  lcdfreeze(0);

  tick=0; 
  while (tick < delay) {
    key=bi_scanbtn();
    if (key & 0x03) { return 1; }  /* exit on FILER or MENU */
    if (key & 0x40) { break; }     /* 'next' */
    if ((key & 0x10)&&(nCur>0)) { nCur-=2; break; }  /* 'prev' */
    if (key & 0x04) { bi_el(20); } /* on EL, activate backlight for 20 sec (best I can do!) */
    if (key & 0x20) { tick=0; }    /* 'hold' (up) */
    
    /* No delay - I think it looks better than with it */    

    switch (type) {
      case 1: break;    /* MMP */
      case 2: doGMP();  /* GMP */
              break;
      case 3: doZMP();  /* ZMP */
              break;
    }
  }

  return 0;
}



