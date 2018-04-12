//Created by David Soldevila i Aldo Fuster
#include "CacheSim.h"
#include <stdio.h>

/* Posa aqui les teves estructures de dades globals
 * per mantenir la informacio necesaria de la cache
 * */

#define read 0
#define write 1

unsigned MissCounter = 0, HitCounter = 0;

typedef struct{
	int data;
	int v;
} CacheLine;

#define cacheSize 128

CacheLine cache[cacheSize];


/* La rutina init_cache es cridada pel programa principal per
 * inicialitzar la cache.
 * La cache es inicialitzada al comen�ar cada un dels tests.
 * */
void init_cache ()
{
    int i;
	for(i = 0; i < cacheSize; ++i){
		cache[i].v = 0;
	}
}

/* La rutina reference es cridada per cada referencia a simular */ 
void reference (unsigned int address, unsigned int LE)
{
	unsigned int byte;
	unsigned int bloque_m; 
	unsigned int linea_mc;
	unsigned int tag;
	unsigned int miss;
	unsigned int lec_mp;
	unsigned int mida_lec_mp;
	unsigned int esc_mp;
	unsigned int mida_esc_mp;
	unsigned int replacement;
	unsigned int tag_out;

	unsigned int aux = address;
	byte = aux & 31;
	aux= aux/32;
	bloque_m = aux& 134217727;
	linea_mc = aux& 127;
	aux= aux/128;
	tag = aux& 1048575;
	tag_out = -1;
    
    miss = 0;
    //miss = (LE==read && (cache[linea_mc].v == 0) || (cache[linea_mc].v == 1 && cache[linea_mc].data != tag)) || (LE==write && (cache[linea_mc].v == 0  || cache[linea_mc].data != tag));
    miss = cache[linea_mc].v == 0 || cache[linea_mc].data != tag;
    
    replacement = 0;
    replacement = miss && (LE == read &&(cache[linea_mc].v == 1 && cache[linea_mc].data != tag));
 
	if (LE == read) { //read
        ++MissCounter;
		esc_mp = 0;
		mida_esc_mp = 0;
		if (cache[linea_mc].v == 0) { // miss and no replacement
            cache[linea_mc].data = tag;
            cache[linea_mc].v = 1;
            lec_mp = 1;
            mida_lec_mp = 32;
        }
		
		else if (cache[linea_mc].data != tag) { // miss and replacement
            ++MissCounter;
            tag_out = cache[linea_mc].data;
            cache[linea_mc].data = tag;
            lec_mp = 1; 
            mida_lec_mp = 32;
		}
		
		else { // hit
            ++HitCounter;
            lec_mp = 0;
            mida_lec_mp = 0;
		}
	}

	else { //LE == write
		lec_mp = 0;
		mida_lec_mp = 0;
		esc_mp = 1;
		mida_esc_mp = 1;
		if ((cache[linea_mc].v == 0) || (cache[linea_mc].data != tag)){ // miss
            ++MissCounter;
        }
		else{ // hit
            ++HitCounter;
        }
	}

	/* La funcio test_and_print escriu el resultat de la teva simulacio
	 * per pantalla (si s'escau) i comproba si hi ha algun error
	 * per la referencia actual
	 * */
	test_and_print (address, LE, byte, bloque_m, linea_mc, tag,
			miss, lec_mp, mida_lec_mp, esc_mp, mida_esc_mp,
			replacement, tag_out);
}

/* La rutina final es cridada al final de la simulacio */ 
void final (){
    printf("Miss Counter = %u | Hit Counter = %u\n", MissCounter, HitCounter);
}
