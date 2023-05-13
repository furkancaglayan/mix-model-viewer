#include "mixAsset_loader_shader.h"

namespace mix
{
    namespace assetsystem
    {
        namespace loaders
        {

            mix::assetsystem::mixAsset_item* mixAsset_loader_shader::resolve_impl (mix::platform::mixFile& file)
            {
                auto type = mix::shader::get_shader_type (file.get_extension());
                return new mix::assetsystem::mixShader (file.get_path (), file.read_all_text (), type);
            }
            bool mixAsset_loader_shader::save_impl (mix::platform::mixFile& file, mix::assetsystem::mixAsset_item* item)
            {
                return false;
            }
        }     // namespace loaders
    }         // namespace assetsystem
} // namespace mix