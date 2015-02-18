#!/bin/bash

while true; do { cat policy.xml; } | nc -l 843; done

