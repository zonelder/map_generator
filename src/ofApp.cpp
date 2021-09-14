#include "ofApp.h"
#include "BIOMS.cpp"
#include "Matrix.h"
unsigned const int Width = 1024;
Matrix<int> Map(Width, Width);
int waterLvl = 0;
int persent = 0;
double t;
using namespace std;



void ofApp::setup(){
	
	/*///////////////////////инициализация массива высот////////////////////////////fill(0)*/
	Map.fill(0);
	/*///////////////////////////////////////////////////////////////////////////////нормировка*/
	Map.Generate();
	Map.Scaling(255);
	cout << "height in range: " << 0 << " - " << Map.Max()<< endl;
	/// <WaterLvl setting>
	int fullArea = 0;
	int dirt = 0;

	fullArea = Width * Width;
	int need_persent = 24;
	for (int step = 0; step < 100; step++) {
		bool is_up = true;
		if (need_persent > persent)
			waterLvl -= 1;
		if (need_persent < persent)
			waterLvl += 1;

		for (int i = 0; i < Width; i++)
			for (int j = 0; j < Width; j++)
			{
				if (Map(i, j) > waterLvl)
					dirt++;
			}
		persent = float(dirt) / float(fullArea) * 100;
		dirt = 0;
	}

	for (int i = 0; i < Width; i++)
		for (int j = 0; j < Width; j++)
		{
			if (Map(i, j) > waterLvl)
				Map(i, j) -= waterLvl;
			else
				Map(i, j) = 0;
		}
	Map.Scaling(255);
	/// </WaterLvl setting>

}//так уменьшение температуры способствует уменьшению осадков но увеличение высоты увеличитает кол во осадков при том что на высоте температура ниже хмхм


//--------------------------------------------------------------
void ofApp::update(){
	double T = clock();

	cout <<"tick time: "<< T - t <<" "<<T<<"  "<<waterLvl<<" "<< persent <<"% " << endl;// время одного тика(если в update пусто то выводит время отрисовки экрана)
	
	t = T;
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(255, 255, 255);
	for (int i =0; i < ofGetWidth(); i++)
	{	if (!(i<0 || i>Width))// если камера захватывает территорию без карты высот то там ничего не рисуем
		for (int j = 0; j < ofGetHeight(); j++)
		{
			int h = Map(i, j);
			if (!(j<0 || j>Width))// если камера захватывает территорию без карты высот то там ничего не рисуем
			{
					if ((Map(i,j)==0))
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
