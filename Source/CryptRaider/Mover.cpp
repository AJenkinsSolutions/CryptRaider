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
	
	FVector target = StartLocation;
	if(ShouldMove){

		target = StartLocation + MoveOffSet;
		
	}

	FVector Current = GetOwner()->GetActorLocation();
	
	float speed = MoveOffSet.Length() / MoveTime;
	FVector NewLocation = FMath::VInterpConstantTo(Current, target, DeltaTime, speed);

	GetOwner()->SetActorLocation(NewLocation);

	UE_LOG(LogTemp, Log, TEXT("In should move"));
	
	
}

void UMover::SetShouldMove(bool AllowMovement){
	//Why isnt the mover moving
	//We use the movers own method to turn on the private var 
	ShouldMove = AllowMovement;
}

void UMover::ReverseDirection()
{
	MoveOffSet = (MoveOffSet * -1);
}
