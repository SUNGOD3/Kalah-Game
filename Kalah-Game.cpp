#include <bits/stdc++.h>
#include <stdlib.h> 
#include <time.h> 
#define b *7+6
using namespace std;
int dMAX,a[14],ans,amv,stp;
long long node;
bool relc(int h[],int pk){ 
	//判斷一個state經過一個action後的new state 
    //輸入:h[]=原始陣列(狀態空間),pk=action(選取的種子) 
    //輸出:boolean 表示回合是否連續，並且將輸入的state更改為action後的state 
	int tmp=h[pk],idx=pk,ck=0,j=0,r=h[pk];
    for(;--r>0;++h[idx])
        (++idx>13||(pk<6&&idx==13))?idx=0:(6<pk&&idx==6)?++idx:0;
    for(++idx%=14;1;++j)
    	if(pk<6||j){
    		(pk<6)?idx%=13:(idx==6)?++idx:0;
    		(idx==j b)?ck=1:(j*7<=idx&&idx<j b&&!h[idx]&&h[12-idx])?h[j b]+=h[12-idx]+1,--h[idx],h[12-idx]=0:0;
            ++h[idx],h[pk]-=tmp;
    		break;
		}
    for(int j=0,tf,i;j<2;++j){
    	for(i=j*7,tf=1;i<j b;(h[i++])?tf=0:0);
		for(i=(j^1)*7;tf&&i<(j^1) b;h[i++]=0)
           	h[(j^1) b]+=h[i];
	}
    return ck;
}

bool gend(int h[]){
	//判斷該state是否代表遊戲結束 (某一方的豆子拿完了) 
	bool ed1=0,ed2=0;
	for(int i=0;i<6;++i)
		ed1+=h[i],ed2+=h[i+7];
	for(int i=0;(!ed1||!ed2)&&i<6;++i)
		h[6]+=h[i],h[13]+=h[i+7],h[i]=h[i+7]=0;
	return (!ed1||!ed2);
}
int mnx(int h[],int d,int turn,int plr){
	//判斷在某狀態下某玩家的選擇 
	//輸入:h[]=原始陣列,d=當前深度,turn=決定回傳max或min decision,plr=目前做決定的玩家
	//額外輸入:dMAX=最大深度 
	//輸出:v=做出該抉擇後在到深度上限/遊戲結束時得到的最大分數
	//額外輸出:ans=最終抉擇 
	++node;//計算擴展的節點數 
    if (gend(h)||d>=dMAX)return ((!stp)?h[6]-h[13]:h[13]-h[6]);
    int v=((turn)?-99:99),sh[14];
    for(int i=0;i<14;++i)
		sh[i]=h[i];
    for(int i=0;i<6;++i){
		if(!sh[i+plr*7])continue;
		v=((relc(h,i+plr*7))?((turn)?max(v,mnx(h,d+2,turn,plr)):min(v,mnx(h,d+2,turn,plr))):((turn)?max(v,mnx(h,d+1,turn^1,plr^1)):min(v,mnx(h,d+1,turn^1,plr^1))));
		if(!d&&v>amv)
			ans=i+plr*7,amv=v;
		for(int j=0;j<14;++j)
			h[j]=sh[j];
	}
    return v;
}
int mnxab(int h[],int d,int turn,int plr,int A,int B){
	//minimax aB剪枝版 
	++node;//計算擴展的節點數 
    if (gend(h)||d>=dMAX)return ((!stp)?h[6]-h[13]:h[13]-h[6]);
    int v=((turn)?B:A),sh[14];
    for(int i=0;i<14;++i)
		sh[i]=h[i];
    for(int i=0;i<6;++i){
		if((!sh[i+plr*7])||(turn&&v>=A)||(!turn&&v<=B))continue;
		v=((relc(h,i+plr*7))?((turn)?max(v,mnxab(h,d+2,turn,plr,A,v)):min(v,mnxab(h,d+2,turn,plr,v,B))):((turn)?max(v,mnxab(h,d+1,turn^1,plr^1,A,v)):min(v,mnxab(h,d+1,turn^1,plr^1,v,B))));
		if(!d&&v>amv)
			ans=i+plr*7,amv=v;
		for(int j=0;j<14;++j)
			h[j]=sh[j];
	}
    return v;
}
int input(int h[],int plr,int D){
	//輸入:h[]=當前遊戲狀態(14個數字),plr=玩家(0或1),D=搜尋深度
	//輸出:ans=最終選擇(0-5或7-12) 
	for(int i=0;i<14;++i)
		a[i]=h[i];
	stp = plr;
	dMAX = D;
	amv=-99;
	mnxab(a,0,1,stp,99,-99);
	return ans;
} 
void plt(int h[]){
	cout << "\n------------棋盤-------------\n";
	cout << "倉庫1  #12 #11 #10  #9  #8  #7  倉庫0\n      ";
	for(int i=12;i>6;--i)
		cout << h[i] << "    ";
	cout << "\n  " << h[13] << " ------------------------------- " << h[6] << "\n      ";
	for(int i=0;i<6;++i)
		cout << h[i] << "    ";
	cout << "\n倉庫1  #0  #1  #2   #3  #4  #5  倉庫0\n\n";
}
int main(){
	srand(time(NULL));
	int mod,lv,lv2,is;
	cout << "請輸入模式(1=與AI人機對戰/2=看人機互打/3=分析同狀態下的node拓展數/other=離開):";
	cin >> mod;
	if(mod==1){
		cout << "\n選擇AI人機難度(0=隨機選/1~12=人機預判回合數/other=離開)和開始遊戲方向(0下/1上):";
		cin >> lv >> is;
		if((is!=1&&is!=0)||(lv<0||lv>12)){
			cout << "輸入錯誤，"; 
		}
		else{
			int game[14]={4,4,4,4,4,4,0,4,4,4,4,4,4,0},round=0;
			while(1){
				cout << "回合:" << ++round << "\n";
				if(gend(game)){
					cout << "遊戲結束!\n最終成績:玩家0=" << game[6] << " 玩家1=" << game[13];
					if(game[6]==game[13])
						cout << "\n平手";
					else if((is==0&&game[6]>game[13])||(is&&game[6]<game[13]))
						cout << "\n你贏了";
					else
						cout << "\n你輸了";
					break; 
				} 
				if(round==1)plt(game);
				if(is==0){
					int x;
					cout << "輪到玩家回合\n選擇我方的洞(0-5):"; 
					while(cin >> x){
						if(x<0||x>5||game[x]==0)cout << "非法輸入\n";
						else break;
					}
					cout << "你選了#" << x << "後棋盤狀態:\n"; 
					relc(game,x);
					plt(game); 
				}
				if(gend(game)){
					cout << "遊戲結束!\n最終成績:玩家0=" << game[6] << " 玩家1=" << game[13];
					if(game[6]==game[13])
						cout << "\n平手";
					else if((is==0&&game[6]>game[13])||(is&&game[6]<game[13]))
						cout << "\n你贏了";
					else
						cout << "\n你輸了";
					break; 
				} 
				if(lv==0){
					int x = rand()%6+(is^1)*7;
					while(game[x]==0)x = rand()%6+(is^1)*7;
					cout << "人機選了#" << x << "後棋盤狀態:\n"; 
					relc(game,x);
					plt(game);
				}
				else if(lv>0&&lv<13){
					int ch=input(game,is^1,lv);
					cout << "人機選了#" << ch << "後棋盤狀態:\n"; 
					relc(game,ch);
					plt(game);
				}
				if(is==1){
					int x;
					cout << "輪到玩家回合\n選擇我方的洞(7-13):"; 
					while(cin >> x){
						if(x<7||x>13||game[x]==0)cout << "非法輸入\n";
						else break;
					}
					cout << "你選了#" << x << "後棋盤狀態:\n"; 
					relc(game,x);
					plt(game);
				}
			} 
		}
	}
	else if(mod==2){
		cout << "輸入人機0和人機1的實力(0-12)\n";
		while(cin >> lv >> lv2){
			if(lv<0||lv>12||lv2<0||lv2>12)cout << "非法輸入\n";
			else break;
		}
		int sc0=0,sc1=0;
		for(int i=1;i<=1000;++i){
			cout << "第" << i << "局:";
			int game[14]={4,4,4,4,4,4,0,4,4,4,4,4,4,0},round=0;
			while(1){
				if(gend(game)){
					if(game[6]==game[13]){
						cout << "平手\n";
						++sc0;++sc1;
					}
					else if(game[6]>game[13]){
						cout << "人機0贏了\n";
						++sc0;
					}
					else{
						cout << "人機1贏了\n";
						++sc1;
					}
					break;
				}
				if(lv==0){
					int x = rand()%6;
					while(game[x]==0)x = rand()%6;
					relc(game,x);
				}
				else if(lv>0&&lv<13){
					int ch=input(game,0,lv);
					relc(game,ch);
				}
				if(gend(game)){
					if(game[6]==game[13]){
						cout << "平手\n";
						++sc0;++sc1;
					}
					else if(game[6]>game[13]){
						cout << "人機0贏了\n";
						++sc0;
					}
					else{
						cout << "人機1贏了\n";
						++sc1;
					}
					break;
				}
				if(lv2==0){
					int x = rand()%6+7;
					while(game[x]==0)x = rand()%6+7;
					relc(game,x);
				}
				else if(lv2>0&&lv2<13){
					int ch=input(game,1,lv2);
					relc(game,ch);
				}
			}
			if(lv&&lv2)break;
		}
		cout << "玩家0分數:" << sc0 << "\n玩家1分數:" << sc1 << "\n";
	}
	else if(mod==3){
		cout << "輸入state/player/dMAX:";
		while(1){
			int game[14],plr,dM;
			while(1){
				int f=0;
				for(int i=0;i<14;++i){
					cin >> game[i];
					if(game[i]<0)f=1;
				}
				cin >> plr >> dM;
				if(plr<0||dM<0)f=1;
				if(plr!=0&&plr!=1){
					cout << "玩家必須是0或1\n";
				}
				else if(f){
					cout << "不能有負數\n";
				}
				else if(dM<=0||dM>12){
					cout << "dMAX範圍為1-12\n";
				}
				else{
					break;
				}
			}
			for(int i=0;i<14;++i)
				a[i]=game[i];
			stp = plr;
			dMAX = dM;
			amv=-99;
			node=0;
			cout << "minimax無剪枝的結果是:" << mnx(game,0,1,plr) << "\n擴展節點數為:" ;
			cout << node << "\n";
			for(int i=0;i<14;++i)
				a[i]=game[i];
			stp = plr;
			dMAX = dM;
			amv=-99;
			node=0;
			cout << "minimax剪枝(aB)的結果是:" << mnxab(game,0,1,plr,99,-99) << "\n擴展節點數為:" ;
			cout << node << "\n";
		} 
	}
	cout << "程式結束";
	while(mod!=-1){mod=1;};
	return 0;
}
