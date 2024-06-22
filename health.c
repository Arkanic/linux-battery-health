#include <stdio.h>
#include <stdlib.h>

#include "lbh.h"

int main(int argc, char *argv[]) {
	long energy_full = readmes("/sys/class/power_supply/BAT0/energy_full");
	long energy_full_design = readmes("/sys/class/power_supply/BAT0/energy_full_design");
	long energy_now = readmes("/sys/class/power_supply/BAT0/energy_now");

	double percentage = ((float)energy_full / (float)energy_full_design) * 100.0;
	printf("battery health: %.2f\%\n", percentage);

	return 0;
}
