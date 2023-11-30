// Fill out your copyright notice in the Description page of Project Settings.


#include "CDPlatformHub.h"

#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

#include "CDPlatform.h"
#include "../Player/CDPaperCharacter.h"
#include "../AI/CDAICharacter.h"

ACDPlatformHub::ACDPlatformHub()
{
	PrimaryActorTick.bCanEverTick = false;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	BoxComponent->SetupAttachment(GetRootComponent());
}

void ACDPlatformHub::BeginPlay()
{
	Super::BeginPlay();

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ACDPlatformHub::OnOverlap);

	PlatformRotation = GetActorRotation();
	PlatformLocation = GetActorLocation();

	SpawnPlatform(0);
}

void ACDPlatformHub::SpawnPlatform(int32 Index)
{
	AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(PlatformPayload[Index].PlatformClass, PlatformLocation, PlatformRotation);
	PlatformArray.Add(SpawnedActor);
	PlatformState = PlatformPayload[Index].PlatformDirection;

	if (PlatformPayload[Index].PlatformDirection != ECDPlatformDirection::None)
		PlatformDirection = PlatformPayload[Index].PlatformDirection;

	FVector Origin;
	FVector BoxExtent;
	SpawnedActor->GetActorBounds(false, Origin, BoxExtent);
	PlatformLocation.Z -= BoxExtent.Z * 2.f;

	BoxComponent->SetBoxExtent(BoxExtent);
	BoxComponent->SetWorldLocation(SpawnedActor->GetActorLocation());
}

void ACDPlatformHub::DeletePlatform(int32 Index)
{
	PlatformArray[Index]->Destroy();
	PlatformArray.RemoveAt(Index);
}

void ACDPlatformHub::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ACDPaperCharacter>(OtherActor))
	{
		int32 Random = 0;

        do
            Random = FMath::RandRange(0, PlatformPayload.Num() - 1);
        while (PlatformPayload[Random].PlatformDirection == PlatformDirection || PlatformPayload[Random].PlatformDirection == PlatformState);

		SpawnPlatform(Random);

		if (PlatformArray.Num() > PlatformCount)
			DeletePlatform(0);

		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Cyan, "Overlap " + OtherComp->GetName());
	}
	else if (Cast<ACDAICharacter>(OtherActor))
	{
		AActor* Player = UGameplayStatics::GetActorOfClass(GetWorld(), APaperCharacter::StaticClass());		
		AActor* AI = UGameplayStatics::GetActorOfClass(GetWorld(), ACDAICharacter::StaticClass());
		AI->SetActorLocation(Player->GetActorLocation());
	}
}

