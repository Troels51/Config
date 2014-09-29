#include "Config.hpp"
#include "quickcheck/quickcheck.hh"
class PReadWriteRead : public Property<Config>
{
    bool holdsFor(const Config& config)
    {
        read();
        write();
        read();
    };

};