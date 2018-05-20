# remap

## Description

`remap` allows you to remap the colors of an image to a limited set of colors specified by your palette.

## Installation

```bash
git clone https://github.com/bernhardfritz/remap.git
cd remap
mkdir build
cd build
cmake ..
make
make install
```

## Usage

```bash
remap inputFilename paletteFilename outputFilename
```

## Example

```
remap dungeon.png endesga-32-1x.png output.png
```

![dungeon.png](dungeon.png)

![endesga-32-1x.png](endesga-32-32x.png)

![output.png](output.png)
