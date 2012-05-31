/*
CSCC69S12 Assignment 1 - Potion Brewing
*/

#include <stdio.h>
#include <string.h>
#include "array.h"

/* Compile as "gcc -Wall -g -o testarray testarray.c array.c" */

/* Declare and define the potion array type using the macros in array.h*/

/* potionarray declared and defined in array.h
DECLARRAY_BYTYPE(potionarray, struct potion);
DEFARRAY_BYTYPE(potionarray, struct potion, ARRAYINLINE);
*/

static struct stringarray names;  /* Where is the string array type defined? */
static struct potionarray potions;

struct potion {
    char *type;
    int strength;  
};

int main() {
	struct potion *sleep;
	sleep = malloc(sizeof(*sleep));
	sleep->type = "sleep";
	sleep->strength = 5;
	
	struct potion *flying;
	flying = malloc(sizeof(*flying));
	flying->type = "flying";
	flying->strength = 2;
	
	struct potion *invisibility;
	invisibility = malloc(sizeof(*invisibility));
	invisibility->type = "invisibility";
	invisibility->strength = 6;
	
	unsigned numPot;
	numPot = potionarray_num(&potions);

	potionarray_add(&potions, sleep, &numPot);
	potionarray_add(&potions, flying, &numPot);
	potionarray_add(&potions, invisibility, &numPot);
	potionarray_setsize(&potions, numPot);
		
    /* Add 3 potions to the potions array with their corresponding strengths
    * in the following order:
    * sleep 5
    * flying 2
    * invisibility 6
    */
    

    /* ADD CODE HERE */
    

	/* Iterate over and print the type and efficacy of each potion,
	 * one potion per line  */
	/* For full marks, get the size of the array from the array code rather
	 * than just using the value 3.
	 */
	 
	 /* ADD CODE HERE */
	int i;
	i = 0;
	while( i <= potionarray_num(&potions))
	{
		struct potion p = *potionarray_get(&potions, i);
		printf("Potion at %d is %s with strength %d\n", i, p.type,p.strength);
		i++;
     	}
     
	 /*Use the following line to print the results to stdout (so we can
	  * automatically check the results)
	      printf("Potion at %d is %s with strength %d\n", ?, ?,?);
     */

    

	/* Initialize the names array and add the following strings to the array:
	 * "Linux", "NetBSD"
    */
    
    /* ADD CODE HERE */
	names = *stringarray_create();
	unsigned numN = stringarray_num(&names);
	stringarray_add(&names,"Linux",&numN);
	stringarray_add(&names,"NetBSD",&numN);
	stringarray_setsize(&names, numN);


	/* Iterate over and print the contents of the array names one element
	 * per line.  (Print only the strings and no extra text.)
	 */
	 printf("The contents of the names array:\n");
 	
    /* ADD CODE HERE */
	i = 0;
	while(i <= stringarray_num(&names))
	{
		printf("%s\n",stringarray_get(&names, i));
		i++;
	}
	return 0;
}

