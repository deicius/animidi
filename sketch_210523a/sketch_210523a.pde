import processing.sound.*;
SoundFile soundfile;

String lines[];
float notes[];
float starting[], duration[];
boolean gone[];
boolean ungone[];
float speed=10;
float bpm;
float barh=720/120;
float barw=90;
void setup() {
  soundfile = new SoundFile(this, "wtc19p_bpm88.wav");
  soundfile.play();
  frameRate(30);
  lines = loadStrings("wtc19p.txt");
  size(1280, 720);
  background(0);
  bpm = float(lines[0]);
  speed = barw;
  notes = new float[lines.length-1];
  starting = new float[lines.length-1];
  duration = new float[lines.length-1];
  gone = new boolean[lines.length-1];
  ungone = new boolean[lines.length-1];
  
  for (int i=1; i<lines.length; i++) {
    String[] temp = split(lines[i], ' ');
    notes[i-1] = float(temp[0]);
    starting[i-1] = float(temp[1]);
    duration[i-1] = float(temp[2]);
    gone[i-1]=false;
    ungone[i-1]=true;
  }
}
float beat = 0;
float framecnt = -0.08*30-0.1*30;
void draw() {
  background(0);
  fill(255,0,0);
  rect(640,0,1,720);
  for (int i=0; i<notes.length; i++) {
    fill(255);
    noStroke();
    if(640+(starting[i]-beat)*barw<1280)ungone[i]=false;
    if(!gone[i] && !ungone[i])rect(640+(starting[i]-beat)*barw,720-barh*notes[i],duration[i]*barw,barh);
    if(640+(starting[i]-beat+duration[i])*barw<0)gone[i]=true;
  }
  framecnt+=1;
  beat = framecnt/30*bpm/60;
  if(gone[gone.length-1])noLoop();
}
