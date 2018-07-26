#pragma once
#include <iostream>
class Gamestate
{
public:
	~Gamestate();
	static Gamestate* Get();
	static void Clean();

	void PraiseErri(int iterations);
	enum State
	{
		Game,
		MainMenu,
		Quit
	};
	State currentState;

private:
	Gamestate();
	static Gamestate* Instance;
};
