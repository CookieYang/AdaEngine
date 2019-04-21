#!/usr/bin/env python
import os

env = Environment()
Export('env')
SConscript("main/SCsub")
