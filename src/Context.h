#pragma once

#include "Program.h"
class Context
{
public:
	Context();

public:
	static std::unique_ptr<Context> Create();

	void Render();

private:
	bool Initialize();
	std::unique_ptr<Program> _program;
};