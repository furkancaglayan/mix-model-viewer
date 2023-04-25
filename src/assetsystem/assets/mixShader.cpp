#include "mixShader.h"
#include "../../platform/mixFile.h"

mix::assetsystem::mixShader::mixShader (const mix::platform::mixAsset_path& path, const std::string& source, mix::shader::shader_type type)
: _type{ type }, mix::assetsystem::mixAsset_item (path)
{
    compile (source, _type);
}

mix::assetsystem::mixShader::mixShader (const mix::platform::mixAsset_path& path)
: _type{ mix::shader::get_shader_type (path.get_extension ()) }, mix::assetsystem::mixAsset_item (path)
{
    auto source = mix::platform::mixFile (path).read_all_text();
    compile (source, _type);
}

mix::assetsystem::mixShader::~mixShader ()
{
    glDeleteShader (shader_id);
}

void mix::assetsystem::mixShader::compile (const std::string& source, mix::shader::shader_type type)
{
    shader_id = glCreateShader ((GLenum)type);
    auto c_source = source.c_str ();
    glShaderSource (shader_id, 1, &c_source, NULL);
    glCompileShader (shader_id);
    // print compile errors if any

    int success;
    char infoLog[512];
    glGetShaderiv (shader_id, GL_COMPILE_STATUS, &success);
    is_compiled = success;
    if (!success)
    {
        //TODO: fallback to shader
        glGetShaderInfoLog (shader_id, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}
