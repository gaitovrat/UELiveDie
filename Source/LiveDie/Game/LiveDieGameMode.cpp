// Fill out your copyright notice in the Description page of Project Settings.

#include "LiveDieGameMode.h"
#include "../Character/LiveDieCharacter.h"
#include "Kismet/GameplayStatics.h"

ALiveDieGameMode::ALiveDieGameMode()
{
	DefaultPawnClass = ALiveDieCharacter::StaticClass();
}

void ALiveDieGameMode::RestartLevel()
{
	const FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this);
	UGameplayStatics::OpenLevel(this, *CurrentLevelName);
}
