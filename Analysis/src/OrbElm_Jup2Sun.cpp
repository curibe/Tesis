#include <Preamble.h>

//###############
// MAIN
//###############
int main(int argc,char *argv[])
{

  int i;
  double *XC,*XS,*X,NlC,NlS,time;
  double *OrbElm,SMaxis,Aphelion;

  string Principal,Outdir,Bindir;
  string cmd,r;
  string FPOS,FSunPOS,fileORB_rot,filePOS_rot,filedumpS,filedumpC;
  string pathFPOS,pathOrbRot,pathPosRot,pathFSunPOS;
  string NlinesS,NlinesC,xyz2aei,out;
  char strn[50];

  FILE *Pos,*OrbR,*PosR,*SunPos;  

  
  //*******************
  // FILE
  //*******************
  FPOS="BODY7.pos";
  FSunPOS="BODY6.pos";
  fileORB_rot = "BODY7orb.ref";
  filePOS_rot = "BODY7pos.ref";
  filedumpS = "filePS.dump";
  filedumpC = "filePC.dump";
  
  //*******************
  // PATHS
  //*******************
  Principal = exec("pwd");
  Outdir = Principal+"/output/";
  Bindir = Principal+"/bin";
  
  pathFPOS=Outdir + FPOS;
  pathOrbRot=Outdir + fileORB_rot;
  pathPosRot=Outdir + filePOS_rot;
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
  
  // Creating the dump file fileP.dump from file BODY6.pos
  cmd="tail -n " + NlinesS + pathFSunPOS + " > " + filedumpS;
  system(cmd.c_str());
  
  
  Pos=fopen(pathFPOS.c_str(),"r");
  OrbR=fopen(pathOrbRot.c_str(),"w");
  PosR=fopen(pathPosRot.c_str(),"w");
  SunPos=fopen(pathFSunPOS.c_str(),"r");
    
  for(i=0;i<NlC;i++){
    // Reading files
    fscanf(Pos,"%lf %lf %lf %lf %lf %lf %lf %*lf",&XC[0],&XC[1],&XC[2],&XC[3],&XC[4],&XC[5],&XC[6]);
    fscanf(SunPos,"%lf %lf %lf %lf %lf %lf %lf %*lf",&XS[0],&XS[1],&XS[2],&XS[3],&XS[4],&XS[5],&XS[6]);
    
    // Changing of reference system
    X=ChangeSR(XC,XS);
    
    // Changin unity to kg,km,s
    X=ChangeUnit(X,"AU-DAYS");
    
    // Converting form xyz to aei
    sprintf(strn,"%e %e %e %e %e %e %e %e",X[1],X[2],X[3],X[4],X[5],X[6],X[0],MUSUN);
    xyz2aei = Bindir + "/./state2elem " + strn;
    out = exec(xyz2aei.c_str());
    OrbElm = Split2F((char *)out.c_str());
    
    // Get the semimajor axis
    SMaxis=getSMAxis(OrbElm[0],OrbElm[1]);
    
    // Get the Aphelion Distance
    if(OrbElm[1]<1.0 && OrbElm[1]>0.0) Aphelion = SMaxis*(1.0+OrbElm[1]);
    
    // Converting from km to AU
    Aphelion=Aphelion/AU;
    SMaxis=SMaxis/AU;
    X=ChangeUnit(X,"au-days");
    OrbElm[0]=OrbElm[0]/AU;
    
    //Converting from rad to deg
    OrbElm[2]=OrbElm[2]*RAD2DEG; // inclination
    OrbElm[3]=OrbElm[3]*RAD2DEG; // lnode
    OrbElm[4]=OrbElm[4]*RAD2DEG; // argp
    OrbElm[5]=OrbElm[5]*RAD2DEG; // Mean Anomaly
    
    // Saving State Vector respect to the sun
    fprintf(PosR,"%12.6lf %16E %16E %16E %16E %16E %16E\n",X[0],X[1],X[2],X[3],X[4],X[5],X[6]);
    // Saving Orbital elements respect to the sun
    fprintf(OrbR," %12.6lf %16E  %16E  %16E  %16E  %16E  %16E  %16E  %16E\n",X[0],SMaxis,OrbElm[1],OrbElm[2],OrbElm[3],
	    OrbElm[4],OrbElm[5],OrbElm[0],Aphelion);    
    
  }
  

  fclose(Pos);
  fclose(OrbR);
  fclose(PosR);
  fclose(SunPos);

  return 0;

}
