#pragma once

#include "CoreMinimal.h"
#include "Misc/Paths.h"
#include "Misc/FileHelper.h"
#include "Engine/Texture2D.h"
#include "TextureResource.h"
#include "GameFramework/Actor.h"
#include "Async/Async.h"
#include "Engine/Level.h"


class LEVELTOOLRUNTIME_API ILevelToolManager
{
public:
	/* default construct */
	ILevelToolManager() {};

	static ILevelToolManager* Get()
	{
		static ILevelToolManager Singleton;
		return &Singleton;
	}
	UTexture2D* AsyncGetLevelLoadBackgroundImage() const;
	UTexture2D* GetLevelLoadBackgroundImage() const;
};