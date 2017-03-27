// Copyright (c) Improbable Worlds Ltd, All Rights Reserved
#pragma once

#include "Improbable/Generated/cpp/unreal/EntityTemplate.h"
#include "SpatialOSGameMode.h"
#include "RpgDemoGameMode.generated.h"

UCLASS(minimalapi)
class ARpgDemoGameMode : public AGameModeBase
{
    GENERATED_BODY()

  public:
    ARpgDemoGameMode();
    virtual ~ARpgDemoGameMode();

	UFUNCTION(BlueprintCallable, Category = "RpgDemoGameMode")
	FString GetSpatialOsWorkerType();

	UFUNCTION(BlueprintImplementableEvent, Category = "RpgDemoGameMode")
	void OnSpatialOsConnected();

	UFUNCTION(BlueprintImplementableEvent, Category = "RpgDemoGameMode")
	void OnSpatialOsDisconnected();

	UFUNCTION(BlueprintImplementableEvent, Category = "RpgDemoGameMode")
	void OnSpatialOsFailedToConnect();

    UFUNCTION(BlueprintPure, Category = "RpgDemoGameMode")
    UEntityTemplate* CreatePlayerEntityTemplate(FString clientWorkerId, const FVector& position);

    // clang-format off
    DECLARE_DYNAMIC_DELEGATE_ThreeParams(FGetSpawnerEntityIdResultDelegate, bool, success, FString, errorMessage, int, spawnerEntityId);
    // clang-format on    
    UFUNCTION(BlueprintCallable, Category = "RpgDemoGameMode")
    void GetSpawnerEntityId(const FGetSpawnerEntityIdResultDelegate& callback, int timeoutMs);

	void StartPlay() override;

	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintPure, Category = "RpgDemoGameMode")
	static bool IsConnectedToSpatialOs();

	UFUNCTION(BlueprintPure, Category = "RpgDemoGameMode")
	UCommander* SendWorkerCommand();

	UPROPERTY(BluePrintReadWrite, EditDefaultsOnly, NoClear)
	FString WorkerTypeOverride;

	UPROPERTY(BluePrintReadWrite, EditDefaultsOnly, NoClear)
	FString WorkerIdOverride;

  private:
    DECLARE_DELEGATE(FUnbindDelegate);

	UPROPERTY()
	UCommander* Commander;

    FGetSpawnerEntityIdResultDelegate* mGetSpawnerEntityIdResultCallback;

    FUnbindDelegate UnbindEntityQueryDelegate;
    void UnbindEntityQueryCallback();
    std::uint64_t entityQueryCallback;
};
