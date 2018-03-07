#include <cstdint>
#include "tivaware/inc/hw_memmap.h"
#include "tivaware/driverlib/sysctl.h"
#include "tivaware/driverlib/interrupt.h"
#include "tivaware/driverlib/gpio.h"
#include "tivaware/driverlib/pin_map.h"
#include "tivaware/driverlib/ssi.h"
#include "tivaware/driverlib/rom.h"
#include "tivaware/driverlib/rom_map.h"
#include "tivaware/utils/uartstdio.h"

#include "util/driverlib/ssi.hpp"

#include "common.hpp"

namespace {

constexpr auto IOBaudRate = 115200;

} // namespace

extern "C" {

//! Initializes early hardware
//! Sets up system clock to the 80MHz
void preinitHardware()
{
    MAP_SysCtlClockSet(SYSCTL_SYSDIV_2_5
        | SYSCTL_USE_PLL
        | SYSCTL_XTAL_16MHZ
        | SYSCTL_OSC_MAIN);
    assert(MAP_SysCtlClockGet() == ClockHz);
}

//! Initializes IO UART channel
//! Configures UART0 to work with UARTstdio
void initIO()
{
	MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	MAP_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

	UARTStdioConfig(0, IOBaudRate, ClockHz);

	UARTprintf("Init: IO initialized\n");
}

//! Initializes additional hardware used by software
void initHardware()
{
	// // Configure GPIO of pins of SSI0 module. Pull-up SSI0CLK pin
	// MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
	// MAP_GPIOPinConfigure(GPIO_PA2_SSI0CLK);
	// MAP_GPIOPinConfigure(GPIO_PA3_SSI0FSS);
	// MAP_GPIOPinConfigure(GPIO_PA4_SSI0RX);
	// MAP_GPIOPinConfigure(GPIO_PA5_SSI0TX);
	// MAP_GPIOPinTypeSSI(GPIO_PORTA_BASE,
	// 	GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5);

	// // configure SSI0: TI SSI mode, master, 1.5MHz and 13bits frame width
	// MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_SSI0);
	// MAP_SSIConfigSetExpClk(SSI0_BASE, MAP_SysCtlClockGet(), SSI_FRF_TI,
	// 	SSI_MODE_MASTER, 1500000, 13);
	// SSIEnable(SSI0_BASE);

	UARTprintf("Init: Hardware initialized.\n");
}

}
