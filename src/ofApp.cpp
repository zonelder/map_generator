#include "ofApp.h"
#include<cstdio>
#include<ctime>
#include <cmath>
const unsigned  int Width = 1024;
//const unsigned  int Height = 768;
int m = -1000;
int waterLvl = 0;
double roudness = 55;
int boundVal = -500;
int LandPerCent = 0;
int HeightMap[Width][Width];
int Temperature[Width][Width];
int Wet[Width][Width];

double t;
using namespace std;


bool edgeCondition(int coord_x, int coord_y, int reach)
{
	if (coord_x - reach == 0 || coord_x + reach == Width)
		return true;
	if (coord_y - reach == 0 || coord_y + reach == Width)
		return true;

	return false;
}
int random(int a, int b)
{
	return (a + rand() % int(b - a + 1));
}
int Temp(int j)
{
	if (j < Width / 2)
	{
		return (160 * j / Width - 50 + random(-5, 5));
	}
	else
	{
		return (-(160 * j / int(Width)) + 110 + random(-5, 5));
	}

}

void squareStep(int Array[Width][Width], int x, int y, int reach)
{
	int count = 0;
	float avg = 0.0f;
	if (edgeCondition(x, y, reach))
	{
		Array[x][y] = boundVal;
		return;
	}
	if (x - reach >= 0 && y - reach >= 0)
	{
		avg += Array[x - reach][y - reach];
		count++;
	}
	if (x - reach >= 0 && y + reach < Width)
	{
		avg += Array[x - reach][y + reach];
		count++;
	}
	if (x + reach < Width && y - reach >= 0)
	{
		avg += Array[x + reach][y - reach];
		count++;
	}
	if (x + reach < Width && y + reach < Width)
	{
		avg += Array[x + reach][y + reach];
		count++;
	}
	avg += random(int(-roudness * reach), int(roudness * reach));
	avg /= count;
	Array[x][y] = round(avg);
}
void diamondStep(int Array[Width][Width], int x, int y, int reach)
{
	int count = 0;
	float avg = 0.0f;
	if (edgeCondition(x, y, reach))
	{
		Array[x][y] = boundVal;
		return;
	}

	{
		if (x - reach >= 0)
		{
			avg += Array[x - reach][y];
			count++;
		}
		if (x + reach < Width)
		{
			avg += Array[x + reach][y];
			count++;
		}
		if (y - reach >= 0)
		{
			avg += Array[x][y - reach];
			count++;
		}
		if (y + reach < Width)
		{
			avg += Array[x][y + reach];
			count++;
		}
		avg += random(-roudness * reach, roudness * reach);
		avg /= count;
		Array[x][y] = (int)avg;
	}
}
void diamondSquare(int Array[Width][Width], int size)
{
	int half = size / 2;
	if (half < 1)
		return;
	for (int y = half; y < Width; y += size)
		for (int x = half; x < Width; x += size)
			squareStep(Array, x % Width, y % Width, half);
	int col = 0;
	for (int x = 0; x < Width; x += half)
	{
		col++;
		//If this is an odd column.
		if (col % 2 == 1)
			for (int z = half; z < Width; z += size)
				diamondStep(Array, x % Width, z % Width, half);
		else
			for (int z = 0; z < Width; z += size)
				diamondStep(Array, x % Width, z % Width, half);
	}
	diamondSquare(Array, size / 2);
}

void ofApp::setup(){
	srand(time(0));
	
	
	int Max = -1000;
	int Min = 1000;
	for (int i = 0; i < Width; i++)
		for (int j = 0; j < Width; j++)
		{
			HeightMap[i][j] = 0;
		}
	int size = Width;
	diamondSquare(HeightMap, size / 2);
	for (int i = 0; i < Width; i++)
		for (int j = 0; j < Width; j++)
		{
			
			if (HeightMap[i][j] >= 0)//учет эррозии
			{
				HeightMap[i][j] *= HeightMap[i][j];
			}
			else
			{
				HeightMap[i][j] *=-HeightMap[i][j];
			}
			if (Max < HeightMap[i][j])
			{
				Max = HeightMap[i][j];
			}
			if (Min > HeightMap[i][j])
			{
				Min = HeightMap[i][j];
			}
		}
	int MaxNormed = int(Max/255)+1;
	int MinNormed = abs(int(Min / 255)-1);
	 Max = -1000;
	 Min = 1000;
	for (int i = 0; i < Width; i++)
		for (int j = 0; j < Width; j++)
		{
			if (HeightMap[i][j] > 0) {
				HeightMap[i][j] /= MaxNormed;//числа межлу -1000 и 256; можно еще и нормировать но я хочу оставить ноль недвижимой точкой, так получаеться 
			}
			else
			{
				HeightMap[i][j] /= MinNormed;
			}
			if (Max < HeightMap[i][j])//что морское дно гораздо ниже чем уровень материков,и при большой шероховатости(~50 ) получаеться добиться материков и островов
				Max = HeightMap[i][j];
			if(Min > HeightMap[i][j])
			Min = HeightMap[i][j];
	 }
	cout << "height in range: " << Min << " - " << Max << endl;
}//так уменьшение температуры способствует уменьшению осадков но увеличение высоты увеличитает кол во осадков при том что на высоте температура ниже хмхм

//--------------------------------------------------------------
void ofApp::update(){
	double T = clock();
	//cout <<"tick time: "<< T - t << endl;// время одного тика(если в update пусто то выводит время отрисовки экрана)
	t = T;
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	float normed = 255 / (255.0f - waterLvl);
	ofBackground(255, 255, 255);
	for (int i = camX; i < ofGetWidth()+camX; i++)
	{	if (!(i<0 || i>Width))// если камера захватывает территорию без карты высот то там ничего не рисуем
		for (int j = camY; j < ofGetHeight()+camY; j++)
		{
			int h = (HeightMap[i][j] - waterLvl) * normed;
			if (!(j<0 || j>Width))// если камера захватывает территорию без карты высот то там ничего не рисуем
			{
				if ((HeightMap[i][j]  <= waterLvl) && (HeightMap[i][j] >= -5 + waterLvl))
					ofSetColor(0, 255, 255);//вода у берега
				else
					if ((HeightMap[i][j] <= -5 + waterLvl))
						ofSetColor(0, 0, 128);
					else
						if ((HeightMap[i][j]  >= waterLvl) && (HeightMap[i][j] <= 1 + waterLvl))
							ofSetColor(218, 165, 32);//песок
						else
							ofSetColor(h, h, h);
				ofRect(i - camX, j - camY, 1, 1);
			}

		}
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
