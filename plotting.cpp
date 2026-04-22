#include<iostream>
#include<vector>
#include<cmath>
#include<algorithm>
#include<string>
#include<iomanip>
#include"../include/utility.h"
#include"../include/exploration.h"
#include"../include/plotting.h"

using namespace std;

static const int PLOT_WIDTH=60;
static const int PLOT_HEIGHT=20;

void plotColumn(int col)
{
    if(g_data.empty()){cout<<"No data loaded."<<endl;return;}
    if(col<0||col>=(int)g_headers.size()){cout<<"Invalid column."<<endl;return;}
    vector<double> vals;
    vector<int> rowIdx;
    for(int i=0;i<(int)g_data.size();i++)
    {
        if(col<(int)g_data[i].size()&&!isnan(g_data[i][col]))
        {
            vals.push_back(g_data[i][col]);
            rowIdx.push_back(i);
        }
    }
    if(vals.empty()){cout<<"No valid data in column."<<endl;return;}
    double minV=*min_element(vals.begin(),vals.end());
    double maxV=*max_element(vals.begin(),vals.end());
    double range=maxV-minV;
    if(range==0) range=1;
    cout<<"\n  Column Plot: ["<<col<<"] "<<g_headers[col]<<endl;
    cout<<"  Min="<<minV<<"  Max="<<maxV<<endl;
    cout<<string(PLOT_WIDTH+12,'-')<<endl;
    for(int i=0;i<(int)vals.size();i++)
    {
        int barLen=(int)((vals[i]-minV)/range*PLOT_WIDTH);
        cout<<"  Row "<<setw(3)<<rowIdx[i]<<" | ";
        cout<<string(barLen,'#');
        cout<<" "<<vals[i]<<endl;
    }
    cout<<string(PLOT_WIDTH+12,'-')<<endl;
    cout<<"  Scale: |"<<string(PLOT_WIDTH/2-2,' ')<<"|"<<string(PLOT_WIDTH/2-2,' ')<<"|"<<endl;
    cout<<"       "<<minV<<string(PLOT_WIDTH/2-6,' ')<<(minV+maxV)/2.0<<string(PLOT_WIDTH/2-6,' ')<<maxV<<endl;
}

void plotScatter(int colX,int colY)
{
    if(g_data.empty()){cout<<"No data loaded."<<endl;return;}
    vector<double> xs,ys;
    for(int i=0;i<(int)g_data.size();i++)
    {
        if(colX<(int)g_data[i].size()&&colY<(int)g_data[i].size()
            &&!isnan(g_data[i][colX])&&!isnan(g_data[i][colY]))
        {
            xs.push_back(g_data[i][colX]);
            ys.push_back(g_data[i][colY]);
        }
    }
    if(xs.empty()){cout<<"No valid data."<<endl;return;}
    double minX=*min_element(xs.begin(),xs.end());
    double maxX=*max_element(xs.begin(),xs.end());
    double minY=*min_element(ys.begin(),ys.end());
    double maxY=*max_element(ys.begin(),ys.end());
    double rangeX=(maxX==minX)?1:maxX-minX;
    double rangeY=(maxY==minY)?1:maxY-minY;
    vector<string> grid(PLOT_HEIGHT,string(PLOT_WIDTH,' '));
    for(int i=0;i<(int)xs.size();i++)
    {
        int px=(int)((xs[i]-minX)/rangeX*(PLOT_WIDTH-1));
        int py=(int)((ys[i]-minY)/rangeY*(PLOT_HEIGHT-1));
        py=PLOT_HEIGHT-1-py;
        if(px>=0&&px<PLOT_WIDTH&&py>=0&&py<PLOT_HEIGHT)
            grid[py][px]='*';
    }
    cout<<"\n  Scatter Plot: ["<<colX<<"] "<<g_headers[colX]<<"  vs  ["<<colY<<"] "<<g_headers[colY]<<endl;
    cout<<"  Y: "<<maxY<<endl;
    for(int r=0;r<PLOT_HEIGHT;r++)
        cout<<"  | "<<grid[r]<<endl;
    cout<<"  +"<<string(PLOT_WIDTH,'-')<<endl;
    cout<<"    "<<minX<<string(PLOT_WIDTH-10,' ')<<maxX<<endl;
    cout<<"  X: ["<<colX<<"] "<<g_headers[colX]<<endl;
}