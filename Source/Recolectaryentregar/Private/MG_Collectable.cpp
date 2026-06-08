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
}

void AMG_Collectable::GetLifetimeReplicatedProps(
	TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AMG_Collectable, bIsPickedUp);
	DOREPLIFETIME(AMG_Collectable, PointValue);
}

void AMG_Collectable::OnRep_IsPickedUp()
{
	// Mostrar u ocultar el objeto en todos los clientes
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
		OnRep_IsPickedUp(); // Llamar manualmente en servidor

		// Timer para reaparecer
		GetWorldTimerManager().SetTimer(
			RespawnTimerHandle, this,
			&AMG_Collectable::Respawn,
			RespawnTime, false
		);
	}
}

void AMG_Collectable::Respawn()
{
	if (HasAuthority())
	{
		bIsPickedUp = false;
		OnRep_IsPickedUp();
	}
}