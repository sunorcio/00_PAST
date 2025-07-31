#include "asdd.h"




#include <stdio.h>




static struct DAREAL_struct{
	const char asdf[];
}someshi = {"asdf"};


struct INTERFACE_struct getmyshi(void){
	struct INTERFACE_struct asdf;

	asdf.ptrtodareal = &someshi;
	return asdf;
}

void printmashi(struct INTERFACE_struct someshi){
	printf("%s",((struct DAREAL_struct*)someshi.ptrtodareal)->asdf);
}




