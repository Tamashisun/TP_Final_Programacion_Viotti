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
    UPROPERTY(ReplicatedUsing = OnRep_GameActive, BlueprintReadOnly)
    bool bGameActive = false;

    UPROPERTY(Replicated, BlueprintReadOnly)
    float TimeRemaining = 180.f;

    UPROPERTY(Replicated, BlueprintReadOnly)
    int32 GlobalScore = 0;

    UPROPERTY(Replicated, BlueprintReadOnly)
    int32 ScoreTeamRed = 0;

    UPROPERTY(Replicated, BlueprintReadOnly)
    int32 ScoreTeamBlue = 0;

    UPROPERTY(ReplicatedUsing = OnRep_MatchPhase, BlueprintReadOnly)
    EMatchPhase MatchPhase = EMatchPhase::Countdown;

    UPROPERTY(Replicated, BlueprintReadOnly)
    int32 CountdownValue = 3;

    UFUNCTION()
    void OnRep_GameActive();

    UFUNCTION()
    void OnRep_MatchPhase();

    void SetMatchPhase(EMatchPhase NewPhase);
    void SetCountdownValue(int32 Value);
    void SetMatchTimer(float Value);

    virtual void GetLifetimeReplicatedProps(
        TArray<FLifetimeProperty>& OutLifetimeProps
    ) const override;
};