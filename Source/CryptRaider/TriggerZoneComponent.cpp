// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerZoneComponent.h"

UTriggerZoneComponent::UTriggerZoneComponent()
{

    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

    UE_LOG(LogTemp, Log, TEXT("Trigger Zone constructor"));
}



void UTriggerZoneComponent::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Display, TEXT("Box Component Works"));
}


void UTriggerZoneComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}