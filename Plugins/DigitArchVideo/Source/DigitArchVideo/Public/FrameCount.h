// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "UObject/NoExportTypes.h"
#include "Runtime/Core/Public/HAL/Runnable.h"
#include "VideoData.h"
#include "FrameCount.generated.h"

USTRUCT()
struct FCountPeopleAndPoint
{
	GENERATED_BODY()

	UPROPERTY()
	int32 frame;
	UPROPERTY()
	int32 countPeople;
	UPROPERTY()
	int32 countPoints;
};

USTRUCT()
struct FCountFrame
{
	GENERATED_BODY()

	UPROPERTY()
	int32 FramesCount;
	UPROPERTY()
		int32 People;
	UPROPERTY()
		int32 Points;
	UPROPERTY()
	TArray<FCountPeopleAndPoint> PeopleAndPoints;
};

class DIGITARCHVIDEO_API FrameCountThread : public FRunnable
{

public:

	FrameCountThread();

private:

	uint32 Run() override;
	void Stop() override;
	void Exit() override;

	const FString ProjectDir = FPaths::ProjectDir() / "Log";
	const FString fileName = "FrameCount.json";

	UVideoData* JsonDataClass;
	
	bool bWorking = true;
};

UCLASS(BlueprintType)
class DIGITARCHVIDEO_API UFrameCount : public UObject
{
	GENERATED_BODY()

public:
		~UFrameCount();

		UFUNCTION(BlueprintCallable)
		static UFrameCount* GetInitFrameCount();

private:

	TUniquePtr<FrameCountThread> frameCountThread;

	FRunnableThread* Thread;
};


