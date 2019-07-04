// Fill out your copyright notice in the Description page of Project Settings.

#include "Authorize.h"
#include "Runtime/JsonUtilities/Public/JsonObjectConverter.h"


UAuthorize* UAuthorize::Registrate(FString name)
{
	auto obj = NewObject<UAuthorize>();

	obj->HttpRequest =  obj->CreateHttpRequest("api/user/registr");

	FAuthorizeT d;
	d.name = name;

	obj->HttpRequest->SetContentAsString(obj->GetContent(d));
	obj->HttpRequest->SetVerb("POST");
	obj->HttpRequest->OnProcessRequestComplete().BindUObject(obj, &UAuthorize::OnCompleted);
	obj->HttpRequest->ProcessRequest();

	return obj;
}

void UAuthorize::OnCompleted(FHttpRequestPtr Req, FHttpResponsePtr Resp, bool success)
{
	if (!success) {
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("%s, %i"), *Resp->GetURL(), Resp->GetResponseCode());

	ID = Resp->GetContentAsString();

	UE_LOG(LogTemp, Log, TEXT("%s"), *ID);

	AuthorizeDelegate.Broadcast();
}

void UAuthorize::Activate()
{
}

FString UAuthorize::GetContent(FAuthorizeT& d)
{
	FString json;

	FJsonObjectConverter::UStructToJsonObjectString(d, json);

	return json;
}
