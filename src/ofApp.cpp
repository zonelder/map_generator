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
	
	/*///////////////////////������������� ������� �����////////////////////////////fill(0)*/
	Map.fill(0);
	/*///////////////////////////////////////////////////////////////////////////////����������*/
	Map.Generate();
	Map.Scaling(255);
	cout << "height in range: " << 0 << " - " << Map.Max()<< endl;
	Map.WaterLvl_setting(24);
	/// <set map color>
	
	
	for (int i = 0; i < Width; i++)
		for (int j = 0; j < Width; j++)
		{

			if ((Map(i, j) == 0))
				color(i,j)=ofColor(0, 0, 128);
			else
				if ((Map(i,j) >= 0) && (Map(i, j) <= 10))
					color(i,j)=ofColor(218, 165, 32);//�����

				else
					if (Map(i, j) > 170)
						color(i, j) = ofColor(255, 250, 250);//������� �������
					else
						if ((Map(i, j) < 50) && (Map(i, j) > 10))//���� �������
							color(i, j) = ofColor(34, 177, 34);
						else
							if (Map(i, j) >= 50 && Map(i, j) <80)//������ ���
								color(i, j) = ofColor(44, 133,84);
							else
							if (Map(i, j) >= 80 && Map(i, j) <= 110)//������ ������
								color(i, j) = ofColor(86, 103, 117);
							else
								if (Map(i, j) > 110 && Map(i, j) < 170)//����� �����
									color(i, j) = ofColor(118, 123, 120);
								else
								
				color(i,j)=ofColor(Map(i,j), Map(i, j), Map(i, j));

		}
	/// </summary>
}//��� ���������� ����������� ������������ ���������� ������� �� ���������� ������ ����������� ��� �� ������� ��� ��� ��� �� ������ ����������� ���� ����


//--------------------------------------------------------------
void ofApp::update(){
	double T = clock();
	system("cls");
	cout << "tick time " << " time " << "     water" << "     persent" << endl;
	cout << T - t <<"        "<<T<<"       "<<waterLvl<<"     "<< persent <<"% " << endl;// ����� ������ ����(���� � update ����� �� ������� ����� ��������� ������)
	
	t = T;
	
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(255, 255, 255);
	for (int i =0; i < ofGetWidth(); i++)
	{	if (!(i<0 || i>Width))// ���� ������ ����������� ���������� ��� ����� ����� �� ��� ������ �� ������
		for (int j = 0; j < ofGetHeight(); j++)
		{
			if (!(j<0 || j>Width))// ���� ������ ����������� ���������� ��� ����� ����� �� ��� ������ �� ������
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
