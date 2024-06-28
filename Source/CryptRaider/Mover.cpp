// Fill out your copyright notice in the Description page of Project Settings.


 #include "Mover.h"
 #include "Math/UnrealMathUtility.h"


// Sets default values for this component's properties
UMover::UMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMover::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetOwner()->GetActorLocation();
	
	// ...
	
}


// Called every frame
void UMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// AActor* Owner = GetOwner();


	// FVector OwnerLocation = Owner->GetActorLocation();

	// FString OwnerLocationString = OwnerLocation.ToCompactString();


	// UE_LOG(LogTemp, Log, TEXT("Owner Location: %sOwnerLocationString"), *OwnerLocationString);
	if(ShouldMove){

		FVector Current = GetOwner()->GetActorLocation();
		FVector target = StartLocation + MoveOffSet;
		float speed = FVector::Distance(StartLocation, target) / MoveTime;

		FVector NewLocation = FMath::VInterpConstantTo(Current, target, DeltaTime, speed);

		GetOwner()->SetActorLocation(NewLocation);


	}
	
	// the memory address we want
	//float MyFloat = 5; 
	// the pointer to that memory address
	//float* YourFloat = &MyFloat;
	// * before the pointer 'dereferecing operator' gives us access to the value
	//UE_LOG(LogTemp, Log, TEXT("YourFloat: %f"), *YourFloat);

	//UE_LOG(LogTemp, Log, TEXT("Your message: %uOwner"), Owner);

	
	//UE_LOG(LogTemp, Display, TEXT("DEBUG MESSAGE"));
	// ...
}

