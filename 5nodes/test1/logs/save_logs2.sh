#!/bin/bash

docker logs daemon4$1 > daemon4$1.log
docker logs daemon5$1 > daemon5$1.log
docker logs coordinator4$1 > coordinator4$1.log
docker logs coordinator5$1 > coordinator5$1.log
