#if 1
#define LCD_IO_MODE_8
#define LCD_PORT PORTD
#define LCD_DATA_PORT PORTD
#else
#define LCD_IO_MODE
#define LCD_PORT PORTD
#endif
#define LCD_RS_PORT PORTC
#define LCD_RW_PORT PORTC
#define LCD_E_PORT PORTC
#define LCD_RS_PIN 2
#define LCD_RW_PIN 1
#define LCD_E_PIN 0

#define LCD_DELAY_INIT_REP 150
#define LCD_LINES 4
#define LCD_DISP_LENGTH 20
