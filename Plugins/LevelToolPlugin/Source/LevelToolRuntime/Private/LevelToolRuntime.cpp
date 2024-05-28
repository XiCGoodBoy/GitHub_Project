#include "LevelToolRuntime.h"

DEFINE_LOG_CATEGORY(FLevelToolRuntimeLog);

#define LOCTEXT_NAMESPACE "FLevelToolRuntimeModule"

void FLevelToolRuntimeModule::StartupModule()
{
}

void FLevelToolRuntimeModule::ShutdownModule()
{
    
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FLevelToolRuntimeModule, LevelToolRuntime)