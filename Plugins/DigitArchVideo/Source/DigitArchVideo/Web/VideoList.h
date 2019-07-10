// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "DataRequestBase.h"
#include "VideoData.h"
#include "VideoList.generated.h"


USTRUCT(BlueprintType)
struct FVideoListStruct
{
	GENERATED_BODY()

		UPROPERTY(BlueprintReadOnly)
		TArray<FString> VideoName;
};

USTRUCT(BlueprintType)
struct FNewCoordinate
{
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite)
		FString Frame;

	UPROPERTY(BlueprintReadWrite)
		int32 PeopleIndex;
	
	UPROPERTY(BlueprintReadWrite)
		int32 PointsIndex;

	UPROPERTY(BlueprintReadWrite)
		float X;

	UPROPERTY(BlueprintReadWrite)
		float Y;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FVideoListDelegate, FVideoListStruct, VideoList);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FVideoMetaDelegate, UVideoData*, Data);

UCLASS()
class DIGITARCHVIDEO_API UVideoList : public UOnlineBlueprintCallProxyBase, public DataRequestBase
{
	GENERATED_BODY()
	
	
public:

	UFUNCTION(BlueprintCallable)
	static UVideoList* GetVideoList();

	UPROPERTY(BlueprintAssignable)
	FVideoListDelegate VideoListDelegate;

	UFUNCTION(BlueprintCallable)
	static UVideoList* GetVideoMeta();

	UPROPERTY(BlueprintAssignable)
	FVideoMetaDelegate VideoMeta;

	UFUNCTION(BlueprintCallable)
	static UVideoList* SetNewCoordinate(FNewCoordinate data);

private:

	TSharedPtr<IHttpRequest> HttpRequest;

	void ParseResp(const FString& jsonData);

	void Activate() override {};

	void OnCompleted(FHttpRequestPtr Req, FHttpResponsePtr Resp, bool success) override;
	void OnCompletedMeta(FHttpRequestPtr Req, FHttpResponsePtr Resp, bool success);
};
