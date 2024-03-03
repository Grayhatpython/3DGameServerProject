#include "Program.h"
#include "Shader.h"

Program::Program()
{

}

Program::~Program()
{
	if (_program)
		glDeleteProgram(_program);
}

std::unique_ptr<Program> Program::Create(const std::vector<std::shared_ptr<Shader>>& shaders)
{
	auto program = std::unique_ptr<Program>(new Program());
	if (program->Link(shaders) == false)
		return nullptr;

	return std::move(program);
}

bool Program::Link(const std::vector<std::shared_ptr<Shader>>& shaders)
{
	_program = glCreateProgram();

	for (const auto& shader : shaders)
		glAttachShader(_program, shader->GetShader());

	glLinkProgram(_program);

	int success = 0;
	glGetProgramiv(_program, GL_LINK_STATUS, &success);
	if (!success)
	{
		char infoLog[1024];
		glGetProgramInfoLog(_program, 1024, nullptr, infoLog);
		SPDLOG_ERROR("Failed to link program: {}", infoLog);
		return false;
	}

	return true;
}
