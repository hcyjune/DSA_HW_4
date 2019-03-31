#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <bitset>//check
 
using namespace std;
 
int task;
char chess;
int alpha_initial=0;
int beta_initial=2;
long long one=1;
long long root=0;
int chess_num=0;
unordered_map<long long, int> m[3][3];
 
int WINLOSE(long long &a){
	int line_X=0;
	int line_O=0;
	for (int i=0;i<49;i=i+10){//check row
		int num_X=0;
		int num_O=0;
		for (int j=0;j<9;j=j+2){
			int k=i+j;
			if ((a>>k)%4==1)//X
				num_X+=1;
			else if ((a>>k)%4==2)//O
				num_O+=1;
		}
		if (num_X>=4)
			line_X+=1;
		else if (num_O>=4)
			line_O+=1;
	}
	for (int j=0;j<9;j=j+2){//check column
		int num_X=0;
		int num_O=0;
		for (int i=0;i<49;i=i+10){
			int k=i+j;
			if ((a>>k)%4==1)//X
				num_X+=1;
			else if ((a>>k)%4==2)//O
				num_O+=1;
		}
		if (num_X>=4)
			line_X+=1;
		else if (num_O>=4)
			line_O+=1;
	}
	int k;
	for (int i=0;i<2;i++){//check diagonal
		int num_X=0;
		int num_O=0;
		for (int j=0;j<5;j++){
			if (i==0)
				k=12*j;
			else if (i==1)
				k=8*(j+1);
			if ((a>>k)%4==1)//X
				num_X+=1;
			else if ((a>>k)%4==2)//O
				num_O+=1;
		}
		if (num_X>=4)
			line_X+=1;
		else if (num_O>=4)
			line_O+=1;
	}
	int winlose=1;//tie
	if (line_X>line_O)
		winlose=0;//X wins
	else if (line_X<line_O)
		winlose=2;//O wins
	return winlose;
}
int PRUNE(long long &node,int alpha,int beta) {
	//auto it = m[][].find();
	int ori_alpha = alpha;
	int ori_beta = beta;
	auto it=m[alpha][beta].find(node);
	if (it!=m[alpha][beta].end())
		return it->second;
	else{
		vector<int> empty;//check empty position to calculate depth, player, children
		for (int i=0;i<49;i=i+2){
			if ((node>>i)%4==0)
				empty.push_back(i);
		}
		if (empty.size()==3){//depth=0
			long long node_tmp=node;
			for (int i=0;i<empty.size();i++)
				node_tmp+=(one<<empty[i]);//X
			int tmp=WINLOSE(node_tmp);
			m[ori_alpha][ori_beta][node]=tmp;
			return tmp;
		}
		else{
			for (int i=0;i<empty.size()-1;i++){//children
				for (int j=i+1;j<empty.size();j++){
					long long node_tmp=node;
					if (empty.size()%4==1){//player=O
						node_tmp=node+(one<<(empty[i]+1));
						node_tmp+=(one<<(empty[j]+1));;
						int tmp=PRUNE(node_tmp,alpha,beta);//prevent calling PRUNE twice
						if (tmp>alpha)
							alpha=tmp;
					}
					else if (empty.size()%4==3){//player=X
						node_tmp=node+(one<<empty[i]);
						node_tmp+=(one<<empty[j]);
						int tmp=PRUNE(node_tmp,alpha,beta);
						if (tmp<beta)
							beta=tmp;
					}
					if (beta<=alpha){
						i=empty.size();
						j=empty.size();
					}
				}
			}
			if (empty.size()%4==1){//player=O
				m[ori_alpha][ori_beta][node]=alpha;
				return alpha;
			}
			else if (empty.size()%4==3){//player=X
				m[ori_alpha][ori_beta][node]=beta;
				return beta;
			}
		}
	}
}
int main(int argc,char* argv[]){
	cin >> task;
	while(chess_num<=25*task){
		cin >> chess;
		if (chess=='O')
			root+=(1<<1);
		else if (chess=='X')
			root+=1;
		chess_num+=1;
		if (chess_num%25!=0)
			root=root<<2;
		else if (chess_num%25==0){//root done
			int result=PRUNE(root,alpha_initial,beta_initial);//alpha beta pruning
			if (result==2)
				cout << "O win" << endl;
			else if (result==1)
				cout << "Draw" << endl;
			else
				cout << "X win" << endl;
			root=0;
		}
	}
	return 0;
}
