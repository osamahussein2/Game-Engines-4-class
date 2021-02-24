#include "HandleShaders.h"

std::unique_ptr<HandleShaders> HandleShaders::shaderInstance = nullptr;
std::unordered_map<std::string, GLuint> HandleShaders::programs = std::unordered_map<std::string, GLuint>();

HandleShaders::HandleShaders()
{
    
}

HandleShaders::~HandleShaders()
{
    OnDestroy();
}



HandleShaders* HandleShaders::GetInstance()
{
    if (shaderInstance.get() == nullptr) {
        shaderInstance.reset(new HandleShaders);
    }
    return shaderInstance.get();
}

void HandleShaders::CreateProgram(const std::string& shaderName_, const std::string& vertexShaderName_, const std::string& FragShaderName_)
{
    const std::string& vertexShaderCode = ReadShader(vertexShaderName_);
    const std::string& fragShaderCode = ReadShader(FragShaderName_);

    if (vertexShaderCode == "" || fragShaderCode == "") {
        return;
    }

    GLuint vertexShader = CreateShader(GL_VERTEX_SHADER, vertexShaderCode, shaderName_);
    GLuint fragmentShader = CreateShader(GL_FRAGMENT_SHADER, fragShaderCode, shaderName_);

    if (vertexShader == 0 || fragmentShader == 0) {
        return;
    }

    GLint linkResult = 0;
    GLuint program = glCreateProgram();

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &linkResult);

    if (!linkResult) {
        GLint infoLogLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &linkResult);
        std::vector<char> programLog(infoLogLength);
        glGetProgramInfoLog(program, infoLogLength, NULL, &programLog[0]);
        std::string programString(programLog.begin(), programLog.end());
        Debug::Error("Shaders have failed to link" + shaderName_ + "ERROR: " + programString, "HandleShaders.cpp", __LINE__);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        glDeleteProgram(program);
        return;
    }

    programs[shaderName_] = program;
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

GLuint HandleShaders::GetShader(const std::string& shaderName_)
{
    if (programs.find(shaderName_) != programs.end()) {
        return programs[shaderName_];
    }
    return 0;
}

void HandleShaders::OnDestroy()
{
    if (programs.size() > 0) {
        for (auto p : programs) {
            glDeleteProgram(p.second);
        }
        programs.clear();
    }
}

std::string HandleShaders::ReadShader(const std::string& filePath_)
{
    std::string shaderCode = "";
    std::ifstream file;
    file.exceptions(std::ifstream::badbit);
    try {
        file.open(filePath_);
        std::stringstream tmpStream;
        tmpStream << file.rdbuf();
        file.close();
        shaderCode = tmpStream.str();
    }
    catch (std::ifstream::failure error_) {
        Debug::Error("Couldn't read the shader file: " + filePath_, "HandleShaders.cpp", __LINE__);
        return "";
    }

    return shaderCode;
}

GLuint HandleShaders::CreateShader(GLenum shaderType, const std::string& source_, const std::string& shaderName_)
{
    GLint compileResult = 0;
    GLuint shader = glCreateShader(shaderType);
    const char* shaderCodePtr = source_.c_str();
    const int shaderCodeSize = source_.size();

    glShaderSource(shader, 1, &shaderCodePtr, &shaderCodeSize);
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);

    if (!compileResult) {
        GLint infoLogLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
        std::vector<char> shaderLog(infoLogLength);
        glGetShaderInfoLog(shader, infoLogLength, NULL, &shaderLog[0]);
        std::string shaderString(shaderLog.begin(), shaderLog.end());
        Debug::Error("Error compiling shader" + shaderName_ + "ERROR: \n" + shaderString, "HandleShaders.cpp", __LINE__);
        return 0;
    }

    return shader;
}