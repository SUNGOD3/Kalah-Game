#include <bits/stdc++.h>
#include <stdlib.h> 
#include <time.h> 
#define b *7+6
using namespace std;
int dMAX,a[14],ans,amv,stp;
long long node;
bool relc(int h[],int pk){ 
	//�P�_�@��state�g�L�@��action�᪺new state 
    //��J:h[]=��l�}�C(���A�Ŷ�),pk=action(������ؤl) 
    //��X:boolean ��ܦ^�X�O�_�s��A�åB�N��J��state��אּaction�᪺state 
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
	//�P�_��state�O�_�N��C������ (�Y�@�誺���l�����F) 
	bool ed1=0,ed2=0;
	for(int i=0;i<6;++i)
		ed1+=h[i],ed2+=h[i+7];
	for(int i=0;(!ed1||!ed2)&&i<6;++i)
		h[6]+=h[i],h[13]+=h[i+7],h[i]=h[i+7]=0;
	return (!ed1||!ed2);
}
int mnx(int h[],int d,int turn,int plr){
	//�P�_�b�Y���A�U�Y���a����� 
	//��J:h[]=��l�}�C,d=��e�`��,turn=�M�w�^��max��min decision,plr=�ثe���M�w�����a
	//�B�~��J:dMAX=�̤j�`�� 
	//��X:v=���X�ӧ�ܫ�b��`�פW��/�C�������ɱo�쪺�̤j����
	//�B�~��X:ans=�̲ק�� 
	++node;//�p���X�i���`�I�� 
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
	//minimax aB�ŪK�� 
	++node;//�p���X�i���`�I�� 
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
	//��J:h[]=��e�C�����A(14�ӼƦr),plr=���a(0��1),D=�j�M�`��
	//��X:ans=�̲׿��(0-5��7-12) 
	for(int i=0;i<14;++i)
		a[i]=h[i];
	stp = plr;
	dMAX = D;
	amv=-99;
	mnxab(a,0,1,stp,99,-99);
	return ans;
} 
void plt(int h[]){
	cout << "\n------------�ѽL-------------\n";
	cout << "�ܮw1  #12 #11 #10  #9  #8  #7  �ܮw0\n      ";
	for(int i=12;i>6;--i)
		cout << h[i] << "    ";
	cout << "\n  " << h[13] << " ------------------------------- " << h[6] << "\n      ";
	for(int i=0;i<6;++i)
		cout << h[i] << "    ";
	cout << "\n�ܮw1  #0  #1  #2   #3  #4  #5  �ܮw0\n\n";
}
int main(){
	srand(time(NULL));
	int mod,lv,lv2,is;
	cout << "�п�J�Ҧ�(1=�PAI�H�����/2=�ݤH������/3=���R�P���A�U��node�ݮi��/other=���}):";
	cin >> mod;
	if(mod==1){
		cout << "\n���AI�H������(0=�H����/1~12=�H���w�P�^�X��/other=���})�M�}�l�C����V(0�U/1�W):";
		cin >> lv >> is;
		if((is!=1&&is!=0)||(lv<0||lv>12)){
			cout << "��J���~�A"; 
		}
		else{
			int game[14]={4,4,4,4,4,4,0,4,4,4,4,4,4,0},round=0;
			while(1){
				cout << "�^�X:" << ++round << "\n";
				if(gend(game)){
					cout << "�C������!\n�̲צ��Z:���a0=" << game[6] << " ���a1=" << game[13];
					if(game[6]==game[13])
						cout << "\n����";
					else if((is==0&&game[6]>game[13])||(is&&game[6]<game[13]))
						cout << "\n�AĹ�F";
					else
						cout << "\n�A��F";
					break; 
				} 
				if(round==1)plt(game);
				if(is==0){
					int x;
					cout << "���쪱�a�^�X\n��ܧڤ誺�}(0-5):"; 
					while(cin >> x){
						if(x<0||x>5||game[x]==0)cout << "�D�k��J\n";
						else break;
					}
					cout << "�A��F#" << x << "��ѽL���A:\n"; 
					relc(game,x);
					plt(game); 
				}
				if(gend(game)){
					cout << "�C������!\n�̲צ��Z:���a0=" << game[6] << " ���a1=" << game[13];
					if(game[6]==game[13])
						cout << "\n����";
					else if((is==0&&game[6]>game[13])||(is&&game[6]<game[13]))
						cout << "\n�AĹ�F";
					else
						cout << "\n�A��F";
					break; 
				} 
				if(lv==0){
					int x = rand()%6+(is^1)*7;
					while(game[x]==0)x = rand()%6+(is^1)*7;
					cout << "�H����F#" << x << "��ѽL���A:\n"; 
					relc(game,x);
					plt(game);
				}
				else if(lv>0&&lv<13){
					int ch=input(game,is^1,lv);
					cout << "�H����F#" << ch << "��ѽL���A:\n"; 
					relc(game,ch);
					plt(game);
				}
				if(is==1){
					int x;
					cout << "���쪱�a�^�X\n��ܧڤ誺�}(7-13):"; 
					while(cin >> x){
						if(x<7||x>13||game[x]==0)cout << "�D�k��J\n";
						else break;
					}
					cout << "�A��F#" << x << "��ѽL���A:\n"; 
					relc(game,x);
					plt(game);
				}
			} 
		}
	}
	else if(mod==2){
		cout << "��J�H��0�M�H��1����O(0-12)\n";
		while(cin >> lv >> lv2){
			if(lv<0||lv>12||lv2<0||lv2>12)cout << "�D�k��J\n";
			else break;
		}
		int sc0=0,sc1=0;
		for(int i=1;i<=1000;++i){
			cout << "��" << i << "��:";
			int game[14]={4,4,4,4,4,4,0,4,4,4,4,4,4,0},round=0;
			while(1){
				if(gend(game)){
					if(game[6]==game[13]){
						cout << "����\n";
						++sc0;++sc1;
					}
					else if(game[6]>game[13]){
						cout << "�H��0Ĺ�F\n";
						++sc0;
					}
					else{
						cout << "�H��1Ĺ�F\n";
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
						cout << "����\n";
						++sc0;++sc1;
					}
					else if(game[6]>game[13]){
						cout << "�H��0Ĺ�F\n";
						++sc0;
					}
					else{
						cout << "�H��1Ĺ�F\n";
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
		cout << "���a0����:" << sc0 << "\n���a1����:" << sc1 << "\n";
	}
	else if(mod==3){
		cout << "��Jstate/player/dMAX:";
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
					cout << "���a�����O0��1\n";
				}
				else if(f){
					cout << "���঳�t��\n";
				}
				else if(dM<=0||dM>12){
					cout << "dMAX�d��1-12\n";
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
			cout << "minimax�L�ŪK�����G�O:" << mnx(game,0,1,plr) << "\n�X�i�`�I�Ƭ�:" ;
			cout << node << "\n";
			for(int i=0;i<14;++i)
				a[i]=game[i];
			stp = plr;
			dMAX = dM;
			amv=-99;
			node=0;
			cout << "minimax�ŪK(aB)�����G�O:" << mnxab(game,0,1,plr,99,-99) << "\n�X�i�`�I�Ƭ�:" ;
			cout << node << "\n";
		} 
	}
	cout << "�{������";
	while(mod!=-1){mod=1;};
	return 0;
}
