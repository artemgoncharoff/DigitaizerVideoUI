#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "VideoData.generated.h"

USTRUCT(BlueprintType)
struct FPeople
{
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite)
		TArray<float> pose_keypoints_2d;
};

USTRUCT(BlueprintType)
struct FFrameInfo
{
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite)
		TArray<FPeople> people;
	UPROPERTY(BlueprintReadWrite)
		FString version;
};

USTRUCT(BlueprintType)
struct FFrameData
{
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite)
		int32 frame;
	UPROPERTY(BlueprintReadWrite)
		FFrameInfo data;
};

USTRUCT(BlueprintType)
struct FVideoMeta
{
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite)
		TArray<FFrameData> frames;
};

UCLASS(BlueprintType)
class DIGITARCHVIDEO_API UVideoData : public UObject
{
	GENERATED_BODY()


public:

	UVideoData();
	~UVideoData();

	UFUNCTION(BlueprintCallable)
		static UVideoData* CreateVideoData();

	UFUNCTION(BlueprintCallable)
		void Destroy();

	void ReadJson(const FString& jsonData);

	UPROPERTY(BlueprintReadWrite)
	FVideoMeta VideoData;

private:

	FString read_file();

};
