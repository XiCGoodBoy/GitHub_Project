// Fill out your copyright notice in the Description page of Project Settings.


#include "ScannerSettingsDetails.h"

#include "DetailCategoryBuilder.h"
#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "FScannerConfig.h"

#define LOCTEXT_NAMESPACE "ImportRulesTable"

void FScannerSettingsDetails::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	TArray<TSharedPtr<FStructOnScope>> StructBeingCustomized;
	DetailBuilder.GetStructsBeingCustomized(StructBeingCustomized);
	check(StructBeingCustomized.Num()==1);
	FScannerConfig* ScannerSettingsIns = reinterpret_cast<FScannerConfig*>(StructBeingCustomized[0].Get()->
		GetStructMemory());
	IDetailCategoryBuilder* RulesCategory = &DetailBuilder.EditCategory(
		TEXT("RulesTable"), FText::GetEmpty(), ECategoryPriority::Default);

	if (RulesCategory)
	{
		RulesCategory->SetShowAdvanced(true);
		RulesCategory->AddCustomRow(LOCTEXT("ImportRulesTable", "Import Rules Table"), true)
		             .ValueContent()
		[
			SNew(SHorizontalBox)
			+ SHorizontalBox::Slot()
			  .Padding(0)
			  .AutoWidth()
			[
				SNew(SButton)
				.Text(LOCTEXT("Import", "Import"))
				.ToolTipText(LOCTEXT("ImportRulesTable_Tooltop", "Import Rules Table to the Config"))
				.IsEnabled_Lambda([this,ScannerSettingsIns]()-> bool
				             {
					             return ScannerSettingsIns->bUseRulesTable;
				             })
				             .OnClicked_Lambda([this,ScannerSettingsIns]()
				             {
					             if (ScannerSettingsIns)
					             {
					             	// ScannerSettingsIns->HandleImportRulesTable();
					             }
				             	return (FReply::Handled());
				             })
			]
		];
	}
}


#undef LOCTEXT_NAMESPACE
