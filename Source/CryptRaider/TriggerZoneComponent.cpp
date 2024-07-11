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

    
    AActor* ActorInZone = ConfirmActorAcceptableTag();
    
    if(ActorInZone != nullptr){

        AttachActorToComponent(ActorInZone);

        //Move Door
        Mover->SetShouldMove(true);

    
    }else{
        UE_LOG(LogTemp, Log, TEXT("Relocking "));

        Mover->SetShouldMove(false);
    }
}

void UTriggerZoneComponent::AttachActorToComponent(AActor *ActorInZone)
{
    // Casting
    UPrimitiveComponent *ActorInZoneComponent = Cast<UPrimitiveComponent>(ActorInZone->GetRootComponent());

    if (ActorInZoneComponent != nullptr)
    {
        USceneComponent *ComponentToAttachTo = GetOwner()->GetRootComponent();

        ActorInZone->AttachToComponent(ComponentToAttachTo, FAttachmentTransformRules::KeepWorldTransform);
        ActorInZoneComponent->SetSimulatePhysics(false);
    }

    // UE_LOG(LogTemp, Log, TEXT("Unlocking: Acceptable Actor in zone %s"), *ActorInZone->GetActorNameOrLabel());

   
}

void UTriggerZoneComponent::SetMover(UMover* NewMover)
{
    Mover = NewMover;
}


AActor* UTriggerZoneComponent::ConfirmActorAcceptableTag() const {

    AActor* ReturnActor = nullptr;

    TArray<AActor*> Actors;
    GetOverlappingActors(Actors);

    for(AActor* Actor: Actors){

    //      UE_LOG(LogTemp, Log, TEXT("Overlapping Actor %s"), *Actor->GetActorNameOrLabel());
        if(Actor->ActorHasTag(AcceptableTag) && !Actor->ActorHasTag("Grabbed")){
            
            return Actor;
        }

    }

    return ReturnActor;


}