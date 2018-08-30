# 7days
[![Build Status](https://travis-ci.com/aszkid/7days.svg?token=9ZEmBfsVntWTpozGw8zE&branch=travis)](https://travis-ci.com/aszkid/7days)
## (1) Requirements
*7days* requires
- `SFML` >=2.5.0 for everything,
- `python3` for tilemap packing, with `numpy` and `Pillow` (`PIL`).

### Debian/Ubuntu systems
```
chmod +x deps-ubuntu.sh
./deps-ubuntu.sh
```

### Other systems
For now, manually.


## (2) Building
### Tile maps
Tile maps are built with the very primitive script `pack.py`, which takes a single argument `<tilemap>`.

`pack.py` will open `run/tiles/<tilemap>.json`, which describes the tilemap to be constructed.
The script expects a `size` key (integer) with the tile size, and a key `tiles` with an array of objects containing a `name` key (string).
Each `name` value points to a `.png` tile in `run/tiles/<tilemap>/<name>.png`.

`pack.py` packs all the tiles described, for now horizontally.
At runtime, tiles are identified by the horizontal (L-to-R) order in which they appear.

### Unix systems
```
chmod +x configure
SFML_DIR=/blah/sfml ./configure
make
```

### Other systems
For now, not considered.


## (3) Running
The `run` folder contains all runtime information.
For now, the game assumes an executing path 1-level deep into the project root (e.g. it fetches `../run/config.json`).
