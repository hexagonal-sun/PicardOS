/* Useful definitions for manipulating the LCD */
#define LED_ENABLE 0x10
#define LCD_RS 0x2
#define LCD_E  0x1
#define LCD_RW 0x4
#define LCD_BUSY_MASK 0x80
#define LCD_BACKLIGHT_MASK 0x20
volatile unsigned int *PIO_A;
volatile unsigned int *PIO_B;

/* LCD commands */
#define LCD_NEWLINE 0xC0

enum reg_type
{
	REG_DATA = 0,
	REG_CONTROL = 1
};


/* Useful function declorations. */
void _lcd_busy(); /* wait until the LCD isn't busy */
void _print_char(unsigned char c); /* Print a char to the display */
void _lcd_send_command(enum reg_type type,
                       unsigned char data); /* Send a command to the LCD */
