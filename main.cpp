#include "mbed.h"
#include "rtos.h"
#include "uvisor-lib/uvisor-lib.h"



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

int main() {

   led1 = 1;

  
  while(1){      
    /* Blink led */ 
    led1 = !led1;
		Thread::wait(1000);
  }

}
