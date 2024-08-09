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

PLAY LAN MULTIPLAYER
Setup
- Modify Config/CustinConfig.ini
     + PIELanHost= Server IPConfig 
- Map: LV_Lobby (default)
- Number of Players = 1
- Net Mode = PlayStandAlone

Setup on server:
- Modify Server.bat
     + SET MapName=LVMap_TimeSquare_Multi
     + SET ExePath= UnrealEditor DIR
	 
Run
- Run Server.bat on PC1
- Play map LV_Lobby on PC1
- Play map LV_Lobby on PC2
- Play Game

HOW TO TEST LINUX Server build local
- Install wsl
- Install Ubuntu 20
- Build Linux Server
- Get fleet param by command: .\command\anywhere-params.ps1 -Profile batstoi -Region ap-northeast-1 -EnvName duy
- Run .\BatsToiSupreme_RealServer.sh with param abow
