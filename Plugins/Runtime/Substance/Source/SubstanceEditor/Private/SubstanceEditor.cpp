// Copyright 2018 Allegorithmic Inc. All rights reserved.
// File: SubstanceEditor.cpp

#include "SubstanceEditor.h"
#include "SubstanceEditorPrivatePCH.h"
#include "SubstanceEditorModule.h"
#include "SSubstanceEditorPanel.h"

#include "ScopedTransaction.h"
#include "Factories.h"

#include "Widgets/Colors/SColorPicker.h"
#include "Widgets/Docking/SDockTab.h"
#include "Interfaces/IMainFrameModule.h"
#include "DesktopPlatformModule.h"
#include "Toolkits/IToolkitHost.h"
#include "WorkspaceMenuStructure.h"

#include "Runtime/Slate/Public/Framework/MultiBox/MultiBoxBuilder.h"

#include "Editor/WorkspaceMenuStructure/Public/WorkspaceMenuStructureModule.h"
#include "Editor/PropertyEditor/Public/PropertyEditorModule.h"
#include "Editor/PropertyEditor/Public/IDetailsView.h"

#define LOCTEXT_NAMESPACE "SubstanceEditor"

const FName FSubstanceEditor::SubstanceTabId(TEXT("SubstanceEditor_GraphView"));

/** Substance Editor Commands*/
class FSubstanceEditorCommands : public TCommands<FSubstanceEditorCommands>
{
public:

	/** Constructor */
	FSubstanceEditorCommands()
		: TCommands<FSubstanceEditorCommands>(
		      "SubstanceEditor",
		      NSLOCTEXT("Contexts", "SubstanceEditor", "Substance Graph Instance Editor"),
		      NAME_None,
		      FEditorStyle::GetStyleSetName()) // Icon Style Set
	{
	}

	/** Export graph instance values to a sbsprs file */
	TSharedPtr<FUICommandInfo> ExportPreset;

	/** Import graph instance values from a sbsprs file */
	TSharedPtr<FUICommandInfo> ImportPreset;

	/** Reset graph instance values to default */
	TSharedPtr<FUICommandInfo> ResetDefaultValues;

	/** Initialize commands */
	virtual void RegisterCommands() override;
};

void FSubstanceEditorCommands::RegisterCommands()
{
	UI_COMMAND(ExportPreset, "Export preset", "Export graph instance values to a substance preset file (.sbsprs).", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(ImportPreset, "Import preset", "Import graph instance values from a substance preset file (.sbsprs).", EUserInterfaceActionType::Button, FInputChord());
	UI_COMMAND(ResetDefaultValues, "Reset", "Reset graph instance values to default.", EUserInterfaceActionType::Button, FInputChord());
}

void FSubstanceEditor::RegisterTabSpawners(const TSharedRef<class FTabManager>& TM)
{
	FAssetEditorToolkit::RegisterTabSpawners(TM);

	const IWorkspaceMenuStructure& MenuStructure = WorkspaceMenu::GetMenuStructure();

	TM->RegisterTabSpawner(
	    SubstanceTabId,
	    FOnSpawnTab::CreateSP(this, &FSubstanceEditor::SpawnTab_SubstanceEditor))
	.SetDisplayName(LOCTEXT("SubstanceEditorTab", "SubstanceEditor"))
	.SetGroup(MenuStructure.GetStructureRoot());
}

void FSubstanceEditor::UnregisterTabSpawners(const TSharedRef<class FTabManager>& TM)
{
	FAssetEditorToolkit::UnregisterTabSpawners(TM);

	TM->UnregisterTabSpawner(SubstanceTabId);
}

FSubstanceEditor::~FSubstanceEditor()
{
	if (GEditor)
	{
		GEditor->UnregisterForUndo(this);
		GEditor->GetEditorSubsystem<UImportSubsystem>()->OnAssetReimport.RemoveAll(this);
	}
}

void FSubstanceEditor::InitSubstanceEditor(const TSharedPtr< class IToolkitHost >& InitToolkitHost, UObject* ObjectToEdit)
{
	EditedGraph = CastChecked<USubstanceGraphInstance>(ObjectToEdit);

	// cannot edit incomplete instance
	if (!EditedGraph || !EditedGraph->Instance || !EditedGraph->ParentFactory)
	{
		return;
	}

	// Register to be notified when an object is reimported.
	GEditor->GetEditorSubsystem<UImportSubsystem>()->OnAssetReimport.AddSP(this, &FSubstanceEditor::OnObjectReimported);

	// Support undo/redo
	EditedGraph->SetFlags(RF_Transactional);

	GEditor->RegisterForUndo(this);

	// Register our commands. This will only register them if not previously registered
	FSubstanceEditorCommands::Register();

	BindCommands();

	CreateInternalWidgets();

	const TSharedRef<FTabManager::FLayout> StandaloneDefaultLayout = FTabManager::NewLayout("Standalone_SubstanceEditor_Layout")
	        ->AddArea
	        (
	            FTabManager::NewPrimaryArea()
	            ->SetOrientation(Orient_Vertical)
	            ->Split
	            (
	                FTabManager::NewSplitter()
	                ->SetOrientation(Orient_Vertical)
	                ->Split
	                (
	                    FTabManager::NewStack()
	                    ->AddTab(SubstanceTabId, ETabState::OpenedTab)
	                    ->SetHideTabWell(true)
	                )
	            )
	        );

	const bool bCreateDefaultStandaloneMenu = true;
	const bool bCreateDefaultToolbar = true;

	//#NOTE:: We are setting the Factory as the editing object as this will be the root of the reimport
	FAssetEditorToolkit::InitAssetEditor(EToolkitMode::Standalone,
	                                     InitToolkitHost,
	                                     SubstanceEditorModule::SubstanceEditorAppIdentifier,
	                                     StandaloneDefaultLayout,
	                                     bCreateDefaultStandaloneMenu,
	                                     bCreateDefaultToolbar,
	                                     EditedGraph);

	ISubstanceEditorModule* SubstanceEditorModule = &FModuleManager::LoadModuleChecked<ISubstanceEditorModule>("SubstanceEditor");
	AddMenuExtender(SubstanceEditorModule->GetMenuExtensibilityManager()->GetAllExtenders());

	ExtendToolbar();
	RegenerateMenusAndToolbars();
}

USubstanceGraphInstance* FSubstanceEditor::GetGraph() const
{
	return EditedGraph;
}

FName FSubstanceEditor::GetToolkitFName() const
{
	return FName("SubstanceEditor");
}

FText FSubstanceEditor::GetBaseToolkitName() const
{
	return LOCTEXT("AppLabel", "Substance Editor");
}

FString FSubstanceEditor::GetWorldCentricTabPrefix() const
{
	return LOCTEXT("WorldCentricTabPrefix", "Font ").ToString();
}

FLinearColor FSubstanceEditor::GetWorldCentricTabColorScale() const
{
	return FLinearColor(0.3f, 0.2f, 0.5f, 0.5f);
}

TSharedRef<SDockTab> FSubstanceEditor::SpawnTab_SubstanceEditor(const FSpawnTabArgs& Args)
{
	check(Args.GetTabId().TabType == SubstanceTabId);

	TSharedRef<SDockTab> SpawnedTab =
	    SNew(SDockTab)
	    .TabRole(ETabRole::NomadTab)
	    .Label(FText::FromString(GetTabPrefix() + TEXT("Substance Editor")))
	    [
	        SubstanceEditorPanel.ToSharedRef()
	    ];

	AddToSpawnedToolPanels(Args.GetTabId().TabType, SpawnedTab);

	return SpawnedTab;
}

void FSubstanceEditor::AddToSpawnedToolPanels(const FName& TabIdentifier, const TSharedRef<SDockTab>& SpawnedTab)
{
	TWeakPtr<SDockTab>* TabSpot = SpawnedToolPanels.Find(TabIdentifier);

	if (!TabSpot)
	{
		SpawnedToolPanels.Add(TabIdentifier, SpawnedTab);
	}
	else
	{
		check(!TabSpot->IsValid());
		*TabSpot = SpawnedTab;
	}
}

void FSubstanceEditor::AddReferencedObjects(FReferenceCollector& Collector)
{
	Collector.AddReferencedObject(EditedGraph);
}

void FSubstanceEditor::PostUndo(bool bSuccess)
{
	SubstanceEditorPanel->OnUndo();
}

void FSubstanceEditor::PostRedo(bool bSuccess)
{
	SubstanceEditorPanel->OnRedo();
}

void FSubstanceEditor::NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, class FEditPropertyChain* PropertyThatChanged)
{
}

void FSubstanceEditor::CreateInternalWidgets()
{
	if (EditedGraph && EditedGraph->Instance)
	{
		SubstanceEditorPanel = SNew(SSubstanceEditorPanel)
		                       .SubstanceEditor(SharedThis(this));
	}
}

void FSubstanceEditor::ExtendToolbar()
{
	struct Local
	{
		static void FillToolbar(FToolBarBuilder& ToolbarBuilder)
		{
			ToolbarBuilder.BeginSection("Reset to default values.");
			{
				ToolbarBuilder.AddToolBarButton(FSubstanceEditorCommands::Get().ResetDefaultValues);
			}
			ToolbarBuilder.EndSection();

			ToolbarBuilder.BeginSection("Presets");
			{
				ToolbarBuilder.AddToolBarButton(FSubstanceEditorCommands::Get().ExportPreset);
				ToolbarBuilder.AddToolBarButton(FSubstanceEditorCommands::Get().ImportPreset);
			}
			ToolbarBuilder.EndSection();
		}
	};

	TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
	ToolbarExtender->AddToolBarExtension(
	    "Asset",
	    EExtensionHook::After,
	    GetToolkitCommands(),
	    FToolBarExtensionDelegate::CreateStatic(&Local::FillToolbar)
	);

	AddToolbarExtender(ToolbarExtender);

	ISubstanceEditorModule* SubstanceEditorModule = &FModuleManager::LoadModuleChecked<ISubstanceEditorModule>("SubstanceEditor");
	AddToolbarExtender(SubstanceEditorModule->GetToolBarExtensibilityManager()->GetAllExtenders());
}

void FSubstanceEditor::BindCommands()
{
	const FSubstanceEditorCommands& Commands = FSubstanceEditorCommands::Get();

	ToolkitCommands->MapAction(
	    Commands.ResetDefaultValues,
	    FExecuteAction::CreateSP(this, &FSubstanceEditor::OnResetDefaultValues),
	    FCanExecuteAction());

	ToolkitCommands->MapAction(
	    Commands.ExportPreset,
	    FExecuteAction::CreateSP(this, &FSubstanceEditor::OnExportPreset),
	    FCanExecuteAction());

	ToolkitCommands->MapAction(
	    Commands.ImportPreset,
	    FExecuteAction::CreateSP(this, &FSubstanceEditor::OnImportPreset),
	    FCanExecuteAction());
}

void FSubstanceEditor::OnExportPreset() const
{
	if (GetGraph())
	{
		Substance::Helpers::ExportPresetFromGraph(GetGraph());
	}
}

void FSubstanceEditor::OnImportPreset()
{
	if (GetGraph())
	{
		Substance::Helpers::ImportAndApplyPresetForGraph(GetGraph());
	}
}

void FSubstanceEditor::OnResetDefaultValues()
{
	if (GetGraph())
	{
		GetGraph()->Modify(true);
		Substance::Helpers::ResetToDefault(GetGraph()->Instance);

		if (SubstanceEditorPanel.IsValid())
		{
			SubstanceEditorPanel->ResetThumbnailInputs(GetGraph()->Instance.get());
		}

		GetGraph()->PrepareOutputsForSave();
		Substance::Helpers::RenderSync(GetGraph()->Instance, true);
		GetGraph()->SaveAllOutputs();
	}
}

void FSubstanceEditor::OnObjectReimported(UObject* InObject)
{
	const USubstanceGraphInstance* GraphInstance = Cast<USubstanceGraphInstance>(InObject);
	const USubstanceInstanceFactory* InstanceFactory = Cast<USubstanceInstanceFactory>(InObject);

	if (GraphInstance == EditedGraph || EditedGraph->ParentFactory == InstanceFactory)
	{
		this->CloseWindow();
	}
}

#undef LOC_NAMESPACE
#undef LOCTEXT_NAMESPACE
