#ifndef DEFINES_H
#define DEFINES_H


///////////////////////////////// DEFINES ///////////////////////////////////////

#define WINDOW_WIDTH		500 //출력할 창의 크기
#define WINDOW_HEIGHT		500//출력할 창의 크기

#define NUM_CITIES			 10 //도식들의 수 즉노드의 수이다. 이를 조작하여 도시의 개수를 10 15 20으로 바꾸어 결과값을 확인한다
#define CITY_SIZE			  5 //도시들의 출력크기
				
#define	MUTATION_RATE		0.2 //돌연변이 발생확률에 대한 설정
#define	CROSSOVER_RATE	    0.75//교배율에 대한 설정
#define	POP_SIZE			  40 //염색체 수

//must be a multiple of 2 
#define NUM_BEST_TO_ADD	2




//used to rectify precision errors
#define EPSILON				0.000001//부동소수에러를 위한 입실론값

#endif