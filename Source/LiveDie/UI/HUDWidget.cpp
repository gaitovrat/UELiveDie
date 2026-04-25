// Fill out your copyright notice in the Description page of Project Settings.

#include "HUDWidget.h"

#include "../Components/HealthComponent.h"

void UHUDWidget::BindToCharacter(ALiveDieCharacter *Character)
{
	if (!Character)
		return;

	BoundCharacter = Character;

	UHealthComponent *Component = Character->FindComponentByClass<UHealthComponent>();
	if (!Component)
		return;

	Component->OnHealthChanged.AddDynamic(this, &ThisClass::HandleHealthChanged);

	if (ProgressBar)
	{
		ProgressBar->SetPercent(Component->GetHealthPercent());
	}
}

void UHUDWidget::HandleHealthChanged(const float NewHealth, const float MaxHealth)
{
	if (!ProgressBar)
		return;

	const float Percent = MaxHealth > 0.f ? NewHealth / MaxHealth : 0.f;
	ProgressBar->SetPercent(Percent);
}
