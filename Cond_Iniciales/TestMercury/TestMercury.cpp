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
#define SPK1     "/home/cesar/Projects/JUPITER/kernels/020204_SE_JUP199.LONG.bsp"
#define SPK2     "/home/cesar/Projects/JUPITER/kernels/de405.bsp"
#define SPK3     "/home/cesar/Projects/JUPITER/kernels/020514_SE_SAT105.bsp"
#define SPK4     "/home/cesar/Projects/JUPITER/kernels/new-kernels/jup230l.bsp"
#define SPK5     "/home/cesar/Projects/JUPITER/kernels/new-kernels/de721.bsp"
#define leap     "/home/cesar/Projects/JUPITER/kernels/naif0009.tls"
#define leap_ut  "/home/cesar/Projects/JUPITER/kernels/naif0007.tls"
#define t_obs    "19 JUL 2009 15:06:30.00"


#define MJ 1.899E27
#define Gconst 6.67428E-20
#define HOUR 3600.0
#define DAY 24*HOUR
#define YEAR 365.0*DAY
#define UA 1.496E8
#define MSUN 1.9891E30
#define MUSUN 1.328182e+11
#define MUJup Gconst*MJ
#define stp HOUR/DAY
#define a 1000.0
#define b 100.0
#define c a*b
#define d a/b


using namespace std;

int main()
{

  double Xg[6],Xe[6],Xio[6],Xc[6];
  double elmsI[8],elmsE[8],elmsG[8],elmsC[8];
  double aI;

  // Variables Spice
  SpiceDouble lt;  
  SpiceDouble et,ET,ET0,STEP,TEND;
  SpiceDouble step;


  ofstream IoPos;
  ofstream EPos;
  ofstream GPos;
  ofstream CPos;
  ofstream INIpos;

  // LOAD SPICE KERNELS
  furnsh_c(SPK1);
  furnsh_c(SPK2);
  furnsh_c(SPK3);


  IoPos.open("IoPos.dat");
  EPos.open("EPos.dat");
  GPos.open("GPos.dat");
  CPos.open("CPos.dat");
  INIpos.open("INIopen.dat");
  ofstream ElmsIo("Io.aei");


  // ********************************
  // INITIAL CONDITIONS
  // ********************************

  ET0=0.0;
  STEP=1.0*HOUR;
  TEND=1.5*DAY;
  double day=24.0*HOUR;
  
  cout<<"HOUR: "<<HOUR<<"   DAY: "<<DAY<<"  day: "<<day<<endl;
  cout<<"STEP: "<<STEP<<"   TEND: "<<TEND<<endl;
  cout<<"86400/DAY: "<<8640.0/DAY<<endl;
  cout<<"3600/HOUR: "<<3600.0/HOUR<<endl;
  cout<<"stp: "<<stp<<endl;
  cout<<"******************\n"
      <<"a: "<<a<<"    b: "<<b<<"    c: "<<c<<"    d: "<<d<<endl;

  // INITIAL STATE VECTOR
  spkezr_c("501",ET0,FRAME,"NONE","599",Xio,&lt);
  spkezr_c("502",ET0,FRAME,"NONE","599",Xe,&lt);
  spkezr_c("503",ET0,FRAME,"NONE","599",Xg,&lt);
  spkezr_c("504",ET0,FRAME,"NONE","599",Xc,&lt);


  // ORBITAL ELEMENTS
  oscelt_c (Xio,ET0,MUJup,elmsI);
  oscelt_c (Xe,ET0,MUJup,elmsE);
  oscelt_c (Xg,ET0,MUJup,elmsG);
  oscelt_c (Xc,ET0,MUJup,elmsC);

  aI=elmsI[0]/(1-elmsI[1]);

  // Xio[0]=Xio[0]/UA; Xio[1]=Xio[1]/UA; Xio[2]=Xio[2]/UA;
  // Xio[3]=Xio[3]/UA; Xio[4]=Xio[4]/UA; Xio[5]=Xio[5]/UA;


  IoPos.setf(ios::scientific);
  IoPos.setf(ios::showpoint);
  IoPos.precision(8);
  EPos.setf(ios::scientific);
  EPos.setf(ios::showpoint);
  EPos.precision(8);
  GPos.setf(ios::scientific);
  GPos.setf(ios::showpoint);
  GPos.precision(8);
  CPos.setf(ios::scientific);
  CPos.setf(ios::showpoint);
  CPos.precision(8);
  ElmsIo.setf(ios::scientific);
  ElmsIo.setf(ios::showpoint);
  ElmsIo.precision(8);


  INIpos.setf(ios::scientific);
  INIpos.setf(ios::showpoint);
  INIpos.precision(8);
  INIpos<<ET0<<setw(20)<<Xio[0]<<setw(20)<<Xio[1]<<setw(20)<<Xio[2]<<setw(20)
	<<Xio[3]<<setw(20)<<Xio[4]<<setw(20)<<Xio[5]<<"\n"
	<<ET0<<setw(20)<<Xe[0]<<setw(20)<<Xe[1]<<setw(20)<<Xe[2]<<setw(20)
	<<Xe[3]<<setw(20)<<Xe[4]<<setw(20)<<Xe[5]<<"\n"
	<<ET0<<setw(20)<<Xg[0]<<setw(20)<<Xg[1]<<setw(20)<<Xg[2]<<setw(20)
	<<Xg[3]<<setw(20)<<Xg[4]<<setw(20)<<Xg[5]<<"\n"
	<<ET0<<setw(20)<<Xc[0]<<setw(20)<<Xc[1]<<setw(20)<<Xc[2]<<setw(20)
	<<Xc[3]<<setw(20)<<Xc[4]<<setw(20)<<Xc[5]<<endl;
  INIpos<<"\n"<<endl;
  INIpos<<ET0<<setw(20)<<aI<<setw(20)<<elmsI[1]<<setw(20)<<elmsI[2]<<setw(20)
	<<elmsI[3]<<setw(20)<<elmsI[4]<<setw(20)<<elmsI[5]<<setw(20)<<elmsI[6]<<setw(20)<<elmsI[7]<<"\n"
	<<ET0<<setw(20)<<elmsE[0]<<setw(20)<<elmsE[1]<<setw(20)<<elmsE[2]<<setw(20)
	<<elmsE[3]<<setw(20)<<elmsE[4]<<setw(20)<<elmsE[5]<<setw(20)<<elmsE[6]<<setw(20)<<elmsE[7]<<"\n"
	<<ET0<<setw(20)<<elmsG[0]<<setw(20)<<elmsG[1]<<setw(20)<<elmsG[2]<<setw(20)
	<<elmsG[3]<<setw(20)<<elmsG[4]<<setw(20)<<elmsG[5]<<setw(20)<<elmsG[6]<<setw(20)<<elmsG[7]<<"\n"
	<<ET0<<setw(20)<<elmsC[0]<<setw(20)<<elmsC[1]<<setw(20)<<elmsC[2]<<setw(20)
	<<elmsC[3]<<setw(20)<<elmsC[4]<<setw(20)<<elmsC[5]<<setw(20)<<elmsC[6]<<setw(20)<<elmsC[7]<<endl;

  INIpos.close();

  double dt;
  for( ET=ET0;ET<=TEND;ET=ET+STEP)
    {
      spkezr_c("501",ET,FRAME,"NONE","599",Xio,&lt);
      spkezr_c("502",ET,FRAME,"NONE","599",Xe,&lt);
      spkezr_c("503",ET,FRAME,"NONE","599",Xg,&lt);
      spkezr_c("504",ET,FRAME,"NONE","599",Xc,&lt);

      IoPos<<ET<<setw(20)<<Xio[0]/UA<<setw(20)<<Xio[1]/UA<<setw(20)<<Xio[2]/UA<<setw(20)
	   <<Xio[3]/UA<<setw(20)<<Xio[4]/UA<<setw(20)<<Xio[5]/UA<<endl;
      EPos<<ET<<setw(20)<<Xe[0]<<setw(20)<<Xe[1]<<setw(20)<<Xe[2]<<setw(20)
	   <<Xe[3]<<setw(20)<<Xe[4]<<setw(20)<<Xe[5]<<endl;
      GPos<<ET<<setw(20)<<Xg[0]<<setw(20)<<Xg[1]<<setw(20)<<Xg[2]<<setw(20)
	   <<Xg[3]<<setw(20)<<Xg[4]<<setw(20)<<Xg[5]<<endl;
      CPos<<ET<<setw(20)<<Xc[0]<<setw(20)<<Xc[1]<<setw(20)<<Xc[2]<<setw(20)
	   <<Xc[3]<<setw(20)<<Xc[4]<<setw(20)<<Xc[5]<<endl;

      oscelt_c (Xio,ET,MUJup,elmsI);
      aI=elmsI[0]/(1-elmsI[1]);
      aI=aI/UA;
      dt=ET/day;
      cout<<"ET: "<<ET<<"    DAY: "<<DAY<<"   day: "<<day<<"     ET/day: "<<dt<<"            ET/DAY: "<<ET/DAY<<endl;

      ElmsIo<<dt<<setw(20)<<aI<<setw(20)<<elmsI[1]<<setw(20)<<elmsI[2]<<setw(20)
	    <<elmsI[3]<<setw(20)<<elmsI[4]<<setw(20)<<elmsI[5]<<setw(20)<<elmsI[6]<<setw(20)<<elmsI[7]<<endl;
      
    }

  IoPos.close();
  EPos.close();
  GPos.close();
  CPos.close();
  ElmsIo.close();





}
