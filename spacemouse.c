#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <X11/Xlib.h>
#include <spnav.h>
#include <xdo.h>

void sig(int s)
{
    spnav_close();
	exit(0);
}

int main(void)
{
	xdo_t *xdo;
	int ret = 0;
    spnav_event sev;

    signal(SIGINT, sig);
    
    if(spnav_open()==-1) {
      	fprintf(stderr, "failed to connect to the space navigator daemon\n");
		return 1;
	}
    
	xdo = xdo_new(NULL);

    while(spnav_wait_event(&sev)) {
    	if(sev.type == SPNAV_EVENT_MOTION) {
			printf("got motion event: t(%d, %d, %d) ", sev.motion.x, sev.motion.y, sev.motion.z);
			printf("r(%d, %d, %d)\n", sev.motion.rx, sev.motion.ry, sev.motion.rz);
			ret = xdo_mousemove_relative(xdo, sev.motion.x / 10, (sev.motion.z * -1) / 10);
			if (ret) {
				printf("xdo_mousemove_relative reported an error\n");
			}
		} else {	/* SPNAV_EVENT_BUTTON */
			printf("got button %s event b(%d)\n", sev.button.press ? "press" : "release", sev.button.bnum);
		}
	}

	spnav_close();
	return 0;
}
