// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "ld48/ld48GameModeBase.h"
#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4883)
#endif
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeld48GameModeBase() {}
// Cross Module References
	LD48_API UClass* Z_Construct_UClass_Ald48GameModeBase_NoRegister();
	LD48_API UClass* Z_Construct_UClass_Ald48GameModeBase();
	ENGINE_API UClass* Z_Construct_UClass_AGameModeBase();
	UPackage* Z_Construct_UPackage__Script_ld48();
// End Cross Module References
	void Ald48GameModeBase::StaticRegisterNativesAld48GameModeBase()
	{
	}
	UClass* Z_Construct_UClass_Ald48GameModeBase_NoRegister()
	{
		return Ald48GameModeBase::StaticClass();
	}
	struct Z_Construct_UClass_Ald48GameModeBase_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UE4CodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UE4CodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_Ald48GameModeBase_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_AGameModeBase,
		(UObject* (*)())Z_Construct_UPackage__Script_ld48,
	};
#if WITH_METADATA
	const UE4CodeGen_Private::FMetaDataPairParam Z_Construct_UClass_Ald48GameModeBase_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "HideCategories", "Info Rendering MovementReplication Replication Actor Input Movement Collision Rendering Utilities|Transformation" },
		{ "IncludePath", "ld48GameModeBase.h" },
		{ "ModuleRelativePath", "ld48GameModeBase.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_Ald48GameModeBase_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<Ald48GameModeBase>::IsAbstract,
	};
	const UE4CodeGen_Private::FClassParams Z_Construct_UClass_Ald48GameModeBase_Statics::ClassParams = {
		&Ald48GameModeBase::StaticClass,
		"Game",
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x009002ACu,
		METADATA_PARAMS(Z_Construct_UClass_Ald48GameModeBase_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_Ald48GameModeBase_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_Ald48GameModeBase()
	{
		static UClass* OuterClass = nullptr;
		if (!OuterClass)
		{
			UE4CodeGen_Private::ConstructUClass(OuterClass, Z_Construct_UClass_Ald48GameModeBase_Statics::ClassParams);
		}
		return OuterClass;
	}
	IMPLEMENT_CLASS(Ald48GameModeBase, 2381844049);
	template<> LD48_API UClass* StaticClass<Ald48GameModeBase>()
	{
		return Ald48GameModeBase::StaticClass();
	}
	static FCompiledInDefer Z_CompiledInDefer_UClass_Ald48GameModeBase(Z_Construct_UClass_Ald48GameModeBase, &Ald48GameModeBase::StaticClass, TEXT("/Script/ld48"), TEXT("Ald48GameModeBase"), false, nullptr, nullptr, nullptr);
	DEFINE_VTABLE_PTR_HELPER_CTOR(Ald48GameModeBase);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
#ifdef _MSC_VER
#pragma warning (pop)
#endif
