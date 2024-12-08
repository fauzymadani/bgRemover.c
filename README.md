# bgRemover.c
a background remover with c!!

## Requirements
- `g++`
- `gcc`
- `libopencv-dev`

## Installation 
```bash
sudo apt install libopencv-dev #debian based distro
git clone https://github.com/fauzymadani/bgRemover.c.git
cd bgRemover.c
g++ -o remove_bg main.c `pkg-config --cflags --libs opencv4`
```

## Usage example
supported extension: `jpeg` only.
```bash
./remove_bg input.jpeg output.png
```
Use with image that have a green background!.
this tools is not serious, i'm just bored and still under development.
