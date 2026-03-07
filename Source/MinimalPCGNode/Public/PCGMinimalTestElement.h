#pragma once

#include "PCGSettings.h"

#include "PCGMinimalTestElement.generated.h"

UCLASS(BlueprintType, ClassGroup = (Procedural), Category = "Unrealcode | Test Nodes")
class MINIMALPCGNODE_API UPCGMinimalTestElement : public UPCGSettings
{
	GENERATED_BODY()

public:
	// Begin UPCGSettings interface
public:
	#if WITH_EDITOR
	virtual FName GetDefaultNodeName() const override;
	virtual FText GetDefaultNodeTitle() const override;
	virtual FText GetNodeTooltipText() const override;
	virtual EPCGSettingsType GetType() const override;
	#endif
	virtual bool HasDynamicPins() const override;
	virtual FPCGDataTypeIdentifier GetCurrentPinTypesID(const UPCGPin* InPin) const override;
protected:
	virtual TArray<FPCGPinProperties> InputPinProperties() const override;
	virtual TArray<FPCGPinProperties> OutputPinProperties() const override;
	virtual FPCGElementPtr CreateElement() const override;
	// End UPCGSettings interface

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Settings", meta = (PCG_Overridable))
	bool bExampleSetting = false;
};

class MINIMALPCGNODE_API FPCGMinimalTestElement : public IPCGElement
{
protected:
	// Begin IPCGElement interface
	virtual bool ExecuteInternal(FPCGContext* Context) const override;
	// End IPCGElement interface
};