// Fill out your copyright notice in the Description page of Project Settings.

#include "FrameCount.h"
#include "Runtime/JsonUtilities/Public/JsonObjectConverter.h"

FrameCountThread::FrameCountThread()
{
}

uint32 FrameCountThread::Run()
{
	JsonDataClass = UVideoData::CreateVideoData();

	UE_LOG(LogTemp, Log, TEXT("Complited!"));
	
	FCountFrame data;

	data.FramesCount = JsonDataClass->VideoData.frames.Num();

	int PeopleCount = 0;
	int PointCount = 0;

	for (int i = 0; i < JsonDataClass->VideoData.frames.Num(); i++)
	{
		FCountPeopleAndPoint t;
		t.frame = i + 1;

		t.countPeople = JsonDataClass->VideoData.frames[i].data.people.Num();
		data.People += t.countPeople;
		
		for (int j = 0; j < JsonDataClass->VideoData.frames[i].data.people.Num(); j++)
		{
			for (int x = 0; x < JsonDataClass->VideoData.frames[i].data.people[j].pose_keypoints_2d.Num(); x++)
			{
				if (x % 2 == 0)
				{
					if(JsonDataClass->VideoData.frames[i].data.people[j].pose_keypoints_2d[x] > 1 && JsonDataClass->VideoData.frames[i].data.people[j].pose_keypoints_2d[x+1] > 1)
					{
						PointCount += 1;
					}
				}
				
			}

			PeopleCount += PointCount;
			PointCount = 0;
		}

		t.countPoints = PeopleCount;
		PeopleCount = 0;
		data.Points += t.countPoints;
		data.PeopleAndPoints.Add(t);
	}

	FString json;

	FJsonObjectConverter::UStructToJsonObjectString(data, json);

	IPlatformFile& PlatformFile = FPlatformFileManager::Get().GetPlatformFile();

	if (PlatformFile.CreateDirectory(*ProjectDir))
	{
		const FString AbsoluteFilePath = ProjectDir / fileName;
		FPaths::GetProjectFilePath();

		FFileHelper::SaveStringToFile(json, *AbsoluteFilePath);
	}

	return 0;
}

void FrameCountThread::Stop()
{
	bWorking = false;
}

void FrameCountThread::Exit()
{
}

UFrameCount::~UFrameCount()
{
	if (Thread != nullptr)
	{
		Thread->Kill();
		Thread->WaitForCompletion();

		frameCountThread.Reset();
	}
}

UFrameCount* UFrameCount::GetInitFrameCount()
{
	auto obj = NewObject<UFrameCount>();
	obj->frameCountThread = MakeUnique<FrameCountThread>();
	obj->Thread = FRunnableThread::Create(obj->frameCountThread.Get(), TEXT("FrameCount"));

	return obj;
}

	
