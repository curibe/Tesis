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
  string fileSun="BODY6.pos";
  string Fdump="Comet.pos";
  string fileANAL="OrbElms_SUN.orb";
  string Nl,NameF,pathPOS,pathORB,Dir,out;
  string XYZ2AEI,pbr, Desc;
    
  char *CMD, *strl, strn[200];
  int Ndir,N;
  double *State,output,*OrbElm,*SunS;
  double ET,X[6],Tini,Xs,Time, distance,SMaxis;

  
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

  // Cleaning file in Analysis folder
  cmd = "rm " + pathAnal;
  system(cmd.c_str());
 
  
  for(int i=1;i<=Ndir;i++){

    //%%%%%%%%%%%%%%%%%%%%% SECTION I %%%%%%%%%%%%%%%%%%%%%%%%%%%%

    //Path of folder output in each run directories
    Dir=Rundir+"run"+toString(i)+"/output/";
    
    // Path of files BODY7.pos and BODY7.orb
    // Path of executable xyz2aei.out 
    pathPOS = Dir + filePOS;
    pathORB = Dir + fileORB;
    XYZ2AEI = Bindir + "/./xyz2aei.out";
    
    //Path of Description file
    Desc=Rundir+"run"+toString(i)+"/Description.txt";
    
    printf("***************************************\n");
    printf("DIR: %s   ,  i: %d\n",Dir.c_str(),i);

    // Reading the last line of BODY7.pos : Comet
    cmd = "tail -n 1 " + pathPOS;
    out = exec(cmd.c_str());
    printf("i:%d     out: %s\n",i,out.c_str());
    strl=(char *)out.c_str();
    State=Split2F(strl);
    printf("COMET STATE:  %e %e %e %e %e %e %e %e\n",State[0],State[1],State[2],State[3],State[4],State[5],State[6],State[7]);

    // Get the initial time of the run
    //cout<<"Get the initial time of the run"<<endl;
    cmd="grep -v \"#\" " + Desc + " | grep \"Start\" | gawk -F\"=\" '{print $2}' ";
    r=exec(cmd);
    Tini=atof(r.c_str())*DAYS; // in seconds
    printf("Tini: %E\n",Tini);


    //Reading the file BODY6.pos : Sun
    //Finding the line in which the time value equal to State[0].
    cmd = "grep \" " + toString(State[0]) + "\" " + Dir + fileSun;
    cout<<"cmd: "<<cmd<<endl;
    out=exec(cmd.c_str());
    strl=(char *)out.c_str();
    SunS=Split2F(strl);
    
    //printf("COMET STATE:  %.3lf %e %e %e %e %e %e %e\n",State[0],State[1],State[2],State[3],State[4],State[5],State[6],State[7]);
    printf("SUN STATE:  %.3lf %e %e %e %e %e %e %e\n",SunS[0],SunS[1],SunS[2],SunS[3],SunS[4],SunS[5],SunS[6],SunS[7]);


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

    // Converting the time from days to JD
    Time=(Tini + State[0]);
    //printf("Time: %E\n",Time);

    // CHANGING OF REFERENCE FRAME: FROM JUPITER TO SUN
    X[0]=State[1]-SunS[1]; X[1]=State[2]-SunS[2]; X[2]=State[3]-SunS[3];
    X[3]=State[4]-SunS[4]; X[4]=State[5]-SunS[5]; X[5]=State[6]-SunS[6];

    

    //%%%%%%%%%%%%%%%%%%%%%% SECTION III %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
    /*
    sprintf(strn,"%e %e %e %e %e %e %e %e",X[0],X[1],X[2],X[3],X[4],X[5],Time,MUSUN);
    printf("strn: %s\n",&strn[0]);
    XYZ2AEI = Bindir + "/./xyz2aei.out " +strn;
    printf("pbr : %s\n",XYZ2AEI.c_str());
    out = exec(XYZ2AEI.c_str());
    OrbElm = Split2F((char *)out.c_str());
    SMaxis = getSMAxis(OrbElm[0],OrbElm[1]);

    //N=sizeof(State);
    
    // Verifying if the comet has gotten out of the SOI
    if(distance>RSOI){
      printf("Run %d : has gotten out of SOI.\n");
      ORB=fopen(pathAnal.c_str(),"a");
      fprintf(ORB,"%4d   %10lf   %16E   %16E   %16E   %16E   %16E   %16E   %16E   %16E   %16E   %16E\n",
	      i,SMaxis,OrbElm[1],OrbElm[2],OrbElm[3],OrbElm[4],OrbElm[5],OrbElm[6],OrbElm[7]);
      fclose(ORB);     
    }
        
    /*
    for(int j=0;j<N;j++)
    printf("%E\n",State[j]);*/
  }

    printf("SALI DEL FOR\n");
  int a=1;
  float b=2.0;
  double c=3.0;
  char *d="Hola";
  string e="STRING";
  string f;
  char g;
  char *h;
  char *pr;
  double z=1.2345;

  printf("Types of variable:\n");
  printf("a: %s\n",typeid(a).name());
  printf("b: %s\n",typeid(b).name());
  printf("c: %s\n",typeid(c).name());
  printf("d: %s\n",typeid(d).name());
  printf("e: %s\n",typeid(e).name());
  printf("f: %s\n",typeid(f).name());
  printf("g: %s\n",typeid(g).name());
  printf("h: %s\n",typeid(h).name());
  


 
  return 0;
}
