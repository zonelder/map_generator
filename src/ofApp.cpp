#include "ofApp.h"
#include<cstdio>
#include<ctime>
#include "System.cpp"
#include "BIOMS.cpp"
unsigned const int Width = 1024;


int waterLvl = 0;
int boundVal = 0;
unsigned int roudness = 1;
int**HeightMap;//нужно удаление массива или создать класс карты и все атрибуты точек держать в этом классе. на каждую точку приходиться параметр высоты, владжности, температруы, расстояни до воды исцева открашивания
int Temperature[Width][Width];
int Wet[Width][Width];
int persent = 0;
double t;
using namespace std;

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
/// <DIAMOND SQUARE>

void squareStep(int** Array, int x, int y, int reach, unsigned int Width)
{
	int count = 0;
	float avg = 0.0f;
	if (edgeCondition(x, y, reach, Width))
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
	if (avg < 0)
		avg = 0;
	else
	Array[x][y] = round(avg);
}
void diamondStep(int** Array, int x, int y, int reach, unsigned int Width)
{
	int count = 0;
	float avg = 0.0f;
	if (edgeCondition(x, y, reach, Width))
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
		if (avg < 0)
			avg = 0;
		else
		Array[x][y] = (int)avg;
	}
}
void diamondSquare(int** Array, int size, unsigned int Width)
{
	int half = size / 2;
	if (half < 1)
		return;
	for (int y = half; y < Width; y += size)
		for (int x = half; x < Width; x += size)
			squareStep(Array, x % Width, y % Width, half, Width);
	int col = 0;
	for (int x = 0; x < Width; x += half)
	{
		col++;
		//If this is an odd column.
		if (col % 2 == 1)
			for (int z = half; z < Width; z += size)
				diamondStep(Array, x % Width, z % Width, half, Width);
		else
			for (int z = 0; z < Width; z += size)
				diamondStep(Array, x % Width, z % Width, half, Width);
	}
	diamondSquare(Array, size / 2, Width);
}
/// </DIAMOND SQUARE>
void ofApp::setup(){
	srand(time(0));
	
	
	int Max = 0;
	/*///////////////////////инициализация массива высот////////////////////////////*/
	HeightMap = new int*[Width];
	*HeightMap = new int[Width * Width];//нигде память не освобождается
	for (int i = 0; i < Width; i++)

	{
		if(i!=0)
		HeightMap[i] = HeightMap[i - 1] + Width;
		for (int j = 0; j < Width; j++)
		{

			HeightMap[i][j] = 0;
		}
	}
	/*///////////////////////////////////////////////////////////////////////////////*/
	int size = Width;
	diamondSquare(HeightMap, size / 2,Width);
	for (int i = 0; i < Width; i++)
		for (int j = 0; j < Width; j++)
		{
			HeightMap[i][j] *= HeightMap[i][j];
			if (Max < HeightMap[i][j])
			{
				Max = HeightMap[i][j];
			}
		}
	int MaxNormed = int(Max/255)+1;
	Max = 0;
	for (int i = 0; i < Width; i++)
		for (int j = 0; j < Width; j++)
		{
				HeightMap[i][j] /= MaxNormed;//числа межлу -1000 и 256; можно еще и нормировать но я хочу оставить ноль недвижимой точкой, так получаеться 
				if (Max < HeightMap[i][j])
					Max = HeightMap[i][j];
	 }
	cout << "height in range: " << 0 << " - " << Max << endl;
	int fullArea = 0;
	int dirt = 0;
	
	fullArea = Width * Width;
	int need_persent = 24;
	for(int step=0;step<100;step++){
		bool is_up = true;
		if (need_persent > persent)
			waterLvl -= 1;
		if(need_persent < persent)
			waterLvl += 1;
		
		for (int i = 0; i < Width; i++)
		for (int j = 0; j < Width; j++)
		{
			if (HeightMap[i][j] > waterLvl)
				dirt++;
		}
		persent = float(dirt) / float(fullArea) * 100;
		dirt = 0;
	}
	
	
}//так уменьшение температуры способствует уменьшению осадков но увеличение высоты увеличитает кол во осадков при том что на высоте температура ниже хмхм


//--------------------------------------------------------------
void ofApp::update(){
	double T = clock();

	cout <<"tick time: "<< T - t <<" "<<T<<"  "<<waterLvl<<" "<< persent <<"% " << endl;// время одного тика(если в update пусто то выводит время отрисовки экрана)
	
	t = T;
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	float normed = 255 / (255.0f - waterLvl);
	ofBackground(255, 255, 255);
	for (int i =0; i < ofGetWidth(); i++)
	{	if (!(i<0 || i>Width))// если камера захватывает территорию без карты высот то там ничего не рисуем
		for (int j = 0; j < ofGetHeight(); j++)
		{
			int h = (HeightMap[i][j] - waterLvl) * normed;
			if (!(j<0 || j>Width))// если камера захватывает территорию без карты высот то там ничего не рисуем
			{
					if ((HeightMap[i][j] <= waterLvl))
						ofSetColor(0, 0, 128);
					else/*
						if ((HeightMap[i][j] >= waterLvl) && (HeightMap[i][j] <= 1 + waterLvl))
							ofSetColor(218, 165, 32);//песок

						else
							if (HeightMap[i][j] > 170)
								ofSetColor(255, 250, 250);
							else
								if ((HeightMap[i][j] < 40) && (HeightMap[i][j] > 1 + waterLvl))
									ofSetColor(144, 238, 144);
								else
									if (HeightMap[i][j] >= 40 && HeightMap[i][j] <= 80)
										ofSetColor(205, 179, 139);
									else
										if (HeightMap[i][j] > 80 && HeightMap[i][j] < 170)
											ofSetColor(139, 139, 141);
										else
										*/
							ofSetColor(h, h, h);
				ofRect(i , j , 1, 1);
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
