#include <bits/stdc++.h>
#define fi first
#define se second
using namespace std;
int main(){
	freopen("notyetwtc41p.txt","r",stdin);
	freopen("wtc41p.txt","w",stdout);
	cout<<60<<endl;
	int a;cin>>a;
	double offset[a];
	vector<pair<double, double> > bpm;
	double st,b;
	for(int i=0; i<a; i++){
		cin>>st>>b;
		bpm.push_back({st,b});
	}
	bpm.push_back({1000000,b});
	offset[0]=0.0;
	for(int i=1; i<a; i++){
		offset[i]=offset[i-1]+(bpm[i].fi-bpm[i-1].fi)/bpm[i-1].se*60.0;
	}
	vector<pair<double,pair<double,double> > > mus;
	int num;cin>>num;
	for(int i=0; i<num; i++){
		double n,s,d;cin>>n>>s>>d;
		mus.push_back({n,{s,d}});
	}
	int pt=0;
	for(int i=0; i<num; i++){
		if(pt<a && mus[i].se.fi>=bpm[pt+1].fi)pt++;
		double dur = 0;
		double back=mus[i].se.fi+mus[i].se.se;
		double start=mus[i].se.fi;
		for(int j=pt; j<a; j++){
			if(back<=bpm[j].fi)break;
			double curbpm=bpm[j].se;
			dur+=(min(back,bpm[j+1].fi)-max(start,bpm[j].fi))*60.0/curbpm;
		}
		cout<<mus[i].fi<<' '<<offset[pt]+(mus[i].se.fi-bpm[pt].fi)*60.0/bpm[pt].se<<' '<<dur<<endl;
		
	}
}
