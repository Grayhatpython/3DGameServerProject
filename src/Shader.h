#pragma once

class Shader
{
private:
	Shader();

public:
	~Shader();

	static std::unique_ptr<Shader> CreateFormFile(const std::string& fileName, GLenum shaderType);

public:
	uint32_t	GetShader() const { return _shader; }

private:
	bool		LoadFild(const std::string& fileName, GLenum shaderType);

private:
	uint32_t	_shader{ 0 };
};

