#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "MG_Character.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS()
class RECOLECTARYENTREGAR_API AMG_Character : public ACharacter
{
    GENERATED_BODY()

public:
    AMG_Character();

    virtual void BeginPlay() override;
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
    virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

    // ── Input Assets (asignar en Blueprint) ──────────────────────────
    UPROPERTY(EditDefaultsOnly, Category = "Input")
    UInputMappingContext* DefaultMappingContext;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    UInputAction* MoveAction;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    UInputAction* LookAction;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    UInputAction* JumpAction;

    // ── Replicación ───────────────────────────────────────────────────
    UPROPERTY(ReplicatedUsing = OnRep_IsCarrying, BlueprintReadOnly)
    bool bIsCarrying = false;

    // La fruta que está cargando actualmente
    UPROPERTY(Replicated, BlueprintReadOnly)
    int32 CarriedPointValue = 0;
    
    UFUNCTION()
    void OnRep_IsCarrying();

    // ── RPCs ──────────────────────────────────────────────────────────
    UFUNCTION(Server, Reliable, WithValidation)
    void Server_PickupObject();

    UFUNCTION(Server, Reliable, WithValidation)
    void Server_DeliverObject();

    UFUNCTION(NetMulticast, Reliable)
    void Multicast_PlayPickupEffect();

    // ── Overlap ───────────────────────────────────────────────────────
    UFUNCTION()
    void OnOverlapBegin(
        UPrimitiveComponent* OverlappedComp,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult
    );

private:
    // ── Input Handlers ────────────────────────────────────────────────
    void DoMove(const FInputActionValue& Value);
    void DoLook(const FInputActionValue& Value);
    void DoJumpStart();
    void DoJumpEnd();
};