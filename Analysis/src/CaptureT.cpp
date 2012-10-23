#include <Preamble.h>


//##############################
// MAIN PROGRAM
//##############################
int main(int argc,char *argv[])
{

  FILE *file,*TCapture;
  
  int Ndir,i,nl;

  double Tini,State[6],Time,Distance,Tcapture;
  
  string Principal,r,cmd;
  string Rundir,Bindir,Analdir,Srcdir;
  //string Rundir("/RUNDIR/");
  //string Bindir("/BIN/");
  string File,Fdump,CaptFile,Captdir;
  string Nl,NameF;
  string Dir,Desc;
  

  //******************
  // FILES
  //******************
  File="BODY1.pos";
  Fdump="Comet.dump";
  CaptFile = "CaptureTime.dat";
  
  //*******************
  // PATHS
  //*******************
  Principal=exec("pwd");
  Rundir=Principal+"/RUNDIR/";
  Bindir=Principal+"/BIN";
  Analdir=Principal+"/Analysis/";
  Srcdir = Principal + "/Analysis/src/";
  Captdir = Analdir + CaptFile;
  
  //system("rm Capture.dat"); // Deleting file

  // Read the total number of runs
  cmd="ls -d "+Rundir+"* | wc -l";
  r=exec(cmd);
  Ndir=atoi(r.c_str());
  

  // Headfile of the text file with the capture time
  //==================================================
  TCapture = fopen(Captdir.c_str(),"w");
  fprintf(TCapture,"# Time Capture         Run\n");
  fprintf(TCapture,"#------------------------------------\n");
  //fclose(TCapture);

    
  
  for(i=1;i<=Ndir;i++){

    //Path of folder output in each run directories
    // Path of the Description file
    Dir=Rundir+"run"+toString(i)+"/output/";
    Desc=Rundir+"run"+toString(i)+"/Description.txt";
    cmd="wc -l " + Dir + File + "| gawk '{print $1}'";
    Nl=exec(cmd);
    nl=atoi(Nl.c_str());
    
    // Creating a dump file: Comet.dump
    cmd="tail -n " + toString(nl-4) + " " + Dir + File + " > " + Dir + Fdump;
    system(cmd.c_str());

    // Get the initial time of the run
    cmd="grep -v \"#\" " + Desc + " | grep \"Start\" | gawk -F\"=\" '{print $2}' ";
    r=exec(cmd);
    Tini=atof(r.c_str());
    //printf("cmd: %s\n",cmd.c_str());


    NameF=Dir+Fdump;
    printf("NameF: %s\n",NameF.c_str());
    file = fopen(NameF.c_str(),"r");
    for(int j=0;j<=nl-4;j++){
      fscanf(file,"%lf %lf %lf %lf %lf %lf %lf %lf",&Time,&State[0],&State[1],&State[2],&State[3],
	     &State[4],&State[5],&Distance);
      //printf("Time: %lf     Distance: %E    RSOI(AU): %E\n",Time,Distance,RSOI/AU);
      if(Distance>RSOI/AU){
	Tcapture = (Tini+Time)/365.25 + 2000;
	//TCapture=fopen("Capture.dat","a");
	fprintf(TCapture,"%lf   %d\n",Tcapture,i);
	//fclose(TCapture);
	break;	  
      }
    }
    fclose(file);
    cmd="rm "+ Dir + Fdump;
    system(cmd.c_str());
   
  }
  fclose(TCapture);


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

  
  




