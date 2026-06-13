#pragma once
#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "MG_GameState.generated.h"

UENUM(BlueprintType)
enum class EMatchPhase : uint8
{
    Countdown   UMETA(DisplayName = "Countdown"),
    Playing     UMETA(DisplayName = "Playing"),
    Finished    UMETA(DisplayName = "Finished")
};

UCLASS()
class RECOLECTARYENTREGAR_API AMG_GameState : public AGameStateBase
{
    GENERATED_BODY()

public:
    UPROPERTY(Replicated, BlueprintReadOnly)
    float TimeRemaining = 180.f;

    UPROPERTY(Replicated, BlueprintReadOnly)
    int32 GlobalScore = 0;

    UPROPERTY(Replicated, BlueprintReadOnly)
    int32 ScoreTeamRed = 0;

    UPROPERTY(Replicated, BlueprintReadOnly)
    int32 ScoreTeamBlue = 0;

    UPROPERTY(ReplicatedUsing = OnRep_GameActive, BlueprintReadOnly)
    bool bGameActive = false;

    UPROPERTY(Replicated, BlueprintReadOnly)
    EMatchPhase MatchPhase = EMatchPhase::Countdown;

    UPROPERTY(Replicated, BlueprintReadOnly)
    int32 CountdownValue = 0;
    
    UPROPERTY(Replicated, BlueprintReadOnly)
    int32 FruitsTeamRed = 0;

    UPROPERTY(Replicated, BlueprintReadOnly)
    int32 FruitsTeamBlue = 0;

    UFUNCTION()
    void OnRep_GameActive();

    // Setters usados por el GameMode
    void SetMatchPhase(EMatchPhase NewPhase);
    void SetCountdownValue(int32 NewValue);
    void SetMatchTimer(float NewTime);

    virtual void GetLifetimeReplicatedProps(
        TArray<FLifetimeProperty>& OutLifetimeProps
    ) const override;
};