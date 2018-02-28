// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "Gameframework/actor.h"
#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetTotalMassonPlate() > TriggerMass)
	{
		OnOpen.Broadcast();
	}

	else
	{
		OnClose.Broadcast();
	}	
}

float UOpenDoor::GetTotalMassonPlate()
{
	float TotalMass = 0;

	TArray<AActor*> OverlapingActors;
	PresurePlate->GetOverlappingActors(OverlapingActors);

	for (const auto* Actor: OverlapingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("%s on PreassurePLate"),*Actor->GetName())
	}

	return TotalMass;
}
