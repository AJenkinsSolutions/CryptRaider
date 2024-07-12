// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Mover.h"
// #include <string>
#include "TriggerZoneComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CRYPTRAIDER_API UTriggerZoneComponent : public UBoxComponent
{
	GENERATED_BODY()

public:
	UTriggerZoneComponent();

protected: 
	virtual void BeginPlay() override;

public:	
	// Called every frame
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

    void AttachActorToComponent(AActor *ActorInZone);

    UFUNCTION(BlueprintCallable)
    void SetMover(UMover *Mover);

private:
    
    // string AcceptableTag = "Unlock1";

    UPROPERTY(EditAnywhere)
    UMover *Mover;

    AActor* ConfirmActorAcceptableTag() const;
	
};
