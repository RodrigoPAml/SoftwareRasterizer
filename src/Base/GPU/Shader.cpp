#include <Rasterizer.hpp>
#include "Shader.hpp"

namespace Rasterizer {
namespace GPU {

	int Shader::TotalInstances = 0;

	Shader::Shader(
		const std::string& verticeShader, 
		const std::string& fragmentShader, 
		const std::string& geometryShader
	)
	{
		Shader::TotalInstances++;

		this->id = 0;

		std::string error = "";

		char* VS = nullptr;
		char* FS = nullptr;
		char* GS = nullptr;

		if(verticeShader.size() > 0)
		{
			VS = new char[verticeShader.size() + 1];
			strcpy(VS, verticeShader.c_str());
		}

		if(fragmentShader.size() > 0)
		{
			FS = new char[fragmentShader.size() + 1];
			strcpy(FS, fragmentShader.c_str());
		}
			
		if(geometryShader.size() > 0)
		{
			GS = new char[geometryShader.size() + 1];
			strcpy(GS, geometryShader.c_str());
		}		
			
		unsigned int vertex, fragment, geometry;

		vertex = glCreateShader(GL_VERTEX_SHADER);

		glShaderSource(vertex, 1, &VS, NULL);
		glCompileShader(vertex);

		error = Shader::GetError(vertex, "VertexData");
			
		if(!error.empty())
		{
			glDeleteShader(vertex);

			delete[] VS;
			delete[] FS;
			delete[] GS;
		}

		if (!fragmentShader.empty())
		{
			fragment = glCreateShader(GL_FRAGMENT_SHADER);

			glShaderSource(fragment, 1, &FS, NULL);
			glCompileShader(fragment);

			error = Shader::GetError(fragment, "FRAGMENT");

			if (!error.empty())
			{
				glDeleteShader(vertex);
				glDeleteShader(fragment);

				delete[] VS;
				delete[] FS;
				delete[] GS;
			}
		}

		if(!geometryShader.empty())
		{
			geometry = glCreateShader(GL_GEOMETRY_SHADER);

			glShaderSource(geometry, 1, &GS, NULL);
			glCompileShader(geometry);

			error = Shader::GetError(fragment, "GEOMETRY");

			if(!error.empty())
			{
				glDeleteShader(vertex);
				glDeleteShader(fragment);
				glDeleteShader(geometry);

				delete[] VS;
				delete[] FS;
				delete[] GS;
			}
		}

		this->id = glCreateProgram();

		glAttachShader(this->id, vertex);

		if(!fragmentShader.empty())
			glAttachShader(this->id, fragment);

		if(!geometryShader.empty())
			glAttachShader(this->id, geometry);

		glLinkProgram(this->id);

		error = Shader::GetError(fragment, "FRAGMENT");

		glDeleteShader(vertex);

		if (!fragmentShader.empty())
			glDeleteShader(fragment);

		if (!geometryShader.empty())
			glDeleteShader(geometry);

		delete[] VS;
		delete[] FS;
		delete[] GS;

		if(!error.empty())
		{
			glDeleteShader(this->id);

			this->id = 0;
		}
	}

	Shader::~Shader()
	{
		Shader::TotalInstances--;

		if(this->id != 0)
		{
			if(Shader::currentID == this->id)
			{
				Shader::currentID = 0;
				glUseProgram(0);
			}

			glDeleteProgram(this->id);
		}
	}

	unsigned int Shader::GetId() const
	{
		return this->id;
	}

	void Shader::Use() const
	{
		glUseProgram(this->id);
		Shader::currentID = this->id;
	}
	
	void Shader::SetBool(const std::string& label, bool value) 
	{
		glUniform1i(GetUniform(label), (int)value);
	}

	void Shader::SetInt(const std::string& label, int value) 
	{
		glUniform1i(GetUniform(label), value);
	}

	void Shader::SetFloat(const std::string& label, float value) 
	{
		glUniform1f(GetUniform(label), value);
	}

	void Shader::SetXY(const std::string& label, float x, float y) 
	{
		glUniform2f(GetUniform(label), x, y);
	}

	void Shader::SetXYZ(const std::string& label, float x, float y, float z) 
	{
		glUniform3f(GetUniform(label), x, y, z);
	}

	void Shader::SetXYZW(const std::string& label, float x, float y, float z, float w) 
	{
		glUniform4f(GetUniform(label), x, y, z, w);
	}

	void Shader::ClearCurrentShader()
	{
		glUseProgram(0);
		Shader::currentID = 0;
	}

	int Shader::GetInstanceCount()
	{
		return Shader::TotalInstances;
	}

	unsigned int Shader::GetUniform(const std::string& label)
	{
		unsigned int uniform;
		auto it = this->uniforms.find(label);

		if (it != this->uniforms.end())
			uniform = it->second;
		else
		{
			uniform = glGetUniformLocation(this->id, label.c_str());
			this->uniforms[label] = uniform;
		}

		return uniform;
	}

	std::string Shader::GetError(unsigned int shader, const std::string& type)
	{
		GLint success = 0;
		GLchar error[1024];

		if(type != "PROGRAM")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

			if(!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, error);

				return error;
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);

			if(!success)
			{
				glGetProgramInfoLog(shader, 1024, NULL, error);
					
				return error;
			}
		}

		return "";
	}

	unsigned int Shader::currentID = 0;
}}
