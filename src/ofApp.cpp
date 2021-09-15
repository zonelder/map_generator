#include "ofApp.h"
#include "BIOMS.cpp"
#include "Matrix.h"
unsigned const int Width = 1024;
Matrix<int> Map(Width, Width);
Matrix<ofColor>color(Width, Width);
int waterLvl = 0;
int persent = 24;
double t;
using namespace std;



void ofApp::setup(){
	
	/*///////////////////////инициализация массива высот////////////////////////////fill(0)*/
	Map.fill(0);
	/*///////////////////////////////////////////////////////////////////////////////нормировка*/
	Map.Generate();
	Map.Scaling(255);
	cout << "height in range: " << 0 << " - " << Map.Max()<< endl;
	Map.WaterLvl_setting(24);

	for (int i = 0; i < Width; i++)
		for (int j = 0; j < Width; j++)
		{

			if ((Map(i, j) == 0))
				color(i,j)=ofColor(0, 0, 128);
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
				color(i,j)=ofColor(Map(i,j), Map(i, j), Map(i, j));

		}
}//так уменьшение температуры способствует уменьшению осадков но увеличение высоты увеличитает кол во осадков при том что на высоте температура ниже хмхм


//--------------------------------------------------------------
void ofApp::update(){
	double T = clock();
	system("cls");
	cout << "tick time " << " time " << "     water" << "     persent" << endl;
	cout << T - t <<"        "<<T<<"       "<<waterLvl<<"     "<< persent <<"% " << endl;// время одного тика(если в update пусто то выводит время отрисовки экрана)
	
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
				ofSetColor(color(i, j));
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
