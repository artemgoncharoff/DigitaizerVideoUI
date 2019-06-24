// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "DataRequestBase.h"
#include "Authorize.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDelegatTest);

USTRUCT()
struct FAuthorizeT
{
	GENERATED_BODY()

	UPROPERTY()
		FString name;
};

USTRUCT()
struct FUserID
{
	GENERATED_BODY()

		UPROPERTY()
		FString LoginId;
};

UCLASS()
class DIGITARCHVIDEO_API UAuthorize : public UOnlineBlueprintCallProxyBase, public DataRequestBase
{
	GENERATED_BODY()


public:

	UFUNCTION(BlueprintCallable)
	static UAuthorize* Registrate(FString name);


	void OnCompleted(FHttpRequestPtr Req, FHttpResponsePtr Resp, bool success) override;

private:

	FDelegatTest* DelegatTest;

	TSharedPtr<IHttpRequest> HttpRequest;
	virtual void Activate() override;
	
	FString GetContent(FAuthorizeT& d);
};
