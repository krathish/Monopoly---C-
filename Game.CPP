#include<iostream.h>
#include<ctype.h>
#include<string.h>
#include<conio.h>
#include<stdio.h>
#include<math.h>
#include<fstream.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>


ifstream f1,f2;
ofstream f3,f4;
int ppsubc,pqsubc,v;
int i,j,m=13,n=79,flag=0,flag2=0;
int pos1[2]={1,1},pos2[2]={1,1};
class player{
public:	int money;
player(){money=25000;}

}pp,pq;

class location{

	char name[20];
	int cost;
	public:
	int rent;

public:
	int x,y;
	int owner;
	void accept(){
		cout<<"x";cin>>x;
		cout<<"y";cin>>y;
		cout<<"name";gets(name);
		cout<<"cost";cin>>cost;
		cout<<"rent";cin>>rent;
		cout<<"owner";cin>>owner;

	}

	void display(){
		//cout<<"x";cout<<x<<"\t";
		//cout<<"y";cout<<y<<"\t";
		if(v==1)
		{cout<<"\n\t\tPosition of player P";}
		else if(v==2){cout<<"\n\t\tPosition of player Q";}
		cout<<"\nNAME: ";puts(name);
		cout<<"COST: ";cout<<cost<<"\t";
		cout<<"RENT: ";cout<<rent<<"\t";
		cout<<"OWNER: ";
		if(owner==0){cout<<"NO OWNER";}
		else if(owner==1)cout<<"P" ;
		else if(owner==2)cout<<"Q";
	}
	int rx(){return x;}
	int ry(){return y;}
	int rcost(){return cost;}
	int rrent(){return rent;}
	int rowner(){return owner;}
	char* rname(){return name;}


}p1;
void result_of_game();

void instruct()
{cout<<"            Read the INSTRUCTIONS and proceed as given below"<<endl;
 cout<<"            The computer will roll the dice for you"<<endl;
 cout<<"            And change your position accordingly. "<<endl<<"            To exit the game press 'e' at any time\n"<<endl<<"\nPress enter to Proceed\n";
 getch();
}

/*
void kaand(){
f1.open("BACKUP",ios::binary);
location p2;
cout<<endl;
while(f1.read((char*)&p2,sizeof(p2))){
p2.display();
cout<<endl;
}
}*/

void playerdisp()
{

 if(pp.money>=ppsubc )
  {pp.money=pp.money-ppsubc;
   ppsubc=0;	}
 else
 {cout<<"Player P you have lost, Q has won, press enter to exit";getch();}
 if(pq.money>=pqsubc )
  {pq.money=pq.money-pqsubc;
  pqsubc=0;}
 else
 {cout<<"Player Q you have lost, P has won, press enter to exit";getch();}

cout<<endl<<"PLAYER P CASH: $"<<pp.money;
cout<<'\t'<<"PLAYER Q CASH: $"<<pq.money<<endl;
}


void create(){
f3.open("backup",ios::binary | ios::app);
p1.accept();
f3.write((char*)&p1,sizeof(p1));
cout<<"RECORD ADDED, press enter";
f3.close();
}


void backupfile(){
f3.open("text",ios::binary);
f2.open("backup",ios::binary);
while(f2.read((char*)&p1,sizeof(p1)))
{
f3.write((char*)&p1,sizeof(p1));
}
f3.close();
f2.close();
}
void rents(int rent,int v)
{if(v==1)
	{pp.money=pp.money-rent;pq.money=pq.money+rent;
	cout<<"\nRent Paid to Q by P\n";}
else if(v==2)
	{pq.money=pq.money-rent;pp.money=pp.money+rent;
	cout<<"\nRent Paid to P by Q\n";}
}
void modowner(int x1,int y1,int n){
f3.open("copy",ios::binary);
f2.open("text",ios::binary);
//cout<<" (only owner changed) \n";
while(f2.read((char*)&p1,sizeof(p1)))
{ if((p1.rx()!=x1)||(p1.ry()!=y1)){

	 f3.write((char*)&p1,sizeof(p1));
	 }
	else{ p1.owner=n;

	f3.write((char*)&p1,sizeof(p1));
	 cout<<"Purchase complete\n";
	 //p1.display();
	}
}

f3.close();
f2.close();
remove("text");
rename("copy","text");
}

void searchxy(int x1,int y1){
f1.open("text",ios::binary);
while(f1.read((char*)&p1,sizeof(p1)))
{if(p1.rx()==x1 && p1.ry()==y1)
	{
	 if( v==1  && pp.money>=p1.rcost() && p1.owner==0)
	  {

		cout<<endl<<"PLAYER P CASH: $"<<pp.money;
		cout<<'\t'<<"PLAYER Q CASH: $"<<pq.money<<endl;

		p1.display();
		cout<<"\nP, do you want to buy the property?(Y/N):";
		char ch;
		cin>> ch;
		if(ch=='e'){result_of_game();getch();exit(0);}
		cout<<endl;
		if(toupper(ch)=='Y')
			{
			ppsubc=p1.rcost();
			modowner(pos1[0],pos1[1],1);
			}

		else if(toupper(ch)=='N')
			p1.owner=0;


	  }
	  else if(v==1 && pp.money>=p1.rrent() &&p1.owner==2)
	  {p1.display();rents(p1.rrent(),v); }
	  else if( v==1 && p1.owner==1){p1.display();cout<<"\nAlready owned";}

	  if( v==2  && pq.money>=p1.rcost() && p1.owner==0)
	  {p1.display();
	  cout<<"\nQ, do you want to buy the property?(Y/N):";
		char ch;
		cin>> ch;
		if(ch=='e'){result_of_game();getch();exit(0);}
		cout<<endl;
		if(toupper(ch)=='Y')
			{
			pqsubc=p1.rcost();
			modowner(pos2[0],pos2[1],2);
			}

		else if(toupper(ch)=='N')
			p1.owner=0;
	}

	  else if(v==2 && pq.money>=p1.rrent() &&p1.owner==1)
	  { p1.display();rents(p1.rrent(),v); }
	  else if(v==2 && p1.owner==2){p1.display();cout<<"\nAlready owned";}

		}
}
f1.close();
}

int searchowner(int n){
int asset=0;
f1.open("text",ios::binary);
while(f1.read((char*)&p1,sizeof(p1)))
{
if(p1.rowner()==n)
	{
	asset=asset+p1.rcost();
	}
}
f1.close();
return asset;
}
void result_of_game(){
int assetp=searchowner(1)+pp.money;
int assetq=searchowner(2)+pp.money;
	if(assetp>assetq){
	cout<<"P is the overall winner";}
	else if(assetq>assetp){
	cout<<"Q is the overall winner";}
	else
	cout<<"BOTH ARE THE WINNERS";
}

void show() {
f1.open("text",ios::binary);
while(f1.read((char*)&p1,sizeof(p1)))
	{p1.display();
	}
f1.close();
}



void move(int pos1[]){
int i;
randomize();
int r=1;
if(pos1[0]==1){
for(i=0;i<=2*r&& pos1[1]!=77;r--,pos1[1]+=2);
}
if(pos1[1]==77){
for(i=0;i<=2*r&& pos1[0]!=11;r--,pos1[0]+=2);
}
if(pos1[0]==11){
for(i=0;i<=2*r&& pos1[1]!=1;r--,pos1[1]-=2);
}
if(pos1[1]==1) {
for(i=0;i<=2*r&& pos1[0]!=1;r--,pos1[0]-=2);
}


}




void display()
{clrscr();

 char a[13][79];
 for(i=0;i<m;i++)
 {for(j=0;j<n;j++)
	{ if(i==0 || i==m-1)
		a[i][j]='_';
	else  if (j==0 || j==n-1)
		a[i][j]='|';
	else if(j==2 || j==n-3 ||( i==1 && j%4==0) ||( i==m-2 && j%4==0))
		a[i][j]='|';
	else if(i==2 || i==m-3 ||(i%4==0) &&(j==1) ||(i%4==0) &&(j==n-2) )
	a[i][j]='-';
	else
		a[i][j]=' ';

 }
}
 a[1][1]='S';
 a[pos1[0]][pos1[1]]='P';
 a[pos2[0]][pos2[1]]='Q';
 if(pos1[0]==pos2[0] && pos1[1]==pos2[1])
 {
 a[pos2[0]][pos2[1]]='B';
 }

for(i=0;i<m;i++)
{for(j=0;j<n;j++)
 {cout<<a[i][j];}
 cout<<endl;
}


v=1; searchxy(pos1[0],pos1[1]) ;
v=2; searchxy(pos2[0],pos2[1]) ;


playerdisp();
move(pos1);
move(pos1);

move(pos2);


}


void main(){

clrscr();
instruct();
char x;
cout<<"Do you want to continue last saved game?\n(Note cash of players will still reset to $25000) (Y/N):";cin>>x;
if(toupper(x)=='N')
backupfile();
char ch='\n';
while(ch!='e'){
display();
ch=getchar();
}
if(ch=='e'){
int assetp=searchowner(1)+pp.paisa;
int assetq=searchowner(2)+pq.paisa;
	if(assetp>assetq){
	cout<<"P is the overall winner";}
	else if(assetq>assetp){
	cout<<"Q is the overall winner";}
	else
	cout<<"BOTH ARE THE WINNERS";
}
//reset();
getch();
}
