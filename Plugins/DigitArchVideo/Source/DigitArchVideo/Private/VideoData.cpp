// Fill out your copyright notice in the Description page of Project Settings.

#include "VideoData.h"
#include "Runtime/Core/Public/Misc/Paths.h"
#include "Runtime/Json/Public/Json.h"
#include "Runtime/JsonUtilities/Public/JsonObjectConverter.h"
#include "Runtime/Core/Public/Misc/FileHelper.h"

UVideoData::UVideoData() : Super()
{
	UE_LOG(LogTemp, Log, TEXT("Hi!"));
}

UVideoData::~UVideoData()
{
	UE_LOG(LogTemp, Log, TEXT("Destroy!"));
}

UVideoData* UVideoData::CreateVideoData()
{
	auto obj = NewObject<UVideoData>();

	obj->ReadJson(obj->read_file());
	return obj;
}

void UVideoData::Destroy()
{
	delete this;
}

void UVideoData::ReadJson(const FString& jsonData)
{
	const TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(jsonData);
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);


	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		for (auto& json : JsonObject->Values)
		{
			FFrameData t;
			FString nameFrame = json.Key;
			nameFrame.RemoveFromEnd(".jpg");
			t.frame = FCString::Atoi(*nameFrame);
			FJsonObjectConverter::JsonObjectToUStruct<FFrameInfo>(json.Value->AsObject().ToSharedRef(), &t.data);

			VideoData.frames.Add(t);
		}

		VideoData.frames.Sort([](const FFrameData& a, const FFrameData& b)
		{
			return a.frame < b.frame;
		});
	}
}

FString UVideoData::read_file()
{
	const FString JsonPath = FPaths::ProjectPluginsDir() / "DigitArchVideo" / "Resources" / "test.json";
	FString data;
	FFileHelper::LoadFileToString(data, *JsonPath);
	return data;
}
