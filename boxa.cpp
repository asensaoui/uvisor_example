#include "mbed.h"
#include "rtos.h"
#include "uvisor-lib/uvisor-lib.h"

#include "boxa.h"


/* uVisor pointer */
typedef struct {
  int thesecret;
  RawSerial * pc;
  int caller_id;
  InterruptIn * sw;
} my_box_context;

/* Configure ACL */
static const UvisorBoxAclItem acl[] = {
};


static void my_box_main(const void *);
void __print_secret(void);


/* Init box */
UVISOR_BOX_NAMESPACE(NULL);
UVISOR_BOX_HEAPSIZE(4096);
UVISOR_BOX_MAIN(my_box_main, osPriorityNormal, UVISOR_BOX_STACK_SIZE);
UVISOR_BOX_CONFIG(my_box, acl, UVISOR_BOX_STACK_SIZE, my_box_context);

/* RPC Gateways */
UVISOR_BOX_RPC_GATEWAY_SYNC(my_box, print_secret, __print_secret, void);

int btn_pressed = 0;

void __print_secret(void)
{
	if(btn_pressed){
    uvisor_ctx->pc->printf("%d\r\n", uvisor_ctx->thesecret);
    btn_pressed = 0;
  }
}

void init_secret(void)
{
  uvisor_ctx->thesecret = 0;
}

static void my_box_switch_irq(void)
{
  /* Simualte some workload */
  for(int i = 0; i<5000;i++);
  /* print on serial port */
  uvisor_ctx->thesecret++;
  btn_pressed = 1;
}

void thready()
{
  /* do some stuff */
  while(1)
  {
    for(int i = 0; i<5000;i++);
  }
}
static void my_box_main(const void *)
{
  osStatus status;
	uvisor_ctx->pc = new RawSerial(USBTX, USBRX);
    if (!uvisor_ctx->pc) {
        return;
  }

   /* allocate a box-specific switch handler */
  if(!(uvisor_ctx->sw = new InterruptIn(SW1)))
      uvisor_ctx->pc->printf("ERROR: failed to allocate memories for SW1\n");
  else
  {
      /* register handler for switch SW1 */
      uvisor_ctx->sw->mode(PullUp);
      uvisor_ctx->sw->fall(my_box_switch_irq);

      /* no problem to return here as everything is initialized */
      
  }


	init_secret();

    /* Start ScThread Thread */
  Thread * threadsc = new Thread();
  status = threadsc->start(thready);
  if (status != osOK) {
    printf("Could not start thready.\r\n");
    uvisor_error(USER_NOT_ALLOWED);
  }

	static const TFN_Ptr my_fn_array[] = {
      (TFN_Ptr) __print_secret
    };



	while(1){
		int status;

    /* NOTE: This serializes all access to the number store! */
    status = rpc_fncall_waitfor(my_fn_array, 1, &uvisor_ctx->caller_id, UVISOR_WAIT_FOREVER);

    if (status) {
        uvisor_ctx->pc->printf("Failure is not an option.\r\n");
        uvisor_error(USER_NOT_ALLOWED);
    }

	}


}