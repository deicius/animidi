#define NOMINMAX
#include <windows.h>
#include <iostream>
#include <cmath>
#include <limits>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

	double q=0.25,h=0.5,f=0.2,dh=0.75;
	double freq=1760*2*2;
	long long int pos=0;
	double maxi=0;
	double bpm=100.0;
	vector <pair<double,pair<double,double> > > notes;

//class instrument{
//	public:
//		string name;
//		double calc(double deg);
//};



typedef signed short	BitDepth;

const double pi = 3.141592653589;
const long long samplerate			=	44100;
const int channels					=	1;
long long NUM_SAMPLES			=	44100*13;

double sinecalc(double d, long long i);
double realcalc(int len, double arr[], double d, long long i);
double note_to_freq(int n);
void makesomething(double getsound[]);
void sound(BitDepth buffer[], double getsound[]);
void getmaxi(double getsound[]);
void dothing();
double amp_normalize(double freq);
template<typename _Ty> void write(ofstream& stream, const _Ty& ty);
void writeWaveFile(const char* filename, BitDepth* buffer);
void readinput();


double sinecalc(double d, long long i){
	return sin((i*d)*pi/180.0);
}
double note_to_freq(double n){
	return 440.0*pow(2,(double(n)-69.0)/12.0);
}
double amp_normalize(double freq){
	return pow(1.8,220.0/freq);
}
double realcalc(int len, double arr[], double d, long long k){
	double bbb=0.0;
	for(int j=1; j<=len; j++){
		bbb+=sinecalc(d*double(j),k)*arr[j-1]/**amp_normalize(d*double(j))*/;
//		bbb+=sinecalc(d*double(j),k)*arr[j-1]*pow(10000.0,(330.0/freq));

	}
	return bbb;
}

void makesomething(double getsound[]) {
	for(auto e:notes){
		double curnote=e.first;
		double curfreq=note_to_freq(curnote);
		double curdeg=360.0*curfreq/44100.0;
		double curtime=e.second.first;
		double curdur=e.second.second;
		long long pos=int(double(curtime*44100.0*60.0/bpm));
		long long durr=int(double(curdur*44100.0*60.0/bpm));
		
		long long sustain=6615ll;
		long long rc_on=75ll;
		long long rc_off=sustain;
		long long hit_dur=4410ll;
		long long hit_sus=200ll;
		double hit_amp=0.10;
		double arrr_amp=1.0;
//		double arrr[11]={2.0,2.7,0.05,0.005,0.01,0.001,0.0001,0.00001,0.000001,0.0000001,0.00000001};
		double arrr[7]={3.0,1.5,0.3,0.03,0.05,0.0002,0.000005};
		double hit[9]={3.0,5.0,1.0,0.3,0.7,0.005,0.0005,0.00005,0.000005};
//		double arrr[7]={10,2.0,0.05,0.0001,0.00001,0.000001,0.0000001};
//		double arrr[9]={5.0,3.0,0.5,0.1,0.05,0.01,0.005,0.001,0.0005};
//		double arrr[10]={100.000000,6.914277,0.462681,0.371497,0.379807,0.010237,0.023093,0.006043,0.014100,0.004279};
//		double arrr[100]={100.000000,10.785444,0.091972,1.315251,0.865250,0.080137,0.102962,1.064937,0.038063,0.054466,0.033977,0.124010,0.000218,0.015159,0.005966,0.044377,0.002247,0.000348,0.003046,0.001152,0.003137,0.000529,0.000118,0.000047,0.000538,0.000288,0.000714,0.000028,0.000029,0.000071,0.000045,0.000023,0.000021,0.000020,0.000020,0.000023,0.000024,0.000019,0.000018,0.000014,0.000025,0.000023,0.000016,0.000019,0.000021,0.000020,0.000023,0.000030,0.000023,0.000023,0.000018,0.000018,0.000017,0.000036,0.000021,0.000024,0.000023,0.000027,0.000020,0.000020,0.000020,0.000023,0.000025,0.000021,0.000026,0.000027,0.000020,0.000021,0.000022,0.000021,0.000017,0.000023,0.000028,0.000023,0.000020,0.000023,0.000018,0.000020,0.000024,0.000029,0.000022,0.000026,0.000023,0.000031,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000,0.000000};
//		double arrr[89]={100.000000,37.555128,3.463259,7.674554,3.985640,0.099684,0.298170,0.086365,0.051894,0.453014,0.302766,0.015958,0.517065,0.025079,0.005482,0.018892,0.002679,0.001071,0.007785,0.002766,0.002702,0.000257,0.014482,0.008083,0.001122,0.000705,0.005373,0.001277,0.037263,0.007175,0.001484,0.000545,0.000064,0.001102,0.009210,0.005347,0.000876,0.000035,0.000066,0.000062,0.005249,0.000223,0.000098,0.000156,0.000053,0.000026,0.000025,0.000016,0.000023,0.000087,0.000488,0.000454,0.000094,0.000019,0.000016,0.000021,0.000012,0.000012,0.000014,0.000023,0.000010,0.000011,0.000009,0.000009,0.000006,0.000013,0.000010,0.000009,0.000013,0.000009,0.000009,0.000011,0.000012,0.000012,0.000010,0.000014,0.000007,0.000008,0.000009,0.000010,0.000013,0.000009,0.000011,0.000009,0.000008,0.000007,0.000010,0.000009,0.000005};
//		double arrr[228]={100.000000,14.185499,1.561742,6.435304,2.445632,0.182976,0.149083,0.037440,0.065238,0.714977,0.345586,0.049877,0.547094,1.285719,0.044172,0.031682,0.008078,0.001228,0.043657,0.031143,0.021638,0.006509,0.006167,0.078223,0.085947,0.011765,0.036487,0.016069,0.055378,0.232863,0.011753,0.012056,0.001081,0.002303,0.100323,0.054672,0.021466,0.016380,0.001105,0.000606,0.002509,0.044540,0.004107,0.001914,0.001060,0.000234,0.000506,0.000147,0.000187,0.000336,0.010470,0.005130,0.001638,0.000242,0.000048,0.000232,0.000493,0.000117,0.000133,0.000084,0.000311,0.000075,0.000026,0.000038,0.000015,0.000046,0.000079,0.000036,0.000057,0.000040,0.000028,0.000082,0.000079,0.000040,0.000039,0.000051,0.000049,0.000042,0.000028,0.000034,0.000025,0.000040,0.000035,0.000022,0.000035,0.000034,0.000025,0.000022,0.000024,0.000030,0.000021,0.000037,0.000055,0.000024,0.000037,0.000018,0.000020,0.000032,0.000031,0.000022,0.000033,0.000023,0.000028,0.000026,0.000027,0.000014,0.000020,0.000020,0.000023,0.000037,0.000038,0.000023,0.000010,0.000028,0.000017,0.000055,0.000029,0.000029,0.000019,0.000017,0.000022,0.000022,0.000021,0.000027,0.000021,0.000037,0.000008,0.000017,0.000013,0.000018,0.000020,0.000020,0.000022,0.000024,0.000022,0.000018,0.000023,0.000019,0.000033,0.000018,0.000030,0.000022,0.000029,0.000024,0.000033,0.000022,0.000016,0.000016,0.000010,0.000044,0.000014,0.000023,0.000025,0.000016,0.000029,0.000016,0.000020,0.000034,0.000041,0.000015,0.000035,0.000018,0.000065,0.000042,0.000026,0.000015,0.000025,0.000022,0.000016,0.000021,0.000019,0.000019,0.000017,0.000019,0.000025,0.000015,0.000008,0.000025,0.000018,0.000017,0.000030,0.000020,0.000016,0.000035,0.000037,0.000023,0.000033,0.000022,0.000017,0.000026,0.000029,0.000026,0.000029,0.000016,0.000022,0.000014,0.000013,0.000039,0.000032,0.000047,0.000017,0.000029,0.000028,0.000018,0.000034,0.000018,0.000045,0.000016,0.000022,0.000017,0.000024,0.000032,0.000016,0.000028,0.000018,0.000024,0.000024,0.000031,0.000028,0.000019,0.000024,0.000034,0.000029,0.000028,0.000035,0.000022,0.000025,0.000005};
		for(long long i=0; i<min(durr+sustain,NUM_SAMPLES); i++){
			double bp=0.0;
			
			
//			
//			double arrr[7]={1,1,1,1,1,1,1};
//			bp+=atan(pow(tan(double(i)*pi*curfreq/44100.0),-1.0));
			bp+=realcalc(7,arrr,curdeg,i)*arrr_amp;
			if(i<hit_dur){
				bp+=realcalc(9,hit,curdeg,i)*(double(hit_dur-i+hit_sus)/double(hit_dur))*hit_amp;
			}
//			bp+=sinecalc(curdeg,i)*4.0;
//			bp+=sinecalc(curdeg*1.01,i)*3.0;

//			bp*=(max(0.0,(150000.0-double(i))/25000.0));
			bp*=pow((max(0.0,(441000.0-double(i))/441000.0)),1);
//			bp*=0.1*min(1.0,pow((max(0.0,double(i)/441000.0)),-0.5)-1.0);
//			bp*=(max(0.0,pow(2.5,(88200.0-double(i))/88200.0)-1));
			bp*=amp_normalize(curfreq);
			bp*=double(min(rc_on,i))/double(rc_on);
			bp*=double(min(rc_off,durr+sustain-i))/double(rc_off);
			getsound[pos]+=bp;
			pos++;
		}
	}
	
}


void sound(BitDepth buffer[], double getsound[]) {
	for(long long i=0; i<NUM_SAMPLES; i++) {
		buffer[i] = short(getsound[i]/maxi*20000.0);
	}return;
}

void getmaxi(double getsound[]){
	for(long long i=0; i<NUM_SAMPLES; i++){
		maxi=max(abs(getsound[i]),maxi);
	}cout<<maxi<<endl;
	return;
}

template<typename _Ty> void write(ofstream& stream, const _Ty& ty) {
	stream.write((const char*)&ty, sizeof(_Ty));
}

void writeWaveFile(const char* filename, BitDepth* buffer) {
	ofstream stream(filename, ios::binary);

	stream.write("RIFF", 4);
	::write<int>(stream, 36+(NUM_SAMPLES*sizeof(BitDepth)));
	stream.write("WAVEfmt ", 8);
	::write<int>(stream, 16);
	::write<short>(stream, 1);
	::write<unsigned short>(stream, channels);
	::write<int>(stream, samplerate);
	::write<int>(stream, samplerate*channels*sizeof(BitDepth));
	::write<short>(stream, channels*sizeof(BitDepth));
	::write<short>(stream, sizeof(BitDepth)*8);
	stream.write("data", 4);
	::write<int>(stream, NUM_SAMPLES*sizeof(BitDepth));
	stream.write((const char*)&buffer[0], NUM_SAMPLES*sizeof(BitDepth));
	stream.close();
}

void readinput(){
	cin>>bpm;
	double note=0;
	double t=0.0,dur=0.0;double latest=0.0;
	while(cin>>note>>t>>dur){
		notes.push_back({note,{t,dur}});
//		notes.push_back({130-note,{t,dur}});//invert
		latest=max(latest,t+dur);
	}
	NUM_SAMPLES=44100ll*int(latest*60.0/bpm+5.0);
//	NUM_SAMPLES=44100ll*60;
//	for(auto e:notes)cout<<e.first<<' '<<e.second.first<<' '<<e.second.second<<endl;
	return;
}

void dothing(BitDepth buffer[], double getsound[]){
	makesomething(getsound);
	getmaxi(getsound);
	sound(buffer,getsound);
	return;
}

int main(int argc, char** argv) {
	freopen("wtc41p.txt","r",stdin);
	SetConsoleTitleA("wAvE gENARTOR");
	string filename = "wtc41p";
	readinput();
	
	
	BitDepth* buffer = new BitDepth[NUM_SAMPLES];
	double* getsound = new double[NUM_SAMPLES];
//		makesomething(getsound);
//		cout<<maxi<<endl;
//	sound(buffer,getsound);
	dothing(buffer,getsound);

	writeWaveFile(string(filename+string(".wav")).c_str(), buffer);
	delete[] buffer;

	cout << filename << ".wav written!" << endl;
	cin.get();
	return 0;
}
