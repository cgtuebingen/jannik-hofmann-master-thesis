using System.IO;
using System;

namespace UnrealBuildTool.Rules
{
    public class External : ModuleRules
    {
        private string ModulePath {
            get { return ModuleDirectory; }
        }

        private string BinariesPath {
            get { return Path.GetFullPath(Path.Combine(ModulePath, "../Binaries/")); }
        }

        public External(ReadOnlyTargetRules Target) : base(Target)
        {
            // Tell Unreal that this Module only imports Third-Party-Assets
            Type = ModuleType.External;

            LoadLibraries(Target);
        }

        public bool LoadLibraries(ReadOnlyTargetRules Target)
        {
            bool isLibrarySupported = Target.Platform == UnrealTargetPlatform.Win64;
            //bool bDebug = (Target.Configuration == UnrealTargetConfiguration.Debug && Target.bDebugBuildsActuallyUseDebugCRT);

            if (isLibrarySupported)
            {
                //string PlatformString = (Target.Platform == UnrealTargetPlatform.Win64) ? "x64" : "x86";

                // Explicitly name the used libraries
                /*PublicAdditionalLibraries.Add(Path.Combine(ModulePath, "Boost/lib/libboost_chrono-vc141-mt-1_64.lib"));
                PublicAdditionalLibraries.Add(Path.Combine(ModulePath, "Boost/lib/libboost_date_time-vc141-mt-1_64.lib"));
                PublicAdditionalLibraries.Add(Path.Combine(ModulePath, "Boost/lib/libboost_filesystem-vc141-mt-1_64.lib"));
                PublicAdditionalLibraries.Add(Path.Combine(ModulePath, "Boost/lib/libboost_iostreams-vc141-mt-1_64.lib"));
                PublicAdditionalLibraries.Add(Path.Combine(ModulePath, "Boost/lib/libboost_system-vc141-mt-1_64.lib"));
                PublicAdditionalLibraries.Add(Path.Combine(ModulePath, "Boost/lib/libboost_thread-vc141-mt-1_64.lib"));*/
                PublicAdditionalLibraries.Add(Path.Combine(ModulePath, "BoostLibrary/boost_1_75_0/stage/lib/libboost_date_time-vc141-mt-x64-1_75.lib"));
                PublicAdditionalLibraries.Add(Path.Combine(ModulePath, "BoostLibrary/boost_1_75_0/stage/lib/libboost_thread-vc141-mt-x64-1_75.lib"));
                PublicAdditionalLibraries.Add(Path.Combine(ModulePath, "BoostLibrary/boost_1_75_0/stage/lib/libboost_chrono-vc141-mt-x64-1_75.lib"));



                PublicIncludePaths.Add(Path.Combine(ModulePath, "BoostLibrary/boost_1_75_0"));
                PublicIncludePaths.Add(Path.Combine(ModulePath, "BoostLibrary/boost_1_75_0/stage/lib"));
                PublicIncludePaths.Add(Path.Combine(ModulePath, "MsgPack/msgpack_3_3_0_cpp"));
                //PublicIncludePaths.Add(Path.Combine(ModulePath, "Boost/include/boost-1_64"));
                //PublicIncludePaths.Add(Path.Combine(ModulePath, "PCL_181/include/pcl-1.8"));

                // Not sure if needed
                PublicDefinitions.Add("_CRT_SECURE_NO_WARNINGS=1");
                PublicDefinitions.Add("BOOST_DISABLE_ABI_HEADERS=1");

                // Needed configurations in order to run Boost
                bUseRTTI = true;
                bEnableExceptions = true;
                //bEnableUndefinedIdentifierWarnings = false;
            }

            PublicDefinitions.Add(string.Format("WITH_BOOST_BINDING={0}", isLibrarySupported ? 1 : 0));

            return isLibrarySupported;
        }
    }
}