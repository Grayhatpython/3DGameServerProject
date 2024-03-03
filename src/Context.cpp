#include "Context.h"
#include "Program.h"
#include "Shader.h"

Context::Context()
{
}

std::unique_ptr<Context> Context::Create()
{
	auto context = std::unique_ptr<Context>(new Context());
	if (context->Initialize() == false)
		return nullptr;

	return std::move(context);
}

void Context::Render()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(_program->GetProgram());
    glDrawArrays(GL_POINTS, 0, 1);
}

bool Context::Initialize()
{
    std::shared_ptr<Shader> vertexShader = Shader::CreateFormFile("../Shader/simple.vs", GL_VERTEX_SHADER);
    std::shared_ptr<Shader> fragmentShader = Shader::CreateFormFile("../Shader/simple.fs", GL_FRAGMENT_SHADER);

    if (vertexShader == nullptr || fragmentShader == nullptr)
        return false;

    SPDLOG_INFO("Vertex Shader id : {}", vertexShader->GetShader());
    SPDLOG_INFO("Fragment Shader id : {}", fragmentShader->GetShader());

    _program = Program::Create({ fragmentShader, vertexShader });
    if (_program == nullptr)
        return false;

    SPDLOG_INFO("Program id : {}", _program->GetProgram());

    glClearColor(0.1f, 0.1f, 0.1f, 0.0f);

    uint32_t vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

	return true;
}
