// Function prototypes main
void main(void);
void Init_Conditions(void);
void Switches_Process(void);
void Init_Timers(void);
void Init_LEDs(void);

// Function prototypes clocks
void Init_Clocks(void);


// Function prototypes systems
void enable_interrupts(void);

// Function prototypes
__interrupt void Timer2_B0_ISR(void);
 __interrupt void TIMER2_B1_ISR(void);
void Init_Timer_B2(void);
void TimerB0code(void);
void usleep10(unsigned int usec);
void five_msec_sleep(unsigned int fivemsec);

// Function prototypes ports
void Init_Ports(void);
void Init_Port1(void);
void Init_Port2(void);
void Init_Port3(char clock_state);
void Init_Port4(void);
void Init_PortJ(void);

// LCD Prototypes
void Init_LCD(void);
void lcd_clear(void);
void lcd_putc(char c);
void lcd_puts(char *s);
void lcd_out(char *s, char line);
void lcd_write(char data, char command);
void lcd_command( char data);
