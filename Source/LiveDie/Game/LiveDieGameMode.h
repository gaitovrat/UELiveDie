// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LiveDieGameMode.generated.h"

/**
 *
 */
UCLASS()
class LIVEDIE_API ALiveDieGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ALiveDieGameMode();

	UFUNCTION(BlueprintCallable)
	void RestartLevel();
};
