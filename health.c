#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lbh.h"

struct {
	char *batname;
	short full;
	long long scaledivisor;
	char *scaletext;
} Config;

void initconfig(void) {
	Config.batname = "BAT0";
	Config.full = 0;
	Config.scaledivisor = 1000000;
	Config.scaletext = "Wh";
}

void showhelp(void) {
	fprintf(stderr, "Usage: ./health\n");
	fprintf(stderr, "Flags:\n"
		"--full                display all known values\n"
		"--scale <w, m, u>     unit to display full values in, irrelevant if --full is not specified\n"
		"    w = watt hours\n    m = milli watt hours\n    u = micro watt hours\n"
	);
}

int main(int argc, char *argv[]) {
	initconfig();

	for(int i = 1; i < argc; i++) {
		short more = i+1 < argc;

		if(!strcmp(argv[i], "--full")) {
			Config.full = 1;
		} else if(!strcmp(argv[i], "--scale") && more) {
			char *scaleraw = argv[++i];
			switch(scaleraw[0]) {
				case 'w':
					break;
				case 'm':
					Config.scaledivisor = 1000;
					Config.scaletext = "mWh";
					break;
				case 'u':
					Config.scaledivisor = 1;
					Config.scaletext = "μWh";
					break;
				default:
					showhelp();
					return 1;
					break;
			}
		} else {
			showhelp();
			return 1;
		}
	}

	long energy_full = readmes("/sys/class/power_supply/BAT0/energy_full");
	long energy_full_design = readmes("/sys/class/power_supply/BAT0/energy_full_design");
	long energy_now = readmes("/sys/class/power_supply/BAT0/energy_now");

	double percentage = ((float)energy_full / (float)energy_full_design) * 100.0;
	printf("battery health: %.2f\%\n", percentage);

	if(Config.full) {
		double energy_fullsc = energy_full / (double)Config.scaledivisor;
		double energy_full_designsc = energy_full_design / (double)Config.scaledivisor;
		double energy_nowsc = energy_now / (double)Config.scaledivisor;

		printf("full charge capacity: %.2f %s\ndesign full charge capacity: %.2f %s\ncurrent charge: %.2f %s\n", energy_fullsc, Config.scaletext, energy_full_designsc, Config.scaletext, energy_nowsc, Config.scaletext);
	}

	return 0;
}
