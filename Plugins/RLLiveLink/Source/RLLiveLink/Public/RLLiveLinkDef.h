// Copyright 2022 The Reallusion Authors. All Rights Reserved.

#pragma once
#include "RLLiveLinkStringTable.h"
#include "Widgets/Notifications/INotificationWidget.h"

enum class ELightType : int
{
    Directional = 0,
    Point,
    Spot,
    Rect
};

enum class ELightColor : int
{
    Red = 0,
    Green,
    Blue
};

enum class ETransferMode : int
{
    Merge,
    Simplify,
    BatchMerge,
    BatchSimplify,
    Batch
};

struct FMergeComponentData
{
    FMergeComponentData( UPrimitiveComponent* InPrimComponent )
        : PrimComponent( InPrimComponent )
        , bShouldIncorporate( true )
    {
    }

    /** Component extracted from selected actors */
    TWeakObjectPtr<UPrimitiveComponent> PrimComponent;
    /** Flag determining whether or not this component should be incorporated into the merge */
    bool bShouldIncorporate;
};

struct ExportFbxSetting
{
    UObject* pObjectToExport;
    FString strSaveFilePath;
};

class CSceneTempData
{
public:
    FString strAssetName;
    FTransform kTransform;
    AActor* pParentActor;
    FString strFolderName;
    bool bPilotTarget;
};

struct CCreateRLLevelSequencerData
{
    FString strAssetName;
    FString strMotionName;
    FString GetMotionGamePath() const
    {
        return "/Game/RLContent/" + strAssetName + "/Motion/" + strMotionName + "." + strMotionName;
    };
};

struct CSwitchCameraData
{
    FString strCameraName;
    int nSwitchFrame;
};

class FLiveLinkNotificationWidgetProvider : public INotificationWidget
{
public:
    FLiveLinkNotificationWidgetProvider( TSharedRef<SWidget> WidgetToDisplay ) : kNotificationWidget( WidgetToDisplay ) {}

    virtual ~FLiveLinkNotificationWidgetProvider() {}

    virtual void OnSetCompletionState( SNotificationItem::ECompletionState State ) override {}
    virtual TSharedRef<SWidget> AsWidget() override { return kNotificationWidget; }

private:
    TSharedRef<SWidget> kNotificationWidget;
};

static const TMap< FName, FString > s_kUEToICCameraPropertyNameMap =
{
    // SetFocalLength
    { IC_CURRENT_FOCAL_LENGTH, UE_CURRENT_FOCAL_LENGTH },

    // -PostProcess
    { IC_FOCAL_REIGON,            UE_FOCAL_REIGON           },
    { IC_NEAR_TRANSITION_REGION,  UE_NEAR_TRANSITION_REGION },
    { IC_FAR_TRANSITION_REGION,   UE_FAR_TRANSITION_REGION  },
    { IC_NEAR_BLUR,               UE_NEAR_BLUR              },
    { IC_FAR_BLUR,                UE_FAR_BLUR               },
    // -CameraFlimbackSettings
    { IC_SENSOR_WIDTH,             UE_SENSOR_WIDTH          },
    { IC_SENSOR_HEIGHT,            UE_SENSOR_HEIGHT         },

    // -CameraFocusSetting
    { IC_FOCUS_DISTANCE,          UE_FOCUS_DISTANCE         },
    { IC_FOCUS_OFFSET,            UE_FOCUS_OFFSET           },
};

static const TMap< FName, FString > s_kUEPropertyNameAndPathMap =
{
    // -PostProcess
    { UE_FOCAL_REIGON,            UE_FOCAL_REIGON_PATH           },
    { UE_NEAR_TRANSITION_REGION,  UE_NEAR_TRANSITION_REGION_PATH },
    { UE_FAR_TRANSITION_REGION,   UE_FAR_TRANSITION_REGION_PATH  },
    { UE_NEAR_BLUR,               UE_NEAR_BLUR_PATH              } ,
    { UE_FAR_BLUR,                UE_FAR_BLUR_PATH               },
    // -CameraFlimbackSettings
    { UE_SENSOR_WIDTH,            UE_SENSOR_WIDTH_PATH           },
    { UE_SENSOR_HEIGHT,           UE_SENSOR_HEIGHT_PATH          },

    // -CameraFocusSetting
    { UE_FOCUS_DISTANCE,          UE_FOCUS_DISTANCE_PATH         },
    { UE_FOCUS_OFFSET,            UE_FOCUS_OFFSET_PATH           },
};
