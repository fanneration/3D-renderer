#include<vector>
#include<cmath>
#include<iostream>
using namespace std;
const double pi=3.14159265358979,fov[61]={-pi/4,-29*pi/120,-28*pi/120,-27*pi/120,-26*pi/120,-25*pi/120,-24*pi/120,-23*pi/120,-22*pi/120,-21*pi/120,-20*pi/120,-19*pi/120,-18*pi/120,-17*pi/120,-16*pi/120,-15*pi/120,-14*pi/120,-13*pi/120,-12*pi/120,-11*pi/120,-10*pi/120,-9*pi/120,-8*pi/120,-7*pi/120,6*pi/120,-5*pi/120,-4*pi/120,-3*pi/120,-2*pi/120,-pi/120,0,
pi/120,2*pi/120,3*pi/120,4*pi/120,5*pi/120,6*pi/120,7*pi/120,8*pi/120,9*pi/120,10*pi/120,11*pi/120,12*pi/120,13*pi/120,14*pi/120,15*pi/120,16*pi/120,17*pi/120,18*pi/120,19*pi/120,20*pi/120,21*pi/120,22*pi/120,23*pi/120,24*pi/120,25*pi/120,26*pi/120,27*pi/120,28*pi/120,29*pi/120,pi/4};
string screen[26]={"                                                                                                                       ",
                    "                                                                                                                       ",
                    "                                                                                                                       ",
                    "                                                                                                                       ",
                    "                                                                                                                       ",
                    "                                                                                                                       ",
                    "                                                                                                                       ",
                    "                                                                                                                       ",
                    "                                                                                                                       ",
                    "                                                                                                                       ",
                    "                                                                                                                       ",
                    "                                                                                                                       ",
                    "                                                                                                                       ",
                    "                                                                                                                       ",
                    "                                                                                                                       ",
                    "                                                                                                                       ",
                    "                                                                                                                       ",
                    "                                                                                                                       ",
                    "                                                                                                                       ",
                    "                                                                                                                       ",
                    "                                                                                                                       ",
                    "                                                                                                                       ",
                    "                                                                                                                       ",
                    "                                                                                                                       ",
                    "                                                                                                                       ",
                    "                                                                                                                       "},screen2[26];
double arraydistance[61],arraypx[61];
void distance(double x1,double x2,double y1,double y2){
    double slope=(y1-y2)/(x1-x2);
    for (int i=0;i<61;i++){
        arraydistance[i]=(1/cos(fov[i]))*((y1-x1*slope)/(tan(fov[i])-slope));
    }
}
void px(double x1,double x2,double y1,double y2){
    double slope=(y1-y2)/(x1-x2);
    for (int i=0;i<61;i++){
        if ((y1-x1*slope)/(tan(fov[i])-slope)>=0&&((y1-x1*slope)/(tan(fov[i])-slope)>=min(x1,x2)&&(y1-x1*slope)/(tan(fov[i])-slope)<=max(x1,x2))){
            arraypx[i]=3*fov[i]/(2*pi);
        }else{
            arraypx[i]=-1;
        }
    }
}
void render(vector<pair<double,double>> points,vector<pair<int,int>> lines,vector<string*> textures){
    int pxsize=0;
    int pxpos=0;
    for (int i=0;i<26;i++){
        screen[i]="                                                                                                                       ";
        screen2[i]="                                                                                                                       ";
    }
    for (int i=0;i<lines.size();i++){
        pxsize=0;
        pxpos=0;
        distance(points[lines[i].first].first,points[lines[i].second].first,points[lines[i].first].second,points[lines[i].second].second);
        px(points[lines[i].first].first,points[lines[i].second].first,points[lines[i].first].second,points[lines[i].second].second);
        for (int j=0;j<61;j++){
            if (arraypx[j]!=-1){
                pxsize++;
            }
        }
        for (int j=0;j<61;j++){
            if (arraypx[j]!=-1){
                for (int k=0;k<26/arraydistance[j]&&arraydistance!=0;k++){
                    if (!(13-13/arraydistance[j]+k<0||13-13/arraydistance[j]+k>25)){
                        if (arraydistance[j]<=5){
                            screen2[(int)(13-13/arraydistance[j]+k)][(int)(120*arraypx[j]+59)]='#';
                            if (textures[i][(int)(16*k/(26/arraydistance[j]))][(int)(16*pxpos/pxsize)]=='#'){
                                screen[(int)(13-13/arraydistance[j]+k)][(int)(120*arraypx[j]+59)]='#';
                            }
                        }else if (arraydistance[j]>5&&arraydistance[j]<=10&&screen2[(int)(12-13/arraydistance[j]+k)][(int)(120*arraypx[j]+59)]!='#'){
                            screen2[(int)(13-13/arraydistance[j]+k)][(int)(120*arraypx[j]+59)]='=';
                            if (textures[i][(int)(16*k/(26/arraydistance[j]))][(int)(16*pxpos/pxsize)]=='#'){
                                screen[(int)(13-13/arraydistance[j]+k)][(int)(120*arraypx[j]+59)]='=';
                            }
                        }else if (arraydistance[j]>10&&arraydistance[j]<=15&&screen2[(int)(12-13/arraydistance[j]+k)][(int)(120*arraypx[j]+59)]!='#'&&screen2[(int)(12-13/arraydistance[j]+k)][(int)(120*arraypx[j]+59)]!='='){
                            screen2[(int)(13-13/arraydistance[j]+k)][(int)(120*arraypx[j]+59)]='.';
                            if (textures[i][(int)(16*k/(26/arraydistance[j]))][(int)(16*pxpos/pxsize)]=='#'){
                                screen[(int)(13-13/arraydistance[j]+k)][(int)(120*arraypx[j]+59)]='.';
                            }
                        }
                    }
                }
                pxpos++;
            }
        }
    }
}
