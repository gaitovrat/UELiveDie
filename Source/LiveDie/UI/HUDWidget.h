// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "../Character/LiveDieCharacter.h"
#include "HUDWidget.generated.h"

/**
 *
 */
UCLASS()
class LIVEDIE_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	UProgressBar *ProgressBar;

	UFUNCTION(BlueprintCallable)
	void BindToCharacter(ALiveDieCharacter *Character);

	UFUNCTION()
	void HandleHealthChanged(float NewHealth, float MaxHealth);

private:
	TWeakObjectPtr<ALiveDieCharacter> BoundCharacter;
};
