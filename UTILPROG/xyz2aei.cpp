#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <SpiceUsr.h>


int main(int argc,char *argv[])
{
  int i;
  double state[6];
  double Elms[8];
  double et,Mu;

  // IF NUMBER OF PARAMETERS IS LESS 8
  if(argc<8){
    printf("***********ERROR**********\n");
    printf("You must provide 8 values\n");
    printf("**************************\n");
    exit(0);
  }

  for(i=0;i<6;i++){
    state[i]=atof(argv[i+1]);
  }
  et=atof(argv[i+1]);
  Mu=atof(argv[i+2]);
  
  

  //CONVERT STATE TO ELEMENTS
  if(Mu>0){
    oscelt_c(state,et,Mu,Elms);
  }else{
    Elms[0]=Elms[1]=Elms[2]=Elms[3]=Elms[4]=Elms[5]=Elms[6]=Elms[7]=0.0;
  }

  for(i=0;i<8;i++){
    fprintf(stdout,"%e ",Elms[i]);
  }
  fprintf(stdout,"\n");
}
