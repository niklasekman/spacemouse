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
	int key_threshold = 50;
	int mouse_sensitivity = 20;
	char space_keydown = 0; /* TODO: Use bitmasks instead */
	char shift_keydown = 0;
	char w_keydown = 0;
	char s_keydown = 0;
	char a_keydown = 0;
	char d_keydown = 0;
	spnav_event sev;

	signal(SIGINT, sig);
    
	if(spnav_open()==-1) {
		fprintf(stderr, "failed to connect to the space navigator daemon\n");
		return 1;
	}
    
	xdo = xdo_new(NULL);

	while(spnav_wait_event(&sev)) {
		if(sev.type == SPNAV_EVENT_MOTION) {

			/*printf("got motion event: t(%d, %d, %d) ", 
					sev.motion.x, 
					sev.motion.y, 
					sev.motion.z);

			printf("r(%d, %d, %d)\n", 
					sev.motion.rx, 
					sev.motion.ry, 
					sev.motion.rz);*/
			
			/* mouse move */
			ret = xdo_mousemove_relative(xdo, 
						(sev.motion.ry * -1) / mouse_sensitivity,
						(sev.motion.rx * -1) / mouse_sensitivity);

			if(ret) {
				printf("xdo_mousemove_relative reported an error\n");
			}
			/* TODO: Refactor following to a function */
			/* space */
			if(sev.motion.y > key_threshold && space_keydown == 0) {
				ret = xdo_keysequence_down(xdo, CURRENTWINDOW, "space", 0);
				space_keydown = 1;
				if(ret) {
					printf("xdo_keysequence_down reported an error\n");
				}
			} else if(sev.motion.y < key_threshold && space_keydown == 1) {
				ret = xdo_keysequence_up(xdo, CURRENTWINDOW, "space", 0);
				space_keydown = 0;
				if(ret) {
					printf("xdo_keysequence_up reported an error\n");
				}
			}

			/* shift */
			if(sev.motion.y < key_threshold * -1 && shift_keydown == 0) {
				ret = xdo_keysequence_down(xdo, CURRENTWINDOW, "shift", 0);
				shift_keydown = 1;
				if(ret) {
					printf("xdo_keysequence_down reported an error\n");
				}
			} else if(sev.motion.y > key_threshold * -1 && shift_keydown == 1) {
				ret = xdo_keysequence_up(xdo, CURRENTWINDOW, "shift", 0);
				shift_keydown = 0;
				if(ret) {
					printf("xdo_keysequence_up reported an error\n");
				}
			}

			/* w */
			if(sev.motion.z > key_threshold && w_keydown == 0) {
				ret = xdo_keysequence_down(xdo, CURRENTWINDOW, "w", 0);
				w_keydown = 1;
				if(ret) {
					printf("xdo_keysequence_down reported an error\n");
				}
			} else if(sev.motion.z < key_threshold && w_keydown == 1) {
				ret = xdo_keysequence_up(xdo, CURRENTWINDOW, "w", 0);
				w_keydown = 0;
				if(ret) {
					printf("xdo_keysequence_up reported an error\n");
				}
			}

			/* s */
			if(sev.motion.z < key_threshold * -1 && s_keydown == 0) {
				ret = xdo_keysequence_down(xdo, CURRENTWINDOW, "s", 0);
				s_keydown = 1;
				if(ret) {
					printf("xdo_keysequence_down reported an error\n");
				}
			} else if(sev.motion.z > key_threshold * -1 && s_keydown == 1) {
				ret = xdo_keysequence_up(xdo, CURRENTWINDOW, "s", 0);
				s_keydown = 0;
				if(ret) {
					printf("xdo_keysequence_up reported an error\n");
				}
			}

			/* a */
			if(sev.motion.x < key_threshold * -1 && a_keydown == 0) {
				ret = xdo_keysequence_down(xdo, CURRENTWINDOW, "a", 0);
				a_keydown = 1;
				if(ret) {
					printf("xdo_keysequence_down reported an error\n");
				}
			} else if(sev.motion.x > key_threshold * -1 && a_keydown == 1) {
				ret = xdo_keysequence_up(xdo, CURRENTWINDOW, "a", 0);
				a_keydown = 0;
				if(ret) {
					printf("xdo_keysequence_up reported an error\n");
				}
			}
			
			/* d */
			if(sev.motion.x > key_threshold && d_keydown == 0) {
				ret = xdo_keysequence_down(xdo, CURRENTWINDOW, "d", 0);
				d_keydown = 1;
				if(ret) {
					printf("xdo_keysequence_down reported an error\n");
				}
			} else if(sev.motion.x < key_threshold && d_keydown == 1) {
				ret = xdo_keysequence_up(xdo, CURRENTWINDOW, "d", 0);
				d_keydown = 0;
				if(ret) {
					printf("xdo_keysequence_up reported an error\n");
				}
			}

		} else {	/* SPNAV_EVENT_BUTTON */
			printf("got button %s event b(%d)\n", 
					sev.button.press ? "press" : "release", sev.button.bnum);
		}
	}

	spnav_close();
	return 0;
}
