#include <iostream>
#include <fstream>
#include <string>
#include "Shader.hpp"

static std::string LoadSource(const char* filepath)
{
	std::string source;
	std::ifstream file;
	file.open(filepath);

	std::string line;

	while (getline(file, line))
	{
		source += (line + '\n');
	}

	file.close();

	return source;
}

static GLuint CompileShader(GLenum type, const char* source)
{
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, 0);
	glCompileShader(shader);

	int compileStatus;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
	if (compileStatus == GL_FALSE)
	{
		int messageLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &messageLength);
		messageLength++;
		char* message = new char[messageLength];
		glGetShaderInfoLog(shader, messageLength, &messageLength, message);
		message[messageLength - 1] = '\n';
		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "Vertex" : type == GL_FRAGMENT_SHADER ? "Fragment" : "Unknown") << " Shader!\n";
		std::cout << message;
		delete[messageLength] message;
		glDeleteShader(shader);
		return 0U;
	}
	return shader;
}

GLuint GenShaderProgram(const char* vs_filepath, const char* fs_filepath)
{
	std::string vertexShaderString = LoadSource(vs_filepath);
	std::string fragmentShaderString = LoadSource(fs_filepath);

	GLuint shaderProgram = glCreateProgram();
	GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, vertexShaderString.c_str());
	GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderString.c_str());
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}