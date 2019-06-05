// Fill out your copyright notice in the Description page of Project Settings.

#include "UserSetting.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerState.h"

void UUserSetting::SetPlayerName(FString name, UObject* obj)
{
	obj->GetWorld()->GetFirstPlayerController()->PlayerState->SetPlayerName(name);
}
