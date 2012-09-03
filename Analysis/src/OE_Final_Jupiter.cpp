#include <Preamble.h>

//###############
// MAIN
//###############
int main(int argc,char *argv[])
{

  string Principal,r,cmd;
  string Rundir,Bindir,pathAnal,Analysis;
  //string Rundir("/RUNDIR/");
  //string Bindir("/BIN/");
  string Rdir;
  string filePOS,fileORB,fileANAL;
  string Nl,NameF,pathPOS,pathORB,Dir,out;
    
  char *CMD, *strl;
  int Ndir,N;
  double *State,output,*OrbElm;
  
  FILE *POS,*ORB;


  //*******************
  // FILES
  //*******************
  filePOS="BODY7.pos";
  fileORB="BODY7.orb";
  fileANAL="OrbElms.orb";
  
  
  //*******************
  // PATHS
  //*******************
  Principal = exec("pwd");
  Rundir = Principal+"/RUNDIR/";
  Bindir = Principal+"/BIN";
  Analysis = Principal + "/Analysis/";
  pathAnal = Analysis + fileANAL;

  // Read the total number of runs
  cmd="ls -d "+Rundir+"* | wc -l";
  r=exec(cmd);
  Ndir=atoi(r.c_str());
 
  
  for(int i=1;i<=Ndir;i++){

    
    //Path of folder output in each run directories
    Dir=Rundir+"run"+toString(i)+"/output/";
    
    // Path of files BODY7.pos and BODY7.orb
    pathPOS = Dir + filePOS;
    pathORB = Dir + fileORB;
        

    // Reading the last line of BODY7.pos
    cmd = "tail -n 1 " + pathPOS;
    out = exec(cmd.c_str());
    strl=(char *)out.c_str();
    State=Split2F(strl);
    //N=sizeof(State);
    
    // Verifying if the comet has gotten out of the SOI
    if(State[7]>RSOI){
      printf("Run %d : has gotten out of SOI.\n");
      cmd = "tail -n 1 " + pathORB;
      out = exec(cmd.c_str());
      OrbElm = Split2F((char *)out.c_str());
      ORB=fopen(pathAnal.c_str(),"a");
      fprintf(ORB,"%10lf   %16E   %16E   %16E   %16E   %16E   %16E   %16E   %16E   %16E   %16E   %4d\n",
	      OrbElm[0],OrbElm[1],OrbElm[2],OrbElm[3],OrbElm[4],OrbElm[5],OrbElm[6],OrbElm[7],OrbElm[8],OrbElm[9],
	      OrbElm[10],i);
      fclose(ORB);     
    }
        
    /*
    for(int j=0;j<N;j++)
    printf("%E\n",State[j]);*/
  }
 
  return 0;
}
