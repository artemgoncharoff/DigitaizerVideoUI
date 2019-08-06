#pragma once

#include "CoreMinimal.h"
#include "Http.h"

static class DIGITARCHVIDEO_API DataRequestBase
{
	
public:


	TSharedPtr<IHttpRequest> CreateHttpRequest(const FString& urlReq);

	virtual void OnCompleted(FHttpRequestPtr Req, FHttpResponsePtr Resp, bool success) = 0;
	
	FString ID;

	FString GetUrl();

private:

	FString CombineURL(const FString& urlReq);

	FString GetServerUrl(const FString& urlReq);

	FString ServerUrl;
};
