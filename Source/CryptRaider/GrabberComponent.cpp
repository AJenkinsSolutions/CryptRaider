// Fill out your copyright notice in the Description page of Project Settings.


#include "GrabberComponent.h"





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

	//Set Physic Handler location on tick if somethins is grabbed
	if (PhysicsHandler->GetGrabbedComponent() != nullptr)
	{
		FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance;
		PhysicsHandler->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
	}
	
	
	
}

void UGrabberComponent::Release(){

	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandler();

	if(PhysicsHandle == nullptr){
		return;
	}
	UPrimitiveComponent* GrabbedComponent = PhysicsHandle->GetGrabbedComponent();
	if(GrabbedComponent != nullptr){
		
		GrabbedComponent->WakeAllRigidBodies();
		PhysicsHandle->ReleaseComponent();
		GrabbedComponent->GetOwner()->Tags.Remove("Grabbed");

	}


}

void UGrabberComponent::Grab(){


	UPhysicsHandleComponent* PhysicsHandler = GetPhysicsHandler();
	if(PhysicsHandler == nullptr){ 
		return;
	}

	FHitResult OutHitResult;
	bool HasHit = IsGrabberInReach(OutHitResult);

	UPrimitiveComponent* HitComponent = OutHitResult.GetComponent();
	
	FVector HitImpactPoint = OutHitResult.ImpactPoint;


	if(HasHit){
		DrawDebugSphere(GetWorld(), OutHitResult.ImpactPoint, 10, 10, FColor::Blue, false, 3);
		
		
		//Wake Rigid Bodies before connecting Primative Component to Handle
		HitComponent->WakeAllRigidBodies();
		GetOwner()->Tags.Add("Grabbed");

		OutHitResult.GetActor()->Tags.Add("Grabbed");
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


bool UGrabberComponent::IsGrabberInReach(FHitResult &OutHitResult) const
{
	// GEOMATERY SWEEP
	// Vectors - Line
	FVector StartLocation = GetComponentLocation();
	FVector Direction = GetForwardVector();
	FVector EndLocation = StartLocation + (Direction * MaxGrabDistance); 

	//Collison Shape 
	FCollisionShape CollisionSphere = FCollisionShape::MakeSphere(SphereRadius);

	
	bool HasHit = GetWorld()->SweepSingleByChannel(
		OutHitResult,
		StartLocation,
		EndLocation,
		FQuat::Identity,
		ECC_GameTraceChannel2,
		CollisionSphere
	);
	
	return HasHit;
    
}

/**
 * This function will handle the sweeping logic
 * Outputs a HitResult obj 
 * Returns a bool if sweep has hit a grabbable object
*/








