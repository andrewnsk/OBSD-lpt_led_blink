#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <machine/sysarch.h>
#include <machine/pio.h>

void ioport(int port) {
        u_long iomap[32];
        struct i386_set_ioperm_args ioperm;
        ioperm.iomap = iomap;
		
        syscall(SYS_sysarch, I386_GET_IOPERM, (char *) &ioperm);
        iomap[port >> 5] &= ~(1 << (port & 0x1f));
        syscall(SYS_sysarch, I386_SET_IOPERM, (char *) &ioperm);
}

void ioport_disable(int port) {
        u_long iomap[32];
        struct i386_set_ioperm_args ioperm;
 
        ioperm.iomap = iomap;
        syscall(SYS_sysarch, I386_GET_IOPERM, (char *) &ioperm);
        iomap[port >> 5] &= ~(0 << (port & 0x1f));
        syscall(SYS_sysarch, I386_SET_IOPERM, (char *) &ioperm);
}

void circle_blink() {

		int led_state_one;
		int led_state_two;
		int led_state_three;
		int led_state_four;
		
		led_state_one = 14;
		led_state_two = 13;
		led_state_three = 11;
		led_state_four = 7;

			outb(0x378, led_state_one);
			usleep(400000);
				
			outb(0x378, led_state_two);
			usleep(400000);
			
			outb(0x378, led_state_three);
			usleep(400000);
			
			outb(0x378, led_state_four);
			usleep(400000);
}

int main() {
		int i;
		i = 60;		

				for(i = 0; i < 60; i++) {
				ioport(0x378);                  
				printf("ioperm enable\n");
				circle_blink();
				ioport_disable(0x378);
				printf("ioperm disable\n");
								}
        return 0;
}
