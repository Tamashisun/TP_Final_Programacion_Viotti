#include "MG_GameState.h"
#include "Net/UnrealNetwork.h"

void AMG_GameState::GetLifetimeReplicatedProps(
    TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);

    DOREPLIFETIME(AMG_GameState, TimeRemaining);
    DOREPLIFETIME(AMG_GameState, GlobalScore);
    DOREPLIFETIME(AMG_GameState, bGameActive);
}

void AMG_GameState::OnRep_GameActive()
{
    UE_LOG(LogTemp, Warning, TEXT("GameActive changed: %s"),
        bGameActive ? TEXT("Active") : TEXT("Inactive"));
}