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
                //"NeuralInteractionClient",
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
