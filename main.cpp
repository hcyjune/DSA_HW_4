#include <iostream>
#include <deque>
#include <string>
#include <unordered_map>
using namespace std;
int main(){
	string s;
	cin >> s;
	deque<long long> v;
	long long x=29;
	char a='a';
	long long M=1000000007;
	v.push_back(0ll);
	for (int i=0;i<s.size();i++){
		long long tmp=s[i]-a+1;
		v.push_back(tmp%M);
	}
	int q,type;
	cin >> q;
	unordered_map<long long,int> m[10];
	for (int i=0;i<q;i++){
		cin >> type;
		if (type==1){
			char c;
			cin >> c;
			long long tmp=c-a+1;
			tmp=tmp%M;
			v.pop_front();
			v.push_front(tmp);
			v.push_front(0ll);
			long long y=v[0];
			for (int i=1;i<11;i++){
				y=(y*x+v[i])%M;
				auto it=m[i-1].find(y);
				if (it!=m[i-1].end())
					(it->second)++;
			}
		}
		else if (type==2){
			char c;
			cin >> c;
			long long tmp=c-a+1;
			v.push_back(tmp%M);
			long long y=v[0];
			for (int i=1;i<11;i++){
				long long z=v[v.size()-i];
				for (int j=1;j<i;j++)
					z=(z*x)%M;
				y=(y+z)%M;
				auto it=m[i-1].find(y);
				if (it!=m[i-1].end())
					(it->second)++;
			}
		}
		else{
			string ss;
			cin >> ss;
			int len=ss.size();
			deque<long long> vv;
			vv.push_back(0ll);
			for (int i=0;i<len;i++){
				long long tmp=ss[i]-a+1;
				vv.push_back((vv[i]*x+tmp)%M);
			}
			int flag=0;
			if (len<=10){
				auto it=m[len-1].find(vv[len]);
				if (it!=m[len-1].end()){
					cout << it->second << endl;
					flag=1;
				}
			}
			if (flag==0){
				deque<long long> vvv;
				vvv.push_back(0ll);
				for (int i=1;i<v.size();i++){
					vvv.push_back((vvv[i-1]*x+v[i])%M);
				}
	
				/*
				for (int i=0;i<v.size();i++){
					cout << v[i] << ' ';
				}
				cout << endl;
				*/
				int end=v.size()-len;
				int count=0;
				//cout << vv[len] << endl;
				long long y=1;
				for (int j=0;j<len;j++)
					y=(y*x)%M;
				for (int i=1;i<end+1;i++){
					long long tmp;
					tmp=vvv[i-1];
					tmp=(tmp*y)%M;
					long long hash=(vvv[i+len-1]-tmp+M)%M;
					if (hash==vv[len])
						count++;
				}
				if (len<=10)
					m[len-1][vv[len]]=count;
				cout << count << endl;
			}
		}
	}
	return 0;
}
