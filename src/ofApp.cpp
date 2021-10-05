#include "ofApp.h"
#include "BIOMS.h"
#include "Map.h"
#include "Matrix.h"
double t;
int step = 0;
Map GlobalMap(24);
using namespace std;



void ofApp::setup(){

	
	GlobalMap.Generate();
	GlobalMap.coloring();
	
}//так уменьшение температуры способствует уменьшению осадков но увеличение высоты увеличитает кол во осадков при том что на высоте температура ниже хмхм


//--------------------------------------------------------------
void ofApp::update(){
	double T = clock();
	//system("cls");
	//cout << "tick time " << " time " << "     water" << "     persent" << endl;
	//cout << T - t <<"        "<<T<<"       "<<waterLvl<<"     "<< persent <<"% " << endl;// время одного тика(если в update пусто то выводит время отрисовки экрана)
	if ((T - step) > 10000)
	{
		step += 10000;
		switch (GlobalMap.GetRenderStatus()) {
		case renderStatus::HeightMap:
			
			GlobalMap.SetRenderstatus(renderStatus::HeatMap);
			break;
		case renderStatus::HeatMap:
			
			GlobalMap.SetRenderstatus(renderStatus::WetMap);
			break;
		case renderStatus::WetMap:
			
			GlobalMap.SetRenderstatus(renderStatus::BiomMap);
			break;
		case renderStatus::BiomMap:
			
			GlobalMap.SetRenderstatus(renderStatus::HeightMap);
			break;
		default:
			
			GlobalMap.SetRenderstatus(renderStatus::HeightMap);
			break;
		}
		GlobalMap.coloring();
	}
	t = T;
	/*for (int i = 0; i < Width; i++)
		for (int j = 0; j < Width; j++)
		{float max = -100;
					int im = 0;
					int jm = 0;
			for(int d1=-1;d1<=1;d1++)
				for (int d2 = -1; d2 <= 1; d2++)
				{
					
					if (i + d1>=0 && i + d1<Width)
						if(j + d2>=0 && j + d2<Width)
					{
						float dTemp = float(Temp(i, j) - Temp(i + d1, j + d2)) / 8.0f;
						if (dTemp >= max)
						{
							max = dTemp;
							im = i + d1;
							jm = j + d2;
						}
					
					}	
				}
			Temp(i, j) -= max;
			Temp(im, jm) +=max;
		}
		*/
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(255, 255, 255);
	
	for (int i = 0; i < ofGetWidth(); i++)
	{
		if (!(i < 0 || i >= GlobalMap.GetWidth()))// если камера захватывает территорию без карты высот то там ничего не рисуем
			for (int j = 0; j < ofGetHeight(); j++)
				if (!(j<0 || j>=GlobalMap.GetWidth()))
				{
					ofSetColor(GlobalMap.color(i, j));
					ofRect(i, j, 1, 1);
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
	//cout << "Temp= " << Temp(x, y) << "  " << "  Height = " << Map(x, y)<<"   Wet = "<<Wet(x,y) << endl;
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
