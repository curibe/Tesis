#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <cstring>
#include <sstream>
#include <cstdlib>
#include <fstream>
#include <typeinfo>

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


//##############################
// MAIN PROGRAM
//##############################
int main(int argc,char *argv[])
{

  FILE *file,*TCapture;
  
  int Ndir,i;

  double Tini,State[6],Time,Distance,Tcapture;
  
  string S="other string";
  string Principal,r,cmd;
  string Rundir,Bindir;
  //string Rundir("/RUNDIR/");
  //string Bindir("/BIN/");
  string Rdir;
  string File="BODY7.pos";
  string Fdump="Comet.pos";
  string Nl,NameF;
    
  char* CMD;
  

  //*******************
  // PATHS
  //*******************
  Principal=exec("pwd");
  Rundir=Principal+"/RUNDIR/";
  Bindir=Principal+"/BIN";
  
  // Read the total number of runs
  cmd="ls -d "+Rundir+"* | wc -l";
  r=exec(cmd);
  Ndir=atoi(r.c_str());
  
  printf("path: %s\n",Principal.c_str());
  printf("rundir: %s\n",Rundir.c_str());
  printf("cmd: %s\n",cmd.c_str());
  printf("Ndir: %d\n",Ndir);

  // Headfile of the text file with the capture time
  //==================================================
  TCapture = fopen("Capture.txt","a");
  fprintf(TCapture,"# Time Capture         Run\n");
  fprintf(TCapture,"#------------------------------------");
  fclose(TCapture);

  string Dir,Desc;
  int nl;
  
  for(i=1;i<=Ndir;i++){

    //Path of folder output in each run directories
    // Path of the Description file
    Dir=Rundir+"run"+toString(i)+"/output/";
    Desc=Rundir+"run"+toString(i)+"/Description.txt";
    
    cmd="wc -l " + Dir + File + "| gawk '{print $1}'";
    Nl=exec(cmd);
    nl=atoi(Nl.c_str());
    
    // Creating a dump file: Comet.pos
    cmd="tail -n " + toString(nl-4) + " "+ Dir + File + " > " + Dir+Fdump;
    printf("Dir: %s\n",Dir.c_str());
    printf("cmd: %s\n",cmd.c_str());
    system(cmd.c_str());

    // Get the initial time of the run
    cmd="grep -v \"#\" " + Desc + " | grep \"Tini\" | gawk -F\"=\" '{print $2}' ";
    r=exec(cmd);
    Tini=atof(r.c_str());
    //printf("cmd: %s\n",cmd.c_str());


    NameF=Dir+File;
    file = fopen(NameF.c_str(),"r");
    for(int j=0;j<=nl-4;j++){
      fscanf(file,"%lf %lf %lf %lf %lf %lf %lf %lf",&Time,&State[0],&State[0],&State[0],&State[0],
	     &State[0],&State[0],&Distance);
      if(Distance>RSOI){
	Tcapture = (Tini+Time)/365.25 + 2000;
	TCapture=fopen("Capture.dat","a");
	fprintf(TCapture,"%lf   %lf\n",Tcapture,i);
	fclose(TCapture);
	break;	  
      }
    }
    fclose(file);
   
  }
  

}
  // int a=1;
  // float b=2.0;
  // double c=3.0;
  // char *d="Hola";
  // string e="STRING";
  // string f;
  // char g;
  // char *h;

  // printf("Types of variable:\n");
  // printf("a: %s\n",typeid(a).name());
  // printf("b: %s\n",typeid(b).name());
  // printf("c: %s\n",typeid(c).name());
  // printf("d: %s\n",typeid(d).name());
  // printf("e: %s\n",typeid(e).name());
  // printf("f: %s\n",typeid(f).name());
  // printf("g: %s\n",typeid(g).name());
  // printf("h: %s\n",typeid(h).name());

  
  




