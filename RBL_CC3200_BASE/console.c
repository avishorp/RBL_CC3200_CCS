// Console (UART) output functions
// LICENSE: GPLv3

#include <stdlib.h>
#include <string.h>

// Driverlib includes
#include "hw_types.h"
#include "hw_memmap.h"
#include "prcm.h"
#include "pin.h"
#include "uart.h"
#include "rom.h"
#include "rom_map.h"

#include "settings.h"

#include "console.h"

char g_cConsoleBuffer[CONSOLE_BUFFER_SIZE];
int g_iConsoleWritePtr;
int g_iConsoleReadPtr;
int g_iConsoleLength;

// Initialize the console
void ConsoleInit()
{
	// Configure the UART
	MAP_UARTConfigSetExpClk(CONSOLE,
			MAP_PRCMPeripheralClockGet(CONSOLE_PERIPH),
	        CONSOLE_BAUD_RATE,
			(UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

	// Clear the console buffer
	memset(g_cConsoleBuffer, 0, sizeof(g_cConsoleBuffer));
	g_iConsoleWritePtr = 0;
	g_iConsoleReadPtr = 0;
	g_iConsoleLength = 0;
}

// Print a message to the console. This function copies the message
// to the console buffer, and it is non-blocking. If there is not enough space
// in the buffer, the message will be truncated and the last printed character
// will be CONSOLE_NOSPACE
void ConsolePrint(const char* pStr)
{
	const char* p = pStr;

	// Copy the message
	while ((*p != 0) && (g_iConsoleLength < CONSOLE_BUFFER_SIZE)) {
		g_cConsoleBuffer[g_iConsoleWritePtr] = *p;
		p++;
		g_iConsoleWritePtr = (g_iConsoleWritePtr + 1) % CONSOLE_BUFFER_SIZE;
		g_iConsoleLength++;
	}

	// Kick the sending process (if not already in progress)
	ConsoleProcessTX();
}

void ConsoleProcessTX()
{
	while(g_iConsoleLength > 0) {
		// There are characters to send
		tBoolean r = MAP_UARTCharPutNonBlocking(CONSOLE, g_cConsoleBuffer[g_iConsoleReadPtr]);

		if (r) {
			// The character was put successfully
			g_iConsoleReadPtr = (g_iConsoleReadPtr + 1) % CONSOLE_BUFFER_SIZE;
			g_iConsoleLength--;
		}
		else
			// No space in the UART buffer
			return;
	}
}


