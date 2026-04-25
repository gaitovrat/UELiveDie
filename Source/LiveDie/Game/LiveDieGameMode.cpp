// Fill out your copyright notice in the Description page of Project Settings.

#include "LiveDieGameMode.h"
#include "../Character/LiveDieCharacter.h"

ALiveDieGameMode::ALiveDieGameMode()
{
	DefaultPawnClass = ALiveDieCharacter::StaticClass();
}
