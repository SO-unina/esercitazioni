#ifndef _P_H_
#define _P_H_

#define P1 1
#define P2 2

#define FTOK_PATH_Q  "."
#define FTOK_CHAR_Q 'a'


struct msg_calc{
	long processo;
	float numero;
};

//Genera un valore float nell'intervallo [i_dx,i_sx]
float generaFloat(int i_dx,int i_sx);

#endif // _P_H_
