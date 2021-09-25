#include "ofApp.h"
#include "BIOMS.cpp"
#include "Matrix.h"
unsigned const int Width = 1024;
Matrix<int> Map(Width, Width);
Matrix<ofColor>color(Width, Width);
Matrix<int>Temp(Width, Width);
Matrix<int>Wet(Width, Width);
Matrix<int>Range(Width, Width);
int waterLvl = 0;
int persent = 24;
double t;
using namespace std;
 static ofColor Coldest =ofColor(0, 255, 255);
 static ofColor Colder = ofColor(170, 255, 255);
 static ofColor Cold = ofColor(0, 229 , 133 );
 static ofColor Warm = ofColor(255, 255, 100 );
 static ofColor Warmer = ofColor(255, 100 , 0);
 static ofColor Warmest = ofColor(241 , 12 , 0);
 bool color_status = true;

//влажность дообавить+ ветер(по ветру идет передача влажности)
void ofApp::setup(){
	
	/*///////////////////////инициализация массива высот и температур////////////////////////////fill(0)*/
	Map.fill(0);
	Temp.fill(0);
	Wet.fill(0);
	Range.fill(0);
	
	/*///////////////////////////////////////////////////////////////////////////////нормировка*/
	Map.Generate();
	Temp.setRoudness(2);
	Temp.Generate();
	Temp.Scaling(50);
	for (int i = 0; i < Width; i++)
		for (int j = 0; j < Width; j++)
		{
			if (j < Width / 2)
				Temp(i,j) += 160 * j / Width - 50;
			else
				Temp(i,j) += -(160 * j / int(Width)) + 110;
		}
	Map.Scaling(255);
	cout << "height in range: " << 0 << " - " << Map.Max()<< endl;
	Map.WaterLvl_setting(24);
	for (int i = 0; i < Width; i++)
		for (int j = 0; j < Width; j++)
		{
			Temp(i, j) = -float(Map(i, j)) / 7.0f + Temp(i, j);//7- за сколько понижается тмпература с единичей высоты, можно настраивать и генерировать более мягкие или жесткие условия
		}
	/// <set Wet>;
	/// /<set Wet>
	/// <set map color>
	
	for (int i = 0; i < Width; i++)
		for (int j = 0; j < Width; j++)
		{
			//color(i, j) = ofColor(255 - 3 * Temp(i, j) - 150, 255 -3*Temp(i, j) -150, 255 - 3 * Temp(i, j) - 150);
			if ((Map(i, j) <= 0))
				color(i,j)=ofColor(rand() % 13,rand() % 13, 128+rand()%13);
			//if (Map(i,j)==0)
				//color(i,j) = ofColor(204+rand()%13, 204 + rand() % 13, 217+rand()%13);
			else
				if ((Map(i,j) >= 0) && (Map(i, j) <= 10))
					color(i,j)=ofColor(218, 165, 32);//песок

				else
					if (Map(i, j) > 170)
					{
						int rnd = random(-8, 8);
						if (Map(i, j) + rnd > 255)
							rnd = Map(i, j);
						else
							rnd += Map(i, j);
						//color(i, j) = ofColor(255, 250, 250);//снежная вершина
						color(i, j) = ofColor(rnd, rnd, rnd);
					}
					else
						if ((Map(i, j) < 50) && (Map(i, j) > 10))//типа лесочек

						{
							
							color(i, j) = ofColor(34, 177, 34);
						}
						else
							if (Map(i, j) >= 50 && Map(i, j) <80)//темный лес
								color(i, j) = ofColor(44, 133,84);
							else
							if (Map(i, j) >= 80 && Map(i, j) <= 110)//горный массив
								color(i, j) = ofColor(86, 103, 117);
							else
								if (Map(i, j) > 110 && Map(i, j) < 170)//серые скалы
									color(i, j) = ofColor(118, 123, 120);
								else
								
				color(i,j)=ofColor(Map(i,j), Map(i, j), Map(i, j));
			

		}
	/// </summary>
}//так уменьшение температуры способствует уменьшению осадков но увеличение высоты увеличитает кол во осадков при том что на высоте температура ниже хмхм


//--------------------------------------------------------------
void ofApp::update(){
	double T = clock();
	int step = 0;
	//system("cls");
	cout << "tick time " << " time " << "     water" << "     persent" << endl;
	cout << T - t <<"        "<<T<<"       "<<waterLvl<<"     "<< persent <<"% " << endl;// время одного тика(если в update пусто то выводит время отрисовки экрана)
	if ((T - step) > 10000)
	{
		step += 10000;
		color_status = !color_status;
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
	for (int i =0; i < ofGetWidth(); i++)
	{	if (!(i<0 || i>Width))// если камера захватывает территорию без карты высот то там ничего не рисуем
		for (int j = 0; j < ofGetHeight(); j++)
		{
			if (!(j<0 || j>Width))// если камера захватывает территорию без карты высот то там ничего не рисуем
			{
				if (color_status == false) {
					if (Temp(i, j) > 40)
						color(i, j) = Warmest;
					else
						if (Temp(i, j) > 20 && Temp(i, j) <= 40)
							color(i, j) = Warmer;
						else
							if (Temp(i, j) > 10 && Temp(i, j) <= 20)
								color(i, j) = Warm;
							else
								if (Temp(i, j) > -20 && Temp(i, j) <= 10)
									color(i, j) = Cold;
								else if (Temp(i, j) > -30 && Temp(i, j) <= -20)
									color(i, j) = Colder;
								else if (Temp(i, j) <= -30)
									color(i, j) = Coldest;
				}
				else
				{
					if ((Map(i, j) <= 0))
						color(i, j) = ofColor(rand() % 13, rand() % 13, 128 + rand() % 13);
					//if (Map(i,j)==0)
						//color(i,j) = ofColor(204+rand()%13, 204 + rand() % 13, 217+rand()%13);
					else
						if ((Map(i, j) >= 0) && (Map(i, j) <= 10))
							color(i, j) = ofColor(218, 165, 32);//песок

						else
							if (Map(i, j) > 170)
							{
								int rnd = random(-8, 8);
								if (Map(i, j) + rnd > 255)
									rnd = Map(i, j);
								else
									rnd += Map(i, j);
								//color(i, j) = ofColor(255, 250, 250);//снежная вершина
								color(i, j) = ofColor(rnd, rnd, rnd);
							}
							else
								if ((Map(i, j) < 50) && (Map(i, j) > 10))//типа лесочек

								{

									color(i, j) = ofColor(34, 177, 34);
								}
								else
									if (Map(i, j) >= 50 && Map(i, j) < 80)//темный лес
										color(i, j) = ofColor(44, 133, 84);
									else
										if (Map(i, j) >= 80 && Map(i, j) <= 110)//горный массив
											color(i, j) = ofColor(86, 103, 117);
										else
											if (Map(i, j) > 110 && Map(i, j) < 170)//серые скалы
												color(i, j) = ofColor(118, 123, 120);
											else

												color(i, j) = ofColor(Map(i, j), Map(i, j), Map(i, j));


				}
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
	cout << "Temp= " << Temp(x, y) << "  " << "  Height = " << Map(x, y)<<"   Wet = "<<Wet(x,y)<<endl;
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
