#include <memory>
#include <vector>

#include "type.h"
#include "ipWorker.h"
#include "parser.h"


int main( int argc, char const *argv[] )
{
    WorkParams params{};
    if ( !ParserCommandLine( params, argc, argv ) ) 
    {
        return 2;
    }

    std::unique_ptr< IpWorker > ipWorker = IpWorker::MakePtr( params );

    ipWorker->ReadIpPool();
    if ( ipWorker->GetIpPool().empty() )
    {
        return 1;
    }
    ipWorker->SortingIpPool();
    ipWorker->Filtration();
    ipWorker->OutAddresses();
    return 0;
}
