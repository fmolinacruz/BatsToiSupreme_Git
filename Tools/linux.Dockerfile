# Use the official Unreal Engine runtime image as the base image
FROM ghcr.io/epicgames/unreal-engine:runtime

# Copy the dedicated server build to the container
COPY --chmod=777 ./LinuxServer /home/ue4/project

# Copy start up script
COPY --chmod=777 ./Tools/linux-server-start.sh /home/ue4/project

# Set the working directory
WORKDIR /home/ue4/project

# Expose the necessary ports
EXPOSE 7777/udp
EXPOSE 7777/tcp

# To run the docker with env variable instead
# Example: docker run -dit --name unreal -p 7777:7777/udp -e DOCKER_MAPNAME=Map_1 -e DOCKER_GAMEMODE=Default [IMAGE_NAME]
# ENV SERVER_MAPNAME ""
# ENV SERVER_GAMEMODE "Default"
# CMD ["/home/ue4/project/linux-server-start.sh", "-m", "${SERVER_MAPNAME}", "-g", "${SERVER_GAMEMODE}"]