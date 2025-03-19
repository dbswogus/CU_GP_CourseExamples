#include "GameFunc.h"
#include <windows.h>

bool f_input_left = false, f_input_right = false, f_input_up = false, f_input_down = false; //비행기 이동을 위한 상태
//기존 코드는 키보드를 때면 바로 f_input = 0이 되어서 멈추는 현상 발생 -> true 일 때만 움직이게
bool m_input; //미사일 이동을 위한 상태

std::string f_output; // 비행기 텍스쳐
std::string m_output; // 미사일 텍스쳐


//비행기 위치
int f_X;
int f_Y;

//미사일 위치
int m_X;
int m_Y;

// 흘러간 시간 기록
double g_elapsed_time_ms;


/////////////////////////////////////////////////////////////
// InitGame() 
// 프로그램이 시작될 때 최초에 한 번 호출되는 함수.
// 이 함수에서 게임에 필요한 자원(이미지, 사운드 등)을 로딩하고, 상태 변수들을 초기화 해야한다.
void InitGame() {
	f_output = "*";
	m_output = "!";
	m_input = false;

	g_flag_running = true;

	f_X = 10;
	f_Y = 10;
	g_elapsed_time_ms = 0;

	// std::cout 출력에 버퍼를 사용하여, 출력 속도가 느려지는 현상을 피한다.
	setvbuf(stdout, NULL, _IOLBF, 4096);

	// Clear the console screen.
	// 표준출력 화면을 깨끗히 지운다.
	system("cls");
}






/////////////////////////////////////////////////////////////
// Update() 
// 게임의 내용을 업데이트하는 함수.
// 실제 게임의 룰을 구현해야하는 곳.
// 게임에서 일어나는 변화는 모두 이 곳에서 구현한다.
// main 함수의 while loop에 의해서 무한히 반복 호출된다는 것을 주의.
void Update() {
	//키 입력에 따른 로직
	
	//비행기
	if (f_input_left) f_X -= 1; // left
	
	else if (f_input_right) f_X += 1; // right

	else if (f_input_up) f_Y -= 1;//up
	
	else if (f_input_down) f_Y += 1;//down
	

	//////////////////////////////////////////////
	// 화면을 벗어났을 때 다시 돌아오게 하기
	if (f_X > 29) f_X = 29;
	
	else if (f_X < 0) f_X = 0;

	if (f_Y < 0) f_Y = 0;

	else if (f_Y > 19) f_Y = 19;
	

	// 미사일
	if (!m_input)
	{
		m_X = f_X;
		m_Y = f_Y;
	}
	else {
		m_Y -= 1;
		if (m_Y <0)
		{
			m_input = false;
		}
	}

	////////////////////////////////////////////////
	g_elapsed_time_ms += 33;
}




/////////////////////////////////////////////////////////////
// Render() 
// 그림을 그리는 함수.
// main 함수의 while loop에 의해서 무한히 반복 호출된다는 것을 주의.
void Render() {
	//// 1. 배경 그리기.
	// 1.1. 커서를 콘솔 화면의 왼쪽 위 모서리 부분으로 옮긴다. 좌표(0, 0)
	// <windows.h>에서 제공하는 함수를 사용한다.
	COORD cur;
	cur.X = 0;
	cur.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);

	
	//// 1.2. 배경 부분을 '_'으로 채운다.
	for ( int i=0; i<20; i++ ) {
		for ( int j=0; j<30; j++ ) {
			std::cout << "_";
		}
		std::cout << std::endl;
	}

	//// 1.3. 배경 아래에 시간을 표시한다,
	std::cout << "Elapsed Time: " << g_elapsed_time_ms / 1000.0f << std::endl;


	//// 2. 캐릭터 그리기.
	
	// 2.1. 비행기 그리기

	cur.X = f_X;
	cur.Y = f_Y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);
	std::cout << f_output;
	std::cout.flush(); //출력버퍼 안비워주니까 문제가 생김 *! 이런식으로 출력 됨


	//2.2 미사일 그리기
	if (m_input)
	{
		cur.X = m_X;
		cur.Y = m_Y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);
		std::cout << m_output;
	}
	//// 3. 프레임 완성.
	// std::cout으로 출력한 내용 중, 아직 화면에 표시되 않고 버퍼에 남아 있는 것이 있다면, 모두 화면에 출력되도록 한다.
	std::cout.flush();
}



/////////////////////////////////////////////////////////////
// HandleEvents() 
// 이벤트를 처리하는 함수.
// main 함수의 while loop에 의해서 무한히 반복 호출된다는 것을 주의.
void HandleEvents()
{
	SDL_Event event;

	if (SDL_PollEvent(&event)) {

		switch (event.type) {

		case SDL_QUIT:
			g_flag_running = false;
			break;

		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_LEFT) {
				f_input_left = true; // 왼쪽
			}
			else if (event.key.keysym.sym == SDLK_RIGHT) {
				f_input_right = true; // 오른쪽
			}
			else if (event.key.keysym.sym == SDLK_UP) {
				f_input_up = true; // 위
			}
			else if (event.key.keysym.sym == SDLK_DOWN) {
				f_input_down = true; // 아래
			}
			else if (event.key.keysym.sym == SDLK_SPACE) {
				m_input = true;
			}
			break;

		case SDL_KEYUP:
			if (event.key.keysym.sym == SDLK_LEFT) {
				f_input_left = false;
			}
			else if (event.key.keysym.sym == SDLK_RIGHT) {
				f_input_right = false;
			}
			else if (event.key.keysym.sym == SDLK_UP) {
				f_input_up = false;
			}
			else if (event.key.keysym.sym == SDLK_DOWN) {
				f_input_down = false;
			}
			break;

		default:
			break;
		}
	}

}




/////////////////////////////////////////////////////////////
// ClearGame() 
// 프로그램이 끝날 때 한 번 호출되는 함수.
// 이 함수에서 사용된 자원(이미지, 사운드 등)과 메모리 등을 해제해야한다.
void ClearGame()
{
}

