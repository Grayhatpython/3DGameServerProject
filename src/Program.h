#pragma once

class Shader;
class Program
{
public:
	Program();
	~Program();

public:
	static std::unique_ptr<Program> Create(const std::vector<std::shared_ptr<Shader>>& shaders);

public:
	uint32_t GetProgram() const { return _program; }

private:
	bool Link(const std::vector<std::shared_ptr<Shader>>& shaders);

private:
	uint32_t _program{ 0 };
};