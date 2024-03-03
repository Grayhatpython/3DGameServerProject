#include "Shader.h"

Shader::Shader()
{

}

Shader::~Shader()
{
	if (_shader)
		glDeleteShader(_shader);
}

std::unique_ptr<Shader> Shader::CreateFormFile(const std::string& fileName, GLenum shaderType)
{
	auto shader = std::unique_ptr<Shader>(new Shader());
	if (shader->LoadFild(fileName, shaderType) == false)
		return nullptr;

	return std::move(shader);
}

bool Shader::LoadFild(const std::string& fileName, GLenum shaderType)
{
	auto text = LoadTextFile(fileName);
	if (text.has_value() == false)
		return false;

	auto& source = text.value();
	const char* sourcePtr = source.c_str();
	auto sourceLength = static_cast<int32_t>(source.length());

	_shader = glCreateShader(shaderType);
	glShaderSource(_shader, 1, reinterpret_cast<const GLchar* const*>(&sourcePtr), &sourceLength);
	glCompileShader(_shader);

	int success = 0;
	glGetShaderiv(_shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		char infoLog[1024];
		glGetShaderInfoLog(_shader, 1024, nullptr, infoLog);
		SPDLOG_ERROR("Failed to compile shader : {}", fileName);
		SPDLOG_ERROR("Failed Info Log : {}", infoLog);
		return false;
	}

	return true;
}
