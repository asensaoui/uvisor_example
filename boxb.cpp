#include "mbed.h"
#include "rtos.h"
#include "uvisor-lib/uvisor-lib.h"

#include "boxa.h"


/* uVisor pointer */
typedef struct {
} my_box_context;

/* Configure ACL */
static const UvisorBoxAclItem acl[] = {
};

static void my_boxb_main(const void *);


/* Init box */
UVISOR_BOX_NAMESPACE(NULL);
UVISOR_BOX_HEAPSIZE(0x1000);
UVISOR_BOX_MAIN(my_boxb_main, osPriorityNormal, UVISOR_BOX_STACK_SIZE);
UVISOR_BOX_CONFIG(my_boxb, acl, UVISOR_BOX_STACK_SIZE, my_box_context);



static void my_boxb_main(const void *)
{

	while(1){
		/* Print the secret */
    print_secret();
	}


}