#include <Preamble.h>

//###############
// MAIN
//###############
int main(int argc,char *argv[])
{

  string Principal,r,cmd;
  string Rundir,Bindir;
  //string Rundir("/RUNDIR/");
  //string Bindir("/BIN/");
  string Rdir;
  string filePOS="BODY7.pos";
  string fileORB="BODY7.orb";
  string Fdump="Comet.pos";
  string Nl,NameF,pathPOS,pathORB,Dir,out;
    
  char *CMD;
  int Ndir;
  double *State;

  FILE *POS,*ORB;


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
  double output;
  char* strl;
  int N;
  for(int i=1;i<=Ndir;i++){

    
    //Path of folder output in each run directories
    // Path of the Description file
    Dir=Rundir+"run"+toString(i)+"/output/";
    pathPOS = Dir + filePOS;
    pathORB = Dir + fileORB;
    printf("Dir: %s , i: %d\n",Dir.c_str(),i);
    cmd = "tail -n 1 " + pathPOS;
    out = exec(cmd.c_str());
    printf("i:%d  out: %s\n",i,out.c_str());
    strl=(char *)out.c_str();
    State=splitof(strl);
    N=sizeof(State);
    printf("N: %d\n",N);
    for(int j=0;j<N;j++)
      printf("%E\n",State[j]);
    //printf("%lf %lf %lf %lf %lf %lf %lf %lf\n",State[0],State[1],State[2],State[3],State[4],State[5],State[6],State[7]);
    
  }

  

}
