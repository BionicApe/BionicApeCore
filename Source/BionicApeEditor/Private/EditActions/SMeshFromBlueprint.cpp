// Created by Bionic Ape. All Rights Reserved.

#include "EditActions/SMeshFromBlueprint.h"
#include "Widgets/Input/SCheckBox.h"
#include "Editor/EditorEngine.h"
#include "Widgets/Layout/SUniformGridPanel.h"
#include "Widgets/Text/STextBlock.h"

#define LOCTEXT_NAMESPACE "SMeshFromBlueprints"


void SMeshFromBlueprint::Construct(const FArguments& InArgs)
{
	SWindow::Construct(
		SWindow::FArguments()
		.Title(LOCTEXT("SMeshFromBlueprintsTitle", "Extract Options"))
		.SupportsMinimize(false)
		.SupportsMaximize(false)
		.ClientSize(FVector2D(900, 500))
		[
			SNew(SVerticalBox)
			+ SVerticalBox::Slot()
			[
				SNew(SCheckBox)
				.OnCheckStateChanged_Static(&SMeshFromBlueprint::OnChecked, &ExtractOptions.bSpawnOneActorPerComponent /*, ExtractOptions.bSpawnOneActorPerComponent*/)
				.IsChecked_Static(&SMeshFromBlueprint::IsChecked, &ExtractOptions.bSpawnOneActorPerComponent)
				.ToolTipText(LOCTEXT("SMeshFromBlueprints_Tooltip_SpawnOneActorPerComponent", "Spawns One Actor Per Component"))
				.Content()
				[
					SNew(STextBlock)
					.Text(LOCTEXT("SMeshFromBlueprints_Checkbox_SpawnOneActorPerComponent", "Spawn One Actor per Component"))
				]
			]
			+ SVerticalBox::Slot()
			[
				SNew(SCheckBox)
				.OnCheckStateChanged_Static(&SMeshFromBlueprint::OnChecked, &ExtractOptions.bUseLevelNameAsRootFolder)
				.IsChecked_Static(&SMeshFromBlueprint::IsChecked, &ExtractOptions.bUseLevelNameAsRootFolder)
				.ToolTipText(LOCTEXT("SMeshFromBlueprints_Tooltip_UseLevelNameAsRootFolder", "Use Level Name As Root Folder"))
				.Content()
				[
					SNew(STextBlock)
					.Text(LOCTEXT("SMeshFromBlueprints_Checkbox_UseLevelNameAsRootFolder", "Use Level Name As Root Folder"))
				]
			]
			+ SVerticalBox::Slot()
			[
				SNew(SCheckBox)
				.OnCheckStateChanged_Static(&SMeshFromBlueprint::OnChecked, &ExtractOptions.bIterateAllActors)
				.IsChecked_Static(&SMeshFromBlueprint::IsChecked, &ExtractOptions.bIterateAllActors)
				.ToolTipText(LOCTEXT("SMeshFromBlueprints_Tooltip_IterateAllActors", "Iterate All Actors"))
				.Content()
				[
					SNew(STextBlock)
					.Text(LOCTEXT("SMeshFromBlueprints_Checkbox_IterateAllActors", "Iterate All Actors"))
				]
			]
			+ SVerticalBox::Slot()
				[
					SNew(SCheckBox)
					.OnCheckStateChanged_Static(&SMeshFromBlueprint::OnChecked, &ExtractOptions.bSkipActorReplacementConfirmation)
				.IsChecked_Static(&SMeshFromBlueprint::IsChecked, &ExtractOptions.bSkipActorReplacementConfirmation)
				.ToolTipText(LOCTEXT("SMeshFromBlueprints_Tooltip_bSkipActorReplacementConfirmation", ""))
				.Content()
				[
					SNew(STextBlock)
					.Text(LOCTEXT("SMeshFromBlueprints_Checkbox_bSkipActorReplacementConfirmation", "Skip Actor Replacement Confirmation"))
				]
			]
			+ SVerticalBox::Slot()
			[
				SNew(SCheckBox)
				.OnCheckStateChanged_Static(&SMeshFromBlueprint::OnChecked, &ExtractOptions.bForceStatic)
				.IsChecked_Static(&SMeshFromBlueprint::IsChecked, &ExtractOptions.bForceStatic)
				.ToolTipText(LOCTEXT("SMeshFromBlueprints_Tooltip_ForceStatic", "Force Static Component"))
				.Content()
				[
					SNew(STextBlock)
					.Text(LOCTEXT("SMeshFromBlueprints_Checkbox_ForceStatic", "Force Static Component"))
				]
			]
			+ SVerticalBox::Slot()
			[
				SNew(SCheckBox)
				.OnCheckStateChanged_Static(&SMeshFromBlueprint::OnChecked, &ExtractOptions.bOnlyConstructorComponentsActors)
				.IsChecked_Static(&SMeshFromBlueprint::IsChecked, &ExtractOptions.bOnlyConstructorComponentsActors)
				.ToolTipText(LOCTEXT("SMeshFromBlueprints_Tooltip_OnlyConstructorComponentsActors", "Only Actors that have Components spawned in the Blueprint's constructor"))
				.Content()
				[
					SNew(STextBlock)
					.Text(LOCTEXT("SMeshFromBlueprints_Checkbox_OnlyConstructorComponentsActors", "Only Actors that have Components spawned in the Blueprint's constructor"))
				]
			]
			+ SVerticalBox::Slot()
			[
				SNew(SCheckBox)
				.OnCheckStateChanged_Static(&SMeshFromBlueprint::OnChecked, &ExtractOptions.bDeleteOriginal)
				.IsChecked_Static(&SMeshFromBlueprint::IsChecked, &ExtractOptions.bDeleteOriginal)
				.ToolTipText(LOCTEXT("SMeshFromBlueprints_Tooltip_bDeleteOriginal", "Delete Original"))
				.Content()
				[
					SNew(STextBlock)
					.Text(LOCTEXT("SMeshFromBlueprints_Checkbox_bDeleteOriginal", "Delete Original"))
				]
				]
			+ SVerticalBox::Slot()
				[
					SNew(SCheckBox)
					.OnCheckStateChanged_Static(&SMeshFromBlueprint::OnChecked, &ExtractOptions.bSkipDeleteConfirmation)
				.IsChecked_Static(&SMeshFromBlueprint::IsChecked, &ExtractOptions.bSkipDeleteConfirmation)
				.ToolTipText(LOCTEXT("SMeshFromBlueprints_Tooltip_bSkipDeleteConfirmation", "Skip Delete Confirmation"))
				.Content()
				[
					SNew(STextBlock)
					.Text(LOCTEXT("SMeshFromBlueprints_Checkbox_bSkipDeleteConfirmation", "Skip Delete Confirmation"))
				]
			]
			//
			+ SVerticalBox::Slot()
			.AutoHeight()
			.HAlign(HAlign_Right)
			.Padding(5)
			[
				SNew(SUniformGridPanel)
				.SlotPadding(FEditorStyle::GetMargin("StandardDialog.SlotPadding"))
				.MinDesiredSlotWidth(FEditorStyle::GetFloat("StandardDialog.MinDesiredSlotWidth"))
				.MinDesiredSlotHeight(FEditorStyle::GetFloat("StandardDialog.MinDesiredSlotHeight"))
				+ SUniformGridPanel::Slot(0, 0)
				.HAlign(HAlign_Left)
				[
					SNew(SButton)
					.HAlign(HAlign_Left)
					.ContentPadding(FEditorStyle::GetMargin("StandardDialog.ContentPadding"))
					.Text(LOCTEXT("Cancel", "Cancel"))
					.OnClicked(this, &SMeshFromBlueprint::OnButtonClick, EButtonValue::Cancel)
					.IsEnabled(true)
				]
				+ SUniformGridPanel::Slot(1, 0)
				.HAlign(HAlign_Left)
				[
					SNew(SButton)
					.HAlign(HAlign_Left)
					.ContentPadding(FEditorStyle::GetMargin("StandardDialog.ContentPadding"))
					.Text(LOCTEXT("Accept", "Accept"))
					.OnClicked(this, &SMeshFromBlueprint::OnButtonClick, EButtonValue::Accept)
					.IsEnabled(true)
				]
			]
		]
	);
}

ECheckBoxState SMeshFromBlueprint::IsChecked(bool* Value)
{
	return *Value ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;
}

void SMeshFromBlueprint::OnChecked(ECheckBoxState NewCheckedState, bool* Value)
{
	*Value = NewCheckedState == ECheckBoxState::Checked;
}

bool SMeshFromBlueprint::ShowModal(FExtractOptions& OutExtractOptions)
{
	OutExtractOptions = ExtractOptions;
	GEditor->EditorAddModalWindow(SharedThis(this));
	return ButtonPressed == EButtonValue::Accept;
}


FReply SMeshFromBlueprint::OnButtonClick(EButtonValue NewButtonPressed)
{
	ButtonPressed = NewButtonPressed;
	RequestDestroyWindow();
	return FReply::Handled();
}

#undef LOCTEXT_NAMESPACE