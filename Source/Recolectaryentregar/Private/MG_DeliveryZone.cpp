#include "MG_DeliveryZone.h"
#include "Components/BoxComponent.h"
#include "Net/UnrealNetwork.h"
#include "MG_Character.h"
#include "MG_PlayerState.h"
#include "MG_GameState.h"

AMG_DeliveryZone::AMG_DeliveryZone()
{
    PrimaryActorTick.bCanEverTick = false;
    bReplicates = true;

    DeliveryBox = CreateDefaultSubobject<UBoxComponent>(TEXT("DeliveryBox"));
    RootComponent = DeliveryBox;
    DeliveryBox->SetBoxExtent(FVector(100.f, 100.f, 50.f));

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    Mesh->SetupAttachment(RootComponent);
}

void AMG_DeliveryZone::BeginPlay()
{
    Super::BeginPlay();

    if (HasAuthority())
    {
        DeliveryBox->OnComponentBeginOverlap.AddDynamic(
            this, &AMG_DeliveryZone::OnOverlapBegin
        );
    }
}

void AMG_DeliveryZone::GetLifetimeReplicatedProps(
    TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AMG_DeliveryZone, TeamID);
}

void AMG_DeliveryZone::OnOverlapBegin(
    UPrimitiveComponent* OverlappedComp,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult)
{
    if (!HasAuthority()) return;

    AMG_Character* Character = Cast<AMG_Character>(OtherActor);
    if (!Character) return;

    // Verificar que el jugador lleva un objeto
    if (!Character->bIsCarrying) return;

    // Verificar que el jugador es del mismo equipo
    AMG_PlayerState* PS = Character->GetPlayerState<AMG_PlayerState>();
    if (!PS || PS->TeamID != TeamID) return;

    // Entregar objeto
    Character->Server_DeliverObject();

    // Sumar puntaje al GameState
    AMG_GameState* GS = GetWorld()->GetGameState<AMG_GameState>();
    if (GS)
    {
        GS->GlobalScore += 1;
        PS->IndividualScore += 1;
    }
}