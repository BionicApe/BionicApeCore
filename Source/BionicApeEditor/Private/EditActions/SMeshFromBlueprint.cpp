// Created by Bionic Ape. All Rights Reserved.

#include "EditActions/SMeshFromBlueprints.h"

#define LOCTEXT_NAMESPACE "SMeshFromBlueprints"



void SMeshFromBlueprint::Construct(const FArguments& InArgs)
{
	AllowCancelClick = true;

	SWindow::Construct(
		SWindow::FArguments()
			.Title(LOCTEXT("SMeshFromBlueprintsTitle", "Extract Options"))
			.SupportsMinimize(false)
			.SupportsMaximize(false)
			.ClientSize(FVector2D(900, 500))
			[
				SNew(SVerticalBox)
				+ SVerticalBox::Slot() // Add user input block
				.Padding(2)
				[
					SNew(SBorder)
					.BorderImage(FEditorStyle::GetBrush("ToolPanel.GroupBorder"))
				[
					SNew(SVerticalBox)
					+ SVerticalBox::Slot()
					.AutoHeight()
					[
						SNew(STextBlock)
						.Text(LOCTEXT("SelectPath", "Select a Skeletal Mesh or Skeleton for source pose (or none for current pose)"))
						.Font(FCoreStyle::GetDefaultFontStyle("Regular", 14))
					]
					+ SVerticalBox::Slot()
					.MaxHeight(450)
					.Padding(3)
					[
						ContentBrowserModule.Get().CreateAssetPicker(AssetPickerConfig)
					]
					+ SVerticalBox::Slot()
					.AutoHeight()
					[
						SNew(SSeparator)
					]
				]
			]
	+ SVerticalBox::Slot()
		.AutoHeight()
		.HAlign(HAlign_Fill)
		.Padding(5)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			.FillWidth(1)
			[
				SNew(SCheckBox)
				.IsChecked(this, &SCopyBonesLocationDialog::IsRotationsChecked)
				.IsEnabled_Lambda([this]() { return SelectedOptions.bUpdateReferenceSkeleton; })
				.ToolTipText(LOCTEXT("UpdateRotationsCheckboxTooltip", "Updates the bone rotations when updating the reference skeleton"))
				.OnCheckStateChanged(this, &SCopyBonesLocationDialog::OnRotationCheckStateChange)
				.Content()
			[
				SNew(STextBlock)
				.Text(LOCTEXT("UpdateRefSkeletonRotation", "Rotations"))
			]
		]
	+ SHorizontalBox::Slot()
		.FillWidth(1)
		[
			SNew(SCheckBox)
			.IsChecked(this, &SCopyBonesLocationDialog::IsTranslationChecked)
		.IsEnabled_Lambda([this]() { return SelectedOptions.bUpdateReferenceSkeleton; })
		.ToolTipText(LOCTEXT("UpdateLocationCheckboxTooltip", "Updates the bone translations when updating the reference skeleton"))
		.OnCheckStateChanged(this, &SCopyBonesLocationDialog::OnTranslationCheckStateChange)
		.Content()
		[
			SNew(STextBlock)
			.Text(LOCTEXT("UpdateRefSkeletonLocation", "Location"))
		]
		]
	+ SHorizontalBox::Slot()
		.FillWidth(1)
		[
			SNew(SCheckBox)
			.IsChecked(this, &SCopyBonesLocationDialog::IsScaleChecked)
		.IsEnabled_Lambda([this]() { return SelectedOptions.bUpdateReferenceSkeleton; })
		.ToolTipText(LOCTEXT("UpdateLocationCheckboxTooltip", "Updates the bone scales when updating the reference skeleton"))
		.OnCheckStateChanged(this, &SCopyBonesLocationDialog::OnScaleCheckStateChange)
		.Content()
		[
			SNew(STextBlock)
			.Text(LOCTEXT("UpdateRefSkeletonScale", "Scale"))
		]
		]
		]
	+ SVerticalBox::Slot()
		.AutoHeight()
		.HAlign(HAlign_Fill)
		.Padding(5)
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
		.FillWidth(1)
		[
			SNew(SCheckBox)
			.Style(&FEditorStyle::GetWidgetStyle<FCheckBoxStyle>("Menu.RadioButton"))
		.IsChecked(this, &SCopyBonesLocationDialog::IsUpdateRefSkelChecked)
		.ToolTipText(LOCTEXT("UpdateRefSkeletonCheckboxTooltip", "Updates the reference skeleton bones. This is generally what you want."))
		.OnCheckStateChanged(this, &SCopyBonesLocationDialog::OnUpdateRefSkelChange)
		.Content()
		[
			SNew(STextBlock)
			.Text(LOCTEXT("UpdateRefSkeleton", "Update Ref Skeleton?"))
		]
		]
	+ SHorizontalBox::Slot()
		.FillWidth(1)
		[
			SNew(SCheckBox)
			.Style(&FEditorStyle::GetWidgetStyle<FCheckBoxStyle>("Menu.RadioButton"))
		.IsChecked(this, &SCopyBonesLocationDialog::IsUpdateMeshGeoChecked)
		.ToolTipText(LOCTEXT("UpdateMeshGeoCheckboxTooltip", "Updates the mesh vertex positions. (Experimental)"))
		.OnCheckStateChanged(this, &SCopyBonesLocationDialog::OnUpdateMeshChange)
		.Content()
		[
			SNew(STextBlock)
			.Text(LOCTEXT("UpdateMeshGeo", "Update Mesh Geometry?"))
		]
		]
		]
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
		.OnClicked(this, &SCopyBonesLocationDialog::OnButtonClick, ECopyPoseType::Cancel)
		.IsEnabled(true)
		]
	+ SUniformGridPanel::Slot(1, 0)
		[
			SNew(SButton)
			.HAlign(HAlign_Center)
		.ContentPadding(FEditorStyle::GetMargin("StandardDialog.ContentPadding"))
		.Text(LOCTEXT("UseCurrentPose", "Use Current Pose"))
		.IsEnabled_Lambda([this]()
			{
				if (SelectedOptions.bUpdateReferenceSkeleton)
				{
					return SelectedOptions.bLocations || SelectedOptions.bScale || SelectedOptions.bRotations;
				}
				return SelectedOptions.bUpdateMesh || SelectedOptions.bUpdateReferenceSkeleton;
			})
		.ToolTipText(LOCTEXT("UseCurrentPoseTooltip", "Use the pose of the preview mesh as the pose source"))
				.OnClicked(this, &SCopyBonesLocationDialog::OnButtonClick, ECopyPoseType::CurrentPose)
		]
	+ SUniformGridPanel::Slot(2, 0)
		[
			SNew(SButton)
			.HAlign(HAlign_Center)
		.ContentPadding(FEditorStyle::GetMargin("StandardDialog.ContentPadding"))
		.Text(LOCTEXT("UseSelectedPose", "Use Selected asset pose"))
		.ToolTipText(LOCTEXT("UseSelectedPoseTooltip", "Use the selected mesh or skeleton as the pose source"))
		.IsEnabled_Lambda([this]()
			{
				if (SelectedOptions.bUpdateReferenceSkeleton)
				{
					return SelectedOptions.bLocations || SelectedOptions.bScale || SelectedOptions.bRotations;
				}
				return PickedMeshOrSkeleton != nullptr && (
					SelectedOptions.bUpdateMesh || SelectedOptions.bUpdateReferenceSkeleton
					);
			})
		.OnClicked(this, &SCopyBonesLocationDialog::OnButtonClick, ECopyPoseType::SelectedAsset)
		]

		]
		]
	);
}

#undef LOCTEXT_NAMESPACE

