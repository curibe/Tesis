#include <Preamble.h>

//###############
// MAIN
//###############
int main(int argc,char *argv[])
{

  string Principal,r,cmd;
  string Rundir,Bindir,pathAnal,Analysis,EqFile;
  string Rdir,OBSERVER,TARGET,getSTATE;
  string filePOS,fileANAL;
  string Nl,NameF,pathPOS,Dir,out;
  string pbr, Desc;
    
  char *strl, strn[200];
  int Ndir;
  double XEQ[3];
  double XCE[6],Tini,Time, distance;
  double RIE,RJE,Alpha,Delta;

  vector<double> State;
  vector<double> XJE;

  FILE *EQF;


  //*************************
  // FILES
  //*************************
  filePOS="BODY1.pos";
  fileANAL="Equatorial_coordinates_final.dat";
  OBSERVER="EARTH";
  TARGET="JUPITER";
    
  
  //*******************
  // PATHS
  //*******************
  Principal = exec("pwd");
  Rundir = Principal+"/RUNDIR/";
  Bindir = Principal+"/BIN/";
  Analysis = Principal + "/Analysis/";
  EqFile = Analysis + fileANAL;
  

  // Read the total number of runs
  cmd="ls -d "+Rundir+"* | wc -l";
  r=exec(cmd);
  Ndir=atoi(r.c_str());

  // Cleaning file in Analysis folder
  cmd = "rm " + EqFile;
  system(cmd.c_str());

  // OPENING FILE
  EQF=fopen(EqFile.c_str(),"w");
    
  for(int i=1;i<=Ndir;i++){

    //%%%%%%%%%%%%%%%%%%%%% SECTION I %%%%%%%%%%%%%%%%%%%%%%%%%%%%

    //Path of folder output in each run directories
    Dir=Rundir+"run"+toString(i)+"/output/";
    
    // Path of files BODY7.pos
    // Path of executable GetState.out 
    pathPOS = Dir + filePOS;
    getSTATE = Bindir + "./GetState.out";
    
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
    
    
        
    //%%%%%%%%%%%%%%%%% SECTION II %%%%%%%%%%%%%%%%%%%%%%%%%%%

    // CONVERTING FROM (AU,DAYS,MJUP) to (km,s,kg) unit system
    //=========================================================
    /* COMET*/
    State[0]*=DAYS;
    State[1]*=AU; State[2]*=AU; State[3]*=AU;
    State[4]*=AU/DAYS; State[5]*=AU/DAYS; State[6]*=AU/DAYS;
    distance = State[7]*AU;
     
    //printf("COMET STATE:  %E %e %e %e %e %e %e %e\n",State[0],State[1],State[2],State[3],State[4],State[5],State[6],State[7]);
   
    // Converting the time from days to JD
    Time=(Tini + State[0]);
   
    // GET THE STATE OF JUPITER RESPECT TO THE EARTH IN Time
    //=========================================================
    sprintf(strn,"%e ",Time);
    getSTATE = Bindir + "./GetState.out " + OBSERVER + " "  + TARGET + " " + strn;
    //printf("pbr : %s\n",getSTATE.c_str());
    out = exec(getSTATE.c_str());
    //printf("out: %s\n",out.c_str());
    XJE = Split2F((char *)out.c_str());
    //printf("XJE: %E %E %E %E %E %E\n",XJE[0],XJE[1],XJE[2],XJE[3],XJE[4],XJE[5]);
    //printf("State: %E %E %E %E %E %E\n",State[1],State[2],State[3],State[4],State[5],State[6]);
    //N=sizeof(Staten);

    
    // GET THE STATE OF  COMET RESPECT TO THE EARTH
    //==================================================
    XCE[0]=State[1]+XJE[0];    XCE[3]=State[4]+XJE[3];
    XCE[1]=State[2]+XJE[1];    XCE[4]=State[5]+XJE[4];
    XCE[2]=State[3]+XJE[2];    XCE[5]=State[6]+XJE[5];
    
    //printf("XCE: %E %E %E %E %E %E\n",XCE[0],XCE[1],XCE[2],XCE[3],XCE[4],XCE[5]);
    
    //%%%%%%%%%%%%%%%%%%%%%% SECTION III %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

    // GET THE STATE RESPECT TO THE EQUATORIAL SYSTEM
    //==================================================
    Ecl2Eq(XCE,XEQ);
    //printf("XEQ(MAIN): %E %E %E\n",XEQ[0],XEQ[1],XEQ[2]);
    //printf("XEQ(MAIN-after): %E %E %E\n",XEQ[0],XEQ[1],XEQ[2]);
    // CALCULATING THE DISTANCE OF COMET RESPECT TO EARTH
    //=====================================================
    RIE=sqrt(XEQ[0]*XEQ[0]+XEQ[1]*XEQ[1]+XEQ[2]*XEQ[2]);
    RJE=sqrt(XJE[0]*XJE[0]+XJE[1]*XJE[1]+XJE[2]*XJE[2])/AU;
    //printf("RIE: %E\n",sqrt(XEQ[0]*XEQ[0]));

    // CONVERTING FROM (km,s,kg) to (AU.DAYS,MJUP)
    //==================================================
    //XEQ[0]=XEQ[0]/AU;   XEQ[1]=XEQ[1]/AU;    XEQ[2]=XEQ[2]/AU;

    // CALCULATING THE RIGTH ASCENSION AND DECLINATION
    //==================================================
    Delta=asin(XEQ[2]/RIE)*RAD2DEG;
    Alpha=Atan(XEQ[1],XEQ[0])*RAD2DEG;
    //printf("Alpha: %lf    Delta: %lf\n",Alpha,Delta);
    fprintf(EQF,"%lf %lf\n",Alpha,Delta);
       
    
  }
        

  fclose(EQF);
  
  return 0;
}
