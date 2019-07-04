// Fill out your copyright notice in the Description page of Project Settings.

#include "VideoList.h"
#include "Runtime/Json/Public/Json.h"
#include "JsonObjectConverter.h"

UVideoList* UVideoList::GetVideoList()
{
	auto obj = NewObject<UVideoList>();

	obj->HttpRequest = obj->CreateHttpRequest("api/file/names");

	obj->HttpRequest->SetVerb("GET");

	obj->HttpRequest->OnProcessRequestComplete().BindUObject(obj, &UVideoList::OnCompleted);
	obj->HttpRequest->ProcessRequest();

	return obj;
}

UVideoList* UVideoList::GetVideoMeta()
{
	auto obj = NewObject<UVideoList>();

	obj->HttpRequest = obj->CreateHttpRequest("api/file/meta");

	obj->HttpRequest->SetVerb("GET");

	obj->HttpRequest->OnProcessRequestComplete().BindUObject(obj, &UVideoList::OnCompletedMeta);
	obj->HttpRequest->ProcessRequest();

	return obj;
}

void UVideoList::ParseResp(const FString& jsonData)
{
	const TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(jsonData);
	TSharedPtr<FJsonValue> JsonValue;

	FVideoListStruct dateS;

	if (FJsonSerializer::Deserialize(JsonReader, JsonValue) && JsonValue.IsValid())
	{
		for (auto& json : JsonValue->AsArray())
		{
			dateS.VideoName.Add(json->AsString());
		}
	}

	

	VideoListDelegate.Broadcast(dateS);
}

void UVideoList::OnCompleted(FHttpRequestPtr Req, FHttpResponsePtr Resp, bool success)
{

	if (!success) {
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("%s, %i \n Body: %s"), *Resp->GetURL(), Resp->GetResponseCode(), *Resp->GetContentAsString());

	ParseResp(Resp->GetContentAsString());
}

void UVideoList::OnCompletedMeta(FHttpRequestPtr Req, FHttpResponsePtr Resp, bool success)
{
	if (!success) {
		return;
	}

	auto data = NewObject<UVideoData>();

	data->ReadJson(Resp->GetContentAsString());

	GLog->Log(Resp->GetContentAsString());

	VideoMeta.Broadcast(data);
}
