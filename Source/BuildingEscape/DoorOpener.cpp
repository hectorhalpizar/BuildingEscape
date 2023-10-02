// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "DoorOpener.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UDoorOpener::UDoorOpener()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDoorOpener::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();

	FString ObjectName = GetOwner()->GetName();

	if (ActorThatOpens == NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("ActorThatOpens is NULL on %s"), *ObjectName);
	}
	
	if (PressurePlate == NULL)
	{
		UE_LOG(LogTemp, Warning, TEXT("PressurePlate is NULL on %s"), *ObjectName);
	}

	// ...
	
}

void UDoorOpener::OpenDoor()
{
	Owner->SetActorRotation(FRotator(0.f, OpenAngle, 0.f));
}

void UDoorOpener::CloseDoor()
{
	Owner->SetActorRotation(FRotator(0.f, -180.f, 0.f));
}

// Called every frame
void UDoorOpener::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Pool the Trigger Volume
	if (ActorThatOpens != NULL 
	&& PressurePlate != NULL 
	&& PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		// If the ActorThatOpens is in the volume
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}

	// Check if it's time to close the door
	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay)
	{
		CloseDoor();
	}
}

