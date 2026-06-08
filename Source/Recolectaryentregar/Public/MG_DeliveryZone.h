#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MG_DeliveryZone.generated.h"

UCLASS()
class RECOLECTARYENTREGAR_API AMG_DeliveryZone : public AActor
{
    GENERATED_BODY()

public:
    AMG_DeliveryZone();

    virtual void BeginPlay() override;

    // Zona de colision
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    class UBoxComponent* DeliveryBox;

    // Mesh visual del granero
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    UStaticMeshComponent* Mesh;

    // A qué equipo pertenece esta zona (0 = rojo, 1 = azul)
    UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Replicated)
    int32 TeamID = 0;

    // Detectar cuando el jugador entra
    UFUNCTION()
    void OnOverlapBegin(
        UPrimitiveComponent* OverlappedComp,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult
    );

    virtual void GetLifetimeReplicatedProps(
        TArray<FLifetimeProperty>& OutLifetimeProps
    ) const override;
};