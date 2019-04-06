#include "lcd.h"
#include <Wire.h>

/* this trivial implementation uses 0x10-0x1F as control characters.
 * 0x00-0x0F aren't used because the LCD allows them to be programmed
 * as graphics data.
 * 
 */
enum LCD_CMDS {
  LCD_NOP = 0x10,
  LCD_GOTO,      // 8 bits: 3-bit line, 5-bit column
  LCD_BACKLIGHT, // 8 bits: brightness
  LCD_SETCGRAM,  // 9 chars: address and CG RAM data
  LCD_CLEAR,     // no bits
};

static uint8_t brightness = 0;

void
proc(int chars) {
  uint8_t buf[9];
  while (Wire.available() > 0) {
    uint8_t c = Wire.read();
    // controls done with control characters, but 0-10 are the character graphics range.
    if (c >= 0x20 || c < 0x10) {
      lcd_putc(c);
      continue;
    }
    switch (c) {
    case LCD_NOP: default:
      break;
    case LCD_GOTO:
      // silently fail if there's not a byte available yet
      if (Wire.available() < 1)
        break;
      c = Wire.read();
      lcd_gotoxy(c & 0x1F, (c & ~0x1F) >> 5);
      break;
    case LCD_SETCGRAM:
      for (int i = 0; i < 9; ++i) {
        buf[i] = Wire.read();
      }
      lcd_cgram(buf[0], buf + 1);
      break;
    case LCD_BACKLIGHT:
      if (Wire.available() < 1)
        c = (!brightness) * 255;
      else
        c = Wire.read();
      analogWrite(9, c);
      brightness = c;
      break;
    case LCD_CLEAR:
      lcd_clrscr();
      break;
    }
  }
}

void
setup() {
  pinMode(9, OUTPUT);
  analogWrite(9, brightness);
  Wire.begin(0x32);
  Wire.onReceive(proc);
  lcd_init(LCD_DISP_ON);
}


void
loop() {
  delay(1000);
}
