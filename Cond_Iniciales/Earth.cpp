//===========================
// GENERAL
//===========================
#include<vector>
#include<cmath>
#include<fstream>
#include<cstdlib>
#include<iostream>
#include<string>
#include<sstream>
#include<cstring>
#include<iomanip>
#include<algorithm>

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

//=====================================================
//SPICE
//=====================================================
#include <SpiceUsr.h>

#define ABCORR "NONE"//Correction for aberration
#define FRAME  "ECLIPJ2000"
//#define FRAME  "J2000"

//===========================
// LOAD KERNELS
//===========================
// #define SPK1     "/home/cesar/Projects/JUPITER/kernels/020204_SE_JUP199.LONG.bsp"
// #define SPK2     "/home/cesar/Projects/JUPITER/kernels/de405.bsp"
// #define SPK3     "/home/cesar/Projects/JUPITER/kernels/020514_SE_SAT105.bsp"
// #define SPK4     "/home/cesar/Projects/JUPITER/kernels/new-kernels/jup230l.bsp"
// #define SPK5     "/home/cesar/Projects/JUPITER/kernels/new-kernels/de721.bsp"
// #define leap     "/home/cesar/Projects/JUPITER/kernels/naif0009.tls"
// #define leap_ut  "/home/cesar/Projects/JUPITER/kernels/naif0007.tls"
#define SPK1     "../kernels/020204_SE_JUP199.LONG.bsp"
#define SPK2     "../kernels/de405.bsp"
#define SPK3     "../kernels/020514_SE_SAT105.bsp"
#define leap     "../kernels/naif0009.tls"
#define leap_ut  "../kernels/naif0007.tls"
#define t_obs    "19 JUL 2009 15:06:30.00"

//===============================
// CONSTANTES
//===============================
#define M_IO  8.94E22
#define M_ERUOPE  4.8E22
#define M_GANYMEDE  1.48E23
#define M_CALIXTO  1.08E23
#define MJUP  1.9E27
#define HOUR 3600.0
#define DAY 24*HOUR




using namespace std;

int main(int argc, char *argv[])
{

//VARIABLES BASICAS
  double X[6];
  double DeltaT;
  //char tinicial,tfinal,tmin;
  
  // Variables Spice
  SpiceDouble lt;  
  SpiceDouble et,ETF,ET0;
  
  
  // LOAD SPICE KERNELS
  furnsh_c(SPK1);
  furnsh_c(SPK2);
  furnsh_c(SPK3);
  furnsh_c(leap);
  furnsh_c(leap_ut);

  ET0=0.0;
  ETF=2*365.25*86400;
  DeltaT=86400;
  

  for(et=ET0; et<=ETF; et=et+DeltaT)
    {
      spkezr_c("3",et,FRAME,"NONE","10",X,&lt);

      printf("%E  %E  %E  %E  %E  %E  %E\n",et,X[0],X[1],X[2],X[3],X[4],X[5]);
      //printf("t: %f\n",(Timp-Tmin)/120.0);

    }
 

}

