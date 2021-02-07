// Some copyright should be here...

using System.IO;
using System;

using UnrealBuildTool;

namespace UnrealBuildTool.Rules
{
    public class NeuralInteractionClient : ModuleRules
    {
        private string ModulePath {
            get { return ModuleDirectory; }
        }

        private string ThirdPartyPath {
            get { return Path.GetFullPath(Path.Combine(ModulePath, "../ThirdParty/")); }
        }

        private string BinariesPath {
            get { return Path.GetFullPath(Path.Combine(ModulePath, "../../Binaries/")); }
        }

        public NeuralInteractionClient(ReadOnlyTargetRules Target) : base(Target)
        {
            PrivateIncludePaths.Add("Source/NeuralInteractionClient/Private");
            PublicIncludePaths.Add("Source/NeuralInteractionClient/Public");
            PrivateIncludePaths.Add("NeuralInteractionClient/Private");
            PublicIncludePaths.Add("NeuralInteractionClient/Public");

            PublicDependencyModuleNames.AddRange(new string[] {
                "Core",
                "External",
                "NeuralInteractionClient",
                // ... add private dependencies that you statically link with here ...
            });
            PrivateDependencyModuleNames.AddRange(new string[] {
                    "CoreUObject",
                    "Engine",
                    "Slate",
                    "SlateCore",

                    "Core",
                    "InputCore",
            });

            // Since the PCL module needs this, we also have to use these flags here
            bUseRTTI = true;
            bEnableExceptions = true;
            //bEnableUndefinedIdentifierWarnings = false;
        }
    }
}

/*using System.IO;
using System;

using UnrealBuildTool;

public class NeuralInteractionClient : ModuleRules
{
    private string ModulePath {
        get { return ModuleDirectory; }
    }

    private string BinariesPath {
        get { return Path.GetFullPath(Path.Combine(ModulePath, "../Binaries/")); }
    }

    public NeuralInteractionClient(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        bool isLibrarySupported = (Target.Platform == UnrealTargetPlatform.Win64);
        bool bDebug = (Target.Configuration == UnrealTargetConfiguration.Debug && Target.bDebugBuildsActuallyUseDebugCRT);

        if (isLibrarySupported)
        {
            PublicIncludePaths.AddRange(
                new string[] {
				    // ... add public include paths required here ...
                    Path.Combine(ModulePath, "../ThirdParty/BoostLibrary/boost_1_75_0"),
                    Path.Combine(ModulePath, "../ThirdParty/MsgPack/msgpack_3_3_0_cpp")
                }
                );

            PublicDefinitions.Add("_CRT_SECURE_NO_WARNINGS=1");
            PublicDefinitions.Add("BOOST_DISABLE_ABI_HEADERS=1");
            bUseRTTI = true;
            bEnableExceptions = true;
            //bEnableUndefinedIdentifierWarnings = false;
        }

        PublicDefinitions.Add(string.Format("WITH_PCL_BINDING={0}", isLibrarySupported ? 1 : 0));
        PublicDefinitions.Add(string.Format("WITH_BOOST_BINDING={0}", isLibrarySupported ? 1 : 0));

        PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
*/
