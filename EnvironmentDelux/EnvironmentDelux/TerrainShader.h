#ifndef TERRAINSHADER_H
#define TERRAINSHADER_H

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glad\glad.h>
#include "Camera.h"
#include "Maths.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
class TerrainShader
{
public:
	TerrainShader();

	void Start() { glUseProgram(programID); }
	void Stop() { glUseProgram(0); }
	void CleanUp();

	void LoadTransformationMatrix(glm::mat4 matrix);
	void LoadProjectionMatrix(glm::mat4 matrix);
	void LoadViewMatrix(Camera camera);

	void LoadFloat(unsigned int location, float value)
	{
		glUniform1f(location, value);
	}

	void LoadVector3(unsigned int location, glm::vec3 vector)
	{
		glUniform3f(location, vector.x, vector.y, vector.z);
	}

	void LoadBoolean(unsigned int location, bool state)
	{
		float value = 0;
		if (state)
		{
			value = 1;
		}
		glUniform1f(location, value);
	}

	void LoadMatrix4(unsigned int location, glm::mat4 matrix)
	{
		glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
	}

	unsigned int GetProgramID() { return this->programID; }

	~TerrainShader();

private:
	unsigned int programID;
	unsigned int vertexShaderID;
	unsigned int fragmentShaderID;
	const char* VERTEX_FILE = "TerrainVertexShader.txt";
	const char* FRAGMENT_FILE = "TerrainFragmentShader.txt";

	// UNIFORM LOCATIONS //

	unsigned int transformationMatrixLocation;
	unsigned int projectionMatrixLocation;
	unsigned int viewMatrixLocation;

	/////////////////////

	unsigned int LoadShader(const char* filepath, unsigned int type);
	void CheckCompileErrors(unsigned int shader, std::string type);
	unsigned int GetUniformLocation(const char* name);

	void BindAttributes()
	{
		BindAttribute(0, "position");
		BindAttribute(1, "textureCoords");
	}

	void GetAllUniformLocations();

	void BindAttribute(int attribute, const char* variable)
	{
		glBindAttribLocation(programID, attribute, variable);
	}
};
#endif