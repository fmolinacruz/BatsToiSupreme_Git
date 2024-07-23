Batstoi Supreme

Engine: Unreal Engine 5.2

ReRun
1. Clean_generated.bat for clean temp file
2. Generate Visual studio file
3. Run BatsToiSupreme_Real.sln
4. Build config: Development editor Win64

Run
1. TimeSquare Local map: Player Map
   Multiplayer Map: LVMap_TimeSquare_Multi
   Cathy Local Map: Cathy_ModernArenaWithCrowd

Need 2 gamepad to play game

** Build Server
1. Open c++ project
2. Build config: Development Server, Win64
3. Run Config: Development editor Win64
4. Open Editor
5. Package with config: Windows, Development, BatsToiSupreme_RealServer, 

** Deploy to AWS
1. Run Power shell
2. Run First Setup for prepare asset
- Command/FirstSetup.bat
3. Run Aws Config
- Command/aws-configure.bat
4. Deploy
- Command/ps-run-upload-deploy.ps1
