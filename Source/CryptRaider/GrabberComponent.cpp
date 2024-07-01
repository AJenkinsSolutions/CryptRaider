// Fill out your copyright notice in the Description page of Project Settings.


#include "GrabberComponent.h"

#include "DrawDebugHelpers.h"

#include "PhysicsEngine/PhysicsHandleComponent.h"

// Sets default values for this component's properties
UGrabberComponent::UGrabberComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabberComponent::BeginPlay()
{
	Super::BeginPlay();

	UPhysicsHandleComponent* PhysicsHandlerComp = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if(PhysicsHandlerComp != nullptr){

		FString ownerName = PhysicsHandlerComp->GetName();

		UE_LOG(LogTemp, Log, TEXT("Got physics handler %s"), *ownerName);

	}else{
		UE_LOG(LogTemp, Warning, TEXT("No Phyics handler found"));
	}
	// ...
	
}


// Called every frame
void UGrabberComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	FRotator GrabberRotation = GetComponentRotation();
	FString RotationString = GrabberRotation.ToCompactString();

	// UE_LOG(LogTemp, Log, TEXT("Grabber Rotation: %s"), *RotationString);

	// UWorld*	world = GetWorld();

	// double timeElapsed = world->GetTimeSeconds();

	// UE_LOG(LogTemp, Log, TEXT("Time Elasped: %f "), timeElapsed);

	
	// float Damage = 0; 
	//Setting up reference to the damage variable
	// float& DamageRef = Damage;
	//can be used jsut like a reglar variable
	// UE_LOG(LogTemp, Display, TEXT("Damage %f"), DamageRef);


}

void UGrabberComponent::Release(){

	UE_LOG(LogTemp, Log, TEXT("Entered into Release Function in C++"));
}

void UGrabberComponent::Grab(){

	FVector StartLocation = GetComponentLocation() + GetForwardVector();
	FVector Direction = GetForwardVector();

	FVector EndLocation = (StartLocation + Direction) * MaxGrabDistance; 
	
	int32 segments = 12;
	
	DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red );
	DrawDebugSphere(GetWorld(), StartLocation, SphereRadius, segments, FColor::Blue);
	 

	FCollisionShape CollisionSphere = FCollisionShape::MakeSphere(SphereRadius);
	FHitResult HitResult;
	bool HasHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		FQuat::Identity,
		ECC_GameTraceChannel2,
		CollisionSphere
	);

	if(HasHit){

		AActor* HitActor = HitResult.GetActor();
		// FString ActorName = Actor->GetActorNameOrLabel();
		UE_LOG(LogTemp, Log, TEXT("Hit Actor: %s"), *HitActor->GetActorNameOrLabel());


	}else{
		UE_LOG(LogTemp, Display, TEXT("No Actor Hit"));
	}



}


