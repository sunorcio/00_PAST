/* meant for quick language tests, complex tests get their own folder */
/* do not delete tests, name or comment them */




#include <stdio.h>




#define STR_(X) #X
#define STR(X) STR_(X)
#define astring "10"
#define aliteral 10
void literaltostringmacro(){
	printf("%"STR(aliteral)"f",100.123);
}




void stringdeclarationinmemory(){
	char* asdf[] = {"sdfa","asdf"};
	{unsigned int i;
	for(i = 0;i<10;i++){
		printf("%d\n",asdf[0][i]);	
	}}
}




void arrayofarrayslayout(void){

	int asdff[2][8] = {0};
	int* asdf = asdff[0];


	{unsigned int i;
	for(i = 0;i<2;i++){
		{unsigned int j;
		for(j = 0;j<8;j++){
			asdff[i][j] = j;
		}}
	}}

	{unsigned int i;
	for(i = 0;i<16;i++){
		printf("%d\n",asdf[i]);
	}}
}




void endiantest(void){
	unsigned long asdf = 0x000000000000bcfa;

	printf("%lx\n",asdf);
	printf("%x\n",*(((unsigned char *)&asdf)+1) );
}




struct structassign{
	int asdf;
	int asdff;
}assignstruct = {0};

void struct_assignment(void){
	struct structassign asdf;

	asdf = assignstruct;
}




int main(void){
	
	arrayofarrayslayout();
}
