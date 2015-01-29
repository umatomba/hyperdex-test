#!/bin/bash

docker logs daemon1$1 > daemon1$1.log
docker logs daemon2$1 > daemon2$1.log
docker logs daemon3$1 > daemon3$1.log
docker logs coordinator1$1 > coordinator1$1.log
docker logs coordinator2$1 > coordinator2$1.log
docker logs coordinator3$1 > coordinator3$1.log
