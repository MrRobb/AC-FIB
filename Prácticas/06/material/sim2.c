//Created by Solde
#include "CacheSim.h"
 
/* Posa aqui les teves estructures de dades globals
 * per mantenir la informacio necesaria de la cache
 * */

#define read 0
#define write 1

typedef struct{
	int data
	int v;
	int d;
} CacheLine;
 
#define cacheSize 128

CacheLine cache[cacheSize]; // cache de 128 bloques con dirty bit
 
/* La rutina init_cache es cridada pel programa principal per
 * inicialitzar la cache.
 * La cache es inicialitzada al començar cada un dels tests.
 * */
 
void init_cache ()
{ 
	int i;
	for(i = 0; i < 128; ++i) {
		cache[i].v = 0;
		cache[i].d = 0;
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
		aux = aux / 32;
		bloque_m = aux & 134217727;
		linea_mc = aux & 127;
		aux = aux/128;
		tag = aux & 1048575;
		tag_out = -1;
 
		if (LE == read) { //read
			if (cache[linea_mc].v == 0) { //miss and no replacement
				cache[linea_mc].data = tag;
				miss = 1;
				replacement = 0;
				lec_mp = 1;
				mida_lec_mp = 32;
				esc_mp = 0;
				mida_esc_mp = 0;
			}
			else if (cache[linea_mc].data != tag) { //miss and replacement
				tag_out = cache[linea_mc].data;
				cache[linea_mc].data = tag;
				miss = 1;
				replacement = 1;
				lec_mp = 1;
				mida_lec_mp = 32;
				if (cache[linea_mc].d == 0) {
					esc_mp = 0;
					mida_esc_mp = 0;
				}
				else { //d = 1
					cache[linea_mc].d = 0;  
					esc_mp = 1;
					mida_esc_mp = 32;
				}
			}
			else { //hit
				miss = 0;
				replacement = 0;
				lec_mp = 0;
				mida_lec_mp = 0;
				esc_mp = 0;
				mida_esc_mp = 0;
			}
		}
 
		else { //write
			if (cache[linea_mc].v == 0) { //miss and no replacement
				cache[linea_mc].data = tag;
				cache[linea_mc].d = 1;
				cache[linea_mc].v = 1;
				miss = 1;
				replacement = 0;
				lec_mp = 1;
				mida_lec_mp = 32;
				esc_mp = 0;
				mida_esc_mp = 0;
			}
 
			else if (cache[linea_mc].data != tag) { //miss and replacement
				tag_out = cache[linea_mc].data;
				cache[linea_mc].data = tag;
				cache[linea_mc].d = 1;
				miss = 1;
				replacement = 1;
				lec_mp = 1;
				mida_lec_mp = 32;
			
				if (cache[linea_mc].d == 0) {
				cache[linea_mc].d = 1;
				esc_mp = 0;
				mida_esc_mp = 0;
				}
 
				else { // DB = 1
					cache[linea_mc].DB = 1;
					esc_mp = 1;
					mida_esc_mp = 32;
				}
		  	}
	
			else{ //hit
				miss = 0;
				replacement = 0;
				lec_mp = 0;
				mida_lec_mp = 0;
				esc_mp = 0;
				mida_esc_mp = 0;	
				cache[linea_mc].d = 1;
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
 
void final ()
{
		/* Escriu aqui el teu codi */  
}
