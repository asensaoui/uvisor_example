#include "mbed.h"
#include "rtos.h"
#include "uvisor-lib/uvisor-lib.h"

#include "boxa.h"


/* Main box Access Control Lists (ACLs). */

static const UvisorBoxAclItem g_main_box_acls[] = {
    {GCR,                                   sizeof(*GCR),       UVISOR_TACLDEF_PERIPH},
    {TMR0,                                  sizeof(*TMR0),     	UVISOR_TACLDEF_PERIPH}, 
    {TMR1,                                  sizeof(*TMR1),      UVISOR_TACLDEF_PERIPH}, 
    {GPIO0,                                 sizeof(*GPIO0),     UVISOR_TACLDEF_PERIPH}, 
    {UART0,                                 sizeof(*UART0),     UVISOR_TACLDEF_PERIPH},
    {(void *)0x42100000,										0x1000,						  UVISOR_TACLDEF_PERIPH},
};


/* Enable uVisor, using the ACLs we just created. */
UVISOR_SET_MODE_ACL(UVISOR_ENABLED, g_main_box_acls);

DigitalOut led1(LED2);
DigitalOut led2(LED1);

void blink_led(void)
{ 
    led1 = !led1;
}

int main() {

   led1 = 1;

  
  while(1){      
    
    
    led1 = !led1;
		Thread::wait(1000);
  }

}
