#include "CreateFactoryCommand.h"
#include "CreateFactoryOptions.h"

#include "Misc/FileHelper.h"


bool CreateFactoryCommand::Run(const FCreateFactoryOptions& Options)
{
    const FString& TemplatePath = FPaths::ProjectPluginsDir() + "BionicApeCore/Resources/CreateFactoryTemplate/[ModuleName]Editor/";
    const FString& TargetPath = TemplatePath.Replace(*FString("[ModuleName]"), *Options.ModuleName);
    // const FString& TargetPath = Options.TargetPath + Options.ModuleName + "Editor/";

    // UE_LOG(LogTemp, Warning, TEXT("TemplatePath: %s"), *TemplatePath);
    // UE_LOG(LogTemp, Warning, TEXT("TargetPath: %s"), *TargetPath);

    IPlatformFile& FileManager = FPlatformFileManager::Get().GetPlatformFile();

    TArray<FString> BlacklistKeywords;
    TMap<FString, FString> PathReplacementsMap;
    
    PathReplacementsMap.Add("[Module]", Options.ModuleName);
    
    for (const EFactoryType FactoryType : TEnumRange<EFactoryType>())
    {
        if (FactoryType == Options.FactoryType)
        {
            PathReplacementsMap.Add("[" + StaticEnum<EFactoryType>()->GetDisplayValueAsText(FactoryType).ToString() + "]", Options.FactoryName);
        }
        else
        {
            BlacklistKeywords.Add("[" + StaticEnum<EFactoryType>()->GetDisplayValueAsText(FactoryType).ToString() + "]");
        }
    }
    
    const TMap<FString, FString> FileReplacementsMap =
    {
        {"[Module]", Options.ModuleName},
        {"[Module_Upper]", Options.ModuleName.ToUpper()},
        {"[Factory]", Options.FactoryName}
    };
    
    DirectoryCopierAndParser Visitor(TemplatePath, TargetPath, Options.bReplaceFileIfExists, BlacklistKeywords, PathReplacementsMap, FileReplacementsMap);
    if(!FileManager.IterateDirectoryRecursively(*TemplatePath,Visitor))
    {
        UE_LOG(LogTemp, Error, TEXT("Unexpected error trying to find CreateFactory template directory in path: %s"), *TemplatePath);
        return false;
    }

    // TODO: Check that module files use the factory we just created (if they already existed and we chose not to replace files, they may not use our factory)
    // In that case, we will have to add the line:
    // AssetTools.RegisterAssetTypeActions(MakeShareable(new F[Factory]TypeActions(AssetCategoryBit)));
    // in the file:
    // [Module]EditorModule.cpp
    // in:
    // F[Module]EditorModuleModule::StartupModule()

    return true;
}

bool DirectoryCopierAndParser::Visit(const TCHAR* FilenameOrDirectory, bool bIsDirectory)
{
    const FString FilenameOrDirectoryString = FString(FilenameOrDirectory);
    for (FString BlacklistKeyword : BlacklistKeywords)
    {
        if (FilenameOrDirectoryString.Contains(BlacklistKeyword))
        {
            return true;
        }
    }
    
    FString TargetFilenameOrDirectory = FilenameOrDirectoryString.Replace(*SourcePath, *TargetPath);
    for (TPair<FString, FString> Replacement : PathReplacementsMap)
    {
        TargetFilenameOrDirectory.ReplaceInline(*Replacement.Key, *Replacement.Value);
    }
    
    IPlatformFile& FileManager = FPlatformFileManager::Get().GetPlatformFile();
    if(bIsDirectory)
    {
        if (!FileManager.DirectoryExists(*TargetFilenameOrDirectory))
        {
            FileManager.CreateDirectoryTree(*TargetFilenameOrDirectory);
        }
    }
    else
    {
        if (bReplaceFileIfExists || !FileManager.FileExists(*TargetFilenameOrDirectory))
        {
            FileManager.CopyFile(*TargetFilenameOrDirectory, FilenameOrDirectory);
            ParseFile(TargetFilenameOrDirectory, FileReplacementsMap);
        }
    }
    return true;
}

void DirectoryCopierAndParser::ParseFile(const FString& FilePath, const TMap<FString,FString>& ReplacementsMap)
{
    TArray<FString> FileLines;
    TArray<FString> ParsedLines;
    
    FFileHelper::LoadANSITextFileToStrings(*FilePath, &IFileManager::Get(), FileLines);
    for (FString Line : FileLines)
    {
        for(const TPair<FString,FString>& Replacement : ReplacementsMap)
        {
            Line.ReplaceInline(*Replacement.Key, *Replacement.Value, ESearchCase::CaseSensitive);
        }
        ParsedLines.Add(Line);
    }

    if (!FFileHelper::SaveStringArrayToFile(ParsedLines, *FilePath, FFileHelper::EEncodingOptions::AutoDetect))
    {
        UE_LOG(LogTemp, Warning, TEXT("Unexpected error parsing file: %s"), *FilePath);
    }
}