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
  string filePOS="BODY7.pos";
  string fileORB="BODY7.orb";
  string Fdump="Comet.pos";
  string fileANAL="OrbElms.orb";
  string Nl,NameF,pathPOS,pathORB,Dir,out;
  string XYZ2AEI,pbr, Desc;
    
  char *CMD, *strl, strn[200];
  int Ndir,N;
  double *State,output,*OrbElm;
  double ET,X,Tini;
  
  FILE *POS,*ORB;


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
    // Path of executable xyz2aei.out 
    pathPOS = Dir + filePOS;
    pathORB = Dir + fileORB;
    XYZ2AEI = Bindir + "/./xyz2aei.out";
    
    //Path of Description file
    Desc=Rundir+"run"+toString(i)+"/Description.txt";
    
    
    printf("Dir: %s , i: %d\n",Dir.c_str(),i);

    // Reading the last line of BODY7.pos : Comet
    cmd = "tail -n 1 " + pathPOS;
    out = exec(cmd.c_str());
    printf("i:%d  out: %s\n",i,out.c_str());
    strl=(char *)out.c_str();
    State=SplitToF(strl);

    // Get the initial time of the run
    cmd="grep -v \"#\" " + Desc + " | grep \"Start\" | gawk -F\"=\" '{print $2}' ";
    r=exec(cmd);
    Tini=atof(r.c_str());

    // CONVERTING FROM (AU,DAYS,MJUP) to (km,s,kg) unit system
    ET = State[0]*


    sprintf(strn,"%e %e %e %e %e %e %e",State[1],State[2],State[3],State[4],State[5],State[5],State[6],State[7]);
    printf("strn: %s\n",&strn[0]);
    XYZ2AEI = Bindir + "/./xyz2aei.out " +strn;
    printf("pbr : %s\n",pbr.c_str());

    //N=sizeof(State);
    /*
    // Verifying if the comet has gotten out of the SOI
    if(State[7]>RSOI){
      printf("Run %d : has gotten out of SOI.\n");
      

      
      ORB=fopen(pathAnal.c_str(),"a");
      fprintf(ORB,"%4d   %10lf   %16E   %16E   %16E   %16E   %16E   %16E   %16E   %16E   %16E   %16E\n",
	      i,OrbElm[0],OrbElm[1],OrbElm[2],OrbElm[3],OrbElm[4],OrbElm[5],OrbElm[6],OrbElm[7],OrbElm[8],OrbElm[9],
	      OrbElm[10]);
      fclose(ORB);     
    }
        
    /*
    for(int j=0;j<N;j++)
    printf("%E\n",State[j]);*/
  }
 
  return 0;
}
