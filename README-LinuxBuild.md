# Build Linux Server

### Environment Set up

#### 1-Install Linux Cross-Compile Toolchain

- Navigate to [Cross-Compile Toolchain Page](https://dev.epicgames.com/documentation/en-us/unreal-engine/linux-development-requirements-for-unreal-engine?application_version=5.4), and find the version that you compile your source code Unreal Editor.

- Install the tool.

#### 2-Modify Source Engine Editor to build EOS plugin with Linux

- Open `\Engine\Plugins\Online\OnlineSubsystemEOS\OnlineSubsystemEOS.uplugin`. And add `Linux` to `PlatformAllowList`:

```sh
"PlatformAllowList": [
	"Win64",
	"Mac",
	"Android",
	"Linux"
]
```

- Navigate to `\Engine\Plugins\Online\OnlineSubsystemEOS\Private`. Duplicate `Mac` folder and rename the folder to `Linux`. Then inside that folder rename `MacEOSHelpers.h` to `LinuxEOSHelpers.h`
- Build the `UnrealEditor` again (not require Rebuild).

#### 3-Install Docker

Follow the instructions here [Docker Window Install](https://docs.docker.com/desktop/install/windows-install/)

This might require installing WSL2 in the process.

#### 4-Create Github Token to pull Unreal Engine runtime image

Follow the instructions here [Authenticating with GitHub Container Registry](https://dev.epicgames.com/documentation/en-us/unreal-engine/quick-start-guide-for-using-container-images-in-unreal-engine?application_version=5.4)

After getting your access token, open `Command Prompt` or `PowerShell` and run this

```sh
echo ACCESS_TOKEN | docker login ghcr.io -u USERNAME --password-stdin
```

Try to pull runtime image for Linux, it might take a while. Make sure `Docker` is running.

```sh
docker pull ghcr.io/epicgames/unreal-engine:runtime
```

### Build and Run Linux server with docker image

#### 1-Package project as a Linux Server

Open Project and Go to Packaging project. Please choose `Development` for binary configuration for debugging purposes.

![Pack Linux Server](https://raw.githubusercontent.com/DuncanDam/EOSDemo/main/pack-linux.png)

Select `Build` folder, or any folder you like but make sure to update that with docker build.

#### 2-Build Docker image

Open `Command Prompt` or `PowerShell`, and navigate to the project folder.

```sh
cd PROJECT_DIRECTORY
```

```sh
docker build -t eos-demo -f ./tools/linux.Dockerfile .
```

#### 3-Mount the docker image and run the dedicated server

Start image and name it `unreal`

```sh
docker run -dit --name unreal -p 7777:7777/udp eos-demo
```

Start and attach to the image process

```sh
docker start unreal
docker attach unreal
```

Now you should see this and can start a new linux server
```sh
ue4@ee030e556770:~/project$./linux-server-start.sh -m Map_1 -g Default
```

To remove the image run
```sh
docker remove unreal
```

**NOTE**: An alternative way to run is using Docker environment variable, you can uncomment these from `tools/linux.Dockerfile`

```sh
# To run the docker with env variable instead
# Example: docker run -dit --name unreal -p 7777:7777/udp -e DOCKER_MAPNAME=Map_1 -e DOCKER_GAMEMODE=Default [IMAGE_NAME]
ENV SERVER_MAPNAME ""
ENV SERVER_GAMEMODE "Default"
CMD ["/home/ue4/project/linux-server-start.sh", "-m", "${SERVER_MAPNAME}", "-g", "${SERVER_GAMEMODE}"]
```

And to run

```sh
docker run -dit --name unreal -p 7777:7777/udp -e DOCKER_MAPNAME=Map_1 -e DOCKER_GAMEMODE=Default eos-demo
```

Now you can run the client and connect to the local Linux Dedicated Server.
