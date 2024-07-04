// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerZoneComponent.h"

void UTriggerZoneComponent::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Display, TEXT("Box Component Works"));
}
