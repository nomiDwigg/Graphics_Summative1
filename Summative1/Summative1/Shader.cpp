// library
#include<iostream>
#include<fstream>
#include<vector>
#include<iterator>

// this
#include "Shader.h"

Shader::Shader(void) {}
Shader::~Shader(void) {}

std::map<const char*, GLuint>
Shader::uniqueIDs;

GLuint 
Shader::CreateProgram(const char* vertexShaderFilename, const char* fragmentShaderFilename)
{
	std::string programName = vertexShaderFilename + *fragmentShaderFilename;

	// ensure thgis program has not already been created
	std::map<const char*, GLuint>::iterator iterProgramID;
	iterProgramID = uniqueIDs.find(programName.c_str());
	if (iterProgramID != uniqueIDs.end())
	{
		return(uniqueIDs[programName.c_str()]);
	}
	else
	{
		// Create the shaders from the filepath
		GLuint vertex = CreateShader(GL_VERTEX_SHADER, vertexShaderFilename);
		GLuint fragment = CreateShader(GL_FRAGMENT_SHADER, fragmentShaderFilename);

		// Create the program handle, attach the shaders and link it
		GLuint program = glCreateProgram();
		glAttachShader(program, vertex);
		glAttachShader(program, fragment);
		glLinkProgram(program);


		// Check for link errors
		int link_result = 0;
		glGetProgramiv(program, GL_LINK_STATUS, &link_result);
		if (link_result == GL_FALSE)
		{
			PrintErrorDetails(false, program, programName.c_str());
			return 0;
		}

		uniqueIDs.insert(std::pair<const char*, GLuint>(programName.c_str(), program));
		return program;
	}
}

GLuint 
Shader::CreateShader(GLenum shaderType, const char* shaderName)
{
	// Read the shader files and save the source code as strings
	std::string shaderSource = ReadShaderFile(shaderName);

	// ensure that this shader has not already been created
	std::map<const char*, GLuint>::iterator iterShaderID = uniqueIDs.find(shaderName);
	if (iterShaderID != uniqueIDs.end())
	{
		return(uniqueIDs[shaderName]);
	}
	else
	{
		// Create the shader ID and create pointers for source code string and length
		GLuint shaderID = glCreateShader(shaderType);
		const char* shaderSourcePtr = shaderSource.c_str();

		// Populate the Shader Object (ID) and compile
		glShaderSource(shaderID, 1, &shaderSourcePtr, NULL);
		glCompileShader(shaderID);

		// Check for errors
		int compile_result = 0;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compile_result);
		if (compile_result == GL_FALSE)
		{
			PrintErrorDetails(true, shaderID, shaderName);
			return 0;
		}

		uniqueIDs.insert(std::pair< const char*, GLuint>(shaderName, shaderID));
		return shaderID;
	}
}

std::string 
Shader::ReadShaderFile(const char* filename)
{
	// Open the file for reading
	std::ifstream file(filename, std::ios::in);
	std::string shaderCode;

	// Ensure the file is open and readable
	if (!file.good()) {
		std::cout << "Cannot read file:  " << filename << std::endl;
		return "";
	}

	// Determine the size of of the file in characters and resize the string variable to accomodate
	file.seekg(0, std::ios::end);
	shaderCode.resize((unsigned int)file.tellg());

	// Set the position of the next character to be read back to the beginning
	file.seekg(0, std::ios::beg);
	// Extract the contents of the file and store in the string variable
	file.read(&shaderCode[0], shaderCode.size());
	file.close();
	return shaderCode;
}

void 
Shader::PrintErrorDetails(bool isShader, GLuint id, const char* name)
{
	int infoLogLength = 0;
	// Retrieve the length of characters needed to contain the info log
	(isShader == true) ? glGetShaderiv(id, GL_INFO_LOG_LENGTH, &infoLogLength) : glGetProgramiv(id, GL_INFO_LOG_LENGTH, &infoLogLength);
	std::vector<char> log(infoLogLength);

	// Retrieve the log info and populate log variable
	(isShader == true) ? glGetShaderInfoLog(id, infoLogLength, NULL, &log[0]) : glGetProgramInfoLog(id, infoLogLength, NULL, &log[0]);
	std::cout << "Error compiling " << ((isShader == true) ? "shader" : "program") << ": " << name << std::endl;
	std::cout << &log[0] << std::endl;
}