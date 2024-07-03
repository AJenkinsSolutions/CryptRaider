// Fill out your copyright notice in the Description page of Project Settings.


#include "GrabberComponent.h"

#include "DrawDebugHelpers.h"



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
	
}


// Called every frame
void UGrabberComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UPhysicsHandleComponent* PhysicsHandler = GetPhysicsHandler();
	if(PhysicsHandler == nullptr){
		return;
	}

	//Set Physic Handler location on tick
	FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
	PhysicsHandler->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
	
}

void UGrabberComponent::Release(){

	

	if(GetPhysicsHandler() == nullptr){
		return;
	}

	if(GetPhysicsHandler()->GetGrabbedComponent()){
		GetPhysicsHandler()->ReleaseComponent();
	}


}

void UGrabberComponent::Grab(){


	UPhysicsHandleComponent* PhysicsHandler = GetPhysicsHandler();
	if(PhysicsHandler == nullptr){ 
		return;
	}


	// GEOMATERY SWEEP
	// Vectors - Line
	FVector StartLocation = GetComponentLocation();
	FVector Direction = GetForwardVector();
	FVector EndLocation = StartLocation + (Direction * MaxGrabDistance); 

	//Collison Shape 
	FCollisionShape CollisionSphere = FCollisionShape::MakeSphere(SphereRadius);
	
	//Out Result
	FHitResult HitResult;
	bool HasHit = GetWorld()->SweepSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		FQuat::Identity,
		ECC_GameTraceChannel2,
		CollisionSphere
	);
	// HitResult Variables
	UPrimitiveComponent* HitComponent = HitResult.GetComponent();
	FVector HitImpactPoint = HitResult.ImpactPoint;


	if(HasHit){
		DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10, 10, FColor::Blue, false, 3);
		// UE_LOG(LogTemp, Log, TEXT("Hit Actor: %s"), HitResult.GetActor()->GetActorNameOrLabel());
		
		//Wake Rigid Bodies before connecting Primative Component to Handle
		HitComponent->WakeAllRigidBodies();
		//Handle Physics
		PhysicsHandler->GrabComponentAtLocationWithRotation(
			HitComponent,
			NAME_None,
			HitImpactPoint,
			GetComponentRotation()
			);
		

	}else{
		UE_LOG(LogTemp, Display, TEXT("No Hit"));
	}

	
	
}
//const means it doesnt change anything in our grabber
UPhysicsHandleComponent* UGrabberComponent::GetPhysicsHandler() const{


	UPhysicsHandleComponent* result = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if(result == nullptr){
		
		UE_LOG(LogTemp, Error, TEXT("No Grabber requires a UPhysicsHandler"));

	}

	//UE_LOG(LogTemp, Display, TEXT("PhysicsHandle Name %s"), *result->GetName());\

	return result;
	
}





