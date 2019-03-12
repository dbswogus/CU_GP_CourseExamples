#include "GameFunc.h"
#include <iostream>
#include <windows.h>

extern bool g_flag_running;

// ĳ������ ���� ����
int g_state; // ��ǥ��: 0, �ູ: 1, ����: 2

// ĳ������ ��ġ
int g_pos_x;
int g_pos_y;

// �귯�� �ð� ���
double g_time;


/////////////////////////////////////////////////////////////
// InitGame() 
// ���α׷��� ���۵� �� ���ʿ� �� �� ȣ��Ǵ� �Լ�.
// �� �Լ����� ���ӿ� �ʿ��� �ڿ�(�̹���, ���� ��)�� �ε��ϰ�, ���� �������� �ʱ�ȭ �ؾ��Ѵ�.
void InitGame()
{
	g_flag_running = true;
 
	g_state = 0;		// ��ǥ��
	g_pos_x = 15;
	g_pos_y = 10;
	g_time = 0.0;

	// Clear the console screen.
	// ǥ����� ȭ���� ������ �����.
	system("cls");
}






/////////////////////////////////////////////////////////////
// Update() 
// ������ ������ �����ϴ� �Լ�.
// ���ӿ� �Ͼ�� ��ȭ���� ��� �� ������ �����Ѵ�.
// ���� ������ ���� �����ؾ��ϴ� ��.
// main �Լ��� while loop�� ���ؼ� ������ �ݺ� ȣ��ȴ�.
void Update()
{
	// Elapsed Time
	// ���� ���ۺ��� ������� �귯�� �ð��� ���.
	// 0.03�ʸ� ���Ѵ�. main �Լ��� SDL_Delay(30) �κ��� �ָ�����.
	g_time += 0.03;

	// ĳ������ ��ġ�� �ڵ����� 1ĭ�� �̵��ϰ� �Ѵ�.
	g_pos_x++;

	// ĳ������ ��ġ�� ������ ��迡 ������ �ٽ� ���� ���� �κ����� ������.  
	if ( g_pos_x >= 29 ) g_pos_x=0;
}




/////////////////////////////////////////////////////////////
// Render() 
// �׸��� �׸��� �Լ�.
// main �Լ��� while loop�� ���ؼ� ������ �ݺ� ȣ��ȴ�.
void Render()
{
	//// 1. ��� �׸���.
	// 1.1. Ŀ���� �ܼ� ȭ���� ���� �� �𼭸� �κ����� �ű��. ��ǥ(0, 0)
	// <windows.h>���� �����ϴ� �Լ��� ����Ѵ�.
	COORD cur;
	cur.X = 0;
	cur.Y = 0;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);

	// 1.2. ��� �κ��� '.'���� ä���.
	for ( int i=0; i<20; i++ )
	{
		for ( int j=0; j<30; j++ )
		{
			std::cout << ".";
		}
		std::cout << std::endl;
	}

	// 1.3. ��� �Ʒ��� �ð��� ǥ���Ѵ�,
	std::cout << "Elapsed Time: " << g_time << std::endl;


	//// 2. ĳ���� �׸���.
	// 2.1. Ŀ���� ĳ���Ͱ� �׷��� ��ġ�� �ű��. 
	cur.X = g_pos_x;
	cur.Y = g_pos_y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);

	// 2.2. ���� ���¿� �´� ĳ���� ǥ���� �׸���.
	if ( g_state == 1 )
	{
		std::cout << "(:";
	}
	else if ( g_state == 2 )
	{
		std::cout << "o;";
	}
	else 
	{
		std::cout << "|:";
	}

}



/////////////////////////////////////////////////////////////
// HandleEvents() 
// �̺�Ʈ�� ó���ϴ� �Լ�.
// main �Լ��� while loop�� ���ؼ� ������ �ݺ� ȣ��ȴ�.
void HandleEvents()
{
	SDL_Event event;
	if(SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			g_flag_running = false;
			break;

		case SDL_KEYDOWN:
			if ( event.key.keysym.sym == SDLK_LEFT )
			{
				g_state = 1;
			}
			else if ( event.key.keysym.sym == SDLK_RIGHT )
			{
				g_state = 2;
			}
			break;

		case SDL_KEYUP:
			if ( event.key.keysym.sym == SDLK_LEFT 
				|| event.key.keysym.sym == SDLK_RIGHT )
			{
				g_state = 0;
			}
			break;

		case SDL_MOUSEBUTTONDOWN:
		
			// If the mouse left button is pressed. 
			if ( event.button.button == SDL_BUTTON_LEFT )
			{
			}
			break;

		default:
			break;
		}
	}
}




/////////////////////////////////////////////////////////////
// ClearGame() 
// ���α׷��� ���� �� �� �� ȣ��Ǵ� �Լ�.
// �� �Լ����� ���� �ڿ�(�̹���, ���� ��)�� �޸� ���� �����ؾ��Ѵ�.
void ClearGame()
{
}

