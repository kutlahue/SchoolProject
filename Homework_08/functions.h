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

// Switch proto
void Switch1_Process(void);
void Switch2_Process(void);
void Switches_Process(void);
void disableInput(void);
void enableInput(void);

//Menu proto
void select_menu(void);
void shape_menu(void);
void shape_STRAIGHT(void);
void menu_process(int);

// Shapes
void select_menu(void);
void shape_Blank(void);
void STRAIGHT_Process(void);
void CIRCLE_Process(void);
void TRIANGLE_Process(void);
void FIGURE_8_Process(void);
void ONE_CIRCLE_Process(int complete);
void STRAIGHT_TIME_Process(void);
void CLOCK_TIME_Process(void);
void project_5_process(void);

// Timers
void Init_Timer_A0(void);
void ten_msec_timer_code_switch(void);
void fifty_msec_sleep_A1(unsigned int);


// ADC
void ADC_Process(void);
void Init_ADC(void);
char* itoa(int);
void sample_process(void);
void disableADC(void);
void enableADC(void);
void IR_calibration(unsigned char);
void do_stuff(void);
void set_treshold(void);
void black_line_detect(void);


// Serial
void uart_send_byte(unsigned char data);