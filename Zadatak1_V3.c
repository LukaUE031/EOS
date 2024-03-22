#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include <unistd.h>

#define FILENAME_SIZE 1024
#define MAX_LINE 2048

int izbor=-1;

//Izgled menija
void printMeni(){
printf("Meni:\n\n");
printf("1.Unos kombinacija\n");
printf("2.Prikaz kombinacije\n");
printf("3.Brisanje kombinacije\n");
printf("4.Izlaz\n");
}


//Citanje vrednosti sa tastera
int Taster(){
FILE *fp;
char *str;
char tval1,tval2,tval3,tval4,cond=0;
size_t num_of_bytes = 6;
int button_new=0,button_old=0;
int flag=0;
while(1){

fp = fopen ("/dev/button", "r");
if(fp==NULL) {
puts("Problem pri otvaranju /dev/button");
return -1;
}
str = (char *)malloc(num_of_bytes+1);
getline(&str, &num_of_bytes, fp);
if(fclose(fp)){
puts("Problem pri zatvaranju /dev/button");
return -1;
}
if (str[5]-48 ==1)
		cond=1;
else if (str[4]-48 ==1)
	cond=2;
else 
	cond=0;
	free(str);
	
button_new=cond;
if(button_new!=button_old){
if(button_new==1){
	printMeni();
	flag=1;
}
else if(button_new==2){
	
}	
button_new=button_old;

}	
sleep(1);	
            }
}

//Citanje switch-eva

void Switch(){

	FILE* fp1;
	long int period = 20000L;
	char *str;
	char sval1 = 0,sval2,sval3,sval4;
	size_t num_of_bytes = 6;
int switch_state = 0;	
	
	
fp1 = fopen ("/dev/switch", "r");
		if(fp1==NULL)
		{
			puts("Problem pri otvaranju /dev/switch");
			exit(1);
		}


		str = (char *)malloc(num_of_bytes+1); 
		getline(&str, &num_of_bytes, fp1); 

		if(fclose(fp1))
		{
			puts("Problem pri zatvaranju /dev/switch");
			exit(1);
		}


		sval1 = str[2] - 48;
		sval2 = str[3] - 48;
		sval3 = str[4] - 48;
		sval4 = str[5] - 48;
		free(str);

		switch_state = 0;
		if (sval4 == 1)
			switch_state += 1;
		if (sval3 == 1)
			switch_state += 2;
		if (sval2 == 1)
			switch_state += 4;


}

//Unos zeljenih kombinacija
void napisiKombinaciju(){
FILE* unos;
unos =fopen("input_kombinacije.txt","w");
int b;
for(int i=0;i<16;i++){
printf("Napisite zeljenu kombinaciju: 0x");
scanf("%x",&b);
fprintf(unos,"0x%x\n",b);
    	}
printf("Popunjen ulazni fajl\n");
fclose(unos);
	
return;
	
}

//Prikazivanje kombinacije
int  prikaziKombinaciju(){
	FILE *fp;
	char filename[FILENAME_SIZE];
  	char buffer[MAX_LINE];
	
	int read_line = 0;
	
	
	printf("Kombinacija: ");
  	scanf("%d", &read_line);
	
	 fp = fopen("input_kombinacije.txt", "r");
	
	if (fp == NULL)
  {
    printf("Error opening file.\n");
    return 1;
  }
	
	bool keep_reading = true;
  int current_line = 1;
  do 
  {
    fgets(buffer, MAX_LINE, fp);

    if (feof(fp))
    {
      keep_reading = false;
      printf("File %d lines.\n", current_line-1);
      printf("Couldn't find line %d.\n", read_line);
    }
    else if (current_line == read_line)
    {
      keep_reading = false;
      printf("Kombinacija:%s\n", buffer);
    }

    current_line++;

  } while (keep_reading);

  fclose(fp);
}

int main(int argc,char** argv){

printMeni();

int flag=1;
int stanje=0;
while(flag){
printf("\nIzaberite opciju iz menija: ");
scanf("%d",&izbor);


switch(izbor){
	case 1:
		printf("Unos kombinacija\n");
		napisiKombinaciju();
		Taster();
	break;
	
	case 2:
		printf("Prikaz kombinacija\n");
		Switch();
		Taster();
	break;
	
	case 3:
		printf("Brisanje kombinacije\n");
	prikaziKombinaciju();
		
		
	break;
	
	case 4:
		printf("Izlaz\n\n");
		flag=0;	
	break;			
		
		default:
		printf("Netacan unos!\n");
		break;	

		}

	}
	




	
return 0;

}

