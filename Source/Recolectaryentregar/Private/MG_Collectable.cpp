#include "MG_Collectable.h"
#include "Components/SphereComponent.h"
#include "Net/UnrealNetwork.h"

AMG_Collectable::AMG_Collectable()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	RootComponent = CollisionSphere;
	CollisionSphere->SetSphereRadius(50.f);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
}

void AMG_Collectable::BeginPlay()
{
	Super::BeginPlay();

	// Asignar puntos según tipo
	switch (FruitType)
	{
	case EFruitType::Banana:   PointValue = 1; break;
	case EFruitType::Apple:  PointValue = 2; break;
	case EFruitType::Strawberry: PointValue = 3; break;
	}
}

void AMG_Collectable::GetLifetimeReplicatedProps(
	TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AMG_Collectable, bIsPickedUp);
	DOREPLIFETIME(AMG_Collectable, PointValue);
	DOREPLIFETIME(AMG_Collectable, FruitType);
}

void AMG_Collectable::OnRep_IsPickedUp()
{
	Mesh->SetVisibility(!bIsPickedUp);
	CollisionSphere->SetCollisionEnabled(
		bIsPickedUp ? ECollisionEnabled::NoCollision
					: ECollisionEnabled::QueryOnly
	);
}

void AMG_Collectable::PickUp()
{
    if (HasAuthority() && !bIsPickedUp)
    {
        bIsPickedUp = true;
        CollisionSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision); // ← agregar esto
        OnRep_IsPickedUp();
        SelfDestroy();
    }
}

void AMG_Collectable::SelfDestroy()
{
	if (HasAuthority())
	{
		Destroy();
	}
}