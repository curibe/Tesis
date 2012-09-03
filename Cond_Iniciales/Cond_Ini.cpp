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
  double Rje,Xjup[6],Xio[6],Xeur[6],Xgan[6],Xcal[6],Xsun[6],Xsat[6];
  double DeltaT,Timp;
  //char tinicial,tfinal,tmin;
  
  // Variables Spice
  SpiceDouble lt;  
  SpiceDouble et,ETF,ET0,Tmin,ET_obs;
  SpiceDouble step;
  
  //OUTPUT FILE
  ofstream JupPos,IoPos,EuPos,GanPos,CaPos,SunPos,SatPos;
  
  
  //  ConstSpiceChar *t_obs="19 JUL 2009 15:06:30.000";
  ConstSpiceChar *tinicial="19 JUL 2009 11:00:00.000";
  //ConstSpiceChar *tfinal="19 MAY 2009 00:00:00.000";
  ConstSpiceChar *tfinal=argv[1];
  //   ConstSpiceChar *tmin="19 JUL 2009 09:00:00.000";
  ConstSpiceChar *tmin="19 JUL 2009 09:00:00.000";

  
  
  
  // LOAD SPICE KERNELS
  furnsh_c(SPK1);
  furnsh_c(SPK2);
  furnsh_c(SPK3);
  furnsh_c(leap);
  furnsh_c(leap_ut);



  str2et_c (tinicial,&ET0);
  str2et_c (tfinal,&ETF);
  str2et_c (t_obs,&ET_obs);
  str2et_c (tmin,&Tmin);

  
  //********************************
  // OUTPUT FILE
  //********************************
  JupPos.open("JupiterPos.dat");
  JupPos.setf(ios::scientific);
  JupPos.setf(ios::showpoint);
  JupPos.precision(15);

  IoPos.open("Io.pos");
  IoPos.setf(ios::scientific);
  IoPos.setf(ios::showpoint);
  IoPos.precision(15);

  EuPos.open("Europa.pos");
  EuPos.setf(ios::scientific);
  EuPos.setf(ios::showpoint);
  EuPos.precision(15);

  GanPos.open("Ganymede.pos");
  GanPos.setf(ios::scientific);
  GanPos.setf(ios::showpoint);
  GanPos.precision(15);

  CaPos.open("Calixto.pos");
  CaPos.setf(ios::scientific);
  CaPos.setf(ios::showpoint);
  CaPos.precision(15);

  SatPos.open("Saturn.pos");
  SatPos.setf(ios::scientific);
  SatPos.setf(ios::showpoint);
  SatPos.precision(15);

  SunPos.open("Sun.pos");
  SunPos.setf(ios::scientific);
  SunPos.setf(ios::showpoint);
  SunPos.precision(15);



  // Delta de Tiempo
  //double delta=(ET0-Tmin)/60.0; // 120 segundos
  double delta;
  delta=atof(argv[2]);

  cout.setf(ios::scientific);
  cout.setf(ios::showpoint);	
  cout.precision(15);
  cout<<"#***************************************************************************"<<endl;
  cout<<"CONDICIONES INICIALES\n"<<endl;
  cout<<"TIEMPO INICIAL (ET0):  "<<ET0<<"    FECHA:  "<<tinicial<<endl;
  cout<<"TIEMPO FINAL (ETF):  "<<ETF<<"    FECHA:  "<<tfinal<<endl;
  cout<<"TIEMPO MINIMO (Tmin):  "<<Tmin<<"    FECHA:  "<<tmin<<endl;
  cout<<"TIEMPO DE OBSERVACION (ET_obs):  "<<ET_obs<<"    FECHA:  "<<t_obs<<endl;
  cout<<"DELTA DE TIEMPO (delta):  "<<delta<<" segundos "<<endl;
  cout<<"****************************************************************************\n"<<endl;

  ofstream Datini("TimeIni.txt");
  Datini.setf(ios::scientific);
  Datini.setf(ios::showpoint);
  Datini.precision(8);
  Datini<<"#***************************************************************************"<<"\n"
	<<"#CONDICIONES INICIALES TEMPORALES\n"
	<<"#***************************************************************************"<<"\n\n"
	<<"#-------------------------------------------------"<<"\n"
	<<"#TIEMPO INICIAL (ET0),    FECHA:  "<<tinicial<<"\n"
	<<"#-------------------------------------------------"<<"\n"
	<<ET0<<"\n\n"
	<<"#-------------------------------------------------"<<"\n"
	<<"#TIEMPO FINAL (ETF),    FECHA:  "<<tfinal<<"\n"
	<<"#-------------------------------------------------"<<"\n"
	<<ETF<<"\n\n"
	<<"#-------------------------------------------------"<<"\n"
	<<"#TIEMPO MINIMO (Tmin),    FECHA:  "<<tmin<<"\n"
	<<"#-------------------------------------------------"<<"\n"
	<<Tmin<<"\n\n"
	<<"#-------------------------------------------------"<<"\n"
	<<"#TIEMPO DE OBSERVACION (ET_obs),    FECHA:  "<<t_obs<<"\n"
	<<"#-------------------------------------------------"<<"\n"
	<<ET_obs<<"\n\n"
	<<"#-------------------------------------------------"<<"\n"
	<<"#DELTA DE TIEMPO (delta) _segundos_ "<<"\n"
	<<"#-------------------------------------------------"<<"\n"
	<<delta<<endl;

  Datini.close();

  for(Timp=Tmin; Timp<=ET0; Timp=Timp+delta)
    {
      spkezr_c("399",Timp,FRAME,"NONE","599",Xjup,&lt);
      spkezr_c("501",Timp,FRAME,"NONE","599",Xio,&lt);
      spkezr_c("502",Timp,FRAME,"NONE","599",Xeur,&lt);
      spkezr_c("503",Timp,FRAME,"NONE","599",Xgan,&lt);
      spkezr_c("504",Timp,FRAME,"NONE","599",Xcal,&lt);
      spkezr_c("10",Timp,FRAME,"NONE","599",Xsun,&lt);
      spkezr_c("6",Timp,FRAME,"NONE","599",Xsat,&lt);

      JupPos<<Timp<<setw(25)<<Xjup[0]<<setw(25)<<Xjup[1]<<setw(25)<<Xjup[2]<<setw(25)
	    <<Xjup[3]<<setw(25)<<Xjup[4]<<setw(25)<<Xjup[5]<<endl;

      IoPos<<Timp<<setw(25)<<Xio[0]<<setw(25)<<Xio[1]<<setw(25)<<Xio[2]<<setw(25)
	    <<Xio[3]<<setw(25)<<Xio[4]<<setw(25)<<Xio[5]<<endl;
      
      EuPos<<Timp<<setw(25)<<Xeur[0]<<setw(25)<<Xeur[1]<<setw(25)<<Xeur[2]<<setw(25)
	    <<Xeur[3]<<setw(25)<<Xeur[4]<<setw(25)<<Xeur[5]<<endl;

      GanPos<<Timp<<setw(25)<<Xgan[0]<<setw(25)<<Xgan[1]<<setw(25)<<Xgan[2]<<setw(25)
	    <<Xgan[3]<<setw(25)<<Xgan[4]<<setw(25)<<Xgan[5]<<endl;

      CaPos<<Timp<<setw(25)<<Xcal[0]<<setw(25)<<Xcal[1]<<setw(25)<<Xcal[2]<<setw(25)
	    <<Xcal[3]<<setw(25)<<Xcal[4]<<setw(25)<<Xcal[5]<<endl;

      SunPos<<Timp<<setw(25)<<Xsun[0]<<setw(25)<<Xsun[1]<<setw(25)<<Xsun[2]<<setw(25)
	    <<Xsun[3]<<setw(25)<<Xsun[4]<<setw(25)<<Xsun[5]<<endl;

      SatPos<<Timp<<setw(25)<<Xsat[0]<<setw(25)<<Xsat[1]<<setw(25)<<Xsat[2]<<setw(25)
	    <<Xsat[3]<<setw(25)<<Xsat[4]<<setw(25)<<Xsat[5]<<endl;

      //printf("t: %f\n",(Timp-Tmin)/120.0);

    }
 
  JupPos.close();
  IoPos.close();
  EuPos.close();
  GanPos.close();
  CaPos.close();
  SunPos.close();
  SatPos.close();
}

