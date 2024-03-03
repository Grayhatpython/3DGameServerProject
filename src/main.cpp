#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include "Core.h"

int main(int argc, char** argv)
{   
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    {
        std::unique_ptr<Core> core = std::make_unique<Core>();
        assert(core->Initialize());

        core->Update();
    }

    return 0;
}