#include "ILevelToolManager.h"
#include "LevelToolRuntime.h"

/* Convert Image to UTexture2D need head file */
#include "IImageWrapper.h"
#include "IImageWrapperModule.h"
#include "Interfaces/IPluginManager.h"



UTexture2D* ILevelToolManager::AsyncGetLevelLoadBackgroundImage() const
{
	/* Query specify module,then used to get picture path */
	FModuleStatus TemModuleStatus;
	if (!FModuleManager::Get().QueryModule(*FString(TEXT("LevelToolCommon")),TemModuleStatus))
	{
		UE_LOG(FLevelToolRuntimeLog,Warning,TEXT("Query LevelToolCommon Module fail,lead not find specify image"))
		return nullptr;
	}
	
	/* Get Specify Picture Path in the Level Plugin */
	const FString LevelToolModulePath=TemModuleStatus.FilePath;
	const FString ImagePath=FPaths::ConvertRelativePathToFull(LevelToolModulePath+FString(TEXT("../../../../Image/LevelLoadBackground.Png")));
	
	/* First Get Image Raw Data */
	TArray<uint8> RawFileData;
	if (!FFileHelper::LoadFileToArray(RawFileData, *ImagePath))
	{
		UE_LOG(LogTemp, Error, TEXT("Load %s file to array failed."), *ImagePath);
		return nullptr;
	}

	/* Create UTexture2D Object */
	UTexture2D* Texture = NewObject<UTexture2D>(GetTransientPackage(), NAME_None, RF_Transient);

	/* Image to UTexture2D Core Implementation */
	TFunction<void()> CustomFunction = [Texture, RawFileData,ImagePath]
	{
		/* Get IImageWrapperModule*/
		IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));

		/* Detect image format,because difference image format need different image wrapper */
		const EImageFormat DetectedFormat = ImageWrapperModule.DetectImageFormat(RawFileData.GetData(), RawFileData.Num());
		const TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule.CreateImageWrapper(DetectedFormat);

		/* Detect image Wrapper is valid then set compressed, then pass by GetRaw get Image data */
		if (ImageWrapper.IsValid() && ImageWrapper->SetCompressed(RawFileData.GetData(), RawFileData.Num()))
		{
			/* Get image raw data */
			TArray<uint8> UncompressedRGBA;
			if (Texture && ImageWrapper->GetRaw(ERGBFormat::RGBA, 8, UncompressedRGBA))
			{
				/* set UTexture2D texture data */
				Texture->SetPlatformData(new FTexturePlatformData());

				/* set UTexture2D size(Width and Height) */
				Texture->GetPlatformData()->SizeX = ImageWrapper->GetWidth();
				Texture->GetPlatformData()->SizeY = ImageWrapper->GetHeight();

				/* I don't know,but UE is like this write  */
				Texture->GetPlatformData()->SetNumSlices(1);

				/* Format in which mip data is stored */
				Texture->GetPlatformData()->PixelFormat = PF_B8G8R8A8;
				
				// Allocate first mipmap.
				FTexture2DMipMap* Mip = new FTexture2DMipMap();
				Texture->GetPlatformData()->Mips.Add(Mip);
				Mip->SizeX = Texture->GetPlatformData()->SizeX;
				Mip->SizeY = Texture->GetPlatformData()->SizeY;
             
				// Lock the texture so that it can be modified
				Mip->BulkData.Lock(LOCK_READ_WRITE);
				
				uint8* TextureData = (uint8*) Mip->BulkData.Realloc(Mip->SizeX * Mip->SizeY * 4);
				FMemory::Memcpy(TextureData, UncompressedRGBA.GetData(), UncompressedRGBA.Num());
				Mip->BulkData.Unlock();

				/* clear data */
				UncompressedRGBA.Empty();
				
				// FLevelToolImageData TemImageData;
				// TemImageData.Image=Texture;
				// TemImageData.ImagePath=ImagePath;
				//ImageData.Add(*FPaths::GetBaseFilename(ImagePath),TemImageData);
				Texture->UpdateResource();
			}
		}
	};
	//Has Problem!!!!!
	Async(EAsyncExecution::ThreadPool, CustomFunction);
	return Texture;
	
}

UTexture2D* ILevelToolManager::GetLevelLoadBackgroundImage() const
{
	//获取LevelToolPlugin插件
	const TSharedPtr<IPlugin> PluginManager=IPluginManager::Get().FindPlugin(TEXT("LevelToolPlugin"));
	const FString LevelToolPluginPath= PluginManager->GetBaseDir();
	
	//获取指定的LevelLoadBackground图片路径
	const FString ImagePath=FPaths::Combine(LevelToolPluginPath,FString(TEXT("Image/LevelLoadBackground.Png")));

	//检查文件是否存在
	if (!FPaths::FileExists(ImagePath)) return nullptr;
	
	/* First Get Image Raw Data */
	TArray<uint8> RawFileData;
	if (!FFileHelper::LoadFileToArray(RawFileData, *ImagePath))
	{
		UE_LOG(LogTemp, Warning, TEXT("Load %s file to array failed."), *ImagePath);
		return nullptr;
	}

	/* Create UTexture2D Object */
	UTexture2D* Texture = NewObject<UTexture2D>(GetTransientPackage(), NAME_None, RF_Transient);

	/* Image to UTexture2D Core Implementation */

	/* Get IImageWrapperModule*/
	IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));

	/* Detect image format,because difference image format need different image wrapper */
	const EImageFormat DetectedFormat = ImageWrapperModule.DetectImageFormat(RawFileData.GetData(), RawFileData.Num());
	const TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule.CreateImageWrapper(DetectedFormat);

	/* Detect image Wrapper is valid then set compressed, then pass by GetRaw get Image data */
	if (ImageWrapper.IsValid() && ImageWrapper->SetCompressed(RawFileData.GetData(), RawFileData.Num()))
		{
			/* Get image raw data */
			TArray<uint8> UncompressedRGBA;
			if (Texture && ImageWrapper->GetRaw(ERGBFormat::RGBA, 8, UncompressedRGBA))
			{
				/* set UTexture2D texture data */
				Texture->SetPlatformData(new FTexturePlatformData());

				/* set UTexture2D size(Width and Height) */
				Texture->GetPlatformData()->SizeX = ImageWrapper->GetWidth();
				Texture->GetPlatformData()->SizeY = ImageWrapper->GetHeight();
				
				/* I don't know,but UE is like this write,Guess is picture division */
				Texture->GetPlatformData()->SetNumSlices(1);

				/* Format in which mip data is stored */
				Texture->GetPlatformData()->PixelFormat = PF_B8G8R8A8;
				
				/* Allocate a mipmap,because not mipmap will show not mipmap err */
				FTexture2DMipMap* Mip = new FTexture2DMipMap();
				Texture->GetPlatformData()->Mips.Add(Mip);

				/* set mipmap size */
				Mip->SizeX = Texture->GetPlatformData()->SizeX;
				Mip->SizeY = Texture->GetPlatformData()->SizeY;
             
				/* Lock the texture so that it can be modified */
				Mip->BulkData.Lock(LOCK_READ_WRITE);

				/* for mipmap allocate size,Width * Height * PixelSize */
				uint8* TextureData = (uint8*) Mip->BulkData.Realloc(Mip->SizeX * Mip->SizeY * 4);

				/* for allocate space set data */
				FMemory::Memcpy(TextureData, UncompressedRGBA.GetData(), UncompressedRGBA.Num());

				/* Unlock */
				Mip->BulkData.Unlock();

				/* Update resource,else will breakpoint */
				Texture->UpdateResource();
				
				/* clear data */
				UncompressedRGBA.Empty();
			}
		}
	return Texture;
}
