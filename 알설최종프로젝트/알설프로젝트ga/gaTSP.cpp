#include "gaTSP.h"
#include <fstream>
#include <iostream>
#include <time.h>
#include<string>
using namespace std;




////////////////////////////////////////////////////////////////////////////////

//---------------------GrabPermutation----------------------
//
//	given an int, this function returns a vector containing
//	a random permutation of all the integers up to the supplied
//	parameter.
//------------------------------------------------------------
//인코딩 기법
vector<int> SGenome::GrabPermutation(int &limit)//순열을 이용하여 염색체를 채우는 함수이다.
{
	vector<int> vecPerm;
	
	for (int i=0; i<limit; i++)
	{
		//we use limit-1 because we want ints numbered from zero
		int NextPossibleNumber = RandInt(0, limit-1);

		while(TestNumber(vecPerm, NextPossibleNumber))// 같은 숫자가 있으면 계속 새롭게 랜덤한 숫자로 바꿔준다. 
		{
			NextPossibleNumber = RandInt(0, limit-1);
		}

		vecPerm.push_back(NextPossibleNumber);
	}

	return vecPerm;
}

//---------------------TestNumber-----------------------------
//
//	checks if a given integer is already contained in a vector
//	of integers.
//------------------------------------------------------------
bool SGenome::TestNumber(const vector<int> &vec, const int &number)//중복을 확인 하기 위해 사용하는 함수이다.
{
	for (int i=0; i<vec.size(); ++i)
	{
		if (vec[i] == number)
		{
			return true;
		}
	}

	return false;
}






/////////////////////////////////////////////////////////////////////////////
//
//	Methods for CgaTSP
//
////////////////////////////////////////////////////////////////////////////

//-----------------------CalculatePopulationsFitness--------------------------
//
//	calculates the fitness of each member of the population, updates the
//	fittest, the worst, keeps a sum of the total fittness scores and the
//	average fitness score of the population (most of these stats are required
//	when we apply pre-selection fitness scaling.
//-----------------------------------------------------------------------------
void CgaTSP::CalculatePopulationsFitness()// 적응도를 계산하는 함수로 selection전에 scaling을 해주었다.
{
	//for each chromo
	for (int i=0; i<m_iPopSize; ++i)
	{

		//calculate the tourlength for each chromosome
		double TourLength = 
		m_pMap->GetTourLength(m_vecPopulation[i].vecCities);

		m_vecPopulation[i].dFitness = TourLength;
		
		//keep a track of the shortest route found each generation
		if (TourLength < m_dShortestRoute)// 가장 경로의 값이 작은 값을 찾는다
		{
			m_dShortestRoute = TourLength;

			m_iFittestGenome = i;
		}
		
		//keep a track of the worst tour each generation
		if (TourLength > m_dLongestRoute)// 가장 경로의 값이 큰 값을 찾는다
		{
			m_dLongestRoute = TourLength;
		}

	}//next chromo

	//Now we have calculated all the tour lengths we can assign
	//the fitness scores
	for (int i=0; i<m_iPopSize; ++i)
	{
		m_vecPopulation[i].dFitness = 
		m_dLongestRoute - m_vecPopulation[i].dFitness;//가장 큰 경로값에서 현재 경로값을 빼서 scaling하였다. 값이 클수록 적합도가 높은것으로 취급하였다.
	}

}




//--------------------------RouletteWheelSelection----------------------
//
//	selects a member of the population by using roulette wheel selection
//	as described in the text.
//-----------------------------------------------------------------------
SGenome& CgaTSP::RouletteWheelSelection()//룰렛셀렉션이며 적합도가 높을수록 선택될 확률을 높게 하는 방식이다
{
	double fSlice	= RandFloat() * m_dTotalFitness;
	
	double cfTotal	= 0.0;
	
	int	SelectedGenome = 0;
	
	for (int i=0; i<m_iPopSize; ++i)
	{
		
		cfTotal += m_vecPopulation[i].dFitness;
		
		if (cfTotal > fSlice) // 이 조건문을 통해 selete를 한다
		{
			SelectedGenome = i;//그때의 값을 초기화
			
			break;
		}
	}
	
	return m_vecPopulation[SelectedGenome];
}

//-----------------------------ChooseSection----------------------------
//
//	given a <vector> size and a min span, this will calculate a random
//	beginning and end point within the <vector>. Used mainly in 
//	mutation and crossover operators
//----------------------------------------------------------------------
void ChooseSection(int& beg,// 이 함수는 코드내에서 사용하지 않는다. 이와 비슷한 로직을 mutation과 crossover에서 직접구현하여 사용한다. 
	int& end,
	const int vec_size,
	const int min_span)
{

	beg = RandInt(0, vec_size - 1 - min_span);

	end = beg;

	//find an end
	while (end <= beg)
	{
		end = RandInt(0, vec_size - 1);
	}
}
//---------------------------MutateEM-----------------------------
//
//	Mutates the chromosome by choosing two random genes and swapping
//	their position.
//-----------------------------------------------------------------
void CgaTSP::MutateEM(vector<int> &chromo)//돌연변이를 발생시키는 함수 여기서는 exchange nutation을 사용하였다.
{
	//return dependent upon mutation rate
	if (RandFloat() > m_dMutationRate) return; //이전에 초기화 해놓은 돌연변이 발생확률보다 많은 비율이면 리턴한다.

	//choose first gene
	int pos1 = RandInt(0, chromo.size()-1);//돌연변이 발생위치선정

	//choose second
	int pos2 = pos1;

	while (pos1 == pos2)//서로 다를때 까지 랜덤하게 값을 바꿔준다
	{
		pos2 = RandInt(0, chromo.size()-1);
	}

	//swap their positions
	swap(chromo[pos1], chromo[pos2]);//둘을 스왑하여 넣어준다 
}



//-------------------------CrossoverPMX---------------------------------
//
// crossover operator based on 'partially matched crossover' as 
// defined in the text
//-------------------------------------------------------------------
void CgaTSP::CrossoverPMX(const vector<int>	&mum, 
							            const vector<int>	&dad, 
							            vector<int>	      &baby1, 
						            	vector<int>       &baby2)//교배를 진행하는 함수이며 교배 방법으로는 pmx를 사용한다
{
	baby1 = mum; //교차하기 전의 초기화
	baby2 = dad;
	
	//just return dependent on the crossover rate or if the
	//chromosomes are the same.
	if ( (RandFloat() > m_dCrossoverRate) || (mum == dad)) // 서로 같은 경우나 이전에 초기화 해놓은 교배율보다 작으면 리턴한다
	{
		return;
	}

	//first we choose a section of the chromosome
	int beg = RandInt(0, mum.size()-2); // 각각 교차할 범위를 정하는 부분
	
	int end = beg;
	
	//find an end
	while (end <= beg)
	{
		end = RandInt(0, mum.size()-1);
	}// 여기까지 교차할 범위를 구한다

	//now we iterate through the matched pairs of genes from beg
	//to end swapping the places in each child
	vector<int>::iterator posGene1, posGene2;

	for (int pos = beg; pos < end+1; ++pos)
	{
		//these are the genes we want to swap
		int gene1 = mum[pos];
		int gene2 = dad[pos];

		if (gene1 != gene2)
		{
			//find and swap them in baby1
			posGene1 = find(baby1.begin(), baby1.end(), gene1);//body1에서의 교차연산
			posGene2 = find(baby1.begin(), baby1.end(), gene2);//body1에서의 교차연산

			swap(*posGene1, *posGene2);

			//and in baby2
			posGene1 = find(baby2.begin(), baby2.end(), gene1);//body2에서의 교차연산
			posGene2 = find(baby2.begin(), baby2.end(), gene2);//body2에서의 교차연산
			
			swap(*posGene1, *posGene2);
		}
		
	}//next pair
}	


//-----------------------CreateStartingPopulation()------------------------
//
//	clears any existing population, fills a vector with a random population
//	of genomes and resets appropriate member variables
//-------------------------------------------------------------------------
void CgaTSP::CreateStartingPopulation()
{
	//make sure the vector of genomes is empty before we
	//start
	m_vecPopulation.clear();
	
	//create a new population of random genomes
	for (int i=0; i<m_iPopSize; ++i)
	{
		m_vecPopulation.push_back(SGenome(m_iChromoLength));
	}

	//make sure variables are initialised correctly
	m_iGeneration	 = 0;
	m_dShortestRoute = 9999999;
	m_iFittestGenome = 0;
	m_bStarted			 = false;

}
//-----------------------------------Run-----------------------------------
//
//	This is the function that initializes a new population and sets the
//  ga running 
//------------------------------------------------------------------------
void CgaTSP::Run(HWND hwnd)
{
	//The first thing we have to do is create a random population
	//of genomes
	CreateStartingPopulation();

	m_bStarted = true;

}
//-------------------------Reset()------------------------------
//
//	resets all the relevant variables ready for a new generation
//--------------------------------------------------------------
void CgaTSP::Reset()
{
	//just make the shortest route some excessively large distance
	m_dShortestRoute	= 999999999;
	m_dLongestRoute		= 0;
	m_dTotalFitness		= 0;
}

//------------------------Epoch-------------------------------
//
//	creates a new population of genomes using the selection,
//	mutation and crossover operators
//------------------------------------------------------------
void CgaTSP::Epoch()//위에서 만든 교차연산,변이,선택등을 이용하여 한세대를 만들어 가는 과정이다
{

	//first reset variables and calculate the fitness of each genome
	Reset();
	
	CalculatePopulationsFitness();//적합도를 계산하는 함수호출

	//if a solution is found exit
	if ((m_dShortestRoute <= m_pMap->BestPossibleRoute()))// 가장좋은경로 탑색시 종료
	{
		m_bStarted = false;
		
		return;
	}
	
	//create a temporary vector for the new population
	vector<SGenome> vecNewPop;
	
	//First add NUM_BEST_TO_ADD number of the last generation's
	//fittest genome(elitism)
	for (int i=0; i<NUM_BEST_TO_ADD; ++i)
	{
		vecNewPop.push_back(m_vecPopulation[m_iFittestGenome]);// 2개의 최고 적합도 염색체를 넣어준다.
	}
	

	//now create the remainder of the population
	while (vecNewPop.size() != m_iPopSize)
	{
	
		//grab two parents
		SGenome mum = RouletteWheelSelection();//룰렛셀렉션
		SGenome dad = RouletteWheelSelection();//룰렛셀렉션

		//create 2 children
		SGenome baby1, baby2;
		
		//Breed them
		CrossoverPMX(mum.vecCities,
					       dad.vecCities,
					       baby1.vecCities,
					       baby2.vecCities);//pmx교배 

		//and mutate them
		MutateEM(baby1.vecCities);//돌연변이 함수 
		MutateEM(baby2.vecCities);//돌연변이 함수 

		//add them to new population
		vecNewPop.push_back(baby1);//새로 만들어진 2염색체 넣어주기
		vecNewPop.push_back(baby2);
	}

	//copy into next generation
	m_vecPopulation = vecNewPop;

	//increment generation counter
	++m_iGeneration;
}

//-------------------------------Render-------------------------------
//
//	This function does all our drawing and textual output. Called from
// the winproc when it receives a WM_PAINT msg
//--------------------------------------------------------------------
void CgaTSP::Render(HDC surface, int cx, int cy)
{

		//draw all the cities
	for (int city_num = 0; city_num < m_pMap->m_vecCityCoOrds.size(); ++city_num)
	{
		int x = (int)m_pMap->m_vecCityCoOrds[city_num].x;
		int y = (int)m_pMap->m_vecCityCoOrds[city_num].y;
		
		Ellipse(surface, x-CITY_SIZE, y+CITY_SIZE, x+CITY_SIZE, y-CITY_SIZE);
	}
	
	//draw the fittest route so far
	vector<int> route = m_vecPopulation[m_iFittestGenome].vecCities;
	
	//only display the routes if we are in a run
	if (m_iGeneration != 0)
	{
		
		MoveToEx(surface, (int)m_pMap->m_vecCityCoOrds[route[0]].x, (int)m_pMap->m_vecCityCoOrds[route[0]].y, NULL);
		
		for (int i=1; i<route.size(); ++i)
		{
			int CityX = (int)m_pMap->m_vecCityCoOrds[route[i]].x;
			int CityY = (int)m_pMap->m_vecCityCoOrds[route[i]].y;
			
			LineTo(surface, CityX, CityY);
			
			//draw the numbers representing the order the cities are visited.
			//No point drawing them after about a 100 cities as the display
			//just becomes confused
			if (NUM_CITIES < 100)
			{
				string CityNumber = itos(i);
			
				TextOut(surface, CityX, CityY, CityNumber.c_str(), CityNumber.size());
			}
		}

		//now draw the line from the last city visited back to the starting point
		LineTo(surface, (int)m_pMap->m_vecCityCoOrds[route[0]].x, (int)m_pMap->m_vecCityCoOrds[route[0]].y);
	}	
	
	//print stats
	string sGen = itos(m_iGeneration);
	sGen = "Generation: " + sGen;
	TextOut(surface, 5, 5, sGen.c_str(), sGen.size());
	string a = ftos(Time)+"ms";// 걸린 시간을 출력하기 위해 사용하였다.
	TextOut(surface, 5, 25, a.c_str(), a.size());
	a = "12181796 안우현";
	TextOut(surface, 5, 45, a.c_str(), a.size());



	if (!m_bStarted)
	{
		string Start = "Press Return to start a new run";

		TextOut(surface, cx/2 - (Start.size() * 3), cy - 20, Start.c_str(), Start.size());
	}

	else

	{
		string Start = "Space to stop";
		
		TextOut(surface, cx/2 - (Start.size() * 3), cy - 20, Start.c_str(), Start.size());
	}	
}


