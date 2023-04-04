#!/usr/bin/env bash
glslangValidator -o ../vert.spv -V shader.vert
glslangValidator -o ../frag.spv -V shader.frag