#include <Preamble.h>

//###############
// MAIN
//###############
int main(int argc,char *argv[])
{

  int i;
  double XJ[6],XC[6],NlC,NlS,t;
  FILE *Pos,*OrbR,*PosR,*SunPos;

  string Principal,Outdir;
  string cmd,r;
  string FPOS="BODY7.pos";
  string FSunPOS="BODY6.pos";
  string fileORB_rot = "BODY7orb.ref";
  string filePOS_rot = "BODY7pos.ref";
  string filedumpC = "filePS.dump";
  string filedumpA = "filePC.dump";
  string NlinesS,NlinesC;

  

  //*******************
  // PATHS
  //*******************
  Principal = exec("pwd");
  Outdir = Principal+"/output/";
  
  pathFPOS=Outdir + FPOS;
  pathOrbRot=Ourdir + fileORB_rot;
  pathPosRot=Ourdir + filePOS_rot;
  pathFSunPOS=Outdir + FSunPOS;
  
  // READING THE NUMBER OF LINES
  cmd="wc -l "+ pathFPOS + " | gawk \'{print $1}\'";
  NlinesC=exec(cmd);
  NlC=atof(NlinesC.c_str());
  
  // READING THE NUMBER OF LINES
  cmd="wc -l "+ pathFSunPOS + " | gawk \'{print $1}\'";
  NlinesS=exec(cmd);
  NlS=atof(NlinesS.c_str());
  
  
  // Creating the dump file fileP.dump from file BODY7.pos
  cmd="tail -n " + NlinesC + pathFPOS + " > " + filedumpC;
  system(cmd.c_str());
  
  // Creating the dump file fileP.dump from file BODY7.pos
  cmd="tail -n " + NlinesS + pathFSunPOS + " > " + filedumpS;
  system(cmd.c_str());
  
  
  FPOS=fopen(filedumpC,"r");
  OrbR=fopen(pathOrbRot,"w");
  PosR=fopen(pathPosRot,"w");
  SunPos=fopen(pathFsunPOS,"r");
    
  for(i=0;i<NlC;i++){
    fscanf(FPOS,"%lf %lf %lf %lf %lf %lf %lf %*lf",&t,&XJ[0],&XJ[1],&XJ[2],&XJ[3],&XJ[4],&XJ[5]);
    fscanf(SunPos,"%*lf %lf %lf %lf %lf %lf %lf %*lf",&XS[0],&XS[1],&XS[2],&XS[3],&XS[4],&XS[5]);
    
  }
  




  fclose(FPOS);

  return 0;

}
