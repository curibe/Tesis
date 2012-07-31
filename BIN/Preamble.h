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
#define YEARS=365.25*DAYS
#define AU 1.49597870700e8 
#define RSOI 4.8305783e7
#define RJUP 71492.0


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

       s << argument;
       r = s.str();

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



double* SplitToF(char* Str){


  char *token;
  
  printf("String: %s \n",Str);
  
  //vector <double> VecStr;
  double VecStr[9];
  token = strtok(Str," \t\n");
  //Str=chain.c_str();
  int i=0;
  while(token !=NULL){
    //VecStr.push_back(atof(token));
    VecStr[i]=atof(token);
    token=strtok(NULL," \t\n");
    i++;
  }
  
  /*
  for(int i=0;i<VecStr.size();++i){
    // cout<<"Show vector:\n";
    printf("%E\n",VecStr[i]);
    } */
  return (double *) VecStr;
       
}
