#ifndef CMAPTSP_H
#define CMAPTSP_H

//////////////////////////////////////////////////////////////////
//
//	Name:	CmapTSP.h
//
//	Author: Mat Buckland
//
//	Desc:	Class for calculating city positions and the distances
//			between them.
//
///////////////////////////////////////////////////////////////////


#include <vector>

#include "utils.h"
#include "defines.h"

using namespace std;



const double pi = 3.1415926535897;//파이에 대한 상수설정


//---------------------------------------------------------
//	define a simple struct to hold the coordinates of each
//	city
//---------------------------------------------------------
struct CoOrd //도시에 대한 구조체
{
	float x, y;
	
	CoOrd(){}
	CoOrd(float a, float b):x(a),y(b){}
};


//---------------------------------------------------------------
// definition of the map class
//---------------------------------------------------------------
class CmapTSP
{
private:
	
  //number of cities in the problem
	int				m_NumCities;//도시의 수

	//client window dimensions
	int				m_MapWidth;//창의 크기
	int				m_MapHeight;//창의 크기

	//holds the length of the solution, if one is calculable.
	double		m_dBestPossibleRoute;//최적의 경로를 담는 변수
	
	//calculate the coordinates of each city (positioned in a circle)
	void			CreateCitiesCircular(); // 원형으로 도시를 만드는 함수
	
	//calculates the distance between two cities
  double		CalculateA_to_B(const CoOrd &city1, const CoOrd &city2);//도시 사이의 거리계산
	
	void			CalculateBestPossibleRoute();//가장 좋은 해를 갖는 루틔
	
	
public:

	//the city coordinates
  vector<CoOrd>	m_vecCityCoOrds;
	
	CmapTSP(int w, int h, int nc):m_MapWidth(w),
								                m_MapHeight(h),
								                m_NumCities(nc)
								
	{
		//calculate the co-ordinates for the cities
		CreateCitiesCircular();

		CalculateBestPossibleRoute();
	}


	//call this if user resizes client area
	void	  Resize(const int new_width, const int new_height);
	
	//calculates the tour length
  double	GetTourLength(const vector<int> &route);

	//accessor methods
	double	BestPossibleRoute()const{return m_dBestPossibleRoute;}
	
};




#endif