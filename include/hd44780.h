

/*								STM32F103C6-HITACHI44780U PIN/PORT CONFIGURATION
 *
 * 				RS = PB0----------------\
 *				RW = PB1------------------> CONTROL <-> GPIOB(RS), GPIOB(RW), GPIOA(EN)
 *				EN = PA8----------------/
 *
 *
 *				DB4 = PA9---------------\
 *				DB5 = PA10--------------\\----------> DATA <-> GPIOA(DB4), GPIOA(DB5), GPIOB(DB6), GPIOB(DB7)
 *				DB6 = PB5---------------//---------->
 *				DB7 = PB6---------------/
 *
 *
 *
 * [AHB]----------->[BRIDGE 1]------------->[APB2]---------------------->[GPIO:A B C D E, AFIO, USART1]
 *
 *
 *
 *
 *
 *
 *
 */

#ifndef HD44780_H_
#define HD44780_H_

#define HD44780_CMD_RESET            		0x30     	/*!< Resets display - used in init 3x */
#define HD44780_CMD_CLEAR            		0x01     	/*!< Clears display */
#define HD44780_CMD_RETURN_HOME      		0x02     	/*!< Sets DDRAM pointer to 0 */
#define HD44780_CMD_ENTRY_MODE       		0x04     	/*!< Sets how the pointer is updated after a character write */
#define HD44780_CMD_DISPLAY          		0x08     	/*!< Display settings */
#define HD44780_CMD_SHIFT            		0x10     	/*!< Cursor and display movement */
#define HD44780_CMD_FUNCTION         		0x20     	/*!< Screen type setup */
#define HD44780_CMD_CGRAM_ADDR      	 	0x40     	/*!< Sets CGRAM address */
#define HD44780_CMD_DDRAM_ADDR		       	0x80     	/*!< Sets DDRAM address */

/* ENTRY_MODE Command parameters */
#define HD44780_ENTRY_SHIFT_DISP 			0x01	 		/*!< Shift display */
#define HD44780_ENTRY_SHIFT_CURS 			0x00	 		/*!< Shift cursor */
#define HD44780_ENTRY_ADDR_INC   			0x02     		/*!< Increments pointer */
#define HD44780_ENTRY_ADDR_DEC   			0x00	 		/*!< Decrements pointer */

/* DISPLAY Command parameters */
#define HD44780_DISP_ON       				0x04      /*!< Enables the display */
#define HD44780_DISP_OFF      				0x00      /*!< Disables the display */
#define HD44780_DISP_CURS_ON  				0x02      /*!< Enables cursor */
#define HD44780_DISP_CURS_OFF 				0x00      /*!< Disables cursor */
#define HD44780_DISP_BLINK_ON				0x01      /*!< Enables cursor blinking */
#define HD44780_DISP_BLINK_OFF  			0x00      /*!< Disables cursor blinking */

/* SHIFT Command parameters */
#define HD44780_SHIFT_DISPLAY    			0x08      /*!< Shifts the display or shifts the cursor if not set */
#define HD44780_SHIFT_CURSOR    			0x00      /*!< Shifts the display or shifts the cursor if not set */
#define HD44780_SHIFT_RIGHT      			0x04      /*!< Shift to the right */
#define HD44780_SHIFT_LEFT      			0x00      /*!< Shift to the left  */

/* FUNCTION Command parameters */
#define HD44780_FUNC_BUS_8BIT  				0x10      /*!< 8 bit bus */
#define HD44780_FUNC_BUS_4BIT  				0x00      /*!< 4 bit bus */
#define HD44780_FUNC_LINES_2   				0x08      /*!< 2 lines */
#define HD44780_FUNC_LINES_1   				0x00      /*!< 1 line */
#define HD44780_FUNC_FONT_5x10 				0x04      /*!< 5x10 font */
#define HD44780_FUNC_FONT_5x8  				0x00      /*!< 5x8 font */

/* Busy Flag - actually not used */
#define HD44780_BUSY_FLAG        			0x80      /*!< Busy flag */


/***************************************************************
 *
 * CONFIGURATION
 *
 ***************************************************************/

#define HD44780_CONF_BUS							HD44780_FUNC_BUS_4BIT
#define HD44780_CONF_LINES							HD44780_FUNC_LINES_2
#define HD44780_CONF_FONT							HD44780_FUNC_FONT_5x8

#define HD44780_DISP_LENGTH							16
#define HD44780_DISP_ROWS							2
#define HD44780_CONF_SCROLL_MS						20




/* HD44780 Data lines - use the same port for all the lines */
#define HD44780_DATABIT0							GPIO_Pin_0	//not used in 4-bit mode
#define HD44780_DATABIT1							GPIO_Pin_1	//not used in 4-bit mode
#define HD44780_DATABIT2							GPIO_Pin_2	//not used in 4-bit mode
#define HD44780_DATABIT3							GPIO_Pin_3	//not used in 4-bit mode
#define HD44780_DATABIT4							GPIO_Pin_9
#define HD44780_DATABIT5							GPIO_Pin_10
#define HD44780_DATABIT6							GPIO_Pin_5
#define HD44780_DATABIT7							GPIO_Pin_6

/* HD44780 Control lines - use the same port for all the lines */
#define HD44780_RS_BIT								GPIO_Pin_0
#define HD44780_RW_BIT								GPIO_Pin_1
#define HD44780_EN_BIT								GPIO_Pin_8

/* defines the peripheral clocks that need to be enabled for the above pins */
#define HD44780_RCC_AHBPeriph RCC_APB2Periph_GPIOA  | RCC_APB2Periph_GPIOB  //or something like "RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOD"


/***************************************************************
 *
 * FUNCTIONS
 *
 ***************************************************************/

#define hd44780_RS_On()		            GPIO_WriteBit(GPIOB,HD44780_RS_BIT, Bit_SET)
#define hd44780_RS_Off()	           	GPIO_WriteBit(GPIOB, HD44780_RS_BIT, Bit_RESET)
#define hd44780_RW_On()		            GPIO_WriteBit(GPIOB, HD44780_RW_BIT, Bit_SET)
#define hd44780_RW_Off()	            GPIO_WriteBit(GPIOB, HD44780_RW_BIT, Bit_RESET)
#define hd44780_EN_On()		            GPIO_WriteBit(GPIOA, HD44780_EN_BIT, Bit_SET)
#define hd44780_EN_Off()	            GPIO_WriteBit(GPIOA, HD44780_EN_BIT, Bit_RESET)

#define hd44780_EN_high_delay()     	hd44780_Delay(20000)   //4095)
#define hd44780_init_delay()        	hd44780_Delay(1279000)	//16ms
#define hd44780_init_delay2()       	hd44780_Delay(51400)	//5ms
#define hd44780_init_delay3()       	hd44780_Delay(10280)	//1ms
#define hd44780_init_end_delay()    	hd44780_Delay(20560)	//2ms

#define hd44780_clear()                       	  hd44780_wr_cmd( HD44780_CMD_CLEAR )
#define hd44780_home()                        	  hd44780_wr_cmd( HD44780_CMD_RETURN_HOME )
#define hd44780_entry( inc_dec, shift )           hd44780_wr_cmd( ( HD44780_CMD_ENTRY_MODE | inc_dec | shift ) & 0x07 )
#define hd44780_display( on_off, cursor, blink )  hd44780_wr_cmd( ( HD44780_CMD_DISPLAY | on_off | cursor | blink ) & 0x0F )
#define hd44780_shift( inc_dec, shift )           hd44780_wr_cmd( ( HD44780_CMD_SHIFT | inc_dec | shift ) & 0x1F )
#define hd44780_function( bus, lines, font )      hd44780_wr_cmd( ( HD44780_CMD_FUNCTION | bus | lines | font ) & 0x3F )
#define hd44780_cgram_addr( addr )                hd44780_wr_cmd( HD44780_CMD_CGRAM_ADDR | ( addr & 0x3F ) )
#define hd44780_ddram_addr( addr )                hd44780_wr_cmd( HD44780_CMD_DDRAM_ADDR | ( addr & 0x7F ) )
#define hd44780_write_char( c )                   hd44780_wr_data( c & 0xff )



#endif /* HD44780_H_ */
