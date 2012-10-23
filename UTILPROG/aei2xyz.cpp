#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <SpiceUsr.h>

#define RAD2DEG 180.0/M_PI
#define DEG2RAD M_PI/180.0


int main(int argc,char *argv[])
{
  int i;
  double state[6];
  double Elms[8];
  double et;

   // IF NUMBER OF PARAMETERS IS LESS 10
  if(argc<10){
    printf("***********ERROR**********\n");
    printf("You must provide 10 values\n");
    printf("**************************\n");
    exit(0);
  }

  for(i=0;i<8;i++){
    Elms[i]=atof(argv[i+1]);
    //ANGLES IN RADIANS
    if(i>=2 && i<=5)
      Elms[i]*=DEG2RAD;
  }
  
  et=atof(argv[i+1]);

  if(Elms[0]>0){
    conics_c(Elms,et,state);
  }else{
    state[0]=state[1]=state[2]=state[3]=state[4]=state[5]=0.0;
  }

  for(i=0;i<6;i++){
    fprintf(stdout,"%e ",state[i]);
  }
  fprintf(stdout,"\n");

}
    
