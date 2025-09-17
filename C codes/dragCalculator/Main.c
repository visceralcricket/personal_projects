#include <stdio.h>

#define KNOT 0.514444
#define SEALEVEL 1.225

double calcDrag(double airDens, double airSpeed, double refArea, double dragC);
void showResults(double airDens, double airSpeed, double refArea, double dragC);

int main(void) {
	
	double airDens, airSpeed, refArea, dragC;

	do {
		printf("\nPlease input the next\nAir density [kg/m^3] | Airspeed in knots [knots] | Reference area [m^2] | Drag coefficient.\n< ");
		scanf("%lf %lf %lf %lf", &airDens, &airSpeed, &refArea, &dragC);

	}while(airDens < 0 || airSpeed < 0 || refArea < 0 || dragC < 0);

	airSpeed = airSpeed * KNOT;

	showResults(airDens, airSpeed, refArea, dragC);



}

void showResults(double airDens, double airSpeed, double refArea, double dragC) {
	
	double result = calcDrag(airDens, airSpeed, refArea, dragC);
	printf("\n\tThe total drag is : %.2lf N\n", result);

}

double calcDrag(double airDens, double airSpeed, double refArea, double dragC) {

	return (0.5 * airDens) * (airSpeed * airSpeed) * dragC * refArea;

}