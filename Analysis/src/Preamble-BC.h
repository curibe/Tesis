#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <cstring>
#include <sstream>
#include <cstdlib>
#include <fstream>
#include <typeinfo>
#include <unistd.h>
#include <vector>

//#####################
// PRECOMPILATED
//#####################
#define HOURS 3600.0
#define DAYS 86400.0
#define YEARS 31557600.0 // seconds
#define AU 1.49597870700e8
#define UV 1.49597870700e8/86400.0
#define RSOI 4.8305783e7
#define RJUP 71492.0
#define MUSUN 1.328182e+11
#define MUJUP 1.268113e+08
#define IncJ 0.02276  /*In radians.  Inclination of jupiter respect to ecliptic. (1.304 deg)*/
#define aJ 7.7832780168E+08 //5.2028*AU
#define epsilonE 23.45*(M_PI)/180.0
#define RAD2DEG 180.0/M_PI
#define DEG2RAD M_PI/180.0


using namespace std;




/**************************************/
/* This template shows the power of   */
/* C++ templates. This function will  */
/* convert anything to a string!      */
/* Precondition:                      */
/* operator<< is defined for type T    */
/**************************************/
template <class T>
string toString( T argument)
{
       string r;
       stringstream s;
       char str[30];
       
       if(!strcmp(typeid(argument).name(),"d")){
	 sprintf(str,"%.5lf",argument);
	 r=string(str); 
       }//*/
       if(!strcmp(typeid(argument).name(),"i")){
	 s << argument;
	 r = s.str();}
       
       return r;

}
 

//*********************************
// Function that get the output of
// a command ejecution in bash
// using the tool popen
//*********************************
std::string exec(string cmd) {
  FILE* pipe = popen(cmd.c_str(), "r");
  if (!pipe) return "ERROR";
  char buffer[128];
  std::string result = "";
  while(!feof(pipe)) {
    if(fgets(buffer, 128, pipe) != NULL){
      result += buffer; }
    
  }
  pclose(pipe);
  result=result.substr(0,result.length()-1);
  return result;
}



vector<double> Split2F(char* Str){


  char *token;
  vector <double> VecStr;
  //double *Vec;
  int N;
  
  //double VecStr[9];
  token = strtok(Str," \t\n");
  //Str=chain.c_str();
  int i=0;
  
  while(token !=NULL){
    VecStr.push_back(atof(token));
    //VecStr[i]=atof(token);
    token=strtok(NULL," \t\n");
    
    i++;
  }
  
  return VecStr;
  //N=VecStr.size();
  //Vec=(double *)malloc(N*sizeof(double));
  //copy(VecStr.begin(),VecStr.end(),Vec);
    
  /*
  for(int i=0;i<VecStr.size();++i){
    // cout<<"Show vector:\n";
    printf("%E\n",VecStr[i]);
    } */

  
  //return (double*)Vec;
  //free(Vec);
  
       
}

double getSMAxis(double rp, double e){

  double a;
  // FOR ELIPTIC AND HYPERBOLIC ORBITS
  if( e<1 || e>1) { a = fabs(rp/(1-e)); }
  // FOR PARABOLIC ORBITS
  if(fabs(e-1)<=1e-3){ a = rp;}

  return a;

}


double Tisserand(double rp, double e, double I)
{
  double a,p,T;

  //For Ecliptic and Hyperbolic Orbit
  if(e<1.0 || e>1.0)
    {
      a=fabs(rp/(1-e));
      p=rp*(1+e);
      T= aJ/a + 2*sqrt(p/aJ)*cos(IncJ-I);
      return T;
    }
  // For parabolic Orbit
  if(fabs(e-1)<=1e-3)
    {
      a=rp;
      p=2*rp;
      T= aJ/a + 2*sqrt(p/aJ)*cos(IncJ-I);
      return T;
    }
}

int ChangeSR(double St1[7], double St2[7], double x[7]){
  //printf("ROUTINE St1:  %e %e %e %e %e %e %e\n",St1[0],St1[1],St1[2],St1[3],St1[4],St1[5],St1[6]);
  //printf("ROUTINE St2:  %e %e %e %e %e %e %e\n",St2[0],St2[1],St2[2],St2[3],St2[4],St2[5],St2[6]);
  //printf("ROUTINE St1-St2:  %e %e %e %e %e %e %e\n",St1[0],St1[1]-St2[1],St1[2]-St2[2],St1[3]-St2[3],St1[4]-St2[4],St1[5]-St2[5],St1[6]-St2[6]);
  x[0]=St1[0];
  x[1]=St1[1]-St2[1]; 
  x[2]=St1[2]-St2[2]; 
  x[3]=St1[3]-St2[3];
  x[4]=St1[4]-St2[4]; 
  x[5]=St1[5]-St2[5]; 
  x[6]=St1[6]-St2[6];
  //printf("ROUTINE x:  %e %e %e %e %e %e %e\n",x[0],x[1],x[2],x[3],x[4],x[5],x[6]);
  return (0);
}


/************************************************
* This routine make change of units
* The allowed convertions are:
* AU-DAYS: convert from AU,DAYS to km,s
* AU-YEARS: convert from AU,YEARS to km,s
* au-days: convert from km,s to AU,DAYS
**************************************************/
int ChangeUnit(double St[7],char *type,double ST[7]){
  
  if(!strcmp(type,"AU-DAYS")){
    ST[0]=St[0]*DAYS;
    ST[1]=St[1]*AU; ST[2]=St[2]*AU; ST[3]=St[3]*AU;
    ST[4]=St[4]*(AU/DAYS); ST[5]=St[5]*(AU/DAYS); ST[6]=St[6]*(AU/DAYS);
  }
  if(!strcmp(type,"AU-YEARS")){
    ST[0]=St[0]*YEARS;
    ST[1]=St[1]*AU; ST[2]=St[2]*AU; ST[3]=St[3]*AU;
    ST[4]=St[4]*(AU/YEARS); ST[5]=St[5]*(AU/YEARS); ST[6]=St[6]*(AU/YEARS);
  }
  if(!strcmp(type,"au-days")){
    ST[0]=St[0]/DAYS;
    ST[1]=St[1]/AU; ST[2]=St[2]/AU; ST[3]=St[3]/AU;
    ST[4]=St[4]/(AU/DAYS); ST[5]=St[5]/(AU/DAYS); ST[6]=St[6]/(AU/DAYS);
  }
  return (0);

}

int Ecl2Eq(double XECL[7],double XEQ[3]){

  
  //printf("XECL: %E %E %E %E %E %E\n",XECL[0],XECL[1],XECL[2],XECL[3],XECL[4],XECL[5]);
  XEQ[0]=XECL[0];
  XEQ[1]=XECL[1]*cos(epsilonE)-XECL[2]*sin(epsilonE);
  XEQ[2]=XECL[1]*sin(epsilonE)+XECL[2]*cos(epsilonE);
  //printf("XEq(Ecl2Eq): %E %E %E \n",XEQ[0],XEQ[1],XEQ[2]);
  return (0);

}


double Atan(double x,double y)
{

  double r,alpha,theta;
  
  alpha=atan(y/x);
  //Cuadrante I
  theta=alpha;
  
  //Cuadrante II
  if(x<0.0 && y>0.0) theta=M_PI-fabs(alpha);
  
  //Cuadrante III
  if(x<0.0 && y<0.0) theta=M_PI+alpha;
  
  //Cuadrante IV
  if(x>0.0 && y<0.0) theta=2*M_PI-fabs(alpha);
  
  return theta;
  
}
