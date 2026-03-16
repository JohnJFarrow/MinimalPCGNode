
#include "PCGMinimalTestElement.h"
#include "PCGContext.h"
#include "PCGPin.h"
#include "Data/PCGBasePointData.h"

#define LOCTEXT_NAMESPACE "PCGUnrealCode"

namespace
{
	const FName NodeName("MinimalTestNode");
	const FText NodeTitle = FText::Format(LOCTEXT("NodeTitle", "PCG Unrealcode | {0}"), FText::FromName(NodeName));
	const FText Tooltip = LOCTEXT("Tooltip", "Copies input to output");
}

#if WITH_EDITOR
FName UPCGMinimalTestElementSettings::GetDefaultNodeName() const
{
	return NodeName;
}

FText UPCGMinimalTestElementSettings::GetDefaultNodeTitle() const
{
	return NodeTitle;
}

FText UPCGMinimalTestElementSettings::GetNodeTooltipText() const
{
	return Tooltip;
}

EPCGSettingsType UPCGMinimalTestElementSettings::GetType() const
{
	return EPCGSettingsType::Spatial;
}

bool UPCGMinimalTestElementSettings::HasDynamicPins() const
{
	return true;
}


#endif


FPCGDataTypeIdentifier UPCGMinimalTestElementSettings::GetCurrentPinTypesID(const UPCGPin* InPin) const
{
	// Returns the current pin types, which can either be the static types from the pin properties, or a dynamic type based on connected edges.
	// By default we set output pin types to the union of the default input pin incident edge types, if it is dynamic and the default input exists.

	const FName PinName = InPin->GetFName();

	// In/Out = Spline Data
	if (PinName == PCGPinConstants::DefaultInputLabel)
	{
		return EPCGDataType::Spatial;
	}

	return Super::GetCurrentPinTypesID(InPin);
}


TArray<FPCGPinProperties> UPCGMinimalTestElementSettings::InputPinProperties() const
{
	// Init pins - increase the number to add more pins
	TArray<FPCGPinProperties> PinProperties;

	constexpr bool bAllowMultipleConnections = false;
	constexpr bool bAllowMultipleData = false;

	// Pin default ctor is no exported
	FPCGPinProperties& Pin = PinProperties.Emplace_GetRef(PCGPinConstants::DefaultInputLabel, FPCGDataTypeInfoSpatial::AsId(), bAllowMultipleConnections, bAllowMultipleData);
	Pin.Usage = EPCGPinUsage::Normal;

	return PinProperties;
}


TArray<FPCGPinProperties> UPCGMinimalTestElementSettings::OutputPinProperties() const
{
	// See InputPinProperties as it's essentially the same, but for output pins

	TArray<FPCGPinProperties> PinProperties;

	FPCGPinProperties& Pin = PinProperties.Emplace_GetRef(PCGPinConstants::DefaultOutputLabel, FPCGDataTypeInfo::AsId());

	Pin.Usage = EPCGPinUsage::Normal;
	Pin.AllowedTypes = EPCGDataType::Spatial;
	Pin.bAllowMultipleData = true;

	return PinProperties;
}


FPCGElementPtr UPCGMinimalTestElementSettings::CreateElement() const
{
	// Return your class which is the actual node behaviour
	// Use MakeShared<T> for this
	return MakeShared<FPCGMinimalTestElement>();
}
// End UPCGSettings interface

// Begin IPCGElement interface
bool FPCGMinimalTestElement::ExecuteInternal(FPCGContext* Context) const
{
	// Example implementation
	// This is the behaviour of your node
	// You can grab data from your pins and your settings directly from the Context arg

	// Add some basic profiler support
	TRACE_CPUPROFILER_EVENT_SCOPE(FPCGMinimalTestElement::Execute);

	// Double check settings
	check(Context != nullptr);

	// Resolve settings
	const UPCGMinimalTestElementSettings* const Settings = Context->GetInputSettings<UPCGMinimalTestElementSettings>();
	check(Settings != nullptr);

	// Get input pin with the default label
	TArray<FPCGTaggedData> Sources = Context->InputData.GetInputsByPin(PCGPinConstants::DefaultInputLabel);

	// No data, so early out
	if (Sources.Num() == 0)
	{
		return true;
	}

	// Example - will just spit out the data coming in
	// You would add your own outputs here
	Context->OutputData.TaggedData.Append(Sources);

	return true;
}
// End IPCGElement interface

#undef LOCTEXT_NAMESPACE
