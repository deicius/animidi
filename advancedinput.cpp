#include <bits/stdc++.h>
using namespace std;
bool cmp(pair<int,pair<double,double> > a, pair<int,pair<double,double> >b){
	if(a.second.first==b.second.first)return a.first<b.first;
	else return a.second.first<b.second.first;
}
bool cmp2(pair<int,pair<double,double> > a, pair<int,pair<double,double> >b){
	return a.first<b.first;
}
vector<pair<double,pair<double,double> > > v;
void inputbruh(int a,double qwerty){
//	cout<<a<<' '<<qwerty<<endl;
	if(a==0){
		//single note
		double note;double dur,st;cin>>note>>st>>dur;
		st+=qwerty;
		v.push_back({note,{st,dur}});
	}
	if(a==1){
		//run of notes
		int num=0;cin>>num;
		double dur=0;double st=0;cin>>st;cin>>dur;
		st+=qwerty;
			double spacing=0;cin>>spacing;
		for(int i=0; i<num; i++){
			double note;cin>>note;
			if(note!=-1)v.push_back({note,{st+double(i)*spacing, dur}});
		}
	}
	if(a==2){
		//trills
		int note1,note2,num;double dur,st;cin>>note1>>note2>>num>>st>>dur;
		st+=qwerty;
		for(int i=0; i<num; i++){
			if(i%2==0)v.push_back({note1,{st+i*dur,dur}});
			if(i%2==1)v.push_back({note2,{st+i*dur,dur}});
		}
	}
	if(a==3){
//		enter voices
		double pos=0;
		cin>>pos;
		pos+=qwerty;
		int num=0;
		while(1){
			cin>>num;
			if(num==-2)break;
			double dur;cin>>dur;
//			cout<<num<<' '<<dur<<endl;
			for(int i=0; i<num; i++){
				double note;cin>>note;
				if(note!=-1)v.push_back({note,{pos+i*dur,dur}});
//				if(note==1)cout<<"WYGWYDGFDUYHGADSUYFG HAHUSIGFUYASS GFAUYGIFSYU IY \n";
//				cout<<note<<' ';
			}
			pos+=num*dur;
//			cout<<endl<<endl;
		}
	}
	if(a==4){
		float bar;cin>>bar;
		int bpb=3;
		while(1){
			int b;cin>>b;
			if(b==-3)break;
			inputbruh(b,double(bpb*bar));
		}
	}
	if(a==5){
		int num;double st,dur;cin>>num>>st>>dur;
		st+=qwerty;
		for(int i=0; i<num; i++){
			double note;cin>>note;
			if(note!=-1)v.push_back({note,{st,dur}});
		}
	}
}

int main(){
	freopen("advanced41p.txt","r",stdin);
	freopen("notyetwtc41p.txt","w",stdout);
	
	while(1){
		int a;cin>>a;
		if(a==-1)break;
		inputbruh(a,0);
	}
	double bpm=64;
	cout<<bpm<<endl;
	sort(v.begin(),v.end(),cmp);
	for(auto e:v)cout<<(e.first)<<' '<<e.second.first<<' '<<e.second.second<<endl;
}
