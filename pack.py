#!/usr/bin/env python3

import argparse
import json
import numpy as np
from PIL import Image

path = "run/tiles/"
parser = argparse.ArgumentParser()
parser.add_argument("tilemap", help="name of tilemap to pack")
args = parser.parse_args()

print("Packing tilemap `{}`...".format(args.tilemap))

with open(path + "{}.json".format(args.tilemap)) as f:
    data = json.load(f)
    tiles_f = [ path + "{}/{}.png".format(args.tilemap, t["name"]) for t in data["tiles"] ]
    tiles_i = np.hstack(np.asarray(i) for i in [ Image.open(t) for t in tiles_f ])
    Image.fromarray(tiles_i).save(path + "{}_pack.png".format(args.tilemap))
