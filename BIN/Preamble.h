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
#define DAYS 24*HOURS
#define YEARS 365.25*DAYS
#define AU 1.49597870700e8 
#define RSOI 4.8305783e7
#define RJUP 71492.0
#define MUSUN 1.328182e+11
#define MUJUP 1.268113e+08
#define IncJ 0.02276  /*In radians.  Inclination of jupiter respect to ecliptic. (1.304 deg)*/
#define aJ 5.2028*AU



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



double* Split2F(char* Str){


  char *token;
  vector <double> VecStr;
  double *Vec;
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
  
  N=VecStr.size();
  Vec=(double *)malloc(N*sizeof(double));
  copy(VecStr.begin(),VecStr.end(),Vec);
    
  /*
  for(int i=0;i<VecStr.size();++i){
    // cout<<"Show vector:\n";
    printf("%E\n",VecStr[i]);
    } */

  
  return (double*)Vec;
  free(Vec);
       
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

double* ChangeSR(double St1[7], double St2[7]){

  double x[7];
  
  x[0]=St1[0];
  x[1]=St1[1]-St2[1]; x[2]=St1[2]-St2[2]; x[3]=St1[3]-St2[3];
  x[4]=St1[4]-St2[4]; x[3]=St1[5]-St2[5]; x[6]=St1[6]-St2[6];
  return (double *)x;
}

double* ChangeUnit(double St[7],char *type){
  
  if(!strcmp(type,"AU-DAYS")){
    St[0]*=DAYS;
    St[1]*=AU; St[2]*=AU; St[3]*=AU;
    St[4]*=AU/DAYS; St[5]*=AU/DAYS; St[6]*=AU/DAYS;
  }
  if(!strcmp(type,"AU-YEARS")){
    St[0]*=YEARS;
    St[1]*=AU; St[2]*=AU; St[3]*=AU;
    St[4]*=AU/YEARS; St[5]*=AU/YEARS; St[6]*=AU/YEARS;
  }
  return (double *)St;

}
