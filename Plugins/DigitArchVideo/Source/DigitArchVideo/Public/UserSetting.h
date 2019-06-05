// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UserSetting.generated.h"

/**
 * 
 */
UCLASS()
class DIGITARCHVIDEO_API UUserSetting : public UObject
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, meta=(DefaultToSelf = "obj", HidePin="obj"))
		static void SetPlayerName(FString name, UObject* obj);
	
};
