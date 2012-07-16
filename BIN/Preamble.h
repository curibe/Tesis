#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <cstring>
#include <sstream>
#include <cstdlib>
#include <fstream>
#include <typeinfo>
#include <unistd.h>

//#####################
// PRECOMPILATED
//#####################
#define RSOI 1e8


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
