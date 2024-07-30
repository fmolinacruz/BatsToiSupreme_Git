#!/bin/bash
set -e

MAP_NAME="LV_LobbyServer"
GAMEMODE_NAME="Default"
SERVER_SCRIPT=/home/ue4/project/BatsToiSupreme_RealServer.sh

main() {
    while getopts "hm:g:" opt; do
        case $opt in
        h) 
            usage && exit 0
        ;;
        m) 
            MAP_NAME=$OPTARG
        ;;
        g) 
            GAMEMODE_NAME=$OPTARG
        ;;
        \?) usage_error "Invalid option: -$OPTARG";;
        esac
    done

    if [ -z "$MAP_NAME" ]; then
        echo "Map name cannot be empty."
        exit 1
    fi

    $SERVER_SCRIPT "$MAP_NAME"?game="$GAMEMODE_NAME" -server -log -epicapp=DedicatedServerDev -MAPNAME="$MAP_NAME" -GAMEMODE="$GAMEMODE_NAME"
}

usage_error() {
  message="$1"
  exit_code="$2"

  echo "ERROR: $message"
  echo ""
  usage
  exit "${exit_code:-1}"
}

usage() {
  echo "usage: linux-server-start.sh"
  echo ""
  echo "Options"
  echo "   -m         (Required) Dedicated server map name. Default is empty."
  echo "   -g         Dedicated server GameMode name. Default is \"Default\""
  echo ""
}

main "$@"