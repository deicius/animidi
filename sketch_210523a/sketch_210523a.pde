import processing.sound.*;
SoundFile soundfile;
String filename = "input";
float notes[], star[], dur[];
float bpm=60;
float beat=0;
float framecnt=-0.08*30;
float barH=6, barW=90;
float fr = 30;
int ptf=0, ptb=0;
int[] chord={0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
void setup() {
  size(1280, 720);
  frameRate(fr);
  background(0);
  playsound();
  inputdata();
  updateindex();
}

void draw() {
  for (int i=0; i<12; i++)chord[i]=0;
  drawnotes();
  drawcursor();
  drawchord();
  framecnt += 1;
  beat = framecnt/fr*bpm/60.0;
  updateindex();
}

void playsound() {
  soundfile = new SoundFile(this, filename + ".wav");
  soundfile.play();
}



void inputdata() {
  String[] lines = loadStrings(filename + ".txt");
  int len = lines.length-1;
  bpm = float(lines[0]);
  notes = new float[len];
  star = new float[len];
  dur = new float[len];
  for (int i=0; i<len; i++) {
    String[] temp = split(lines[i+1], ' ');
    notes[i] = float(temp[0]);
    star[i] = float(temp[1]);
    dur[i] = float(temp[2]);
  }
}

void updateindex() {
  int temp1=ptf, temp2=ptb;
  for (int i=ptf; i<notes.length; i++) {
    if (star[i]+dur[i]-beat>=-640/barW) {
      temp1=i;
      break;
    }
  }
  for (int i=ptb; i<notes.length; i++) {
    if (i<notes.length-1) {
      if (star[i]-beat<=640/barW && star[i+1]-beat>640/barW) {
        temp2=i;
        break;
      }
    } else temp2 = i;
  }
  ptf=temp1;
  ptb=temp2;
}

void drawcursor() {
  colorMode(RGB, 255, 255, 255);
  noStroke();
  fill(255, 0, 0);
  rect(639, 0, 2, 720);
}

void drawnotes() {
  background(0);

  for (int i=ptf; i<=ptb; i++) {
    float t1=star[i]-beat, t2=star[i]+dur[i]-beat;
    noStroke();
    if (t1*barW<0 && t2*barW>0) {
      colorMode(HSB, 360, 1, 1);
      fill(int(notes[i])*7%12*30, 1, 1);
      chord[int(notes[i])%12]=1;
    } else if (t2*barW<=0) {
      colorMode(RGB, 255, 255, 255);
      fill(255+t2*barW/640*255);
    } else {
      colorMode(RGB, 255, 255, 255);
      fill(255-t1*barW/640*255);
    }
    rect(640+t1*barW, 720-barH*notes[i], dur[i]*barW, barH);
  }
}


void drawchord() {

  float x=150, y=150, r=100, s=75, b=PI/12.0;

  for (int i=0; i<12; i++) {
    colorMode(HSB, 360, 1, 1);
    noStroke();
    if (chord[i]==1) {
      fill((i*7)%12*30, 1, 1);
      arc(x, y, r*2, r*2, 
        b*(2*i-1-6), 
        b*(2*i+1-6));
    }
  }
  for (int i=0; i<12; i++) {
    if (chord[i]==1) {
      colorMode(RGB, 255, 255, 255);
      stroke(255);
      strokeWeight(3);
      for (int j=0; j<12; j++) {
        if (chord[j]==1) {
          line(x+s*cos(b*(2*i-6)), 
            y+s*sin(b*(2*i-6)), 
            x+s*cos(b*(2*j-6)), 
            y+s*sin(b*(2*j-6)));
        }
      }
    }
  }
}
