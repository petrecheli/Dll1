#include "sdk.h"
#include "pch.h"
#include <Windows.h>
#include <future>

std::future<void> main_future;

UWorld* world = 0;

void init()
{

    //Init World
    world = 0x00000;

    for (int i = 0; i < world->Levels.Count; i++) {
        auto ptr = world->Levels.Objects[i];

        if (ptr) {
            auto actors = ptr->NearActors;

            for (int j = 0; j < actors.Count; j++) {

                auto actor = actors.Objects[j];

                if (actor) {
                    printf("[%d] Actor %llx", j, (uint64_t)actor);
                }
            }

        }
    }
}


BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        main_future = std::async(std::launch::async, init);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

