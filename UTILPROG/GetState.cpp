#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <math.h>
#include <iostream>
#include <cstring>
#include <sstream>
#include <cstdlib>
#include <fstream>
#include <typeinfo>
#include <unistd.h>
#include <vector>

using namespace std;

//===============
// SPICE
//==============
#include <SpiceUsr.h>
#define ABCORR "NONE"//Correction for aberration
#define FRAME  "ECLIPJ2000"
//Define kernels location
#define SPK1     "../kernels/020204_SE_JUP199.LONG.bsp"
#define SPK2     "../kernels/de405.bsp"
#define SPK3     "../kernels/020514_SE_SAT105.bsp"
#define leap     "../kernels/naif0009.tls"
#define leap_ut  "../kernels/naif0007.tls"


typedef struct 
{
  string Name;
  string ID;
}Body;


int main(int argc,char *argv[])
{

  
  Body Planet[10];
  char *OBSERVER,*TARGET;
  int i,j;
  SpiceDouble et,X[6],lt;

  // Settxsing Bodies
  Planet[0].Name="MERCURY";        Planet[0].ID="199";
  Planet[1].Name="VENUS";          Planet[1].ID="299";
  Planet[2].Name="EARTH";          Planet[2].ID="399";
  Planet[3].Name="MOON";           Planet[3].ID="301";
  Planet[4].Name="MARS";           Planet[4].ID="499";
  Planet[5].Name="JUPITER";        Planet[5].ID="599";
  Planet[6].Name="SATURN";         Planet[6].ID="699";
  Planet[7].Name="URANUS";         Planet[7].ID="799";
  Planet[8].Name="NEPTUNO";        Planet[8].ID="899";
  Planet[9].Name="SUN";            Planet[9].ID="10";
  
  //Load Spice kernels
  furnsh_c(SPK1);
  furnsh_c(SPK2);
  furnsh_c(SPK3);
  furnsh_c(leap);
  furnsh_c(leap_ut);
  
  
  OBSERVER=argv[1];
  TARGET=argv[2];
  et=atof(argv[3]);
 
  //printf("set xrange[-0.3:0.3]\n");
  for(i=0;i<=9;i++){
    for(j=0;j<=9;j++){
      if(!strcmp(OBSERVER,Planet[i].Name.c_str()) && !strcmp(TARGET,Planet[j].Name.c_str())){
	//printf("(i,j):(%d,%d)    Obs: %s    ObsID: %s        Tg: %s    TgID: %s\n",i,j,Planet[i].Name,
	//Planet[i].ID,Planet[j].Name,Planet[j].ID);
      //for(double t=et;t<=365.25*86400;t=t+86400.0){
	spkezr_c(Planet[j].ID.c_str(),et,FRAME,ABCORR,Planet[i].ID.c_str(),X,&lt);
	//printf("splot \"<echo \'%E %E %E\'\" w p pt 7 lc 3 \n",X[0],X[1],X[2]);
	//printf("%E %E %E\n",X[0],X[1],X[2]);
	
	break;
      }
    }
  }
  
  for(i=0;i<6;i++){
  printf("%lf ",X[i]);
  }
  printf("\n");
  
  
  return (0);
}
