#pragma once
#include <iostream>
class Gamestate
{
public:
	~Gamestate();
	void PraiseErri(int iterations);
	static Gamestate* Get();
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

