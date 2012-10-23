#include <Preamble.h>

//##############################
// MAIN PROGRAM
//##############################
int main(int argc,char *argv[])
{
  
  string Principal,r,cmd;
  string Rundir,Bindir;
  string Rdir,dir;
  string Nl,NameF;
  
  int Ndir;
    
    
  //dir2=getcwd(dir2,50);
  
  
  //*******************
  // PATHS
  //*******************
  Principal=exec("pwd");
  Rundir=Principal+"/RUNDIR/";
  Bindir=Principal+"/BIN";

  cmd="ls -d "+Rundir+"* | wc -l";
  r=exec(cmd);
  Ndir=atoi(r.c_str());
  
  printf("***************************************************\n");
  printf("*  Preparing Simulation in each Directory ...\n");
  printf("***************************************************\n");
  printf("\nPROGRESS:\n\n");
  for(int i=1;i<=Ndir;i++){
    
    dir= Rundir + "run" + toString(i);
    printf("dir: %s\n",dir.c_str());
    chdir(dir.c_str());
    system("make prepare > OurRun.dump");
    //ProgressBar(i,30,Ndir,"Building ");
  }
  
  return 0;
  
}
