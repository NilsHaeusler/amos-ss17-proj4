#!/bin/bash

sudo modprobe can
sudo modprobe vcan
sudo ip link add dev vcan0 type vcan
sudo ip link set up vcan0

sudo /sbin/ip link set can0 up type can bitrate 500000
