#include <time.h>
#include <stdlib.h>

float generaFloat(int i_sx,int i_dx){
	float x = (float) (rand()+i_sx)/(float)(RAND_MAX/i_dx);
	return x;
}
