#!/usr/bin/bash

docker volume create sae103
# docker image pull clock:latest
docker container run -d --name sae103-forever -v sae103:/work clock

files=$(ls *.c)
for file in $files
do 
    docker container cp $file sae103-forever:/work/sae103
done

docker container stop sae103-forever 
echo y | docker container prune 
docker volume rm sae103
