#include "mixAsset_base.h"

namespace mix
{
    namespace assetsystem
    {
        void mix::assetsystem::mixAsset_base::read ()
        {
            assert (_data.is_open ());
            _content = std::string  ((std::istreambuf_iterator<char> (_data)),
                                  std::istreambuf_iterator<char> ());
        }


        inline void mix::assetsystem::mixAsset_base::close ()
        {
            assert (_data.is_open ());
            _data.close ();
        }
    } // namespace assetsystem
} // namespace mix