#include <Preamble.h>

//###############
// MAIN
//###############
int main(int argc,char *argv[])
{

  string Principal,r,cmd;
  string Rundir,Bindir,pathAnal,Analysis,OrbFile;
  string Rdir;
  string filePOS,fileORB,fileSun,Fdump,fileANAL;
  string Nl,NameF,pathPOS,pathORB,Dir,out,TissFile,TissName;
  string XYZ2AEI,pbr, Desc;
    
  char *strl, strn[200];
  int Ndir;
  double Tiss;
  double X[6],Tini,Time, distance,SMaxis,Aphelion;
  

  vector <double> State;
  vector <double> SunS;
  vector <double> OrbElm; 
  
  FILE *ORB,*TISS;


  //*************************
  // FILES
  //*************************
  filePOS="BODY1.pos";
  fileORB="BODY1.orb";
  fileSun="BODY7.pos";
  fileANAL="OrbElms_SUN.orb";
  TissName="Tisserand.dat";
  
  
  //*******************
  // PATHS
  //*******************
  Principal = exec("pwd");
  Rundir = Principal+"/RUNDIR/";
  Bindir = Principal+"/BIN/";
  Analysis = Principal + "/Analysis/";
  OrbFile = Analysis + fileANAL;
  TissFile = Analysis + TissName;

  // Read the total number of runs
  cmd="ls -d "+Rundir+"* | wc -l";
  r=exec(cmd);
  Ndir=atoi(r.c_str());

  // Cleaning file in Analysis folder
  cmd = "rm " + OrbFile;
  system(cmd.c_str());
  cmd = "rm " + TissFile;
  system(cmd.c_str());

  //****************************
  // HEADERS OF FILES
  //****************************
  ORB=fopen(OrbFile.c_str(),"a");
  fprintf(ORB,"#==================================================================================================\n");
  fprintf(ORB,"#  COLUMN LABELS:  SMaxis   Q   ecc   inc    lnode   argp    M0    epoch   Mu   indexRun\n");
  fprintf(ORB,"#  Units: km,rad,s\n");
  fprintf(ORB,"#==================================================================================================\n");
  fclose(ORB);
  
  TISS=fopen(TissFile.c_str(),"a");
  fprintf(TISS,"#=========================================================================\n");
  fprintf(TISS,"#  COLUMN LABELS: SMaxis   rp   ecc   inc   Tiss   indexRun\n");
  fprintf(TISS,"#  Units: km,rad,s\n");
  fprintf(TISS,"#=========================================================================\n");
  fclose(TISS);
  
  for(int i=1;i<=Ndir;i++){

    //%%%%%%%%%%%%%%%%%%%%% SECTION I %%%%%%%%%%%%%%%%%%%%%%%%%%%%

    //Path of folder output in each run directories
    Dir=Rundir+"run"+toString(i)+"/output/";
    
    // Path of files BODY7.pos and BODY7.orb
    // Path of executable xyz2aei.out 
    pathPOS = Dir + filePOS;
    pathORB = Dir + fileORB;
    XYZ2AEI = Bindir + "./xyz2aei.out";
    
    //Path of Description file
    Desc=Rundir+"run"+toString(i)+"/Description.txt";
    
    
    // Reading the last line of BODY7.pos : Comet
    cmd = "tail -n 1 " + pathPOS;
    out = exec(cmd.c_str());
    strl=(char *)out.c_str();
    State=Split2F(strl);
    //printf("%lf   %E   %E   %E   %E   %E   %E   %E\n",State[0],State[1],State[2],State[3],State[4],State[5],State[6],State[7]);

    // Get the initial time of the run
    cmd="grep -v \"#\" " + Desc + " | grep \"Start\" | gawk -F\"=\" '{print $2}' ";
    r=exec(cmd);
    Tini=atof(r.c_str())*DAYS; // in seconds
    
    
    //Reading the file BODY6.pos : Sun
    //Finding the line in which the time value equal to State[0] (time).
    cmd = "grep \" " + toString(State[0]) + "\" " + Dir + fileSun;
    //cout<<"cmd: "<<cmd<<endl;
    out=exec(cmd.c_str());
    strl=(char *)out.c_str();
    SunS=Split2F(strl);
    
    //printf("vx-sun (AU/DAYS): %E    vx-sun(km/s): %E DAYS: %E   AU: %E    AU/DAYS: %E     uv:  %E     UV:  %E\n",SunS[4],SunS[4]*AU/DAYS,DAYS,AU,AU/DAYS,uv,UV);
    
    //%%%%%%%%%%%%%%%%% SECTION II %%%%%%%%%%%%%%%%%%%%%%%%%%%

    // CONVERTING FROM (AU,DAYS,MJUP) to (km,s,kg) unit system
    //=========================================================
    /* COMET*/
    State[0]*=DAYS;
    State[1]*=AU; State[2]*=AU; State[3]*=AU;
    State[4]*=AU/DAYS; State[5]*=AU/DAYS; State[6]*=AU/DAYS;
    distance = State[7]*AU;
    /* SUN */
    SunS[0]*=DAYS;
    SunS[1]*=AU; SunS[2]*=AU; SunS[3]*=AU;
    SunS[4]*=AU/DAYS; SunS[5]*=AU/DAYS; SunS[6]*=AU/DAYS;
    
 
    //printf("COMET STATE:  %E %e %e %e %e %e %e %e\n",State[0],State[1],State[2],State[3],State[4],State[5],State[6],State[7]);
    //printf("SUN STATE:  %E %e %e %e %e %e %e %e\n",SunS[0],SunS[1],SunS[2],SunS[3],SunS[4],SunS[5],SunS[6],SunS[7]);

    // Converting the time from days to JD
    Time=(Tini + State[0]);
    
    // CHANGING OF REFERENCE FRAME: FROM JUPITER TO SUN
    X[0]=State[1]-SunS[1]; X[1]=State[2]-SunS[2]; X[2]=State[3]-SunS[3];
    X[3]=State[4]-SunS[4]; X[4]=State[5]-SunS[5]; X[5]=State[6]-SunS[6];


    //printf("STATE (respect Sun):  %E %e %e %e %e %e %e %e\n",X[0],X[1],X[2],X[3],X[4],X[5],X[6],X[7]);
    

    //%%%%%%%%%%%%%%%%%%%%%% SECTION III %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    ///*
    /********************************************
     Getting the orbital elements and the Tisserand Parameter.
    The orbital element are stored in the array OrbElm. The entrance are:
    OrbElm[0]: perifocal distance (rp)
    OrbElm[1]: eccentricity (ecc)
    OrbElm[2]: Inclination (inc)
    OrbElm[3]: Longitude of Ascending Node (lnode)
    OrbElm[4]: Argument of periapsis (argp)
    OrbElm[5]: Mean anomaly at epoch (m0)
    OrbElm[6]: Epoch (t0)
    OrbElm[7]: Gravitational Parameter (mu) 
    ***********************************************/

    sprintf(strn,"%e %e %e %e %e %e %e %e",X[0],X[1],X[2],X[3],X[4],X[5],Time,MUSUN);
    XYZ2AEI = Bindir + "./xyz2aei.out " +strn;
    //printf("pbr : %s\n",XYZ2AEI.c_str());
    out = exec(XYZ2AEI.c_str());
    //printf("out: %s\n",out.c_str());
    OrbElm = Split2F((char *)out.c_str());
    SMaxis = getSMAxis(OrbElm[0],OrbElm[1]);
    //printf("SMaxis: %E\n",SMaxis);
    Tiss = Tisserand(OrbElm[0],OrbElm[1],OrbElm[2]);
    // Determining the Aphelion 
    if(OrbElm[1]<1.0 && OrbElm[1]>0.0){
      Aphelion = SMaxis*(1+OrbElm[1]);
    }else{ Aphelion=0.0;}

    //N=sizeof(Staten);
    
    
    
    // Verifying if the comet has gotten out of the SOI
    if(distance>RSOI){
      ORB=fopen(OrbFile.c_str(),"a");
      TISS=fopen(TissFile.c_str(),"a");
      fprintf(ORB,"%16E   %16E   %16E   %16E   %16E   %16E   %16E   %16E   %16E    %4d\n",
	      SMaxis,Aphelion,OrbElm[1],OrbElm[2],OrbElm[3],OrbElm[4],OrbElm[5],OrbElm[6],OrbElm[7],i);
      fprintf(TISS,"%16E %16E %16E %16E %14lf %4d\n",SMaxis,OrbElm[0],OrbElm[1],OrbElm[2],Tiss,i);
      fclose(ORB); 
      fclose(TISS);
    }
        
  }
  
 
  
  return 0;
}
