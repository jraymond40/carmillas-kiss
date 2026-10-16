#!/bin/bash
export MUDLIB_ABS_DIR="$PWD"

# Replaces the variables and outputs to ck.cfg
envsubst < ck.cfg.template > ck.cfg

../driver ck.cfg

