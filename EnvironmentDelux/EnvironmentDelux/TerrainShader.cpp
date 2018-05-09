#include "TerrainShader.h"


TerrainShader::TerrainShader()
{
	vertexShaderID = LoadShader(VERTEX_FILE, GL_VERTEX_SHADER);
	fragmentShaderID = LoadShader(FRAGMENT_FILE, GL_FRAGMENT_SHADER);
	programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	BindAttributes();
	glLinkProgram(programID);
	glValidateProgram(programID);
	GetAllUniformLocations();
}


TerrainShader::~TerrainShader()
{
}

void TerrainShader::CleanUp()
{
	Stop();
	glDetachShader(programID, vertexShaderID);
	glDetachShader(programID, fragmentShaderID);
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
	glDeleteProgram(programID);
}

unsigned int TerrainShader::LoadShader(const char* filepath, unsigned int type)
{
	// 1. retrieve the vertex/fragment source code from filePath
	std::string shaderCode;
	std::ifstream shaderFile;
	// ensure ifstream objects can throw exceptions:
	shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// open files
		shaderFile.open(filepath);
		std::stringstream shaderStream;
		// read file's buffer contents into streams
		shaderStream << shaderFile.rdbuf();
		// close file handlers
		shaderFile.close();
		// convert stream into string
		shaderCode = shaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	const char* Code = shaderCode.c_str();
	// 2. compile shaders
	unsigned int shaderID;
	// vertex shader
	shaderID = glCreateShader(type);
	glShaderSource(shaderID, 1, &Code, NULL);
	glCompileShader(shaderID);
	CheckCompileErrors(shaderID, "Shader");

	return shaderID;
}

void TerrainShader::CheckCompileErrors(unsigned int shader, std::string type)
{
	int success;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
}

unsigned int TerrainShader::GetUniformLocation(const char* name)
{
	return glGetUniformLocation(programID, name);
}

void TerrainShader::GetAllUniformLocations()
{
	transformationMatrixLocation = GetUniformLocation("transformationMatrix");
	projectionMatrixLocation = GetUniformLocation("projectionMatrix");
	viewMatrixLocation = GetUniformLocation("viewMatrix");
}



// Loading Uniforms //

void TerrainShader::LoadTransformationMatrix(glm::mat4 matrix)
{
	LoadMatrix4(transformationMatrixLocation, matrix);
}

void TerrainShader::LoadProjectionMatrix(glm::mat4 matrix)
{
	LoadMatrix4(projectionMatrixLocation, matrix);
}

void TerrainShader::LoadViewMatrix(Camera camera)
{
	glm::mat4 viewMatrix = Math::CreateViewMatrix(camera);
	LoadMatrix4(viewMatrixLocation, viewMatrix);
}

