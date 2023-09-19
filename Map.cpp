#include <iostream>
#include<cstdlib>
#include<iomanip>
#include<fstream>
#include<time.h>
#include"Map.h"
#include<time.h>
using namespace std;
inline void newpage(){
   system("cls");
}
int player::playagain(){
    int x;
        cout<<setw(20)<<""<<"would you like to play again\n";
        cout<<setw(20)<<""<<"1:yes,i would like\n";
        cout<<setw(20)<<""<<"0:no,next time\n";
        do
       {
          while(!(cin >> x)) {
              cin.clear();
              cin.ignore(1000, '\n');
              cout << "please only choose a number\n";
             }
          if((x!=1)&&(x!=0)) cout<<"please only choose 1 or 0\n";
        }
        while((x!=1)&&(x!=0));
        if (x==1){
           newpage();
            return 1;
         }
         return 0 ;
}
void player::writestate(int x){
    int store[9];
    int i=0;
    ifstream fp ("states.txt");
    try{
       if (fp.is_open()){
           while(fp>>store[i]){
                i++;
                fp>>store[i];
                i++;
                fp>>store[i];
                i++;
           }
           fp.close();
        }
       else throw(2);
    }

    catch(int x){cout<<"could not open file('states.txt') to read current state than write last game result please check it existence manually\n";}

    try{
        ofstream fp2 ( "states.txt" );
        if (fp2.is_open()){
            for(i=0;i<=9;i++){
                switch(i)
                   { case 0:fp2<<store[i]<<"\n";break;
                    case 1:{if ((diff==1)&&(x==1)){fp2<<store[i]+1<<"\n";}
                           else fp2<<store[i]<<"\n";
                           }break;
                    case 2:{if ((diff==1)&&(x==0)){fp2<<store[i]+1<<"\n";}
                           else fp2<<store[i]<<"\n";
                           }break;
                    case 3:fp2<<store[i]<<"\n";break;
                    case 4:{if ((diff==2)&&(x==1)){fp2<<store[i]+1<<"\n";}
                             else fp2<<store[i]<<"\n";
                            }break;
                    case 5:{if ((diff==2)&&(x==0)){fp2<<store[i]+1<<"\n";}
                            else fp2<<store[i]<<"\n";
                           }break;
                    case 6:fp2<<store[i]<<"\n";break;
                    case 7:{if ((diff==3)&&(x==1)){fp2<<store[i]+1<<"\n";}
                          else fp2<<store[i]<<"\n";
                          }break;
                    case 8:{if ((diff==3)&&(x==0)){fp2<<store[i]+1<<"\n";}
                           else fp2<<store[i]<<"\n";
                          }break;
                }}

        }
            else throw('a');
    }

    catch(char x){cout<<"could not open file('states.txt') to write last game result please check it existence manually\n";}



}
//constructor call for function introduction that take of initialization
Map::Map(){
 introduction();
}
void Map::create(){
    int numbomb,a,b ;
    switch (diff){
    case 1:{
    d=6;
    numberofbomb=6;
    Map1 = new char*[6];
        for (int i = 0; i <6; i++){
                Map1[i] = new char[6];}
    Map2 = new char*[6];
        for (int i = 0; i <6; i++){
                Map2[i] = new char[6];}

     numbomb=6;}break;
     case 2:{
             d=10;
    numberofbomb=25;
    Map1 = new char*[10];
        for (int i = 0; i <10; i++){
                Map1[i] = new char[10];}
    Map2 = new char*[10];
        for (int i = 0; i <10; i++){
                Map2[i] = new char[10];}
    numbomb=25;
     }break;
     case 3:{
    d=15;
    numberofbomb=60;
    Map1 = new char*[15];
    for (int i = 0; i <15; i++){
                Map1[i] = new char[15];}
    Map2 = new char*[15];
    for (int i = 0; i <15; i++){
                Map2[i] = new char[15];}
     numbomb=60;
    }break;
    }

    for(int i=0;i<d;i++) {
        for(int j=0;j<d;j++){
            Map1[i][j]=' ';
            Map2[i][j]=' ';
        }
     }
srand(time(0));
     while(numbomb!=0){
            a=(rand() %d);
            b=(rand() %d);
            if (Map1[a][b]==' '){
            Map1[a][b]='*';
            numbomb--;}
     }
};
player::player(){
    diff=2;
    return;
}
Map::~Map(){
    for (int i = 0; i < d; i++){
      delete[] Map1[i];
      delete[] Map2[i];}
	delete[] Map1;
	delete[] Map2;
	Map1=0;
	Map2=0;

}
//function responsible for map drawing
void Map::draw(){
    //calculate the remaining number of bomb
        int numbomb=0;
        for(int i=0;i<d;i++) {
        for(int j=0;j<d;j++){
            if(Map2[i][j]=='*') numbomb++;
        }}
            cout<<setw(15)<<"number of remaining bombs "<<(numberofbomb-numbomb);
            cout<<"\n    ";
            //draw the map
            for (int j=0;j<d;j++){
            cout<<setw(3)<<j+1;}
            cout<<endl;
    for(int i=0;i<d;i++){
            cout<<"    ";
            for (int j=0;j<d;j++){
            cout<<"---";}
            cout<<endl;
            cout<<setw(4)<<i+1;
            for (int j=0;j<d;j++){
             cout<<"|"<<Map2[i][j]<<" ";
            }
            cout<<"|"<<endl;

    }
            cout<<"    ";
            for (int j=0;j<d;j++){
            cout<<"---";}
            cout<<endl;
}
//check the given case
int Map:: check(int x,int y){
    int z=0;
    //return 0 if case has mine in it which signal a loss
    if (Map1[x][y]=='*'){
             for(int i=0;i<d;i++) {
        for(int j=0;j<d;j++){
            Map2[i][j]=Map1[i][j];
        }
     }
            return 0;}
            //else calculate the number of bombs near it and show it
    else{
        if(x!=(d-1)){if(Map1[x+1][y]=='*') z++;}
        if((x!=(d-1))&&(y!=(d-1))){if(Map1[x+1][y+1]=='*') z++;}
        if((x!=(d-1))&&(y!=0)){if(Map1[x+1][y-1]=='*') z++;}
        if(y!=(d-1)){if(Map1[x][y+1]=='*') z++;}
        if((y!=0)){if(Map1[x][y-1]=='*') z++;}
        if((x!=0)&&(y!=(d-1))){if(Map1[x-1][y+1]=='*') z++;}
        if((x!=0)){if(Map1[x-1][y]=='*') z++;}
        if((x!=0)&&(y!=0)){if(Map1[x-1][y-1]=='*') z++;}

        Map2[x][y]=(char)(z+48);
        if(z==0){
        if(x!=(d-1)){if (Map2[x+1][y]==' '){check(x+1,y);}}
        if((x!=(d-1))&&(y!=(d-1))){if (Map2[x+1][y+1]==' '){check(x+1,y+1);}}
        if((x!=(d-1))&&(y!=0)){if (Map2[x+1][y-1]==' '){check(x+1,y-1);}}
        if(y!=(d-1)){if (Map2[x][y+1]==' '){check(x,y+1);}}
        if((y!=0)){if (Map2[x][y-1]==' '){check(x,y-1);}}
        if((x!=0)&&(y!=d-1)){if (Map2[x-1][y+1]==' '){check(x-1,y+1);}}
        if((x!=0)){if (Map1[x-1][y]==' '){check(x-1,y);}}
        if((x!=0)&&(y!=0)){if (Map2[x-1][y-1]==' '){check(x-1,y-1);}}

        }
        return 1;

    }
}
//endgame check for the condition of winning
int Map:: endgame(){
         int numbomb=0;
        for(int i=0;i<d;i++) {
        for(int j=0;j<d;j++){
            if(Map2[i][j]=='*') numbomb++;
        }}
        if (numberofbomb-numbomb==0){
                for(int i=0;i<d;i++) {
                for(int j=0;j<d;j++){
            if(Map2[i][j]==' '){return 0;}
        }}
        cout <<setw(35)<<""<< "you win\n";
        return 1 ;}
        return 0 ;

}
//play is responsible for utilizing the others class methods for progress of game
void Map::play(){
    int a,x,y,result;
    draw();
    cout<<setw(5)<<""<<"1:clear case\n";
    cout<<setw(5)<<""<<"2:define as mine\n";
    cout<<setw(5)<<""<<"3:define as maybe\n";
    do
    {
       while(!(cin >> a)) {
          cin.clear();
          cin.ignore(1000, '\n');
          cout << "please only choose a number\n";
        }
        if((a!=1)&&(a!=2)&&(a!=3)) cout<<"please choose one of the three choices\n";

    }
    while((a!=1)&&(a!=2)&&(a!=3));
    do{
    cout<<"please,give the longitudinal coordinate\n";
       while(!(cin >> x)) {
          cin.clear();
          cin.ignore(1000, '\n');
          cout << "please only choose a number\n";
        }
    cout<<"please,give the horizontal coordinate\n";
       while(!(cin >> y)) {
          cin.clear();
          cin.ignore(1000, '\n');
          cout << "please only choose a number\n";
        }
    if ((x>d)||(x<1)||(y>d)||(y<1))cout<<"give reasonable coordinate\n";}
    while(!((x<=d)&&(x>=1)&&(y<=d)&&(y>=1)));
    newpage();
    switch(a)
    { case 1:{ x--;y--;
               result=check(x,y);
                newpage();
               if (result==0){cout <<setw(35)<<""<< "you lose\n";
                    draw();
                    writestate(0);

                    return ;
                     }
                 if (endgame()==1){
                               writestate(1);
                               return;
               }
                 return play();
                 };break;
      case 2:{if (Map2[x-1][y-1]==' ')Map2[x-1][y-1]='*';
               newpage();
               if (endgame()==1){
                               writestate(1);
                               return;
               }
               else return play();
              }break;
      case 3:{if (Map2[x-1][y-1]==' ')Map2[x-1][y-1]='M';
              newpage();
              return play();
               }break;
      }

}
int player:: difficulty(){
    int x;
    cout <<setw(35)<<""<< "please choose difficulty\n";
    cout<<setw(20)<<""<<"1:easy\n";
    cout<<setw(20)<<""<<"2:medium\n";
    cout<<setw(20)<<""<<"3:hard\n";
    do
    {
       while(!(cin >> x)) {
          cin.clear();
          cin.ignore(1000, '\n');
          cout << "please only choose a number\n";
        }
        if((x!=1)&&(x!=2)&&(x!=3)) cout<<"you can only chose one of three difficulty\n";
    }
    while((x!=1)&&(x!=2)&&(x!=3));
    newpage();
    diff=x ;
    return 0;
}
void player::states(){
    int a,b,c;
    try{
    ifstream fp ("states.txt");
    if (fp.is_open()){
        while(fp>>a){
                fp>>b>>c;
            switch(a)
                 { case 1:cout<<setw(20)<<""<<"easy wines  "<<b<<"  loses  "<<c<<"\n" ;break;
                   case 2:cout<<setw(20)<<""<<"medium wines  "<<b<<"  loses  "<<c<<"\n" ;break;
                   case 3:cout<<setw(20)<<""<<"hard wines  "<<b<<"  loses  "<<c<<"\n" ;break;
      }

}
        fp.close();
       cout<<"\n\nplease enter 0 to exit " ;
    do
    {
        while(!(cin >>a)) {
          cin.clear();
          cin.ignore(1000, '\n');
          cout << "please only choose a number\n";
        }

    }
    while((a!=0));
    newpage();
        return;
    }
    else throw 1;
}
catch(int x){cout<<"could not open file('states.txt') to read current state please check it existence manually\n";}
}
int Map::introduction(){
      int x;
    cout <<setw(35)<<""<< "Hello welcome to minesweeper game\n";
    cout<<setw(20)<<""<<"1:play\n";
    cout<<setw(20)<<""<<"2:change difficulty\n";
    cout<<setw(20)<<""<<"3:view stats\n";
    cout<<setw(20)<<""<<"4:exit\n";
    do
    {

       while(!(cin >> x)) {
          cin.clear();
          cin.ignore(1000, '\n');
          cout << "please only choose a number\n";
        }
        if((x!=1)&&(x!=2)&&(x!=3)&&(x!=4)) cout<<"please choose from 1 to 4\n";

    }
    while((x!=1)&&(x!=2)&&(x!=3)&&(x!=4));
    newpage();
    switch(x)
    { case 1:{
        create();
        play() ;
        if (playagain()==1){
        return introduction();}
        }break;
      case 2:{difficulty();
              return introduction();}break;
      case 3:{states();
               return introduction();}break;
      case 4:return 0 ;break;
      }
      return 0 ;

}
