#include "CmapTSP.h"
#include <iostream>
#include <fstream>
#include <math.h>
float dist[NUM_CITIES][NUM_CITIES];

//--------------------Create Cities-------------------------
//
//	Evenly spaces the cities on the perimeter of a wheel and
//  returns a vector of their coordinates
//----------------------------------------------------------
void CmapTSP::CreateCitiesCircular()//도시들을 생성
{
	//first caculate the radius of spread and the origin
	const int margin = 50;
	double radius;
	if (m_MapHeight < m_MapWidth)
	{
		radius = (m_MapHeight / 2) - margin;
	}
	else
	{
		radius = (m_MapWidth / 2) - margin;
	}
	CoOrd origin(m_MapWidth / 2, m_MapHeight / 2);

	//calculate angle division between adjacent cities.
	double SegmentSize = 2 * pi / m_NumCities;
	
	double angle = 0;
	
	vector<CoOrd> vecCities;

	while (angle < 2 * pi)//각도가 2파이보다 작을때 반복한다
	{
		CoOrd ThisCity;
		
		ThisCity.x = radius * sin(angle) + origin.x;
		ThisCity.y = radius * cos(angle) + origin.y;
		m_vecCityCoOrds.push_back(ThisCity);
		
		angle += SegmentSize;
	}//좌표들과 각을 갱신한다
	
}
//-------------------------------BestPossibleFitness---------------------------------
//
//	calculates the distance of the optimum route. We use this so we
//	can tell when to stop each run
//----------------------------------------------------------------------
void CmapTSP::CalculateBestPossibleRoute()//최단 경로를 구하는 함수이다
{
	m_dBestPossibleRoute = 0;
	
	for (int city=0; city<m_vecCityCoOrds.size()-1; ++city)
	{
		m_dBestPossibleRoute += CalculateA_to_B(m_vecCityCoOrds[city], m_vecCityCoOrds[city+1]);
		
		//add in a small amount to cover any precision errors we may have made
		m_dBestPossibleRoute += EPSILON;
	}
	
	//add in the distance from the last to the first
	m_dBestPossibleRoute += CalculateA_to_B(m_vecCityCoOrds[m_vecCityCoOrds.size()-1], m_vecCityCoOrds[0]);
}

//---------------------Calculate Distance----------------------
//
//	returns the distance between the two given cities
//-------------------------------------------------------------
double CmapTSP::CalculateA_to_B(const CoOrd &city1, const CoOrd &city2)
{
	double xDist = city1.x - city2.x;
	double yDist = city1.y - city2.y;
	
	return sqrt(xDist*xDist + yDist*yDist);
}

//-----------------Calculate Fitness ---------------------------
//
//	calculates the total distance the salesman must travel for
//	the given order of cities
//--------------------------------------------------------------
double CmapTSP::GetTourLength(const vector<int> &route)//위에서 마는 두도시를 계산하는 함수를 이용하여 경로의 총 거리를 구하는 함수
{
	double TotalDistance = 0;
	
	for (int i=0; i<route.size()-1; ++i)
	{
		int city1 = route[i];
		int city2 = route[i+1];
		
		TotalDistance += CalculateA_to_B(m_vecCityCoOrds[city1], m_vecCityCoOrds[city2]);
	}
	
	//don't forget this is a closed loop so we need to add in the distance 
	//from the last city visited back to the first
	int last  = route[route.size()-1];
	int first = route[0];
	
	TotalDistance += CalculateA_to_B(m_vecCityCoOrds[last], m_vecCityCoOrds[first]);
	
	return TotalDistance;
}
//--------------------------- Refresh --------------------------------
//
//	used to recalculate the city positions and the best possible tour 
//	if map sizes are changed (eg if user changes window size)
//--------------------------------------------------------------------
void CmapTSP::Resize(const int new_width, const int new_height)//노드 즉 도시들의 값이 바뀌었을 때 다시 계산하는함수이다.
{
	m_MapWidth  = new_width;
	m_MapHeight = new_height;

	m_vecCityCoOrds.clear();

	CreateCitiesCircular();
	
	CalculateBestPossibleRoute();
}



